#ifndef AST_H
#define AST_H

#include <string>
#include <iostream>
#include <vector>



namespace ast
{
    inline void printTabs(int tabs)
    {
        for(int i=0;i<tabs;i++){
            std::cout << "\t";
        }
        
    }
    enum class ASTNodeType {
        DeclNode, StmtNode, ExprNode, ParamNode, Declarator, Initializer, 
        CmpdStmtNode, TypeNode, InitDeclarator, FuncNode, GroupNode, StrategyNode,
        StratDeclNode, IndicatorNode, RegimeNode, SignalFuncNode, ExprStmtNode,
        ProgramNode, GroupDeclaration, GroupDeclarator, ASTNode, ReturnNode,
        BreakNode, ContinueNode, IfNode, WhileNode, ForNode,LiteralIntNode, LiteralFloatNode,
        LiteralStringNode, LiteralBoolNode, IdentifierNode, BinaryExprNode, UnaryExprNode,
        AssignmentNode,CallNode,CommaExprNode,MemberAccessNode,ArrayAccessNode,ConditionalExprNode,
        TimeseriesNode,PortfolioStateNode, CastExprNode, SignalFuncListNode
    };
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
    class ExprStmtNode;
    class ProgramNode;
    class GroupDeclaration;
    class GroupDeclarator;
    class ASTNode;
    class ReturnNode;
    class BreakNode;
    class ContinueNode;
    class IfNode;
    class WhileNode;
    class ForNode;
    class LiteralIntNode;
    class LiteralFloatNode;
    class LiteralStringNode;
    class LiteralBoolNode;
    class IdentifierNode;
    class BinaryExprNode;
    class UnaryExprNode;
    class AssignmentNode;
    class CallNode;
    class CommaExprNode;
    class MemberAccessNode;
    class ArrayAccessNode;
    class ConditionalExprNode;
    class TimeseriesNode;
    class PortfolioStateNode;
    class CastExprNode;
    class SignalFuncListNode;
    

    enum DataTypes
    {
        INT_TYPE,
        FLOAT_TYPE,
        BOOL_TYPE,
        STRING_TYPE,
        VOID_TYPE,
        RGM_TYPE,
        TIMESERIES_TYPE,
        GROUP_TYPE
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
        virtual void visit(CmpdStmtNode &node) {}
        
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
        virtual void visit(SignalFuncListNode &node){}

        // Program root
        virtual void visit(ProgramNode &node) {}
    };

    class ASTNode
    {
    public:
        ASTNodeType nodeType;
        ASTNode() : nodeType(ASTNodeType::ASTNode) {}
        virtual ~ASTNode() = default;
        
        ASTNode(const ASTNode &) = delete;
        ASTNode &operator=(const ASTNode &) = delete;
        virtual void printNode(){
            std::cout << "ASTNode" << std::endl;
        }
        virtual void accept(ASTVisitor &) {}
    };
    class CmpdStmtNode : public ASTNode
    {
    public:
        std::vector<DeclNode *> declarations;
        std::vector<StmtNode *> statements;

        CmpdStmtNode() : ASTNode() { nodeType = ASTNodeType::CmpdStmtNode; }
        ~CmpdStmtNode() override = default;
        void printNode(int tabs){
            if(declarations.size()>0){
                std::cout << "compound" << std::endl;
            }
            else{
                std::cout << "NULL" << std::endl;
            }
        }
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };
    
    class TypeNode : public ASTNode
    {
    public:
        DataTypes type = INT_TYPE;
        bool constFlag = false;
        std::string id;
        bool userDefinedFlag = false;
        
