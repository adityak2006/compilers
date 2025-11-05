%code requires{
    #include "ast.h"
}

%{
#include <iostream>
#include <string>
#include <fstream>
#include "ast.h"
#include "symbol_table.h"
#include "symbol_table_printer.h"

using namespace std;

extern FILE *yyin;
extern int col;
int yyparse(void);
int yylex();
void yyerror(const char* s);
extern int yylineno;
extern char *yytext;

ProgramNode* progRoot;
SymbolTable symtab;


static void populateArrayFromInitializer(ArraySym* arr, Initializer* initNode) {
    if (!arr || !initNode) return;

    if (initNode->initializerList.empty()) {
        if (initNode->expr) {
            std::cerr << "Warning: line " << yylineno << ": Cannot initialize array '" << arr->name << "' with a non-list expression. Only '{...}' is supported.\n";
        }
        return;
    }

    int init_list_idx = 0;

    for (auto& elem_sym_ptr : arr->elements) {
        Symbol* elem_sym = elem_sym_ptr.get();
        if (!elem_sym) continue;

        if (init_list_idx >= initNode->initializerList.size()) {
            return; 
        }

        Initializer* current_init = initNode->initializerList[init_list_idx];
        if (!current_init) continue;

        if (auto nestedArr = dynamic_cast<ArraySym*>(elem_sym)) {
            if (current_init->expr) {
                std::cerr << "Warning: line " << yylineno << ": brace-enclosed initializer expected for sub-array of '" << arr->name << "'.\n";
            } else {
                populateArrayFromInitializer(nestedArr, current_init);
            }
            init_list_idx++;
        } 
        else if (current_init->expr) {
            if (auto lint = dynamic_cast<LiteralIntNode*>(current_init->expr)) {
                if (auto is = dynamic_cast<IntSym*>(elem_sym)) is->value = lint->value;
                else if (auto fs = dynamic_cast<FloatSym*>(elem_sym)) fs->value = (double)lint->value;
                else if (auto bs = dynamic_cast<BoolSym*>(elem_sym)) bs->value = (lint->value != 0);
            } else if (auto lflt = dynamic_cast<LiteralFloatNode*>(current_init->expr)) {
                if (auto fs = dynamic_cast<FloatSym*>(elem_sym)) fs->value = lflt->value;
                else if (auto is = dynamic_cast<IntSym*>(elem_sym)) is->value = (int)lflt->value; // note: truncation
            } else if (auto lbool = dynamic_cast<LiteralBoolNode*>(current_init->expr)) {
                if (auto bs = dynamic_cast<BoolSym*>(elem_sym)) bs->value = lbool->value;
            }
            
            init_list_idx++; // Consume this initializer (which was an expression)
        } else {
            std::cerr << "Warning: line " << yylineno << ": expected expression for scalar element of '" << arr->name << "', got list.\n";
            init_list_idx++;
        }
    }
}

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

    std::vector<ASTNode*>* nodeList;


}

%token STRATEGY SYMBOL TIMEFRAME P_SIZE INDICATORS REGIMES 
%token FUN SCOPE ARROW
%token ENTRYLONG ENTRYSHORT EXITLONG EXITSHORT
%token OPEN CLOSE HIGH LOW VOLUME
%token POSITION_SHARES ENTRY_PRICE DAYS_IN_POSITION PORTFOLIO_VALUE CASH_AVAILABLE
%token SMA EMA RSI BB ATR SDV MAX MIN SUM MEDIAN AVG ABS CORRELATION SLOPE RSQUARED
%token GROUP 

%token FOR WHILE IF ELSE CONTINUE BREAK RETURN

%token INT FLOAT BOOL VOID RGM CONST TIMESERIES

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
%type <expr> primaryExpression postfixExpression expression unaryExpression multiplicativeExpression additiveExpression
%type <expr> shiftExpression relationalExpression equalityExpression andExpression exclusiveOrExpression inclusiveOrExpression
%type <expr> logicalAndExpression logicalOrExpression conditionalExpression assignmentExpression timeseries timeseriesExpression
%type <exprVec> argumentExpressionList identifierList

