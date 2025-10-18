#ifndef SYMBOL_TABLE_BUILDER_H
#define SYMBOL_TABLE_BUILDER_H

#include "ast.h"
#include "symbol_table.h"

// This visitor walks the AST and populates the symbol table
class SymbolTableBuilder : public ast::ASTVisitor
{
private:
    symtab::SymbolTable *symTable;
    symtab::StrategySymbol *currentStrategy = nullptr;

public:
    SymbolTableBuilder(symtab::SymbolTable *st) : symTable(st) {}

    // Program root
    void visit(ast::ProgramNode &node) override
    {
        // Process global declarations first
        for (auto decl : node.globalDeclarations)
        {
            decl->accept(*this);
        }

        // Process group definitions
        for (auto group : node.groups)
        {
            group->accept(*this);
        }

        // Process function definitions
        for (auto func : node.functions)
        {
            func->accept(*this);
        }

        // Process strategy definitions
        for (auto strategy : node.strategies)
        {
            strategy->accept(*this);
        }
    }

    // Declarations
    void visit(ast::DeclNode &node) override
    {
        // Get the type
        ast::TypeNode *typeNode = node.type;

        // Process each declarator
        for (auto initDecl : node.decls)
        {
            if (initDecl->declarator)
            {
                ast::Declarator *decl = initDecl->declarator;

                if (decl->funcFlag)
                {
                    // Function declaration (prototype)
                    auto funcSym = new symtab::FunctionSymbol(decl->id);
                    funcSym->returnType = typeNode;
                    funcSym->type = typeNode;
                    funcSym->isDefined = false;

                    // Add parameters
                    for (auto param : decl->params)
                    {
                        auto paramSym = new symtab::ParameterSymbol(param->id);
                        paramSym->type = param->type;
                        funcSym->parameters.push_back(paramSym);
                    }

                    symTable->defineSymbol(funcSym);
                }
                else
                {
                    // Variable declaration
                    auto varSym = new symtab::VariableSymbol(decl->id);
                    varSym->type = typeNode;
                    varSym->isConst = typeNode->constFlag;
                    varSym->isArray = decl->arrayFlag;
                    varSym->isGlobal = (symTable->getCurrentScope()->type == symtab::Scope::GLOBAL_SCOPE);

                    if (initDecl->initializer)
                    {
                        varSym->initializer = initDecl->initializer;
                    }

                    if (!symTable->defineSymbol(varSym))
                    {
                        // Error: redeclaration
                        delete varSym;
                    }
                }
            }
        }
    }

    // Function definition
    void visit(ast::FuncNode &node) override
    {
        // Check if already declared
        symtab::Symbol *existing = symTable->lookupInCurrentScope(node.name);
        symtab::FunctionSymbol *funcSym = nullptr;

        if (existing && existing->kind == symtab::SYM_FUNCTION)
        {
            funcSym = static_cast<symtab::FunctionSymbol *>(existing);
            funcSym->isDefined = true;
        }
        else
        {
            // Create new function symbol
            funcSym = new symtab::FunctionSymbol(node.name);
            funcSym->returnType = node.returnType;
            funcSym->type = node.returnType;
            funcSym->isDefined = true;
            symTable->defineSymbol(funcSym);
        }

        // Enter function scope
        symTable->enterScope(node.name, symtab::Scope::FUNCTION_SCOPE);
        funcSym->bodyScope = symTable->getCurrentScope();

        // Add parameters to function scope
        int paramIndex = 0;
        for (auto param : node.params)
        {
            auto paramSym = new symtab::ParameterSymbol(param->id);
            paramSym->type = param->type;
            paramSym->paramIndex = paramIndex++;

            if (!symTable->defineSymbol(paramSym))
            {
                delete paramSym;
            }

            funcSym->parameters.push_back(paramSym);
        }

        // Process function body
        if (node.body)
        {
            node.body->accept(*this);
        }

        // Exit function scope
        symTable->exitScope();
    }

