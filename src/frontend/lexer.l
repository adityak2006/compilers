%{
#include "y.tab.h"
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
"regime"             {col+=strlen(yytext); return REGIME; }
"fun"                {col+=strlen(yytext); return FUNC; }
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
"timeseries"         {col+=strlen(yytext); return TIMESERIES; }
"array"              {col+=strlen(yytext); return ARRAY; }
"crosses_above"      {col+=strlen(yytext); return CROSSES_ABOVE; }
"risk_management"    {col+=strlen(yytext); return RISK_MANAGE; }
"trending"           {col+=strlen(yytext); return TRENDING; }
"ranging"            {col+=strlen(yytext); return RANGING; }
"lookback"           {col+=strlen(yytext); return LOOKBACK; }
"rolling_beta"       {col+=strlen(yytext); return ROLLING_BETA; }
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
"STDEV"              {col+=strlen(yytext); return STDEV; }
"MAX"                {col+=strlen(yytext); return MAX; }
"MIN"                {col+=strlen(yytext); return MIN; }
"SUM"                {col+=strlen(yytext); return SUM; }
"MEDIAN"             {col+=strlen(yytext); return MEDIAN; }
"AVG"                {col+=strlen(yytext); return AVG; }
"ABS"                {col+=strlen(yytext); return ABS; }
"CORRELATION"        {col+=strlen(yytext); return CORRELATION; }
"SLOPE"              {col+=strlen(yytext); return SLOPE; }
"RSQUARED"           {col+=strlen(yytext); return RSQUARED; }
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

\n {col=1;}
.  {printf("Unexpected token in line %d at column %d : %s\n",yylineno,col,yytext);}

%%

int yywrap(){
    return 1;
}
