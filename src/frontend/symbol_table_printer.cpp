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

// Forward declaration for recursive printing
static void printSymbol(const Symbol *s, std::ostream &out, int indent = 0);

// Print details for function parameters
static void printFunctionParams(const FunctionSym *fn, std::ostream &out, int indent)
{
    if (fn->parameters.empty())
    {
        out << indentStr(indent + 1) << "Parameters: (none)\n";
        return;
    }

    out << indentStr(indent + 1) << "Parameters:\n";
    for (size_t i = 0; i < fn->parameters.size(); ++i)
    {
        const Symbol *param = fn->parameters[i].get();
        if (!param)
            continue;

        out << indentStr(indent + 2) << "[param " << i << "] Name: " << param->name
            << ", Kind: " << symKindName(param->kind)
            << " (Loc: " << param->loc.line << ":" << param->loc.column << ")";

        // Add type-specific values for simple types if they are constants
        if (auto is = dynamic_cast<const IntSym *>(param))
        {
            if (is->isConst)
                out << ", Value: " << is->value;
        }
        else if (auto fs = dynamic_cast<const FloatSym *>(param))
        {
            if (fs->isConst)
                out << ", Value: " << std::fixed << std::setprecision(2) << fs->value;
        }
        else if (auto bs = dynamic_cast<const BoolSym *>(param))
        {
            if (bs->isConst)
                out << ", Value: " << (bs->value ? "true" : "false");
        }
        out << "\n";
    }
}

// Print a single symbol (and a little type-specific info)
static void printSymbol(const Symbol *s, std::ostream &out, int indent)
{
    if (!s)
        return;

    // --- Base Symbol Info ---
    out << indentStr(indent) << "Name: " << s->name << ", Kind: " << symKindName(s->kind)
        << " (Loc: " << s->loc.line << ":" << s->loc.column << ")";

    // --- Type-specific extras (Same line) ---
    if (auto is = dynamic_cast<const IntSym *>(s))
    {
        out << " | Value: " << is->value << (is->isConst ? " [CONST]" : " [VAR]");
    }
    else if (auto fs = dynamic_cast<const FloatSym *>(s))
    {
        out << " | Value: " << std::fixed << std::setprecision(2) << fs->value << (fs->isConst ? " [CONST]" : " [VAR]");
    }
    else if (auto bs = dynamic_cast<const BoolSym *>(s))
    {
        out << " | Value: " << (bs->value ? "true" : "false") << (bs->isConst ? " [CONST]" : " [VAR]");
    }
    else if (auto ts = dynamic_cast<const TimeseriesSym *>(s))
    {
        out << " | Capacity: " << ts->capacity << ", Count: " << ts->count;
    }
    else if (auto strat = dynamic_cast<const StrategySym *>(s))
    {
        // timeframe is an int[3] array: {day, hour, minute}
        out << " | StratName: \"" << strat->name << "\""
            << ", Timeframe: {" << strat->timeframe[0] << "d, "
            << strat->timeframe[1] << "h, " << strat->timeframe[2] << "m}";
    }
    else if (auto rg = dynamic_cast<const RegimeSym *>(s))
    {
        out << " | Current: " << (rg->current ? "true" : "false");
    }
    else if (auto grp = dynamic_cast<const GroupSym *>(s))
    {
        out << " | Members: " << grp->members.size();
    }
    else if (auto arr = dynamic_cast<const ArraySym *>(s))
    {
        out << " | Elements: " << arr->size();
    }
    else if (auto fn = dynamic_cast<const FunctionSym *>(s))
    {
        out << " | Params: " << fn->parameters.size();
        if (fn->returnType)
        {
            out << ", Returns: " << symKindName(fn->returnType->kind)
                << " (Loc: " << fn->returnType->loc.line
                << ":" << fn->returnType->loc.column << ")";

            // If it's a simple type, print its value attributes if const
            if (auto is = dynamic_cast<const IntSym *>(fn->returnType.get()))
            {
                if (is->isConst)
                    out << ", Value: " << is->value;
            }
            else if (auto fs = dynamic_cast<const FloatSym *>(fn->returnType.get()))
            {
                if (fs->isConst)
                    out << ", Value: " << std::fixed << std::setprecision(2) << fs->value;
            }
            else if (auto bs = dynamic_cast<const BoolSym *>(fn->returnType.get()))
            {
                if (bs->isConst)
                    out << ", Value: " << (bs->value ? "true" : "false");
            }
        }
    }

    out << "\n";


    if (auto fn = dynamic_cast<const FunctionSym *>(s))
    {
        printFunctionParams(fn, out, indent);
    }

    if (auto grp = dynamic_cast<const GroupSym *>(s))
    {
        out << indentStr(indent + 1) << "--- Group Members for " << grp->name << " ---\n";
        for (const auto &m : grp->members)
        {
            printSymbol(m.second.get(), out, indent + 2);
        }
        out << indentStr(indent + 1) << "--------------------------------\n";
    }

    if (auto arr = dynamic_cast<const ArraySym *>(s))
    {
        out << indentStr(indent + 1) << "--- Array Elements for " << arr->name << " ---\n";
        for (size_t i = 0; i < arr->elements.size(); ++i)
        {
            const Symbol *el = arr->elements[i].get();
            if (!el)
                continue;

            // Print index tag
            out << indentStr(indent + 2) << "[ Index " << i << " ]\n";

            // Print symbol details for the element, deeply indented
            printSymbol(el, out, indent + 3);
        }
        out << indentStr(indent + 1) << "---------------------------------\n";
    }
}

// Recursively print scope and its children
static void printScopeRecursive(const Scope *scope, std::ostream &out, int indent = 0, int depth = 0)
{
    if (!scope)
        return;

    out << "\n"
        << indentStr(indent) << "==========================================\n";
    out << indentStr(indent) << "SCOPE LEVEL " << depth << " (" << (depth == 0 ? "GLOBAL" : "LOCAL") << ")\n";
    out << indentStr(indent) << "==========================================\n";

    // Print symbols in this scope
    if (scope->table.empty())
    {
        out << indentStr(indent + 1) << "(No symbols defined in this scope)\n";
    }
    else
    {
        out << indentStr(indent + 1) << "--- DEFINITIONS ---\n";
        for (const auto &entry : scope->table)
        {
            const Symbol *s = entry.second.get();
            printSymbol(s, out, indent + 2);
        }
        out << indentStr(indent + 1) << "-------------------\n";
    }

    // Recurse into children
    if (!scope->children.empty())
    {
        out << indentStr(indent + 1) << "--- CHILD SCOPES ---\n";
        for (const auto &child : scope->children)
        {
            printScopeRecursive(child.get(), out, indent + 1, depth + 1);
        }
    }
}

void printSymbolTable(const SymbolTable &st, std::ostream &out)
{
    out << "\n\n**************************************************\n";
    out << "COMPILER SYMBOL TABLE DUMP\n";
    out << "**************************************************\n";

    if (!st.global)
    {
        out << " (Empty Symbol Table)\n";
        out << "**************************************************\n";
        return;
    }

    printScopeRecursive(st.global.get(), out, 0, 0);

    out << "\n**************************************************\n";
}
