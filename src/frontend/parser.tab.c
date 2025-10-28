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
#line 5 "parser.y"

#include <iostream>
#include <string>
#include "ast.h"

using namespace std;

extern FILE *yyin;
extern int col;
int yyparse(void);
int yylex();
void yyerror(const char* s);
extern int yylineno;
extern char *yytext;

ProgramNode* progRoot;

#line 89 "parser.tab.c"

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
  YYSYMBOL_REF = 10,                       /* REF  */
  YYSYMBOL_SCOPE = 11,                     /* SCOPE  */
  YYSYMBOL_ARROW = 12,                     /* ARROW  */
  YYSYMBOL_ENTRYLONG = 13,                 /* ENTRYLONG  */
  YYSYMBOL_ENTRYSHORT = 14,                /* ENTRYSHORT  */
  YYSYMBOL_EXITLONG = 15,                  /* EXITLONG  */
  YYSYMBOL_EXITSHORT = 16,                 /* EXITSHORT  */
  YYSYMBOL_OPEN = 17,                      /* OPEN  */
  YYSYMBOL_CLOSE = 18,                     /* CLOSE  */
  YYSYMBOL_HIGH = 19,                      /* HIGH  */
  YYSYMBOL_LOW = 20,                       /* LOW  */
  YYSYMBOL_VOLUME = 21,                    /* VOLUME  */
  YYSYMBOL_POSITION_SHARES = 22,           /* POSITION_SHARES  */
  YYSYMBOL_ENTRY_PRICE = 23,               /* ENTRY_PRICE  */
  YYSYMBOL_DAYS_IN_POSITION = 24,          /* DAYS_IN_POSITION  */
  YYSYMBOL_PORTFOLIO_VALUE = 25,           /* PORTFOLIO_VALUE  */
  YYSYMBOL_CASH_AVAILABLE = 26,            /* CASH_AVAILABLE  */
  YYSYMBOL_SMA = 27,                       /* SMA  */
  YYSYMBOL_EMA = 28,                       /* EMA  */
  YYSYMBOL_RSI = 29,                       /* RSI  */
  YYSYMBOL_BB = 30,                        /* BB  */
  YYSYMBOL_ATR = 31,                       /* ATR  */
  YYSYMBOL_SDV = 32,                       /* SDV  */
  YYSYMBOL_MAX = 33,                       /* MAX  */
  YYSYMBOL_MIN = 34,                       /* MIN  */
  YYSYMBOL_SUM = 35,                       /* SUM  */
  YYSYMBOL_MEDIAN = 36,                    /* MEDIAN  */
  YYSYMBOL_AVG = 37,                       /* AVG  */
  YYSYMBOL_ABS = 38,                       /* ABS  */
  YYSYMBOL_CORRELATION = 39,               /* CORRELATION  */
  YYSYMBOL_SLOPE = 40,                     /* SLOPE  */
  YYSYMBOL_RSQUARED = 41,                  /* RSQUARED  */
  YYSYMBOL_GROUP = 42,                     /* GROUP  */
  YYSYMBOL_FOR = 43,                       /* FOR  */
  YYSYMBOL_WHILE = 44,                     /* WHILE  */
  YYSYMBOL_IF = 45,                        /* IF  */
  YYSYMBOL_ELSE = 46,                      /* ELSE  */
  YYSYMBOL_CONTINUE = 47,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 48,                     /* BREAK  */
  YYSYMBOL_RETURN = 49,                    /* RETURN  */
  YYSYMBOL_INT = 50,                       /* INT  */
  YYSYMBOL_FLOAT = 51,                     /* FLOAT  */
  YYSYMBOL_BOOL = 52,                      /* BOOL  */
  YYSYMBOL_VOID = 53,                      /* VOID  */
  YYSYMBOL_STRING = 54,                    /* STRING  */
  YYSYMBOL_RGM = 55,                       /* RGM  */
  YYSYMBOL_CONST = 56,                     /* CONST  */
  YYSYMBOL_TIMESERIES = 57,                /* TIMESERIES  */
  YYSYMBOL_AND = 58,                       /* AND  */
  YYSYMBOL_OR = 59,                        /* OR  */
  YYSYMBOL_LEFT_OP = 60,                   /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 61,                  /* RIGHT_OP  */
  YYSYMBOL_LEQ = 62,                       /* LEQ  */
  YYSYMBOL_GEQ = 63,                       /* GEQ  */
  YYSYMBOL_EQ = 64,                        /* EQ  */
  YYSYMBOL_NEQ = 65,                       /* NEQ  */
  YYSYMBOL_IDENTIFIER = 66,                /* IDENTIFIER  */
  YYSYMBOL_STRINGLIT = 67,                 /* STRINGLIT  */
  YYSYMBOL_INTLIT = 68,                    /* INTLIT  */
  YYSYMBOL_FLOATLIT = 69,                  /* FLOATLIT  */
  YYSYMBOL_LOWER_THAN_ELSE = 70,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_71_ = 71,                       /* '{'  */
  YYSYMBOL_72_ = 72,                       /* '}'  */
  YYSYMBOL_73_ = 73,                       /* '='  */
  YYSYMBOL_74_ = 74,                       /* ';'  */
  YYSYMBOL_75_ = 75,                       /* ','  */
  YYSYMBOL_76_ = 76,                       /* '('  */
  YYSYMBOL_77_ = 77,                       /* ')'  */
  YYSYMBOL_78_ = 78,                       /* '['  */
  YYSYMBOL_79_ = 79,                       /* ']'  */
  YYSYMBOL_80_ = 80,                       /* '.'  */
  YYSYMBOL_81_ = 81,                       /* '+'  */
  YYSYMBOL_82_ = 82,                       /* '-'  */
  YYSYMBOL_83_ = 83,                       /* '~'  */
  YYSYMBOL_84_ = 84,                       /* '!'  */
  YYSYMBOL_85_ = 85,                       /* '*'  */
  YYSYMBOL_86_ = 86,                       /* '/'  */
  YYSYMBOL_87_ = 87,                       /* '%'  */
  YYSYMBOL_88_ = 88,                       /* '<'  */
  YYSYMBOL_89_ = 89,                       /* '>'  */
  YYSYMBOL_90_ = 90,                       /* '&'  */
  YYSYMBOL_91_ = 91,                       /* '^'  */
  YYSYMBOL_92_ = 92,                       /* '|'  */
  YYSYMBOL_93_ = 93,                       /* '?'  */
  YYSYMBOL_94_ = 94,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 95,                  /* $accept  */
  YYSYMBOL_translationUnit = 96,           /* translationUnit  */
  YYSYMBOL_strategyDefinition = 97,        /* strategyDefinition  */
  YYSYMBOL_strategyBody = 98,              /* strategyBody  */
  YYSYMBOL_strategyDeclarations = 99,      /* strategyDeclarations  */
  YYSYMBOL_indicatorSection = 100,         /* indicatorSection  */
  YYSYMBOL_regimeSection = 101,            /* regimeSection  */
  YYSYMBOL_signalFunctionList = 102,       /* signalFunctionList  */
  YYSYMBOL_signalFunction = 103,           /* signalFunction  */
  YYSYMBOL_primaryExpression = 104,        /* primaryExpression  */
  YYSYMBOL_timeseries = 105,               /* timeseries  */
  YYSYMBOL_timeseriesExpression = 106,     /* timeseriesExpression  */
  YYSYMBOL_postfixExpression = 107,        /* postfixExpression  */
  YYSYMBOL_argumentExpressionList = 108,   /* argumentExpressionList  */
  YYSYMBOL_unaryExpression = 109,          /* unaryExpression  */
  YYSYMBOL_unaryOperator = 110,            /* unaryOperator  */
  YYSYMBOL_castExpression = 111,           /* castExpression  */
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
  YYSYMBOL_group_declarationList = 131,    /* group_declarationList  */
  YYSYMBOL_group_declaration = 132,        /* group_declaration  */
  YYSYMBOL_specifier_qualifierList = 133,  /* specifier_qualifierList  */
  YYSYMBOL_group_declaratorList = 134,     /* group_declaratorList  */
  YYSYMBOL_group_declarator = 135,         /* group_declarator  */
  YYSYMBOL_direct_declarator = 136,        /* direct_declarator  */
  YYSYMBOL_parameterList = 137,            /* parameterList  */
  YYSYMBOL_parameter_declaration = 138,    /* parameter_declaration  */
  YYSYMBOL_identifierList = 139,           /* identifierList  */
  YYSYMBOL_type_name = 140,                /* type_name  */
  YYSYMBOL_direct_abstract_declarator = 141, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 142,              /* initializer  */
  YYSYMBOL_initializerList = 143,          /* initializerList  */
  YYSYMBOL_statement = 144,                /* statement  */
  YYSYMBOL_compoundStatement = 145,        /* compoundStatement  */
  YYSYMBOL_declarationList = 146,          /* declarationList  */
  YYSYMBOL_statementList = 147,            /* statementList  */
  YYSYMBOL_expressionStatement = 148,      /* expressionStatement  */
  YYSYMBOL_selectionStatement = 149,       /* selectionStatement  */
  YYSYMBOL_iterationStatement = 150,       /* iterationStatement  */
  YYSYMBOL_jumpStatement = 151,            /* jumpStatement  */
  YYSYMBOL_globalDeclaration = 152,        /* globalDeclaration  */
  YYSYMBOL_function_definition = 153       /* function_definition  */
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
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2100

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  207
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  515

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   325


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
       2,     2,     2,    84,     2,     2,     2,    87,    90,     2,
      76,    77,    85,    81,    75,    82,    80,    86,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    94,    74,
      88,    73,    89,    93,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    78,     2,    79,    91,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,    92,    72,    83,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   122,   122,   134,   148,   161,   171,   182,   183,   190,
     191,   198,   199,   206,   212,   218,   224,   230,   235,   240,
     245,   253,   257,   261,   265,   269,   270,   274,   279,   284,
     289,   294,   299,   308,   317,   326,   338,   349,   358,   367,
     376,   385,   394,   403,   412,   422,   431,   443,   446,   457,
     468,   479,   493,   510,   521,   532,   543,   554,   565,   576,
     587,   601,   612,   626,   629,   635,   640,   646,   652,   657,
     662,   667,   672,   680,   684,   691,   694,   717,   720,   723,
     726,   729,   735,   738,   747,   750,   757,   765,   775,   778,
     785,   795,   798,   805,   815,   818,   825,   832,   839,   849,
     852,   859,   869,   872,   882,   885,   895,   898,   908,   911,
     921,   924,   934,   937,   947,   950,   959,   962,   977,   981,
     989,   992,   999,  1004,  1011,  1015,  1024,  1029,  1034,  1039,
    1044,  1049,  1054,  1059,  1068,  1074,  1079,  1087,  1092,  1099,
    1108,  1111,  1115,  1118,  1126,  1131,  1138,  1143,  1149,  1158,
    1163,  1166,  1171,  1175,  1180,  1185,  1192,  1197,  1204,  1210,
    1215,  1223,  1230,  1239,  1242,  1249,  1252,  1257,  1263,  1267,
    1272,  1277,  1283,  1287,  1295,  1300,  1306,  1315,  1320,  1327,
    1330,  1333,  1336,  1339,  1345,  1348,  1352,  1356,  1364,  1369,
    1376,  1381,  1388,  1392,  1400,  1406,  1416,  1422,  1429,  1440,
    1444,  1448,  1452,  1460,  1463,  1466,  1472,  1479
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
  "TIMEFRAME", "P_SIZE", "INDICATORS", "REGIMES", "FUN", "REF", "SCOPE",
  "ARROW", "ENTRYLONG", "ENTRYSHORT", "EXITLONG", "EXITSHORT", "OPEN",
  "CLOSE", "HIGH", "LOW", "VOLUME", "POSITION_SHARES", "ENTRY_PRICE",
  "DAYS_IN_POSITION", "PORTFOLIO_VALUE", "CASH_AVAILABLE", "SMA", "EMA",
  "RSI", "BB", "ATR", "SDV", "MAX", "MIN", "SUM", "MEDIAN", "AVG", "ABS",
  "CORRELATION", "SLOPE", "RSQUARED", "GROUP", "FOR", "WHILE", "IF",
  "ELSE", "CONTINUE", "BREAK", "RETURN", "INT", "FLOAT", "BOOL", "VOID",
  "STRING", "RGM", "CONST", "TIMESERIES", "AND", "OR", "LEFT_OP",
  "RIGHT_OP", "LEQ", "GEQ", "EQ", "NEQ", "IDENTIFIER", "STRINGLIT",
  "INTLIT", "FLOATLIT", "LOWER_THAN_ELSE", "'{'", "'}'", "'='", "';'",
  "','", "'('", "')'", "'['", "']'", "'.'", "'+'", "'-'", "'~'", "'!'",
  "'*'", "'/'", "'%'", "'<'", "'>'", "'&'", "'^'", "'|'", "'?'", "':'",
  "$accept", "translationUnit", "strategyDefinition", "strategyBody",
  "strategyDeclarations", "indicatorSection", "regimeSection",
  "signalFunctionList", "signalFunction", "primaryExpression",
  "timeseries", "timeseriesExpression", "postfixExpression",
  "argumentExpressionList", "unaryExpression", "unaryOperator",
  "castExpression", "multiplicativeExpression", "additiveExpression",
  "shiftExpression", "relationalExpression", "equalityExpression",
  "andExpression", "exclusiveOrExpression", "inclusiveOrExpression",
  "logicalAndExpression", "logicalOrExpression", "conditionalExpression",
  "assignmentExpression", "expression", "declaration",
  "declarationSpecifiers", "initDeclaratorList", "initDeclarator",
  "typeSpecifier", "groupSpecifier", "group_declarationList",
  "group_declaration", "specifier_qualifierList", "group_declaratorList",
  "group_declarator", "direct_declarator", "parameterList",
  "parameter_declaration", "identifierList", "type_name",
  "direct_abstract_declarator", "initializer", "initializerList",
  "statement", "compoundStatement", "declarationList", "statementList",
  "expressionStatement", "selectionStatement", "iterationStatement",
  "jumpStatement", "globalDeclaration", "function_definition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-351)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     166,   -35,   -20,   -27,  -351,  -351,  -351,  -351,  -351,  -351,
     106,  -351,    78,  -351,  -351,    32,  -351,  -351,  -351,  -351,
     -21,    16,    33,   389,  -351,  -351,  -351,  -351,  -351,   -33,
       9,  -351,   -38,   103,   308,   389,   389,   389,   651,  -351,
     -52,    34,  -351,   -33,   915,  2008,   983,    76,    82,   159,
     106,   -29,     1,  -351,   719,  -351,  -351,  -351,  -351,  1459,
      44,  -351,   -46,  -351,  -351,  -351,  -351,  -351,  -351,  -351,
    -351,  -351,  -351,  -351,  -351,  -351,   131,   135,   169,   175,
     177,   178,   179,   180,   187,   188,   189,   190,   191,   193,
     199,  -351,  -351,  -351,  -351,   915,   575,  -351,  -351,  -351,
    -351,  -351,  -351,  -351,    23,   203,  1459,  -351,    60,    89,
     137,    26,   145,   205,   186,   204,   239,   -48,  -351,  -351,
    -351,  -351,  -351,    90,    99,  -351,  -351,   219,   232,  -351,
     230,   294,   226,   258,  1051,   101,   104,   106,   783,  -351,
    -351,  -351,   -52,  1459,   253,   357,  1527,  1567,  1607,  1647,
    1687,  1727,  1767,  1807,  1847,  1887,  1927,  1967,  2007,  -351,
      30,  -351,   109,   105,   227,  1119,  1459,   240,  1459,  -351,
    1459,  1459,  1459,  1459,  1459,  1459,  1459,  1459,  1459,  1459,
    1459,  1459,  1459,  1459,  1459,  1459,  1459,  1459,  1459,  -351,
     250,  -351,  -351,   231,   439,  -351,   230,  -351,   230,  -351,
     112,    75,  -351,   238,   849,  1187,   241,  -351,  -351,  -351,
     245,   246,   255,   256,   257,   261,   263,   264,   265,   266,
     267,   268,   273,   275,   276,   251,   278,   279,   280,   282,
     291,   292,   293,   295,   296,   297,   304,   305,   306,   307,
     324,   326,   327,   328,   329,   330,   331,   332,   341,   342,
     343,   344,   345,   346,   347,  -351,   847,  1459,  -351,   358,
     104,  1459,  -351,   113,  -351,    11,  -351,  -351,  -351,  -351,
    -351,    60,    60,    89,    89,   137,   137,   137,   137,    26,
      26,   145,   205,   186,   204,   239,   -58,  -351,   364,   351,
     352,   353,   356,   359,  1255,  -351,  -351,   150,  -351,  -351,
    -351,   507,   643,  -351,  -351,  -351,  -351,  -351,    13,  -351,
    -351,  -351,  -351,  -351,   117,  -351,   368,   230,  2059,  2059,
    2059,  2059,  2059,  2059,  2059,  2059,  2059,  2059,  2059,  2059,
    2059,  2059,  2059,   369,   380,   382,   383,   384,   385,   417,
     429,   366,  2059,   430,   431,   432,   433,   434,   435,   436,
     441,   444,   446,   448,   450,   451,   485,   499,  2059,   498,
     500,   501,   502,  -351,  -351,  -351,  -351,  1459,  -351,  -351,
    1459,   494,  1323,  1459,  1459,  -351,  -351,  -351,   152,  -351,
    -351,  -351,   711,  -351,  -351,   230,   230,   230,   230,   560,
    -351,  -351,  -351,  -351,   495,   503,   505,   509,   510,   541,
     544,   545,   546,   547,   556,   557,   558,   559,   561,   562,
     563,   568,   569,   570,   571,   572,   573,   577,   548,   549,
     578,   608,   612,   617,  -351,  -351,   506,  1323,   118,   128,
    -351,  -351,  -351,  -351,  -351,  -351,   123,  -351,  -351,  -351,
    -351,  -351,  -351,   515,   583,   629,  2059,  -351,  -351,  -351,
    -351,  -351,  -351,  -351,  -351,  -351,  -351,  -351,  -351,  -351,
    -351,   628,   630,  -351,  -351,  -351,  -351,   631,  1391,   779,
     779,   230,   230,   230,   230,   620,   623,   638,   641,   645,
     676,   682,   779,   129,  -351,   591,  -351,  -351,  -351,  -351,
    -351,  -351,   650,   652,  -351,  -351,   694,  -351,   779,   779,
     686,   687,   690,  -351,  -351,  -351,  -351,   698,   695,   707,
     762,   713,   716,   714,  -351
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,   127,   128,   129,   126,   130,   131,
       0,   132,     0,   205,   204,     0,   120,   133,     2,   203,
       0,     0,   136,     0,   121,     1,     3,   149,   118,     0,
       0,   122,   124,     0,     0,     0,   143,   140,     0,   137,
       0,     0,   119,     0,     0,     0,     0,     0,     0,     7,
       0,   160,     0,   156,     0,   141,   142,   135,   138,     0,
       0,   144,   146,   150,   123,    77,    28,    27,    29,    30,
      31,    70,    71,    72,    68,    69,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    24,    22,    23,     0,     0,    78,    79,    80,
      81,    63,    47,    26,    75,    82,     0,    84,    88,    91,
      94,    99,   102,   104,   106,   108,   110,   112,   114,   174,
     125,   161,   155,     0,     0,   152,    82,     0,     0,     4,
       0,     9,     0,     0,     0,   158,   159,     0,     0,   134,
     147,   139,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   177,
       0,   116,     0,   163,     0,     0,     0,     0,     0,    76,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   153,
       0,   154,   151,     0,     0,     8,     0,    11,     0,   170,
       0,     0,   166,     0,     0,     0,     0,   157,   145,   148,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   175,     0,     0,    25,     0,
     164,     0,    65,     0,    73,     0,    67,   115,    85,    86,
      87,    89,    90,    92,    93,    97,    98,    95,    96,   100,
     101,   103,   105,   107,   109,   111,     0,   162,     0,     0,
       0,     0,     0,     0,     0,   184,   192,     0,   188,   190,
     179,     0,     0,   180,   181,   182,   183,    10,     5,   206,
     171,   165,   167,   172,     0,   168,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   178,   117,    83,     0,    66,    64,
       0,     0,     0,     0,     0,   199,   200,   201,     0,   193,
     186,   189,     0,   185,   191,     0,     0,     0,     0,     0,
      12,   173,   169,   207,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    74,   113,     0,     0,     0,     0,
     202,   187,    17,    18,    19,    20,     0,    48,    32,    49,
      33,    50,    34,     0,     0,     0,     0,    53,    37,    54,
      38,    55,    39,    56,    40,    57,    41,    58,    42,    59,
      43,     0,     0,    61,    45,    62,    46,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   196,   194,    13,    14,    15,    16,
      51,    35,     0,     0,    60,    44,     0,   197,     0,     0,
       0,     0,     0,   198,   195,    52,    36,     0,     0,     0,
       0,     0,     0,     0,     6
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -351,  -351,  -351,  -351,  -351,  -351,  -351,  -351,  -351,  -351,
     -90,  -351,  -351,  -351,   -44,  -351,   -97,    70,    71,   -37,
      67,   607,   637,   644,   646,   654,  -351,   -43,   -42,   -95,
    -184,     6,  -351,   787,    59,  -351,   796,   -13,   -16,  -351,
     700,   -17,   -26,   705,  -351,  -351,   -36,   -88,  -351,  -297,
    -126,  -351,   543,  -350,  -351,  -351,  -351,   837,  -351
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    12,    13,    48,    49,   131,   197,   308,   390,   101,
     102,   103,   104,   263,   126,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   161,   297,
      14,    51,    30,    31,    16,    17,    38,    39,    40,    60,
      61,    32,   200,    53,   124,   164,   201,   120,   160,   299,
     300,   301,   302,   303,   304,   305,   306,    18,    19
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     105,   162,   119,   127,   195,   384,    15,   159,    52,   169,
     298,   187,    41,   137,    27,   136,   140,   257,    15,   123,
      55,    56,   427,    62,    29,    58,   385,   386,   387,   388,
      45,    20,    46,    27,   135,    44,   370,    27,    45,    22,
      46,    58,    59,    29,    23,   188,    21,   133,   143,   134,
      33,   105,   105,   119,   226,   228,   230,   232,   234,   236,
     238,   240,   242,   244,   246,   248,   250,   252,   254,    24,
     307,   265,   309,   268,   269,   270,   138,   468,    25,   389,
     163,     1,    37,    42,    43,   384,   257,     2,   177,   178,
     369,   203,    34,   286,    37,    37,    37,    37,    27,   165,
     209,   166,   255,   167,    35,   256,    28,    47,    29,   132,
      45,    63,    46,    37,   179,   180,    41,   381,   141,   142,
       3,   105,   105,   264,   105,    62,   267,   260,     4,     5,
       6,     7,     8,     9,    10,    11,   471,   472,   473,   474,
     275,   276,   277,   278,   105,   170,   171,   172,     3,   128,
     105,   204,   311,   205,   129,    37,     4,     5,     6,     7,
       8,     9,   316,    11,   366,   138,   130,   189,   364,     1,
     173,   174,   484,   485,   190,     2,   191,    45,   314,    46,
     204,   259,   205,   134,   257,   497,   258,   138,   367,   310,
     368,   393,   138,   257,   391,   469,   206,   175,   176,   378,
      15,   503,   504,   257,   257,   470,   498,   144,     3,   181,
     182,   145,   105,   105,   119,   365,     4,     5,     6,     7,
       8,     9,    10,    11,   379,   257,   430,   257,   226,   228,
     230,   232,   234,   236,   238,   240,   242,   244,   246,   248,
     250,   252,   254,   271,   272,   146,   273,   274,   279,   280,
     105,   147,   403,   148,   149,   150,   151,   105,   105,   432,
     433,   434,   435,   152,   153,   154,   155,   156,   419,   157,
      66,    67,    68,    69,    70,   158,   168,   184,   428,   429,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   183,   185,   186,   192,   193,
       3,   194,   196,   198,   261,   288,   266,    15,     4,     5,
       6,     7,     8,     9,    10,    11,   287,   312,   317,   225,
      50,   318,   319,   105,    27,   424,   333,   425,   105,   105,
     105,   320,   321,   322,   133,   199,   134,   323,   105,   324,
     325,   326,   327,   328,   329,   486,   487,   488,   489,   330,
       3,   331,   332,   334,   335,   336,   478,   337,     4,     5,
       6,     7,     8,     9,    10,    11,   338,   339,   340,   371,
     341,   342,   343,   483,    66,    67,    68,    69,    70,   344,
     345,   346,   347,   105,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   348,
       3,   349,   350,   351,   352,   353,   354,   355,     4,     5,
       6,     7,     8,     9,    10,    11,   356,   357,   358,   359,
     360,   361,   362,   227,   105,   105,   105,   372,   373,   374,
     375,     3,   402,   376,   259,   199,   134,   394,   105,     4,
       5,     6,     7,     8,     9,    36,    11,   392,   395,    65,
     396,   397,   398,   399,   105,   105,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     3,   289,   290,   291,   400,   292,   293,   294,     4,
       5,     6,     7,     8,     9,    10,    11,   401,   404,   405,
     406,   407,   408,   409,   410,    91,    92,    93,    94,   411,
     194,   295,   412,   296,   413,    96,   414,    65,   415,   416,
      97,    98,    99,   100,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,     3,
     289,   290,   291,   417,   292,   293,   294,     4,     5,     6,
       7,     8,     9,    10,    11,   418,   420,   426,   421,   422,
     423,   436,   437,    91,    92,    93,    94,   467,   194,   380,
     438,   296,   439,    96,   475,    65,   440,   441,    97,    98,
      99,   100,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,     3,   442,   443,
     444,   445,   446,   461,   462,     4,     5,     6,     7,     8,
       9,    36,    11,   447,   448,   449,   450,   499,   451,   452,
     453,    91,    92,    93,    94,   454,   455,   456,   457,   458,
     459,    96,   476,    65,   460,   463,    97,    98,    99,   100,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,   464,   289,   290,   291,   465,
     292,   293,   294,     3,   466,   477,   479,   490,   480,   481,
     491,     4,     5,     6,     7,     8,     9,    36,    11,    91,
      92,    93,    94,   492,   194,   383,   493,   296,   500,    96,
     501,    65,   494,    57,    97,    98,    99,   100,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,   495,   289,   290,   291,   496,   292,   293,
     294,     3,   502,   505,   506,   507,   508,   509,   511,     4,
       5,     6,     7,     8,     9,    36,    11,    91,    92,    93,
      94,   510,   194,   431,   513,   296,   512,    96,   514,    65,
     281,   139,    97,    98,    99,   100,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   282,   289,   290,   291,     3,   292,   293,   294,   283,
      64,    54,   284,     4,     5,     6,     7,     8,     9,    10,
      11,   285,   208,   207,   382,    91,    92,    93,    94,    26,
     194,     0,     0,   296,     0,    96,     0,    65,     0,     0,
      97,    98,    99,   100,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,     0,
       0,     3,     0,     0,     0,     0,     0,     0,     0,     4,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     0,
       0,     0,     0,    91,    92,    93,    94,     0,    95,   363,
       0,     0,     0,    96,     0,    65,   313,     0,    97,    98,
      99,   100,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,    92,    93,    94,     0,    95,     0,     0,     0,
       0,    96,     0,    65,     0,     0,    97,    98,    99,   100,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    91,
      92,    93,    94,     0,     0,     0,     0,     0,     0,    96,
       0,    65,   125,     0,    97,    98,    99,   100,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    91,    92,    93,
      94,     0,     0,     0,     0,     0,     0,    96,     0,    65,
     202,     0,    97,    98,    99,   100,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    91,    92,    93,    94,     0,
       0,     0,     0,     0,     0,    96,   262,    65,     0,     0,
      97,    98,    99,   100,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    91,    92,    93,    94,     0,     0,     0,
       0,     0,     0,    96,     0,    65,   315,     0,    97,    98,
      99,   100,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,    92,    93,    94,     0,     0,     0,     0,   377,
       0,    96,     0,    65,     0,     0,    97,    98,    99,   100,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    91,
      92,    93,    94,     0,     0,     0,     0,   296,     0,    96,
       0,    65,     0,     0,    97,    98,    99,   100,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    91,    92,    93,
      94,     0,     0,     0,     0,     0,     0,    96,   482,    65,
       0,     0,    97,    98,    99,   100,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    91,    92,    93,    94,     0,
       0,     0,     0,     0,     0,    96,     0,     0,     0,     0,
      97,    98,    99,   100,    66,    67,    68,    69,    70,     0,
       0,     0,     0,     0,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   229,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   231,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   233,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   235,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   237,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   239,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   241,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   243,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   245,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   247,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   249,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   251,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       3,     0,     0,     0,     0,     0,     0,     0,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,   253,   121,     0,    66,    67,    68,    69,
      70,     0,     0,     0,     0,   122,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224
};

