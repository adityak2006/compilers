#include "ast.h"
#include "symbol_table.h"

#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/Location.h"
#include "mlir/IR/Attributes.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlowOps.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <unordered_set>

using namespace mlir;
using namespace std;


static Type mapType(MLIRContext &ctx, DataTypes t)
{
    switch (t)
    {
    case INT_TYPE:
        return IntegerType::get(&ctx, 32);
    case FLOAT_TYPE:
        return Float64Type::get(&ctx);
    case BOOL_TYPE:
        return IntegerType::get(&ctx, 1);
    case VOID_TYPE:
    default:
        return mlir::NoneType::get(&ctx);
    }
}

class MLIRCodegenVisitor : public ASTVisitor
{
public:
    MLIRCodegenVisitor() : context(), builder(&context)
    {
        context.getOrLoadDialect<func::FuncDialect>();
        context.getOrLoadDialect<arith::ArithDialect>();
        context.getOrLoadDialect<memref::MemRefDialect>();
        context.getOrLoadDialect<scf::SCFDialect>();
        context.getOrLoadDialect<cf::ControlFlowDialect>();
        module = ModuleOp::create(builder.getUnknownLoc());
    }

    ModuleOp getModule() { return module; }

    void setInsertionPointToStart(Block *b) { builder.setInsertionPointToStart(b); }
    Block *getModuleBody() { return module.getBody(); }


    void visit(StmtNode &node) override
    {
        switch (node.nodeType)
        {
        case ASTNodeType::CmpdStmtNode:
            visit(static_cast<CmpdStmtNode &>(node));
            break;
        case ASTNodeType::ExprStmtNode:
            visit(static_cast<ExprStmtNode &>(node));
            break;
        case ASTNodeType::ReturnNode:
            visit(static_cast<ReturnNode &>(node));
            break;
        case ASTNodeType::IfNode:
            visit(static_cast<IfNode &>(node));
            break;
        case ASTNodeType::WhileNode:
            visit(static_cast<WhileNode &>(node));
            break;
        case ASTNodeType::ForNode:
            visit(static_cast<ForNode &>(node));
            break;
        case ASTNodeType::BreakNode:
            visit(static_cast<BreakNode &>(node));
            break;
        case ASTNodeType::ContinueNode:
            visit(static_cast<ContinueNode &>(node));
            break;
        default:
            cerr << "Error: Unhandled StmtNode type in MLIRCodegenVisitor." << endl;
            break;
        }
    }

    void visit(DeclNode &node) override
    {
        bool isGlobal = (currentFunctionEntry == nullptr);
        Type baseType = mapType(context, node.type->type);

        for (InitDeclarator *initDecl : node.decls)
        {
            if (!initDecl || !initDecl->declarator)
                continue;

            string varName = initDecl->declarator->id;
            bool isConst = node.type ? node.type->constFlag : false;

            MemRefType slotType;
            if (initDecl->declarator->arrayFlag)
            {
                SmallVector<int64_t> shape;
                for (int s : initDecl->declarator->arraySizes)
                {
                    shape.push_back((int64_t)s);
                }
                slotType = MemRefType::get(shape, baseType);
            }
            else
            {
                slotType = MemRefType::get({}, baseType); 
            }

            if (isGlobal)
            {
                globalVars.insert(varName);
                Attribute initAttr;
                if (initDecl->initializer && initDecl->initializer->expr)
                {
                    Attribute val = getConstantAttr(initDecl->initializer->expr, baseType);
                    RankedTensorType tensorTy =
                        RankedTensorType::get({}, baseType);
                    initAttr = DenseElementsAttr::get(tensorTy, val);
                }

                IntegerAttr alignment = nullptr;

                builder.create<mlir::memref::GlobalOp>(
                    builder.getUnknownLoc(),
                    (llvm::StringRef)varName,
                    builder.getStringAttr("private"),
                    slotType,
                    initAttr,
                    isConst,
                    alignment                         
                );
            }
            else
            {
                Value slot = builder.create<memref::AllocOp>(builder.getUnknownLoc(), slotType);
                valueTable[varName] = slot;

                if (initDecl->initializer && initDecl->initializer->expr)
                {
                    Value rhs = lowerExpr(*initDecl->initializer->expr);
                    auto eltType = slotType.getElementType();
                    if (rhs.getType() != eltType)
                    {
                        rhs = createCast(rhs, eltType);
                    }
                    builder.create<memref::StoreOp>(builder.getUnknownLoc(), rhs, slot);
                }
            }
        }
    }

