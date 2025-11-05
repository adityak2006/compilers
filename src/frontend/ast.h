#ifndef AST_H
#define AST_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

static void printTabs(int tabs)
{
    for (int i = 0; i < tabs; i++)
    {
        cout << "\t";
    }
}
enum class ASTNodeType
{
    DeclNode,
    StmtNode,
    ExprNode,
    ParamNode,
    Declarator,
    Initializer,
    CmpdStmtNode,
    TypeNode,
    InitDeclarator,
    FuncNode,
    GroupNode,
    StrategyNode,
    StratDeclNode,
    IndicatorNode,
    RegimeNode,
    SignalFuncNode,
    ExprStmtNode,
    ProgramNode,
    GroupDeclaration,
    GroupDeclarator,
    ASTNode,
    ReturnNode,
    BreakNode,
    ContinueNode,
    IfNode,
    WhileNode,
    ForNode,
    LiteralIntNode,
    LiteralFloatNode,
    LiteralStringNode,
    LiteralBoolNode,
    IdentifierNode,
    BinaryExprNode,
    UnaryExprNode,
    AssignmentNode,
    CallNode,
    CommaExprNode,
    MemberAccessNode,
    ArrayAccessNode,
    ConditionalExprNode,
    TimeseriesNode,
    PortfolioStateNode,
    CastExprNode,
    SignalFuncListNode
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
class ASTVisitor;


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
    ENTRY_LONG,
    ENTRY_SHORT,
    EXIT_LONG,
    EXIT_SHORT
};

enum TimeseriesFuncType
{
    OPEN_TS,
    CLOSE_TS,
    HIGH_TS,
    LOW_TS,
    VOLUME_TS,
    SMA_TS,
    EMA_TS,
    RSI_TS,
    BB_TS,
    ATR_TS,
    SDV_TS,
    MAX_TS,
    MIN_TS,
    SUM_TS,
    MEDIAN_TS,
    AVG_TS,
    ABS_TS,
    CORRELATION_TS,
    SLOPE_TS,
    RSQUARED_TS
};

enum PortfolioStateType
{
    PORTFOLIO_VALUE_STATE,
    CASH_AVAILABLE_STATE,
    POSITION_SHARES_STATE,
    ENTRY_PRICE_STATE,
    DAYS_IN_POSITION_STATE
};

class ASTNode
{
public:
    ASTNodeType nodeType;
    ASTNode() : nodeType(ASTNodeType::ASTNode) {}

    virtual void printNode()
    {
        cout << "ASTNode" << endl;
    }

    virtual void visitAcceptor(ASTVisitor &visitor);
};

class ASTVisitor
{
public:
    virtual void visit(StmtNode &node);
    virtual void visit(DeclNode &node);
    virtual void visit(ExprNode &node);
    virtual void visit(ParamNode &node);
    virtual void visit(Declarator &node);
    virtual void visit(Initializer &node);
    virtual void visit(CmpdStmtNode &node);
    virtual void visit(TypeNode &node);
    virtual void visit(InitDeclarator &node);
    virtual void visit(FuncNode &node);
    virtual void visit(GroupNode &node);
    virtual void visit(StrategyNode &node);
    virtual void visit(StratDeclNode &node);
    virtual void visit(IndicatorNode &node);
    virtual void visit(RegimeNode &node);
    virtual void visit(SignalFuncNode &node);
    virtual void visit(ExprStmtNode &node);
    virtual void visit(ProgramNode &node);
    virtual void visit(GroupDeclaration &node);
    virtual void visit(GroupDeclarator &node);
    virtual void visit(ASTNode &node);
    virtual void visit(ReturnNode &node);
    virtual void visit(BreakNode &node);
    virtual void visit(ContinueNode &node);
    virtual void visit(IfNode &node);
    virtual void visit(WhileNode &node);
    virtual void visit(ForNode &node);
    virtual void visit(LiteralIntNode &node);
    virtual void visit(LiteralFloatNode &node);
    virtual void visit(LiteralStringNode &node);
    virtual void visit(LiteralBoolNode &node);
    virtual void visit(IdentifierNode &node);
    virtual void visit(BinaryExprNode &node);
    virtual void visit(UnaryExprNode &node);
    virtual void visit(AssignmentNode &node);
    virtual void visit(CallNode &node);
    virtual void visit(CommaExprNode &node);
    virtual void visit(MemberAccessNode &node);
    virtual void visit(ArrayAccessNode &node);
    virtual void visit(ConditionalExprNode &node);
    virtual void visit(TimeseriesNode &node);
    virtual void visit(PortfolioStateNode &node);
    virtual void visit(CastExprNode &node);
    virtual void visit(SignalFuncListNode &node);
};

