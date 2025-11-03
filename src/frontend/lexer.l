%{
#include "parser.tab.h"
#include <string.h>
#include <stdlib.h>
int col = 1;
%}

%option yylineno

digit [0-9]
integer {digit}+
identifier [a-zA-Z_][a-zA-Z0-9_]*


%% 
\/\/[^\n]*           {;}
"strategy"           {col+=strlen(yytext); return STRATEGY;} 
"symbol"             {col+=strlen(yytext); return SYMBOL;}
"timeframe"          {col+=strlen(yytext); return TIMEFRAME;}
"p_size"             {col+=strlen(yytext); return P_SIZE;}
"indicators"         {col+=strlen(yytext); return INDICATORS; }
"regimes"            {col+=strlen(yytext); return REGIMES; }
"rgm"                {col+=strlen(yytext); return RGM; }
"fun"                {col+=strlen(yytext); return FUN; }
"REF"                {col+=strlen(yytext); return REF; }
"group"              {col+=strlen(yytext); return GROUP; }
"entry_long"         {col+=strlen(yytext); return ENTRYLONG; }
"entry_short"        {col+=strlen(yytext); return ENTRYSHORT; }
"exit_long"          {col+=strlen(yytext); return EXITLONG; }
"exit_short"         {col+=strlen(yytext); return EXITSHORT; }
"open"               {col+=strlen(yytext); return OPEN; }
"close"              {col+=strlen(yytext); return CLOSE; }
"high"               {col+=strlen(yytext); return HIGH; }
"low"                {col+=strlen(yytext); return LOW; }
"volume"             {col+=strlen(yytext); return VOLUME; }
"position_shares"    {col+=strlen(yytext); return POSITION_SHARES; }
"entry_price"        {col+=strlen(yytext); return ENTRY_PRICE; }
"days_in_position"   {col+=strlen(yytext); return DAYS_IN_POSITION; }
"portfolio_value"    {col+=strlen(yytext); return PORTFOLIO_VALUE; }
"cash_available"     {col+=strlen(yytext); return CASH_AVAILABLE; }
"SMA"                {col+=strlen(yytext); return SMA; }
"EMA"                {col+=strlen(yytext); return EMA; }
"RSI"                {col+=strlen(yytext); return RSI; }
"BB"                 {col+=strlen(yytext); return BB; }
"ATR"                {col+=strlen(yytext); return ATR; }
"SDV"                {col+=strlen(yytext); return SDV; }
"MAX"                {col+=strlen(yytext); return MAX; }
"MIN"                {col+=strlen(yytext); return MIN; }
"SUM"                {col+=strlen(yytext); return SUM; }
"MEDIAN"             {col+=strlen(yytext); return MEDIAN; }
"AVG"                {col+=strlen(yytext); return AVG; }
"ABS"                {col+=strlen(yytext); return ABS; }
"CORRELATION"        {col+=strlen(yytext); return CORRELATION; }
"SLOPE"              {col+=strlen(yytext); return SLOPE; }
"RSQUARED"           {col+=strlen(yytext); return RSQUARED; }
"while"              {col+=strlen(yytext); return WHILE; }
"for"                {col+=strlen(yytext); return FOR; }
"if"                 {col+=strlen(yytext); return IF; }
"else"               {col+=strlen(yytext); return ELSE; }
"int"                {col+=strlen(yytext); return INT; }
"float"              {col+=strlen(yytext); return FLOAT; }
"bool"               {col+=strlen(yytext); return BOOL; }
"void"               {col+=strlen(yytext); return VOID; }
"string"             {col+=strlen(yytext); return STRING; }
"timeseries"         {col+=strlen(yytext); return TIMESERIES; }
"AND"|"&&"           {col+=strlen(yytext); return AND; }
"OR"|"||"            {col+=strlen(yytext); return OR; }
"NOT"|"!"            {col+=strlen(yytext); return '!'; }
"XOR"|"^"            {col+=strlen(yytext); return '^'; }
">>"                 {col+=strlen(yytext); return(RIGHT_OP); }
"<<"                 {col+=strlen(yytext); return(LEFT_OP); }
"continue"           {col+=strlen(yytext); return CONTINUE; }
"break"              {col+=strlen(yytext); return BREAK; }
"return"             {col+=strlen(yytext); return RETURN; }
"const"              {col+=strlen(yytext); return CONST; }
{identifier}         {col+=strlen(yytext); yylval.id = new std::string(yytext); return IDENTIFIER;}
{integer}            {col+=strlen(yytext); yylval.intVal = atoi(yytext); return INTLIT;}
([0-9]+(\.[0-9]+)?)([eE][+-]?[0-9]+)? {col+=strlen(yytext); yylval.floatVal = atof(yytext); return FLOATLIT;}
"+"                  {col+=strlen(yytext); return '+';}
"-"                  {col+=strlen(yytext); return '-';}
"*"                  {col+=strlen(yytext); return '*';}
"/"                  {col+=strlen(yytext); return '/';}
"%"                  {col+=strlen(yytext); return '%';}
"("                  {col+=strlen(yytext); return '(';}
")"                  {col+=strlen(yytext); return ')';}
">="                 {col+=strlen(yytext); return GEQ;}
"<="                 {col+=strlen(yytext); return LEQ;}
"=="                 {col+=strlen(yytext); return EQ;}
"!="                 {col+=strlen(yytext); return NEQ;}
"="                  {col+=strlen(yytext); return '=';}
">"                  {col+=strlen(yytext); return '>';}
"<"                  {col+=strlen(yytext); return '<';}
","                  {col+=strlen(yytext); return ',';}
"{"                  {col+=strlen(yytext); return '{';}
"}"                  {col+=strlen(yytext); return '}';}
"["                  {col+=strlen(yytext); return '[';}
"]"                  {col+=strlen(yytext); return ']';}
";"                  {col+=strlen(yytext); return ';';}
"::"                 {col+=strlen(yytext); return SCOPE;}
":"                  {col+=strlen(yytext); return ':';}
"~"                  {col+=strlen(yytext); return '~';}
"?"                  {col+=strlen(yytext); return '?';}
"."                  {col+=strlen(yytext); return '.';}
"&"                  {col+=strlen(yytext); return '&';}
"|"                  {col+=strlen(yytext); return '|';}
"->"                 {col+=strlen(yytext); return ARROW;}
\"[^\"]*\"           {col+=strlen(yytext); yylval.id = new std::string(yytext); return STRINGLIT;}
[ \t]                {col+=strlen(yytext);}
\n                   {col=1;}
.                    {printf("Unexpected token in line %d at column %d : %s\n",yylineno,col,yytext);}

%%

int yywrap(){
    return 1;
}
