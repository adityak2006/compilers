%code requires{
	#include "ast.h"
}

%{
#include <iostream>
#include <string>
#include "ast.h"

using namespace std;

extern FILE *yyin;
extern int col;
int yyparse(void);
int yylex();
void yyerror(const char* s);
extern int yylineno;
extern char *yytext;

ProgramNode* progRoot;
%}


%union {
	ProgramNode* prog;
	ASTNode* node;
	ExprNode* expr;
	StmtNode* stmt;
	FuncNode* func;
	DeclNode* decl;
	ParamNode* param;
	Initializer* init;
	Declarator* declarator;
	CmpdStmtNode* cmpdStmt;
	TypeNode* type;
	InitDeclarator* initDecl;
	GroupNode* group;
	StrategyNode* strategy;
	StratDeclNode* strategyDecl;
	IndicatorNode* indicator;
	RegimeNode* regime;
	SignalFuncNode* signalFunc;
	GroupDeclaration* groupDeclaration;
	GroupDeclarator* groupDeclarator;
	SignalFuncListNode* sigFuncList;
    int intVal;
    float floatVal;
    std::string* id;
	std::vector<ExprNode*>* exprVec;
	std::vector<StmtNode*>* stmtVec;
	std::vector<DeclNode*>* declVec;
	std::vector<InitDeclarator*>* initDeclVec;
	std::vector<Initializer*>* initList;
	std::vector<ParamNode*>* paramVec;
	std::vector<GroupDeclaration*>* groupDeclList;
	std::vector<GroupDeclarator*>* groupDeclaratorList;

}

%token STRATEGY SYMBOL TIMEFRAME P_SIZE INDICATORS REGIMES 
%token FUN REF SCOPE ARROW
%token ENTRYLONG ENTRYSHORT EXITLONG EXITSHORT
%token OPEN CLOSE HIGH LOW VOLUME
%token POSITION_SHARES ENTRY_PRICE DAYS_IN_POSITION PORTFOLIO_VALUE CASH_AVAILABLE
%token SMA EMA RSI BB ATR SDV MAX MIN SUM MEDIAN AVG ABS CORRELATION SLOPE RSQUARED
%token GROUP 

%token FOR WHILE IF ELSE CONTINUE BREAK RETURN

%token INT FLOAT BOOL VOID STRING RGM CONST TIMESERIES

%token AND OR LEFT_OP RIGHT_OP LEQ GEQ EQ NEQ

%token <id> IDENTIFIER STRINGLIT
%token <intVal> INTLIT
%token <floatVal> FLOATLIT 

%type <intVal> unaryOperator
%type <prog> translationUnit
%type <strategy> strategyDefinition strategyBody
%type <strategyDecl> strategyDeclarations
%type <indicator> indicatorSection
%type <regime> regimeSection
%type <signalFunc> signalFunction
%type <sigFuncList> signalFunctionList
%type <node> globalDeclaration
%type <expr> primaryExpression postfixExpression expression unaryExpression castExpression multiplicativeExpression additiveExpression
%type <expr> shiftExpression relationalExpression equalityExpression andExpression exclusiveOrExpression inclusiveOrExpression
%type <expr> logicalAndExpression logicalOrExpression conditionalExpression assignmentExpression timeseries timeseriesExpression
%type <exprVec> argumentExpressionList identifierList

%type <param> parameterDeclaration
%type <paramVec> parameterList

%type <stmtVec> statementList
%type <stmt> compoundStatement statement jumpStatement iterationStatement selectionStatement expressionStatement

%type <func> function_definition
%type <decl> declaration
%type <declVec> declarationList
%type <type> declarationSpecifiers typeSpecifier specifier_qualifierList typeName

%type <init> initializer
%type <initList> initializerList
%type <initDecl> initDeclarator
%type <initDeclVec> initDeclaratorList

%type <declarator> directDeclarator directAbstractDeclarator

%type <group> groupSpecifier
%type <groupDeclaration> groupDeclaration
%type <groupDeclList> groupDeclarationList
%type <groupDeclarator> groupDeclarator
%type <groupDeclaratorList> groupDeclaratorList
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%