// forward declare SymbolTableVisitor (actual implementation lives in symbol_table_visitor.*)
class SymbolTableVisitor;

class StmtNode : public ASTNode
{
public:
    StmtNode()
    {
        nodeType = ASTNodeType::StmtNode;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        StmtNode currObj = *this;
        visitor.visit(currObj);
    }
};

class CmpdStmtNode : public StmtNode
{
public:
    vector<DeclNode *> declarations;
    vector<StmtNode *> statements;

    CmpdStmtNode()
    {
        nodeType = ASTNodeType::CmpdStmtNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        if (declarations.size() > 0)
        {
            cout << "compound statement" << endl;
        }
        else
        {
            cout << "NULL" << endl;
        }
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        CmpdStmtNode currObj = *this;
        visitor.visit(currObj);
    }
};

class TypeNode : public ASTNode
{
public:
    DataTypes type = INT_TYPE;
    bool constFlag = false;
    string id;
    bool userDefinedFlag = false;
    Declarator *abstractDecl = NULL;
    TypeNode()
    {
        nodeType = ASTNodeType::TypeNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "TypeNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        TypeNode currObj = *this;
        visitor.visit(currObj);
    }
};

class ParamNode : public ASTNode
{
public:
    TypeNode *type = NULL;
    string id;
    Declarator *declarator = NULL;

    ParamNode()
    {
        nodeType = ASTNodeType::ParamNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "TypeNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        ParamNode currObj = *this;
        visitor.visit(currObj);
    }
};

class Declarator : public ASTNode
{
public:
    string id;
    bool arrayFlag = false;
    vector<ExprNode *> arraySizes;
    bool funcFlag = false;
    vector<ParamNode *> params;

    Declarator()
    {
        nodeType = ASTNodeType::Declarator;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "Declarator" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        Declarator currObj = *this;
        visitor.visit(currObj);
    }
};

class Initializer : public ASTNode
{
public:
    vector<Initializer *> initializerList;
    ExprNode *expr = NULL;

    Initializer()
    {
        nodeType = ASTNodeType::Initializer;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "Initializer" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        Initializer currObj = *this;
        visitor.visit(currObj);
    }
};

class InitDeclarator : public ASTNode
{
public:
    Declarator *declarator = NULL;
    Initializer *initializer = NULL;

    InitDeclarator()
    {
        nodeType = ASTNodeType::InitDeclarator;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "InitDeclarator" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        InitDeclarator currObj = *this;
        visitor.visit(currObj);
    }
};

class DeclNode : public ASTNode
{
public:
    TypeNode *type = NULL;
    vector<InitDeclarator *> decls;

    DeclNode()
    {
        nodeType = ASTNodeType::DeclNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "DeclNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        DeclNode currObj = *this;
        visitor.visit(currObj);
    }
};


class ExprStmtNode : public StmtNode
{
public:
    ExprNode *expr = NULL;
    ExprStmtNode()
    {
        nodeType = ASTNodeType::ExprStmtNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "ExprStmtNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        ExprStmtNode currObj = *this;
        visitor.visit(currObj);
    }
};

class ReturnNode : public StmtNode
{
public:
    ExprNode *expr = NULL;
    ReturnNode()
    {
        nodeType = ASTNodeType::ReturnNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "ReturnNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        ReturnNode currObj = *this;
        visitor.visit(currObj);
    }
};