%type <param> parameterDeclaration
%type <paramVec> parameterList

/* %type <stmtVec> statementList */
%type <stmt> compoundStatement statement jumpStatement iterationStatement selectionStatement expressionStatement indiRegCompoundStatement

%type <func> function_definition
%type <decl> declaration
/* %type <declVec> declarationList */
%type <type> declarationSpecifiers typeSpecifier

%type <init> initializer
%type <initList> initializerList
%type <initDecl> initDeclarator
%type <initDeclVec> initDeclaratorList

%type <declarator> directDeclarator

%type <group> groupSpecifier
%type <groupDeclaration> groupDeclaration
%type <groupDeclList> groupDeclarationList
%type <groupDeclarator> groupDeclarator
%type <groupDeclaratorList> groupDeclaratorList

%type <node> blockItem
%type <nodeList> blockItemList


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
    : STRATEGY IDENTIFIER 
        {
            std::string sname = *$2;
            int zeros[3] = {0,0,0};
            
            if (!symtab.currentScope->define(std::make_unique<StrategySym>(sname, sname, zeros, yylineno, col-1))) {
                std::cerr << "Error: redeclaration of strategy '" << sname << "' at line " << yylineno << "\n";
            }
            symtab.enterScope();
        }
      '{' strategyBody '}' 
        {
            symtab.exitScope();

            $$ = new StrategyNode();
            $$->id = *$2;
            if ($5) {
                $$->declarations = $5->declarations;
                $$->indicators = $5->indicators;
                $$->regimes = $5->regimes;
                $$->signals = $5->signals;
            }


            Symbol* sym = symtab.currentScope->lookup(*$2);
            if (sym) {
                if (auto ss = dynamic_cast<StrategySym*>(sym)) {
                    if ($5 && $5->declarations) {
                        StratDeclNode* sd = $5->declarations;
                        if (sd && sd->timeframe.size() >= 3) {
                            for (size_t i = 0; i < 3; ++i) ss->timeframe[i] = sd->timeframe[i];
                        }
                    }
                }
            }

            // Optionally attach parsed decl info back to the StrategySym (lookup in enclosing scope)
            
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

indiRegCompoundStatement
    : '{' {
        ;
    } blockItemList '}' {
        CmpdStmtNode* node = new CmpdStmtNode();
        for (ASTNode* item : *$3) {
            if (!item) continue;
            if (item->nodeType == ASTNodeType::DeclNode) {
                node->declarations.push_back((DeclNode*)item);
            }
            else {
                node->statements.push_back((StmtNode*)item);
            }
        }
        delete $3;
        $$ = node;
    }
    ;

indicatorSection
    : {$$ = NULL;}
    | INDICATORS indiRegCompoundStatement {
        $$ = new IndicatorNode();
        $$->body = (CmpdStmtNode*)$2;
    }
    ;

regimeSection
    : {$$ = NULL;}
    | REGIMES indiRegCompoundStatement {
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
    | unaryOperator unaryExpression {
        UnaryExprNode* node = new UnaryExprNode();
        node->operand = (ExprNode*)$2;
        if($1=='+'){
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
    : '+' {
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

multiplicativeExpression
    : unaryExpression {
        $$ = $1;
    }
    | multiplicativeExpression '*' unaryExpression {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = $1;
        node->rightOperand = $3;
        node->op = "*";
        $$ = node;
    }
    | multiplicativeExpression '/' unaryExpression {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = $1;
        node->rightOperand = $3;
        node->op = "/";
        $$ = node;

    }
    | multiplicativeExpression '%' unaryExpression {
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
        $$ = node;
    }
    | declarationSpecifiers initDeclaratorList ';' {
    DeclNode* node = new DeclNode();
    node->type = $1;
    node->decls = *$2;
    $$ = node;

    for (InitDeclarator* id : node->decls) {
        if (!id || !id->declarator) continue;
        Declarator* d = id->declarator;
        std::string name = d->id;
        DataTypes dt = node->type ? node->type->type : DataTypes::INT_TYPE;
        bool isConst = node->type ? node->type->constFlag : false;

        if (d->arrayFlag) 
        {
            std::vector<int> dims;
            bool all_dims_valid = true;

            for (ExprNode* sizeExpr : d->arraySizes) {
                if (auto lit = dynamic_cast<LiteralIntNode*>(sizeExpr)) {
                    if (lit->value > 0) {
                        dims.push_back(lit->value);
                    } else {
                        std::cerr << "Error: line " << yylineno << ": array dimension for '" << name << "' must be a positive integer.\n";
                        all_dims_valid = false;
                        break;
                    }
                } else {
                    std::cerr << "Error: line " << yylineno << ": array dimension for '" << name << "' is not a constant integer expression.\n";
                    all_dims_valid = false;
                    break;
                }
            }

            if (all_dims_valid) {
                DataTypes baseType = dt; 
                bool isConstArr = isConst;

                auto arr = std::make_unique<ArraySym>(name, dims, baseType, isConstArr, yylineno, col - 1);

                if (id->initializer) {
                    populateArrayFromInitializer(arr.get(), id->initializer);
                }

                if (!symtab.currentScope->define(std::move(arr))) {
                    std::cerr << "Error: redeclaration of array '" << name
                              << "' at line " << yylineno << "\n";
                }
            }
            continue;
        }


        bool hadLiteralInit = false;
        int intInit = 0;
        double floatInit = 0.0;
        bool boolInit = false;
        std::string stringInit;

        if (id->initializer && id->initializer->expr) {
            ASTNode* initExpr = id->initializer->expr;
            // integer literal (handles int literals, plus 'true'/'false' from the lexer)
            if (auto lint = dynamic_cast<LiteralIntNode*>(initExpr)) {
                hadLiteralInit = true;
                intInit = lint->value;
                if (dt == DataTypes::BOOL_TYPE) {
                    boolInit = (lint->value != 0);
                }
            }
            // float literal
            else if (auto lflt = dynamic_cast<LiteralFloatNode*>(initExpr)) {
                hadLiteralInit = true;
                floatInit = lflt->value;
            }
            // bool literal
            else if (auto lbool = dynamic_cast<LiteralBoolNode*>(initExpr)) {
                hadLiteralInit = true;
                boolInit = lbool->value;
            }
            else {
                std::cerr << "Note: initializer for '" << name << "' at line " << yylineno
                          << " is not a literal; storing default value for now\n";
            }
        }

        switch (dt) {
            case DataTypes::INT_TYPE: {
                int val = hadLiteralInit ? intInit : 0;
                if (!symtab.currentScope->define(std::make_unique<IntSym>(name, val, isConst, yylineno, col-1))) {
                    std::cerr << "Error: redeclaration of '" << name << "' at line " << yylineno << "\n";
                }
                break;
            }
            case DataTypes::FLOAT_TYPE: {
                double val = hadLiteralInit ? floatInit : 0.0;
                // if initializer was an int literal but variable is float, use int->float conversion
                if (!hadLiteralInit && id->initializer && id->initializer->expr) {
                    if (auto lint = dynamic_cast<LiteralIntNode*>(id->initializer->expr)) {
                        val = static_cast<double>(lint->value);
                        hadLiteralInit = true;
                    }
                }
                if (!symtab.currentScope->define(std::make_unique<FloatSym>(name, val, isConst, yylineno, col-1))) {
                    std::cerr << "Error: redeclaration of '" << name << "' at line " << yylineno << "\n";
                }
                break;
            }
            case DataTypes::BOOL_TYPE: {
                bool val = hadLiteralInit ? boolInit : false;
                if (!symtab.currentScope->define(std::make_unique<BoolSym>(name, val, isConst, yylineno, col-1))) {
                    std::cerr << "Error: redeclaration of '" << name << "' at line " << yylineno << "\n";
                }
                break;
            }
            case DataTypes::TIMESERIES_TYPE: {
                size_t cap = 256;
                if (hadLiteralInit && intInit > 0) cap = static_cast<size_t>(intInit);
                if (!symtab.currentScope->define(std::make_unique<TimeseriesSym>(name, cap, yylineno, col-1))) {
                    std::cerr << "Error: redeclaration of '" << name << "' at line " << yylineno << "\n";
                }
                break;
            }
            case DataTypes::GROUP_TYPE: {
                if (!symtab.currentScope->define(std::make_unique<GroupSym>(name, yylineno, col-1))) {
                    std::cerr << "Error: redeclaration of group '" << name << "' at line " << yylineno << "\n";
                }
                break;
            }
            case DataTypes::RGM_TYPE: {
                if (!symtab.currentScope->define(std::make_unique<RegimeSym>(name, yylineno, col-1))) {
                    std::cerr << "Error: redeclaration of regime '" << name << "' at line " << yylineno << "\n";
                }
                break;
            }
            default: {
                SymKind kindToUse = SymKind::Array;

                if (!symtab.currentScope->define(std::make_unique<Symbol>(name, kindToUse, yylineno, col-1))) {
                    std::cerr << "Error: redeclaration of '" << name << "' at line " << yylineno << "\n";
                }
                break;
            }
        }
    }
}


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

        // Create GroupSym and populate member map
        auto groupSym = std::make_unique<GroupSym>(node->id, yylineno, col-1);

        for (GroupDeclaration* gdecl : node->members) {
            if (!gdecl) continue;
            TypeNode* t = gdecl->type;
            DataTypes dt = t ? t->type : DataTypes::INT_TYPE;
            bool isConst = t ? t->constFlag : false;

            for (GroupDeclarator* gd : gdecl->declarators) {
                if (!gd) continue;
                std::string memberName;
                if (gd->declarator && !gd->declarator->id.empty()) {
                    memberName = gd->declarator->id;
                } else {
                    continue; // skip anonymous
                }

                std::unique_ptr<Symbol> memSym;
                switch (dt) {
                    case DataTypes::INT_TYPE:
                        memSym = std::make_unique<IntSym>(memberName, 0, isConst, yylineno, col-1);
                        break;
                    case DataTypes::FLOAT_TYPE:
                        memSym = std::make_unique<FloatSym>(memberName, 0.0, isConst, yylineno, col-1);
                        break;
                    case DataTypes::BOOL_TYPE:
                        memSym = std::make_unique<BoolSym>(memberName, false, isConst, yylineno, col-1);
                        break;
                    case DataTypes::TIMESERIES_TYPE:
                        memSym = std::make_unique<TimeseriesSym>(memberName, 256, yylineno, col-1);
                        break;
                    case DataTypes::GROUP_TYPE:
                        memSym = std::make_unique<Symbol>(memberName, SymKind::Group, yylineno, col-1);
                        break;
                    default:
                        memSym = std::make_unique<IntSym>(memberName, 0, isConst, yylineno, col-1);
                        break;
                }

                groupSym->members.emplace(memberName, std::move(memSym));
            }
        }

        // define group type in current scope
        if (!symtab.currentScope->define(std::move(groupSym))) {
            std::cerr << "Error: redeclaration of group type '" << node->id
                      << "' at line " << yylineno << "\n";
        }
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
    : declarationSpecifiers groupDeclaratorList ';' {
        GroupDeclaration* node = new GroupDeclaration();
        node->type= $1;
        node->declarators = *$2;
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
	;

directDeclarator
    : IDENTIFIER {
        Declarator* node = new Declarator();
        node->id = *$1;
        $$ = node;
    }
    | directDeclarator '[' conditionalExpression ']' {
        $$ = $1;
        $$->arrayFlag = true;
        $$->arraySizes.push_back($3);
    }
    | directDeclarator '(' parameterList ')' {
        $$ = $1;
        $$->funcFlag = true;
        $$->params = *$3;
    }
    | directDeclarator '(' identifierList ')' {
        $$ = $1;
        $$->funcFlag = true;
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
        node->declarator = $2;
        $$ = node;
    }
    | declarationSpecifiers {
        ParamNode* node = new ParamNode();
        node->type = $1;
        node->declarator = nullptr;
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

blockItem
    : declaration {
        $$ = (ASTNode*)$1;
    }
    | statement {
        $$ = (ASTNode*)$1;
    }
    ;


blockItemList
    : /* empty */ {
        $$ = new std::vector<ASTNode*>();
    }
    | blockItemList blockItem {
        $$ = $1;
        $$->push_back($2);
    }
    ;

compoundStatement
    : '{' {
        symtab.enterScope();
    } blockItemList '}' {
        CmpdStmtNode* node = new CmpdStmtNode();
        for (ASTNode* item : *$3) {
            if (!item) continue;
            if (item->nodeType == ASTNodeType::DeclNode) {
                node->declarations.push_back((DeclNode*)item);
            }
            else {
                node->statements.push_back((StmtNode*)item);
            }
        }
        delete $3;
        $$ = node;
        symtab.exitScope();
    }
    ;




/* declarationList
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
    ; */

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
    : FUN IDENTIFIER '(' ARROW typeSpecifier ')' {
        std::string fname = *$2;
         auto funcSym = std::make_unique<FunctionSym>(fname, yylineno, col-1);
        TypeNode* retType = $5;
        switch (retType->type) {
            case DataTypes::INT_TYPE:
                funcSym->returnType = std::make_unique<IntSym>("<ret>", 0, false, yylineno, col-1);
                break;
            case DataTypes::FLOAT_TYPE:
                funcSym->returnType = std::make_unique<FloatSym>("<ret>", 0.0, false, yylineno, col-1);
                break;
            case DataTypes::BOOL_TYPE:
                funcSym->returnType = std::make_unique<BoolSym>("<ret>", false, false, yylineno, col-1);
                break;
            case DataTypes::TIMESERIES_TYPE:
                funcSym->returnType = std::make_unique<TimeseriesSym>("<ret>", 256, yylineno, col-1);
                break;
            default:
                funcSym->returnType = std::make_unique<Symbol>("<ret>", SymKind::Array, yylineno, col-1);
                break;
        }

        if (!symtab.currentScope->define(std::move(funcSym))) {
            std::cerr << "Error: redeclaration of function '" << fname << "' at line " << yylineno << "\n";
        }

        
        symtab.enterScope();
    } compoundStatement {
        FuncNode* node = new FuncNode();
        node->name = *$2;
        node->returnType = $5;
        node->body = (CmpdStmtNode*)$8;
        $$ = node;

        symtab.exitScope();
    }
    | FUN IDENTIFIER '(' parameterList ARROW typeSpecifier ')' {
        std::string fname = *$2;

        auto funcSym = std::make_unique<FunctionSym>(fname, yylineno, col-1);

        TypeNode* retType = $6;
        switch (retType->type) {
            case DataTypes::INT_TYPE:
                funcSym->returnType = std::make_unique<IntSym>("<ret>", 0, false, yylineno, col-1);
                break;
            case DataTypes::FLOAT_TYPE:
                funcSym->returnType = std::make_unique<FloatSym>("<ret>", 0.0, false, yylineno, col-1);
                break;
            case DataTypes::BOOL_TYPE:
                funcSym->returnType = std::make_unique<BoolSym>("<ret>", false, false, yylineno, col-1);
                break;
            case DataTypes::TIMESERIES_TYPE:
                funcSym->returnType = std::make_unique<TimeseriesSym>("<ret>", 256, yylineno, col-1);
                break;
            default:
                funcSym->returnType = std::make_unique<Symbol>("<ret>", SymKind::Array, yylineno, col-1);
                break;
        }

        for (ParamNode* p : *$4) {
            if (!p || !p->type || !p->declarator) continue;
            
            std::string pname = p->declarator->id;
            DataTypes pdt = p->type->type;
            bool isConst = p->type->constFlag;

            if (p->declarator->arrayFlag) {
                std::vector<int> dims;
                for (ExprNode* sizeExpr : p->declarator->arraySizes) {
                    if (auto lit = dynamic_cast<LiteralIntNode*>(sizeExpr)) {
                        dims.push_back(lit->value);
                    } else {
                        dims.push_back(0);
                    }
                }
                funcSym->parameters.push_back(std::make_unique<ArraySym>(pname, dims, pdt, isConst, yylineno, col-1));
            } else {
                switch (pdt) {
                    case DataTypes::INT_TYPE:
                        funcSym->parameters.push_back(std::make_unique<IntSym>(pname, 0, false, yylineno, col-1));
                        break;
                    case DataTypes::FLOAT_TYPE:
                        funcSym->parameters.push_back(std::make_unique<FloatSym>(pname, 0.0, false, yylineno, col-1));
                        break;
                    case DataTypes::BOOL_TYPE:
                        funcSym->parameters.push_back(std::make_unique<BoolSym>(pname, false, false, yylineno, col-1));
                        break;
                    case DataTypes::TIMESERIES_TYPE:
                        funcSym->parameters.push_back(std::make_unique<TimeseriesSym>(pname, 256, yylineno, col-1));
                        break;
                    default:
                        funcSym->parameters.push_back(std::make_unique<Symbol>(pname, SymKind::Array, yylineno, col-1));
                        break;
                }
            }
        }

        if (!symtab.currentScope->define(std::move(funcSym))) {
            std::cerr << "Error: redeclaration of function '" << fname << "' at line " << yylineno << "\n";
        }

        symtab.enterScope();

        for (ParamNode* p : *$4) {
            if (!p || !p->type || !p->declarator) continue;

            std::string pname = p->declarator->id;
            DataTypes pdt = p->type->type;
            bool isConst = p->type->constFlag;

            if (p->declarator->arrayFlag) {
                std::vector<int> dims;
                for (ExprNode* sizeExpr : p->declarator->arraySizes) {
                    if (auto lit = dynamic_cast<LiteralIntNode*>(sizeExpr)) {
                        dims.push_back(lit->value);
                    } else {
                        dims.push_back(0);
                    }
                }
                if (!symtab.currentScope->define(std::make_unique<ArraySym>(pname, dims, pdt, isConst, yylineno, col-1))) {
                    std::cerr << "Error: redeclaration of param '" << pname << "' at line " << yylineno << "\n";
                }
            } 
            else {
            switch (pdt) {
                    case DataTypes::INT_TYPE:
                        if (!symtab.currentScope->define(std::make_unique<IntSym>(pname, 0, false, yylineno, col-1)))
                            std::cerr << "Error: redeclaration of param '" << pname << "' at line " << yylineno << "\n";
                            break;
                    case DataTypes::FLOAT_TYPE:
                        if (!symtab.currentScope->define(std::make_unique<FloatSym>(pname, 0.0, false, yylineno, col-1)))
                            std::cerr << "Error: redeclaration of param '" << pname << "' at line " << yylineno << "\n";
                            break;
                    case DataTypes::BOOL_TYPE:
                        if (!symtab.currentScope->define(std::make_unique<BoolSym>(pname, false, false, yylineno, col-1)))
                            std::cerr << "Error: redeclaration of param '" << pname << "' at line " << yylineno << "\n";
                            break;
                    case DataTypes::TIMESERIES_TYPE:
                        if (!symtab.currentScope->define(std::make_unique<TimeseriesSym>(pname, 256, yylineno, col-1)))
                            std::cerr << "Error: redeclaration of param '" << pname << "' at line " << yylineno << "\n";
                            break;
                    default:
                        if (!symtab.currentScope->define(std::make_unique<Symbol>(pname, SymKind::Array, yylineno, col-1)))
                            std::cerr << "Error: redeclaration of param '" << pname << "' at line " << yylineno << "\n";
                        break;
                }
            }
        }

    } compoundStatement {
        FuncNode* node = new FuncNode();
        node->name = *$2;
        node->returnType = $6;
        node->params = *$4;
        node->body = (CmpdStmtNode*)$9;
        $$ = node;

        symtab.exitScope();
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
        if (progRoot) progRoot->printNode();
        else cout << "Empty program!" << endl;
        printSymbolTable(symtab, std::cout);
    }
    else
        cout << "Parse Failed" << endl;
    

    fclose(yyin);
    return 0;
}
