#include "semantic.h"
#include <sstream>
#include <iostream>
#include <memory>
#include <typeinfo>

// ================================================================
// Helper: Create a fresh Symbol* for a parameter given name & type
// ================================================================
Symbol* SemanticVisitor::makeSymbolForType(const std::string &name, DataTypes t)
{
    switch(t)
    {
        case INT_TYPE:        return new IntSym(name, 0, false, 0, 0);
        case FLOAT_TYPE:      return new FloatSym(name, 0.0, false, 0, 0);
        case BOOL_TYPE:       return new BoolSym(name, false, false, 0, 0);
        case TIMESERIES_TYPE: return new TimeseriesSym(name, 0, 0, 0);
        default:              return new Symbol(name, SymKind::Int, 0, 0);
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
    return ((a == b) || (isNumeric(a) && isNumeric(b))); // allow int <-> float comparisons     
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
    // (But we make sure to be in global)
    // symtab.global created in constructor, currentScope points to it.
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
    // Same type is always allowed
    if(from == to) return true;

    // Numeric casts: INT <-> FLOAT
    if((from == INT_TYPE || from == FLOAT_TYPE) &&
       (to == INT_TYPE || to == FLOAT_TYPE))
        return true;

    // Boolean casts (only BOOL <-> BOOL)
    if(from == BOOL_TYPE && to == BOOL_TYPE)
        return true;

    // Timeseries and Group types generally cannot be cast
    // You can extend this if needed
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
        case SymKind::Void: return VOID_TYPE;
        default: return INT_TYPE; // fallback
    }
}
// --- Visitors ---------------------------------------------------------------

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

    for(auto initDecl : node.decls)
    {
        if(!initDecl || !initDecl->declarator) continue;
        std::string name = initDecl->declarator->id;

        // Create symbol based on declared type
        std::unique_ptr<Symbol> sym;
        switch (dt)
        {
            case INT_TYPE:
                sym = std::make_unique<IntSym>(name, /*value*/ 0, /*isConst*/ node.type->constFlag, 0, 0);
                break;
            case FLOAT_TYPE:
                sym = std::make_unique<FloatSym>(name, 0.0, node.type->constFlag, 0, 0);
                break;
            case BOOL_TYPE:
                sym = std::make_unique<BoolSym>(name, false, node.type->constFlag, 0, 0);
                break;
            case TIMESERIES_TYPE:
                // default capacity 0; real capacity can be set by initializer if you want
                sym = std::make_unique<TimeseriesSym>(name, /*cap*/ 0, 0, 0);
                break;
            case GROUP_TYPE:
                sym = std::make_unique<GroupSym>(name, 0, 0);
                break;
            case RGM_TYPE:
                sym = std::make_unique<RegimeSym>(name, 0, 0);
                break;
            default:
                // unknown / void: create generic Symbol
                sym = std::make_unique<Symbol>(name, SymKind::Int, 0, 0);
                break;
        }

        if(!define(std::move(sym))) addErrorFmt("Redefinition of symbol '%s'", name);
        

        // If initializer exists, analyze it and check type compatibility
        if (initDecl->initializer && initDecl->initializer->expr)
        {
            initDecl->initializer->expr->visitAcceptor(*this);
            DataTypes rhs = inferred[initDecl->initializer->expr];
            
            if(dt == FLOAT_TYPE && rhs == INT_TYPE) {} // ok: implicit promotion (optional to warn)
            else if (dt != rhs)
            {
                addErrorFmt("Type mismatch in initializer for '%s' (declared %s, initializer %s)", name);
                std::ostringstream s;
                s << " declared " << typeToString(dt) << ", initializer " << typeToString(rhs);
                addError(s.str());
            }
        }
    }
}

void SemanticVisitor::visit(InitDeclarator &node)
{
    // Nothing here; handled in DeclNode
}

void SemanticVisitor::visit(CmpdStmtNode &node)
{
    symtab.enterScope();

    for(auto d : node.declarations)
        if(d) d->visitAcceptor(*this);

    for(auto s : node.statements)
        if(s) s->visitAcceptor(*this);

    symtab.exitScope();
    return;
}

