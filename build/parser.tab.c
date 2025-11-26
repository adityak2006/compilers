/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "/Users/robinhood/compilers/src/frontend/parser.y"

#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Verifier.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include "ast.h"
#include "symbol_table.h"
#include "symbol_table_printer.h"
#include "mlir_generator.h"
#include "semantic.h"

using namespace std;

extern FILE *yyin;
extern int col;
int yyparse(void);
int yylex();
void yyerror(const char* s);
extern int yylineno;
extern char *yytext;

ProgramNode* progRoot;
::SymbolTable symtab;


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


#line 157 "/Users/robinhood/compilers/build/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_STRATEGY = 3,                   /* STRATEGY  */
  YYSYMBOL_SYMBOL = 4,                     /* SYMBOL  */
  YYSYMBOL_TIMEFRAME = 5,                  /* TIMEFRAME  */
  YYSYMBOL_P_SIZE = 6,                     /* P_SIZE  */
  YYSYMBOL_INDICATORS = 7,                 /* INDICATORS  */
  YYSYMBOL_REGIMES = 8,                    /* REGIMES  */
  YYSYMBOL_FUN = 9,                        /* FUN  */
  YYSYMBOL_SCOPE = 10,                     /* SCOPE  */
  YYSYMBOL_ARROW = 11,                     /* ARROW  */
  YYSYMBOL_ENTRYLONG = 12,                 /* ENTRYLONG  */
  YYSYMBOL_ENTRYSHORT = 13,                /* ENTRYSHORT  */
  YYSYMBOL_EXITLONG = 14,                  /* EXITLONG  */
  YYSYMBOL_EXITSHORT = 15,                 /* EXITSHORT  */
  YYSYMBOL_OPEN = 16,                      /* OPEN  */
  YYSYMBOL_CLOSE = 17,                     /* CLOSE  */
  YYSYMBOL_HIGH = 18,                      /* HIGH  */
  YYSYMBOL_LOW = 19,                       /* LOW  */
  YYSYMBOL_VOLUME = 20,                    /* VOLUME  */
  YYSYMBOL_POSITION_SHARES = 21,           /* POSITION_SHARES  */
  YYSYMBOL_ENTRY_PRICE = 22,               /* ENTRY_PRICE  */
  YYSYMBOL_DAYS_IN_POSITION = 23,          /* DAYS_IN_POSITION  */
  YYSYMBOL_PORTFOLIO_VALUE = 24,           /* PORTFOLIO_VALUE  */
  YYSYMBOL_CASH_AVAILABLE = 25,            /* CASH_AVAILABLE  */
  YYSYMBOL_SMA = 26,                       /* SMA  */
  YYSYMBOL_EMA = 27,                       /* EMA  */
  YYSYMBOL_RSI = 28,                       /* RSI  */
  YYSYMBOL_BB = 29,                        /* BB  */
  YYSYMBOL_ATR = 30,                       /* ATR  */
  YYSYMBOL_SDV = 31,                       /* SDV  */
  YYSYMBOL_MAX = 32,                       /* MAX  */
  YYSYMBOL_MIN = 33,                       /* MIN  */
  YYSYMBOL_SUM = 34,                       /* SUM  */
  YYSYMBOL_MEDIAN = 35,                    /* MEDIAN  */
  YYSYMBOL_AVG = 36,                       /* AVG  */
  YYSYMBOL_ABS = 37,                       /* ABS  */
  YYSYMBOL_CORRELATION = 38,               /* CORRELATION  */
  YYSYMBOL_SLOPE = 39,                     /* SLOPE  */
  YYSYMBOL_RSQUARED = 40,                  /* RSQUARED  */
  YYSYMBOL_GROUP = 41,                     /* GROUP  */
  YYSYMBOL_FOR = 42,                       /* FOR  */
  YYSYMBOL_WHILE = 43,                     /* WHILE  */
  YYSYMBOL_IF = 44,                        /* IF  */
  YYSYMBOL_ELSE = 45,                      /* ELSE  */
  YYSYMBOL_CONTINUE = 46,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 47,                     /* BREAK  */
  YYSYMBOL_RETURN = 48,                    /* RETURN  */
  YYSYMBOL_INT = 49,                       /* INT  */
  YYSYMBOL_FLOAT = 50,                     /* FLOAT  */
  YYSYMBOL_BOOL = 51,                      /* BOOL  */
  YYSYMBOL_VOID = 52,                      /* VOID  */
  YYSYMBOL_RGM = 53,                       /* RGM  */
  YYSYMBOL_CONST = 54,                     /* CONST  */
  YYSYMBOL_TIMESERIES = 55,                /* TIMESERIES  */
  YYSYMBOL_AND = 56,                       /* AND  */
  YYSYMBOL_OR = 57,                        /* OR  */
  YYSYMBOL_LEFT_OP = 58,                   /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 59,                  /* RIGHT_OP  */
  YYSYMBOL_LEQ = 60,                       /* LEQ  */
  YYSYMBOL_GEQ = 61,                       /* GEQ  */
  YYSYMBOL_EQ = 62,                        /* EQ  */
  YYSYMBOL_NEQ = 63,                       /* NEQ  */
  YYSYMBOL_IDENTIFIER = 64,                /* IDENTIFIER  */
  YYSYMBOL_STRINGLIT = 65,                 /* STRINGLIT  */
  YYSYMBOL_INTLIT = 66,                    /* INTLIT  */
  YYSYMBOL_FLOATLIT = 67,                  /* FLOATLIT  */
  YYSYMBOL_LOWER_THAN_ELSE = 68,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_69_ = 69,                       /* '{'  */
  YYSYMBOL_70_ = 70,                       /* '}'  */
  YYSYMBOL_71_ = 71,                       /* '='  */
  YYSYMBOL_72_ = 72,                       /* ';'  */
  YYSYMBOL_73_ = 73,                       /* ','  */
  YYSYMBOL_74_ = 74,                       /* '('  */
  YYSYMBOL_75_ = 75,                       /* ')'  */
  YYSYMBOL_76_ = 76,                       /* '['  */
  YYSYMBOL_77_ = 77,                       /* ']'  */
  YYSYMBOL_78_ = 78,                       /* '.'  */
  YYSYMBOL_79_ = 79,                       /* '+'  */
  YYSYMBOL_80_ = 80,                       /* '-'  */
  YYSYMBOL_81_ = 81,                       /* '~'  */
  YYSYMBOL_82_ = 82,                       /* '!'  */
  YYSYMBOL_83_ = 83,                       /* '*'  */
  YYSYMBOL_84_ = 84,                       /* '/'  */
  YYSYMBOL_85_ = 85,                       /* '%'  */
  YYSYMBOL_86_ = 86,                       /* '<'  */
  YYSYMBOL_87_ = 87,                       /* '>'  */
  YYSYMBOL_88_ = 88,                       /* '&'  */
  YYSYMBOL_89_ = 89,                       /* '^'  */
  YYSYMBOL_90_ = 90,                       /* '|'  */
  YYSYMBOL_91_ = 91,                       /* '?'  */
  YYSYMBOL_92_ = 92,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 93,                  /* $accept  */
  YYSYMBOL_translationUnit = 94,           /* translationUnit  */
  YYSYMBOL_strategyDefinition = 95,        /* strategyDefinition  */
  YYSYMBOL_96_1 = 96,                      /* $@1  */
  YYSYMBOL_strategyBody = 97,              /* strategyBody  */
  YYSYMBOL_strategyDeclarations = 98,      /* strategyDeclarations  */
  YYSYMBOL_indiRegCompoundStatement = 99,  /* indiRegCompoundStatement  */
  YYSYMBOL_100_2 = 100,                    /* $@2  */
  YYSYMBOL_indicatorSection = 101,         /* indicatorSection  */
  YYSYMBOL_regimeSection = 102,            /* regimeSection  */
  YYSYMBOL_signalFunctionList = 103,       /* signalFunctionList  */
  YYSYMBOL_signalFunction = 104,           /* signalFunction  */
  YYSYMBOL_primaryExpression = 105,        /* primaryExpression  */
  YYSYMBOL_timeseries = 106,               /* timeseries  */
  YYSYMBOL_timeseriesExpression = 107,     /* timeseriesExpression  */
  YYSYMBOL_postfixExpression = 108,        /* postfixExpression  */
  YYSYMBOL_argumentExpressionList = 109,   /* argumentExpressionList  */
  YYSYMBOL_unaryExpression = 110,          /* unaryExpression  */
  YYSYMBOL_unaryOperator = 111,            /* unaryOperator  */
  YYSYMBOL_multiplicativeExpression = 112, /* multiplicativeExpression  */
  YYSYMBOL_additiveExpression = 113,       /* additiveExpression  */
  YYSYMBOL_shiftExpression = 114,          /* shiftExpression  */
  YYSYMBOL_relationalExpression = 115,     /* relationalExpression  */
  YYSYMBOL_equalityExpression = 116,       /* equalityExpression  */
  YYSYMBOL_andExpression = 117,            /* andExpression  */
  YYSYMBOL_exclusiveOrExpression = 118,    /* exclusiveOrExpression  */
  YYSYMBOL_inclusiveOrExpression = 119,    /* inclusiveOrExpression  */
  YYSYMBOL_logicalAndExpression = 120,     /* logicalAndExpression  */
  YYSYMBOL_logicalOrExpression = 121,      /* logicalOrExpression  */
  YYSYMBOL_conditionalExpression = 122,    /* conditionalExpression  */
  YYSYMBOL_assignmentExpression = 123,     /* assignmentExpression  */
  YYSYMBOL_expression = 124,               /* expression  */
  YYSYMBOL_declaration = 125,              /* declaration  */
  YYSYMBOL_declarationSpecifiers = 126,    /* declarationSpecifiers  */
  YYSYMBOL_initDeclaratorList = 127,       /* initDeclaratorList  */
  YYSYMBOL_initDeclarator = 128,           /* initDeclarator  */
  YYSYMBOL_typeSpecifier = 129,            /* typeSpecifier  */
  YYSYMBOL_groupSpecifier = 130,           /* groupSpecifier  */
  YYSYMBOL_groupDeclarationList = 131,     /* groupDeclarationList  */
  YYSYMBOL_groupDeclaration = 132,         /* groupDeclaration  */
  YYSYMBOL_groupDeclaratorList = 133,      /* groupDeclaratorList  */
  YYSYMBOL_groupDeclarator = 134,          /* groupDeclarator  */
  YYSYMBOL_directDeclarator = 135,         /* directDeclarator  */
  YYSYMBOL_parameterList = 136,            /* parameterList  */
  YYSYMBOL_parameterDeclaration = 137,     /* parameterDeclaration  */
  YYSYMBOL_initializer = 138,              /* initializer  */
  YYSYMBOL_initializerList = 139,          /* initializerList  */
  YYSYMBOL_statement = 140,                /* statement  */
  YYSYMBOL_blockItem = 141,                /* blockItem  */
  YYSYMBOL_blockItemList = 142,            /* blockItemList  */
  YYSYMBOL_compoundStatement = 143,        /* compoundStatement  */
  YYSYMBOL_144_3 = 144,                    /* $@3  */
  YYSYMBOL_expressionStatement = 145,      /* expressionStatement  */
  YYSYMBOL_selectionStatement = 146,       /* selectionStatement  */
  YYSYMBOL_iterationStatement = 147,       /* iterationStatement  */
  YYSYMBOL_148_4 = 148,                    /* $@4  */
  YYSYMBOL_forInitStatement = 149,         /* forInitStatement  */
  YYSYMBOL_optionalExpression = 150,       /* optionalExpression  */
  YYSYMBOL_jumpStatement = 151,            /* jumpStatement  */
  YYSYMBOL_globalDeclaration = 152,        /* globalDeclaration  */
  YYSYMBOL_function_definition = 153,      /* function_definition  */
  YYSYMBOL_154_5 = 154,                    /* $@5  */
  YYSYMBOL_155_6 = 155                     /* $@6  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1348

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  182
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  466

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   323


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    82,     2,     2,     2,    85,    88,     2,
      74,    75,    83,    79,    73,    80,    78,    84,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    92,    72,
      86,    71,    87,    91,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    77,    89,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    69,    90,    70,    81,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   201,   201,   216,   234,   233,   276,   286,   297,   297,
     316,   317,   324,   325,   332,   333,   340,   346,   352,   358,
     364,   369,   374,   379,   387,   391,   395,   399,   400,   404,
     409,   414,   419,   424,   429,   438,   447,   456,   468,   479,
     488,   497,   506,   515,   524,   533,   542,   552,   561,   573,
     576,   587,   598,   609,   623,   640,   651,   662,   673,   684,
     695,   706,   717,   731,   742,   756,   759,   765,   770,   776,
     782,   787,   792,   797,   802,   810,   814,   821,   824,   844,
     847,   850,   853,   859,   862,   869,   877,   887,   890,   897,
     907,   910,   917,   927,   930,   937,   944,   951,   961,   964,
     971,   981,   984,   994,   997,  1007,  1010,  1020,  1023,  1033,
    1036,  1046,  1049,  1059,  1062,  1071,  1074,  1090,  1095,  1245,
    1248,  1255,  1260,  1267,  1271,  1280,  1285,  1290,  1295,  1300,
    1305,  1310,  1325,  1381,  1389,  1394,  1401,  1410,  1415,  1423,
    1431,  1436,  1444,  1449,  1456,  1462,  1471,  1476,  1484,  1489,
    1496,  1499,  1502,  1505,  1508,  1514,  1517,  1524,  1527,  1534,
    1534,  1554,  1558,  1566,  1572,  1582,  1589,  1589,  1607,  1608,
    1612,  1613,  1617,  1621,  1625,  1629,  1637,  1640,  1643,  1649,
    1649,  1689,  1689
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "STRATEGY", "SYMBOL",
  "TIMEFRAME", "P_SIZE", "INDICATORS", "REGIMES", "FUN", "SCOPE", "ARROW",
  "ENTRYLONG", "ENTRYSHORT", "EXITLONG", "EXITSHORT", "OPEN", "CLOSE",
  "HIGH", "LOW", "VOLUME", "POSITION_SHARES", "ENTRY_PRICE",
  "DAYS_IN_POSITION", "PORTFOLIO_VALUE", "CASH_AVAILABLE", "SMA", "EMA",
  "RSI", "BB", "ATR", "SDV", "MAX", "MIN", "SUM", "MEDIAN", "AVG", "ABS",
  "CORRELATION", "SLOPE", "RSQUARED", "GROUP", "FOR", "WHILE", "IF",
  "ELSE", "CONTINUE", "BREAK", "RETURN", "INT", "FLOAT", "BOOL", "VOID",
  "RGM", "CONST", "TIMESERIES", "AND", "OR", "LEFT_OP", "RIGHT_OP", "LEQ",
  "GEQ", "EQ", "NEQ", "IDENTIFIER", "STRINGLIT", "INTLIT", "FLOATLIT",
  "LOWER_THAN_ELSE", "'{'", "'}'", "'='", "';'", "','", "'('", "')'",
  "'['", "']'", "'.'", "'+'", "'-'", "'~'", "'!'", "'*'", "'/'", "'%'",
  "'<'", "'>'", "'&'", "'^'", "'|'", "'?'", "':'", "$accept",
  "translationUnit", "strategyDefinition", "$@1", "strategyBody",
  "strategyDeclarations", "indiRegCompoundStatement", "$@2",
  "indicatorSection", "regimeSection", "signalFunctionList",
  "signalFunction", "primaryExpression", "timeseries",
  "timeseriesExpression", "postfixExpression", "argumentExpressionList",
  "unaryExpression", "unaryOperator", "multiplicativeExpression",
  "additiveExpression", "shiftExpression", "relationalExpression",
  "equalityExpression", "andExpression", "exclusiveOrExpression",
  "inclusiveOrExpression", "logicalAndExpression", "logicalOrExpression",
  "conditionalExpression", "assignmentExpression", "expression",
  "declaration", "declarationSpecifiers", "initDeclaratorList",
  "initDeclarator", "typeSpecifier", "groupSpecifier",
  "groupDeclarationList", "groupDeclaration", "groupDeclaratorList",
  "groupDeclarator", "directDeclarator", "parameterList",
  "parameterDeclaration", "initializer", "initializerList", "statement",
  "blockItem", "blockItemList", "compoundStatement", "$@3",
  "expressionStatement", "selectionStatement", "iterationStatement", "$@4",
  "forInitStatement", "optionalExpression", "jumpStatement",
  "globalDeclaration", "function_definition", "$@5", "$@6", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-380)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      17,   -27,   -17,    -5,  -380,  -380,  -380,  -380,  -380,   392,
    -380,    36,  -380,  -380,   -11,  -380,  -380,  -380,  -380,  -380,
      -1,    23,  -380,  -380,  -380,  -380,  -380,    10,  -380,   -41,
      27,    83,   139,  -380,    35,   455,   109,   191,   392,    35,
       8,  -380,    35,   115,  -380,  -380,  -380,  -380,  -380,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,   126,   156,   173,   176,
     179,   182,   184,   186,   188,   223,   234,   236,   241,   243,
     246,  -380,  -380,  -380,   455,   656,  -380,  -380,  -380,  -380,
    -380,  -380,  -380,     0,   254,   656,    88,    82,   123,   -38,
     121,   235,   238,   239,   272,   -36,  -380,  -380,  -380,   253,
     292,   294,   358,   291,   293,   392,   139,   114,  -380,   293,
    -380,  -380,   723,   762,   801,   840,   879,   918,   957,   996,
    1035,  1074,  1113,  1152,  1191,  1230,  1269,  -380,   -45,  -380,
     -19,   522,   656,   304,   656,  -380,   656,   656,   656,   656,
     656,   656,   656,   656,   656,   656,   656,   656,   656,   656,
     656,   656,   656,   656,   656,  -380,   312,  -380,   310,   372,
    -380,   306,  -380,  -380,    35,   308,   309,   315,   316,   317,
     318,   320,   322,   323,   324,   325,   355,   363,   364,   365,
     311,   313,   367,   373,   375,   376,   377,   378,   380,   383,
     385,   386,   390,   391,   393,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
    -380,   455,   656,  -380,  -380,   -13,  -380,   -39,  -380,  -380,
    -380,  -380,  -380,  -380,    88,    88,    82,    82,   123,   123,
     123,   123,   -38,   -38,   121,   235,   238,   239,   272,   -46,
     389,  -380,  -380,   310,  -380,   396,  -380,  -380,  1308,  1308,
    1308,  1308,  1308,  1308,  1308,  1308,  1308,  1308,  1308,  1308,
    1308,  1308,  1308,   445,   446,   447,   448,   449,   450,   451,
     452,   456,  1308,   457,   459,   460,   461,   462,   464,   465,
     466,   467,   497,   498,   499,   500,   501,   504,  1308,   503,
     505,   506,   507,  -380,  -380,   656,  -380,  -380,   656,   565,
    -380,  -380,    29,  -380,  -380,   396,   502,   508,   509,   510,
     512,   515,   518,   519,   520,   521,   523,   524,   525,   555,
     556,   557,   558,   559,   560,   561,   562,   563,   564,   566,
     567,   569,   568,   570,   571,   572,  -380,  -380,   511,   185,
     396,   396,   396,   396,   585,  -380,  -380,  -380,  -380,  -380,
    -380,  -380,  -380,  -380,   513,   514,   580,  1308,  -380,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,
    -380,  -380,   582,   583,  -380,  -380,  -380,  -380,   581,   577,
     578,   584,   587,   588,   589,  -380,  -380,   169,  -380,  -380,
    -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,  -380,
     116,   252,   579,   590,   591,   593,   592,   622,   596,  -380,
     656,   656,  -380,  -380,  -380,   171,  -380,   396,   396,   396,
     396,  -380,  -380,  -380,   632,   633,  -380,  -380,   627,   321,
      52,   101,  -380,  -380,  -380,  -380,  -380,   626,   628,   636,
    -380,  -380,   656,   388,   388,  -380,  -380,   631,   634,   637,
    -380,   529,   639,   656,   388,   638,   635,  -380,   640,   388,
     573,  -380,   586,   645,   641,  -380
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,   126,   127,   128,   125,   129,     0,
     130,     0,   178,   177,     0,   119,   131,     2,   176,     4,
       0,   133,   120,     1,     3,   140,   117,     0,   121,   123,
       0,     0,     0,   118,     0,     0,     0,     0,     0,   145,
       0,   142,     0,     0,   134,   122,    30,    29,    31,    32,
      33,    72,    73,    74,    70,    71,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    24,    25,    26,     0,     0,    79,    80,    81,    82,
      65,    49,    28,    77,    83,     0,    87,    90,    93,    98,
     101,   103,   105,   107,   109,   111,   113,   146,   124,     0,
       0,     0,    10,     0,   144,     0,     0,     0,   137,   139,
     132,   135,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   148,     0,   115,
       0,     0,     0,     0,     0,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   141,     0,     5,     0,    12,
     179,     0,   143,   136,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     147,     0,     0,    27,    67,     0,    75,     0,    69,   114,
      84,    85,    86,    83,    88,    89,    91,    92,    96,    97,
      94,    95,    99,   100,   102,   104,   106,   108,   110,     0,
       0,     8,    11,     0,    14,     0,   181,   138,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,   116,     0,    68,    66,     0,     0,
     157,    13,     6,   159,   180,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    76,   112,     0,     0,
       0,     0,     0,     0,     0,    15,   157,   182,    50,    34,
      51,    35,    52,    36,     0,     0,     0,     0,    55,    39,
      56,    40,    57,    41,    58,    42,    59,    43,    60,    44,
      61,    45,     0,     0,    63,    47,    64,    48,     0,     0,
       0,     0,     0,     0,     0,     9,   161,     0,   155,   156,
     158,   150,   151,   152,   153,   154,    20,    21,    22,    23,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   166,
       0,     0,   172,   173,   174,     0,   162,     0,     0,     0,
       0,   160,    53,    37,     0,     0,    62,    46,     0,     0,
       0,     0,   175,    16,    17,    18,    19,     0,     0,     0,
     169,   168,   170,     0,     0,    54,    38,     0,   171,     0,
     165,   163,     0,   170,     0,     0,     0,   164,     0,     0,
       0,   167,     0,     0,     0,     7
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -380,  -380,  -380,  -380,  -380,  -380,   332,  -380,  -380,  -380,
    -380,  -380,  -380,  -109,  -380,  -380,  -380,   -35,  -380,   106,
     170,    14,   166,   575,   576,   574,   554,   594,  -380,   278,
     -34,   -75,  -306,    20,  -380,   544,    -7,  -380,  -380,   671,
    -380,   551,   -10,  -380,   610,   -56,  -380,  -379,  -380,   371,
    -221,  -380,   289,  -380,  -380,  -380,  -380,   266,  -380,   710,
    -380,  -380,  -380
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    11,    12,    30,   101,   102,   242,   300,   159,   244,
     302,   345,    80,    81,    82,    83,   215,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
     129,   387,    13,    14,    27,    28,    15,    16,    43,    44,
     107,   108,    29,    40,    41,    98,   128,   389,   390,   339,
     391,   346,   392,   393,   394,   429,   442,   449,   395,    17,
      18,   245,   305
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     130,    97,    22,   181,   183,   185,   187,   189,   191,   193,
     195,   197,   199,   201,   203,   205,   207,   209,   127,   105,
       1,   153,   143,   144,   304,   210,     2,   212,   211,   104,
      35,   103,   109,   388,   212,    36,    23,    19,   297,     1,
      97,   340,   341,   342,   343,     2,   298,    20,   145,   146,
     135,    39,    42,    25,   212,   154,   213,   217,     3,    21,
     295,    26,   296,    42,   450,   451,     4,     5,     6,     7,
       8,     9,    10,    31,   131,   457,   132,     3,   133,   239,
     461,   106,    33,    34,   347,     4,     5,     6,     7,     8,
       9,    10,    32,   344,    38,   388,    37,   216,   161,    25,
     219,   220,   221,   222,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   396,
     397,   398,   399,   440,     3,   212,    39,   443,   417,   418,
     419,   420,     4,     5,     6,     7,     8,     9,    10,   181,
     183,   185,   187,   189,   191,   193,   195,   197,   199,   201,
     203,   205,   207,   209,   109,   293,     3,   228,   229,   230,
     231,   139,   140,   315,     4,     5,     6,     7,     8,     9,
      10,   136,   137,   138,   212,    99,   444,    97,   294,   331,
       3,   141,   142,   147,   148,   110,   163,   164,     4,     5,
       6,     7,     8,     9,    10,   100,   433,   434,   435,   436,
     112,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,     3,   379,   380,   381,
     113,   382,   383,   384,     4,     5,     6,     7,     8,     9,
      10,   416,   212,   432,   212,   224,   225,   114,   405,    71,
     115,    72,    73,   116,   303,   385,   117,   386,   118,    75,
     119,   336,   120,   223,    76,    77,    78,    79,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,     3,   379,   380,   381,   121,   382,   383,
     384,     4,     5,     6,     7,     8,     9,    10,   122,   415,
     123,   226,   227,   232,   233,   124,    71,   125,    72,    73,
     126,   303,   421,   149,   386,   134,    75,   150,   152,   151,
     155,    76,    77,    78,    79,   430,   431,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,     3,   156,   157,   158,   160,   448,   218,    36,
       4,     5,     6,     7,     8,     9,    10,   240,   448,   241,
     243,   246,   248,   249,   263,    71,   264,    72,    73,   250,
     251,   252,   253,   386,   254,    75,   255,   256,   257,   258,
      76,    77,    78,    79,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,   259,
     379,   380,   381,     3,   382,   383,   384,   260,   261,   262,
     265,     4,     5,     6,     7,     8,   266,    10,   267,   268,
     269,   270,    71,   271,    72,    73,   272,   303,   273,   274,
     386,   299,    75,   275,   276,   303,   277,    76,    77,    78,
      79,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   306,   307,   308,   309,   310,   311,   312,   313,    71,
     314,    72,    73,   316,    74,   317,   318,   319,   320,    75,
     321,   322,   323,   324,    76,    77,    78,    79,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,   325,   326,   327,   328,   329,   330,   332,
     338,   333,   334,   335,   454,   301,   337,   348,    45,   462,
     402,   403,   378,   349,   350,   351,    71,   352,    72,    73,
     353,   354,   355,   356,   357,   400,    75,   214,   358,   359,
     360,    76,    77,    78,    79,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     372,   371,   373,   374,   404,   375,   376,   377,   406,   407,
     408,   409,   410,    71,   422,    72,    73,   463,   411,   412,
     413,   414,   428,    75,   424,   423,   425,   426,    76,    77,
      78,    79,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,   427,   437,   438,
     439,   445,   447,   446,   452,   455,   237,   212,   458,   453,
     459,   464,   460,   465,   111,   247,   162,   401,   441,   456,
      71,    24,    72,    73,   234,   236,   235,     0,     0,     0,
      75,     0,     0,     0,     0,    76,    77,    78,    79,    46,
      47,    48,    49,    50,     0,     0,     0,   238,     0,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,    47,
      48,    49,    50,     0,     0,     0,     0,   180,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,    47,    48,
      49,    50,     0,     0,     0,     0,   182,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46,    47,    48,    49,
      50,     0,     0,     0,     0,   184,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,    47,    48,    49,    50,
       0,     0,     0,     0,   186,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,    47,    48,    49,    50,     0,
       0,     0,     0,   188,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,    47,    48,    49,    50,     0,     0,
       0,     0,   190,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    46,    47,    48,    49,    50,     0,     0,     0,
       0,   192,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    46,    47,    48,    49,    50,     0,     0,     0,     0,
     194,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,    47,    48,    49,    50,     0,     0,     0,     0,   196,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
      47,    48,    49,    50,     0,     0,     0,     0,   198,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,    47,
      48,    49,    50,     0,     0,     0,     0,   200,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,    47,    48,
      49,    50,     0,     0,     0,     0,   202,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46,    47,    48,    49,
      50,     0,     0,     0,     0,   204,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,    47,    48,    49,    50,
       0,     0,     0,     0,   206,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,    47,    48,    49,    50,     0,
       0,     0,     0,   208,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179
};

static const yytype_int16 yycheck[] =
{
      75,    35,     9,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,    74,    11,
       3,    57,    60,    61,   245,    70,     9,    73,    73,    39,
      71,    38,    42,   339,    73,    76,     0,    64,    77,     3,
      74,    12,    13,    14,    15,     9,    92,    64,    86,    87,
      85,    31,    32,    64,    73,    91,    75,   132,    41,    64,
      73,    72,    75,    43,   443,   444,    49,    50,    51,    52,
      53,    54,    55,    74,    74,   454,    76,    41,    78,   154,
     459,    73,    72,    73,   305,    49,    50,    51,    52,    53,
      54,    55,    69,    64,    11,   401,    69,   131,   105,    64,
     134,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   340,
     341,   342,   343,   429,    41,    73,   106,    75,    12,    13,
      14,    15,    49,    50,    51,    52,    53,    54,    55,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   164,   211,    41,   143,   144,   145,
     146,    79,    80,   272,    49,    50,    51,    52,    53,    54,
      55,    83,    84,    85,    73,    66,    75,   211,   212,   288,
      41,    58,    59,    62,    63,    70,    72,    73,    49,    50,
      51,    52,    53,    54,    55,     4,   417,   418,   419,   420,
      74,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      74,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    72,    73,    72,    73,   139,   140,    74,   357,    64,
      74,    66,    67,    74,    69,    70,    74,    72,    74,    74,
      74,   295,    74,   298,    79,    80,    81,    82,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    74,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    74,   384,
      74,   141,   142,   147,   148,    74,    64,    74,    66,    67,
      74,    69,    70,    88,    72,    71,    74,    89,    56,    90,
      77,    79,    80,    81,    82,   410,   411,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    71,    70,     7,    75,   442,    64,    76,
      49,    50,    51,    52,    53,    54,    55,    65,   453,    69,
       8,    75,    74,    74,    73,    64,    73,    66,    67,    74,
      74,    74,    74,    72,    74,    74,    74,    74,    74,    74,
      79,    80,    81,    82,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    74,
      42,    43,    44,    41,    46,    47,    48,    74,    74,    74,
      73,    49,    50,    51,    52,    53,    73,    55,    73,    73,
      73,    73,    64,    73,    66,    67,    73,    69,    73,    73,
      72,    72,    74,    73,    73,    69,    73,    79,    80,    81,
      82,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    66,    66,    66,    66,    66,    66,    66,    66,    64,
      64,    66,    67,    66,    69,    66,    66,    66,    66,    74,
      66,    66,    66,    66,    79,    80,    81,    82,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    66,    66,    66,    66,    66,    64,    66,
       5,    66,    66,    66,    45,   243,   298,    75,    34,     6,
      67,    67,    71,    75,    75,    75,    64,    75,    66,    67,
      75,    73,    73,    73,    73,    10,    74,    75,    75,    75,
      75,    79,    80,    81,    82,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      73,    75,    73,    75,    64,    75,    75,    75,    66,    66,
      69,    74,    74,    64,    75,    66,    67,    71,    74,    72,
      72,    72,    66,    74,    73,    75,    73,    75,    79,    80,
      81,    82,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    75,    66,    66,
      73,    75,    66,    75,    73,    66,   152,    73,    70,    72,
      75,    66,    72,    72,    43,   164,   106,   346,   429,   453,
      64,    11,    66,    67,   149,   151,   150,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    79,    80,    81,    82,    16,
      17,    18,    19,    20,    -1,    -1,    -1,   153,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,    64,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    64,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    64,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    64,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    64,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,    64,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    64,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    16,    17,    18,    19,    20,    -1,    -1,    -1,    -1,
      64,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    17,    18,    19,    20,    -1,    -1,    -1,    -1,    64,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    64,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,    64,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    64,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    64,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    64,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    64,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     9,    41,    49,    50,    51,    52,    53,    54,
      55,    94,    95,   125,   126,   129,   130,   152,   153,    64,
      64,    64,   129,     0,   152,    64,    72,   127,   128,   135,
      96,    74,    69,    72,    73,    71,    76,    69,    11,   126,
     136,   137,   126,   131,   132,   128,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    64,    66,    67,    69,    74,    79,    80,    81,    82,
     105,   106,   107,   108,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   138,    66,
       4,    97,    98,   129,   135,    11,    73,   133,   134,   135,
      70,   132,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,   138,   139,   123,
     124,    74,    76,    78,    71,   110,    83,    84,    85,    79,
      80,    58,    59,    60,    61,    86,    87,    62,    63,    88,
      89,    90,    56,    57,    91,    77,    71,    70,     7,   101,
      75,   129,   137,    72,    73,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      64,   106,    64,   106,    64,   106,    64,   106,    64,   106,
      64,   106,    64,   106,    64,   106,    64,   106,    64,   106,
      64,   106,    64,   106,    64,   106,    64,   106,    64,   106,
      70,    73,    73,    75,    75,   109,   123,   124,    64,   123,
     110,   110,   110,   110,   112,   112,   113,   113,   114,   114,
     114,   114,   115,   115,   116,   117,   118,   119,   120,   124,
      65,    69,    99,     8,   102,   154,    75,   134,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,   138,   123,    73,    75,    77,    92,    72,
     100,    99,   103,    69,   143,   155,    66,    66,    66,    66,
      66,    66,    66,    66,    64,   106,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      64,   106,    66,    66,    66,    66,   123,   122,     5,   142,
      12,    13,    14,    15,    64,   104,   144,   143,    75,    75,
      75,    75,    75,    75,    73,    73,    73,    73,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    73,    73,    75,    75,    75,    75,    71,    42,
      43,    44,    46,    47,    48,    70,    72,   124,   125,   140,
     141,   143,   145,   146,   147,   151,   143,   143,   143,   143,
      10,   142,    67,    67,    64,   106,    66,    66,    69,    74,
      74,    74,    72,    72,    72,   124,    72,    12,    13,    14,
      15,    70,    75,    75,    73,    73,    75,    75,    66,   148,
     124,   124,    72,   143,   143,   143,   143,    66,    66,    73,
     125,   145,   149,    75,    75,    75,    75,    66,   124,   150,
     140,   140,    73,    72,    45,    66,   150,   140,    70,    75,
      72,   140,     6,    71,    66,    72
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    93,    94,    94,    96,    95,    97,    98,   100,    99,
     101,   101,   102,   102,   103,   103,   104,   104,   104,   104,
     104,   104,   104,   104,   105,   105,   105,   105,   105,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   109,   109,   110,   110,   111,
     111,   111,   111,   112,   112,   112,   112,   113,   113,   113,
     114,   114,   114,   115,   115,   115,   115,   115,   116,   116,
     116,   117,   117,   118,   118,   119,   119,   120,   120,   121,
     121,   122,   122,   123,   123,   124,   124,   125,   125,   126,
     126,   127,   127,   128,   128,   129,   129,   129,   129,   129,
     129,   129,   130,   130,   131,   131,   132,   133,   133,   134,
     135,   135,   136,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   140,   140,   140,   141,   141,   142,   142,   144,
     143,   145,   145,   146,   146,   147,   148,   147,   149,   149,
     150,   150,   151,   151,   151,   151,   152,   152,   152,   154,
     153,   155,   153
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     6,     4,    18,     0,     4,
       0,     2,     0,     2,     0,     2,     4,     4,     4,     4,
       2,     2,     2,     2,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     6,     6,     6,     8,    10,     6,
       6,     6,     6,     6,     6,     6,     8,     6,     6,     1,
       6,     6,     6,     8,    10,     6,     6,     6,     6,     6,
       6,     6,     8,     6,     6,     1,     4,     3,     4,     3,
       1,     1,     1,     1,     1,     1,     3,     1,     2,     1,
       1,     1,     1,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     5,     1,     3,     1,     3,     2,     3,     1,
       2,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     5,     2,     1,     2,     3,     1,     3,     1,
       1,     4,     1,     3,     2,     1,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     2,     0,
       4,     1,     2,     5,     7,     5,     0,     9,     1,     1,
       0,     1,     2,     2,     2,     3,     1,     1,     1,     0,
       8,     0,     9
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* translationUnit: globalDeclaration  */
#line 201 "/Users/robinhood/compilers/src/frontend/parser.y"
                        {
        (yyval.prog) = new ProgramNode();
        ASTNode* node = (yyvsp[0].node);
        if(node->nodeType == ASTNodeType::FuncNode){
            (yyval.prog)->functions.push_back((FuncNode*)node);
        }
        else if(node->nodeType == ASTNodeType::DeclNode){
            (yyval.prog)->globalDeclarations.push_back((DeclNode*)node);
        }
        else if(node->nodeType == ASTNodeType::StrategyNode){
            (yyval.prog)->strategies.push_back((StrategyNode*)node);
        }
        
        progRoot = (yyval.prog);
    }