    void visit(FuncNode &node) override
    {
        SmallVector<Type, 4> argTypes;
        for (auto p : node.params)
        {
            if (!p || !p->type)
                continue;

            if (p->declarator && !p->declarator->arraySizes.empty())
            {
                SmallVector<int64_t> shape;
                for (int s : p->declarator->arraySizes)
                    shape.push_back((int64_t)s);
                Type elt = mapType(context, p->type->type);
                argTypes.push_back(MemRefType::get(shape, elt));
            }
            else
            {
                argTypes.push_back(mapType(context, p->type->type));
            }
        }

        SmallVector<Type, 1> retTypes;
        if (node.returnType)
        {
            Type maybeRet = mapType(context, node.returnType->type);
            if (!mlir::isa<mlir::NoneType>(maybeRet))
            {
                retTypes.push_back(maybeRet);
            }
        }
        auto ftype = FunctionType::get(&context, argTypes, retTypes);
        auto fn = func::FuncOp::create(builder.getUnknownLoc(), node.name, ftype);
        module.push_back(fn);
        auto &entry = *fn.addEntryBlock();
        auto oldEntry = currentFunctionEntry;
        currentFunctionEntry = &entry;

        builder.setInsertionPointToStart(&entry);
        valueTable.clear();

        for (unsigned i = 0; i < node.params.size(); ++i)
        {
            ParamNode *p = node.params[i];
            if (!p || !p->declarator)
                continue;

            std::string pname = p->declarator->id;
            Value arg = entry.getArgument(i);

            if (mlir::isa<MemRefType>(arg.getType()))
            {
                valueTable[pname] = arg;
            }
            else
            {
                auto slot = builder.create<memref::AllocOp>(
                    builder.getUnknownLoc(),
                    MemRefType::get({}, arg.getType()));

                builder.create<memref::StoreOp>(
                    builder.getUnknownLoc(), arg, slot);

                valueTable[pname] = slot;
            }
        }

        if (node.body)
            visit(*node.body);

        currentFunctionEntry = oldEntry;
        builder.setInsertionPointToEnd(module.getBody());
    }

    void visit(CmpdStmtNode &node) override
    {
        for (auto d : node.declarations)
        {
            if (d)
                visit(*d);
        }

        for (auto s : node.statements)
        {
            if (!s)
                continue;
            if (isBlockTerminated())
            {
                break;
            }
            visit(*s);
        }
    }

    void visit(ExprStmtNode &node) override
    {
        if (node.expr)
        {
            lowerExpr(*node.expr); 
        }
    }

    void visit(ReturnNode &node) override
    {
        if (node.expr)
        {
            Value val = lowerExpr(*node.expr);
            builder.create<func::ReturnOp>(builder.getUnknownLoc(), val);
        }
        else
        {
            builder.create<func::ReturnOp>(builder.getUnknownLoc());
        }
    }

    void visit(BreakNode &node) override
    {
        builder.create<cf::BranchOp>(builder.getUnknownLoc(), DestStack.back());
    }

    void visit(ContinueNode &node) override
    {
        builder.create<cf::BranchOp>(builder.getUnknownLoc(), DestStack.back());
    }