class BreakNode : public StmtNode
{
public:
    BreakNode()
    {
        nodeType = ASTNodeType::BreakNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "BreakNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        BreakNode currObj = *this;
        visitor.visit(currObj);
    }
};

class ContinueNode : public StmtNode
{
public:
    ContinueNode()
    {
        nodeType = ASTNodeType::ContinueNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "ContinueNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        ContinueNode currObj = *this;
        visitor.visit(currObj);
    }
};

class IfNode : public StmtNode
{
public:
    ExprNode *condition = NULL;
    StmtNode *thenBranch = NULL;
    StmtNode *elseBranch = NULL;

    IfNode()
    {
        nodeType = ASTNodeType::IfNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "IfNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        IfNode currObj = *this;
        visitor.visit(currObj);
    }
};

class WhileNode : public StmtNode
{
public:
    ExprNode *condition = NULL;
    StmtNode *body = NULL;

    WhileNode()
    {
        nodeType = ASTNodeType::WhileNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "WhileNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        WhileNode currObj = *this;
        visitor.visit(currObj);
    }
};

class ForNode : public StmtNode
{
public:
    ASTNode *init = NULL;
    ExprNode *condition = NULL;
    ExprNode *increment = NULL;
    StmtNode *body = NULL;

    ForNode()
    {
        nodeType = ASTNodeType::ForNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "ForNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        ForNode currObj = *this;
        visitor.visit(currObj);
    }
};

class CmpdStmtAsStmtNode : public StmtNode
{
public:
    CmpdStmtNode *body = NULL;
    CmpdStmtAsStmtNode()
    {
        nodeType = ASTNodeType::CmpdStmtNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "CmpdStmtAsStmtNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        CmpdStmtAsStmtNode currObj = *this;
        visitor.visit(currObj);
    }
};

class ExprNode : public ASTNode
{
public:
    ExprNode()
    {
        nodeType = ASTNodeType::ExprNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "ExprNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        ExprNode currObj = *this;
        visitor.visit(currObj);
    }
};

class LiteralIntNode : public ExprNode
{
public:
    int value = 0;
    LiteralIntNode()
    {
        nodeType = ASTNodeType::LiteralIntNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "LiteralIntNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        LiteralIntNode currObj = *this;
        visitor.visit(currObj);
    }
};

class LiteralFloatNode : public ExprNode
{
public:
    double value = 0.0;
    LiteralFloatNode()
    {
        nodeType = ASTNodeType::LiteralFloatNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "LiteralFloatNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        LiteralFloatNode currObj = *this;
        visitor.visit(currObj);
    }
};

class LiteralStringNode : public ExprNode
{
public:
    string value = "";
    LiteralStringNode()
    {
        nodeType = ASTNodeType::LiteralStringNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "LiteralFloatNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        LiteralStringNode currObj = *this;
        visitor.visit(currObj);
    }
};

class LiteralBoolNode : public ExprNode
{
public:
    bool value = false;
    LiteralBoolNode()
    {
        nodeType = ASTNodeType::LiteralBoolNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "LiteralBoolNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        LiteralBoolNode currObj = *this;
        visitor.visit(currObj);
    }
};

class IdentifierNode : public ExprNode
{
public:
    string id;
    void *symbolEntry = NULL;

    IdentifierNode()
    {
        nodeType = ASTNodeType::IdentifierNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "IdentifierNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        IdentifierNode currObj = *this;
        visitor.visit(currObj);
    }
};

class BinaryExprNode : public ExprNode
{
public:
    string op;
    ExprNode *leftOperand = NULL;
    ExprNode *rightOperand = NULL;

    BinaryExprNode()
    {
        nodeType = ASTNodeType::BinaryExprNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "BinaryExprNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        BinaryExprNode currObj = *this;
        visitor.visit(currObj);
    }
};

enum UnaryOpType
{
    REF_OP,
    ADD_OP,
    SUB_OP,
    BITNOT_OP,
    LOGICALNOT_OP
};

class UnaryExprNode : public ExprNode
{
public:
    UnaryOpType op;
    ExprNode *operand = NULL;

