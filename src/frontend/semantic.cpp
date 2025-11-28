#include "semantic.h"
#include <sstream>
#include <iostream>
#include <memory>
#include <typeinfo>

Symbol* SemanticVisitor::makeSymbolForType(const std::string &name, DataTypes t)
{
    switch(t)
    {
        case INT_TYPE:        return new IntSym(name, 0, false, 0, 0);
        case FLOAT_TYPE:      return new FloatSym(name, 0.0, false, 0, 0);
        case BOOL_TYPE:       return new BoolSym(name, false, false, 0, 0);
        case TIMESERIES_TYPE: return new TimeseriesSym(name, 0, 0, 0);
        default:
            // DO not auto-declare variables 
            return nullptr;
    }
}

void SemanticVisitor::addError(const std::string &msg)
{
    errors.push_back(msg);
    return;
}

void SemanticVisitor::addErrorFmt(const std::string &fmt, const std::string &arg)
{
    std::string s = fmt;
    size_t p = s.find("%s");
    if(p != std::string::npos) s.replace(p, 2, arg);
    addError(s);
    return;
}

std::string SemanticVisitor::typeToString(DataTypes t) const
{
    switch (t)
    {
        case INT_TYPE: return "int";
        case FLOAT_TYPE: return "float";
        case BOOL_TYPE: return "bool";
        case VOID_TYPE: return "void";
        case RGM_TYPE: return "regime";
        case TIMESERIES_TYPE: return "timeseries";
        case GROUP_TYPE: return "group";
    }
        
    return "unknown";
}

bool SemanticVisitor::isNumeric(DataTypes t) const
{
    return (t == INT_TYPE || t == FLOAT_TYPE);
}

bool SemanticVisitor::areComparable(DataTypes a, DataTypes b) const
{
    return ((a == b) || (isNumeric(a) && isNumeric(b))); // allow comparisons between int and float     
}

Symbol *SemanticVisitor::lookup(const std::string &name)
{
    if(!symtab.currentScope) return nullptr;
    return symtab.currentScope->lookup(name);
}

bool SemanticVisitor::define(std::unique_ptr<Symbol> sym)
{
    if(!symtab.currentScope) return false;
    return symtab.currentScope->define(std::move(sym));
}

bool SemanticVisitor::analyze(ProgramNode *root)
{
    errors.clear();
    inferred.clear();
    resolved.clear();

    // Start with global scope already in symbol table constructor.
    visit(*root);

    if(!errors.empty())
    {
        for (auto &e : errors)
            std::cerr << "Semantic error: " << e << "\n";
    }

    return errors.empty();
}

// Helper to check if a cast between two DataTypes is allowed
bool SemanticVisitor::isCastable(DataTypes from, DataTypes to)
{
    if(from == to) return true;

    if((from == INT_TYPE || from == FLOAT_TYPE) &&
       (to == INT_TYPE || to == FLOAT_TYPE))
        return true;

    if(from == BOOL_TYPE && to == BOOL_TYPE)
        return true;

    return false;
}

// Helper: map SymKind to DataTypes
DataTypes SemanticVisitor::SymKindToDataType(SymKind k)
{
    switch(k)
    {
        case SymKind::Int: return INT_TYPE;
        case SymKind::Float: return FLOAT_TYPE;
        case SymKind::Bool: return BOOL_TYPE;
        case SymKind::Timeseries: return TIMESERIES_TYPE;
        case SymKind::Regime: return RGM_TYPE;
        case SymKind::Group: return GROUP_TYPE;
        case SymKind::Void: return VOID_TYPE;
        default: return INT_TYPE; // fallback
    }
}


// Visitor functions for different node types

void SemanticVisitor::visit(ProgramNode &node)
{
    for(auto d : node.globalDeclarations)
        if(d) d->visitAcceptor(*this);

    for(auto f : node.functions)
        if(f) f->visitAcceptor(*this);

    for(auto g : node.groups)
        if(g) g->visitAcceptor(*this);

    for(auto s : node.strategies)
        if(s) s->visitAcceptor(*this);

    return;
}