translationUnit
    : globalDeclaration {
        $$ = new ProgramNode();
        ASTNode* node = $1;
        if(node->nodeType == ASTNodeType::FuncNode){
            $$->functions.push_back((FuncNode*)node);
		}
        else if(node->nodeType == ASTNodeType::DeclNode){
            $$->globalDeclarations.push_back((DeclNode*)node);
		}
        else if(node->nodeType == ASTNodeType::StrategyNode){
            $$->strategies.push_back((StrategyNode*)node);
		}
		
		progRoot = $$;
    }
    | translationUnit globalDeclaration {
        $$ = $1;
        ASTNode* node = $2;
        if(node->nodeType == ASTNodeType::FuncNode){
            $$->functions.push_back((FuncNode*)node);
		}
        else if(node->nodeType == ASTNodeType::DeclNode){
            $$->globalDeclarations.push_back((DeclNode*)node);
		}
        else if(node->nodeType == ASTNodeType::StrategyNode){
            $$->strategies.push_back((StrategyNode*)node);
		}
		progRoot = $$;
    }
;

strategyDefinition
    : STRATEGY IDENTIFIER '{' strategyBody '}' {
		$$ = new StrategyNode();
		$$->id = *$2;
		if($4){
			$$->declarations = $4->declarations;
			$$->indicators = $4->indicators;
            $$->regimes = $4->regimes;
            $$->signals = $4->signals;
		}
	}
    ;

strategyBody
    : strategyDeclarations indicatorSection regimeSection signalFunctionList {
		$$ = new StrategyNode();
		$$->declarations = $1;
        $$->indicators = $2;
        $$->regimes = $3;
        $$->signals = $4;
	}
    ;

strategyDeclarations
    : SYMBOL '=' STRINGLIT ';' TIMEFRAME '=' '{'INTLIT ',' INTLIT',' INTLIT '}' ';' P_SIZE '=' INTLIT ';' {
		$$ = new StratDeclNode();
		$$->symbol = *$3;
		$$->timeframe.push_back($8);
        $$->timeframe.push_back($10);
        $$->timeframe.push_back($12);
        $$->positionSize = $17;
	}
    ;

indicatorSection
    : {$$ = NULL;}
	| INDICATORS compoundStatement {
		$$ = new IndicatorNode();
        $$->body = (CmpdStmtNode*)$2;
	}
    ;

regimeSection
    : {$$ = NULL;}
	| REGIMES compoundStatement {
		$$ = new RegimeNode();
        $$->body = (CmpdStmtNode*)$2;
	}
    ;

signalFunctionList
    :  { $$ = new SignalFuncListNode(); }
    | signalFunctionList signalFunction {
        $$ = $1;
        if ($2) $$->signals.push_back($2);
    }
    ;

signalFunction
    : IDENTIFIER SCOPE ENTRYLONG compoundStatement {
        $$ = new SignalFuncNode();
        $$->regimeId = *$1;
        $$->signalType = ENTRY_LONG;
        $$->body = (CmpdStmtNode*)$4;
    }
    | IDENTIFIER SCOPE ENTRYSHORT compoundStatement {
        $$ = new SignalFuncNode();
        $$->regimeId = *$1;
        $$->signalType = ENTRY_SHORT;
        $$->body = (CmpdStmtNode*)$4;
    }
    | IDENTIFIER SCOPE EXITLONG compoundStatement {
        $$ = new SignalFuncNode();
        $$->regimeId = *$1;
        $$->signalType = EXIT_LONG;
        $$->body = (CmpdStmtNode*)$4;
    }
    | IDENTIFIER SCOPE EXITSHORT compoundStatement {
        $$ = new SignalFuncNode();
        $$->regimeId = *$1;
        $$->signalType = EXIT_SHORT;
        $$->body = (CmpdStmtNode*)$4;
    }
    | ENTRYLONG compoundStatement {
        $$ = new SignalFuncNode();
        $$->signalType = ENTRY_LONG;
        $$->body = (CmpdStmtNode*)$2;
    }
    | ENTRYSHORT compoundStatement {
        $$ = new SignalFuncNode();
        $$->signalType = ENTRY_SHORT;
        $$->body = (CmpdStmtNode*)$2;
    }
    | EXITLONG compoundStatement {
        $$ = new SignalFuncNode();
        $$->signalType = EXIT_LONG;
        $$->body = (CmpdStmtNode*)$2;
    }
    | EXITSHORT compoundStatement {
        $$ = new SignalFuncNode();
        $$->signalType = EXIT_SHORT;
        $$->body = (CmpdStmtNode*)$2;
    }
    ;

