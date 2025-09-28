%{
#include "y.tab.h"
#include <string.h>
#include <stdlib.h>
%}

digit [0-9]
integer {digit}+
identifier [a-zA-Z_][a-zA-Z0-9_]*


%%
"strategy"  {return STRATEGY;} 
"symbol"   {return SYMBOL;}
"timeframe"     {return TIMEFRAME;}
"p_size"    {return P_SIZE;}
"indicators"    { return INDICATORS; }
"regime"    { return REGIME; }

{identifier}  {yylval.id = strdup(yytext); return IDENTIFIER;}
{integer} {yylval.intVal = atoi(yytext); return INTEGER;}
([0-9]+(\.[0-9]+)?)([eE][+-]?[0-9]+)? {yylval.floatVal = atof(yytext); return FLOAT;}

"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"(" {return '(';}
")" {return ')';}
"=" {return '=';}
"," {return ',';}
"{"     {return '{';}
"}"     {return '}';}
\"[^\"]*\" {yylval.id = strdup(yytext); return STRING;}

[ \t] {}
. {printf("Unexpected token %s\n",yytext);}

%%

int yywrap(){
    return 1;
}