void SemanticVisitor::visit(DeclNode &node)
{
    if(!node.type)
    {
        addError("Declaration with missing type");
        return;
    }

    DataTypes dt = node.type->type;
    bool isConst = node.type->constFlag;

    for(auto initDecl : node.decls)
    {
        if(!initDecl || !initDecl->declarator) continue;
        std::string name = initDecl->declarator->id;

        // Create symbol based on declared type
        std::unique_ptr<Symbol> sym;
        switch (dt)
        {
            case INT_TYPE:
                sym = std::make_unique<IntSym>(name, 0, node.type->constFlag, 0, 0);
                break;
            case FLOAT_TYPE:
                sym = std::make_unique<FloatSym>(name, 0.0, node.type->constFlag, 0, 0);
                break;
            case BOOL_TYPE:
                sym = std::make_unique<BoolSym>(name, false, node.type->constFlag, 0, 0);
                break;
            case TIMESERIES_TYPE:
                if(!initDecl->initializer){
                    addErrorFmt("Timeseries '%s' must be initialized at declaration", name);
                    // return;
                }
                
                if(insideIndicator == false){
                    addErrorFmt("Timeseries '%s' declared outside indicator section", initDecl->declarator->id);
                    return;
                }
                sym = std::make_unique<TimeseriesSym>(name, 0, 0, 0);
                break;
            case GROUP_TYPE:
                sym = std::make_unique<GroupSym>(name, 0, 0);
                break;
            case RGM_TYPE:
                if(!initDecl->initializer){
                    addErrorFmt("Regime '%s' must be initialized at declaration", name);
                    // return;
                }

                if(insideRegime == false){
                    addErrorFmt("Regime '%s' declared outside regime section", initDecl->declarator->id);
                    return;
                }
                sym = std::make_unique<RegimeSym>(name, 0, 0);
                break;
            default:
                // unknown/void: create generic Symbol
                sym = std::make_unique<Symbol>(name, SymKind::Int, 0, 0);
                break;
        }

        sym->declared = true;

        if(!define(std::move(sym))) addErrorFmt("Redefinition of symbol '%s'", name);
        
        if(isConst && (!initDecl->initializer || !initDecl->initializer->expr))
        {
            addErrorFmt("Const '%s' must be initialized at declaration", name);
            continue;
        }

        // If initializer exists, analyze it and check type compatibility
        if (initDecl->initializer && initDecl->initializer->expr)
        {
            initDecl->initializer->expr->visitAcceptor(*this);
            DataTypes rhs = inferred[initDecl->initializer->expr];
            
            if(dt == FLOAT_TYPE && rhs == INT_TYPE) {} // works: implicit promotion (optional to warn)
            else if(dt == BOOL_TYPE && rhs == INT_TYPE) {} // works: implicit conversion (optional to warn)
            else if (dt != rhs)
            {      
                std::ostringstream ss;
                ss << "Type mismatch in initializer for " << name << " declared " << typeToString(dt) << ", initializer " << typeToString(rhs);
                addError(ss.str());
            }
        }

    }    
}

void SemanticVisitor::visit(InitDeclarator &node)
{
    // Majority of the work handled in DeclNode
    if (node.initializer)
        node.initializer->visitAcceptor(*this);
}

void SemanticVisitor::visit(Initializer &node)
{
    for (auto init : node.initializerList)
        if (init) init->visitAcceptor(*this);

    if (node.expr)
        node.expr->visitAcceptor(*this);
}

void SemanticVisitor::visit(CmpdStmtNode &node)
{
    if(insideRegime || insideIndicator){
        addError("Nested scopes are not allowed inside regime or indicator sections");
    }
    symtab.enterScope();

    for(auto d : node.declarations)
        if(d) d->visitAcceptor(*this);

    for(auto s : node.statements)
        if(s) s->visitAcceptor(*this);

    symtab.exitScope();
    return;
}

void SemanticVisitor::visit(StmtNode &node)
{
    
    if (auto stmt = dynamic_cast<AssignmentNode*>(&node))
        stmt->visitAcceptor(*this);

    else if (auto stmt = dynamic_cast<ExprStmtNode*>(&node))
        stmt->visitAcceptor(*this);

    else if(auto stmt = dynamic_cast<IfNode*>(&node))
        stmt->visitAcceptor(*this);

    else if(auto stmt = dynamic_cast<WhileNode*>(&node))
        stmt->visitAcceptor(*this);

    else if(auto stmt = dynamic_cast<ForNode*>(&node))
        stmt->visitAcceptor(*this);

    else if(auto stmt = dynamic_cast<ReturnNode*>(&node))
        stmt->visitAcceptor(*this);

    else
        addError("Unknown stmt type");
}