primaryExpression
    : IDENTIFIER {
        $$ = new IdentifierNode();
        ((IdentifierNode*)$$)->id = *$1;
    }
    | INTLIT {
        $$ = new LiteralIntNode();
        ((LiteralIntNode*)$$)->value = $1;
    }
    | FLOATLIT {
        $$ = new LiteralFloatNode();
        ((LiteralFloatNode*)$$)->value = $1;
    }
    | STRINGLIT {
        $$ = new LiteralStringNode();
        ((LiteralStringNode*)$$)->value = *$1;
    }
    | '(' expression ')' { $$ = $2; }
    | timeseriesExpression { $$ = $1; }
    ;

timeseries
    : CLOSE {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::CLOSE_TS;
        $$ = node;
	}
    | OPEN {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::OPEN_TS;
        $$ = node;
	}
    | HIGH {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::HIGH_TS;
        $$ = node;
	}
    | LOW {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::LOW_TS;
        $$ = node;
	}
    | VOLUME {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::VOLUME_TS;
        $$ = node;
	}
    | SMA '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SMA_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | EMA '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::EMA_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | RSI '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSI_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | BB '(' timeseries ',' INTLIT ',' FLOATLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::BB_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		LiteralFloatNode* floatNode = new LiteralFloatNode();
		floatNode->value = $7;
		node->args.push_back($3);
		node->args.push_back(intNode);
		node->args.push_back(floatNode);
        $$ = node;
	}
    | ATR '(' timeseries ',' timeseries ',' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ATR_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $9;
		node->args.push_back($3);
		node->args.push_back($5);
		node->args.push_back($7);
		node->args.push_back(intNode);
        $$ = node;
	}
    | SDV '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SDV_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | MAX '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MAX_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | MIN '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MIN_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | SUM '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SUM_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | MEDIAN '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MEDIAN_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | AVG '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::AVG_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | ABS '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ABS_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | CORRELATION '(' timeseries ',' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::CORRELATION_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $7;
		node->args.push_back($3);
		node->args.push_back($5);
		node->args.push_back(intNode);
        $$ = node;
	}
    | SLOPE '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SLOPE_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | RSQUARED '(' timeseries ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSQUARED_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		node->args.push_back($3);
		node->args.push_back(intNode);
        $$ = node;
	}
    ;

timeseriesExpression
	: timeseries {
		$$ = $1;
	}
    | SMA '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SMA_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
    | EMA '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::EMA_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
    | RSI '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSI_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
    | BB '(' IDENTIFIER ',' INTLIT ',' FLOATLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::BB_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		LiteralFloatNode* floatNode = new LiteralFloatNode();
		floatNode->value = $7;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
		node->args.push_back(floatNode);
        $$ = node;
	}
    | ATR '(' IDENTIFIER ',' IDENTIFIER ',' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ATR_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $9;
		IdentifierNode* idNode1 = new IdentifierNode();
		idNode1->id = *$3;
		IdentifierNode* idNode2 = new IdentifierNode();
		idNode2->id = *$5;
		IdentifierNode* idNode3 = new IdentifierNode();
		idNode3->id = *$7;
		node->args.push_back(idNode1);
		node->args.push_back(idNode2);
		node->args.push_back(idNode3);
		node->args.push_back(intNode);
        $$ = node;
	}
    | SDV '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SDV_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
    | MAX '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MAX_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
    | MIN '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MIN_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
    | SUM '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SUM_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
    | MEDIAN '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MEDIAN_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id =*$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
    | AVG '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::AVG_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
    | ABS '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ABS_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
    | CORRELATION '(' IDENTIFIER ',' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::CORRELATION_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $7;
		IdentifierNode* idNode1 = new IdentifierNode();
		idNode1->id = *$3;
		IdentifierNode* idNode2 = new IdentifierNode();
		idNode2->id = *$5;
		node->args.push_back(idNode1);
		node->args.push_back(idNode2);
		node->args.push_back(intNode);
        $$ = node;
	}
    | SLOPE '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SLOPE_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
    | RSQUARED '(' IDENTIFIER ',' INTLIT ')' {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSQUARED_TS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = $5;
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = *$3;
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        $$ = node;
	}
	;