    void visit(IfNode &node) override
    {
        Block *origBlock = builder.getInsertionBlock();
        Region *parentRegion = origBlock->getParent();

        Value cond = lowerExpr(*node.condition);
        if (!cond.getType().isInteger(1))
            cond = coerceToBool(cond);

        Block *thenBlock = builder.createBlock(parentRegion);
        Block *afterBlock = builder.createBlock(parentRegion);
        Block *elseBlock = afterBlock;
        if (node.elseBranch)
        {
            elseBlock = builder.createBlock(parentRegion);
        }

        builder.setInsertionPointToEnd(origBlock);
        builder.create<cf::CondBranchOp>(builder.getUnknownLoc(), cond, thenBlock, elseBlock);

        builder.setInsertionPointToStart(thenBlock);
        if (node.thenBranch)
            visit(*node.thenBranch);

        if (!isBlockTerminated())
        {
            builder.create<cf::BranchOp>(builder.getUnknownLoc(), afterBlock);
        }

        if (node.elseBranch)
        {
            builder.setInsertionPointToStart(elseBlock);
            visit(*node.elseBranch);

            if (!isBlockTerminated())
            {
                builder.create<cf::BranchOp>(builder.getUnknownLoc(), afterBlock);
            }
        }

        builder.setInsertionPointToStart(afterBlock);
    }

    void visit(WhileNode &node) override
    {
        Block *origBlock = builder.getInsertionBlock();
        Region *parentRegion = origBlock->getParent();

        Block *condBlock = builder.createBlock(parentRegion);
        Block *bodyBlock = builder.createBlock(parentRegion);
        Block *afterBlock = builder.createBlock(parentRegion);

        DestStack.push_back(condBlock);

        builder.setInsertionPointToEnd(origBlock);
        if (!isBlockTerminated())
        {
            builder.create<cf::BranchOp>(builder.getUnknownLoc(), condBlock);
        }

        builder.setInsertionPointToStart(condBlock);
        Value cond = lowerExpr(*node.condition);
        if (!cond.getType().isInteger(1))
            cond = coerceToBool(cond);
        builder.create<cf::CondBranchOp>(builder.getUnknownLoc(), cond, bodyBlock, afterBlock);

        builder.setInsertionPointToStart(bodyBlock);
        if (node.body)
            visit(*node.body);

        if (!isBlockTerminated())
        {
            builder.create<cf::BranchOp>(builder.getUnknownLoc(), condBlock);
        }

        DestStack.pop_back();
        builder.setInsertionPointToStart(afterBlock);
    }

    void visit(ForNode &node) override
    {
        if (node.init)
        {
            if (auto st = dynamic_cast<StmtNode *>(node.init))
                visit(*st);
            else if (auto decl = dynamic_cast<DeclNode *>(node.init))
                visit(*decl);
            else if (auto ex = dynamic_cast<ExprNode *>(node.init))
                lowerExpr(*ex);
        }

        Block *origBlock = builder.getInsertionBlock();
        Region *region = origBlock->getParent();

        Block *condBlock = builder.createBlock(region);
        Block *bodyBlock = builder.createBlock(region);
        Block *incBlock = builder.createBlock(region);
        Block *afterBlock = builder.createBlock(region);

        DestStack.push_back(incBlock);

        builder.setInsertionPointToEnd(origBlock);
        if (!isBlockTerminated())
        {
            builder.create<cf::BranchOp>(builder.getUnknownLoc(), condBlock);
        }

        builder.setInsertionPointToStart(condBlock);
        Value cond;
        if (node.condition)
            cond = lowerExpr(*node.condition);
        else
            cond = builder.create<arith::ConstantIntOp>(builder.getUnknownLoc(), 1, 1);

        if (!cond.getType().isInteger(1))
            cond = coerceToBool(cond);

        builder.create<cf::CondBranchOp>(builder.getUnknownLoc(), cond, bodyBlock, afterBlock);

        builder.setInsertionPointToStart(bodyBlock);
        if (node.body)
            visit(*node.body);

        if (!isBlockTerminated())
        {
            builder.create<cf::BranchOp>(builder.getUnknownLoc(), incBlock);
        }

        builder.setInsertionPointToStart(incBlock);
        if (node.increment)
        {
            if (auto ex = dynamic_cast<ExprNode *>(node.increment))
                lowerExpr(*ex);
        }

        if (!isBlockTerminated())
        {
            builder.create<cf::BranchOp>(builder.getUnknownLoc(), condBlock);
        }

        DestStack.pop_back();
        builder.setInsertionPointToStart(afterBlock);
    }