#line 1808 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 3: /* translationUnit: translationUnit globalDeclaration  */
#line 216 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        (yyval.prog) = (yyvsp[-1].prog);
        ASTNode* node = (yyvsp[0].node);
        if(node->nodeType == ASTNodeType::FuncNode){
            (yyval.prog)->functions.push_back((FuncNode*)node);
        }
        else if(node->nodeType == ASTNodeType::DeclNode){
            (yyval.prog)->globalDeclarations.push_back((DeclNode*)node);
        }
        else if(node->nodeType == ASTNodeType::StrategyNode){
            (yyval.prog)->strategies.push_back((StrategyNode*)node);
        }
        progRoot = (yyval.prog);
    }
#line 1827 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 4: /* $@1: %empty  */
#line 234 "/Users/robinhood/compilers/src/frontend/parser.y"
        {
            std::string sname = *(yyvsp[0].id);
            int zeros[3] = {0,0,0};
            
            if (!symtab.currentScope->define(std::make_unique<StrategySym>(sname, sname, zeros, yylineno, col-1))) {
                std::cerr << "Error: redeclaration of strategy '" << sname << "' at line " << yylineno << "\n";
            }
            symtab.enterScope();
        }
#line 1841 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 5: /* strategyDefinition: STRATEGY IDENTIFIER $@1 '{' strategyBody '}'  */
#line 244 "/Users/robinhood/compilers/src/frontend/parser.y"
        {
            symtab.exitScope();

            (yyval.strategy) = new StrategyNode();
            (yyval.strategy)->id = *(yyvsp[-4].id);
            if ((yyvsp[-1].strategy)) {
                (yyval.strategy)->declarations = (yyvsp[-1].strategy)->declarations;
                (yyval.strategy)->indicators = (yyvsp[-1].strategy)->indicators;
                (yyval.strategy)->regimes = (yyvsp[-1].strategy)->regimes;
                (yyval.strategy)->signals = (yyvsp[-1].strategy)->signals;
            }


            Symbol* sym = symtab.currentScope->lookup(*(yyvsp[-4].id));
            if (sym) {
                if (auto ss = dynamic_cast<StrategySym*>(sym)) {
                    if ((yyvsp[-1].strategy) && (yyvsp[-1].strategy)->declarations) {
                        StratDeclNode* sd = (yyvsp[-1].strategy)->declarations;
                        if (sd && sd->timeframe.size() >= 3) {
                            for (size_t i = 0; i < 3; ++i) ss->timeframe[i] = sd->timeframe[i];
                        }
                    }
                }
            }

            // Optionally attach parsed decl info back to the StrategySym (lookup in enclosing scope)
            
        }