    // Compound statement
    void visit(ast::CmpdStmtNode &node) override
    {
        // Process declarations in this block
        for (auto decl : node.declarations)
        {
            decl->accept(*this);
        }

        // Process statements
        for (auto stmt : node.statements)
        {
            stmt->accept(*this);
        }
    }

    // Group definition
    void visit(ast::GroupNode &node) override
    {
        auto groupSym = new symtab::GroupSymbol(node.id);
        symTable->defineSymbol(groupSym);

        if (!node.isReference)
        {
            // Enter group scope to process members
            symTable->enterScope(node.id, symtab::Scope::GROUP_SCOPE);
            groupSym->memberScope = symTable->getCurrentScope();

            // Process member declarations
            for (auto memberDecl : node.members)
            {
                memberDecl->accept(*this);

                // Add members to group symbol
                if (memberDecl->type)
                {
                    for (auto groupDecl : memberDecl->declarators)
                    {
                        if (groupDecl->declarator)
                        {
                            std::string memberName = groupDecl->declarator->id;
                            symtab::Symbol *memberSym = symTable->lookupInCurrentScope(memberName);
                            if (memberSym)
                            {
                                groupSym->members[memberName] = memberSym;
                                groupSym->memberOrder.push_back(memberSym);
                            }
                        }
                    }
                }
            }

            symTable->exitScope();
        }
    }

    // Group declaration (member)
    void visit(ast::GroupDeclaration &node) override
    {
        ast::TypeNode *typeNode = node.type;

        for (auto groupDecl : node.declarators)
        {
            if (groupDecl->declarator)
            {
                auto memberSym = new symtab::VariableSymbol(groupDecl->declarator->id);
                memberSym->type = typeNode;
                memberSym->kind = symtab::SYM_GROUP_MEMBER;

                if (!symTable->defineSymbol(memberSym))
                {
                    delete memberSym;
                }
            }
        }
    }

    // Strategy definition
    void visit(ast::StrategyNode &node) override
    {
        auto strategySym = new symtab::StrategySymbol(node.id);

        if (node.declarations)
        {
            strategySym->symbol = node.declarations->symbol;
            strategySym->timeframe = node.declarations->timeframe;
            strategySym->positionSize = node.declarations->positionSize;
        }

        symTable->defineSymbol(strategySym);
        currentStrategy = strategySym;

        // Enter strategy scope
        symTable->enterScope(node.id, symtab::Scope::STRATEGY_SCOPE);
        strategySym->strategyScope = symTable->getCurrentScope();

        // Process indicators
        if (node.indicators)
        {
            node.indicators->accept(*this);
        }

        // Process regimes
        if (node.regimes)
        {
            node.regimes->accept(*this);
        }

        // Process signals
        for (auto signal : node.signals)
        {
            signal->accept(*this);
        }

        // Exit strategy scope
        symTable->exitScope();
        currentStrategy = nullptr;
    }

    // Indicator section
    void visit(ast::IndicatorNode &node) override
    {
        auto indicatorSym = new symtab::IndicatorSymbol("indicators");
        indicatorSym->parentStrategy = currentStrategy;
        symTable->defineSymbol(indicatorSym);

        symTable->enterScope("indicators", symtab::Scope::INDICATOR_SCOPE);
        indicatorSym->indicatorScope = symTable->getCurrentScope();

        if (node.body)
        {
            node.body->accept(*this);
        }

        symTable->exitScope();
    }

    // Regime section
    void visit(ast::RegimeNode &node) override
    {
        auto regimeSym = new symtab::RegimeSymbol("regimes");
        regimeSym->parentStrategy = currentStrategy;
        symTable->defineSymbol(regimeSym);

        symTable->enterScope("regimes", symtab::Scope::REGIME_SCOPE);
        regimeSym->regimeScope = symTable->getCurrentScope();

        if (node.body)
        {
            node.body->accept(*this);
        }

        symTable->exitScope();
    }