    Value lowerExpr(ExprNode &expr)
    {
        switch (expr.nodeType)
        {
        case ASTNodeType::LiteralIntNode:
            return lowerLiteralInt(static_cast<LiteralIntNode &>(expr));
        case ASTNodeType::LiteralFloatNode:
            return lowerLiteralFloat(static_cast<LiteralFloatNode &>(expr));
        case ASTNodeType::LiteralBoolNode:
            return lowerLiteralBool(static_cast<LiteralBoolNode &>(expr));
        case ASTNodeType::IdentifierNode:
            return lowerIdentifier(static_cast<IdentifierNode &>(expr));
        case ASTNodeType::BinaryExprNode:
            return lowerBinary(static_cast<BinaryExprNode &>(expr));
        case ASTNodeType::UnaryExprNode:
            return lowerUnary(static_cast<UnaryExprNode &>(expr));
        case ASTNodeType::AssignmentNode:
            return lowerAssignment(static_cast<AssignmentNode &>(expr));
        case ASTNodeType::CallNode:
            return lowerCall(static_cast<CallNode &>(expr));
        case ASTNodeType::CommaExprNode:
            return lowerComma(static_cast<CommaExprNode &>(expr));
        case ASTNodeType::ArrayAccessNode:
            return lowerArrayAccess(static_cast<ArrayAccessNode &>(expr));
        case ASTNodeType::CastExprNode:
            return lowerCast(static_cast<CastExprNode &>(expr));
        default:
            return builder.create<arith::ConstantIntOp>(builder.getUnknownLoc(), 0, 32);
        }
    }

    Value lowerLiteralInt(LiteralIntNode &n)
    {
        return builder.create<arith::ConstantIntOp>(builder.getUnknownLoc(), n.value, 32);
    }

    Value lowerLiteralFloat(LiteralFloatNode &n)
    {
        auto ty = Float64Type::get(&context);
        auto attr = FloatAttr::get(ty, APFloat(n.value));
        return builder.create<arith::ConstantOp>(builder.getUnknownLoc(), ty, attr);
    }

    Value lowerLiteralBool(LiteralBoolNode &n)
    {
        return builder.create<arith::ConstantIntOp>(builder.getUnknownLoc(), n.value ? 1 : 0, 1);
    }

    Value lowerIdentifier(IdentifierNode &n)
    {
        if (globalVars.count(n.id))
        {
            auto globalOp = module.lookupSymbol<memref::GlobalOp>(n.id);
            auto type = globalOp.getType();
            Value addr = builder.create<memref::GetGlobalOp>(builder.getUnknownLoc(), type, n.id);

            if (auto memRefType = mlir::dyn_cast<MemRefType>(type))
            {
                if (memRefType.getRank() == 0)
                {
                    return builder.create<memref::LoadOp>(builder.getUnknownLoc(), addr);
                }
                else
                {
                    return addr;
                }
            }
            return addr;
        }
        auto it = valueTable.find(n.id);
        Value slot = it->second; 
        auto type = slot.getType();

        if (auto memRefType = mlir::dyn_cast<MemRefType>(type))
        {

            if (memRefType.getRank() == 0)
            {
                return builder.create<memref::LoadOp>(builder.getUnknownLoc(), slot);
            }
            else
            {
                return slot;
            }
        }
        return slot;
    }