#line 1874 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 6: /* strategyBody: strategyDeclarations indicatorSection regimeSection signalFunctionList  */
#line 276 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                                             {
        (yyval.strategy) = new StrategyNode();
        (yyval.strategy)->declarations = (yyvsp[-3].strategyDecl);
        (yyval.strategy)->indicators = (yyvsp[-2].indicator);
        (yyval.strategy)->regimes = (yyvsp[-1].regime);
        (yyval.strategy)->signals = (yyvsp[0].sigFuncList);
    }
#line 1886 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 7: /* strategyDeclarations: SYMBOL '=' STRINGLIT ';' TIMEFRAME '=' '{' INTLIT ',' INTLIT ',' INTLIT '}' ';' P_SIZE '=' INTLIT ';'  */
#line 286 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                                                                          {
        (yyval.strategyDecl) = new StratDeclNode();
        (yyval.strategyDecl)->symbol = *(yyvsp[-15].id);
        (yyval.strategyDecl)->timeframe.push_back((yyvsp[-10].intVal));
        (yyval.strategyDecl)->timeframe.push_back((yyvsp[-8].intVal));
        (yyval.strategyDecl)->timeframe.push_back((yyvsp[-6].intVal));
        (yyval.strategyDecl)->positionSize = (yyvsp[-1].intVal);
    }
