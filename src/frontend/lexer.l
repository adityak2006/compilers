%{
#include "y.tab.h"
#include <string.h>
#include <stdlib.h>
int col = 0;
%}

%option yylineno

digit [0-9]
integer {digit}+
identifier [a-zA-Z_][a-zA-Z0-9_]*


%% 
"strategy"      {col+=strlen(yytext); return STRATEGY;} 
"symbol"        {col+=strlen(yytext); return SYMBOL;}
"timeframe"     {col+=strlen(yytext); return TIMEFRAME;}
"p_size"        {col+=strlen(yytext); return P_SIZE;}
"indicators"    {col+=strlen(yytext); return INDICATORS; }
"regime"        {col+=strlen(yytext); return REGIME; }
"fun"           {col+=strlen(yytext); return FUNC; }
"REF"           {col+=strlen(yytext); return REF; }
"group"         {col+=strlen(yytext); return GROUP; }
"entry_long"    {col+=strlen(yytext); return ENTRYLONG; }
"entry_short"   {col+=strlen(yytext); return ENTRYSHORT; }
"exit_long"     {col+=strlen(yytext); return EXITLONG; }
"exit_short"    {col+=strlen(yytext); return EXITSHORT; }
"for"           {col+=strlen(yytext); return FOR; }
"while"         {col+=strlen(yytext); return WHILE; }
"if"            {col+=strlen(yytext); return IF; }
"elseif"        {col+=strlen(yytext); return ELSEIF; }
"else"          {col+=strlen(yytext); return ELSE; }
"int"           {col+=strlen(yytext); return INT; }
"float"         {col+=strlen(yytext); return FLOAT; }
"bool"          {col+=strlen(yytext); return BOOL; }
"void"          {col+=strlen(yytext); return VOID; }
"string"        {col+=strlen(yytext); return STRING; }
"AND"|"&&"      {col+=strlen(yytext); return AND; }
"OR"|"||"       {col+=strlen(yytext); return OR; }
"NOT"|"!"       {col+=strlen(yytext); return NOT; }
"XOR"|"^"       {col+=strlen(yytext); return XOR; }
{identifier}    {col+=strlen(yytext); yylval.id = strdup(yytext); return IDENTIFIER;}
{integer}       {col+=strlen(yytext); yylval.intVal = atoi(yytext); return INTEGERLIT;}
([0-9]+(\.[0-9]+)?)([eE][+-]?[0-9]+)? {col+=strlen(yytext); yylval.floatVal = atof(yytext); return FLOATLIT;}
"+"     {col+=strlen(yytext); return '+';}
"-"     {col+=strlen(yytext); return '-';}
"*"     {col+=strlen(yytext); return '*';}
"/"     {col+=strlen(yytext); return '/';}
"%"     {col+=strlen(yytext); return '%';}
"("     {col+=strlen(yytext); return '(';}
")"     {col+=strlen(yytext); return ')';}
">="    {col+=strlen(yytext); return GEQ;}
"<="    {col+=strlen(yytext); return LEQ;}
"=="    {col+=strlen(yytext); return EQ;}
"!="    {col+=strlen(yytext); return NEQ;}
"="     {col+=strlen(yytext); return '=';}
">"     {col+=strlen(yytext); return '>';}
"<"     {col+=strlen(yytext); return '<';}
","     {col+=strlen(yytext); return ',';}
"{"     {col+=strlen(yytext); return '{';}
"}"     {col+=strlen(yytext); return '}';}
"["     {col+=strlen(yytext); return '[';}
"]"     {col+=strlen(yytext); return ']';}
";"     {col+=strlen(yytext); return ';';}
"::"    {col+=strlen(yytext); return SCOPE;}
":"     {col+=strlen(yytext); return ':';}
\"[^\"]*\" {col+=strlen(yytext); yylval.id = strdup(yytext); return STRINGLIT;}
[ \t]   {col+=strlen(yytext);}

\n {col=0;}
. {printf("Unexpected token in line %d at column %d : %s\n",yylineno,col,yytext);}

%%

int yywrap(){
    return 1;
}