    UnaryExprNode()
    {
        nodeType = ASTNodeType::UnaryExprNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "UnaryExprNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        UnaryExprNode currObj = *this;
        visitor.visit(currObj);
    }
};

class AssignmentNode : public ExprNode
{
public:
    ExprNode *target = NULL;
    ExprNode *value = NULL;

    AssignmentNode()
    {
        nodeType = ASTNodeType::AssignmentNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "AssignmentNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        AssignmentNode currObj = *this;
        visitor.visit(currObj);
    }
};

class CallNode : public ExprNode
{
public:
    ExprNode *callee = NULL;
    vector<ExprNode *> arguments;

    CallNode()
    {
        nodeType = ASTNodeType::CallNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "CallNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        CallNode currObj = *this;
        visitor.visit(currObj);
    }
};

class MemberAccessNode : public ExprNode
{
public:
    ExprNode *object = NULL;
    string member;

    MemberAccessNode()
    {
        nodeType = ASTNodeType::MemberAccessNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "MemberAccessNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        MemberAccessNode currObj = *this;
        visitor.visit(currObj);
    }
};

class ArrayAccessNode : public ExprNode
{
public:
    ExprNode *array = NULL;
    ExprNode *index = NULL;

    ArrayAccessNode()
    {
        nodeType = ASTNodeType::ArrayAccessNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "ArrayAccessNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        ArrayAccessNode currObj = *this;
        visitor.visit(currObj);
    }
};

class ConditionalExprNode : public ExprNode
{
public:
    ExprNode *condition = NULL;
    ExprNode *thenExpr = NULL;
    ExprNode *elseExpr = NULL;

    ConditionalExprNode()
    {
        nodeType = ASTNodeType::ConditionalExprNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "ConditionalExprNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        ConditionalExprNode currObj = *this;
        visitor.visit(currObj);
    }
};

class TimeseriesNode : public ExprNode
{
public:
    TimeseriesFuncType funcType;
    vector<ExprNode *> args;

    TimeseriesNode()
    {
        nodeType = ASTNodeType::TimeseriesNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "TimerSeriesNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        TimeseriesNode currObj = *this;
        visitor.visit(currObj);
    }
};

class PortfolioStateNode : public ExprNode
{
public:
    PortfolioStateType stateType;

    PortfolioStateNode()
    {
        nodeType = ASTNodeType::PortfolioStateNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "PortfolioStateNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        PortfolioStateNode currObj = *this;
        visitor.visit(currObj);
    }
};

class CastExprNode : public ExprNode
{
public:
    TypeNode *targetType = NULL;
    ExprNode *expr = NULL;

    CastExprNode()
    {
        nodeType = ASTNodeType::CastExprNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "CastExprNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        CastExprNode currObj = *this;
        visitor.visit(currObj);
    }
};

class CommaExprNode : public ExprNode
{
public:
    vector<ExprNode *> expressions;

    CommaExprNode()
    {
        nodeType = ASTNodeType::CommaExprNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "CommaExprNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        CommaExprNode currObj = *this;
        visitor.visit(currObj);
    }
};

class FuncNode : public ASTNode
{
public:
    string name;
    TypeNode *returnType = NULL;
    vector<ParamNode *> params;
    CmpdStmtNode *body = NULL;

    FuncNode()
    {
        nodeType = ASTNodeType::FuncNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "FuncNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        FuncNode currObj = *this;
        visitor.visit(currObj);
    }
};

class GroupDeclarator : public ASTNode
{
public:
    Declarator *declarator = NULL;
    ExprNode *bitfield = NULL;
    bool isBitfieldOnly = false;

    GroupDeclarator()
    {
        nodeType = ASTNodeType::GroupDeclarator;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "GroupDeclaratorNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        GroupDeclarator currObj = *this;
        visitor.visit(currObj);
    }
};

class GroupDeclaration : public ASTNode
{
public:
    TypeNode *type = NULL;
    vector<GroupDeclarator *> declarators;

