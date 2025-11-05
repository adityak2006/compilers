#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include "ast.h"

struct Location
{
    int line = 0;
    int column = 0;
    Location(int l, int c) : line(l), column(c) {}
};

enum class SymKind
{
    Int,
    Float,
    Bool,
    Timeseries,
    Function,
    Strategy,
    Regime,
    Group,
    Array,
    Void
};

struct Symbol
{
    const std::string name;
    const SymKind kind;
    Location loc;

    Symbol(std::string n, SymKind k, int row, int col)
        : name(std::move(n)), kind(k), loc(row, col) {}
    virtual ~Symbol() = default;

    const Location *location() const { return &loc; }
};

struct IntSym : Symbol
{
    int value;
    bool isConst;
    IntSym(std::string n, int v, bool c, int row, int col)
        : Symbol(std::move(n), SymKind::Int, row, col), value(v), isConst(c) {}
};

struct FloatSym : Symbol
{
    double value;
    bool isConst;
    FloatSym(std::string n, double v, bool c, int row, int col)
        : Symbol(std::move(n), SymKind::Float, row, col), value(v), isConst(c) {}
};

struct BoolSym : Symbol
{
    bool value;
    bool isConst;
    BoolSym(std::string n, bool v, bool c, int row, int col)
        : Symbol(std::move(n), SymKind::Bool, row, col), value(v), isConst(c) {}
};

struct TimeseriesSym : Symbol
{
    size_t capacity;
    std::vector<int> buf;
    size_t head = 0;
    size_t count = 0;

    TimeseriesSym(std::string n, size_t cap, int row, int col)
        : Symbol(std::move(n), SymKind::Timeseries, row, col),
          capacity(cap), buf(cap) {}

    void push(int v)
    {
        if (capacity == 0)
            return;
        size_t pos = (head + count) % capacity;
        if (count < capacity)
        {
            buf[pos] = v;
            ++count;
        }
        else
        {
            buf[pos] = v;
            head = (head + 1) % capacity;
        }
    }

    int get(size_t idx) const
    {
        if (capacity == 0 || idx >= count)
            throw std::out_of_range("Invalid index");
        size_t offset = count - 1 - idx;
        size_t pos = (head + offset) % capacity;
        return buf[pos];
    }

    int operator[](size_t idx) const { return get(idx); }

    std::vector<int> to_vector_newest_first() const
    {
        std::vector<int> out;
        out.reserve(count);
        for (size_t i = 0; i < count; ++i)
            out.push_back(get(i));
        return out;
    }
};

struct FunctionSym : Symbol
{
    std::vector<std::unique_ptr<Symbol>> parameters;
    std::unique_ptr<Symbol> returnType;
    FunctionSym(std::string n, int row, int col)
        : Symbol(std::move(n), SymKind::Function, row, col) {}
};

struct StrategySym : Symbol
{
    std::string name;
    int timeframe[3];
    StrategySym(std::string n, std::string name, int tf[3], int row, int col)
        : Symbol(std::move(n), SymKind::Strategy, row, col), name(std::move(name))
    {
        std::copy(tf, tf + 3, timeframe);
    }
};

struct RegimeSym : Symbol
{
    bool current;
    RegimeSym(std::string n, int row, int col)
        : Symbol(std::move(n), SymKind::Regime, row, col), current(false) {}
};


struct GroupSym : Symbol
{
    std::unordered_map<std::string, std::unique_ptr<Symbol>> members;
    std::string groupTypeName;
    GroupSym(std::string n, int row, int col)
        : Symbol(std::move(n), SymKind::Group, row, col) {}
};

struct ArraySym : Symbol
{
    std::vector<std::unique_ptr<Symbol>> elements;
    std::vector<int> dimensions;
    DataTypes baseType = INT_TYPE;
    bool isConstArray = false;
    int def_row = 0, def_col = 0;

    // new constructor: provide dims and base type, it will build elements
    ArraySym(std::string n,
             const std::vector<int> &dims,
             DataTypes baseT,
             bool isConst,
             int row,
             int col)
        : Symbol(std::move(n), SymKind::Array, row, col),
          dimensions(dims),
          baseType(baseT),
          isConstArray(isConst),
          def_row(row),
          def_col(col)
    {
        if (!dimensions.empty())
        {
            build_recursive(0, "");
        }
    }