void SemanticVisitor::visit(FuncNode &node)
{
    std::string fname = node.name;

    DataTypes retType = VOID_TYPE;
    if(node.returnType)
        retType = node.returnType->type;

    auto fSym = std::make_unique<FunctionSym>(fname, 0, 0);

    fSym->returnType = std::unique_ptr<Symbol>(
        makeSymbolForType("__ret", retType)
    );

    if(!define(std::move(fSym)))
    {
        addErrorFmt("Redefinition of function '%s'", fname);
    }

    FunctionSym *f = dynamic_cast<FunctionSym*>(lookup(fname));

    symtab.enterScope();
    insideFunction = true;

    DataTypes savedReturnType = currentFunctionReturnType;
    currentFunctionReturnType = retType;

    for(auto p : node.params)
    {
        if(!p) continue;

        std::string pname = p->declarator->id;
        DataTypes ptype = p->type ? p->type->type : INT_TYPE;

        f->parameters.push_back(
            std::unique_ptr<Symbol>(makeSymbolForType(pname, ptype))
        );

        std::unique_ptr<Symbol> localSym(makeSymbolForType(pname, ptype));
        localSym->declared = true;

        if(!define(std::move(localSym)))
        {
            addError("Parameter '" + pname + "' redeclared in function '" + fname + "'");
        }
    }

    if(node.body)
        node.body->visitAcceptor(*this);

    currentFunctionReturnType = savedReturnType;

    insideFunction = false;
    symtab.exitScope();
}

void SemanticVisitor::visit(IdentifierNode &node)
{
    Symbol *s = lookup(node.id);
    if(!s || s->declared == false)
    {
        addErrorFmt("Undefined identifier '%s'", node.id);  
        resolved[&node] = nullptr;
        inferred[&node] = INT_TYPE;
        return;
    }

    resolved[&node] = s;

    // Maps symbol's kind to DataTypes for expression inference
    DataTypes inferredType = INT_TYPE;
    switch(s->kind)
    {
        case SymKind::Int:
            inferredType = INT_TYPE;
            break;
        case SymKind::Float:
            inferredType = FLOAT_TYPE;
            break;
        case SymKind::Bool:
            inferredType = BOOL_TYPE;
            break;
        case SymKind::Timeseries:
            if(!insideStrategy){
                addErrorFmt("Timeseries '%s' can only be used inside the strategy", node.id);
            }
            inferredType = TIMESERIES_TYPE;
            break;
        case SymKind::Group:
            inferredType = GROUP_TYPE;
            break;
        case SymKind::Regime:
            if(!insideRegime){
                addErrorFmt("Regime '%s' can only be used in regime section or for scoping", node.id);
            }
            inferredType = RGM_TYPE;
            break;
        case SymKind::Function:
            inferredType = VOID_TYPE;
            break;
        case SymKind::Array:
            inferredType = TIMESERIES_TYPE; // fallback
            break; 
        default:
            inferredType = INT_TYPE;
            break;
    }

    inferred[&node] = inferredType;
    return;
}

void SemanticVisitor::visit(LiteralIntNode &node)
{
    inferred[&node] = INT_TYPE;
    return;
}

void SemanticVisitor::visit(LiteralFloatNode &node)
{
    inferred[&node] = FLOAT_TYPE;
    return;
}

void SemanticVisitor::visit(LiteralBoolNode &node)
{
    inferred[&node] = BOOL_TYPE;
    return;
}

