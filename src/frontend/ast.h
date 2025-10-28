#ifndef AST_H
#define AST_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

inline void printTabs(int tabs)
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

enum DataTypes
{
    INT,
    FLOAT,
    BOOL,
    STRING,
    VOID,
    RGM,
    TIMESERIES,
    GROUP
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
    OPEN,
    CLOSE,
    HIGH,
    LOW,
    VOLUME,
    SMA,
    EMA,
    RSI,
    BB,
    ATR,
    SDV,
    MAX,
    MIN,
    SUM,
    MEDIAN,
    AVG,
    ABS,
    CORRELATION,
    SLOPE,
    RSQUARED
};

enum PortfolioStateType
{
    PORTFOLIO_VALUE,
    CASH_AVAILABLE,
    POSITION_SHARES,
    ENTRY_PRICE,
    DAYS_IN_POSITION
};

class ASTNode
{
public:
    ASTNodeType nodeType;
    ASTNode() : nodeType(ASTNodeType::ASTNode) {}
    virtual ~ASTNode() = default;

    virtual void printNode()
    {
        cout << "ASTNode" << endl;
    }
};
class CmpdStmtNode : public ASTNode
{
public:
    vector<DeclNode *> declarations;
    vector<StmtNode *> statements;

    CmpdStmtNode()
    {
        nodeType = ASTNodeType::CmpdStmtNode;
    }
    ~CmpdStmtNode() override = default;
    void printNode(int tabs)
    {
        if (declarations.size() > 0)
        {
            cout << "compound" << endl;
        }
        else
        {
            cout << "NULL" << endl;
        }
    }
};

class TypeNode : public ASTNode
{
public:
    DataTypes type = INT;
    bool constFlag = false;
    string id;
    bool userDefinedFlag = false;
    
    TypeNode()
    {
        nodeType = ASTNodeType::TypeNode;
    }
    ~TypeNode() override = default;
};

class ParamNode : public ASTNode
{
public:
    TypeNode *type = NULL;
    string id;

    ParamNode()
    {
        nodeType = ASTNodeType::ParamNode;
    }
    ~ParamNode() override = default;
};

class Declarator : public ASTNode
{
public:
    string id;
    bool arrayFlag = false;
    ExprNode *arraySize = NULL;
    bool funcFlag = false;
    vector<ParamNode *> params;

    Declarator()
    {
        nodeType = ASTNodeType::Declarator;
    }
    ~Declarator() override = default;
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
    ~Initializer() override = default;
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
    ~InitDeclarator() override = default;
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
    ~DeclNode() override = default;
};

class StmtNode : public ASTNode
{
public:
    StmtNode()
    {
        nodeType = ASTNodeType::StmtNode;
    }
    ~StmtNode() override = default;
};

class ExprStmtNode : public StmtNode
{
public:
    ExprNode *expr = NULL;
    ExprStmtNode()
    {
        nodeType = ASTNodeType::ExprStmtNode;
    }
    ~ExprStmtNode() override = default;
};

class ReturnNode : public StmtNode
{
public:
    ExprNode *expr = NULL;
    ReturnNode()
    {
        nodeType = ASTNodeType::ReturnNode;
    }
    ~ReturnNode() override = default;
};

class BreakNode : public StmtNode
{
public:
    BreakNode()
    {
        nodeType = ASTNodeType::BreakNode;
    }
    ~BreakNode() override = default;
};

class ContinueNode : public StmtNode
{
public:
    ContinueNode()
    {
        nodeType = ASTNodeType::ContinueNode;
    }
    ~ContinueNode() override = default;
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
    ~IfNode() override = default;
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
    ~WhileNode() override = default;
};

class ForNode : public StmtNode
{
public:
    ExprNode *init = NULL;
    ExprNode *condition = NULL;
    ExprNode *increment = NULL;
    StmtNode *body = NULL;

    ForNode()
    {
        nodeType = ASTNodeType::ForNode;
    }
    ~ForNode() override = default;
};

class CmpdStmtAsStmtNode : public StmtNode
{
public:
    CmpdStmtNode *body = NULL;
    CmpdStmtAsStmtNode()
    {
        nodeType = ASTNodeType::CmpdStmtNode;
    }
    ~CmpdStmtAsStmtNode() override = default;
};

class ExprNode : public ASTNode
{
public:
    ExprNode()
    {
        nodeType = ASTNodeType::ExprNode;
    }
    ~ExprNode() override = default;
};

class LiteralIntNode : public ExprNode
{
public:
    int value = 0;
    LiteralIntNode()
    {
        nodeType = ASTNodeType::LiteralIntNode;
    }
    ~LiteralIntNode() override = default;
};

