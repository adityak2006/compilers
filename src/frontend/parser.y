%code requires{
	#include "ast.h"
}

%{
#include <iostream>
#include <string>
#include "ast.h"

extern FILE *yyin;
extern int col;
int yyparse(void);
int yylex();
void yyerror(const char* s);
extern int yylineno;
extern char *yytext;

ast::ProgramNode* progRoot;
%}


%union {
	ast::ProgramNode* prog;
	ast::ASTNode* node;
	ast::ExprNode* expr;
	ast::StmtNode* stmt;
	ast::FuncNode* func;
	ast::DeclNode* decl;
	ast::ParamNode* param;
	ast::Declarator* declarator;
	ast::CmpdStmtNode* cmpdStmt;
	ast::TypeNode* type;
	ast::InitDeclarator* initDecl;
	ast::GroupNode* group;
	ast::StrategyNode* strategy;
	ast::StratDeclNode* strategyDecl;
	ast::IndicatorNode* indicator;
	ast::RegimeNode* regime;
	ast::SignalFuncNode* signalFunc;
	ast::GroupDeclaration* groupDeclaration;
	ast::GroupDeclarator* groupDeclarator;
	ast::SignalFuncListNode* sigFuncList;
    int intVal;
    float floatVal;
    std::string* id;
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

%type <prog> translation_unit
%type <strategy> strategy_definition strategy_body
%type <strategyDecl> strategy_declarations
%type <indicator> indicator_section
%type <regime> regime_section
%type <signalFunc> signal_function
%type <sigFuncList> signal_function_list
%type <cmpdStmt> compound_statement
%type <node> external_declaration

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start translation_unit

%%

strategy_definition
    : STRATEGY IDENTIFIER '{' strategy_body '}' {
		$$ = new ast::StrategyNode();
		$$->id = *$2;
		if($4){
			$$->declarations = $4->declarations;
			$$->indicators = $4->indicators;
            $$->regimes = $4->regimes;
            $$->signals = $4->signals;
		}
	}
    ;

strategy_body
    : strategy_declarations indicator_section regime_section signal_function_list {
		$$ = new ast::StrategyNode();
		$$->declarations = $1;
        $$->indicators = $2;
        $$->regimes = $3;
        $$->signals = $4;
	}
    ;

strategy_declarations
    : SYMBOL '=' STRINGLIT ';' TIMEFRAME '=' '{'INTLIT ',' INTLIT',' INTLIT '}' ';' P_SIZE '=' INTLIT ';' {
		$$ = new ast::StratDeclNode();
		$$->symbol = *$3;
		$$->timeframe.push_back($8);
        $$->timeframe.push_back($10);
        $$->timeframe.push_back($12);
        $$->positionSize = $17;
	}
    ;

indicator_section
    : {$$ = NULL;}
	| INDICATORS compound_statement {
		$$ = new ast::IndicatorNode();
        $$->body = $2;
	}
    ;

regime_section
    : {$$ = NULL;}
	| REGIMES compound_statement {
		$$ = new ast::RegimeNode();
        $$->body = $2;
	}
    ;

signal_function_list
    :  { $$ = new ast::SignalFuncListNode(); }
    | signal_function_list signal_function {
        $$ = $1;
        if ($2) $$->signals.push_back($2);
    }
    ;

signal_function
    : IDENTIFIER SCOPE ENTRYLONG compound_statement {
        $$ = new ast::SignalFuncNode();
        $$->regimeId = *$1;
        $$->signalType = ast::SIGNAL_ENTRY_LONG;
        $$->body = $4;
    }
    | IDENTIFIER SCOPE ENTRYSHORT compound_statement {
        $$ = new ast::SignalFuncNode();
        $$->regimeId = *$1;
        $$->signalType = ast::SIGNAL_ENTRY_SHORT;
        $$->body = $4;
    }
    | IDENTIFIER SCOPE EXITLONG compound_statement {
        $$ = new ast::SignalFuncNode();
        $$->regimeId = *$1;
        $$->signalType = ast::SIGNAL_EXIT_LONG;
        $$->body = $4;
    }
    | IDENTIFIER SCOPE EXITSHORT compound_statement {
        $$ = new ast::SignalFuncNode();
        $$->regimeId = *$1;
        $$->signalType = ast::SIGNAL_EXIT_SHORT;
        $$->body = $4;
    }
    | ENTRYLONG compound_statement {
        $$ = new ast::SignalFuncNode();
        $$->signalType = ast::SIGNAL_ENTRY_LONG;
        $$->body = $2;
    }
    | ENTRYSHORT compound_statement {
        $$ = new ast::SignalFuncNode();
        $$->signalType = ast::SIGNAL_ENTRY_SHORT;
        $$->body = $2;
    }
    | EXITLONG compound_statement {
        $$ = new ast::SignalFuncNode();
        $$->signalType = ast::SIGNAL_EXIT_LONG;
        $$->body = $2;
    }
    | EXITSHORT compound_statement {
        $$ = new ast::SignalFuncNode();
        $$->signalType = ast::SIGNAL_EXIT_SHORT;
        $$->body = $2;
    }
    ;

primary_expression
    : IDENTIFIER 
    | INTLIT 
    | FLOATLIT 
    | STRINGLIT 
    | '(' expression ')' 
    | timeseries_expression
    ;

timeseries
    : CLOSE
    | OPEN
    | HIGH
    | LOW
    | VOLUME
    | SMA '(' timeseries ',' INTLIT ')'
    | EMA '(' timeseries ',' INTLIT ')'
    | RSI '(' timeseries ',' INTLIT ')'
    | BB '(' timeseries ',' INTLIT ',' FLOATLIT ')'
    | ATR '(' timeseries ',' timeseries ',' timeseries ',' INTLIT ')'
    | SDV '(' timeseries ',' INTLIT ')'
    | MAX '(' timeseries ',' INTLIT ')'
    | MIN '(' timeseries ',' INTLIT ')'
    | SUM '(' timeseries ',' INTLIT ')'
    | MEDIAN '(' timeseries ',' INTLIT ')'
    | AVG '(' timeseries ',' INTLIT ')'
    | ABS '(' timeseries ',' INTLIT ')'
    | CORRELATION '(' timeseries ',' timeseries ',' INTLIT ')'
    | SLOPE '(' timeseries ',' INTLIT ')'
    | RSQUARED '(' timeseries ',' INTLIT ')'
    ;

timeseries_expression
	: timeseries
    | SMA '(' IDENTIFIER ',' INTLIT ')'
    | EMA '(' IDENTIFIER ',' INTLIT ')'
    | RSI '(' IDENTIFIER ',' INTLIT ')'
    | BB '(' IDENTIFIER ',' INTLIT ',' FLOATLIT ')'
    | ATR '(' IDENTIFIER ',' IDENTIFIER ',' IDENTIFIER ',' INTLIT ')'
    | SDV '(' IDENTIFIER ',' INTLIT ')'
    | MAX '(' IDENTIFIER ',' INTLIT ')'
    | MIN '(' IDENTIFIER ',' INTLIT ')'
    | SUM '(' IDENTIFIER ',' INTLIT ')'
    | MEDIAN '(' IDENTIFIER ',' INTLIT ')'
    | AVG '(' IDENTIFIER ',' INTLIT ')'
    | ABS '(' IDENTIFIER ',' INTLIT ')'
    | CORRELATION '(' IDENTIFIER ',' IDENTIFIER ',' INTLIT ')'
    | SLOPE '(' IDENTIFIER ',' INTLIT ')'
    | RSQUARED '(' IDENTIFIER ',' INTLIT ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| PORTFOLIO_VALUE
	| CASH_AVAILABLE
	| POSITION_SHARES
	| ENTRY_PRICE
	| DAYS_IN_POSITION
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| unary_operator cast_expression
	;

unary_operator
	: REF
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LEQ shift_expression
	| relational_expression GEQ shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ relational_expression
	| equality_expression NEQ relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression '=' assignment_expression
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: type_specifier
	| CONST type_specifier
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: direct_declarator
	| direct_declarator '=' initializer
	;


type_specifier
	: VOID
	| INT
	| FLOAT
    | BOOL
    | STRING
	| RGM
	| TIMESERIES
	| group_specifier
	;

group_specifier
	: GROUP IDENTIFIER '{' group_declaration_list '}'
	| GROUP '{' group_declaration_list '}'
	| GROUP IDENTIFIER
	;

group_declaration_list
	: group_declaration
	| group_declaration_list group_declaration
	;

group_declaration
	: specifier_qualifier_list group_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| CONST specifier_qualifier_list
	| CONST
	;

group_declarator_list
	: group_declarator
	| group_declarator_list ',' group_declarator
	;

group_declarator
	: direct_declarator
	| ':' conditional_expression
	| direct_declarator ':' conditional_expression
	;

direct_declarator
	: IDENTIFIER
	| '(' direct_declarator ')'
	| direct_declarator '[' conditional_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers direct_declarator
	| declaration_specifiers direct_abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' direct_abstract_declarator ')'
	| '[' ']'
	| '[' conditional_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' conditional_expression ']'
	| '(' ')'
	| '(' parameter_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