void SemanticVisitor::visit(BinaryExprNode &node)
{
    if (node.leftOperand)
        node.leftOperand->visitAcceptor(*this);
    if (node.rightOperand)
        node.rightOperand->visitAcceptor(*this);

    const std::string &op = node.op;

    if (op == "=")
    {
        auto id = dynamic_cast<IdentifierNode*>(node.leftOperand);
        if (!id)
        {
            addError("Left-hand side of assignment is not assignable");
            inferred[&node] = INT_TYPE;
            return;
        }

        Symbol *s = lookup(id->id);
        if(!s)
        {
            inferred[&node] = INT_TYPE;
            return; 
        }

        DataTypes lhs = SymKindToDataType(s->kind);
        DataTypes rhs = INT_TYPE;
        
        if(node.rightOperand && inferred.count(node.rightOperand))
            rhs = inferred[node.rightOperand];

        // Const checks
        if(s->kind == SymKind::Int)
        {
            IntSym *is = dynamic_cast<IntSym *>(s);
            if(is && is->isConst)
                addErrorFmt("Cannot assign to const '%s'", id->id);
        }
        else if(s->kind == SymKind::Float)
        {
            FloatSym *fs = dynamic_cast<FloatSym *>(s);
            if(fs && fs->isConst)
                addErrorFmt("Cannot assign to const '%s'", id->id);
        }
        else if(s->kind == SymKind::Bool)
        {
            BoolSym *bs = dynamic_cast<BoolSym *>(s);
            if(bs && bs->isConst)
                addErrorFmt("Cannot assign to const '%s'", id->id);
        }
        else if(s->kind == SymKind::Timeseries)
        {
            addErrorFmt("Timeseries '%s' cannot be assigned after declaration", id->id);
        }
        else if(s->kind == SymKind::Regime)
        {
            addErrorFmt("Regime '%s' cannot be assigned after declaration", id->id);
        }
        
        // Type mismatch check
        if(lhs != rhs)
        {
            std::ostringstream ss;
            ss << "Type mismatch in assignment (lhs " << typeToString(lhs)
               << ", rhs " << typeToString(rhs) << ")";
            addError(ss.str());
        }

        inferred[&node] = lhs;
        return;
    }

    DataTypes L = INT_TYPE;
    DataTypes R = INT_TYPE;
    if (node.leftOperand && inferred.count(node.leftOperand))
        L = inferred[node.leftOperand];
    if (node.rightOperand && inferred.count(node.rightOperand))
        R = inferred[node.rightOperand];

    if (L == TIMESERIES_TYPE || R == TIMESERIES_TYPE)
    {
        // Arithmetic returns a new TimeSeries
        if (op == "+" || op == "-" || op == "*" || op == "/")
        {
            inferred[&node] = TIMESERIES_TYPE;
            return;
        }

        // Comparisons return a Regime
        if (op == "<" || op == ">" || op == "<=" || op == ">=" || op == "==" || op == "!=")
        {
            inferred[&node] = RGM_TYPE;
            return;
        }

        // Logic (AND/OR) returns a Regime
        if (op == "&&" || op == "||" || op == "AND" || op == "OR")
        {
            inferred[&node] = RGM_TYPE;
            return;
        }
    }

    if (op == "+" || op == "-" || op == "*" || op == "/")
    {
        if (!isNumeric(L) || !isNumeric(R))
        {
            addErrorFmt("Arithmetic operator applied to non-numeric operands ('%s')", op);
            inferred[&node] = INT_TYPE;
            return;
        }
        inferred[&node] = (L == FLOAT_TYPE || R == FLOAT_TYPE) ? FLOAT_TYPE : INT_TYPE;
        return;
    }

    if (op == "<" || op == ">" || op == "<=" || op == ">=" || op == "==" || op == "!=")
    {
        if (!areComparable(L, R))
            addErrorFmt("Comparison between incompatible types ('%s')", op);
        inferred[&node] = BOOL_TYPE;
        return;
    }

    if (op == "&&" || op == "||" || op == "AND" || op == "OR")
    {
        if (L == RGM_TYPE || R == RGM_TYPE)
        {
            inferred[&node] = RGM_TYPE;
            return;
        }

        if (L != BOOL_TYPE || R != BOOL_TYPE)
            addErrorFmt("Logical operator '%s' requires boolean operands", op);
        inferred[&node] = BOOL_TYPE;
        return;
    }

    inferred[&node] = INT_TYPE;
    return;
}

