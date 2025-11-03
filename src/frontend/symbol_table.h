#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

struct Location {
    int line = 0;
    int column = 0;
    Location(int l, int c) : line(l), column(c) {}
};

enum class SymKind {
    Int,
    Float,
    Bool,
    Timeseries,
    Function,
    Strategy,
    Regime,
    Group,
    Array
};

struct Symbol {
    const std::string name;
    const SymKind kind;
    Location loc; 

    Symbol(std::string n, SymKind k, int row, int col)
        : name(std::move(n)), kind(k), loc(row, col) {}
    virtual ~Symbol() = default;

    const Location* location() const { return &loc; }
};

struct IntSym : Symbol {
    int value;
    bool isConst;
    IntSym(std::string n, int v, bool c, int row, int col)
        : Symbol(std::move(n), SymKind::Int, row, col), value(v), isConst(c) {}
};

struct FloatSym : Symbol {
    double value;
    bool isConst;
    FloatSym(std::string n, double v, bool c, int row, int col)
        : Symbol(std::move(n), SymKind::Float, row, col), value(v), isConst(c) {}
};

struct BoolSym : Symbol {
    bool value;
    bool isConst;
    BoolSym(std::string n, bool v, bool c, int row, int col)
        : Symbol(std::move(n), SymKind::Bool, row, col), value(v), isConst(c) {}
};

struct TimeseriesSym : Symbol {
    size_t capacity;
    std::vector<int> buf;
    size_t head = 0;
    size_t count = 0; 

    TimeseriesSym(std::string n, size_t cap, int row, int col)
        : Symbol(std::move(n), SymKind::Timeseries, row, col),
          capacity(cap), buf(cap) {}

    void push(int v) {
        if (capacity == 0) return;
        size_t pos = (head + count) % capacity;
        if (count < capacity) {
            buf[pos] = v;
            ++count;
        } else {
            buf[pos] = v;
            head = (head + 1) % capacity;
        }
    }

    int get(size_t idx) const {
        if (capacity == 0 || idx >= count) throw std::out_of_range("Invalid index");
        size_t offset = count - 1 - idx;
        size_t pos = (head + offset) % capacity;
        return buf[pos];
    }

    int operator[](size_t idx) const { return get(idx); }

    std::vector<int> to_vector_newest_first() const {
        std::vector<int> out;
        out.reserve(count);
        for (size_t i = 0; i < count; ++i)
            out.push_back(get(i));
        return out;
    }
};

struct FunctionSym : Symbol {
    std::vector<std::unique_ptr<Symbol>> parameters;
    std::unique_ptr<Symbol> returnType;
    FunctionSym(std::string n, int row, int col)
        : Symbol(std::move(n), SymKind::Function, row, col) {}
};

struct StrategySym : Symbol {
    std::string  name;
    int timeframe;
    StrategySym(std::string n, std::string  name, int tf, int row, int col)
        : Symbol(std::move(n), SymKind::Strategy, row, col), name(std::move(name)), timeframe(tf) {}
};

struct RegimeSym : Symbol {
    bool current;
    RegimeSym(std::string n, int row, int col)
        : Symbol(std::move(n), SymKind::Regime, row, col), current(false) {}
};

struct ArraySym : Symbol {
    std::vector<std::unique_ptr<Symbol>> elements;

    ArraySym(std::string n, int row, int col)
        : Symbol(std::move(n), SymKind::Array, row, col) {}

    void push_int(const std::string &elemName, int v, bool isConst, int row, int col) {
        elements.push_back(std::make_unique<IntSym>(elemName, v, isConst, row, col));
    }
    void push_float(const std::string &elemName, double v, bool isConst, int row, int col) {
        elements.push_back(std::make_unique<FloatSym>(elemName, v, isConst, row, col));
    }
    void push_bool(const std::string &elemName, bool v, bool isConst, int row, int col) {
        elements.push_back(std::make_unique<BoolSym>(elemName, v, isConst, row, col));
    }
    void push_timeseries(const std::string &elemName, size_t cap, int row, int col) {
        elements.push_back(std::make_unique<TimeseriesSym>(elemName, cap, row, col));
    }
    void push_array(std::unique_ptr<ArraySym> arr) {
        elements.push_back(std::move(arr));
    }
    void push_group(const std::string &elemName, int row, int col) {
        elements.push_back(std::make_unique<GroupSym>(elemName, row, col));
    }

    Symbol* get(size_t idx) const {
        if (idx >= elements.size()) return nullptr;
        return elements[idx].get();
    }

    size_t size() const { return elements.size(); }
};


struct GroupSym : Symbol {
    std::unordered_map<std::string, std::unique_ptr<Symbol>> members;
    GroupSym(std::string n, int row, int col)
        : Symbol(std::move(n), SymKind::Group, row, col) {}
};

struct Scope {
    Scope* parent = nullptr;
    std::vector<std::unique_ptr<Scope>> children;
    std::unordered_map<std::string, std::unique_ptr<Symbol>> table;

    Scope() = default;
    ~Scope() = default;

    bool define(std::unique_ptr<Symbol> sym) {
        if (!sym) return false;
        const auto &name = sym->name;
        if (table.find(name) != table.end()) return false;
        table.emplace(name, std::move(sym));
        return true;
    }

    Symbol* lookup(const std::string &name) {
        auto it = table.find(name);
        if (it != table.end()) return it->second.get();
        return parent ? parent->lookup(name) : nullptr;
    }

    const Symbol* lookup(const std::string &name) const {
        auto it = table.find(name);
        if (it != table.end()) return it->second.get();
        return parent ? parent->lookup(name) : nullptr;
    }
};

struct SymbolTable {
    std::unique_ptr<Scope> global;
    Scope* currentScope = nullptr;

    SymbolTable() {
        global = std::make_unique<Scope>();
        currentScope = global.get();
    }

    void enterScope() {
        auto newScope = std::make_unique<Scope>();
        newScope->parent = currentScope;
        currentScope->children.push_back(std::move(newScope));
        currentScope = currentScope->children.back().get();
    }

    void exitScope() {
        if (currentScope && currentScope->parent)
            currentScope = currentScope->parent;
    }
};
