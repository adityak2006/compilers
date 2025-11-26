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

#ifndef YY_YY_USERS_ROBINHOOD_COMPILERS_BUILD_PARSER_TAB_H_INCLUDED
# define YY_YY_USERS_ROBINHOOD_COMPILERS_BUILD_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "/Users/robinhood/compilers/src/frontend/parser.y"

    #include "ast.h"

#line 53 "/Users/robinhood/compilers/build/parser.tab.h"

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
    SCOPE = 265,                   /* SCOPE  */
    ARROW = 266,                   /* ARROW  */
    ENTRYLONG = 267,               /* ENTRYLONG  */
    ENTRYSHORT = 268,              /* ENTRYSHORT  */
    EXITLONG = 269,                /* EXITLONG  */
    EXITSHORT = 270,               /* EXITSHORT  */
    OPEN = 271,                    /* OPEN  */
    CLOSE = 272,                   /* CLOSE  */
    HIGH = 273,                    /* HIGH  */
    LOW = 274,                     /* LOW  */
    VOLUME = 275,                  /* VOLUME  */
    POSITION_SHARES = 276,         /* POSITION_SHARES  */
    ENTRY_PRICE = 277,             /* ENTRY_PRICE  */
    DAYS_IN_POSITION = 278,        /* DAYS_IN_POSITION  */
    PORTFOLIO_VALUE = 279,         /* PORTFOLIO_VALUE  */
    CASH_AVAILABLE = 280,          /* CASH_AVAILABLE  */
    SMA = 281,                     /* SMA  */
    EMA = 282,                     /* EMA  */
    RSI = 283,                     /* RSI  */
    BB = 284,                      /* BB  */
    ATR = 285,                     /* ATR  */
    SDV = 286,                     /* SDV  */
    MAX = 287,                     /* MAX  */
    MIN = 288,                     /* MIN  */
    SUM = 289,                     /* SUM  */
    MEDIAN = 290,                  /* MEDIAN  */
    AVG = 291,                     /* AVG  */
    ABS = 292,                     /* ABS  */
    CORRELATION = 293,             /* CORRELATION  */
    SLOPE = 294,                   /* SLOPE  */
    RSQUARED = 295,                /* RSQUARED  */
    GROUP = 296,                   /* GROUP  */
    FOR = 297,                     /* FOR  */
    WHILE = 298,                   /* WHILE  */
    IF = 299,                      /* IF  */
    ELSE = 300,                    /* ELSE  */
    CONTINUE = 301,                /* CONTINUE  */
    BREAK = 302,                   /* BREAK  */
    RETURN = 303,                  /* RETURN  */
    INT = 304,                     /* INT  */
    FLOAT = 305,                   /* FLOAT  */
    BOOL = 306,                    /* BOOL  */
    VOID = 307,                    /* VOID  */
    RGM = 308,                     /* RGM  */
    CONST = 309,                   /* CONST  */
    TIMESERIES = 310,              /* TIMESERIES  */
    AND = 311,                     /* AND  */
    OR = 312,                      /* OR  */
    LEFT_OP = 313,                 /* LEFT_OP  */
    RIGHT_OP = 314,                /* RIGHT_OP  */
    LEQ = 315,                     /* LEQ  */
    GEQ = 316,                     /* GEQ  */
    EQ = 317,                      /* EQ  */
    NEQ = 318,                     /* NEQ  */
    IDENTIFIER = 319,              /* IDENTIFIER  */
    STRINGLIT = 320,               /* STRINGLIT  */
    INTLIT = 321,                  /* INTLIT  */
    FLOATLIT = 322,                /* FLOATLIT  */
    LOWER_THAN_ELSE = 323          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 92 "/Users/robinhood/compilers/src/frontend/parser.y"

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



#line 177 "/Users/robinhood/compilers/build/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_USERS_ROBINHOOD_COMPILERS_BUILD_PARSER_TAB_H_INCLUDED  */