void SemanticVisitor::visit(UnaryExprNode &node)
{
    if(node.operand) node.operand->visitAcceptor(*this);

    DataTypes operandType = INT_TYPE;
    if(node.operand && inferred.count(node.operand)) operandType = inferred[node.operand];

    if((node.op == ADD_OP || node.op == SUB_OP) && !isNumeric(operandType))
    {
        addError("Unary +/- applied to non-numeric operand");
        inferred[&node] = operandType;
    }

    else if(node.op == LOGICALNOT_OP && operandType != BOOL_TYPE)
    {
        addError("Logical not applied to non-boolean operand");
        inferred[&node] = BOOL_TYPE;
    }

    inferred[&node] = operandType;
    return;
}

void SemanticVisitor::visit(AssignmentNode &node)
{

    if(node.target) node.target->visitAcceptor(*this);
    if(node.value) node.value->visitAcceptor(*this);

    auto id = dynamic_cast<IdentifierNode*>(node.target);
    if(!id)
    {
        addError("Left-hand side of assignment is not assignable");
        return;
    }

    if(!resolved.count(id) || resolved[id] == nullptr)
    {
        return;
    }

    Symbol *s = resolved[id];

    DataTypes lhs;
    switch(s->kind)
    {
        case SymKind::Int:       
            if(dynamic_cast<IntSym*>(s)->isConst){
                addErrorFmt("Cannot assign to const '%s'", id->id);
            }
            lhs = INT_TYPE; 
            break;
        case SymKind::Float:     
            if(dynamic_cast<FloatSym*>(s)->isConst){
                addErrorFmt("Cannot assign to const '%s'", id->id);
            }
            lhs = FLOAT_TYPE;  
            break;
        case SymKind::Bool:      
            if(dynamic_cast<BoolSym*>(s)->isConst){
                addErrorFmt("Cannot assign to const '%s'", id->id);
            }
            lhs = BOOL_TYPE; 
            break;
        case SymKind::Timeseries:
            addErrorFmt("Timeseries '%s' cannot be assigned after declaration, It is immutable", id->id);
            inferred[&node] = TIMESERIES_TYPE;
            return;
        case SymKind::Regime:
            addErrorFmt("Regime '%s' cannot be assigned after declaration, It is immutable", id->id);
            inferred[&node] = RGM_TYPE;
            return;
        case SymKind::Array:
            if(dynamic_cast<BoolSym*>(s)->isConst){
                addErrorFmt("Array '%s' cannot be assigned after declaration, It is immutable", id->id);
            }
            inferred[&node] = INT_TYPE;
            return;
        default:
            lhs = INT_TYPE; 
            break;
    }

    DataTypes rhs = INT_TYPE;
    if(node.value && inferred.count(node.value))
        rhs = inferred[node.value];

    if(lhs == BOOL_TYPE && rhs == INT_TYPE) {} // implicit conversion
    else if(lhs != rhs)
    {
        std::ostringstream ss;
        ss << "Type mismatch in assignment (lhs " << typeToString(lhs)
           << ", rhs " << typeToString(rhs) << ")";
        addError(ss.str());
    }

    inferred[&node] = lhs;
    return;
}

void SemanticVisitor::visit(CallNode &node)
{
    IdentifierNode *id = dynamic_cast<IdentifierNode*>(node.callee);
    if(!id)
    {
        addError("Call of non-identifier callee not supported in semantic pass");
        inferred[&node] = INT_TYPE; // fallback
        return;
    }

    Symbol *s = lookup(id->id);
    if(!s)
    {
        addErrorFmt("Call to undefined function '%s'", id->id.c_str());
        inferred[&node] = INT_TYPE;
        return;
    }

    if(s->kind != SymKind::Function)
    {
        addErrorFmt("Symbol '%s' is not callable", id->id.c_str());
        inferred[&node] = INT_TYPE;
        return;
    }

    FunctionSym *fSym = dynamic_cast<FunctionSym*>(s);
    if(!fSym)
    {
        addErrorFmt("Internal error: Function symbol cast failed for '%s'", id->id.c_str());
        inferred[&node] = INT_TYPE;
        return;
    }

    for(auto &a : node.arguments)
        if(a) a->visitAcceptor(*this);

    // Check argument count
    if(node.arguments.size() != fSym->parameters.size())
    {
        std::ostringstream argStream;
        argStream << fSym->parameters.size() << " arguments, got " << node.arguments.size();
        addErrorFmt("Function '" + id->id + "' expects " + argStream.str(), "");
    }

    // Check argument types
    size_t n = std::min(node.arguments.size(), fSym->parameters.size());
    for(size_t i=0; i<n; ++i)
    {
        ExprNode *argExpr = node.arguments[i];
        Symbol *paramSym = fSym->parameters[i].get();

        if(!argExpr || !paramSym) continue;

        DataTypes argType = inferred.count(argExpr) ? inferred[argExpr] : INT_TYPE;
        DataTypes paramType = SymKindToDataType(paramSym->kind); // helper function

        // Allow int to float promotion
        if(argType == INT_TYPE && paramType == FLOAT_TYPE) continue;

        if(argType != paramType)
        {
            std::ostringstream argStream;
            argStream << (i+1) << " has type " << typeToString(argType) << ", expected " << typeToString(paramType);
            addErrorFmt(("Argument %s of function '" + id->id + "'").c_str(), argStream.str());
        }
    }

    if(fSym->returnType) inferred[&node] = SymKindToDataType(fSym->returnType->kind);
    else inferred[&node] = VOID_TYPE;

    return;
}