        TypeNode() : ASTNode() { nodeType = ASTNodeType::TypeNode; }
        ~TypeNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ParamNode : public ASTNode
    {
    public:
        TypeNode *type = NULL;
        std::string id;

        ParamNode() : ASTNode() { nodeType = ASTNodeType::ParamNode; }
        ~ParamNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class Declarator : public ASTNode
    {
    public:
        std::string id;
        bool arrayFlag = false;
        ExprNode *arraySize = NULL;
        bool funcFlag = false;
        std::vector<ParamNode *> params;

        Declarator() : ASTNode() { nodeType = ASTNodeType::Declarator; }
        ~Declarator() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class Initializer : public ASTNode
    {
    public:
        std::vector<Initializer *> initializerList;
        ExprNode *expr = NULL;

        Initializer() : ASTNode() { nodeType = ASTNodeType::Initializer; }
        ~Initializer() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class InitDeclarator : public ASTNode
    {
    public:
        Declarator *declarator = NULL;
        Initializer *initializer = NULL;

        InitDeclarator() : ASTNode() { nodeType = ASTNodeType::InitDeclarator; }
        ~InitDeclarator() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class DeclNode : public ASTNode
    {
    public:
        TypeNode *type = NULL;
        std::vector<InitDeclarator *> decls;

        DeclNode() : ASTNode() { nodeType = ASTNodeType::DeclNode; }
        ~DeclNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class StmtNode : public ASTNode
    {
    public:
        StmtNode() : ASTNode() { nodeType = ASTNodeType::StmtNode; }
        ~StmtNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ExprStmtNode : public StmtNode
    {
    public:
        ExprNode *expr = NULL;
        ExprStmtNode() : StmtNode() { nodeType = ASTNodeType::ExprStmtNode; }
        ~ExprStmtNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ReturnNode : public StmtNode
    {
    public:
        ExprNode *expr = NULL;
        ReturnNode() : StmtNode() { nodeType = ASTNodeType::ReturnNode; }
        ~ReturnNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class BreakNode : public StmtNode
    {
    public:
        BreakNode() : StmtNode() { nodeType = ASTNodeType::BreakNode; }
        ~BreakNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ContinueNode : public StmtNode
    {
    public:
        ContinueNode() : StmtNode() { nodeType = ASTNodeType::ContinueNode; }
        ~ContinueNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class IfNode : public StmtNode
    {
    public:
        ExprNode *condition = NULL;
        StmtNode *thenBranch = NULL;
        StmtNode *elseBranch = NULL;

        IfNode() : StmtNode() { nodeType = ASTNodeType::IfNode; }
        ~IfNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class WhileNode : public StmtNode
    {
    public:
        ExprNode *condition = NULL;
        StmtNode *body = NULL;

        WhileNode() : StmtNode() { nodeType = ASTNodeType::WhileNode; }
        ~WhileNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ForNode : public StmtNode
    {
    public:
        ExprNode *init = NULL; // Can be expression_statement
        ExprNode *condition = NULL;
        ExprNode *increment = NULL;
        StmtNode *body = NULL;

        ForNode() : StmtNode() { nodeType = ASTNodeType::ForNode; }
        ~ForNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class CmpdStmtAsStmtNode : public StmtNode
    {
    public:
        CmpdStmtNode *body = NULL;
        CmpdStmtAsStmtNode() : StmtNode() { nodeType = ASTNodeType::CmpdStmtNode; }
        ~CmpdStmtAsStmtNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ExprNode : public ASTNode
    {
    public:
        ExprNode() : ASTNode() { nodeType = ASTNodeType::ExprNode; }
        ~ExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class LiteralIntNode : public ExprNode
    {
    public:
        int value = 0;
        LiteralIntNode() : ExprNode() { nodeType = ASTNodeType::LiteralIntNode; }
        ~LiteralIntNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class LiteralFloatNode : public ExprNode
    {
    public:
        double value = 0.0;
        LiteralFloatNode() : ExprNode() { nodeType = ASTNodeType::LiteralFloatNode; }
        ~LiteralFloatNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };
    
    class LiteralStringNode : public ExprNode
    {
    public:
        std::string value;
        LiteralStringNode() : ExprNode() { nodeType = ASTNodeType::LiteralStringNode; }
        ~LiteralStringNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };
    
    class LiteralBoolNode : public ExprNode
    {
    public:
        bool value = false;
        LiteralBoolNode() : ExprNode() { nodeType = ASTNodeType::LiteralBoolNode; }
        ~LiteralBoolNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class IdentifierNode : public ExprNode
    {
    public:
        std::string id;
        void *symbolEntry = NULL;

        IdentifierNode() : ExprNode() { nodeType = ASTNodeType::IdentifierNode; }
        ~IdentifierNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };
    
    class BinaryExprNode : public ExprNode
    {
    public:
        std::string op;
        ExprNode *leftOperand = NULL;
        ExprNode *rightOperand = NULL;

        BinaryExprNode() : ExprNode() { nodeType = ASTNodeType::BinaryExprNode; }
        ~BinaryExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class UnaryExprNode : public ExprNode
    {
    public:
        std::string op;
        ExprNode *operand = NULL;

        UnaryExprNode() : ExprNode() { nodeType = ASTNodeType::UnaryExprNode; }
        ~UnaryExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class AssignmentNode : public ExprNode
    {
    public:
        ExprNode *target = NULL; // Changed from IdentifierNode* to support array access
        ExprNode *value = NULL;

        AssignmentNode() : ExprNode() { nodeType = ASTNodeType::AssignmentNode; }
        ~AssignmentNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class CallNode : public ExprNode
    {
    public:
        ExprNode *callee = NULL;
        std::vector<ExprNode *> arguments;

        CallNode() : ExprNode() { nodeType = ASTNodeType::CallNode; }
        ~CallNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };
    
    class MemberAccessNode : public ExprNode
    {
    public:
        ExprNode *object = NULL;
        std::string member;

        MemberAccessNode() : ExprNode() { nodeType = ASTNodeType::MemberAccessNode; }
        ~MemberAccessNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ArrayAccessNode : public ExprNode
    {
    public:
        ExprNode *array = NULL;
        ExprNode *index = NULL;

        ArrayAccessNode() : ExprNode() { nodeType = ASTNodeType::ArrayAccessNode; }
        ~ArrayAccessNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class ConditionalExprNode : public ExprNode
    {
    public:
        ExprNode *condition = NULL;
        ExprNode *thenExpr = NULL;
        ExprNode *elseExpr = NULL;

        ConditionalExprNode() : ExprNode() { nodeType = ASTNodeType::ConditionalExprNode; }
        ~ConditionalExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class TimeseriesNode : public ExprNode
    {
    public:
        TimeseriesFuncType funcType;
        std::vector<ExprNode *> args; // Can be timeseries expressions or identifiers

        TimeseriesNode() : ExprNode() { nodeType = ASTNodeType::TimeseriesNode; }
        ~TimeseriesNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class PortfolioStateNode : public ExprNode
    {
    public:
        PortfolioStateType stateType;

        PortfolioStateNode() : ExprNode() { nodeType = ASTNodeType::PortfolioStateNode; }
        ~PortfolioStateNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class CastExprNode : public ExprNode
    {
    public:
        TypeNode *targetType = NULL;
        ExprNode *expr = NULL;

        CastExprNode() : ExprNode() { nodeType = ASTNodeType::CastExprNode; }
        ~CastExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class CommaExprNode : public ExprNode
    {
    public:
        std::vector<ExprNode *> expressions;

        CommaExprNode() : ExprNode() { nodeType = ASTNodeType::CommaExprNode; }
        ~CommaExprNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class FuncNode : public ASTNode
    {
    public:
        std::string name;
        TypeNode *returnType = NULL;
        std::vector<ParamNode *> params;
        CmpdStmtNode *body = NULL;

        FuncNode() : ASTNode() { nodeType = ASTNodeType::FuncNode; }
        ~FuncNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    // Represents group_declarator in parser
    class GroupDeclarator : public ASTNode
    {
    public:
        Declarator *declarator = NULL;
        ExprNode *bitfield = NULL; // For bitfield specification (: conditional_expression)
        bool isBitfieldOnly = false;  // True if only bitfield without declarator
        
        GroupDeclarator() : ASTNode() { nodeType = ASTNodeType::GroupDeclarator; }
        ~GroupDeclarator() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    // Represents group_declaration in parser
    class GroupDeclaration : public ASTNode
    {
    public:
        TypeNode *type = NULL;
        std::vector<GroupDeclarator *> declarators;

        GroupDeclaration() : ASTNode() { nodeType = ASTNodeType::GroupDeclaration; }
        ~GroupDeclaration() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class GroupNode : public ASTNode
    {
    public:
        std::string id;                       // Can be empty for anonymous groups
        std::vector<GroupDeclaration *> members; // Group member declarations
        bool isReference = false;        // True if just "GROUP IDENTIFIER" (reference to existing)

        GroupNode() : ASTNode() { nodeType = ASTNodeType::GroupNode; }
        ~GroupNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class StratDeclNode : public ASTNode
    {
    public:
        std::string symbol;        // SYMBOL = STRINGLIT
        std::vector<int> timeframe;   // TIMEFRAME = {int, int, int}
        int positionSize = 0; // P_SIZE = INTLIT

        StratDeclNode() : ASTNode() { nodeType = ASTNodeType::StratDeclNode; }
        ~StratDeclNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class IndicatorNode : public ASTNode
    {
    public:
        CmpdStmtNode *body = NULL;

        IndicatorNode() : ASTNode() { nodeType = ASTNodeType::IndicatorNode; }
        ~IndicatorNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class RegimeNode : public ASTNode
    {
    public:
        CmpdStmtNode *body = NULL;

        RegimeNode() : ASTNode() { nodeType = ASTNodeType::RegimeNode; }
        ~RegimeNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };
    
    class SignalFuncNode : public ASTNode
    {
    public:
        std::string regimeId; // Optional: IDENTIFIER SCOPE signal_type (empty if no regime scope)
        SignalType signalType;
        CmpdStmtNode *body = NULL;

        SignalFuncNode() : ASTNode() { nodeType = ASTNodeType::SignalFuncNode; }
        ~SignalFuncNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
    };
    
    class SignalFuncListNode : public ASTNode
    {
    public:
        std::vector<SignalFuncNode *> signals;
        
        SignalFuncListNode() : ASTNode() { nodeType = ASTNodeType::SignalFuncListNode; }
        ~SignalFuncListNode() override = default;

        void accept(ASTVisitor &v) override { v.visit(*this); }
    };

    class StrategyNode : public ASTNode
    {
    public:
        std::string id;
        StratDeclNode *declarations = NULL; // Strategy declarations (symbol, timeframe, position size)
        IndicatorNode *indicators = NULL;   // Optional indicator section
        RegimeNode *regimes = NULL;         // Optional regime section
        SignalFuncListNode* signals = NULL;       // Signal function list
        
        StrategyNode() : ASTNode() { nodeType = ASTNodeType::StrategyNode; }
        ~StrategyNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
        void printNode(int tabs = 0)
        {
            printTabs(tabs);
            std::cout << "StrategyNode: " << this->id << "\n";
        
            if (this->declarations)
            {
                printTabs(tabs + 1);
                std::cout << "Declarations: Symbol=" << this->declarations->symbol
                        << ", PositionSize=" << this->declarations->positionSize << "\n";

                printTabs(tabs + 1);
                std::cout << "Timeframe: ";
                for (auto t : this->declarations->timeframe)
                    std::cout << t << " ";
                std::cout << "\n";
            }
            
            if (this->indicators && this->indicators->body)
            {
                printTabs(tabs + 1);
                std::cout << "Indicators:\n";
                this->indicators->body->printNode(tabs + 2);
            }
            
            if (this->regimes && this->regimes->body)
            {
                printTabs(tabs + 1);
                std::cout << "Regimes:\n";
                this->regimes->body->printNode(tabs + 2);
            }
            
            if (this->signals)
            {
                printTabs(tabs + 1);
                std::cout << "Signals:\n";
                for (auto sig : this->signals->signals)
                {
                    printTabs(tabs + 2);
                    std::cout << "SignalFunc: ";
                    if (!sig->regimeId.empty())
                        std::cout << "Regime=" << sig->regimeId << ", ";
                    std::cout << "Type=" << static_cast<int>(sig->signalType) << "\n";
                    if (sig->body)
                        sig->body->printNode(tabs + 3);
                }
            }
        }
    };
    
    class ProgramNode : public ASTNode
    {
    public:
        std::vector<FuncNode *> functions;
        std::vector<DeclNode *> globalDeclarations;
        std::vector<StrategyNode *> strategies;
        std::vector<GroupNode *> groups; // Top-level group definitions
        
        ProgramNode() : ASTNode() { nodeType = ASTNodeType::ProgramNode; }
        ~ProgramNode() override = default;
        void accept(ASTVisitor &v) override { v.visit(*this); }
        void printNode()
        {
            std::cout << "ProgramNode\n";
            
            for (auto f : functions)
            {
                std::cout << "Function: " << f->name << "\n";
            }
            
            for (auto d : globalDeclarations)
            {
                std::cout << "Global Declaration\n";
            }
            
            for (auto s : strategies)
            {
                s->printNode();
            }
            
            for (auto g : groups)
            {
                std::cout << "Group: " << g->id << "\n";
            }
        }
    };
    
    
}

#endif