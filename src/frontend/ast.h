#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

namespace ast
{

    class DeclNode;
    class StmtNode;
    class ExprNode;
    class ParamNode;
    class Declarator;
    class Initializer;
    class CmpdStmtNode;
    class TypeNode;
    class InitDeclarator;
    class FuncNode;
    class GroupNode;
    class StrategyNode;
    class StratDeclNode;
    class IndicatorNode;
    class RegimeNode;
    class SignalFuncNode;
    class ProgramNode;
    class GroupDeclaration;
    class GroupDeclarator;

    using String = std::string;
    template <typename T>
    using Vec = std::vector<T>;

    enum DataTypes
    {
        DT_INT,
        DT_FLOAT,
        DT_BOOL,
        DT_STRING,
        DT_VOID,
        DT_RGM,
        DT_TIMESERIES,
        DT_GROUP
    };

    enum SignalType
    {
        SIGNAL_ENTRY_LONG,
        SIGNAL_ENTRY_SHORT,
        SIGNAL_EXIT_LONG,
        SIGNAL_EXIT_SHORT
    };

    enum TimeseriesFuncType
    {
        TS_OPEN,
        TS_CLOSE,
        TS_HIGH,
        TS_LOW,
        TS_VOLUME,
        TS_SMA,
        TS_EMA,
        TS_RSI,
        TS_BB,
        TS_ATR,
        TS_SDV,
        TS_MAX,
        TS_MIN,
        TS_SUM,
        TS_MEDIAN,
        TS_AVG,
        TS_ABS,
        TS_CORRELATION,
        TS_SLOPE,
        TS_RSQUARED
    };

    enum PortfolioStateType
    {
        PS_PORTFOLIO_VALUE,
        PS_CASH_AVAILABLE,
        PS_POSITION_SHARES,
        PS_ENTRY_PRICE,
        PS_DAYS_IN_POSITION
    };

    struct ASTVisitor
    {
        virtual ~ASTVisitor() = default;
        
        // Base node
        virtual void visit(ASTNode &node) {}
        
        // Statement nodes
        virtual void visit(StmtNode &node) {}
        virtual void visit(ExprStmtNode &node) {}
        virtual void visit(ReturnNode &node) {}
        virtual void visit(BreakNode &node) {}
        virtual void visit(ContinueNode &node) {}
        virtual void visit(IfNode &node) {}
        virtual void visit(WhileNode &node) {}
        virtual void visit(ForNode &node) {}
        virtual void visit(CmpdStmtAsStmtNode &node) {}
        
        // Expression nodes
        virtual void visit(ExprNode &node) {}
        virtual void visit(LiteralIntNode &node) {}
        virtual void visit(LiteralFloatNode &node) {}
        virtual void visit(LiteralStringNode &node) {}
        virtual void visit(LiteralBoolNode &node) {}
        virtual void visit(IdentifierNode &node) {}
        virtual void visit(BinaryExprNode &node) {}
        virtual void visit(UnaryExprNode &node) {}
        virtual void visit(AssignmentNode &node) {}
        virtual void visit(CallNode &node) {}
        virtual void visit(MemberAccessNode &node) {}
        virtual void visit(ArrayAccessNode &node) {}
        virtual void visit(ConditionalExprNode &node) {}
        virtual void visit(TimeseriesNode &node) {}
        virtual void visit(PortfolioStateNode &node) {}
        virtual void visit(CastExprNode &node) {}
        virtual void visit(CommaExprNode &node) {}
        
        // Declaration nodes
        virtual void visit(DeclNode &node) {}
        virtual void visit(TypeNode &node) {}
        virtual void visit(ParamNode &node) {}
        virtual void visit(Declarator &node) {}
        virtual void visit(Initializer &node) {}
        virtual void visit(InitDeclarator &node) {}
        virtual void visit(CmpdStmtNode &node) {}
        
        // Function and structure nodes
        virtual void visit(FuncNode &node) {}
        virtual void visit(GroupNode &node) {}
        virtual void visit(GroupDeclarator &node) {}
        virtual void visit(GroupDeclaration &node) {}
        
        // Strategy nodes
        virtual void visit(StrategyNode &node) {}
        virtual void visit(StratDeclNode &node) {}
        virtual void visit(IndicatorNode &node) {}
        virtual void visit(RegimeNode &node) {}
        virtual void visit(SignalFuncNode &node) {}
        
        // Program root
        virtual void visit(ProgramNode &node) {}
    };

    class ASTNode
    {
    public:
        ASTNode() = default;
        virtual ~ASTNode() = default;