void SemanticVisitor::visit(IfNode &node)
{   
    if(insideRegime || insideIndicator){
        addError("If statements are not allowed inside regime or indicator sections");
    }
    if(node.condition) node.condition->visitAcceptor(*this);
    if(node.condition && inferred.count(node.condition) && (inferred[node.condition] != BOOL_TYPE)) addError("If condition is not boolean");
    if(node.thenBranch) node.thenBranch->visitAcceptor(*this);
    if(node.elseBranch) node.elseBranch->visitAcceptor(*this);

    return;
}

void SemanticVisitor::visit(WhileNode &node)
{   
    if(insideRegime || insideIndicator){
        addError("While loops are not allowed inside regime or indicator sections");
    }
    if(node.condition) node.condition->visitAcceptor(*this);
    if(node.condition && inferred.count(node.condition) && inferred[node.condition] != BOOL_TYPE) addError("While condition is not boolean");
    if(node.body) node.body->visitAcceptor(*this);

    return;
}

void SemanticVisitor::visit(ForNode &node)
{
    if(insideRegime || insideIndicator){
        addError("For loops are not allowed inside regime or indicator sections");
    }
    if(node.init) node.init->visitAcceptor(*this);
    if(node.condition) node.condition->visitAcceptor(*this);
    if(node.condition && inferred.count(node.condition) && inferred[node.condition] != BOOL_TYPE) addError("For loop condition is not boolean");
    if(node.increment) node.increment->visitAcceptor(*this);
    if(node.body) node.body->visitAcceptor(*this);

    return;
}

void SemanticVisitor::visit(ReturnNode &node)
{   
    if(insideRegime || insideIndicator){
        addError("Return is not allowed inside regime or indicator sections");
        return;
    }
    if(node.expr)
    {
        node.expr->visitAcceptor(*this);
        DataTypes exprType = inferred[node.expr];

        if(exprType != currentFunctionReturnType)
        {
            if(!(exprType == INT_TYPE && currentFunctionReturnType == FLOAT_TYPE))
                addError("Return type mismatch in function");
        }
    }
    else
    {
        if(currentFunctionReturnType != VOID_TYPE)
            addError("Return type mismatch: expected non-void");
    }
}

void SemanticVisitor::visit(StrategyNode &node)
{
    Symbol *stratSym = lookup(node.id);
    insideStrategy = true;
    symtab.enterScope();

    if (node.declarations)
    {
        node.declarations->visitAcceptor(*this);

        if (node.declarations->positionSize <= 0)
        {
            addError("Strategy position_shares (p_size) must be greater than 0");
        }
    }

    if (node.indicators)
    {
        node.indicators->visitAcceptor(*this);
    }

    if (node.regimes)
    {
        node.regimes->visitAcceptor(*this);
    }

    if (node.signals)
    {
        node.signals->visitAcceptor(*this);
    }

    symtab.exitScope();
    insideStrategy = false;
}

void SemanticVisitor::visit(StratDeclNode &node)
{
    return;
}