#line 1899 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 8: /* $@2: %empty  */
#line 297 "/Users/robinhood/compilers/src/frontend/parser.y"
          {
        ;
    }
#line 1907 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 9: /* indiRegCompoundStatement: '{' $@2 blockItemList '}'  */
#line 299 "/Users/robinhood/compilers/src/frontend/parser.y"
                        {
        CmpdStmtNode* node = new CmpdStmtNode();
        for (ASTNode* item : *(yyvsp[-1].nodeList)) {
            if (!item) continue;
            if (item->nodeType == ASTNodeType::DeclNode) {
                node->declarations.push_back((DeclNode*)item);
            }
            else {
                node->statements.push_back((StmtNode*)item);
            }
        }
        delete (yyvsp[-1].nodeList);
        (yyval.stmt) = node;
    }
#line 1926 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 10: /* indicatorSection: %empty  */
#line 316 "/Users/robinhood/compilers/src/frontend/parser.y"
      {(yyval.indicator) = NULL;}
#line 1932 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 11: /* indicatorSection: INDICATORS indiRegCompoundStatement  */
#line 317 "/Users/robinhood/compilers/src/frontend/parser.y"
                                          {
        (yyval.indicator) = new IndicatorNode();
        (yyval.indicator)->body = (CmpdStmtNode*)(yyvsp[0].stmt);
    }
#line 1941 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 12: /* regimeSection: %empty  */
#line 324 "/Users/robinhood/compilers/src/frontend/parser.y"
      {(yyval.regime) = NULL;}
#line 1947 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 13: /* regimeSection: REGIMES indiRegCompoundStatement  */
#line 325 "/Users/robinhood/compilers/src/frontend/parser.y"
                                       {
        (yyval.regime) = new RegimeNode();
        (yyval.regime)->body = (CmpdStmtNode*)(yyvsp[0].stmt);
    }
#line 1956 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 14: /* signalFunctionList: %empty  */
#line 332 "/Users/robinhood/compilers/src/frontend/parser.y"
       { (yyval.sigFuncList) = new SignalFuncListNode(); }
#line 1962 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 15: /* signalFunctionList: signalFunctionList signalFunction  */
#line 333 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        (yyval.sigFuncList) = (yyvsp[-1].sigFuncList);
        if ((yyvsp[0].signalFunc)) (yyval.sigFuncList)->signals.push_back((yyvsp[0].signalFunc));
    }
#line 1971 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 16: /* signalFunction: IDENTIFIER SCOPE ENTRYLONG compoundStatement  */
#line 340 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                   {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->regimeId = *(yyvsp[-3].id);
        (yyval.signalFunc)->signalType = ENTRY_LONG;
        (yyval.signalFunc)->body = (CmpdStmtNode*)(yyvsp[0].stmt);
    }
#line 1982 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 17: /* signalFunction: IDENTIFIER SCOPE ENTRYSHORT compoundStatement  */
#line 346 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                    {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->regimeId = *(yyvsp[-3].id);
        (yyval.signalFunc)->signalType = ENTRY_SHORT;
        (yyval.signalFunc)->body = (CmpdStmtNode*)(yyvsp[0].stmt);
    }
#line 1993 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 18: /* signalFunction: IDENTIFIER SCOPE EXITLONG compoundStatement  */
#line 352 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                  {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->regimeId = *(yyvsp[-3].id);
        (yyval.signalFunc)->signalType = EXIT_LONG;
        (yyval.signalFunc)->body = (CmpdStmtNode*)(yyvsp[0].stmt);
    }
#line 2004 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 19: /* signalFunction: IDENTIFIER SCOPE EXITSHORT compoundStatement  */
#line 358 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                   {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->regimeId = *(yyvsp[-3].id);
        (yyval.signalFunc)->signalType = EXIT_SHORT;
        (yyval.signalFunc)->body = (CmpdStmtNode*)(yyvsp[0].stmt);
    }
#line 2015 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 20: /* signalFunction: ENTRYLONG compoundStatement  */
#line 364 "/Users/robinhood/compilers/src/frontend/parser.y"
                                  {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->signalType = ENTRY_LONG;
        (yyval.signalFunc)->body = (CmpdStmtNode*)(yyvsp[0].stmt);
    }
#line 2025 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 21: /* signalFunction: ENTRYSHORT compoundStatement  */
#line 369 "/Users/robinhood/compilers/src/frontend/parser.y"
                                   {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->signalType = ENTRY_SHORT;
        (yyval.signalFunc)->body = (CmpdStmtNode*)(yyvsp[0].stmt);
    }
#line 2035 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 22: /* signalFunction: EXITLONG compoundStatement  */
#line 374 "/Users/robinhood/compilers/src/frontend/parser.y"
                                 {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->signalType = EXIT_LONG;
        (yyval.signalFunc)->body = (CmpdStmtNode*)(yyvsp[0].stmt);
    }
#line 2045 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 23: /* signalFunction: EXITSHORT compoundStatement  */
#line 379 "/Users/robinhood/compilers/src/frontend/parser.y"
                                  {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->signalType = EXIT_SHORT;
        (yyval.signalFunc)->body = (CmpdStmtNode*)(yyvsp[0].stmt);
    }
#line 2055 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 24: /* primaryExpression: IDENTIFIER  */
#line 387 "/Users/robinhood/compilers/src/frontend/parser.y"
                 {
        (yyval.expr) = new IdentifierNode();
        ((IdentifierNode*)(yyval.expr))->id = *(yyvsp[0].id);
    }
#line 2064 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 25: /* primaryExpression: INTLIT  */
#line 391 "/Users/robinhood/compilers/src/frontend/parser.y"
             {
        (yyval.expr) = new LiteralIntNode();
        ((LiteralIntNode*)(yyval.expr))->value = (yyvsp[0].intVal);
    }
#line 2073 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 26: /* primaryExpression: FLOATLIT  */
#line 395 "/Users/robinhood/compilers/src/frontend/parser.y"
               {
        (yyval.expr) = new LiteralFloatNode();
        ((LiteralFloatNode*)(yyval.expr))->value = (yyvsp[0].floatVal);
    }