postfixExpression
	: primaryExpression {
		$$ = $1;
	}
	| postfixExpression '[' expression ']' {
		ArrayAccessNode* arrAccess = new ArrayAccessNode();
		arrAccess->array = (ExprNode*)$1;
		arrAccess->index = (ExprNode*)$3;
		$$ = arrAccess;
	}
	| postfixExpression '(' ')' {
		CallNode* node = new CallNode();
		node->callee = (ExprNode*)$1;
		$$ = node;
	}
	| postfixExpression '(' argumentExpressionList ')' {
		CallNode* node = new CallNode();
		node->callee = (ExprNode*)$1;
		node->arguments = *$3;
		$$ = node;
	}
	| postfixExpression '.' IDENTIFIER {
		MemberAccessNode* node = new MemberAccessNode();
		node->object = (ExprNode*)$1;
		node->member = *$3;
		$$ = node;
	}
	| PORTFOLIO_VALUE {
		PortfolioStateNode* node = new PortfolioStateNode();
		node->stateType = PortfolioStateType::PORTFOLIO_VALUE_STATE;
		$$ = node;
	}
	| CASH_AVAILABLE {
		PortfolioStateNode* node = new PortfolioStateNode();
		node->stateType = PortfolioStateType::CASH_AVAILABLE_STATE;
		$$ = node;
	}
	| POSITION_SHARES {
		PortfolioStateNode* node = new PortfolioStateNode();
		node->stateType = PortfolioStateType::POSITION_SHARES_STATE;
		$$ = node;
	}
	| ENTRY_PRICE {
		PortfolioStateNode* node = new PortfolioStateNode();
		node->stateType = PortfolioStateType::ENTRY_PRICE_STATE;
		$$ = node;
	}
	| DAYS_IN_POSITION {
		PortfolioStateNode* node = new PortfolioStateNode();
		node->stateType = PortfolioStateType::DAYS_IN_POSITION_STATE;
		$$ = node;
	}
	;

argumentExpressionList
	: assignmentExpression {
		$$ = new vector<ExprNode*>();
		$$->push_back((ExprNode*)$1);
	}
	| argumentExpressionList ',' assignmentExpression {
		$$ = $1;
		$$->push_back((ExprNode*)$3);
	}
	;

unaryExpression
	: postfixExpression {
		$$ = $1;
	}
	| unaryOperator castExpression {
		UnaryExprNode* node = new UnaryExprNode();
		node->operand = (ExprNode*)$2;
		if($1==REF){
			node->op = UnaryOpType::REF_OP;
		}
		else if($1=='+'){
			node->op = UnaryOpType::ADD_OP;
		}
		else if($1=='-'){
			node->op = UnaryOpType::SUB_OP;
		}
		else if($1=='~'){
			node->op = UnaryOpType::BITNOT_OP;
		}
		else if($1=='!'){	
			node->op = UnaryOpType::LOGICALNOT_OP;
		}
		$$ = node;
	}
	;

unaryOperator
	: REF {
		$$ = REF;
	}
	| '+' {
		$$ = '+';
	}
	| '-' {
		$$ = '-';
	}
	| '~' {
		$$ = '~';
	}
	| '!' {
		$$ = '!';
	}
	;

castExpression
	: unaryExpression {
		$$ = $1;
	}
	| '(' typeName ')' castExpression {
		CastExprNode* node = new CastExprNode();
		node->targetType = (TypeNode*)$2;
		node->expr = (ExprNode*)$4;
		$$ = node;
	}
	;

multiplicativeExpression
	: castExpression {
		$$ = $1;
	}
	| multiplicativeExpression '*' castExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "*";
		$$ = node;
	}
	| multiplicativeExpression '/' castExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "/";
		$$ = node;

	}
	| multiplicativeExpression '%' castExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "%";
		$$ = node;
	}
	;

