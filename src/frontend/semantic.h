#pragma once

#include "ast.h"
#include "symbol_table.h"
#include <string>
#include <vector>
#include <unordered_map>

class SemanticVisitor : public ASTVisitor {
public:
    SymbolTable symtab;

    // Run analysis on program; returns true if no semantic errors.
    bool analyze(ProgramNode* root);

    // Collected errors
    std::vector<std::string> errors;
    void printErrors() const;
private:
    // Context flags
    bool insideIndicator = false;
    bool insideStrategy = false;
    bool insideFunction = false;

    // Inferred types & resolutions (we don't modify AST)
    std::unordered_map<ExprNode*, DataTypes> inferred;
    std::unordered_map<IdentifierNode*, Symbol*> resolved;

    // Helpers
    void addError(const std::string &msg);
    void addErrorFmt(const std::string &fmt, const std::string &arg);
    std::string typeToString(DataTypes t) const;
    bool isNumeric(DataTypes t) const;
    bool areComparable(DataTypes a, DataTypes b) const;
    DataTypes SymKindToDataType(SymKind k);
    // Scope helpers (wrapper to symbol table)
    Symbol* lookup(const std::string &name);
    bool define(std::unique_ptr<Symbol> sym);
    bool isCastable(DataTypes from, DataTypes to);
    // Visit overrides (only those needed — add more if you want)
    void visit(ProgramNode &node) override;
    void visit(DeclNode &node) override;
    void visit(InitDeclarator &node) override;
    void visit(CmpdStmtNode &node) override;
    void visit(FuncNode &node) override;
    void visit(IdentifierNode &node) override;
    void visit(LiteralIntNode &node) override;
    void visit(LiteralFloatNode &node) override;
    void visit(LiteralBoolNode &node) override;
    void visit(BinaryExprNode &node) override;
    void visit(UnaryExprNode &node) override;
    void visit(AssignmentNode &node) override;
    void visit(CallNode &node) override;
    void visit(IfNode &node) override;
    void visit(WhileNode &node) override;
    void visit(ForNode &node) override;
    void visit(ReturnNode &node) override;
    void visit(TimeseriesNode &node) override;
    void visit(PortfolioStateNode &node) override;
    void visit(MemberAccessNode &node) override;
    void visit(ArrayAccessNode &node) override;
    void visit(ConditionalExprNode &node) override;
    void visit(CastExprNode &node) override;
    void visit(CommaExprNode &node) override;
};