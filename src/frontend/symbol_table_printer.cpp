// symbol_table_printer.cpp
#include "symbol_table.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

static const char *symKindName(SymKind k)
{
    switch (k)
    {
    case SymKind::Int:
        return "Int";
    case SymKind::Float:
        return "Float";
    case SymKind::Bool:
        return "Bool";
    case SymKind::Timeseries:
        return "Timeseries";
    case SymKind::Function:
        return "Function";
    case SymKind::Strategy:
        return "Strategy";
    case SymKind::Regime:
        return "Regime";
    case SymKind::Group:
        return "Group";
    case SymKind::Void:
        return "Void";
    case SymKind::Array:
        return "Array";
    default:
        return "Unknown";
    }
}

static std::string indentStr(int indent)
{
    return std::string(indent * 4, ' ');
}

static std::string getSymbolDetails(const Symbol *s)
{
    std::stringstream ss;

    if (auto is = dynamic_cast<const IntSym *>(s))
    {
        ss << "| Value: " << is->value << (is->isConst ? " [CONST]" : " [VAR]");
    }
    else if (auto fs = dynamic_cast<const FloatSym *>(s))
    {
        ss << "| Value: " << std::fixed << std::setprecision(2) << fs->value << (fs->isConst ? " [CONST]" : " [VAR]");
    }
    else if (auto bs = dynamic_cast<const BoolSym *>(s))
    {
        ss << "| Value: " << (bs->value ? "true" : "false") << (bs->isConst ? " [CONST]" : " [VAR]");
    }
    else if (auto ts = dynamic_cast<const TimeseriesSym *>(s))
    {
        ss << "| Capacity: " << ts->capacity << ", Count: " << ts->count;
    }
    else if (auto strat = dynamic_cast<const StrategySym *>(s))
    {
        ss << "| StratName: \"" << strat->name << "\""
           << ", Timeframe: {" << strat->timeframe[0] << "d, "
           << strat->timeframe[1] << "h, " << strat->timeframe[2] << "m}";
    }
    else if (auto rg = dynamic_cast<const RegimeSym *>(s))
    {
        ss << "| Current: " << (rg->current ? "true" : "false");
    }
    else if (auto grp = dynamic_cast<const GroupSym *>(s))
    {
        ss << "| Members: " << grp->members.size();
        if (!grp->groupTypeName.empty())
        {
            ss << " | groupTypeName: \"" << grp->groupTypeName << "\"";
        }
    }
    else if (auto arr = dynamic_cast<const ArraySym *>(s))
    {
        ss << "| Elements: " << arr->size();
        ss << " | Dimensions: ";
        for (size_t i = 0; i < arr->dimensions.size(); ++i)
        {
            ss << "[" << arr->dimensions[i] << "]";
        }
    }
    else if (auto fn = dynamic_cast<const FunctionSym *>(s))
    {
        ss << "| Params: " << fn->parameters.size();
        if (fn->returnType)
        {
            ss << ", Returns: " << symKindName(fn->returnType->kind);
        }
    }

    return ss.str();
}

// Recursively print a symbol and its children
static void printSymbol(const Symbol *s, std::ostream &out, int indent = 0)
{
    if (!s)
        return;

    // Format: p1 (Group) @ 59:15
    out << indentStr(indent) << s->name << " (" << symKindName(s->kind) << ") "
        << "@ " << s->loc.line << ":" << s->loc.column;

    std::string details = getSymbolDetails(s);
    if (!details.empty())
    {
        out << "\n"
            << indentStr(indent + 1) << "└─ " << details;
    }
    out << "\n";


    if (auto fn = dynamic_cast<const FunctionSym *>(s))
    {
        if (!fn->parameters.empty())
        {
            out << indentStr(indent + 1) << "Parameters:\n";
            for (const auto &param : fn->parameters)
            {
                printSymbol(param.get(), out, indent + 2); // RECURSIVE CALL
            }
        }
    }
    else if (auto grp = dynamic_cast<const GroupSym *>(s))
    {
        if (!grp->members.empty())
        {
            out << indentStr(indent + 1) << "Members:\n";
            for (const auto &m : grp->members)
            {
                printSymbol(m.second.get(), out, indent + 2); // RECURSIVE CALL
            }
        }
    }
    else if (auto arr = dynamic_cast<const ArraySym *>(s))
    {
        if (!arr->elements.empty())
        {
            out << indentStr(indent + 1) << "Elements:\n";
            for (const auto &el : arr->elements)
            {
                printSymbol(el.get(), out, indent + 2); // RECURSIVE CALL
            }
        }
    }
}

static void printScopeRecursive(const Scope *scope, std::ostream &out, int indent = 0, int depth = 0)
{
    if (!scope)
        return;

    out << "\n"
        << indentStr(indent) << "---";
    out << " Scope: " << (depth == 0 ? "Global" : "Local") << " (Level " << depth << ")";
    out << " ---\n";

    if (scope->table.empty())
    {
        out << indentStr(indent + 1) << "(empty)\n";
    }
    else
    {
        for (const auto &entry : scope->table)
        {
            printSymbol(entry.second.get(), out, indent + 1);
        }
    }

    if (!scope->children.empty())
    {
        out << indentStr(indent + 1) << "Child Scopes:\n";
        for (const auto &child : scope->children)
        {
            printScopeRecursive(child.get(), out, indent + 1, depth + 1);
        }
    }
}

void printSymbolTable(const SymbolTable &st, std::ostream &out)
{
    out << "\n\n**************************************************\n";
    out << "          COMPILER SYMBOL TABLE DUMP\n";
    out << "**************************************************";

    if (!st.global)
    {
        out << "\n(Empty Symbol Table)\n";
    }
    else
    {
        printScopeRecursive(st.global.get(), out, 0, 0);
    }

    out << "\n**************************************************\n";
}