additiveExpression
	: multiplicativeExpression {
		$$ = $1;
	}
	| additiveExpression '+' multiplicativeExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "+";
		$$ = node;
	}
	| additiveExpression '-' multiplicativeExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "-";
		$$ = node;
	}
	;

shiftExpression
	: additiveExpression {
		$$ = $1;
	}
	| shiftExpression LEFT_OP additiveExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "<<";
		$$ = node;
	}
	| shiftExpression RIGHT_OP additiveExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = ">>";
		$$ = node;
	}
	;

relationalExpression
	: shiftExpression {
		$$ = $1;
	}
	| relationalExpression '<' shiftExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "<";
		$$ = node;
	}
	| relationalExpression '>' shiftExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = ">";
		$$ = node;
	}
	| relationalExpression LEQ shiftExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "<=";
		$$ = node;
	}
	| relationalExpression GEQ shiftExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = ">=";
		$$ = node;
	}
	;

equalityExpression
	: relationalExpression {
		$$ = $1;
	}
	| equalityExpression EQ relationalExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "==";
		$$ = node;
	}
	| equalityExpression NEQ relationalExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "!=";
		$$ = node;
	}
	;

andExpression
	: equalityExpression {
		$$ = $1;
	}
	| andExpression '&' equalityExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "&";
		$$ = node;
	}
	;

exclusiveOrExpression
	: andExpression {
		$$ = $1;
	}
	| exclusiveOrExpression '^' andExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "^";
		$$ = node;
	}
	;

inclusiveOrExpression
	: exclusiveOrExpression {
		$$ = $1;
	}
	| inclusiveOrExpression '|' exclusiveOrExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "|";
		$$ = node;
	}
	;

logicalAndExpression
	: inclusiveOrExpression {
		$$ = $1;
	}
	| logicalAndExpression AND inclusiveOrExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "AND";
		$$ = node;
	}
	;

logicalOrExpression
	: logicalAndExpression {
		$$ = $1;
	}
	| logicalOrExpression OR logicalAndExpression {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = $1;
		node->rightOperand = $3;
		node->op = "OR";
		$$ = node;
	}
	;

conditionalExpression
	: logicalOrExpression {
		$$ = $1;
	}
	| logicalOrExpression '?' expression ':' conditionalExpression {
		ConditionalExprNode* node = new ConditionalExprNode();
		node->condition = $1;
		node->thenExpr = $3;
		node->elseExpr = $5;
		$$ = node;
	}
	;

assignmentExpression
	: conditionalExpression {
		$$ = $1;
	}
	| unaryExpression '=' assignmentExpression {
		AssignmentNode* node = new AssignmentNode();
		node->target = $1;
		node->value = $3;
		$$ = node;
	}
	;

expression
	: assignmentExpression {
		$$ = $1;
	}
	| expression ',' assignmentExpression {
		CommaExprNode* node;

		if($1->nodeType == ASTNodeType::CommaExprNode){
			node = (CommaExprNode*)$1;
		}
		else{
			node = new CommaExprNode();
			node->expressions.push_back((ExprNode*)$1);
		}
		node->expressions.push_back((ExprNode*)$3);
        $$ = node;
	}
	;

declaration
	: declarationSpecifiers ';' {
		DeclNode* node = new DeclNode();
		node->type = $1;
	}
	| declarationSpecifiers initDeclaratorList ';' {
		DeclNode* node = new DeclNode();
		node->type = $1;
		node->decls = *$2;
	}
	;

declarationSpecifiers
	: typeSpecifier {
		$$ = $1;
	}
	| CONST typeSpecifier {
		$$ = $2;
		$$->constFlag = true;
	}
	;

initDeclaratorList
	: initDeclarator {
		vector<InitDeclarator*>* initVec = new vector<InitDeclarator*>();
		initVec->push_back($1);
		$$ = initVec;
	}
	| initDeclaratorList ',' initDeclarator {
		$$ = $1;
		$$->push_back($3);
	}
	;