    Value lowerBinary(BinaryExprNode &n)
    {
        string op = n.op;

        if (op == "AND" || op == "&&")
        {
            Value l = lowerExpr(*n.leftOperand);
            Value l_bool = coerceToBool(l);
            auto ifOp = builder.create<scf::IfOp>(
                builder.getUnknownLoc(), builder.getIntegerType(1), l_bool, true);
            builder.setInsertionPointToStart(&ifOp.getThenRegion().front());
            Value r = lowerExpr(*n.rightOperand);
            builder.create<scf::YieldOp>(builder.getUnknownLoc(), coerceToBool(r));
            builder.setInsertionPointToStart(&ifOp.getElseRegion().front());
            auto falseVal = builder.create<arith::ConstantIntOp>(builder.getUnknownLoc(), 0, 1);
            builder.create<scf::YieldOp>(builder.getUnknownLoc(), mlir::ValueRange{falseVal});
            builder.setInsertionPointAfter(ifOp);
            return ifOp.getResult(0);
        }

        if (op == "OR" || op == "||")
        {
            Value l = lowerExpr(*n.leftOperand);
            Value l_bool = coerceToBool(l);
            auto ifOp = builder.create<scf::IfOp>(
                builder.getUnknownLoc(), builder.getIntegerType(1), l_bool, true);
            builder.setInsertionPointToStart(&ifOp.getThenRegion().front());
            auto trueVal = builder.create<arith::ConstantIntOp>(builder.getUnknownLoc(), 1, 1);
            builder.create<scf::YieldOp>(builder.getUnknownLoc(), mlir::ValueRange{trueVal});
            builder.setInsertionPointToStart(&ifOp.getElseRegion().front());
            Value r = lowerExpr(*n.rightOperand);
            builder.create<scf::YieldOp>(builder.getUnknownLoc(), coerceToBool(r));
            builder.setInsertionPointAfter(ifOp);
            return ifOp.getResult(0);
        }

        Value l = lowerExpr(*n.leftOperand);
        Value r = lowerExpr(*n.rightOperand);
        bool isFloat = mlir::dyn_cast<FloatType>(l.getType()) ||
                       mlir::dyn_cast<FloatType>(r.getType());

        if (isFloat)
        {
            auto f64 = Float64Type::get(&context);
            if (!mlir::dyn_cast<FloatType>(l.getType()))
            {
                l = createCast(l, f64);
            }
            if (!mlir::dyn_cast<FloatType>(r.getType()))
            {
                r = createCast(r, f64);
            }
        }

        if (isFloat)
        {
            if (op == "+")
                return builder.create<arith::AddFOp>(builder.getUnknownLoc(), l, r);
            if (op == "-")
                return builder.create<arith::SubFOp>(builder.getUnknownLoc(), l, r);
            if (op == "*")
                return builder.create<arith::MulFOp>(builder.getUnknownLoc(), l, r);
            if (op == "/")
                return builder.create<arith::DivFOp>(builder.getUnknownLoc(), l, r);
            if (op == "==")
                return builder.create<arith::CmpFOp>(builder.getUnknownLoc(), arith::CmpFPredicate::OEQ, l, r);
            if (op == "!=")
                return builder.create<arith::CmpFOp>(builder.getUnknownLoc(), arith::CmpFPredicate::ONE, l, r);
            if (op == "<")
                return builder.create<arith::CmpFOp>(builder.getUnknownLoc(), arith::CmpFPredicate::OLT, l, r);
            if (op == "<=")
                return builder.create<arith::CmpFOp>(builder.getUnknownLoc(), arith::CmpFPredicate::OLE, l, r);
            if (op == ">")
                return builder.create<arith::CmpFOp>(builder.getUnknownLoc(), arith::CmpFPredicate::OGT, l, r);
            if (op == ">=")
                return builder.create<arith::CmpFOp>(builder.getUnknownLoc(), arith::CmpFPredicate::OGE, l, r);
        }
        else
        {
            if (op == "+")
                return builder.create<arith::AddIOp>(builder.getUnknownLoc(), l, r);
            if (op == "-")
                return builder.create<arith::SubIOp>(builder.getUnknownLoc(), l, r);
            if (op == "*")
                return builder.create<arith::MulIOp>(builder.getUnknownLoc(), l, r);
            if (op == "/")
                return builder.create<arith::DivSIOp>(builder.getUnknownLoc(), l, r); // S = Signed
            if (op == "%")
                return builder.create<arith::RemSIOp>(builder.getUnknownLoc(), l, r); // S = Signed
            if (op == "&")
                return builder.create<arith::AndIOp>(builder.getUnknownLoc(), l, r);
            if (op == "|")
                return builder.create<arith::OrIOp>(builder.getUnknownLoc(), l, r);
            if (op == "^")
                return builder.create<arith::XOrIOp>(builder.getUnknownLoc(), l, r);
            if (op == "<<")
                return builder.create<arith::ShLIOp>(builder.getUnknownLoc(), l, r);
            if (op == ">>")
                return builder.create<arith::ShRSIOp>(builder.getUnknownLoc(), l, r); // S = Signed
            if (op == "==")
                return builder.create<arith::CmpIOp>(builder.getUnknownLoc(), arith::CmpIPredicate::eq, l, r);
            if (op == "!=")
                return builder.create<arith::CmpIOp>(builder.getUnknownLoc(), arith::CmpIPredicate::ne, l, r);
            if (op == "<")
                return builder.create<arith::CmpIOp>(builder.getUnknownLoc(), arith::CmpIPredicate::slt, l, r);
            if (op == "<=")
                return builder.create<arith::CmpIOp>(builder.getUnknownLoc(), arith::CmpIPredicate::sle, l, r);
            if (op == ">")
                return builder.create<arith::CmpIOp>(builder.getUnknownLoc(), arith::CmpIPredicate::sgt, l, r);
            if (op == ">=")
                return builder.create<arith::CmpIOp>(builder.getUnknownLoc(), arith::CmpIPredicate::sge, l, r);
        }
        return l;
    }