    // Signal function
    void visit(ast::SignalFuncNode &node) override
    {
        std::string signalName = signalTypeToString(node.signalType);
        if (!node.regimeId.empty())
        {
            signalName = node.regimeId + "::" + signalName;
        }

        auto signalSym = new symtab::SignalSymbol(signalName, node.signalType);
        signalSym->regimeId = node.regimeId;
        signalSym->parentStrategy = currentStrategy;

        symTable->defineSymbol(signalSym);

        if (currentStrategy)
        {
            currentStrategy->signals.push_back(signalSym);
        }

        symTable->enterScope(signalName, symtab::Scope::SIGNAL_SCOPE);
        signalSym->signalScope = symTable->getCurrentScope();

        if (node.body)
        {
            node.body->accept(*this);
        }

        symTable->exitScope();
    }

    // Identifier - link to symbol
    void visit(ast::IdentifierNode &node) override
    {
        symtab::Symbol *sym = symTable->lookup(node.id);
        if (sym)
        {
            node.symbolEntry = sym;
        }
        else
        {
            symTable->addError("Undefined symbol: " + node.id);
        }
    }

    // Statements that create new scopes
    void visit(ast::WhileNode &node) override
    {
        symTable->enterScope("while", symtab::Scope::BLOCK_SCOPE);

        if (node.condition)
        {
            node.condition->accept(*this);
        }
        if (node.body)
        {
            node.body->accept(*this);
        }

        symTable->exitScope();
    }

    void visit(ast::ForNode &node) override
    {
        symTable->enterScope("for", symtab::Scope::BLOCK_SCOPE);

        if (node.init)
        {
            node.init->accept(*this);
        }
        if (node.condition)
        {
            node.condition->accept(*this);
        }
        if (node.increment)
        {
            node.increment->accept(*this);
        }
        if (node.body)
        {
            node.body->accept(*this);
        }

        symTable->exitScope();
    }

    void visit(ast::IfNode &node) override
    {
        if (node.condition)
        {
            node.condition->accept(*this);
        }

        if (node.thenBranch)
        {
            symTable->enterScope("if-then", symtab::Scope::BLOCK_SCOPE);
            node.thenBranch->accept(*this);
            symTable->exitScope();
        }

        if (node.elseBranch)
        {
            symTable->enterScope("if-else", symtab::Scope::BLOCK_SCOPE);
            node.elseBranch->accept(*this);
            symTable->exitScope();
        }
    }

    // Expression nodes that contain identifiers
    void visit(ast::BinaryExprNode &node) override
    {
        if (node.leftOperand)
        {
            node.leftOperand->accept(*this);
        }
        if (node.rightOperand)
        {
            node.rightOperand->accept(*this);
        }
    }

    void visit(ast::UnaryExprNode &node) override
    {
        if (node.operand)
        {
            node.operand->accept(*this);
        }
    }

    void visit(ast::AssignmentNode &node) override
    {
        if (node.target)
        {
            node.target->accept(*this);
        }
        if (node.value)
        {
            node.value->accept(*this);
        }
    }

    void visit(ast::CallNode &node) override
    {
        if (node.callee)
        {
            node.callee->accept(*this);
        }
        for (auto arg : node.arguments)
        {
            arg->accept(*this);
        }
    }

    void visit(ast::MemberAccessNode &node) override
    {
        if (node.object)
        {
            node.object->accept(*this);
        }
    }

    void visit(ast::ArrayAccessNode &node) override
    {
        if (node.array)
        {
            node.array->accept(*this);
        }
        if (node.index)
        {
            node.index->accept(*this);
        }
    }

private:
    std::string signalTypeToString(ast::SignalType type)
    {
        switch (type)
        {
        case ast::SIGNAL_ENTRY_LONG:
            return "entrylong";
        case ast::SIGNAL_ENTRY_SHORT:
            return "entryshort";
        case ast::SIGNAL_EXIT_LONG:
            return "exitlong";
        case ast::SIGNAL_EXIT_SHORT:
            return "exitshort";
        default:
            return "unknown";
        }
    }
};

#endif // SYMBOL_TABLE_BUILDER_H