initDeclarator
	: directDeclarator  {
		$$ = new InitDeclarator();
		$$->declarator = $1;
	}
	| directDeclarator '=' initializer {
		$$ = new InitDeclarator();
		$$->declarator = $1;
		$$->initializer = $3;
	}
	;


typeSpecifier
	: VOID {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::VOID_TYPE;
		$$ = node;
	}
	| INT  {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::INT_TYPE;
		$$ = node;
	}
	| FLOAT {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::FLOAT_TYPE;
		$$ = node;
	}
    | BOOL {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::BOOL_TYPE;
		$$ = node;
	}
    | STRING {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::STRING_TYPE;
		$$ = node;
	}
	| RGM {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::RGM_TYPE;
		$$ = node;
	}
	| TIMESERIES {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::TIMESERIES_TYPE;
		$$ = node;
	}
	| groupSpecifier {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::GROUP_TYPE;
		node->userDefinedFlag = true;
		$$ = node;
	}
	;

groupSpecifier
	: GROUP IDENTIFIER '{' groupDeclarationList '}' {
		GroupNode* node = new GroupNode();
		node->id = *$2;
		node->members = *$4;
		$$ = node;
	}
	| GROUP '{' groupDeclarationList '}' {
		GroupNode* node = new GroupNode();
		node->members = *$3;
		$$ = node;
	}
	| GROUP IDENTIFIER {
		GroupNode* node = new GroupNode();
		node->id = *$2;
		$$ = node;
	}
	;

groupDeclarationList
	: groupDeclaration {
		vector<GroupDeclaration*>* vec = new vector<GroupDeclaration*>();
        vec->push_back($1);
        $$ = vec;
	}
	| groupDeclarationList groupDeclaration {
		$$ = $1;
		$$->push_back($2);
	}
	;

groupDeclaration
	: specifier_qualifierList groupDeclaratorList ';' {
		GroupDeclaration* node = new GroupDeclaration();
		node->type= $1;
		node->declarators = *$2;
        $$ = node;
	}
	;

specifier_qualifierList
    : typeSpecifier {
        $$ = $1;
    }
    | CONST specifier_qualifierList {
        $2->constFlag = true;
        $$ = $2;
    }
    | typeSpecifier specifier_qualifierList {
        $$ = $1;
    }
    | CONST {
        TypeNode* node = new TypeNode();
        node->constFlag = true;
        $$ = node;
    }
    ;

groupDeclaratorList
	: groupDeclarator {
		vector<GroupDeclarator*>* groupDeclVec = new vector<GroupDeclarator*>();
        groupDeclVec->push_back($1);
        $$ = groupDeclVec;
	}
	| groupDeclaratorList ',' groupDeclarator {
		$$ = $1;
		$$->push_back($3);
	}
	;

groupDeclarator
	: directDeclarator {
		GroupDeclarator* node = new GroupDeclarator();
        node->declarator = $1;
        $$ = node;
	}
	| ':' conditionalExpression {
		GroupDeclarator* node = new GroupDeclarator();
        node->isBitfieldOnly = true;
        node->bitfield = $2;
        $$ = node;
	}
	| directDeclarator ':' conditionalExpression {
		GroupDeclarator* node = new GroupDeclarator();
        node->declarator = $1;
        node->bitfield = $3;
        $$ = node;
	}
	;

directDeclarator
	: IDENTIFIER {
		Declarator* node = new Declarator();
		node->id = *$1;
		$$ = node;
	}
	| '(' directDeclarator ')' {
		$$ = $2;
	}
	| directDeclarator '[' conditionalExpression ']' {
		$$ = $1;
		$$->arrayFlag = true;
		$$->arraySize = $3;
	}
	| directDeclarator '[' ']' {
		$$ = $1;
		$$->arrayFlag = true;
	}
	| directDeclarator '(' parameterList ')' {
		$$ = $1;
		$$->funcFlag = true;
		$$->params = *$3;
	}
	| directDeclarator '(' identifierList ')' {
		$$ = $1;
		$$->funcFlag = true;
		// incomplete
	}
	| directDeclarator '(' ')' {
		$$ = $1;
		$1->funcFlag = true;
	}
	;