    GroupDeclaration()
    {
        nodeType = ASTNodeType::GroupDeclaration;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "GroupDeclarationNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        GroupDeclaration currObj = *this;
        visitor.visit(currObj);
    }
};

class GroupNode : public ASTNode
{
public:
    string id;
    vector<GroupDeclaration *> members;
    bool isReference = false;

    GroupNode()
    {
        nodeType = ASTNodeType::GroupNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "GroupNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        GroupNode currObj = *this;
        visitor.visit(currObj);
    }
};

class StratDeclNode : public ASTNode
{
public:
    string symbol;
    vector<int> timeframe;
    int positionSize = 0;

    StratDeclNode()
    {
        nodeType = ASTNodeType::StratDeclNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "StratDeclNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        StratDeclNode currObj = *this;
        visitor.visit(currObj);
    }
};

class IndicatorNode : public ASTNode
{
public:
    CmpdStmtNode *body = NULL;

    IndicatorNode()
    {
        nodeType = ASTNodeType::IndicatorNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "IndicatorNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        IndicatorNode currObj = *this;
        visitor.visit(currObj);
    }
};

class RegimeNode : public ASTNode
{
public:
    CmpdStmtNode *body = NULL;

    RegimeNode()
    {
        nodeType = ASTNodeType::RegimeNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "RegimeNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        RegimeNode currObj = *this;
        visitor.visit(currObj);
    }
};

class SignalFuncNode : public ASTNode
{
public:
    string regimeId;
    SignalType signalType;
    CmpdStmtNode *body = NULL;

    SignalFuncNode()
    {
        nodeType = ASTNodeType::SignalFuncNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "SignalFuncNode" << endl;
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        SignalFuncNode currObj = *this;
        visitor.visit(currObj);
    }
};

class SignalFuncListNode : public ASTNode
{
public:
    vector<SignalFuncNode *> signals;

    SignalFuncListNode()
    {
        nodeType = ASTNodeType::SignalFuncListNode;
    }
    void printNode(int tabs)
    {
        printTabs(tabs);
        cout << "SignalFuncListNode" << endl;
        for (int i = 0; i < signals.size(); i++)
        {
            signals[i]->printNode(tabs + 1);
        }
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        SignalFuncListNode currObj = *this;
        visitor.visit(currObj);
    }
};

class StrategyNode : public ASTNode
{
public:
    string id;
    StratDeclNode *declarations = NULL;
    IndicatorNode *indicators = NULL;
    RegimeNode *regimes = NULL;
    SignalFuncListNode *signals = NULL;

    StrategyNode()
    {
        nodeType = ASTNodeType::StrategyNode;
    }
    void printNode(int tabs = 0)
    {
        printTabs(tabs);
        cout << "StrategyNode: " << this->id << "\n";

        if (this->declarations)
        {
            declarations->printNode(tabs + 1);
        }

        if (this->indicators && this->indicators->body)
        {
            indicators->printNode(tabs + 1);
        }

        if (this->regimes && this->regimes->body)
        {
            regimes->printNode(tabs + 1);
        }

        if (this->signals)
        {
            signals->printNode(tabs + 1);
        }
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        StrategyNode currObj = *this;
        visitor.visit(currObj);
    }
};

class ProgramNode : public ASTNode
{
public:
    vector<FuncNode *> functions;
    vector<DeclNode *> globalDeclarations;
    vector<StrategyNode *> strategies;
    vector<GroupNode *> groups;

    ProgramNode()
    {
        nodeType = ASTNodeType::ProgramNode;
    }
    void printNode() override
    {
        cout << "ProgramNode\n";
        for (auto f : functions)
        {
            f->printNode(1);
        }

        for (auto d : globalDeclarations)
        {
            d->printNode(1);
        }

        for (auto s : strategies)
        {
            s->printNode(1);
        }

        for (auto g : groups)
        {
            g->printNode(1);
        }
    }
    void visitAcceptor(ASTVisitor &visitor)
    {
        ProgramNode currObj = *this;
        visitor.visit(currObj);
    }
};

#endif