static const yytype_int16 yycheck[] =
{
      44,    96,    44,    46,   130,   302,     0,    95,    34,   106,
     194,    59,    29,    12,    66,    51,    59,    75,    12,    45,
      36,    37,   372,    40,    76,    38,    13,    14,    15,    16,
      76,    66,    78,    66,    51,    73,    94,    66,    76,    66,
      78,    54,    94,    76,    71,    93,    66,    76,    94,    78,
      71,    95,    96,    95,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,    10,
     196,   166,   198,   170,   171,   172,    75,   427,     0,    66,
      96,     3,    23,    74,    75,   382,    75,     9,    62,    63,
      79,   134,    76,   188,    35,    36,    37,    38,    66,    76,
     143,    78,    72,    80,    71,    75,    74,     4,    76,    50,
      76,    77,    78,    54,    88,    89,   133,   301,    74,    75,
      42,   165,   166,   165,   168,   142,   168,   163,    50,    51,
      52,    53,    54,    55,    56,    57,    13,    14,    15,    16,
     177,   178,   179,   180,   188,    85,    86,    87,    42,    73,
     194,    76,    77,    78,    72,    96,    50,    51,    52,    53,
      54,    55,   205,    57,   261,    75,     7,    77,   256,     3,
      81,    82,   469,   470,    75,     9,    77,    76,   204,    78,
      76,    76,    78,    78,    75,   482,    77,    75,    75,    77,
      77,   317,    75,    75,    77,    77,   137,    60,    61,   294,
     194,   498,   499,    75,    75,    77,    77,    76,    42,    64,
      65,    76,   256,   257,   256,   257,    50,    51,    52,    53,
      54,    55,    56,    57,    74,    75,    74,    75,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   173,   174,    76,   175,   176,   181,   182,
     294,    76,   342,    76,    76,    76,    76,   301,   302,   385,
     386,   387,   388,    76,    76,    76,    76,    76,   358,    76,
      17,    18,    19,    20,    21,    76,    73,    91,   373,   374,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    90,    92,    58,    79,    67,
      42,    71,     8,    77,    77,    74,    66,   301,    50,    51,
      52,    53,    54,    55,    56,    57,    66,    79,    77,    66,
      12,    76,    76,   367,    66,   367,    75,   370,   372,   373,
     374,    76,    76,    76,    76,    77,    78,    76,   382,    76,
      76,    76,    76,    76,    76,   471,   472,   473,   474,    76,
      42,    76,    76,    75,    75,    75,   446,    75,    50,    51,
      52,    53,    54,    55,    56,    57,    75,    75,    75,     5,
      75,    75,    75,   468,    17,    18,    19,    20,    21,    75,
      75,    75,    75,   427,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    75,
      42,    75,    75,    75,    75,    75,    75,    75,    50,    51,
      52,    53,    54,    55,    56,    57,    75,    75,    75,    75,
      75,    75,    75,    66,   468,   469,   470,    76,    76,    76,
      74,    42,    66,    74,    76,    77,    78,    68,   482,    50,
      51,    52,    53,    54,    55,    56,    57,    79,    68,    10,
      68,    68,    68,    68,   498,   499,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    68,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    68,    68,    68,
      68,    68,    68,    68,    68,    66,    67,    68,    69,    68,
      71,    72,    68,    74,    68,    76,    68,    10,    68,    68,
      81,    82,    83,    84,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    68,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    66,    68,    73,    68,    68,
      68,    11,    77,    66,    67,    68,    69,    71,    71,    72,
      77,    74,    77,    76,    69,    10,    77,    77,    81,    82,
      83,    84,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    77,    75,
      75,    75,    75,    75,    75,    50,    51,    52,    53,    54,
      55,    56,    57,    77,    77,    77,    77,    46,    77,    77,
      77,    66,    67,    68,    69,    77,    77,    77,    77,    77,
      77,    76,    69,    10,    77,    77,    81,    82,    83,    84,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    77,    43,    44,    45,    77,
      47,    48,    49,    42,    77,    66,    68,    77,    68,    68,
      77,    50,    51,    52,    53,    54,    55,    56,    57,    66,
      67,    68,    69,    75,    71,    72,    75,    74,    68,    76,
      68,    10,    77,    72,    81,    82,    83,    84,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    77,    43,    44,    45,    75,    47,    48,
      49,    42,    68,    77,    77,    75,    68,    72,     6,    50,
      51,    52,    53,    54,    55,    56,    57,    66,    67,    68,
      69,    74,    71,    72,    68,    74,    73,    76,    74,    10,
     183,    72,    81,    82,    83,    84,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,   184,    43,    44,    45,    42,    47,    48,    49,   185,
      43,    35,   186,    50,    51,    52,    53,    54,    55,    56,
      57,   187,   142,   138,   301,    66,    67,    68,    69,    12,
      71,    -1,    -1,    74,    -1,    76,    -1,    10,    -1,    -1,
      81,    82,    83,    84,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    -1,    71,    72,
      -1,    -1,    -1,    76,    -1,    10,    77,    -1,    81,    82,
      83,    84,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    -1,    71,    -1,    -1,    -1,
      -1,    76,    -1,    10,    -1,    -1,    81,    82,    83,    84,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    10,    79,    -1,    81,    82,    83,    84,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    10,
      79,    -1,    81,    82,    83,    84,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    10,    -1,    -1,
      81,    82,    83,    84,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    10,    79,    -1,    81,    82,
      83,    84,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    74,
      -1,    76,    -1,    10,    -1,    -1,    81,    82,    83,    84,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    74,    -1,    76,
      -1,    10,    -1,    -1,    81,    82,    83,    84,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    10,
      -1,    -1,    81,    82,    83,    84,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    66,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    66,    -1,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    77,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     9,    42,    50,    51,    52,    53,    54,    55,
      56,    57,    96,    97,   125,   126,   129,   130,   152,   153,
      66,    66,    66,    71,   129,     0,   152,    66,    74,    76,
     127,   128,   136,    71,    76,    71,    56,   129,   131,   132,
     133,   136,    74,    75,    73,    76,    78,     4,    98,    99,
      12,   126,   137,   138,   131,   133,   133,    72,   132,    94,
     134,   135,   136,    77,   128,    10,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    66,    67,    68,    69,    71,    76,    81,    82,    83,
      84,   104,   105,   106,   107,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     142,    66,    77,   137,   139,    79,   109,   122,    73,    72,
       7,   100,   129,    76,    78,   136,   141,    12,    75,    72,
     122,    74,    75,    94,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,   142,
     143,   123,   124,   133,   140,    76,    78,    80,    73,   111,
      85,    86,    87,    81,    82,    60,    61,    62,    63,    88,
      89,    64,    65,    90,    91,    92,    58,    59,    93,    77,
      75,    77,    79,    67,    71,   145,     8,   101,    77,    77,
     137,   141,    79,   122,    76,    78,   129,   138,   135,   122,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    66,   105,    66,   105,    66,
     105,    66,   105,    66,   105,    66,   105,    66,   105,    66,
     105,    66,   105,    66,   105,    66,   105,    66,   105,    66,
     105,    66,   105,    66,   105,    72,    75,    75,    77,    76,
     141,    77,    77,   108,   123,   124,    66,   123,   111,   111,
     111,   112,   112,   113,   113,   114,   114,   114,   114,   115,
     115,   116,   117,   118,   119,   120,   124,    66,    74,    43,
      44,    45,    47,    48,    49,    72,    74,   124,   125,   144,
     145,   146,   147,   148,   149,   150,   151,   145,   102,   145,
      77,    77,    79,    77,   137,    79,   122,    77,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    72,   142,   123,   111,    75,    77,    79,
      94,     5,    76,    76,    76,    74,    74,    74,   124,    74,
      72,   125,   147,    72,   144,    13,    14,    15,    16,    66,
     103,    77,    79,   145,    68,    68,    68,    68,    68,    68,
      68,    68,    66,   105,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    66,   105,
      68,    68,    68,    68,   123,   122,    73,   148,   124,   124,
      74,    72,   145,   145,   145,   145,    11,    77,    77,    77,
      77,    77,    77,    75,    75,    75,    75,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    75,    75,    77,    77,    77,    77,    71,   148,    77,
      77,    13,    14,    15,    16,    69,    69,    66,   105,    68,
      68,    68,    77,   124,   144,   144,   145,   145,   145,   145,
      77,    77,    75,    75,    77,    77,    75,   144,    77,    46,
      68,    68,    68,   144,   144,    77,    77,    75,    68,    72,
      74,     6,    73,    68,    74
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    97,    98,    99,   100,   100,   101,
     101,   102,   102,   103,   103,   103,   103,   103,   103,   103,
     103,   104,   104,   104,   104,   104,   104,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   108,   108,   109,   109,   110,   110,   110,
     110,   110,   111,   111,   112,   112,   112,   112,   113,   113,
     113,   114,   114,   114,   115,   115,   115,   115,   115,   116,
     116,   116,   117,   117,   118,   118,   119,   119,   120,   120,
     121,   121,   122,   122,   123,   123,   124,   124,   125,   125,
     126,   126,   127,   127,   128,   128,   129,   129,   129,   129,
     129,   129,   129,   129,   130,   130,   130,   131,   131,   132,
     133,   133,   133,   133,   134,   134,   135,   135,   135,   136,
     136,   136,   136,   136,   136,   136,   137,   137,   138,   138,
     138,   139,   139,   140,   140,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   142,   142,   142,   143,   143,   144,
     144,   144,   144,   144,   145,   145,   145,   145,   146,   146,
     147,   147,   148,   148,   149,   149,   150,   150,   150,   151,
     151,   151,   151,   152,   152,   152,   153,   153
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     5,     4,    18,     0,     2,     0,
       2,     0,     2,     4,     4,     4,     4,     2,     2,     2,
       2,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     6,     6,     6,     8,    10,     6,     6,     6,
       6,     6,     6,     6,     8,     6,     6,     1,     6,     6,
       6,     8,    10,     6,     6,     6,     6,     6,     6,     6,
       8,     6,     6,     1,     4,     3,     4,     3,     1,     1,
       1,     1,     1,     1,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     4,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     5,     1,     3,     1,     3,     2,     3,
       1,     2,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     4,     2,     1,     2,     3,
       1,     2,     2,     1,     1,     3,     1,     2,     3,     1,
       3,     4,     3,     4,     4,     3,     1,     3,     2,     2,
       1,     1,     3,     1,     2,     3,     2,     3,     3,     4,
       2,     3,     3,     4,     1,     3,     4,     1,     3,     1,
       1,     1,     1,     1,     2,     3,     3,     4,     1,     2,
       1,     2,     1,     2,     5,     7,     5,     6,     7,     2,
       2,     2,     3,     1,     1,     1,     7,     8
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
#line 122 "parser.y"
                        {
        (yyval.prog) = new ProgramNode();
        ASTNode* node = (yyvsp[0].node);
        if(node->nodeType == ASTNodeType::FuncNode)
            (yyval.prog)->functions.push_back((FuncNode*)node);
        else if(node->nodeType == ASTNodeType::DeclNode)
            (yyval.prog)->globalDeclarations.push_back((DeclNode*)node);
        else if(node->nodeType == ASTNodeType::StrategyNode)
            (yyval.prog)->strategies.push_back((StrategyNode*)node);
		
		progRoot = (yyval.prog);
    }
#line 1906 "parser.tab.c"
    break;

  case 3: /* translationUnit: translationUnit globalDeclaration  */
#line 134 "parser.y"
                                        {
        (yyval.prog) = (yyvsp[-1].prog);
        ASTNode* node = (yyvsp[0].node);
        if(node->nodeType == ASTNodeType::FuncNode)
            (yyval.prog)->functions.push_back((FuncNode*)node);
        else if(node->nodeType == ASTNodeType::DeclNode)
            (yyval.prog)->globalDeclarations.push_back((DeclNode*)node);
        else if(node->nodeType == ASTNodeType::StrategyNode)
            (yyval.prog)->strategies.push_back((StrategyNode*)node);
		progRoot = (yyval.prog);
    }
#line 1922 "parser.tab.c"
    break;

  case 4: /* strategyDefinition: STRATEGY IDENTIFIER '{' strategyBody '}'  */
#line 148 "parser.y"
                                               {
		(yyval.strategy) = new StrategyNode();
		(yyval.strategy)->id = *(yyvsp[-3].id);
		if((yyvsp[-1].strategy)){
			(yyval.strategy)->declarations = (yyvsp[-1].strategy)->declarations;
			(yyval.strategy)->indicators = (yyvsp[-1].strategy)->indicators;
            (yyval.strategy)->regimes = (yyvsp[-1].strategy)->regimes;
            (yyval.strategy)->signals = (yyvsp[-1].strategy)->signals;
		}
	}
#line 1937 "parser.tab.c"
    break;

  case 5: /* strategyBody: strategyDeclarations indicatorSection regimeSection signalFunctionList  */
#line 161 "parser.y"
                                                                             {
		(yyval.strategy) = new StrategyNode();
		(yyval.strategy)->declarations = (yyvsp[-3].strategyDecl);
        (yyval.strategy)->indicators = (yyvsp[-2].indicator);
        (yyval.strategy)->regimes = (yyvsp[-1].regime);
        (yyval.strategy)->signals = (yyvsp[0].sigFuncList);
	}
#line 1949 "parser.tab.c"
    break;

  case 6: /* strategyDeclarations: SYMBOL '=' STRINGLIT ';' TIMEFRAME '=' '{' INTLIT ',' INTLIT ',' INTLIT '}' ';' P_SIZE '=' INTLIT ';'  */
#line 171 "parser.y"
                                                                                                          {
		(yyval.strategyDecl) = new StratDeclNode();
		(yyval.strategyDecl)->symbol = *(yyvsp[-15].id);
		(yyval.strategyDecl)->timeframe.push_back((yyvsp[-10].intVal));
        (yyval.strategyDecl)->timeframe.push_back((yyvsp[-8].intVal));
        (yyval.strategyDecl)->timeframe.push_back((yyvsp[-6].intVal));
        (yyval.strategyDecl)->positionSize = (yyvsp[-1].intVal);
	}
#line 1962 "parser.tab.c"
    break;

  case 7: /* indicatorSection: %empty  */
#line 182 "parser.y"
      {(yyval.indicator) = NULL;}
#line 1968 "parser.tab.c"
    break;

  case 8: /* indicatorSection: INDICATORS compoundStatement  */
#line 183 "parser.y"
                                       {
		(yyval.indicator) = new IndicatorNode();
        (yyval.indicator)->body = (yyvsp[0].stmt);
	}
#line 1977 "parser.tab.c"
    break;

  case 9: /* regimeSection: %empty  */
#line 190 "parser.y"
      {(yyval.regime) = NULL;}
#line 1983 "parser.tab.c"
    break;

  case 10: /* regimeSection: REGIMES compoundStatement  */
#line 191 "parser.y"
                                    {
		(yyval.regime) = new RegimeNode();
        (yyval.regime)->body = (yyvsp[0].stmt);
	}
#line 1992 "parser.tab.c"
    break;

  case 11: /* signalFunctionList: %empty  */
#line 198 "parser.y"
       { (yyval.sigFuncList) = new SignalFuncListNode(); }
#line 1998 "parser.tab.c"
    break;

  case 12: /* signalFunctionList: signalFunctionList signalFunction  */
#line 199 "parser.y"
                                        {
        (yyval.sigFuncList) = (yyvsp[-1].sigFuncList);
        if ((yyvsp[0].signalFunc)) (yyval.sigFuncList)->signals.push_back((yyvsp[0].signalFunc));
    }
#line 2007 "parser.tab.c"
    break;

  case 13: /* signalFunction: IDENTIFIER SCOPE ENTRYLONG compoundStatement  */
#line 206 "parser.y"
                                                   {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->regimeId = *(yyvsp[-3].id);
        (yyval.signalFunc)->signalType = SIGNAL_ENTRY_LONG;
        (yyval.signalFunc)->body = (yyvsp[0].stmt);
    }
#line 2018 "parser.tab.c"
    break;

  case 14: /* signalFunction: IDENTIFIER SCOPE ENTRYSHORT compoundStatement  */
#line 212 "parser.y"
                                                    {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->regimeId = *(yyvsp[-3].id);
        (yyval.signalFunc)->signalType = SIGNAL_ENTRY_SHORT;
        (yyval.signalFunc)->body = (yyvsp[0].stmt);
    }
#line 2029 "parser.tab.c"
    break;

  case 15: /* signalFunction: IDENTIFIER SCOPE EXITLONG compoundStatement  */
#line 218 "parser.y"
                                                  {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->regimeId = *(yyvsp[-3].id);
        (yyval.signalFunc)->signalType = SIGNAL_EXIT_LONG;
        (yyval.signalFunc)->body = (yyvsp[0].stmt);
    }
#line 2040 "parser.tab.c"
    break;

  case 16: /* signalFunction: IDENTIFIER SCOPE EXITSHORT compoundStatement  */
#line 224 "parser.y"
                                                   {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->regimeId = *(yyvsp[-3].id);
        (yyval.signalFunc)->signalType = SIGNAL_EXIT_SHORT;
        (yyval.signalFunc)->body = (yyvsp[0].stmt);
    }
#line 2051 "parser.tab.c"
    break;

  case 17: /* signalFunction: ENTRYLONG compoundStatement  */
#line 230 "parser.y"
                                  {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->signalType = SIGNAL_ENTRY_LONG;
        (yyval.signalFunc)->body = (yyvsp[0].stmt);
    }
#line 2061 "parser.tab.c"
    break;

  case 18: /* signalFunction: ENTRYSHORT compoundStatement  */
#line 235 "parser.y"
                                   {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->signalType = SIGNAL_ENTRY_SHORT;
        (yyval.signalFunc)->body = (yyvsp[0].stmt);
    }
#line 2071 "parser.tab.c"
    break;

  case 19: /* signalFunction: EXITLONG compoundStatement  */
#line 240 "parser.y"
                                 {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->signalType = SIGNAL_EXIT_LONG;
        (yyval.signalFunc)->body = (yyvsp[0].stmt);
    }
#line 2081 "parser.tab.c"
    break;

  case 20: /* signalFunction: EXITSHORT compoundStatement  */
#line 245 "parser.y"
                                  {
        (yyval.signalFunc) = new SignalFuncNode();
        (yyval.signalFunc)->signalType = SIGNAL_EXIT_SHORT;
        (yyval.signalFunc)->body = (yyvsp[0].stmt);
    }
#line 2091 "parser.tab.c"
    break;

  case 21: /* primaryExpression: IDENTIFIER  */
#line 253 "parser.y"
                 {
        (yyval.expr) = new IdentifierNode();
        ((IdentifierNode*)(yyval.expr))->id = *(yyvsp[0].id);
    }
#line 2100 "parser.tab.c"
    break;

  case 22: /* primaryExpression: INTLIT  */
#line 257 "parser.y"
             {
        (yyval.expr) = new LiteralIntNode();
        ((LiteralIntNode*)(yyval.expr))->value = (yyvsp[0].intVal);
    }
#line 2109 "parser.tab.c"
    break;

  case 23: /* primaryExpression: FLOATLIT  */
#line 261 "parser.y"
               {
        (yyval.expr) = new LiteralFloatNode();
        ((LiteralFloatNode*)(yyval.expr))->value = (yyvsp[0].floatVal);
    }
#line 2118 "parser.tab.c"
    break;

  case 24: /* primaryExpression: STRINGLIT  */
#line 265 "parser.y"
                {
        (yyval.expr) = new LiteralStringNode();
        ((LiteralStringNode*)(yyval.expr))->value = *(yyvsp[0].id);
    }
#line 2127 "parser.tab.c"
    break;

  case 25: /* primaryExpression: '(' expression ')'  */
#line 269 "parser.y"
                         { (yyval.expr) = (yyvsp[-1].expr); }
#line 2133 "parser.tab.c"
    break;

  case 26: /* primaryExpression: timeseriesExpression  */
#line 270 "parser.y"
                           { (yyval.expr) = (yyvsp[0].expr); }
#line 2139 "parser.tab.c"
    break;

  case 27: /* timeseries: CLOSE  */
#line 274 "parser.y"
            {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::CLOSE;
        (yyval.expr) = node;
	}
#line 2149 "parser.tab.c"
    break;

  case 28: /* timeseries: OPEN  */
#line 279 "parser.y"
           {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::OPEN;
        (yyval.expr) = node;
	}
#line 2159 "parser.tab.c"
    break;

  case 29: /* timeseries: HIGH  */
#line 284 "parser.y"
           {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::HIGH;
        (yyval.expr) = node;
	}
#line 2169 "parser.tab.c"
    break;

  case 30: /* timeseries: LOW  */
#line 289 "parser.y"
          {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::LOW;
        (yyval.expr) = node;
	}
#line 2179 "parser.tab.c"
    break;

  case 31: /* timeseries: VOLUME  */
#line 294 "parser.y"
             {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::VOLUME;
        (yyval.expr) = node;
	}
#line 2189 "parser.tab.c"
    break;

  case 32: /* timeseries: SMA '(' timeseries ',' INTLIT ')'  */
#line 299 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SMA;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2203 "parser.tab.c"
    break;

  case 33: /* timeseries: EMA '(' timeseries ',' INTLIT ')'  */
#line 308 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::EMA;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2217 "parser.tab.c"
    break;

  case 34: /* timeseries: RSI '(' timeseries ',' INTLIT ')'  */
#line 317 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSI;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2231 "parser.tab.c"
    break;

  case 35: /* timeseries: BB '(' timeseries ',' INTLIT ',' FLOATLIT ')'  */
#line 326 "parser.y"
                                                    {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::BB;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-3].intVal);
		LiteralFloatNode* floatNode = new LiteralFloatNode();
		floatNode->value = (yyvsp[-1].floatVal);
		node->args.push_back((yyvsp[-5].expr));
		node->args.push_back(intNode);
		node->args.push_back(floatNode);
        (yyval.expr) = node;
	}