parameterList
	: parameterDeclaration {
		vector<ParamNode*>* paramList = new vector<ParamNode*>();
		paramList->push_back($1);
		$$ = paramList;
	}
	| parameterList ',' parameterDeclaration {
		$$ = $1;
		$$->push_back($3);
	}
	;

parameterDeclaration
	: declarationSpecifiers directDeclarator {
		ParamNode* node = new ParamNode();
		node->type = $1;
		node->id = $2->id;
		$$ = node;
	}
	| declarationSpecifiers directAbstractDeclarator {
		ParamNode* node = new ParamNode();
		node->type = $1;
		$$ = node;
	}
	| declarationSpecifiers {
		ParamNode* node = new ParamNode();
        node->type = $1;
        $$ = node;
	}
	;

identifierList
    : IDENTIFIER {
        IdentifierNode* node = new IdentifierNode();
        node->id = *$1;
        vector<ExprNode*>* idList = new vector<ExprNode*>(); 
        idList->push_back(node);
        $$ = idList;
    }
    | identifierList ',' IDENTIFIER {
        $$ = $1;
        IdentifierNode* node = new IdentifierNode();
        node->id = *$3;
        $$->push_back(node);
    }
    ;

typeName
    : specifier_qualifierList {
        $$ = $1;
    }
    | specifier_qualifierList directAbstractDeclarator {
		$$ = $1;
        $$->abstractDecl = $2;
    }
    ;

directAbstractDeclarator
    : '(' directAbstractDeclarator ')' {
        $$ = $2;
    }
    | '[' ']' {
        Declarator* node = new Declarator();
        node->arrayFlag = true;
        $$ = node;
    }
    | '[' conditionalExpression ']' {
        Declarator* node = new Declarator();
        node->arrayFlag = true;
        node->arraySize = $2;
        $$ = node;
    }
    | directAbstractDeclarator '[' ']' {
        $$ = $1;
        $$->arrayFlag = true;
    }
    | directAbstractDeclarator '[' conditionalExpression ']' {
        $$ = $1;
        $$->arrayFlag = true;
        $$->arraySize = $3;
    }
    | '(' ')' {
        Declarator* node = new Declarator();
        node->funcFlag = true;
        $$ = node;
    }
    | '(' parameterList ')' {
        Declarator* node = new Declarator();
        node->funcFlag = true;
        node->params = *$2;
        $$ = node;
    }
    | directAbstractDeclarator '(' ')' {
        $$ = $1;
        $$->funcFlag = true;
    }
    | directAbstractDeclarator '(' parameterList ')' {
        $$ = $1;
        $$->funcFlag = true;
        $$->params = *$3;
    }
    ;

initializer
    : assignmentExpression {
        Initializer* node = new Initializer();
        node->expr = $1;
        $$ = node;
    }
    | '{' initializerList '}' {
        Initializer* node = new Initializer();
        node->initializerList = *$2;
        $$ = node;
    }
    | '{' initializerList ',' '}' {
        Initializer* node = new Initializer();
        node->initializerList = *$2;
        $$ = node;
    }
    ;

initializerList
	: initializer {
		vector<Initializer*>* initVec = new vector<Initializer*>();
		initVec->push_back($1);
		$$ = initVec;
	}
	| initializerList ',' initializer {
		$$ = $1;
		$$->push_back($3);
	}
	;

statement
	: compoundStatement {
		$$ = $1;
	}
	| expressionStatement {
		$$ = $1;
	}
	| selectionStatement {
		$$ = $1;
	}
	| iterationStatement {
		$$ = $1;
	}
	| jumpStatement {
		$$ = $1;
	}
	;

compoundStatement
    : '{' '}' {
        $$ = new CmpdStmtNode();
    }
    | '{' statementList '}' {
        $$ = new CmpdStmtNode();
        ((CmpdStmtNode*)$$)->statements = *$2; 
    }
    | '{' declarationList '}' {
        $$ = new CmpdStmtNode();
        ((CmpdStmtNode*)$$)->declarations = *$2;
    }
    | '{' declarationList statementList '}' {
        $$ = new CmpdStmtNode();
        ((CmpdStmtNode*)$$)->declarations = *$2;
        ((CmpdStmtNode*)$$)->statements = *$3;
    }
    ;