#line 2082 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 27: /* primaryExpression: '(' expression ')'  */
#line 399 "/Users/robinhood/compilers/src/frontend/parser.y"
                         { (yyval.expr) = (yyvsp[-1].expr); }
#line 2088 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 28: /* primaryExpression: timeseriesExpression  */
#line 400 "/Users/robinhood/compilers/src/frontend/parser.y"
                           { (yyval.expr) = (yyvsp[0].expr); }
#line 2094 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 29: /* timeseries: CLOSE  */
#line 404 "/Users/robinhood/compilers/src/frontend/parser.y"
            {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::CLOSE_TS;
        (yyval.expr) = node;
    }
#line 2104 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 30: /* timeseries: OPEN  */
#line 409 "/Users/robinhood/compilers/src/frontend/parser.y"
           {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::OPEN_TS;
        (yyval.expr) = node;
    }
#line 2114 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 31: /* timeseries: HIGH  */
#line 414 "/Users/robinhood/compilers/src/frontend/parser.y"
           {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::HIGH_TS;
        (yyval.expr) = node;
    }
#line 2124 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 32: /* timeseries: LOW  */
#line 419 "/Users/robinhood/compilers/src/frontend/parser.y"
          {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::LOW_TS;
        (yyval.expr) = node;
    }
#line 2134 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 33: /* timeseries: VOLUME  */
#line 424 "/Users/robinhood/compilers/src/frontend/parser.y"
             {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::VOLUME_TS;
        (yyval.expr) = node;
    }
#line 2144 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 34: /* timeseries: SMA '(' timeseries ',' INTLIT ')'  */
#line 429 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SMA_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2158 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 35: /* timeseries: EMA '(' timeseries ',' INTLIT ')'  */
#line 438 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::EMA_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2172 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 36: /* timeseries: RSI '(' timeseries ',' INTLIT ')'  */
#line 447 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSI_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2186 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 37: /* timeseries: BB '(' timeseries ',' INTLIT ',' FLOATLIT ')'  */
#line 456 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                    {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::BB_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-3].intVal);
        LiteralFloatNode* floatNode = new LiteralFloatNode();
        floatNode->value = (yyvsp[-1].floatVal);
        node->args.push_back((yyvsp[-5].expr));
        node->args.push_back(intNode);
        node->args.push_back(floatNode);
        (yyval.expr) = node;
    }