compound_statement
	: '{' '}' {
		$$ = new ast::CmpdStmtNode();
	}
	| '{' statement_list '}' {
		$$ = new ast::CmpdStmtNode();
	}
	| '{' declaration_list '}' {
		$$ = new ast::CmpdStmtNode();
	}
	| '{' declaration_list statement_list '}' {
		$$ = new ast::CmpdStmtNode();
	}
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
    : IF '(' expression ')' statement %prec LOWER_THAN_ELSE
    | IF '(' expression ')' statement ELSE statement
    ;

iteration_statement
	: WHILE '(' expression ')' statement
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

translation_unit
    : external_declaration {
        $$ = new ast::ProgramNode();
        ast::ASTNode* node = $1;
        if(node->nodeType == ast::ASTNodeType::FuncNode)
            $$->functions.push_back((ast::FuncNode*)node);
        else if(node->nodeType == ast::ASTNodeType::DeclNode)
            $$->globalDeclarations.push_back((ast::DeclNode*)node);
        else if(node->nodeType == ast::ASTNodeType::StrategyNode)
            $$->strategies.push_back((ast::StrategyNode*)node);

		progRoot = $$;
    }
    | translation_unit external_declaration {
        $$ = $1;
        ast::ASTNode* node = $2;
        if(node->nodeType == ast::ASTNodeType::FuncNode)
            $$->functions.push_back((ast::FuncNode*)node);
        else if(node->nodeType == ast::ASTNodeType::DeclNode)
            $$->globalDeclarations.push_back((ast::DeclNode*)node);
        else if(node->nodeType == ast::ASTNodeType::StrategyNode)
            $$->strategies.push_back((ast::StrategyNode*)node);
		
		progRoot = $$;
    }
;
external_declaration
    : function_definition {
        $$ = new ast::ASTNode();
    }
    | declaration {
        $$ = new ast::ASTNode();
    }
    | strategy_definition {
        $$ = (ast::ASTNode*)$1;
    }
    ;

function_definition
	: FUN IDENTIFIER '(' ARROW type_specifier ')' compound_statement
	| FUN IDENTIFIER '(' parameter_list ARROW type_specifier ')' compound_statement
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
        printf("Parse successful.\n");
		progRoot->printNode();
	}
    else
        printf("Parse failed.\n");
    

    fclose(yyin);
    return 0;
}
