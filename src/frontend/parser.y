%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%token STRATEGY SYMBOL TIMEFRAME P_SIZE INDICATORS REGIME 
%token ENTRYLONG ENTRYSHORT EXITLONG EXITSHORT 
%token FOR WHILE IF ELSE ELSEIF FUNC REF GROUP
%token INT FLOAT BOOL VOID STRING
%token SCOPE
%token IDENTIFIER
%token INTEGERLIT FLOATLIT STRINGLIT
%token GEQ LEQ EQ NEQ AND OR NOT XOR

%%

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}

int main(int argc, char *argv[]) {
    
}