#line 2248 "parser.tab.c"
    break;

  case 36: /* timeseries: ATR '(' timeseries ',' timeseries ',' timeseries ',' INTLIT ')'  */
#line 338 "parser.y"
                                                                      {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ATR;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-7].expr));
		node->args.push_back((yyvsp[-5].expr));
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2264 "parser.tab.c"
    break;

  case 37: /* timeseries: SDV '(' timeseries ',' INTLIT ')'  */
#line 349 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SDV;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2278 "parser.tab.c"
    break;

  case 38: /* timeseries: MAX '(' timeseries ',' INTLIT ')'  */
#line 358 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MAX;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2292 "parser.tab.c"
    break;

  case 39: /* timeseries: MIN '(' timeseries ',' INTLIT ')'  */
#line 367 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MIN;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2306 "parser.tab.c"
    break;

  case 40: /* timeseries: SUM '(' timeseries ',' INTLIT ')'  */
#line 376 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SUM;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2320 "parser.tab.c"
    break;

  case 41: /* timeseries: MEDIAN '(' timeseries ',' INTLIT ')'  */
#line 385 "parser.y"
                                           {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MEDIAN;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2334 "parser.tab.c"
    break;

  case 42: /* timeseries: AVG '(' timeseries ',' INTLIT ')'  */
#line 394 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::AVG;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2348 "parser.tab.c"
    break;

  case 43: /* timeseries: ABS '(' timeseries ',' INTLIT ')'  */
#line 403 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ABS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2362 "parser.tab.c"
    break;

  case 44: /* timeseries: CORRELATION '(' timeseries ',' timeseries ',' INTLIT ')'  */
#line 412 "parser.y"
                                                               {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::CORRELATION;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-5].expr));
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2377 "parser.tab.c"
    break;

  case 45: /* timeseries: SLOPE '(' timeseries ',' INTLIT ')'  */
