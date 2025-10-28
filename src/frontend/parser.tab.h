/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "parser.y"

	#include "ast.h"

#line 53 "parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    STRATEGY = 258,                /* STRATEGY  */
    SYMBOL = 259,                  /* SYMBOL  */
    TIMEFRAME = 260,               /* TIMEFRAME  */
    P_SIZE = 261,                  /* P_SIZE  */
    INDICATORS = 262,              /* INDICATORS  */
    REGIMES = 263,                 /* REGIMES  */
    FUN = 264,                     /* FUN  */
    REF = 265,                     /* REF  */
    SCOPE = 266,                   /* SCOPE  */
    ARROW = 267,                   /* ARROW  */
    ENTRYLONG = 268,               /* ENTRYLONG  */
    ENTRYSHORT = 269,              /* ENTRYSHORT  */
    EXITLONG = 270,                /* EXITLONG  */
    EXITSHORT = 271,               /* EXITSHORT  */
    OPEN = 272,                    /* OPEN  */
    CLOSE = 273,                   /* CLOSE  */
    HIGH = 274,                    /* HIGH  */
    LOW = 275,                     /* LOW  */
    VOLUME = 276,                  /* VOLUME  */
    POSITION_SHARES = 277,         /* POSITION_SHARES  */
    ENTRY_PRICE = 278,             /* ENTRY_PRICE  */
    DAYS_IN_POSITION = 279,        /* DAYS_IN_POSITION  */
    PORTFOLIO_VALUE = 280,         /* PORTFOLIO_VALUE  */
    CASH_AVAILABLE = 281,          /* CASH_AVAILABLE  */
    SMA = 282,                     /* SMA  */
    EMA = 283,                     /* EMA  */
    RSI = 284,                     /* RSI  */
    BB = 285,                      /* BB  */
    ATR = 286,                     /* ATR  */
    SDV = 287,                     /* SDV  */
    MAX = 288,                     /* MAX  */
    MIN = 289,                     /* MIN  */
    SUM = 290,                     /* SUM  */
    MEDIAN = 291,                  /* MEDIAN  */
    AVG = 292,                     /* AVG  */
    ABS = 293,                     /* ABS  */
    CORRELATION = 294,             /* CORRELATION  */
    SLOPE = 295,                   /* SLOPE  */
    RSQUARED = 296,                /* RSQUARED  */
    GROUP = 297,                   /* GROUP  */
    FOR = 298,                     /* FOR  */
    WHILE = 299,                   /* WHILE  */
    IF = 300,                      /* IF  */
    ELSE = 301,                    /* ELSE  */
    CONTINUE = 302,                /* CONTINUE  */
    BREAK = 303,                   /* BREAK  */
    RETURN = 304,                  /* RETURN  */
    INT = 305,                     /* INT  */
    FLOAT = 306,                   /* FLOAT  */
    BOOL = 307,                    /* BOOL  */
    VOID = 308,                    /* VOID  */
    STRING = 309,                  /* STRING  */
    RGM = 310,                     /* RGM  */
    CONST = 311,                   /* CONST  */
    TIMESERIES = 312,              /* TIMESERIES  */
    AND = 313,                     /* AND  */
    OR = 314,                      /* OR  */
    LEFT_OP = 315,                 /* LEFT_OP  */
    RIGHT_OP = 316,                /* RIGHT_OP  */
    LEQ = 317,                     /* LEQ  */
    GEQ = 318,                     /* GEQ  */
    EQ = 319,                      /* EQ  */
    NEQ = 320,                     /* NEQ  */
    IDENTIFIER = 321,              /* IDENTIFIER  */
    STRINGLIT = 322,               /* STRINGLIT  */
    INTLIT = 323,                  /* INTLIT  */
    FLOATLIT = 324,                /* FLOATLIT  */
    LOWER_THAN_ELSE = 325          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "parser.y"

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
	std::vector<initDecl*>* initDeclVec;
	std::vector<Initializer*>* initList;
	std::vector<ParamNode*>* paramVec;
	std::vector<GroupDeclaration*>* groupDeclList;
	std::vector<GroupDeclarator*>* groupDeclaratorList;


#line 176 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
