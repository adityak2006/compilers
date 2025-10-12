#include <iostream>
#include <vector>
using namespace std;

typedef enum DataTypes
{
    INT,
    FLOAT,
    BOOL,
    STRING,
    VOID
};

class CmpdStmtNode
{
public:
    vector<DeclNode *> declarations;
    vector<StmtNode *> statements;
};

class TypeNode
{
public:
    DataTypes type;
    bool constFlag;
    string id;
    bool userDefinedFlag;
};

class InitDeclarator
{
public:
    Declarator *declarator;
    Initializer *initializer; // if initial value is assigned
};

class Declarator
{
public:
    string id;
    bool arrayFlag;
    ExprNode *arraySize;
    bool funcFlag;
    vector<ParamNode *> params;
};

class Initializer
{
public:
    vector<Initializer *> initializerList;
    ExprNode *expr;
};

class ExprNode
{
};

class ForNode
{
};

class WhileNode
{
};

class FuncNode
{
public:
    string name;
    TypeNode *returnType;
    vector<ParamNode *> params;
    CmpdStmtNode *body;
};

class ParamNode
{
public:
    TypeNode *type;
    string id;
};

class DeclNode
{
public:
    TypeNode *type;
    vector<InitDeclarator *> decls;
};

class StmtNode
{
};

class GroupNode
{
public:
    string id;
    CmpdStmtNode *body;
};

class StratDeclNode
{
public:
    string id;
    vector<int> timeframe;
    int positionSize;
};

class IndicatorNode
{
public:
    CmpdStmtNode *body;
};

class RegimeNode
{
public:
    CmpdStmtNode *body;
};

class SignalFuncNode
{
public:
    string id;
    int signalType;
    CmpdStmtNode *body;
};

class StrategyNode
{
public:
    string id;
    vector<StratDeclNode *> declarations;
    vector<IndicatorNode *> indicators;
    vector<RegimeNode *> regimes;
    vector<SignalFuncNode *> signals;
};

class LiteralIntNode
{
public:
    int value;
};

class LiteralFloatNode
{
public:
    double value;
};

class LiteralStringNode
{
public:
    string value;
};

class LiteralBoolNode
{
public:
    bool value;
};

class IdentifierNode
{
public:
    string id;
    void *symbolEntry = nullptr;
};

class BinaryExprNode
{
public:
    string op;
    ExprNode *leftOperand;
    ExprNode *rightOperand;

};

class UnaryExprNode
{
public:
    std::string op; 
    ExprNode *operand;
};

class AssignmentNode
{
public:
    IdentifierNode* target;
    ExprNode *value;
};

class CallNode
{
public:
    ExprNode *callee;
    vector<ExprNode*> arguments;
};

class MemberAccessNode
{
public:
    ExprNode *object;
    std::string member;
};

class IfNode
{
public:
    ExprNode *condition;
    StmtNode *thenBranch;
    StmtNode *elseBranch;
};

class WhileNode
{
public:
    ExprNode *condition;
    CmpdStmtNode *body;
};

class ForNode
{
public:
    StmtNode* initialisation;
    ExprNode* condition;
    ExprNode* postLoopExpr;
    CmpdStmtNode* body;
};

class ReturnNode
{
public:
    ExprNode *expr;
};

class BreakNode
{
};
class ContinueNode
{
};