    Value lowerUnary(UnaryExprNode &n)
    {
        Value opv = lowerExpr(*n.operand);
        if (!opv)
        { 
            return nullptr;
        }

        switch (n.op)
        {

        case UnaryOpType::ADD_OP:
            return opv;

        case UnaryOpType::SUB_OP:
            if (mlir::dyn_cast<FloatType>(opv.getType()))
            {
                return builder.create<arith::NegFOp>(builder.getUnknownLoc(), opv);
            }
            else if (mlir::dyn_cast<IntegerType>(opv.getType()))
            {
                auto zero = builder.create<arith::ConstantIntOp>(
                    builder.getUnknownLoc(), 0, 32);
                return builder.create<arith::SubIOp>(builder.getUnknownLoc(), zero, opv);
            }

        case UnaryOpType::BITNOT_OP:
            if (mlir::dyn_cast<IntegerType>(opv.getType()))
            {
                auto allOnes = builder.create<arith::ConstantIntOp>(
                    builder.getUnknownLoc(), -1, 32);
                return builder.create<arith::XOrIOp>(builder.getUnknownLoc(), opv, allOnes);
            }
            return opv;

        case UnaryOpType::LOGICALNOT_OP:
        {
            Value boolVal = coerceToBool(opv);
            auto one = builder.create<arith::ConstantIntOp>(builder.getUnknownLoc(), 1, 1);
            return builder.create<arith::XOrIOp>(builder.getUnknownLoc(), boolVal, one);
        }

        default:
            return opv;
        }

        return opv;
    }