declarationList
    : declaration {
        vector<DeclNode*>* vec = new vector<DeclNode*>();
        vec->push_back($1);
        $$ = vec;
    }
    | declarationList declaration {
        $$ = $1;
        $$->push_back($2);
    }
    ;

statementList
	: statement {
		vector<StmtNode*>* vec = new vector<StmtNode*>();
		vec->push_back($1);
		$$ = vec;
	}
	| statementList statement {
		$$ = $1;
		$$->push_back($2);
	}
	;

expressionStatement
	: ';' {
		ExprStmtNode* node = new ExprStmtNode();
		$$ = (StmtNode*)node;
	}
	| expression ';' {
		ExprStmtNode* node = new ExprStmtNode();
		node->expr = $1;
		$$ = (StmtNode*)node;
	}
	;

selectionStatement
    : IF '(' expression ')' statement %prec LOWER_THAN_ELSE {
		IfNode* node = new IfNode();
		node->condition = $3;
		node->thenBranch = $5;
		$$ = (StmtNode*)node;
	}
    | IF '(' expression ')' statement ELSE statement {
		IfNode* node = new IfNode();
		node->condition = $3;
		node->thenBranch = $5;
		node->elseBranch = $7;
		$$ = (StmtNode*)node;
	}
    ;

iterationStatement
	: WHILE '(' expression ')' statement {
		WhileNode* node = new WhileNode();
		node->condition = $3;
		node->body = $5;
		$$ = (StmtNode*)node;
	}
	| FOR '(' expressionStatement expressionStatement ')' statement {
		ForNode* node = new ForNode();
            
        node->init = ((ExprStmtNode*)$3)->expr;
        node->condition = ((ExprStmtNode*)$4)->expr;
        node->body = (CmpdStmtNode*)$6;
        $$ = (StmtNode*)node;
	}
	| FOR '(' expressionStatement expressionStatement expression ')' statement {
		ForNode* node = new ForNode();
        node->init = ((ExprStmtNode*)$3)->expr;
		node->condition = ((ExprStmtNode*)$4)->expr;
        node->increment = $5;
        node->body = (CmpdStmtNode*)$7;
        $$ = (StmtNode*)node;
	}
	;

jumpStatement
	: CONTINUE ';' {
		ContinueNode* node = new ContinueNode();
		$$ = (StmtNode*)node;
	}
	| BREAK ';' {
		BreakNode* node = new BreakNode();
		$$ = (StmtNode*)node;
	}
	| RETURN ';' {
		ReturnNode* node = new ReturnNode();
		$$ = (StmtNode*)node;
	}
	| RETURN expression ';' {
		ReturnNode* node = new ReturnNode();
		node->expr = $2;
		$$ = (StmtNode*)node;
	}
	;

globalDeclaration
    : function_definition {
        $$ = (ASTNode*)$1;
    }
    | declaration {
        $$ = (ASTNode*)$1;
    }
    | strategyDefinition {
        $$ = (ASTNode*)$1;
    }
    ;

function_definition
	: FUN IDENTIFIER '(' ARROW typeSpecifier ')' compoundStatement {
		FuncNode* node = new FuncNode();
		node->name = *$2;
		node->returnType = $5;
		node->body = (CmpdStmtNode*)$7;
		$$ = node;
	}
	| FUN IDENTIFIER '(' parameterList ARROW typeSpecifier ')' compoundStatement {
		FuncNode* node = new FuncNode();
		node->name = *$2;
		node->returnType = $6;
		node->params = *$4;
		node->body = (CmpdStmtNode*)$8;
		$$ = node;
	}
	;

%%


void yyerror(const char *s) {
    fprintf(stderr, "\nError: %s at line %d, column %d, near '%s'\n", s, yylineno, col - 1, yytext);
}

int main() {
    yyin = fopen("./input.txt", "r");
    if (!yyin) {
        perror("File not found\n");
        return 1;
    }

    if (yyparse() == 0){
		cout << "parse successful" << endl;
		progRoot->printNode();
	}
    else
        cout << "Parse Failed" << endl;
    

    fclose(yyin);
    return 0;
}
