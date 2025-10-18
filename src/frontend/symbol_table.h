#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "ast.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace symtab
{

    using String = std::string;
    template <typename T>
    using Vec = std::vector<T>;
    template <typename K, typename V>
    using Map = std::unordered_map<K, V>;

    // Forward declarations
    class SymbolTable;
    class Scope;

    // Symbol kinds in your language
    enum SymbolKind
    {
        SYM_VARIABLE,
        SYM_FUNCTION,
        SYM_PARAMETER,
        SYM_TYPE,
        SYM_STRATEGY,
        SYM_REGIME,
        SYM_INDICATOR,
        SYM_SIGNAL,
        SYM_GROUP,
        SYM_GROUP_MEMBER
    };

    // Base class for all symbol entries
    class Symbol
    {
    public:
        String name;
        SymbolKind kind;
        ast::TypeNode *type = nullptr;    // Data type
        Scope *declScope = nullptr;       // Where it was declared
        ast::ASTNode *declNode = nullptr; // AST node where declared
        int line = 0;                     // Line number of declaration
        int column = 0;

        Symbol(const String &n, SymbolKind k) : name(n), kind(k) {}
        virtual ~Symbol() = default;
    };

    // Variable symbol
    class VariableSymbol : public Symbol
    {
    public:
        bool isConst = false;
        bool isArray = false;
        int arraySize = 0;
        bool isGlobal = false;
        ast::Initializer *initializer = nullptr;

        VariableSymbol(const String &n) : Symbol(n, SYM_VARIABLE) {}
    };

    // Function symbol
    class FunctionSymbol : public Symbol
    {
    public:
        Vec<Symbol *> parameters;
        ast::TypeNode *returnType = nullptr;
        Scope *bodyScope = nullptr; // Function's local scope
        bool isDefined = false;     // true if has body, false if just declaration

        FunctionSymbol(const String &n) : Symbol(n, SYM_FUNCTION) {}
    };

    // Parameter symbol
    class ParameterSymbol : public Symbol
    {
    public:
        int paramIndex = 0; // Position in parameter list

        ParameterSymbol(const String &n) : Symbol(n, SYM_PARAMETER) {}
    };

    // Group/Struct type symbol
    class GroupSymbol : public Symbol
    {
    public:
        Map<String, Symbol *> members; // Member name -> Symbol
        Vec<Symbol *> memberOrder;     // Members in declaration order
        Scope *memberScope = nullptr;

        GroupSymbol(const String &n) : Symbol(n, SYM_GROUP) {}

        Symbol *getMember(const String &memberName)
        {
            auto it = members.find(memberName);
            return (it != members.end()) ? it->second : nullptr;
        }
    };

    // Strategy symbol
    class StrategySymbol : public Symbol
    {
    public:
        String symbol; // Trading symbol
        Vec<int> timeframe;
        int positionSize = 0;
        Scope *strategyScope = nullptr;
        Map<String, Symbol *> regimes;
        Map<String, Symbol *> indicators;
        Vec<Symbol *> signals;

        StrategySymbol(const String &n) : Symbol(n, SYM_STRATEGY) {}
    };

    // Regime symbol
    class RegimeSymbol : public Symbol
    {
    public:
        Scope *regimeScope = nullptr;
        StrategySymbol *parentStrategy = nullptr;

        RegimeSymbol(const String &n) : Symbol(n, SYM_REGIME) {}
    };

    // Indicator symbol
    class IndicatorSymbol : public Symbol
    {
    public:
        Scope *indicatorScope = nullptr;
        StrategySymbol *parentStrategy = nullptr;

        IndicatorSymbol(const String &n) : Symbol(n, SYM_INDICATOR) {}
    };

    // Signal function symbol
    class SignalSymbol : public Symbol
    {
    public:
        ast::SignalType signalType;
        String regimeId; // Optional regime scope
        Scope *signalScope = nullptr;
        StrategySymbol *parentStrategy = nullptr;

        SignalSymbol(const String &n, ast::SignalType type)
            : Symbol(n, SYM_SIGNAL), signalType(type) {}
    };

    // Scope represents a symbol table for a particular scope
    class Scope
    {
    public:
        String scopeName;
        Scope *parent = nullptr;       // Enclosing scope
        Vec<Scope *> children;         // Nested scopes
        Map<String, Symbol *> symbols; // Name -> Symbol
        int scopeLevel = 0;            // Nesting depth (0 = global)

        enum ScopeType
        {
            GLOBAL_SCOPE,
            FUNCTION_SCOPE,
            BLOCK_SCOPE,
            STRATEGY_SCOPE,
            REGIME_SCOPE,
            INDICATOR_SCOPE,
            SIGNAL_SCOPE,
            GROUP_SCOPE
        };
        ScopeType type;

        Scope(const String &name, ScopeType t, Scope *p = nullptr)
            : scopeName(name), type(t), parent(p)
        {
            scopeLevel = (parent) ? parent->scopeLevel + 1 : 0;
        }

        ~Scope()
        {
            // Delete all symbols in this scope
            for (auto &pair : symbols)
            {
                delete pair.second;
            }
            // Delete child scopes
            for (auto child : children)
            {
                delete child;
            }
        }

        // Define a new symbol in this scope
        bool define(Symbol *sym)
        {
            if (symbols.find(sym->name) != symbols.end())
            {
                return false; // Already defined in this scope
            }
            symbols[sym->name] = sym;
            sym->declScope = this;
            return true;
        }

        // Resolve a symbol in this scope only
        Symbol *resolveLocal(const String &name)
        {
            auto it = symbols.find(name);
            return (it != symbols.end()) ? it->second : nullptr;
        }

        // Resolve a symbol in this scope or any enclosing scope
        Symbol *resolve(const String &name)
        {
            Symbol *sym = resolveLocal(name);
            if (sym != nullptr)
                return sym;
            if (parent != nullptr)
                return parent->resolve(name);
            return nullptr;
        }

        // Get all symbols in this scope
        Vec<Symbol *> getAllSymbols()
        {
            Vec<Symbol *> result;
            for (auto &pair : symbols)
            {
                result.push_back(pair.second);
            }
            return result;
        }
    };

    // Main symbol table manager
    class SymbolTable
    {
    private:
        Scope *globalScope = nullptr;
        Scope *currentScope = nullptr;
        Vec<String> errors;

        // Built-in types
        Map<String, ast::DataTypes> builtinTypes;

    public:
        SymbolTable()
        {
            // Initialize global scope
            globalScope = new Scope("global", Scope::GLOBAL_SCOPE);
            currentScope = globalScope;

            // Register built-in types
            builtinTypes["int"] = ast::DT_INT;
            builtinTypes["float"] = ast::DT_FLOAT;
            builtinTypes["bool"] = ast::DT_BOOL;
            builtinTypes["string"] = ast::DT_STRING;
            builtinTypes["void"] = ast::DT_VOID;
            builtinTypes["rgm"] = ast::DT_RGM;
            builtinTypes["timeseries"] = ast::DT_TIMESERIES;
        }

        ~SymbolTable()
        {
            delete globalScope;
        }

        // Scope management
        Scope *getCurrentScope() { return currentScope; }
        Scope *getGlobalScope() { return globalScope; }

        void enterScope(const String &name, Scope::ScopeType type)
        {
            Scope *newScope = new Scope(name, type, currentScope);
            currentScope->children.push_back(newScope);
            currentScope = newScope;
        }

        void exitScope()
        {
            if (currentScope->parent != nullptr)
            {
                currentScope = currentScope->parent;
            }
        }

        // Symbol definition
        bool defineSymbol(Symbol *sym)
        {
            if (!currentScope->define(sym))
            {
                addError("Symbol '" + sym->name + "' already defined in this scope");
                return false;
            }
            return true;
        }

        // Symbol lookup
        Symbol *lookup(const String &name)
        {
            return currentScope->resolve(name);
        }

        Symbol *lookupInCurrentScope(const String &name)
        {
            return currentScope->resolveLocal(name);
        }

        // Type checking helpers
        bool isBuiltinType(const String &typeName)
        {
            return builtinTypes.find(typeName) != builtinTypes.end();
        }

        ast::DataTypes getBuiltinType(const String &typeName)
        {
            auto it = builtinTypes.find(typeName);
            return (it != builtinTypes.end()) ? it->second : ast::DT_VOID;
        }

        GroupSymbol *lookupGroupType(const String &name)
        {
            Symbol *sym = lookup(name);
            if (sym && sym->kind == SYM_GROUP)
            {
                return static_cast<GroupSymbol *>(sym);
            }
            return nullptr;
        }

        // Error handling
        void addError(const String &msg)
        {
            errors.push_back(msg);
        }

        bool hasErrors() const
        {
            return !errors.empty();
        }

        Vec<String> getErrors() const
        {
            return errors;
        }

        void printErrors()
        {
            for (const auto &err : errors)
            {
                fprintf(stderr, "Symbol Table Error: %s\n", err.c_str());
            }
        }

        // Debugging
        void printScope(Scope *scope, int indent = 0)
        {
            if (!scope)
                scope = globalScope;

            String indentStr(indent * 2, ' ');
            printf("%sScope: %s (level %d)\n", indentStr.c_str(),
                   scope->scopeName.c_str(), scope->scopeLevel);

            for (auto &pair : scope->symbols)
            {
                Symbol *sym = pair.second;
                printf("%s  %s: %s\n", indentStr.c_str(),
                       pair.first.c_str(), symbolKindToString(sym->kind).c_str());
            }

            for (auto child : scope->children)
            {
                printScope(child, indent + 1);
            }
        }

        String symbolKindToString(SymbolKind kind)
        {
            switch (kind)
            {
            case SYM_VARIABLE:
                return "Variable";
            case SYM_FUNCTION:
                return "Function";
            case SYM_PARAMETER:
                return "Parameter";
            case SYM_TYPE:
                return "Type";
            case SYM_STRATEGY:
                return "Strategy";
            case SYM_REGIME:
                return "Regime";
            case SYM_INDICATOR:
                return "Indicator";
            case SYM_SIGNAL:
                return "Signal";
            case SYM_GROUP:
                return "Group";
            case SYM_GROUP_MEMBER:
                return "GroupMember";
            default:
                return "Unknown";
            }
        }
    };

} // namespace symtab

#endif // SYMBOL_TABLE_H