void SemanticVisitor::visit(IndicatorNode &node)
{
    insideIndicator = true;

    if (node.body)
    {
        for (auto d : node.body->declarations)
            if (d)
                d->visitAcceptor(*this);

        for (auto s : node.body->statements)
            if (s)
                s->visitAcceptor(*this);
    }

    insideIndicator = false;
}

void SemanticVisitor::visit(RegimeNode &node)
{   
    insideRegime = true;

    if (node.body)
    {
        for (auto d : node.body->declarations)
            if (d)
                d->visitAcceptor(*this);

        for (auto s : node.body->statements)
            if (s)
                s->visitAcceptor(*this);
    }

    insideRegime = false;
}

void SemanticVisitor::visit(SignalFuncNode &node)
{
    insideSignalFunc = true;

    if (node.body)
    {
        for (auto s : node.body->declarations)
            if (s)
                s->visitAcceptor(*this);

        for (auto s : node.body->statements)
            if (s)
                s->visitAcceptor(*this);

        // The last statement must be an expression
        if (!node.body->statements.empty())
        {
            auto lastStmt = node.body->statements.back();
            auto exprStmt = dynamic_cast<ExprStmtNode*>(lastStmt);
            if (!exprStmt)
            {
                addError("Signal function must end in a boolean expression statement");
            }
            else if (exprStmt->expr)
            {
                ExprNode* expr = exprStmt->expr;
                DataTypes t = inferred[expr];

                if (t != BOOL_TYPE && t!= RGM_TYPE)
                {
                    addError("Signal function must evaluate to bool");
                }
            }
        }
        else
        {
            addError("Signal function is empty");
        }
    }

    insideSignalFunc = false;
}


void SemanticVisitor::visit(SignalFuncListNode &node)
{
    for (auto sig : node.signals)
    {
        if (sig)
            sig->visitAcceptor(*this);
    }
}

void SemanticVisitor::visit(TimeseriesNode &node)
{
    for (auto &a : node.args)
    {
        if (a)
            a->visitAcceptor(*this);
    }

    bool valid = true;
    inferred[&node] = TIMESERIES_TYPE;
}

void SemanticVisitor::visit(PortfolioStateNode &node)
{
    inferred[&node] = FLOAT_TYPE;
    return;
}

void SemanticVisitor::visit(MemberAccessNode &node)
{
    if(node.object) node.object->visitAcceptor(*this);

    if(node.object && inferred.count(node.object) && inferred[node.object] == GROUP_TYPE)
    {
        if(auto id = dynamic_cast<IdentifierNode *>(node.object))
        {
            Symbol *s = lookup(id->id);
            if(s)
            {
                GroupSym *gs = dynamic_cast<GroupSym *>(s);
                if(gs)
                {
                    if(gs->members.find(node.member) == gs->members.end()) addErrorFmt("Unknown member '%s' in group '%s'", node.member);
                    
                    else
                    {
                        Symbol *mem = gs->members[node.member].get();
                        if(mem->kind == SymKind::Int) inferred[&node] = INT_TYPE;
                        else if(mem->kind == SymKind::Float) inferred[&node] = FLOAT_TYPE;
                        else if(mem->kind == SymKind::Bool) inferred[&node] = BOOL_TYPE;
                        else inferred[&node] = GROUP_TYPE;
                        return;
                    }
                }
            }
        }
    }

    // fallback
    inferred[&node] = INT_TYPE;
    return;
}

