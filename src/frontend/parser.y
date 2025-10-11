%union {
    int intVal;
    float floatVal;
    char *id;
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

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start translation_unit

%%

strategy_definition
    : STRATEGY IDENTIFIER '{' strategy_body '}'
    ;

strategy_body
    : strategy_declarations indicator_section regime_section signal_function_list
    ;

strategy_declarations
    : SYMBOL '=' STRINGLIT ';' TIMEFRAME '=' '{'INTLIT ',' INTLIT',' INTLIT '}' ';' P_SIZE '=' INTLIT ';'
    ;

indicator_section
    :
	| INDICATORS compound_statement
    ;

regime_section
    :
	| REGIMES compound_statement
    ;

signal_function_list
    :
    | signal_function_list signal_function
    ;

signal_function
    : IDENTIFIER SCOPE ENTRYLONG compound_statement
    | IDENTIFIER SCOPE ENTRYSHORT compound_statement
    | IDENTIFIER SCOPE EXITLONG compound_statement
    | IDENTIFIER SCOPE EXITSHORT compound_statement
	| ENTRYLONG compound_statement
    | ENTRYSHORT compound_statement
    | EXITLONG compound_statement
    | EXITSHORT compound_statement
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
	: GROUP IDENTIFIER '{' struct_declaration_list '}'
	| GROUP '{' struct_declaration_list '}'
	| GROUP IDENTIFIER
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| CONST specifier_qualifier_list
	| CONST
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
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
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
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
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	| strategy_definition
	;

function_definition
	: FUN IDENTIFIER '(' ARROW type_specifier ')' compound_statement
	| FUN IDENTIFIER '(' parameter_list ARROW type_specifier ')' compound_statement
	;

%%
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern int col;
int yyparse(void);
extern int yylineno;
extern char *yytext;

void yyerror(const char *s) {
    fprintf(stderr, "\nError: %s at line %d, column %d, near '%s'\n", s, yylineno, col - 1, yytext);
}

int main() {
    yyin = fopen("input.c", "r");
    if (!yyin) {
        perror("input.txt");
        return 1;
    }

    if (yyparse() == 0)
        printf("Parse successful.\n");
    else
        printf("Parse failed.\n");

    fclose(yyin);
    return 0;
}