    Value lowerAssignment(AssignmentNode &n)
    {
        Value rhs = lowerExpr(*n.value);

        Value slot; 
        Type eltType;

        if (auto arr = dynamic_cast<ArrayAccessNode *>(n.target))
        {
            SmallVector<Value, 4> idxs;
            if (!collectArrayAccess(arr, slot, idxs))
            {
                cerr << "Error: Invalid array access in assignment." << endl;
                return rhs;
            }
            eltType = mlir::dyn_cast<MemRefType>(slot.getType()).getElementType();

            if (rhs.getType() != eltType)
            {
                rhs = createCast(rhs, eltType);
            }
            builder.create<memref::StoreOp>(builder.getUnknownLoc(), rhs, slot, idxs);
            return rhs;
        }

        string varName;
        if (auto id = dynamic_cast<IdentifierNode *>(n.target))
        {
            varName = id->id;
        }

        if (globalVars.count(varName))
        {
            auto globalOp = module.lookupSymbol<memref::GlobalOp>(varName);
            slot = builder.create<memref::GetGlobalOp>(builder.getUnknownLoc(), globalOp.getType(), varName);
            eltType = mlir::dyn_cast<MemRefType>(globalOp.getType()).getElementType();
        }
        else
        {
            slot = valueTable[varName];
            eltType = mlir::dyn_cast<MemRefType>(slot.getType()).getElementType();
        }

        if (rhs.getType() != eltType)
        {
            rhs = createCast(rhs, eltType);
        }

        builder.create<memref::StoreOp>(builder.getUnknownLoc(), rhs, slot);
        return rhs;
    }

    Value lowerCall(CallNode &n)
    {
        auto id = dynamic_cast<IdentifierNode *>(n.callee);
        string funcName = id->id;

        auto toLower = [&](const std::string &s)
        {
            std::string out;
            out.reserve(s.size());
            for (char c : s)
                out.push_back(std::tolower(c));
            return out;
        };

        std::string lowerName = toLower(funcName);

        auto fn = module.lookupSymbol<func::FuncOp>(funcName);

        SmallVector<Value, 4> args;
        for (auto arg : n.arguments)
        {
            args.push_back(lowerExpr(*arg));
        }
        
        auto call = builder.create<func::CallOp>(
            builder.getUnknownLoc(),
            fn,
            args
        );

        if (call.getResults().empty())
        {
            return builder.create<arith::ConstantIntOp>(builder.getUnknownLoc(), 0, 32);
        }
        else
        {
            return call.getResult(0);
        }
    }

    Value lowerComma(CommaExprNode &n)
    {
        Value result;
        for (auto expr : n.expressions)
        {
            if (expr)
            {
                result = lowerExpr(*expr);
            }
        }
        return result;
    }

    Value lowerArrayAccess(ArrayAccessNode &n)
    {
        Value base;
        SmallVector<Value, 4> idxs;

        if (!collectArrayAccess(&n, base, idxs))
        {
            cerr << "Error: Invalid array access." << endl;
            return builder.create<arith::ConstantIntOp>(builder.getUnknownLoc(), 0, 32);
        }
        return builder.create<memref::LoadOp>(builder.getUnknownLoc(), base, idxs);
    }

    Value lowerCast(CastExprNode &n)
    {
        Value v = lowerExpr(*n.expr);
        Type tgt = mapType(context, n.targetType->type);
        return createCast(v, tgt);
    }

    bool collectArrayAccess(ArrayAccessNode *node, Value &outBase, SmallVectorImpl<Value> &outIndices)
    {
        ExprNode *arr = node->array;

        if (auto inner = dynamic_cast<ArrayAccessNode *>(arr))
        {
            if (!collectArrayAccess(inner, outBase, outIndices))
            {
                return false;
            }
        }
        else
        {
            Value base = lowerExpr(*arr);

            if (!base)
            {
                return false;
            }
            if (auto memRefType = mlir::dyn_cast<MemRefType>(base.getType()))
            {
                if (memRefType.getRank() == 0)
                {
                    cerr << "Error: Cannot index scalar variable/value." << endl;
                    return false;
                }
            }
            else
            {
                cerr << "Error: Expression is not a subscriptable array/memref." << endl;
                return false;
            }
            outBase = base;
        }

        Value idx = lowerExpr(*node->index);
        if (!idx.getType().isIndex())
        {
            idx = builder.create<arith::IndexCastOp>(builder.getUnknownLoc(), IndexType::get(&context), idx);
        }
        outIndices.push_back(idx);
        return true;
    }


private:
    MLIRContext context;
    OpBuilder builder{&context};
    ModuleOp module{nullptr};