void SemanticVisitor::visit(FuncNode &node)
{
    std::string fname = node.name;

    // Determine return type (fun name(args -> T))
    DataTypes retType = VOID_TYPE;
    if(node.returnType)
        retType = node.returnType->type;

    // Create FunctionSym using its correct constructor
    auto fSym = std::make_unique<FunctionSym>(fname, 0, 0);

    // Store return type symbol
    fSym->returnType = std::unique_ptr<Symbol>(
        makeSymbolForType("__ret", retType)
    );

    // Define function symbol
    if(!define(std::move(fSym)))
    {
        addErrorFmt("Redefinition of function '%s'", fname);
    }

    // Retrieve the stored FunctionSym
    FunctionSym *f = dynamic_cast<FunctionSym*>(lookup(fname));

    // Enter function scope
    symtab.enterScope();
    insideFunction = true;

    // Process parameters
    for(auto p : node.params)
    {
        if(!p) continue;

        std::string pname = p->declarator->id;
        DataTypes ptype = p->type ? p->type->type : INT_TYPE;

        // Add to function symbol parameter list
        f->parameters.push_back(
            std::unique_ptr<Symbol>(makeSymbolForType(pname, ptype))
        );

        // Add to local scope
        std::unique_ptr<Symbol> localSym(makeSymbolForType(pname, ptype));

        if(!define(std::move(localSym)))
        {
            addError("Parameter '" + pname + "' redeclared in function '" + fname + "'");
        }
    }

    // Visit body
    if(node.body)
        node.body->visitAcceptor(*this);

    insideFunction = false;
    symtab.exitScope();

    return;
}

void SemanticVisitor::visit(IdentifierNode &node)
{
    Symbol *s = lookup(node.id);
    if(!s)
    {
        addErrorFmt("Undefined identifier '%s'", node.id);
        return;
    }

    resolved[&node] = s;

    // Map symbol's kind -> DataTypes for expression inference
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
            inferredType = TIMESERIES_TYPE;
            break;
        case SymKind::Group:
            inferredType = GROUP_TYPE;
            break;
        case SymKind::Regime:
            inferredType = RGM_TYPE;
            break;
        case SymKind::Function:
            inferredType = VOID_TYPE;
            break;
        case SymKind::Array:
            inferredType = TIMESERIES_TYPE;
            break; // fallback
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
    if(node.leftOperand) node.leftOperand->visitAcceptor(*this);
    if(node.rightOperand) node.rightOperand->visitAcceptor(*this);

    DataTypes L = INT_TYPE;
    DataTypes R = INT_TYPE;
    if(node.leftOperand && inferred.count(node.leftOperand)) L = inferred[node.leftOperand];
    if(node.rightOperand && inferred.count(node.rightOperand)) R = inferred[node.rightOperand];

    const std::string &op = node.op;

    // Arithmetic
    if(op == "+" || op == "-" || op == "*" || op == "/")
    {
        if(!isNumeric(L) || !isNumeric(R))
        {
            addErrorFmt("Arithmetic operator applied to non-numeric operands ('%s')", op);
            inferred[&node] = INT_TYPE;
            return;
        }

        inferred[&node] = (L == FLOAT_TYPE || R == FLOAT_TYPE) ? FLOAT_TYPE : INT_TYPE;
        return;
    }

    // Comparison
    if(op == "<" || op == ">" || op == "<=" || op == ">=" || op == "==" || op == "!=")
    {
        if(!areComparable(L, R)) addErrorFmt("Comparison between incompatible types ('%s')", op);

        inferred[&node] = BOOL_TYPE;
        return;
    }

    // Logical
    if(op == "&&" || op == "||")
    {
        if(L != BOOL_TYPE || R != BOOL_TYPE) addErrorFmt("Logical operator '%s' requires boolean operands", op);

        inferred[&node] = BOOL_TYPE;
        return;
    }

    // Fallback
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

    DataTypes lhs = INT_TYPE, rhs = INT_TYPE;
    if(auto id = dynamic_cast<IdentifierNode*> (node.target))
    {
        if(resolved.count(id))
        {
            Symbol *s = resolved[id];
            
            // check const for Int/Float/Bool
            if(s->kind == SymKind::Int)
            {
                IntSym *is = dynamic_cast<IntSym *>(s);
                if(is && is->isConst) addErrorFmt("Cannot assign to const '%s'", id->id);
            }

            else if(s->kind == SymKind::Float)
            {
                FloatSym *fs = dynamic_cast<FloatSym *>(s);
                if (fs && fs->isConst) addErrorFmt("Cannot assign to const '%s'", id->id);
            }

            else if (s->kind == SymKind::Bool)
            {
                BoolSym *bs = dynamic_cast<BoolSym *>(s);
                if(bs && bs->isConst) addErrorFmt("Cannot assign to const '%s'", id->id);
            }

            // get lhs type from symbol kind
            if(s->kind == SymKind::Int) lhs = INT_TYPE;
            else if(s->kind == SymKind::Float) lhs = FLOAT_TYPE;
            else if(s->kind == SymKind::Bool) lhs = BOOL_TYPE;
            else if(s->kind == SymKind::Timeseries) lhs = TIMESERIES_TYPE;
        }
    }

    // non-identifier target: try to infer
    else if(node.target && inferred.count(node.target)) lhs = inferred[node.target];

    if(node.value && inferred.count(node.value)) rhs = inferred[node.value];

    if (lhs != rhs)
    {
        addErrorFmt("Type mismatch in assignment (lhs %s, rhs %s)", typeToString(lhs));

        // append rhs info
        std::ostringstream ss;
        ss << " rhs " << typeToString(rhs);
        addError(ss.str());
    }

    // assignment expr yields LHS type
    inferred[&node] = lhs;
    return;
}