class LiteralFloatNode : public ExprNode
{
public:
    double value = 0.0;
    LiteralFloatNode()
    {
        nodeType = ASTNodeType::LiteralFloatNode;
    }
    ~LiteralFloatNode() override = default;
};

class LiteralStringNode : public ExprNode
{
public:
    string value = "";
    LiteralStringNode()
    {
        nodeType = ASTNodeType::LiteralStringNode;
    }
    ~LiteralStringNode() override = default;
};

class LiteralBoolNode : public ExprNode
{
public:
    bool value = false;
    LiteralBoolNode()
    {
        nodeType = ASTNodeType::LiteralBoolNode;
    }
    ~LiteralBoolNode() override = default;
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
    ~IdentifierNode() override = default;
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
    ~BinaryExprNode() override = default;
};

enum UnaryOpType
{
    REF,
    ADD,
    SUB,
    BITNOT,
    LOGICALNOT
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
    ~UnaryExprNode() override = default;
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
    ~AssignmentNode() override = default;
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
    ~CallNode() override = default;
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
    ~MemberAccessNode() override = default;
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
    ~ArrayAccessNode() override = default;
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
    ~ConditionalExprNode() override = default;
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
    ~TimeseriesNode() override = default;
};

class PortfolioStateNode : public ExprNode
{
public:
    PortfolioStateType stateType;

    PortfolioStateNode()
    {
        nodeType = ASTNodeType::PortfolioStateNode;
    }
    ~PortfolioStateNode() override = default;
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
    ~CastExprNode() override = default;
};

class CommaExprNode : public ExprNode
{
public:
    vector<ExprNode *> expressions;

    CommaExprNode()
    {
        nodeType = ASTNodeType::CommaExprNode;
    }
    ~CommaExprNode() override = default;
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
    ~FuncNode() override = default;
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
    ~GroupDeclarator() override = default;
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
    ~GroupDeclaration() override = default;
};

class GroupNode : public ASTNode
{
public:
    string id = NULL;
    vector<GroupDeclaration *> members;
    bool isReference = false;

    GroupNode()
    {
        nodeType = ASTNodeType::GroupNode;
    }
    ~GroupNode() override = default;
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
    ~StratDeclNode() override = default;
};

class IndicatorNode : public ASTNode
{
public:
    CmpdStmtNode *body = NULL;

    IndicatorNode()
    {
        nodeType = ASTNodeType::IndicatorNode;
    }
    ~IndicatorNode() override = default;
};

class RegimeNode : public ASTNode
{
public:
    CmpdStmtNode *body = NULL;

    RegimeNode()
    {
        nodeType = ASTNodeType::RegimeNode;
    }
    ~RegimeNode() override = default;
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
    ~SignalFuncNode() override = default;
};

class SignalFuncListNode : public ASTNode
{
public:
    vector<SignalFuncNode *> signals;

    SignalFuncListNode()
    {
        nodeType = ASTNodeType::SignalFuncListNode;
    }
    ~SignalFuncListNode() override = default;
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
    ~StrategyNode() override = default;
    void printNode(int tabs = 0)
    {
        printTabs(tabs);
        cout << "StrategyNode: " << this->id << "\n";

        if (this->declarations)
        {
            printTabs(tabs + 1);
            cout << "Declarations: Symbol=" << this->declarations->symbol << ", PositionSize=" << this->declarations->positionSize << "\n";

            printTabs(tabs + 1);
            cout << "Timeframe: ";
            for (auto t : this->declarations->timeframe)
                cout << t << " ";
            cout << "\n";
        }

        if (this->indicators && this->indicators->body)
        {
            printTabs(tabs + 1);
            cout << "Indicators:\n";
            this->indicators->body->printNode(tabs + 2);
        }

        if (this->regimes && this->regimes->body)
        {
            printTabs(tabs + 1);
            cout << "Regimes:\n";
            this->regimes->body->printNode(tabs + 2);
        }

        if (this->signals)
        {
            printTabs(tabs + 1);
            cout << "Signals:\n";
            for (auto sig : this->signals->signals)
            {
                printTabs(tabs + 2);
                cout << "SignalFunc: ";
                if (!sig->regimeId.empty())
                    cout << "Regime=" << sig->regimeId << ", ";
                if (sig->body)
                    sig->body->printNode(tabs + 3);
            }
        }
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
    ~ProgramNode() override = default;
    void printNode()
    {
        cout << "ProgramNode\n";

        for (auto f : functions)
        {
            cout << "Function: " << f->name << "\n";
        }

        for (auto d : globalDeclarations)
        {
            cout << "Global Declaration\n";
        }

        for (auto s : strategies)
        {
            s->printNode();
        }

        for (auto g : groups)
        {
            cout << "Group: " << g->id << "\n";
        }
    }
};

#endif