#line 422 "parser.y"
                                          {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SLOPE;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2391 "parser.tab.c"
    break;

  case 46: /* timeseries: RSQUARED '(' timeseries ',' INTLIT ')'  */
#line 431 "parser.y"
                                             {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSQUARED;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		node->args.push_back((yyvsp[-3].expr));
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2405 "parser.tab.c"
    break;

  case 47: /* timeseriesExpression: timeseries  */
#line 443 "parser.y"
                     {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 2413 "parser.tab.c"
    break;

  case 48: /* timeseriesExpression: SMA '(' IDENTIFIER ',' INTLIT ')'  */
#line 446 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SMA;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2429 "parser.tab.c"
    break;

  case 49: /* timeseriesExpression: EMA '(' IDENTIFIER ',' INTLIT ')'  */
#line 457 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::EMA;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2445 "parser.tab.c"
    break;

  case 50: /* timeseriesExpression: RSI '(' IDENTIFIER ',' INTLIT ')'  */
#line 468 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSI;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2461 "parser.tab.c"
    break;

  case 51: /* timeseriesExpression: BB '(' IDENTIFIER ',' INTLIT ',' FLOATLIT ')'  */
#line 479 "parser.y"
                                                    {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::BB;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-3].intVal);
		LiteralFloatNode* floatNode = new LiteralFloatNode();
		floatNode->value = (yyvsp[-1].floatVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-5].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
		node->args.push_back(floatNode);
        (yyval.expr) = node;
	}
#line 2480 "parser.tab.c"
    break;

  case 52: /* timeseriesExpression: ATR '(' IDENTIFIER ',' IDENTIFIER ',' IDENTIFIER ',' INTLIT ')'  */
#line 493 "parser.y"
                                                                      {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ATR;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode1 = new IdentifierNode();
		idNode->id = (yyvsp[-7].id);
		IdentifierNode* idNode2 = new IdentifierNode();
		idNode->id = (yyvsp[-5].id);
		IdentifierNode* idNode3 = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode1);
		node->args.push_back(idNode2);
		node->args.push_back(idNode3);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2502 "parser.tab.c"
    break;

  case 53: /* timeseriesExpression: SDV '(' IDENTIFIER ',' INTLIT ')'  */
#line 510 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SDV;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2518 "parser.tab.c"
    break;

  case 54: /* timeseriesExpression: MAX '(' IDENTIFIER ',' INTLIT ')'  */
#line 521 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MAX;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2534 "parser.tab.c"
    break;

  case 55: /* timeseriesExpression: MIN '(' IDENTIFIER ',' INTLIT ')'  */
#line 532 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MIN;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2550 "parser.tab.c"
    break;

  case 56: /* timeseriesExpression: SUM '(' IDENTIFIER ',' INTLIT ')'  */
#line 543 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SUM;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2566 "parser.tab.c"
    break;

  case 57: /* timeseriesExpression: MEDIAN '(' IDENTIFIER ',' INTLIT ')'  */
#line 554 "parser.y"
                                           {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::MEDIAN;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2582 "parser.tab.c"
    break;

  case 58: /* timeseriesExpression: AVG '(' IDENTIFIER ',' INTLIT ')'  */
#line 565 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::AVG;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2598 "parser.tab.c"
    break;

  case 59: /* timeseriesExpression: ABS '(' IDENTIFIER ',' INTLIT ')'  */
#line 576 "parser.y"
                                        {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::ABS;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2614 "parser.tab.c"
    break;

  case 60: /* timeseriesExpression: CORRELATION '(' IDENTIFIER ',' IDENTIFIER ',' INTLIT ')'  */
#line 587 "parser.y"
                                                               {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::CORRELATION;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode1 = new IdentifierNode();
		idNode->id = (yyvsp[-5].id);
		IdentifierNode* idNode2 = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode1);
		node->args.push_back(idNode2);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2633 "parser.tab.c"
    break;

  case 61: /* timeseriesExpression: SLOPE '(' IDENTIFIER ',' INTLIT ')'  */
#line 601 "parser.y"
                                          {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::SLOPE;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2649 "parser.tab.c"
    break;

  case 62: /* timeseriesExpression: RSQUARED '(' IDENTIFIER ',' INTLIT ')'  */
#line 612 "parser.y"
                                             {
		TimeseriesNode* node = new TimeseriesNode();
        node->funcType = TimeseriesFuncType::RSQUARED;
		LiteralIntNode* intNode = new LiteralIntNode();
		intNode->value = (yyvsp[-1].intVal);
		IdentifierNode* idNode = new IdentifierNode();
		idNode->id = (yyvsp[-3].id);
		node->args.push_back(idNode);
		node->args.push_back(intNode);
        (yyval.expr) = node;
	}
#line 2665 "parser.tab.c"
    break;

  case 63: /* postfixExpression: primaryExpression  */
#line 626 "parser.y"
                            {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 2673 "parser.tab.c"
    break;

  case 64: /* postfixExpression: postfixExpression '[' expression ']'  */
#line 629 "parser.y"
                                               {
		ArrayAccessNode* arrAccess = new ArrayAccessNode();
		arrAccess->array = (ExprNode*)(yyvsp[-3].expr);
		arrAccess->index = (ExprNode*)(yyvsp[-1].expr);
		(yyval.expr) = arrAccess;
	}
#line 2684 "parser.tab.c"
    break;

  case 65: /* postfixExpression: postfixExpression '(' ')'  */
#line 635 "parser.y"
                                    {
		CallNode* node = new CallNode();
		node->callee = (ExprNode*)(yyvsp[-2].expr);
		(yyval.expr) = node;
	}
#line 2694 "parser.tab.c"
    break;

  case 66: /* postfixExpression: postfixExpression '(' argumentExpressionList ')'  */
#line 640 "parser.y"
                                                           {
		CallNode* node = new CallNode();
		node->callee = (ExprNode*)(yyvsp[-3].expr);
		node->arguments = *(yyvsp[-1].exprVec);
		(yyval.expr) = node;
	}
#line 2705 "parser.tab.c"
    break;

  case 67: /* postfixExpression: postfixExpression '.' IDENTIFIER  */
#line 646 "parser.y"
                                           {
		MemberAccessNode* node = new MemberAccessNode();
		node->object = (ExprNode*)(yyvsp[-2].expr);
		node->member = *(yyvsp[0].id);
		(yyval.expr) = node;
	}
#line 2716 "parser.tab.c"
    break;

  case 68: /* postfixExpression: PORTFOLIO_VALUE  */
#line 652 "parser.y"
                          {
		PortfolioStateNode* node = new PortfolioStateNode();
		node->stateType = PortfolioStateType::PORTFOLIO_VALUE;
		(yyval.expr) = node;
	}
#line 2726 "parser.tab.c"
    break;

  case 69: /* postfixExpression: CASH_AVAILABLE  */
#line 657 "parser.y"
                         {
		PortfolioStateNode* node = new PortfolioStateNode();
		node->stateType = PortfolioStateType::CASH_AVAILABLE;
		(yyval.expr) = node;
	}
#line 2736 "parser.tab.c"
    break;

  case 70: /* postfixExpression: POSITION_SHARES  */
#line 662 "parser.y"
                          {
		PortfolioStateNode* node = new PortfolioStateNode();
		node->stateType = PortfolioStateType::POSITION_SHARES;
		(yyval.expr) = node;
	}
#line 2746 "parser.tab.c"
    break;

  case 71: /* postfixExpression: ENTRY_PRICE  */
#line 667 "parser.y"
                      {
		PortfolioStateNode* node = new PortfolioStateNode();
		node->stateType = PortfolioStateType::ENTRY_PRICE;
		(yyval.expr) = node;
	}
#line 2756 "parser.tab.c"
    break;

  case 72: /* postfixExpression: DAYS_IN_POSITION  */
#line 672 "parser.y"
                           {
		PortfolioStateNode* node = new PortfolioStateNode();
		node->stateType = PortfolioStateType::DAYS_IN_POSITION;
		(yyval.expr) = node;
	}
#line 2766 "parser.tab.c"
    break;

  case 73: /* argumentExpressionList: assignmentExpression  */
#line 680 "parser.y"
                               {
		(yyval.exprVec) = new vector<ExprNode*>();
		(yyval.exprVec)->push_back((ExprNode*)(yyvsp[0].expr));
	}
#line 2775 "parser.tab.c"
    break;

  case 74: /* argumentExpressionList: argumentExpressionList ',' assignmentExpression  */
#line 684 "parser.y"
                                                          {
		(yyval.exprVec) = (yyvsp[-2].exprVec);
		(yyval.exprVec)->push_back((ExprNode*)(yyvsp[0].expr));
	}
#line 2784 "parser.tab.c"
    break;

  case 75: /* unaryExpression: postfixExpression  */
#line 691 "parser.y"
                            {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 2792 "parser.tab.c"
    break;

  case 76: /* unaryExpression: unaryOperator castExpression  */
#line 694 "parser.y"
                                       {
		UnaryExprNode* node = new UnaryExprNode();
		node->operand = (ExprNode*)(yyvsp[0].expr);
		if((yyvsp[-1].intVal)==REF){
			node->op = UnaryOpType::REF;
		}
		else if((yyvsp[-1].intVal)=='+'){
			node->op = UnaryOpType::ADD;
		}
		else if((yyvsp[-1].intVal)=='-'){
			node->op = UnaryOpType::SUB;
		}
		else if((yyvsp[-1].intVal)=='~'){
			node->op = UnaryOpType::BITNOT;
		}
		else if((yyvsp[-1].intVal)=='!'){	
			node->op = UnaryOpType::LOGICALNOT;
		}
		(yyval.expr) = node;
	}
#line 2817 "parser.tab.c"
    break;

  case 77: /* unaryOperator: REF  */
#line 717 "parser.y"
              {
		(yyval.intVal) = REF;
	}
#line 2825 "parser.tab.c"
    break;

  case 78: /* unaryOperator: '+'  */
#line 720 "parser.y"
              {
		(yyval.intVal) = '+';
	}
#line 2833 "parser.tab.c"
    break;

  case 79: /* unaryOperator: '-'  */
#line 723 "parser.y"
              {
		(yyval.intVal) = '-';
	}
#line 2841 "parser.tab.c"
    break;

  case 80: /* unaryOperator: '~'  */
#line 726 "parser.y"
              {
		(yyval.intVal) = '~';
	}
#line 2849 "parser.tab.c"
    break;

  case 81: /* unaryOperator: '!'  */
#line 729 "parser.y"
              {
		(yyval.intVal) = '!';
	}
#line 2857 "parser.tab.c"
    break;

  case 82: /* castExpression: unaryExpression  */
#line 735 "parser.y"
                          {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 2865 "parser.tab.c"
    break;

  case 83: /* castExpression: '(' type_name ')' castExpression  */
#line 738 "parser.y"
                                           {
		CastExprNode* node = new CastExprNode();
		node->targetType = (TypeNode*)(yyvsp[-2].type);
		node->expr = (ExprNode*)(yyvsp[0].expr);
		(yyval.expr) = node;
	}
#line 2876 "parser.tab.c"
    break;

  case 84: /* multiplicativeExpression: castExpression  */
#line 747 "parser.y"
                         {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 2884 "parser.tab.c"
    break;

  case 85: /* multiplicativeExpression: multiplicativeExpression '*' castExpression  */
#line 750 "parser.y"
                                                      {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "*";
		(yyval.expr) = node;
	}
#line 2896 "parser.tab.c"
    break;

  case 86: /* multiplicativeExpression: multiplicativeExpression '/' castExpression  */
#line 757 "parser.y"
                                                      {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "/";
		(yyval.expr) = node;

	}
#line 2909 "parser.tab.c"
    break;

  case 87: /* multiplicativeExpression: multiplicativeExpression '%' castExpression  */
#line 765 "parser.y"
                                                      {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "%";
		(yyval.expr) = node;
	}
#line 2921 "parser.tab.c"
    break;

  case 88: /* additiveExpression: multiplicativeExpression  */
#line 775 "parser.y"
                                   {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 2929 "parser.tab.c"
    break;

  case 89: /* additiveExpression: additiveExpression '+' multiplicativeExpression  */
#line 778 "parser.y"
                                                          {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "+";
		(yyval.expr) = node;
	}
#line 2941 "parser.tab.c"
    break;

  case 90: /* additiveExpression: additiveExpression '-' multiplicativeExpression  */
#line 785 "parser.y"
                                                          {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "-";
		(yyval.expr) = node;
	}
#line 2953 "parser.tab.c"
    break;

  case 91: /* shiftExpression: additiveExpression  */
#line 795 "parser.y"
                             {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 2961 "parser.tab.c"
    break;

  case 92: /* shiftExpression: shiftExpression LEFT_OP additiveExpression  */
#line 798 "parser.y"
                                                     {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "<<";
		(yyval.expr) = node;
	}
#line 2973 "parser.tab.c"
    break;

  case 93: /* shiftExpression: shiftExpression RIGHT_OP additiveExpression  */
#line 805 "parser.y"
                                                      {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = ">>";
		(yyval.expr) = node;
	}
#line 2985 "parser.tab.c"
    break;

  case 94: /* relationalExpression: shiftExpression  */
#line 815 "parser.y"
                          {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 2993 "parser.tab.c"
    break;

  case 95: /* relationalExpression: relationalExpression '<' shiftExpression  */
#line 818 "parser.y"
                                                   {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "<";
		(yyval.expr) = node;
	}
#line 3005 "parser.tab.c"
    break;

  case 96: /* relationalExpression: relationalExpression '>' shiftExpression  */
#line 825 "parser.y"
                                                   {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = ">";
		(yyval.expr) = node;
	}
#line 3017 "parser.tab.c"
    break;

  case 97: /* relationalExpression: relationalExpression LEQ shiftExpression  */
#line 832 "parser.y"
                                                   {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "<=";
		(yyval.expr) = node;
	}
#line 3029 "parser.tab.c"
    break;

  case 98: /* relationalExpression: relationalExpression GEQ shiftExpression  */
#line 839 "parser.y"
                                                   {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = ">=";
		(yyval.expr) = node;
	}
#line 3041 "parser.tab.c"
    break;

  case 99: /* equalityExpression: relationalExpression  */
#line 849 "parser.y"
                               {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 3049 "parser.tab.c"
    break;

  case 100: /* equalityExpression: equalityExpression EQ relationalExpression  */
#line 852 "parser.y"
                                                     {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "==";
		(yyval.expr) = node;
	}
#line 3061 "parser.tab.c"
    break;

  case 101: /* equalityExpression: equalityExpression NEQ relationalExpression  */
#line 859 "parser.y"
                                                      {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "!=";
		(yyval.expr) = node;
	}
#line 3073 "parser.tab.c"
    break;

  case 102: /* andExpression: equalityExpression  */
#line 869 "parser.y"
                             {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 3081 "parser.tab.c"
    break;

  case 103: /* andExpression: andExpression '&' equalityExpression  */
#line 872 "parser.y"
                                               {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "&";
		(yyval.expr) = node;
	}
#line 3093 "parser.tab.c"
    break;

  case 104: /* exclusiveOrExpression: andExpression  */
#line 882 "parser.y"
                        {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 3101 "parser.tab.c"
    break;

  case 105: /* exclusiveOrExpression: exclusiveOrExpression '^' andExpression  */
#line 885 "parser.y"
                                                  {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "^";
		(yyval.expr) = node;
	}
#line 3113 "parser.tab.c"
    break;

  case 106: /* inclusiveOrExpression: exclusiveOrExpression  */
#line 895 "parser.y"
                                {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 3121 "parser.tab.c"
    break;

  case 107: /* inclusiveOrExpression: inclusiveOrExpression '|' exclusiveOrExpression  */
#line 898 "parser.y"
                                                          {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "|";
		(yyval.expr) = node;
	}
#line 3133 "parser.tab.c"
    break;

  case 108: /* logicalAndExpression: inclusiveOrExpression  */
#line 908 "parser.y"
                                {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 3141 "parser.tab.c"
    break;

  case 109: /* logicalAndExpression: logicalAndExpression AND inclusiveOrExpression  */
#line 911 "parser.y"
                                                         {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "AND";
		(yyval.expr) = node;
	}
#line 3153 "parser.tab.c"
    break;

  case 110: /* logicalOrExpression: logicalAndExpression  */
#line 921 "parser.y"
                               {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 3161 "parser.tab.c"
    break;

  case 111: /* logicalOrExpression: logicalOrExpression OR logicalAndExpression  */
#line 924 "parser.y"
                                                      {
		BinaryExprNode* node = new BinaryExprNode();
		node->leftOperand = (yyvsp[-2].expr);
		node->rightOperand = (yyvsp[0].expr);
		node->op = "OR";
		(yyval.expr) = node;
	}
#line 3173 "parser.tab.c"
    break;

  case 112: /* conditionalExpression: logicalOrExpression  */
#line 934 "parser.y"
                              {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 3181 "parser.tab.c"
    break;

  case 113: /* conditionalExpression: logicalOrExpression '?' expression ':' conditionalExpression  */
#line 937 "parser.y"
                                                                       {
		ConditionalExprNode* node = new ConditionalExprNode();
		node->condition = (yyvsp[-4].expr);
		node->thenExpr = (yyvsp[-2].expr);
		node->elseExpr = (yyvsp[0].expr);
		(yyval.expr) = node;
	}
#line 3193 "parser.tab.c"
    break;

  case 114: /* assignmentExpression: conditionalExpression  */
#line 947 "parser.y"
                                {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 3201 "parser.tab.c"
    break;

  case 115: /* assignmentExpression: unaryExpression '=' assignmentExpression  */
#line 950 "parser.y"
                                                   {
		AssignmentNode* node = new AssignmentNode();
		node->target = (yyvsp[-2].expr);
		node->value = (yyvsp[0].expr);
		(yyval.expr) = node;
	}
#line 3212 "parser.tab.c"
    break;

  case 116: /* expression: assignmentExpression  */
#line 959 "parser.y"
                               {
		(yyval.expr) = (yyvsp[0].expr);
	}
#line 3220 "parser.tab.c"
    break;

  case 117: /* expression: expression ',' assignmentExpression  */
#line 962 "parser.y"
                                              {
		CommaExprNode* node;
		if((yyvsp[-2].expr)->type == ASTNodeType::CommaExprNode){
			node = (CommaExprNode*)(yyvsp[-2].expr);
		}
		else{
			node = new CommaExprNode();
			node->expressions.push_back((ExprNode*)(yyvsp[-2].expr));
		}
		node->expressions.push_back((ExprNode*)(yyvsp[0].expr));
        (yyval.expr) = node;
	}
#line 3237 "parser.tab.c"
    break;

  case 118: /* declaration: declarationSpecifiers ';'  */
#line 977 "parser.y"
                                    {
		DeclNode* node = new DeclNode();
		node->type = (yyvsp[-1].type);
	}
#line 3246 "parser.tab.c"
    break;

  case 119: /* declaration: declarationSpecifiers initDeclaratorList ';'  */
#line 981 "parser.y"
                                                       {
		DeclNode* node = new DeclNode();
		node->type = (yyvsp[-2].type);
		node->decls = (yyvsp[-1].initDeclVec);
	}
#line 3256 "parser.tab.c"
    break;

  case 120: /* declarationSpecifiers: typeSpecifier  */
#line 989 "parser.y"
                        {
		(yyval.type) = (yyvsp[0].type);
	}
#line 3264 "parser.tab.c"
    break;

  case 121: /* declarationSpecifiers: CONST typeSpecifier  */
#line 992 "parser.y"
                              {
		(yyval.type) = (yyvsp[0].type);
		(yyval.type)->constFlag = true;
	}
#line 3273 "parser.tab.c"
    break;

  case 122: /* initDeclaratorList: initDeclarator  */
#line 999 "parser.y"
                         {
		vector<InitDeclarator*>* initVec = new vector<InitDeclarator*>();
		initVec.push_back((yyvsp[0].initDecl));
		(yyval.initDeclVec) = initVec;
	}
#line 3283 "parser.tab.c"
    break;

  case 123: /* initDeclaratorList: initDeclaratorList ',' initDeclarator  */
#line 1004 "parser.y"
                                                {
		(yyval.initDeclVec) = (yyvsp[-2].initDeclVec);
		(yyval.initDeclVec)->push_back((yyvsp[0].initDecl));
	}
#line 3292 "parser.tab.c"
    break;

  case 124: /* initDeclarator: direct_declarator  */
#line 1011 "parser.y"
                             {
		(yyval.initDecl) = new InitDeclarator();
		(yyval.initDecl)->declarator = (yyvsp[0].declarator);
	}
#line 3301 "parser.tab.c"
    break;

  case 125: /* initDeclarator: direct_declarator '=' initializer  */
#line 1015 "parser.y"
                                            {
		(yyval.initDecl) = new InitDeclarator();
		(yyval.initDecl)->declarator = (yyvsp[-2].declarator);
		(yyval.initDecl)->initializer = (yyvsp[0].init);
	}
#line 3311 "parser.tab.c"
    break;

  case 126: /* typeSpecifier: VOID  */
#line 1024 "parser.y"
               {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::VOID;
		(yyval.type) = node;
	}
#line 3321 "parser.tab.c"
    break;

  case 127: /* typeSpecifier: INT  */
#line 1029 "parser.y"
               {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::INT;
		(yyval.type) = node;
	}
#line 3331 "parser.tab.c"
    break;

  case 128: /* typeSpecifier: FLOAT  */
#line 1034 "parser.y"
                {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::FLOAT;
		(yyval.type) = node;
	}
#line 3341 "parser.tab.c"
    break;

  case 129: /* typeSpecifier: BOOL  */
#line 1039 "parser.y"
           {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::BOOL;
		(yyval.type) = node;
	}
#line 3351 "parser.tab.c"
    break;

  case 130: /* typeSpecifier: STRING  */
#line 1044 "parser.y"
             {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::STRING;
		(yyval.type) = node;
	}
#line 3361 "parser.tab.c"
    break;

  case 131: /* typeSpecifier: RGM  */
#line 1049 "parser.y"
              {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::RGM;
		(yyval.type) = node;
	}
#line 3371 "parser.tab.c"
    break;

  case 132: /* typeSpecifier: TIMESERIES  */
#line 1054 "parser.y"
                     {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::TIMESERIES;
		(yyval.type) = node;
	}
#line 3381 "parser.tab.c"
    break;

  case 133: /* typeSpecifier: groupSpecifier  */
#line 1059 "parser.y"
                         {
		TypeNode* node = new TypeNode();
		node->type = DataTypes::GROUP;
		node->userDefinedFlag = true;
		(yyval.type) = node;
	}
#line 3392 "parser.tab.c"
    break;

  case 134: /* groupSpecifier: GROUP IDENTIFIER '{' group_declarationList '}'  */
#line 1068 "parser.y"
                                                         {
		GroupNode* node = new GroupNode();
		node->id = (yyvsp[-3].id);
		node->members = *(yyvsp[-1].groupDeclList);
		(yyval.group) = node;
	}
#line 3403 "parser.tab.c"
    break;

  case 135: /* groupSpecifier: GROUP '{' group_declarationList '}'  */
#line 1074 "parser.y"
                                              {
		GroupNode* node = new GroupNode();
		node->members = *(yyvsp[-1].groupDeclList);
		(yyval.group) = node;
	}
#line 3413 "parser.tab.c"
    break;

  case 136: /* groupSpecifier: GROUP IDENTIFIER  */
#line 1079 "parser.y"
                           {
		GroupNode* node = new GroupNode();
		node->id = (yyvsp[0].id);
		(yyval.group) = node;
	}
#line 3423 "parser.tab.c"
    break;

  case 137: /* group_declarationList: group_declaration  */
#line 1087 "parser.y"
                            {
		vector<GroupDeclaration*>* vec = new vector<GroupDeclaration*>();
        vec->push_back((yyvsp[0].groupDeclaration));
        (yyval.groupDeclList) = vec;
	}
#line 3433 "parser.tab.c"
    break;

  case 138: /* group_declarationList: group_declarationList group_declaration  */
#line 1092 "parser.y"
                                                  {
		(yyval.groupDeclList) = (yyvsp[-1].groupDeclList);
		(yyval.groupDeclList)->push_back((yyvsp[0].groupDeclaration));
	}
#line 3442 "parser.tab.c"
    break;

  case 139: /* group_declaration: specifier_qualifierList group_declaratorList ';'  */
#line 1099 "parser.y"
                                                           {
		GroupDeclaration* node = new GroupDeclaration();
		node->type= (yyvsp[-2].type);
		node->declarators = *(yyvsp[-1].groupDeclaratorList);
        (yyval.groupDeclaration) = node;
	}
#line 3453 "parser.tab.c"
    break;

  case 140: /* specifier_qualifierList: typeSpecifier  */
#line 1108 "parser.y"
                    {
        (yyval.type) = (yyvsp[0].type);
    }
#line 3461 "parser.tab.c"
    break;

  case 141: /* specifier_qualifierList: CONST specifier_qualifierList  */
#line 1111 "parser.y"
                                    {
        (yyvsp[0].type)->constFlag = true;
        (yyval.type) = (yyvsp[0].type);
    }
#line 3470 "parser.tab.c"
    break;

  case 142: /* specifier_qualifierList: typeSpecifier specifier_qualifierList  */
#line 1115 "parser.y"
                                            {
        (yyval.type) = (yyvsp[-1].type);
    }
#line 3478 "parser.tab.c"
    break;

  case 143: /* specifier_qualifierList: CONST  */
#line 1118 "parser.y"
            {
        TypeNode* node = new TypeNode();
        node->constFlag = true;
        (yyval.type) = node;
    }
#line 3488 "parser.tab.c"
    break;

  case 144: /* group_declaratorList: group_declarator  */
#line 1126 "parser.y"
                           {
		vector<GroupDeclarator*>* groupDeclVec = new vector<GroupDeclarator*>();
        groupDeclVec->push_back((yyvsp[0].groupDeclarator));
        (yyval.groupDeclaratorList) = vec;
	}
#line 3498 "parser.tab.c"
    break;

  case 145: /* group_declaratorList: group_declaratorList ',' group_declarator  */
#line 1131 "parser.y"
                                                    {
		(yyval.groupDeclaratorList) = (yyvsp[-2].groupDeclaratorList);
		(yyval.groupDeclaratorList)->push_back((yyvsp[0].groupDeclarator));
	}
#line 3507 "parser.tab.c"
    break;

  case 146: /* group_declarator: direct_declarator  */
#line 1138 "parser.y"
                            {
		GroupDeclarator* node = new GroupDeclarator();
        node->declarator = (yyvsp[0].declarator);
        (yyval.groupDeclarator) = node;
	}
#line 3517 "parser.tab.c"
    break;

  case 147: /* group_declarator: ':' conditionalExpression  */
#line 1143 "parser.y"
                                    {
		GroupDeclarator* node = new GroupDeclarator();
        node->isBitfieldOnly = true;
        node->bitfield = (yyvsp[0].expr);
        (yyval.groupDeclarator) = node;
	}
#line 3528 "parser.tab.c"
    break;

  case 148: /* group_declarator: direct_declarator ':' conditionalExpression  */
#line 1149 "parser.y"
                                                      {
		GroupDeclarator* node = new GroupDeclarator();
        node->declarator = (yyvsp[-2].declarator);
        node->bitfield = (yyvsp[0].expr);
        (yyval.groupDeclarator) = node;
	}
#line 3539 "parser.tab.c"
    break;

  case 149: /* direct_declarator: IDENTIFIER  */
#line 1158 "parser.y"
                     {
		Declarator* node = new Declarator();
		node->id = (yyvsp[0].id);
		(yyval.declarator) = node;
	}
#line 3549 "parser.tab.c"
    break;

  case 150: /* direct_declarator: '(' direct_declarator ')'  */
#line 1163 "parser.y"
                                    {
		(yyval.declarator) = (yyvsp[-1].declarator);
	}
#line 3557 "parser.tab.c"
    break;

  case 151: /* direct_declarator: direct_declarator '[' conditionalExpression ']'  */
#line 1166 "parser.y"
                                                          {
		(yyval.declarator) = (yyvsp[-3].declarator);
		(yyval.declarator)->arrayFlag = true;
		(yyval.declarator)->arraySize = (yyvsp[-1].expr);
	}
#line 3567 "parser.tab.c"
    break;

  case 152: /* direct_declarator: direct_declarator '[' ']'  */
#line 1171 "parser.y"
                                    {
		(yyval.declarator) = (yyvsp[-2].declarator);
		(yyval.declarator)->arrayFlag = true;
	}
#line 3576 "parser.tab.c"
    break;

  case 153: /* direct_declarator: direct_declarator '(' parameterList ')'  */
#line 1175 "parser.y"
                                                  {
		(yyval.declarator) = (yyvsp[-3].declarator);
		(yyval.declarator)->funcFlag = true;
		(yyval.declarator)->params = *(yyvsp[-1].paramVec);
	}
#line 3586 "parser.tab.c"
    break;

  case 154: /* direct_declarator: direct_declarator '(' identifierList ')'  */
#line 1180 "parser.y"
                                                   {
		(yyval.declarator) = (yyvsp[-3].declarator);
		(yyval.declarator)->funcFlag = true;
		// incomplete
	}
#line 3596 "parser.tab.c"
    break;

  case 155: /* direct_declarator: direct_declarator '(' ')'  */
#line 1185 "parser.y"
                                    {
		(yyval.declarator) = (yyvsp[-2].declarator);
		(yyvsp[-2].declarator)->funcFlag = true;
	}
#line 3605 "parser.tab.c"
    break;

  case 156: /* parameterList: parameter_declaration  */
#line 1192 "parser.y"
                                {
		vector<ParamNode*>* paramList = new vector<ParamNode>();
		paramList->push_back((yyvsp[0].param));
		(yyval.paramVec) = paramList;
	}
#line 3615 "parser.tab.c"
    break;

  case 157: /* parameterList: parameterList ',' parameter_declaration  */
#line 1197 "parser.y"
                                                  {
		(yyval.paramVec) = (yyvsp[-2].paramVec);
		(yyval.paramVec).push_back((yyvsp[0].param));
	}
#line 3624 "parser.tab.c"
    break;

  case 158: /* parameter_declaration: declarationSpecifiers direct_declarator  */
#line 1204 "parser.y"
                                                  {
		ParamNode* node = new ParamNode();
		node->type = (yyvsp[-1].type);
		node->id = (yyvsp[0].declarator)->id;
		(yyval.param) = node;
	}
#line 3635 "parser.tab.c"
    break;

  case 159: /* parameter_declaration: declarationSpecifiers direct_abstract_declarator  */
#line 1210 "parser.y"
                                                           {
		ParamNode* node = new ParamNode();
		node->type = (yyvsp[-1].type);
		(yyval.param) = node;
	}
#line 3645 "parser.tab.c"
    break;

  case 160: /* parameter_declaration: declarationSpecifiers  */
#line 1215 "parser.y"
                                {
		ParamNode* node = new ParamNode();
        node->type = (yyvsp[0].type);
        (yyval.param) = node;
	}
#line 3655 "parser.tab.c"
    break;

  case 161: /* identifierList: IDENTIFIER  */
#line 1223 "parser.y"
                     {
		IdentifierNode* node = new IdentifierNode();
		node->id = (yyvsp[0].id);
		vector<IdentifierNode*>* idList = new vector<IdentifierNode*>();
		idList->push_back(node);
		(yyval.exprVec) = idList;
	}
#line 3667 "parser.tab.c"
    break;

  case 162: /* identifierList: identifierList ',' IDENTIFIER  */
#line 1230 "parser.y"
                                        {
		(yyval.exprVec) = (yyvsp[-2].exprVec);
		IdentifierNode* node = new IdentifierNode();
		node->id = (yyvsp[0].id);
		(yyval.exprVec)->push_back(node);
	}
#line 3678 "parser.tab.c"
    break;

  case 163: /* type_name: specifier_qualifierList  */
#line 1239 "parser.y"
                              {
        (yyval.type) = (yyvsp[0].type);
    }
#line 3686 "parser.tab.c"
    break;

  case 164: /* type_name: specifier_qualifierList direct_abstract_declarator  */
#line 1242 "parser.y"
                                                         {
		(yyval.type) = (yyvsp[-1].type);
        (yyval.type)->abstractDeclarator = (yyvsp[0].declarator);
    }
#line 3695 "parser.tab.c"
    break;

  case 165: /* direct_abstract_declarator: '(' direct_abstract_declarator ')'  */
#line 1249 "parser.y"
                                         {
        (yyval.declarator) = (yyvsp[-1].declarator);
    }
#line 3703 "parser.tab.c"
    break;

  case 166: /* direct_abstract_declarator: '[' ']'  */
#line 1252 "parser.y"
              {
        Declarator* node = new Declarator();
        node->arrayFlag = true;
        (yyval.declarator) = node;
    }
#line 3713 "parser.tab.c"
    break;

  case 167: /* direct_abstract_declarator: '[' conditionalExpression ']'  */
#line 1257 "parser.y"
                                    {
        Declarator* node = new Declarator();
        node->arrayFlag = true;
        node->arraySize = (yyvsp[-1].expr);
        (yyval.declarator) = node;
    }
#line 3724 "parser.tab.c"
    break;

  case 168: /* direct_abstract_declarator: direct_abstract_declarator '[' ']'  */
#line 1263 "parser.y"
                                         {
        (yyval.declarator) = (yyvsp[-2].declarator);
        (yyval.declarator)->arrayFlag = true;
    }
#line 3733 "parser.tab.c"
    break;

  case 169: /* direct_abstract_declarator: direct_abstract_declarator '[' conditionalExpression ']'  */
#line 1267 "parser.y"
                                                               {
        (yyval.declarator) = (yyvsp[-3].declarator);
        (yyval.declarator)->arrayFlag = true;
        (yyval.declarator)->arraySize = (yyvsp[-1].expr);
    }
#line 3743 "parser.tab.c"
    break;

  case 170: /* direct_abstract_declarator: '(' ')'  */
#line 1272 "parser.y"
              {
        Declarator* node = new Declarator();
        node->funcFlag = true;
        (yyval.declarator) = node;
    }
#line 3753 "parser.tab.c"
    break;

  case 171: /* direct_abstract_declarator: '(' parameterList ')'  */
#line 1277 "parser.y"
                            {
        Declarator* node = new Declarator();
        node->funcFlag = true;
        node->params = *(yyvsp[-1].paramVec);
        (yyval.declarator) = node;
    }
#line 3764 "parser.tab.c"
    break;

  case 172: /* direct_abstract_declarator: direct_abstract_declarator '(' ')'  */
#line 1283 "parser.y"
                                         {
        (yyval.declarator) = (yyvsp[-2].declarator);
        (yyval.declarator)->funcFlag = true;
    }
#line 3773 "parser.tab.c"
    break;

  case 173: /* direct_abstract_declarator: direct_abstract_declarator '(' parameterList ')'  */
#line 1287 "parser.y"
                                                       {
        (yyval.declarator) = (yyvsp[-3].declarator);
        (yyval.declarator)->funcFlag = true;
        (yyval.declarator)->params = *(yyvsp[-1].paramVec);
    }
#line 3783 "parser.tab.c"
    break;

  case 174: /* initializer: assignmentExpression  */
#line 1295 "parser.y"
                           {
        Initializer* node = new Initializer();
        node->expr = (yyvsp[0].expr);
        (yyval.init) = node;
    }
#line 3793 "parser.tab.c"
    break;

  case 175: /* initializer: '{' initializerList '}'  */
#line 1300 "parser.y"
                              {
        Initializer* node = new Initializer();
        node->isList = true;
        node->elements = *(yyvsp[-1].initList);
        (yyval.init) = node;
    }
#line 3804 "parser.tab.c"
    break;

  case 176: /* initializer: '{' initializerList ',' '}'  */
#line 1306 "parser.y"
                                  {
        Initializer* node = new Initializer();
        node->isList = true;
        node->elements = *(yyvsp[-2].initList);
        (yyval.init) = node;
    }
#line 3815 "parser.tab.c"
    break;

  case 177: /* initializerList: initializer  */
#line 1315 "parser.y"
                      {
		vector<Initializer*>* initVec = new vector<Initializer*>();
		initVec->push_back((yyvsp[0].init));
		(yyval.initList) = initVec;
	}
#line 3825 "parser.tab.c"
    break;

  case 178: /* initializerList: initializerList ',' initializer  */
#line 1320 "parser.y"
                                          {
		(yyval.initList) = (yyvsp[-2].initList);
		(yyval.initList)->push_back((yyvsp[0].init));
	}
#line 3834 "parser.tab.c"
    break;

  case 179: /* statement: compoundStatement  */
#line 1327 "parser.y"
                            {
		(yyval.stmt) = (yyvsp[0].stmt);
	}
#line 3842 "parser.tab.c"
    break;

  case 180: /* statement: expressionStatement  */
#line 1330 "parser.y"
                              {
		(yyval.stmt) = (yyvsp[0].stmt);
	}
#line 3850 "parser.tab.c"
    break;

  case 181: /* statement: selectionStatement  */
#line 1333 "parser.y"
                             {
		(yyval.stmt) = (yyvsp[0].stmt);
	}
#line 3858 "parser.tab.c"
    break;

  case 182: /* statement: iterationStatement  */
#line 1336 "parser.y"
                             {
		(yyval.stmt) = (yyvsp[0].stmt);
	}
#line 3866 "parser.tab.c"
    break;

  case 183: /* statement: jumpStatement  */
#line 1339 "parser.y"
                        {
		(yyval.stmt) = (yyvsp[0].stmt);
	}
#line 3874 "parser.tab.c"
    break;

  case 184: /* compoundStatement: '{' '}'  */
#line 1345 "parser.y"
              {
        (yyval.stmt) = new CmpdStmtNode();
    }
#line 3882 "parser.tab.c"
    break;

  case 185: /* compoundStatement: '{' statementList '}'  */
#line 1348 "parser.y"
                            {
        (yyval.stmt) = new CmpdStmtNode();
        (yyval.stmt)->statements = (yyvsp[-1].stmtVec); 
    }
#line 3891 "parser.tab.c"
    break;

  case 186: /* compoundStatement: '{' declarationList '}'  */
#line 1352 "parser.y"
                              {
        (yyval.stmt) = new CmpdStmtNode();
        (yyval.stmt)->declarations = (yyvsp[-1].declVec);
    }
#line 3900 "parser.tab.c"
    break;

  case 187: /* compoundStatement: '{' declarationList statementList '}'  */
#line 1356 "parser.y"
                                            {
        (yyval.stmt) = new CmpdStmtNode();
        (yyval.stmt)->declarations = (yyvsp[-2].declVec);
        (yyval.stmt)->statements = (yyvsp[-1].stmtVec);
    }
#line 3910 "parser.tab.c"
    break;

  case 188: /* declarationList: declaration  */
#line 1364 "parser.y"
                  {
        vector<DeclNode*>* vec = new vector<DeclNode*>();
        vec->push_back((yyvsp[0].decl));
        (yyval.declVec) = vec;
    }
#line 3920 "parser.tab.c"
    break;

  case 189: /* declarationList: declarationList declaration  */
#line 1369 "parser.y"
                                  {
        (yyval.declVec) = (yyvsp[-1].declVec);
        (yyval.declVec)->push_back((yyvsp[0].decl));
    }
#line 3929 "parser.tab.c"
    break;

  case 190: /* statementList: statement  */
#line 1376 "parser.y"
                    {
		vector<StmtNode*>* vec = new vector<StmtNode*>();
		vec->push_back((yyvsp[0].stmt));
		(yyval.stmtVec) = (yyvsp[0].stmt);
	}
#line 3939 "parser.tab.c"
    break;

  case 191: /* statementList: statementList statement  */
#line 1381 "parser.y"
                                  {
		(yyval.stmtVec) = (yyvsp[-1].stmtVec);
		(yyval.stmtVec)->push_back((yyvsp[0].stmt));
	}
#line 3948 "parser.tab.c"
    break;

  case 192: /* expressionStatement: ';'  */
#line 1388 "parser.y"
              {
		ExprStmtNode* node = new ExprStmtNode();
		(yyval.stmt) = (StmtNode*)node;
	}
#line 3957 "parser.tab.c"
    break;

  case 193: /* expressionStatement: expression ';'  */
#line 1392 "parser.y"
                         {
		ExprStmtNode* node = new ExprStmtNode();
		node->expr = (yyvsp[-1].expr);
		(yyval.stmt) = (StmtNode*)node;
	}
#line 3967 "parser.tab.c"
    break;

  case 194: /* selectionStatement: IF '(' expression ')' statement  */
#line 1400 "parser.y"
                                                            {
		IfNode* node = new IfNode();
		node->condition = (yyvsp[-2].expr);
		node->thenBranch = (yyvsp[0].stmt);
		(yyval.stmt) = (stmtNode*)node;
	}
#line 3978 "parser.tab.c"
    break;

  case 195: /* selectionStatement: IF '(' expression ')' statement ELSE statement  */
#line 1406 "parser.y"
                                                     {
		IfNode* node = new IfNode();
		node->condition = (yyvsp[-4].expr);
		node->thenBranch = (yyvsp[-2].stmt);
		node->elseBranch = (yyvsp[0].stmt);
		(yyval.stmt) = (stmtNode*)node;
	}
#line 3990 "parser.tab.c"
    break;

  case 196: /* iterationStatement: WHILE '(' expression ')' statement  */
#line 1416 "parser.y"
                                             {
		WhileNode* node = new WhileNode();
		node->condition = (yyvsp[-2].expr);
		node->body = (yyvsp[0].stmt);
		(yyval.stmt) = (StmtNode*)node;
	}
#line 4001 "parser.tab.c"
    break;

  case 197: /* iterationStatement: FOR '(' expressionStatement expressionStatement ')' statement  */
#line 1422 "parser.y"
                                                                        {
		ForNode* node = new ForNode();
		node->init = (yyvsp[-3].stmt);
		node->condition = (yyvsp[-2].stmt);
		node->body = (yyvsp[0].stmt);
		(yyval.stmt) = (StmtNode*)node;
	}
#line 4013 "parser.tab.c"
    break;

  case 198: /* iterationStatement: FOR '(' expressionStatement expressionStatement expression ')' statement  */
#line 1429 "parser.y"
                                                                                   {
		ForNode* node = new ForNode();
		node->init = (yyvsp[-4].stmt);
		node->condition = (yyvsp[-3].stmt);
		node->increment = (yyvsp[-2].expr);
		node->body = (yyvsp[0].stmt);
		(yyval.stmt) = (StmtNode*)node;
	}
#line 4026 "parser.tab.c"
    break;

  case 199: /* jumpStatement: CONTINUE ';'  */
#line 1440 "parser.y"
                       {
		ContinueNode* node = new ContinueNode();
		(yyval.stmt) = (StmtNode*)node;
	}
#line 4035 "parser.tab.c"
    break;

  case 200: /* jumpStatement: BREAK ';'  */
#line 1444 "parser.y"
                    {
		BreakNode* node = new BreakNode();
		(yyval.stmt) = (StmtNode*)node;
	}
#line 4044 "parser.tab.c"
    break;

  case 201: /* jumpStatement: RETURN ';'  */
#line 1448 "parser.y"
                     {
		ReturnNode* node = new ReturnNode();
		(yyval.stmt) = (StmtNode*)node;
	}
#line 4053 "parser.tab.c"
    break;

  case 202: /* jumpStatement: RETURN expression ';'  */
#line 1452 "parser.y"
                                {
		ReturnNode* node = new ReturnNode();
		node->expr = (yyvsp[-1].expr);
		(yyval.stmt) = (StmtNode*)node;
	}
#line 4063 "parser.tab.c"
    break;

  case 203: /* globalDeclaration: function_definition  */
#line 1460 "parser.y"
                          {
        (yyval.node) = new ASTNode();
    }
#line 4071 "parser.tab.c"
    break;

  case 204: /* globalDeclaration: declaration  */
#line 1463 "parser.y"
                  {
        (yyval.node) = new ASTNode();
    }
#line 4079 "parser.tab.c"
    break;

  case 205: /* globalDeclaration: strategyDefinition  */
#line 1466 "parser.y"
                         {
        (yyval.node) = (ASTNode*)(yyvsp[0].strategy);
    }
#line 4087 "parser.tab.c"
    break;

  case 206: /* function_definition: FUN IDENTIFIER '(' ARROW typeSpecifier ')' compoundStatement  */
#line 1472 "parser.y"
                                                                       {
		FuncNode* node = new FuncNode();
		node->name = (yyvsp[-5].id);
		node->returnType = (yyvsp[-2].type);
		node->body = (yyvsp[0].stmt);
		(yyval.func) = node;
	}
#line 4099 "parser.tab.c"
    break;

  case 207: /* function_definition: FUN IDENTIFIER '(' parameterList ARROW typeSpecifier ')' compoundStatement  */
#line 1479 "parser.y"
                                                                                     {
		FuncNode* node = new FuncNode();
		node->name = (yyvsp[-6].id);
		node->returnType = (yyvsp[-2].type);
		node->params = (yyvsp[-4].paramVec);
		node->body = (yyvsp[0].stmt);
		(yyval.func) = node;
	}
#line 4112 "parser.tab.c"
    break;


#line 4116 "parser.tab.c"

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

#line 1489 "parser.y"



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
		cout << "parse successful" << endl;
		progRoot->printNode();
	}
    else
        cout << "Parse Failed" << endl;
    

    fclose(yyin);
    return 0;
}