void SemanticVisitor::visit(CallNode &node)
{
    // Step 1: Ensure callee is an identifier
    IdentifierNode *id = dynamic_cast<IdentifierNode*>(node.callee);
    if(!id)
    {
        addError("Call of non-identifier callee not supported in semantic pass");
        inferred[&node] = INT_TYPE; // fallback
        return;
    }

    // Step 2: Lookup the function symbol
    Symbol *s = lookup(id->id);
    if(!s)
    {
        addErrorFmt("Call to undefined function '%s'", id->id.c_str());
        inferred[&node] = INT_TYPE;
        return;
    }

    // Step 3: Ensure it’s a function
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

    // Step 4: Visit argument expressions
    for(auto &a : node.arguments)
        if(a) a->visitAcceptor(*this);

    // Step 5: Check argument count
    if(node.arguments.size() != fSym->parameters.size())
    {
        std::ostringstream argStream;
        argStream << fSym->parameters.size() << " arguments, got " << node.arguments.size();
        addErrorFmt("Function '" + id->id + "' expects " + argStream.str(), "");
        
    }

    // Step 6: Check argument types
    size_t n = std::min(node.arguments.size(), fSym->parameters.size());
    for(size_t i=0; i<n; ++i)
    {
        ExprNode *argExpr = node.arguments[i];
        Symbol *paramSym = fSym->parameters[i].get();

        if(!argExpr || !paramSym) continue;

        DataTypes argType = inferred.count(argExpr) ? inferred[argExpr] : INT_TYPE;
        DataTypes paramType = SymKindToDataType(paramSym->kind); // helper function

        // Allow int -> float promotion
        if(argType == INT_TYPE && paramType == FLOAT_TYPE) continue;

        if(argType != paramType)
        {
            std::ostringstream argStream;
            argStream << (i+1) << " has type " << typeToString(argType) << ", expected " << typeToString(paramType);
            addErrorFmt(("Argument %s of function '" + id->id + "'").c_str(), argStream.str());
        }
    }

    // Step 7: Set inferred type of the call node to function return type
    if(fSym->returnType) inferred[&node] = SymKindToDataType(fSym->returnType->kind);
    else inferred[&node] = VOID_TYPE;

    return;
}

void SemanticVisitor::visit(IfNode &node)
{
    if(node.condition) node.condition->visitAcceptor(*this);
    if(node.condition && inferred.count(node.condition) && (inferred[node.condition] != BOOL_TYPE)) addError("If condition is not boolean");
    if(node.thenBranch) node.thenBranch->visitAcceptor(*this);
    if(node.elseBranch) node.elseBranch->visitAcceptor(*this);

    return;
}

void SemanticVisitor::visit(WhileNode &node)
{
    if(node.condition) node.condition->visitAcceptor(*this);
    if(node.condition && inferred.count(node.condition) && inferred[node.condition] != BOOL_TYPE) addError("While condition is not boolean");
    if(node.body) node.body->visitAcceptor(*this);

    return;
}

void SemanticVisitor::visit(ForNode &node)
{
    if(node.init) node.init->visitAcceptor(*this);
    if(node.condition) node.condition->visitAcceptor(*this);
    if(node.condition && inferred.count(node.condition) && inferred[node.condition] != BOOL_TYPE) addError("For loop condition is not boolean");
    if(node.increment) node.increment->visitAcceptor(*this);
    if(node.body) node.body->visitAcceptor(*this);

    return;
}

void SemanticVisitor::visit(ReturnNode &node)
{
    if(node.expr) node.expr->visitAcceptor(*this);
    return;
}

void SemanticVisitor::visit(TimeseriesNode &node)
{
    if(!insideIndicator) addError("Timeseries function used outside an indicator block");
    
    // Visit args
    for(auto &a : node.args)
        if(a) a->visitAcceptor(*this);

    inferred[&node] = TIMESERIES_TYPE;
    return;
}

void SemanticVisitor::visit(PortfolioStateNode &node)
{
    // Portfolio state queries yield numeric values (we assume float)
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
    if(node.array) node.array->visitAcceptor(*this);
    if(node.index) node.index->visitAcceptor(*this);
    if(node.index && inferred.count(node.index) && inferred[node.index] != INT_TYPE) addError("Array index is not integer");

    // If array resolves to ArraySym, infer element type if possible
    if(auto id = dynamic_cast<IdentifierNode*>(node.array))
    {
        Symbol *s = lookup(id->id);
        if(s->kind != SymKind::Array)
        {
            addErrorFmt("'%s' is not an array", id->id);
            inferred[&node] = INT_TYPE;
            return;
        }

        auto arr = dynamic_cast<ArraySym*>(s);
        inferred[&node] = arr->baseType;
        return;
    }

    // fallback
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
    // First, visit the expression being cast
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