    unordered_map<string, Value> valueTable;
    std::vector<Block *> DestStack;

    Block *currentFunctionEntry = nullptr;

    std::unordered_set<std::string> globalVars;

    bool isBlockTerminated()
    {
        Block *currentBlock = builder.getInsertionBlock();
        if (!currentBlock)
            return true;
        return !currentBlock->empty() &&
               currentBlock->back().hasTrait<OpTrait::IsTerminator>();
    }

    Attribute getConstantAttr(ExprNode *expr, Type type)
    {
        if (auto lint = dynamic_cast<LiteralIntNode *>(expr))
        {
            if (auto intTy = mlir::dyn_cast<IntegerType>(type))
            {
                return builder.getIntegerAttr(type, lint->value);
            }
            if (auto floatTy = mlir::dyn_cast<FloatType>(type))
            {
                return builder.getFloatAttr(type, (double)lint->value);
            }
        }
        if (auto lflt = dynamic_cast<LiteralFloatNode *>(expr))
        {
            if (auto floatTy = mlir::dyn_cast<FloatType>(type))
            {
                return builder.getFloatAttr(type, lflt->value);
            }
            if (auto intTy = mlir::dyn_cast<IntegerType>(type))
            {
                return builder.getIntegerAttr(type, (int)lflt->value);
            }
        }
        if (auto lbool = dynamic_cast<LiteralBoolNode *>(expr))
        {
            if (auto intTy = mlir::dyn_cast<IntegerType>(type))
            {
                return builder.getIntegerAttr(type, lbool->value ? 1 : 0);
            }
        }
        return Attribute();
    }

    Value coerceToBool(Value v)
    {
        if (v.getType().isInteger(1))
            return v;

        if (auto it = mlir::dyn_cast<IntegerType>(v.getType()))
        {
            auto zero = builder.create<arith::ConstantIntOp>(builder.getUnknownLoc(), 0, it.getWidth());
            return builder.create<arith::CmpIOp>(builder.getUnknownLoc(), arith::CmpIPredicate::ne, v, zero);
        }
        if (mlir::isa<FloatType>(v.getType()))
        {
            auto zeroAttr = FloatAttr::get(mlir::cast<FloatType>(v.getType()), APFloat(0.0));
            auto zero = builder.create<arith::ConstantOp>(builder.getUnknownLoc(), v.getType(), zeroAttr);
            return builder.create<arith::CmpFOp>(builder.getUnknownLoc(), arith::CmpFPredicate::UNE, v, zero);
        }
        return builder.create<arith::ConstantIntOp>(builder.getUnknownLoc(), 1, 1);
    }

    Value createCast(Value v, Type tgt)
    {
        Type src = v.getType();
        if (src == tgt)
            return v;

        if (mlir::isa<IntegerType>(src) && mlir::isa<FloatType>(tgt))
            return builder.create<arith::SIToFPOp>(builder.getUnknownLoc(), tgt, v);
        if (mlir::isa<FloatType>(src) && mlir::isa<IntegerType>(tgt))
            return builder.create<arith::FPToSIOp>(builder.getUnknownLoc(), tgt, v);
        if (mlir::isa<IntegerType>(src) && mlir::isa<IntegerType>(tgt))
        {
            unsigned srcW = mlir::cast<IntegerType>(src).getWidth();
            unsigned dstW = mlir::cast<IntegerType>(tgt).getWidth();
            if (srcW < dstW)
                return builder.create<arith::ExtSIOp>(builder.getUnknownLoc(), tgt, v);
            else if (srcW > dstW)
                return builder.create<arith::TruncIOp>(builder.getUnknownLoc(), tgt, v);
            else
                return v;
        }
        return v;
    }
};