        ASTNode(const ASTNode &) = delete;
        ASTNode &operator=(const ASTNode &) = delete;

        virtual void accept(ASTVisitor &) {}

    protected:
    };

    class CmpdStmtNode : public ASTNode
    {
    public:
        Vec<DeclNode *> declarations;
        Vec<StmtNode *> statements;

        CmpdStmtNode() = default;
        ~CmpdStmtNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class TypeNode : public ASTNode
    {
    public:
        DataTypes type = DT_INT;
        bool constFlag = false;
        String id;
        bool userDefinedFlag = false;

        TypeNode() = default;
        ~TypeNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ParamNode : public ASTNode
    {
    public:
        TypeNode *type = nullptr;
        String id;

        ParamNode() = default;
        ~ParamNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class Declarator : public ASTNode
    {
    public:
        String id;
        bool arrayFlag = false;
        ExprNode *arraySize = nullptr;
        bool funcFlag = false;
        Vec<ParamNode *> params;

        Declarator() = default;
        ~Declarator() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class Initializer : public ASTNode
    {
    public:
        Vec<Initializer *> initializerList;
        ExprNode *expr = nullptr;

        Initializer() = default;
        ~Initializer() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class InitDeclarator : public ASTNode
    {
    public:
        Declarator *declarator = nullptr;
        Initializer *initializer = nullptr;

        InitDeclarator() = default;
        ~InitDeclarator() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class DeclNode : public ASTNode
    {
    public:
        TypeNode *type = nullptr;
        Vec<InitDeclarator *> decls;

        DeclNode() = default;
        ~DeclNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class StmtNode : public ASTNode
    {
    public:
        StmtNode() = default;
        ~StmtNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ExprStmtNode : public StmtNode
    {
    public:
        ExprNode *expr = nullptr;
        ExprStmtNode() = default;
        ~ExprStmtNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ReturnNode : public StmtNode
    {
    public:
        ExprNode *expr = nullptr;
        ReturnNode() = default;
        ~ReturnNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class BreakNode : public StmtNode
    {
    public:
        BreakNode() = default;
        ~BreakNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ContinueNode : public StmtNode
    {
    public:
        ContinueNode() = default;
        ~ContinueNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class IfNode : public StmtNode
    {
    public:
        ExprNode *condition = nullptr;
        StmtNode *thenBranch = nullptr;
        StmtNode *elseBranch = nullptr;

        IfNode() = default;
        ~IfNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class WhileNode : public StmtNode
    {
    public:
        ExprNode *condition = nullptr;
        StmtNode *body = nullptr;

        WhileNode() = default;
        ~WhileNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ForNode : public StmtNode
    {
    public:
        ExprNode *init = nullptr; // Can be expression_statement
        ExprNode *condition = nullptr;
        ExprNode *increment = nullptr;
        StmtNode *body = nullptr;

        ForNode() = default;
        ~ForNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class CmpdStmtAsStmtNode : public StmtNode
    {
    public:
        CmpdStmtNode *body = nullptr;
        CmpdStmtAsStmtNode() = default;
        ~CmpdStmtAsStmtNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ExprNode : public ASTNode
    {
    public:
        ExprNode() = default;
        ~ExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class LiteralIntNode : public ExprNode
    {
    public:
        int value = 0;
        LiteralIntNode() = default;
        ~LiteralIntNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class LiteralFloatNode : public ExprNode
    {
    public:
        double value = 0.0;
        LiteralFloatNode() = default;
        ~LiteralFloatNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class LiteralStringNode : public ExprNode
    {
    public:
        String value;
        LiteralStringNode() = default;
        ~LiteralStringNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class LiteralBoolNode : public ExprNode
    {
    public:
        bool value = false;
        LiteralBoolNode() = default;
        ~LiteralBoolNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class IdentifierNode : public ExprNode
    {
    public:
        String id;
        void *symbolEntry = nullptr;

        IdentifierNode() = default;
        ~IdentifierNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class BinaryExprNode : public ExprNode
    {
    public:
        String op;
        ExprNode *leftOperand = nullptr;
        ExprNode *rightOperand = nullptr;

        BinaryExprNode() = default;
        ~BinaryExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class UnaryExprNode : public ExprNode
    {
    public:
        String op;
        ExprNode *operand = nullptr;

        UnaryExprNode() = default;
        ~UnaryExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class AssignmentNode : public ExprNode
    {
    public:
        ExprNode *target = nullptr; // Changed from IdentifierNode* to support array access
        ExprNode *value = nullptr;

        AssignmentNode() = default;
        ~AssignmentNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class CallNode : public ExprNode
    {
    public:
        ExprNode *callee = nullptr;
        Vec<ExprNode *> arguments;

        CallNode() = default;
        ~CallNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class MemberAccessNode : public ExprNode
    {
    public:
        ExprNode *object = nullptr;
        String member;

        MemberAccessNode() = default;
        ~MemberAccessNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ArrayAccessNode : public ExprNode
    {
    public:
        ExprNode *array = nullptr;
        ExprNode *index = nullptr;

        ArrayAccessNode() = default;
        ~ArrayAccessNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ConditionalExprNode : public ExprNode
    {
    public:
        ExprNode *condition = nullptr;
        ExprNode *thenExpr = nullptr;
        ExprNode *elseExpr = nullptr;

        ConditionalExprNode() = default;
        ~ConditionalExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class TimeseriesNode : public ExprNode
    {
    public:
        TimeseriesFuncType funcType;
        Vec<ExprNode *> args; // Can be timeseries expressions or identifiers

        TimeseriesNode() = default;
        ~TimeseriesNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class PortfolioStateNode : public ExprNode
    {
    public:
        PortfolioStateType stateType;

        PortfolioStateNode() = default;
        ~PortfolioStateNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class CastExprNode : public ExprNode
    {
    public:
        TypeNode *targetType = nullptr;
        ExprNode *expr = nullptr;

        CastExprNode() = default;
        ~CastExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class CommaExprNode : public ExprNode
    {
    public:
        Vec<ExprNode *> expressions;

        CommaExprNode() = default;
        ~CommaExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class FuncNode : public ASTNode
    {
    public:
        String name;
        TypeNode *returnType = nullptr;
        Vec<ParamNode *> params;
        CmpdStmtNode *body = nullptr;

        FuncNode() = default;
        ~FuncNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    // Represents group_declarator in parser
    class GroupDeclarator : public ASTNode
    {
    public:
        Declarator *declarator = nullptr;
        ExprNode *bitfield = nullptr; // For bitfield specification (: conditional_expression)
        bool isBitfieldOnly = false;  // True if only bitfield without declarator

        GroupDeclarator() = default;
        ~GroupDeclarator() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    // Represents group_declaration in parser
    class GroupDeclaration : public ASTNode
    {
    public:
        TypeNode *type = nullptr;
        Vec<GroupDeclarator *> declarators;

        GroupDeclaration() = default;
        ~GroupDeclaration() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class GroupNode : public ASTNode
    {
    public:
        String id;                       // Can be empty for anonymous groups
        Vec<GroupDeclaration *> members; // Group member declarations
        bool isReference = false;        // True if just "GROUP IDENTIFIER" (reference to existing)

        GroupNode() = default;
        ~GroupNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class StratDeclNode : public ASTNode
    {
    public:
        String symbol;        // SYMBOL = STRINGLIT
        Vec<int> timeframe;   // TIMEFRAME = {int, int, int}
        int positionSize = 0; // P_SIZE = INTLIT

        StratDeclNode() = default;
        ~StratDeclNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class IndicatorNode : public ASTNode
    {
    public:
        CmpdStmtNode *body = nullptr;

        IndicatorNode() = default;
        ~IndicatorNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class RegimeNode : public ASTNode
    {
    public:
        CmpdStmtNode *body = nullptr;

        RegimeNode() = default;
        ~RegimeNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class SignalFuncNode : public ASTNode
    {
    public:
        String regimeId; // Optional: IDENTIFIER SCOPE signal_type (empty if no regime scope)
        SignalType signalType;
        CmpdStmtNode *body = nullptr;

        SignalFuncNode() = default;
        ~SignalFuncNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class StrategyNode : public ASTNode
    {
    public:
        String id;
        StratDeclNode *declarations = nullptr; // Strategy declarations (symbol, timeframe, position size)
        IndicatorNode *indicators = nullptr;   // Optional indicator section
        RegimeNode *regimes = nullptr;         // Optional regime section
        Vec<SignalFuncNode *> signals;         // Signal function list

        StrategyNode() = default;
        ~StrategyNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ProgramNode : public ASTNode
    {
    public:
        Vec<FuncNode *> functions;
        Vec<DeclNode *> globalDeclarations;
        Vec<StrategyNode *> strategies;
        Vec<GroupNode *> groups; // Top-level group definitions

        ProgramNode() = default;
        ~ProgramNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

}

#endif