#line 2203 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 38: /* timeseries: ATR '(' timeseries ',' timeseries ',' timeseries ',' INTLIT ')'  */
#line 468 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                                      {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ATR_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-7].expr));
        node->args.push_back((yyvsp[-5].expr));
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2219 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 39: /* timeseries: SDV '(' timeseries ',' INTLIT ')'  */
#line 479 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SDV_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2233 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 40: /* timeseries: MAX '(' timeseries ',' INTLIT ')'  */
#line 488 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MAX_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2247 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 41: /* timeseries: MIN '(' timeseries ',' INTLIT ')'  */
#line 497 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MIN_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2261 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 42: /* timeseries: SUM '(' timeseries ',' INTLIT ')'  */
#line 506 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SUM_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2275 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 43: /* timeseries: MEDIAN '(' timeseries ',' INTLIT ')'  */
#line 515 "/Users/robinhood/compilers/src/frontend/parser.y"
                                           {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MEDIAN_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2289 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 44: /* timeseries: AVG '(' timeseries ',' INTLIT ')'  */
#line 524 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::AVG_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2303 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 45: /* timeseries: ABS '(' timeseries ',' INTLIT ')'  */
#line 533 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ABS_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2317 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 46: /* timeseries: CORRELATION '(' timeseries ',' timeseries ',' INTLIT ')'  */
#line 542 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                               {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::CORRELATION_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-5].expr));
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2332 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 47: /* timeseries: SLOPE '(' timeseries ',' INTLIT ')'  */
#line 552 "/Users/robinhood/compilers/src/frontend/parser.y"
                                          {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SLOPE_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2346 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 48: /* timeseries: RSQUARED '(' timeseries ',' INTLIT ')'  */
#line 561 "/Users/robinhood/compilers/src/frontend/parser.y"
                                             {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSQUARED_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        node->args.push_back((yyvsp[-3].expr));
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2360 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 49: /* timeseriesExpression: timeseries  */
#line 573 "/Users/robinhood/compilers/src/frontend/parser.y"
                 {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 2368 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 50: /* timeseriesExpression: SMA '(' IDENTIFIER ',' INTLIT ')'  */
#line 576 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SMA_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2384 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 51: /* timeseriesExpression: EMA '(' IDENTIFIER ',' INTLIT ')'  */
#line 587 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::EMA_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2400 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 52: /* timeseriesExpression: RSI '(' IDENTIFIER ',' INTLIT ')'  */
#line 598 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSI_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2416 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 53: /* timeseriesExpression: BB '(' IDENTIFIER ',' INTLIT ',' FLOATLIT ')'  */
#line 609 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                    {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::BB_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-3].intVal);
        LiteralFloatNode* floatNode = new LiteralFloatNode();
        floatNode->value = (yyvsp[-1].floatVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-5].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        node->args.push_back(floatNode);
        (yyval.expr) = node;
    }
#line 2435 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 54: /* timeseriesExpression: ATR '(' IDENTIFIER ',' IDENTIFIER ',' IDENTIFIER ',' INTLIT ')'  */
#line 623 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                                      {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ATR_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode1 = new IdentifierNode();
        idNode1->id = *(yyvsp[-7].id);
        IdentifierNode* idNode2 = new IdentifierNode();
        idNode2->id = *(yyvsp[-5].id);
        IdentifierNode* idNode3 = new IdentifierNode();
        idNode3->id = *(yyvsp[-3].id);
        node->args.push_back(idNode1);
        node->args.push_back(idNode2);
        node->args.push_back(idNode3);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2457 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 55: /* timeseriesExpression: SDV '(' IDENTIFIER ',' INTLIT ')'  */
#line 640 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SDV_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2473 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 56: /* timeseriesExpression: MAX '(' IDENTIFIER ',' INTLIT ')'  */
#line 651 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MAX_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2489 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 57: /* timeseriesExpression: MIN '(' IDENTIFIER ',' INTLIT ')'  */
#line 662 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MIN_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2505 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 58: /* timeseriesExpression: SUM '(' IDENTIFIER ',' INTLIT ')'  */
#line 673 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SUM_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2521 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 59: /* timeseriesExpression: MEDIAN '(' IDENTIFIER ',' INTLIT ')'  */
#line 684 "/Users/robinhood/compilers/src/frontend/parser.y"
                                           {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MEDIAN_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id =*(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2537 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 60: /* timeseriesExpression: AVG '(' IDENTIFIER ',' INTLIT ')'  */
#line 695 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::AVG_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2553 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 61: /* timeseriesExpression: ABS '(' IDENTIFIER ',' INTLIT ')'  */
#line 706 "/Users/robinhood/compilers/src/frontend/parser.y"
                                        {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ABS_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2569 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 62: /* timeseriesExpression: CORRELATION '(' IDENTIFIER ',' IDENTIFIER ',' INTLIT ')'  */
#line 717 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                               {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::CORRELATION_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode1 = new IdentifierNode();
        idNode1->id = *(yyvsp[-5].id);
        IdentifierNode* idNode2 = new IdentifierNode();
        idNode2->id = *(yyvsp[-3].id);
        node->args.push_back(idNode1);
        node->args.push_back(idNode2);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2588 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 63: /* timeseriesExpression: SLOPE '(' IDENTIFIER ',' INTLIT ')'  */
#line 731 "/Users/robinhood/compilers/src/frontend/parser.y"
                                          {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SLOPE_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2604 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 64: /* timeseriesExpression: RSQUARED '(' IDENTIFIER ',' INTLIT ')'  */
#line 742 "/Users/robinhood/compilers/src/frontend/parser.y"
                                             {
        TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSQUARED_TS;
        LiteralIntNode* intNode = new LiteralIntNode();
        intNode->value = (yyvsp[-1].intVal);
        IdentifierNode* idNode = new IdentifierNode();
        idNode->id = *(yyvsp[-3].id);
        node->args.push_back(idNode);
        node->args.push_back(intNode);
        (yyval.expr) = node;
    }
#line 2620 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 65: /* postfixExpression: primaryExpression  */
#line 756 "/Users/robinhood/compilers/src/frontend/parser.y"
                        {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 2628 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 66: /* postfixExpression: postfixExpression '[' expression ']'  */
#line 759 "/Users/robinhood/compilers/src/frontend/parser.y"
                                           {
        ArrayAccessNode* arrAccess = new ArrayAccessNode();
        arrAccess->array = (ExprNode*)(yyvsp[-3].expr);
        arrAccess->index = (ExprNode*)(yyvsp[-1].expr);
        (yyval.expr) = arrAccess;
    }
#line 2639 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 67: /* postfixExpression: postfixExpression '(' ')'  */
#line 765 "/Users/robinhood/compilers/src/frontend/parser.y"
                                {
        CallNode* node = new CallNode();
        node->callee = (ExprNode*)(yyvsp[-2].expr);
        (yyval.expr) = node;
    }
#line 2649 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 68: /* postfixExpression: postfixExpression '(' argumentExpressionList ')'  */
#line 770 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                       {
        CallNode* node = new CallNode();
        node->callee = (ExprNode*)(yyvsp[-3].expr);
        node->arguments = *(yyvsp[-1].exprVec);
        (yyval.expr) = node;
    }
#line 2660 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 69: /* postfixExpression: postfixExpression '.' IDENTIFIER  */
#line 776 "/Users/robinhood/compilers/src/frontend/parser.y"
                                       {
        MemberAccessNode* node = new MemberAccessNode();
        node->object = (ExprNode*)(yyvsp[-2].expr);
        node->member = *(yyvsp[0].id);
        (yyval.expr) = node;
    }
#line 2671 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 70: /* postfixExpression: PORTFOLIO_VALUE  */
#line 782 "/Users/robinhood/compilers/src/frontend/parser.y"
                      {
        PortfolioStateNode* node = new PortfolioStateNode();
        node->stateType = PortfolioStateType::PORTFOLIO_VALUE_STATE;
        (yyval.expr) = node;
    }
#line 2681 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 71: /* postfixExpression: CASH_AVAILABLE  */
#line 787 "/Users/robinhood/compilers/src/frontend/parser.y"
                     {
        PortfolioStateNode* node = new PortfolioStateNode();
        node->stateType = PortfolioStateType::CASH_AVAILABLE_STATE;
        (yyval.expr) = node;
    }
#line 2691 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 72: /* postfixExpression: POSITION_SHARES  */
#line 792 "/Users/robinhood/compilers/src/frontend/parser.y"
                      {
        PortfolioStateNode* node = new PortfolioStateNode();
        node->stateType = PortfolioStateType::POSITION_SHARES_STATE;
        (yyval.expr) = node;
    }
#line 2701 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 73: /* postfixExpression: ENTRY_PRICE  */
#line 797 "/Users/robinhood/compilers/src/frontend/parser.y"
                  {
        PortfolioStateNode* node = new PortfolioStateNode();
        node->stateType = PortfolioStateType::ENTRY_PRICE_STATE;
        (yyval.expr) = node;
    }
#line 2711 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 74: /* postfixExpression: DAYS_IN_POSITION  */
#line 802 "/Users/robinhood/compilers/src/frontend/parser.y"
                       {
        PortfolioStateNode* node = new PortfolioStateNode();
        node->stateType = PortfolioStateType::DAYS_IN_POSITION_STATE;
        (yyval.expr) = node;
    }
#line 2721 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 75: /* argumentExpressionList: assignmentExpression  */
#line 810 "/Users/robinhood/compilers/src/frontend/parser.y"
                           {
        (yyval.exprVec) = new vector<ExprNode*>();
        (yyval.exprVec)->push_back((ExprNode*)(yyvsp[0].expr));
    }
#line 2730 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 76: /* argumentExpressionList: argumentExpressionList ',' assignmentExpression  */
#line 814 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                      {
        (yyval.exprVec) = (yyvsp[-2].exprVec);
        (yyval.exprVec)->push_back((ExprNode*)(yyvsp[0].expr));
    }
#line 2739 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 77: /* unaryExpression: postfixExpression  */
#line 821 "/Users/robinhood/compilers/src/frontend/parser.y"
                        {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 2747 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 78: /* unaryExpression: unaryOperator unaryExpression  */
#line 824 "/Users/robinhood/compilers/src/frontend/parser.y"
                                    {
        UnaryExprNode* node = new UnaryExprNode();
        node->operand = (ExprNode*)(yyvsp[0].expr);
        if((yyvsp[-1].intVal)=='+'){
            node->op = UnaryOpType::ADD_OP;
        }
        else if((yyvsp[-1].intVal)=='-'){
            node->op = UnaryOpType::SUB_OP;
        }
        else if((yyvsp[-1].intVal)=='~'){
            node->op = UnaryOpType::BITNOT_OP;
        }
        else if((yyvsp[-1].intVal)=='!'){   
            node->op = UnaryOpType::LOGICALNOT_OP;
        }
        (yyval.expr) = node;
    }
#line 2769 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 79: /* unaryOperator: '+'  */
#line 844 "/Users/robinhood/compilers/src/frontend/parser.y"
          {
        (yyval.intVal) = '+';
    }
#line 2777 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 80: /* unaryOperator: '-'  */
#line 847 "/Users/robinhood/compilers/src/frontend/parser.y"
          {
        (yyval.intVal) = '-';
    }
#line 2785 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 81: /* unaryOperator: '~'  */
#line 850 "/Users/robinhood/compilers/src/frontend/parser.y"
          {
        (yyval.intVal) = '~';
    }
#line 2793 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 82: /* unaryOperator: '!'  */
#line 853 "/Users/robinhood/compilers/src/frontend/parser.y"
          {
        (yyval.intVal) = '!';
    }
#line 2801 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 83: /* multiplicativeExpression: unaryExpression  */
#line 859 "/Users/robinhood/compilers/src/frontend/parser.y"
                      {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 2809 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 84: /* multiplicativeExpression: multiplicativeExpression '*' unaryExpression  */
#line 862 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                   {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "*";
        (yyval.expr) = node;
    }
#line 2821 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 85: /* multiplicativeExpression: multiplicativeExpression '/' unaryExpression  */
#line 869 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                   {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "/";
        (yyval.expr) = node;

    }
#line 2834 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 86: /* multiplicativeExpression: multiplicativeExpression '%' unaryExpression  */
#line 877 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                   {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "%";
        (yyval.expr) = node;
    }
#line 2846 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 87: /* additiveExpression: multiplicativeExpression  */
#line 887 "/Users/robinhood/compilers/src/frontend/parser.y"
                               {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 2854 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 88: /* additiveExpression: additiveExpression '+' multiplicativeExpression  */
#line 890 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                      {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "+";
        (yyval.expr) = node;
    }
#line 2866 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 89: /* additiveExpression: additiveExpression '-' multiplicativeExpression  */
#line 897 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                      {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "-";
        (yyval.expr) = node;
    }
#line 2878 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 90: /* shiftExpression: additiveExpression  */
#line 907 "/Users/robinhood/compilers/src/frontend/parser.y"
                         {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 2886 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 91: /* shiftExpression: shiftExpression LEFT_OP additiveExpression  */
#line 910 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                 {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "<<";
        (yyval.expr) = node;
    }
#line 2898 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 92: /* shiftExpression: shiftExpression RIGHT_OP additiveExpression  */
#line 917 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                  {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = ">>";
        (yyval.expr) = node;
    }
#line 2910 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 93: /* relationalExpression: shiftExpression  */
#line 927 "/Users/robinhood/compilers/src/frontend/parser.y"
                      {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 2918 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 94: /* relationalExpression: relationalExpression '<' shiftExpression  */
#line 930 "/Users/robinhood/compilers/src/frontend/parser.y"
                                               {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "<";
        (yyval.expr) = node;
    }
#line 2930 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 95: /* relationalExpression: relationalExpression '>' shiftExpression  */
#line 937 "/Users/robinhood/compilers/src/frontend/parser.y"
                                               {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = ">";
        (yyval.expr) = node;
    }
#line 2942 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 96: /* relationalExpression: relationalExpression LEQ shiftExpression  */
#line 944 "/Users/robinhood/compilers/src/frontend/parser.y"
                                               {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "<=";
        (yyval.expr) = node;
    }
#line 2954 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 97: /* relationalExpression: relationalExpression GEQ shiftExpression  */
#line 951 "/Users/robinhood/compilers/src/frontend/parser.y"
                                               {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = ">=";
        (yyval.expr) = node;
    }
#line 2966 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 98: /* equalityExpression: relationalExpression  */
#line 961 "/Users/robinhood/compilers/src/frontend/parser.y"
                           {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 2974 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 99: /* equalityExpression: equalityExpression EQ relationalExpression  */
#line 964 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                 {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "==";
        (yyval.expr) = node;
    }
#line 2986 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 100: /* equalityExpression: equalityExpression NEQ relationalExpression  */
#line 971 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                  {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "!=";
        (yyval.expr) = node;
    }
#line 2998 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 101: /* andExpression: equalityExpression  */
#line 981 "/Users/robinhood/compilers/src/frontend/parser.y"
                         {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 3006 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 102: /* andExpression: andExpression '&' equalityExpression  */
#line 984 "/Users/robinhood/compilers/src/frontend/parser.y"
                                           {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "&";
        (yyval.expr) = node;
    }
#line 3018 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 103: /* exclusiveOrExpression: andExpression  */
#line 994 "/Users/robinhood/compilers/src/frontend/parser.y"
                    {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 3026 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 104: /* exclusiveOrExpression: exclusiveOrExpression '^' andExpression  */
#line 997 "/Users/robinhood/compilers/src/frontend/parser.y"
                                              {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "^";
        (yyval.expr) = node;
    }
#line 3038 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 105: /* inclusiveOrExpression: exclusiveOrExpression  */
#line 1007 "/Users/robinhood/compilers/src/frontend/parser.y"
                            {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 3046 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 106: /* inclusiveOrExpression: inclusiveOrExpression '|' exclusiveOrExpression  */
#line 1010 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                      {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "|";
        (yyval.expr) = node;
    }
#line 3058 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 107: /* logicalAndExpression: inclusiveOrExpression  */
#line 1020 "/Users/robinhood/compilers/src/frontend/parser.y"
                            {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 3066 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 108: /* logicalAndExpression: logicalAndExpression AND inclusiveOrExpression  */
#line 1023 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                     {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "AND";
        (yyval.expr) = node;
    }
#line 3078 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 109: /* logicalOrExpression: logicalAndExpression  */
#line 1033 "/Users/robinhood/compilers/src/frontend/parser.y"
                           {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 3086 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 110: /* logicalOrExpression: logicalOrExpression OR logicalAndExpression  */
#line 1036 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                  {
        BinaryExprNode* node = new BinaryExprNode();
        node->leftOperand = (yyvsp[-2].expr);
        node->rightOperand = (yyvsp[0].expr);
        node->op = "OR";
        (yyval.expr) = node;
    }
#line 3098 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 111: /* conditionalExpression: logicalOrExpression  */
#line 1046 "/Users/robinhood/compilers/src/frontend/parser.y"
                          {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 3106 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 112: /* conditionalExpression: logicalOrExpression '?' expression ':' conditionalExpression  */
#line 1049 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                                   {
        ConditionalExprNode* node = new ConditionalExprNode();
        node->condition = (yyvsp[-4].expr);
        node->thenExpr = (yyvsp[-2].expr);
        node->elseExpr = (yyvsp[0].expr);
        (yyval.expr) = node;
    }
#line 3118 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 113: /* assignmentExpression: conditionalExpression  */
#line 1059 "/Users/robinhood/compilers/src/frontend/parser.y"
                            {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 3126 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 114: /* assignmentExpression: unaryExpression '=' assignmentExpression  */
#line 1062 "/Users/robinhood/compilers/src/frontend/parser.y"
                                               {
        AssignmentNode* node = new AssignmentNode();
        node->target = (yyvsp[-2].expr);
        node->value = (yyvsp[0].expr);
        (yyval.expr) = node;
    }
#line 3137 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 115: /* expression: assignmentExpression  */
#line 1071 "/Users/robinhood/compilers/src/frontend/parser.y"
                           {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 3145 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 116: /* expression: expression ',' assignmentExpression  */
#line 1074 "/Users/robinhood/compilers/src/frontend/parser.y"
                                          {
        CommaExprNode* node;

        if((yyvsp[-2].expr)->nodeType == ASTNodeType::CommaExprNode){
            node = (CommaExprNode*)(yyvsp[-2].expr);
        }
        else{
            node = new CommaExprNode();
            node->expressions.push_back((ExprNode*)(yyvsp[-2].expr));
        }
        node->expressions.push_back((ExprNode*)(yyvsp[0].expr));
        (yyval.expr) = node;
    }
#line 3163 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 117: /* declaration: declarationSpecifiers ';'  */
#line 1090 "/Users/robinhood/compilers/src/frontend/parser.y"
                                {
        DeclNode* node = new DeclNode();
        node->type = (yyvsp[-1].type);
        (yyval.decl) = node;
    }
#line 3173 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 118: /* declaration: declarationSpecifiers initDeclaratorList ';'  */
#line 1095 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                   {
    DeclNode* node = new DeclNode();
    node->type = (yyvsp[-2].type);
    node->decls = *(yyvsp[-1].initDeclVec);
    (yyval.decl) = node;

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

            for (int size : d->arraySizes) {
                if(size > 0)
                {
                    dims.push_back(size);
                }
                else
                {
                    std::cerr << "Error: line " << yylineno << ": array dimension for '" << name << "' must be a positive integer.\n";
                    all_dims_valid = false;
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
                std::string groupType = node->type ? node->type->id : "";

                auto groupVarSym = std::make_unique<GroupSym>(name, yylineno, col-1);
                
                groupVarSym->groupTypeName = groupType; 

                if (!symtab.currentScope->define(std::move(groupVarSym))) {
                    std::cerr << "Error: redeclaration of group variable '" << name << "' at line " << yylineno << "\n";
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
#line 3325 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 119: /* declarationSpecifiers: typeSpecifier  */
#line 1245 "/Users/robinhood/compilers/src/frontend/parser.y"
                    {
        (yyval.type) = (yyvsp[0].type);
    }
#line 3333 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 120: /* declarationSpecifiers: CONST typeSpecifier  */
#line 1248 "/Users/robinhood/compilers/src/frontend/parser.y"
                          {
        (yyval.type) = (yyvsp[0].type);
        (yyval.type)->constFlag = true;
    }
#line 3342 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 121: /* initDeclaratorList: initDeclarator  */
#line 1255 "/Users/robinhood/compilers/src/frontend/parser.y"
                     {
        vector<InitDeclarator*>* initVec = new vector<InitDeclarator*>();
        initVec->push_back((yyvsp[0].initDecl));
        (yyval.initDeclVec) = initVec;
    }
#line 3352 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 122: /* initDeclaratorList: initDeclaratorList ',' initDeclarator  */
#line 1260 "/Users/robinhood/compilers/src/frontend/parser.y"
                                            {
        (yyval.initDeclVec) = (yyvsp[-2].initDeclVec);
        (yyval.initDeclVec)->push_back((yyvsp[0].initDecl));
    }
#line 3361 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 123: /* initDeclarator: directDeclarator  */
#line 1267 "/Users/robinhood/compilers/src/frontend/parser.y"
                        {
        (yyval.initDecl) = new InitDeclarator();
        (yyval.initDecl)->declarator = (yyvsp[0].declarator);
    }
#line 3370 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 124: /* initDeclarator: directDeclarator '=' initializer  */
#line 1271 "/Users/robinhood/compilers/src/frontend/parser.y"
                                       {
        (yyval.initDecl) = new InitDeclarator();
        (yyval.initDecl)->declarator = (yyvsp[-2].declarator);
        (yyval.initDecl)->initializer = (yyvsp[0].init);
    }
#line 3380 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 125: /* typeSpecifier: VOID  */
#line 1280 "/Users/robinhood/compilers/src/frontend/parser.y"
           {
        TypeNode* node = new TypeNode();
        node->type = DataTypes::VOID_TYPE;
        (yyval.type) = node;
    }
#line 3390 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 126: /* typeSpecifier: INT  */
#line 1285 "/Users/robinhood/compilers/src/frontend/parser.y"
           {
        TypeNode* node = new TypeNode();
        node->type = DataTypes::INT_TYPE;
        (yyval.type) = node;
    }
#line 3400 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 127: /* typeSpecifier: FLOAT  */
#line 1290 "/Users/robinhood/compilers/src/frontend/parser.y"
            {
        TypeNode* node = new TypeNode();
        node->type = DataTypes::FLOAT_TYPE;
        (yyval.type) = node;
    }
#line 3410 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 128: /* typeSpecifier: BOOL  */
#line 1295 "/Users/robinhood/compilers/src/frontend/parser.y"
           {
        TypeNode* node = new TypeNode();
        node->type = DataTypes::BOOL_TYPE;
        (yyval.type) = node;
    }
#line 3420 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 129: /* typeSpecifier: RGM  */
#line 1300 "/Users/robinhood/compilers/src/frontend/parser.y"
          {
        TypeNode* node = new TypeNode();
        node->type = DataTypes::RGM_TYPE;
        (yyval.type) = node;
    }
#line 3430 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 130: /* typeSpecifier: TIMESERIES  */
#line 1305 "/Users/robinhood/compilers/src/frontend/parser.y"
                 {
        TypeNode* node = new TypeNode();
        node->type = DataTypes::TIMESERIES_TYPE;
        (yyval.type) = node;
    }
#line 3440 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 131: /* typeSpecifier: groupSpecifier  */
#line 1310 "/Users/robinhood/compilers/src/frontend/parser.y"
                     {
        TypeNode* node = new TypeNode();
        node->type = DataTypes::GROUP_TYPE;
        node->userDefinedFlag = true;

        GroupNode* qnode = (GroupNode*)(yyvsp[0].group);
        if (qnode) {
             node->id = qnode->id;
        }

        (yyval.type) = node;
    }
#line 3457 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 132: /* groupSpecifier: GROUP IDENTIFIER '{' groupDeclarationList '}'  */
#line 1325 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                    {
        GroupNode* node = new GroupNode();
        node->id = *(yyvsp[-3].id);
        node->members = *(yyvsp[-1].groupDeclList);
        (yyval.group) = node;

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
#line 3518 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 133: /* groupSpecifier: GROUP IDENTIFIER  */
#line 1381 "/Users/robinhood/compilers/src/frontend/parser.y"
                       {
        GroupNode* node = new GroupNode();
        node->id = *(yyvsp[0].id);
        (yyval.group) = node;
    }
#line 3528 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 134: /* groupDeclarationList: groupDeclaration  */
#line 1389 "/Users/robinhood/compilers/src/frontend/parser.y"
                       {
        vector<GroupDeclaration*>* vec = new vector<GroupDeclaration*>();
        vec->push_back((yyvsp[0].groupDeclaration));
        (yyval.groupDeclList) = vec;
    }
#line 3538 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 135: /* groupDeclarationList: groupDeclarationList groupDeclaration  */
#line 1394 "/Users/robinhood/compilers/src/frontend/parser.y"
                                            {
        (yyval.groupDeclList) = (yyvsp[-1].groupDeclList);
        (yyval.groupDeclList)->push_back((yyvsp[0].groupDeclaration));
    }
#line 3547 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 136: /* groupDeclaration: declarationSpecifiers groupDeclaratorList ';'  */
#line 1401 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                    {
        GroupDeclaration* node = new GroupDeclaration();
        node->type= (yyvsp[-2].type);
        node->declarators = *(yyvsp[-1].groupDeclaratorList);
        (yyval.groupDeclaration) = node;
    }
#line 3558 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 137: /* groupDeclaratorList: groupDeclarator  */
#line 1410 "/Users/robinhood/compilers/src/frontend/parser.y"
                      {
        vector<GroupDeclarator*>* groupDeclVec = new vector<GroupDeclarator*>();
        groupDeclVec->push_back((yyvsp[0].groupDeclarator));
        (yyval.groupDeclaratorList) = groupDeclVec;
    }
#line 3568 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 138: /* groupDeclaratorList: groupDeclaratorList ',' groupDeclarator  */
#line 1415 "/Users/robinhood/compilers/src/frontend/parser.y"
                                              {
        (yyval.groupDeclaratorList) = (yyvsp[-2].groupDeclaratorList);
        (yyval.groupDeclaratorList)->push_back((yyvsp[0].groupDeclarator));
    }
#line 3577 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 139: /* groupDeclarator: directDeclarator  */
#line 1423 "/Users/robinhood/compilers/src/frontend/parser.y"
                           {
		GroupDeclarator* node = new GroupDeclarator();
        node->declarator = (yyvsp[0].declarator);
        (yyval.groupDeclarator) = node;
	}
#line 3587 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 140: /* directDeclarator: IDENTIFIER  */
#line 1431 "/Users/robinhood/compilers/src/frontend/parser.y"
                 {
        Declarator* node = new Declarator();
        node->id = *(yyvsp[0].id);
        (yyval.declarator) = node;
    }
#line 3597 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 141: /* directDeclarator: directDeclarator '[' INTLIT ']'  */
#line 1436 "/Users/robinhood/compilers/src/frontend/parser.y"
                                      {
        (yyval.declarator) = (yyvsp[-3].declarator);
        (yyval.declarator)->arrayFlag = true;
        (yyval.declarator)->arraySizes.push_back((yyvsp[-1].intVal));
    }
#line 3607 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 142: /* parameterList: parameterDeclaration  */
#line 1444 "/Users/robinhood/compilers/src/frontend/parser.y"
                           {
        vector<ParamNode*>* paramList = new vector<ParamNode*>();
        paramList->push_back((yyvsp[0].param));
        (yyval.paramVec) = paramList;
    }
#line 3617 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 143: /* parameterList: parameterList ',' parameterDeclaration  */
#line 1449 "/Users/robinhood/compilers/src/frontend/parser.y"
                                             {
        (yyval.paramVec) = (yyvsp[-2].paramVec);
        (yyval.paramVec)->push_back((yyvsp[0].param));
    }
#line 3626 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 144: /* parameterDeclaration: declarationSpecifiers directDeclarator  */
#line 1456 "/Users/robinhood/compilers/src/frontend/parser.y"
                                             {
        ParamNode* node = new ParamNode();
        node->type = (yyvsp[-1].type);
        node->declarator = (yyvsp[0].declarator);
        (yyval.param) = node;
    }
#line 3637 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 145: /* parameterDeclaration: declarationSpecifiers  */
#line 1462 "/Users/robinhood/compilers/src/frontend/parser.y"
                            {
        ParamNode* node = new ParamNode();
        node->type = (yyvsp[0].type);
        node->declarator = nullptr;
        (yyval.param) = node;
    }
#line 3648 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 146: /* initializer: assignmentExpression  */
#line 1471 "/Users/robinhood/compilers/src/frontend/parser.y"
                           {
        Initializer* node = new Initializer();
        node->expr = (yyvsp[0].expr);
        (yyval.init) = node;
    }
#line 3658 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 147: /* initializer: '{' initializerList '}'  */
#line 1476 "/Users/robinhood/compilers/src/frontend/parser.y"
                              {
        Initializer* node = new Initializer();
        node->initializerList = *(yyvsp[-1].initList);
        (yyval.init) = node;
    }
#line 3668 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 148: /* initializerList: initializer  */
#line 1484 "/Users/robinhood/compilers/src/frontend/parser.y"
                  {
        vector<Initializer*>* initVec = new vector<Initializer*>();
        initVec->push_back((yyvsp[0].init));
        (yyval.initList) = initVec;
    }
#line 3678 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 149: /* initializerList: initializerList ',' initializer  */
#line 1489 "/Users/robinhood/compilers/src/frontend/parser.y"
                                      {
        (yyval.initList) = (yyvsp[-2].initList);
        (yyval.initList)->push_back((yyvsp[0].init));
    }
#line 3687 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 150: /* statement: compoundStatement  */
#line 1496 "/Users/robinhood/compilers/src/frontend/parser.y"
                        {
        (yyval.stmt) = (yyvsp[0].stmt);
    }
#line 3695 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 151: /* statement: expressionStatement  */
#line 1499 "/Users/robinhood/compilers/src/frontend/parser.y"
                          {
        (yyval.stmt) = (yyvsp[0].stmt);
    }
#line 3703 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 152: /* statement: selectionStatement  */
#line 1502 "/Users/robinhood/compilers/src/frontend/parser.y"
                         {
        (yyval.stmt) = (yyvsp[0].stmt);
    }
#line 3711 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 153: /* statement: iterationStatement  */
#line 1505 "/Users/robinhood/compilers/src/frontend/parser.y"
                         {
        (yyval.stmt) = (yyvsp[0].stmt);
    }
#line 3719 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 154: /* statement: jumpStatement  */
#line 1508 "/Users/robinhood/compilers/src/frontend/parser.y"
                    {
        (yyval.stmt) = (yyvsp[0].stmt);
    }
#line 3727 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 155: /* blockItem: declaration  */
#line 1514 "/Users/robinhood/compilers/src/frontend/parser.y"
                  {
        (yyval.node) = (ASTNode*)(yyvsp[0].decl);
    }
#line 3735 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 156: /* blockItem: statement  */
#line 1517 "/Users/robinhood/compilers/src/frontend/parser.y"
                {
        (yyval.node) = (ASTNode*)(yyvsp[0].stmt);
    }
#line 3743 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 157: /* blockItemList: %empty  */
#line 1524 "/Users/robinhood/compilers/src/frontend/parser.y"
                  {
        (yyval.nodeList) = new std::vector<ASTNode*>();
    }
#line 3751 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 158: /* blockItemList: blockItemList blockItem  */
#line 1527 "/Users/robinhood/compilers/src/frontend/parser.y"
                              {
        (yyval.nodeList) = (yyvsp[-1].nodeList);
        (yyval.nodeList)->push_back((yyvsp[0].node));
    }
#line 3760 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 159: /* $@3: %empty  */
#line 1534 "/Users/robinhood/compilers/src/frontend/parser.y"
          {
        symtab.enterScope();
    }
#line 3768 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 160: /* compoundStatement: '{' $@3 blockItemList '}'  */
#line 1536 "/Users/robinhood/compilers/src/frontend/parser.y"
                        {
        CmpdStmtNode* node = new CmpdStmtNode();
        for (ASTNode* item : *(yyvsp[-1].nodeList)) {
            if (!item) continue;
            if (item->nodeType == ASTNodeType::DeclNode) {
                node->declarations.push_back((DeclNode*)item);
            }
            else {
                node->statements.push_back((StmtNode*)item);
            }
        }
        delete (yyvsp[-1].nodeList);
        (yyval.stmt) = node;
        symtab.exitScope();
    }
#line 3788 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 161: /* expressionStatement: ';'  */
#line 1554 "/Users/robinhood/compilers/src/frontend/parser.y"
          {
        ExprStmtNode* node = new ExprStmtNode();
        (yyval.stmt) = (StmtNode*)node;
    }
#line 3797 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 162: /* expressionStatement: expression ';'  */
#line 1558 "/Users/robinhood/compilers/src/frontend/parser.y"
                     {
        ExprStmtNode* node = new ExprStmtNode();
        node->expr = (yyvsp[-1].expr);
        (yyval.stmt) = (StmtNode*)node;
    }
#line 3807 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 163: /* selectionStatement: IF '(' expression ')' statement  */
#line 1566 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                            {
        IfNode* node = new IfNode();
        node->condition = (yyvsp[-2].expr);
        node->thenBranch = (yyvsp[0].stmt);
        (yyval.stmt) = (StmtNode*)node;
    }
#line 3818 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 164: /* selectionStatement: IF '(' expression ')' statement ELSE statement  */
#line 1572 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                     {
        IfNode* node = new IfNode();
        node->condition = (yyvsp[-4].expr);
        node->thenBranch = (yyvsp[-2].stmt);
        node->elseBranch = (yyvsp[0].stmt);
        (yyval.stmt) = (StmtNode*)node;
    }
#line 3830 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 165: /* iterationStatement: WHILE '(' expression ')' statement  */
#line 1582 "/Users/robinhood/compilers/src/frontend/parser.y"
                                         {
        WhileNode* node = new WhileNode();
        node->condition = (yyvsp[-2].expr);
        node->body = (yyvsp[0].stmt);
        (yyval.stmt) = (StmtNode*)node;
    }
#line 3841 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 166: /* $@4: %empty  */
#line 1589 "/Users/robinhood/compilers/src/frontend/parser.y"
            { symtab.enterScope(); }
#line 3847 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 167: /* iterationStatement: FOR '(' $@4 forInitStatement optionalExpression ';' optionalExpression ')' statement  */
#line 1593 "/Users/robinhood/compilers/src/frontend/parser.y"
                    {
        
        ForNode* node = new ForNode();
        node->init = (yyvsp[-5].node); 
        node->condition = (yyvsp[-4].expr); 
        node->increment = (yyvsp[-2].expr); 
        node->body = (yyvsp[0].stmt); 
        
        (yyval.stmt) = (StmtNode*)node;
        symtab.exitScope();
    }
#line 3863 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 168: /* forInitStatement: expressionStatement  */
#line 1607 "/Users/robinhood/compilers/src/frontend/parser.y"
                          { (yyval.node) = (yyvsp[0].stmt); }
#line 3869 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 169: /* forInitStatement: declaration  */
#line 1608 "/Users/robinhood/compilers/src/frontend/parser.y"
                  { (yyval.node) = (yyvsp[0].decl); }
#line 3875 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 170: /* optionalExpression: %empty  */
#line 1612 "/Users/robinhood/compilers/src/frontend/parser.y"
      { (yyval.expr) = NULL; }
#line 3881 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 171: /* optionalExpression: expression  */
#line 1613 "/Users/robinhood/compilers/src/frontend/parser.y"
                 { (yyval.expr) = (yyvsp[0].expr); }
#line 3887 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 172: /* jumpStatement: CONTINUE ';'  */
#line 1617 "/Users/robinhood/compilers/src/frontend/parser.y"
                   {
        ContinueNode* node = new ContinueNode();
        (yyval.stmt) = (StmtNode*)node;
    }
#line 3896 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 173: /* jumpStatement: BREAK ';'  */
#line 1621 "/Users/robinhood/compilers/src/frontend/parser.y"
                {
        BreakNode* node = new BreakNode();
        (yyval.stmt) = (StmtNode*)node;
    }
#line 3905 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 174: /* jumpStatement: RETURN ';'  */
#line 1625 "/Users/robinhood/compilers/src/frontend/parser.y"
                 {
        ReturnNode* node = new ReturnNode();
        (yyval.stmt) = (StmtNode*)node;
    }
#line 3914 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 175: /* jumpStatement: RETURN expression ';'  */
#line 1629 "/Users/robinhood/compilers/src/frontend/parser.y"
                            {
        ReturnNode* node = new ReturnNode();
        node->expr = (yyvsp[-1].expr);
        (yyval.stmt) = (StmtNode*)node;
    }
#line 3924 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 176: /* globalDeclaration: function_definition  */
#line 1637 "/Users/robinhood/compilers/src/frontend/parser.y"
                          {
        (yyval.node) = (ASTNode*)(yyvsp[0].func);
    }
#line 3932 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 177: /* globalDeclaration: declaration  */
#line 1640 "/Users/robinhood/compilers/src/frontend/parser.y"
                  {
        (yyval.node) = (ASTNode*)(yyvsp[0].decl);
    }
#line 3940 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 178: /* globalDeclaration: strategyDefinition  */
#line 1643 "/Users/robinhood/compilers/src/frontend/parser.y"
                         {
        (yyval.node) = (ASTNode*)(yyvsp[0].strategy);
    }
#line 3948 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 179: /* $@5: %empty  */
#line 1649 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                 {
        std::string fname = *(yyvsp[-4].id);
         auto funcSym = std::make_unique<FunctionSym>(fname, yylineno, col-1);
        TypeNode* retType = (yyvsp[-1].type);
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
            case DataTypes::VOID_TYPE:
                funcSym->returnType = std::make_unique<Symbol>("<ret>", SymKind::Void, yylineno, col-1);
                break;
            default:
                funcSym->returnType = std::make_unique<Symbol>("<ret>", SymKind::Array, yylineno, col-1);
                break;
        }

        if (!symtab.currentScope->define(std::move(funcSym))) {
            std::cerr << "Error: redeclaration of function '" << fname << "' at line " << yylineno << "\n";
        }

        
        symtab.enterScope();
    }
#line 3985 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 180: /* function_definition: FUN IDENTIFIER '(' ARROW typeSpecifier ')' $@5 compoundStatement  */
#line 1680 "/Users/robinhood/compilers/src/frontend/parser.y"
                        {
        FuncNode* node = new FuncNode();
        node->name = *(yyvsp[-6].id);
        node->returnType = (yyvsp[-3].type);
        node->body = (CmpdStmtNode*)(yyvsp[0].stmt);
        (yyval.func) = node;

        symtab.exitScope();
    }
#line 3999 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 181: /* $@6: %empty  */
#line 1689 "/Users/robinhood/compilers/src/frontend/parser.y"
                                                               {
        std::string fname = *(yyvsp[-5].id);

        auto funcSym = std::make_unique<FunctionSym>(fname, yylineno, col-1);

        TypeNode* retType = (yyvsp[-1].type);
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
            case DataTypes::VOID_TYPE:
                funcSym->returnType = std::make_unique<Symbol>("<ret>", SymKind::Void, yylineno, col-1);
                break;
            default:
                funcSym->returnType = std::make_unique<Symbol>("<ret>", SymKind::Array, yylineno, col-1);
                break;
        }

        for (ParamNode* p : *(yyvsp[-3].paramVec)) {
            if (!p || !p->type || !p->declarator) continue;
            
            std::string pname = p->declarator->id;
            DataTypes pdt = p->type->type;
            bool isConst = p->type->constFlag;

            if (p->declarator->arrayFlag) {
                std::vector<int> dims;
                for (int size : p->declarator->arraySizes) {
                    dims.push_back(size);
                }
                funcSym->parameters.push_back(std::make_unique<ArraySym>(pname, dims, pdt, isConst, yylineno, col-1));
            } else {
                switch (pdt) {
                    case DataTypes::INT_TYPE:
                        funcSym->parameters.push_back(std::make_unique<IntSym>(pname, 0, isConst, yylineno, col-1));
                        break;
                    case DataTypes::FLOAT_TYPE:
                        funcSym->parameters.push_back(std::make_unique<FloatSym>(pname, 0.0, isConst, yylineno, col-1));
                        break;
                    case DataTypes::BOOL_TYPE:
                        funcSym->parameters.push_back(std::make_unique<BoolSym>(pname, false, isConst, yylineno, col-1));
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

        for (ParamNode* p : *(yyvsp[-3].paramVec)) {
            if (!p || !p->type || !p->declarator) continue;

            std::string pname = p->declarator->id;
            DataTypes pdt = p->type->type;
            bool isConst = p->type->constFlag;

            if (p->declarator->arrayFlag) {
                std::vector<int> dims;
                for (int size : p->declarator->arraySizes) {
                    dims.push_back(size);
                }
                if (!symtab.currentScope->define(std::make_unique<ArraySym>(pname, dims, pdt, isConst, yylineno, col-1))) {
                    std::cerr << "Error: redeclaration of param '" << pname << "' at line " << yylineno << "\n";
                }
            } 
            else {
            switch (pdt) {
                    case DataTypes::INT_TYPE:
                        if (!symtab.currentScope->define(std::make_unique<IntSym>(pname, 0, isConst, yylineno, col-1)))
                            std::cerr << "Error: redeclaration of param '" << pname << "' at line " << yylineno << "\n";
                            break;
                    case DataTypes::FLOAT_TYPE:
                        if (!symtab.currentScope->define(std::make_unique<FloatSym>(pname, 0.0, isConst, yylineno, col-1)))
                            std::cerr << "Error: redeclaration of param '" << pname << "' at line " << yylineno << "\n";
                            break;
                    case DataTypes::BOOL_TYPE:
                        if (!symtab.currentScope->define(std::make_unique<BoolSym>(pname, false, isConst, yylineno, col-1)))
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

    }
#line 4114 "/Users/robinhood/compilers/build/parser.tab.c"
    break;

  case 182: /* function_definition: FUN IDENTIFIER '(' parameterList ARROW typeSpecifier ')' $@6 compoundStatement  */
#line 1798 "/Users/robinhood/compilers/src/frontend/parser.y"
                        {
        FuncNode* node = new FuncNode();
        node->name = *(yyvsp[-7].id);
        node->returnType = (yyvsp[-3].type);
        node->params = *(yyvsp[-5].paramVec);
        node->body = (CmpdStmtNode*)(yyvsp[0].stmt);
        (yyval.func) = node;

        symtab.exitScope();
    }
#line 4129 "/Users/robinhood/compilers/build/parser.tab.c"
    break;


#line 4133 "/Users/robinhood/compilers/build/parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1812 "/Users/robinhood/compilers/src/frontend/parser.y"



void yyerror(const char *s) {
    fprintf(stderr, "\nError: %s at line %d, column %d, near '%s'\n", s, yylineno, col - 1, yytext);
}

int main() {
    yyin = fopen("./input.txt", "r");
    if (!yyin) {
        perror("File not found\n");
        return 1;
    }

    MLIRCodegenVisitor visitor;

    if (yyparse() == 0) {
        cout << "--- Parse Successful ---" << endl;
        SemanticVisitor semVisitor;
        progRoot->visitAcceptor(semVisitor);
        semVisitor.printErrors();

        if (progRoot) {

            mlir::ModuleOp module = visitor.getModule();
            visitor.setInsertionPointToStart(visitor.getModuleBody());

            for (auto& decl : progRoot->globalDeclarations) {
                if (decl) visitor.visit(*decl);
            }
            
            for (auto& func : progRoot->functions) {
                if (func) visitor.visit(*func);
            }

        } else {
            cout << "Empty program!" << endl;
            return 1;
        }

        mlir::ModuleOp module = visitor.getModule();

        if (mlir::failed(mlir::verify(module))) {
            cerr << "--- MLIR Verification FAILED ---" << endl;
            module.print(llvm::errs()); // Print bad MLIR to stderr
            return -1;
        }

        cout << "--- MLIR Verification Succeeded ---" << endl;
        
        module.print(llvm::outs());

    } else {
        cout << "Parse Failed" << endl;
    }

    fclose(yyin);
    return 0;
}