void SemanticVisitor::visit(ArrayAccessNode &node)
{

    if (node.array)
        node.array->visitAcceptor(*this);
    if (node.index)
        node.index->visitAcceptor(*this);

    if (node.index && inferred.count(node.index) &&
        inferred[node.index] != INT_TYPE)
    {
        addError("Array/Timeseries index is not integer");
    }

    auto id = dynamic_cast<IdentifierNode*>(node.array);
    if (!id)
    {
        addError("Indexing non-identifier expression");
        inferred[&node] = INT_TYPE;
        return;
    }

    Symbol *s = lookup(id->id);
    if (!s)
    {
        addErrorFmt("Undefined identifier '%s' in index access", id->id);
        inferred[&node] = INT_TYPE;
        return;
    }

    int constIndex = 0;
    bool indexIsConst = false;

    if (auto lit = dynamic_cast<LiteralIntNode*>(node.index))
    {
        constIndex = lit->value;
        indexIsConst = true;
    }

    if (s->kind == SymKind::Timeseries)
    {
        TimeseriesSym *ts = dynamic_cast<TimeseriesSym*>(s);
        inferred[&node] = FLOAT_TYPE;

        if (indexIsConst && ts)
        {
            if (ts->capacity <= 0)
            {
                // addErrorFmt("Timeseries '%s' has unspecified capacity — cannot statically verify index", id->id);
            }
            else if (constIndex < 0 || constIndex >= ts->capacity)
            {
                addErrorFmt("Timeseries '%s' index %s out of bounds", id->id);
            }
        }
        return;
    }

    if (s->kind == SymKind::Array)
    {   
        auto arr = dynamic_cast<ArraySym*>(s);
        if (!arr)
        {
            addErrorFmt("Internal error: '%s' is Array kind but cast to ArraySym failed", id->id);
            inferred[&node] = INT_TYPE;
            return;
        }
        int size = 0;

        if (!arr->dimensions.empty())
            size = arr->dimensions[0];
        else
            size = (int)arr->elements.size();

        if (indexIsConst)
        {
            if (size <= 0)
            {
                addErrorFmt("Array '%s' size unknown — cannot check bounds", id->id);
            }
            else if (constIndex < 0 || constIndex >= size)
            {
                addErrorFmt("Array '%s' index %s out of bounds", id->id);
            }
        }

        inferred[&node] = arr->baseType;
        return;
    }

    addErrorFmt("'%s' does not support indexing", id->id);
    inferred[&node] = INT_TYPE;
    return;
}

void SemanticVisitor::visit(ConditionalExprNode &node)
{
    if(node.condition) node.condition->visitAcceptor(*this);
    if(node.condition && inferred.count(node.condition) && inferred[node.condition] != BOOL_TYPE) addError("Conditional expression condition not boolean");
    if(node.thenExpr) node.thenExpr->visitAcceptor(*this);
    if(node.elseExpr) node.elseExpr->visitAcceptor(*this);

    DataTypes tThen = INT_TYPE, tElse = INT_TYPE;
    if(node.thenExpr && inferred.count(node.thenExpr)) tThen = inferred[node.thenExpr];
    if(node.elseExpr && inferred.count(node.elseExpr)) tElse = inferred[node.elseExpr];

    if(tThen != tElse)
    {
        if(isNumeric(tThen) && isNumeric(tElse)) inferred[&node] = FLOAT_TYPE;
        
        else
        {
            addError("Branches of conditional expression have incompatible types");
            inferred[&node] = tThen;
        }
    }

    else inferred[&node] = tThen;

    return;
}

void SemanticVisitor::visit(CastExprNode &node)
{
    if(node.expr) node.expr->visitAcceptor(*this);

    // Determine the type of the expression
    DataTypes exprType = INT_TYPE;
    if(node.expr && inferred.count(node.expr)) exprType = inferred[node.expr];

    // Determine target type
    DataTypes targetType = INT_TYPE;
    if(node.targetType) targetType = node.targetType->type;

    if(!isCastable(exprType, targetType))
    {
        std::ostringstream ss;
        ss << "Invalid cast from '" << typeToString(exprType) << "' to '" << typeToString(targetType) << "'";
        addError(ss.str());    
    }

    // The resulting type of the CastExprNode is the target type
    inferred[&node] = targetType;
    return;
}

void SemanticVisitor::visit(CommaExprNode &node)
{
    DataTypes lastType = INT_TYPE;

    for(auto expr : node.expressions)
    {
        if(!expr) continue;
        expr->visitAcceptor(*this);
        if(inferred.count(expr)) lastType = inferred[expr];
    }

    inferred[&node] = lastType;
    return;
}

void SemanticVisitor::printErrors() const 
{
    if(errors.empty()) 
    {
        cout << "No semantic errors found.\n";
        return;
    }

    cout << "Semantic Errors (" << errors.size() << "):\n";
    for(const auto &e : errors) cout << "- " << e << "\n";
}

void SemanticVisitor::visit(ExprStmtNode &node)
{
    if (node.expr)
        node.expr->visitAcceptor(*this);
}