    void push_int(const std::string &elemName, int v, bool isConst, int row, int col)
    {
        elements.push_back(std::make_unique<IntSym>(elemName, v, isConst, row, col));
    }
    void push_float(const std::string &elemName, double v, bool isConst, int row, int col)
    {
        elements.push_back(std::make_unique<FloatSym>(elemName, v, isConst, row, col));
    }
    void push_bool(const std::string &elemName, bool v, bool isConst, int row, int col)
    {
        elements.push_back(std::make_unique<BoolSym>(elemName, v, isConst, row, col));
    }
    void push_array(std::unique_ptr<ArraySym> arr)
    {
        elements.push_back(std::move(arr));
    }
    void push_group(const std::string &elemName, int row, int col)
    {
        elements.push_back(std::make_unique<GroupSym>(elemName, row, col));
    }

    Symbol *get(size_t idx) const
    {
        if (idx >= elements.size())
            return nullptr;
        return elements[idx].get();
    }

    size_t size() const { return elements.size(); }

    // recursively build the nested array structure
    // dimIdx: current dimension (0 .. dimensions.size()-1)
    // prefix: name prefix (used to make element names like "arr[0][1]")
    void build_recursive(size_t dimIdx, const std::string &prefix)
    {
        if (dimIdx >= dimensions.size())
            return;

        int dim = dimensions[dimIdx];
        for (int i = 0; i < dim; ++i)
        {
            // build element name like "[0]" or "[0][1]" (you can change to parentName+..)
            std::string elemName = prefix.empty() ? ("[" + std::to_string(i) + "]")
                                                  : (prefix + "[" + std::to_string(i) + "]");

            if (dimIdx + 1 == dimensions.size())
            {
                // leaf element -> create a scalar symbol according to baseType
                switch (baseType)
                {
                case INT_TYPE:
                    push_int(elemName, 0, isConstArray, def_row, def_col);
                    break;
                case FLOAT_TYPE:
                    push_float(elemName, 0.0, isConstArray, def_row, def_col);
                    break;
                case BOOL_TYPE:
                    push_bool(elemName, false, isConstArray, def_row, def_col);
                    break;
                case GROUP_TYPE:
                default:
                    // for user-defined types / groups: create a GroupSym placeholder
                    push_group(elemName, def_row, def_col);
                    break;
                }
            }
            else
            {
                // nested array: create a child ArraySym for remaining dimensions
                std::vector<int> subdims(dimensions.begin() + dimIdx + 1, dimensions.end());
                // child name kept as elemName so nested elements can see the index in name
                auto child = std::make_unique<ArraySym>(elemName, subdims, baseType, isConstArray, def_row, def_col);
                push_array(std::move(child));
            }
        } // for indices
    }
};

struct Scope
{
    Scope *parent = nullptr;
    std::vector<std::unique_ptr<Scope>> children;
    std::unordered_map<std::string, std::unique_ptr<Symbol>> table;

    Scope() = default;
    ~Scope() = default;

    bool define(std::unique_ptr<Symbol> sym)
    {
        if (!sym)
            return false;
        const auto &name = sym->name;
        if (table.find(name) != table.end())
            return false;
        table.emplace(name, std::move(sym));
        return true;
    }

    Symbol *lookup(const std::string &name)
    {
        auto it = table.find(name);
        if (it != table.end())
            return it->second.get();
        return parent ? parent->lookup(name) : nullptr;
    }

    const Symbol *lookup(const std::string &name) const
    {
        auto it = table.find(name);
        if (it != table.end())
            return it->second.get();
        return parent ? parent->lookup(name) : nullptr;
    }
};

struct SymbolTable
{
    std::unique_ptr<Scope> global;
    Scope *currentScope = nullptr;

    SymbolTable()
    {
        global = std::make_unique<Scope>();
        currentScope = global.get();
    }

    void enterScope()
    {
        auto newScope = std::make_unique<Scope>();
        newScope->parent = currentScope;
        currentScope->children.push_back(std::move(newScope));
        currentScope = currentScope->children.back().get();
    }

    void exitScope()
    {
        if (currentScope && currentScope->parent)
            currentScope = currentScope->parent;
    }
};
