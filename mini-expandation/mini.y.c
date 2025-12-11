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
#line 1 "mini.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

int yylex();
void yyerror(char* msg);


#line 82 "mini.y.c"

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

#include "mini.y.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_CHAR = 4,                       /* CHAR  */
  YYSYMBOL_EQ = 5,                         /* EQ  */
  YYSYMBOL_NE = 6,                         /* NE  */
  YYSYMBOL_LT = 7,                         /* LT  */
  YYSYMBOL_LE = 8,                         /* LE  */
  YYSYMBOL_GT = 9,                         /* GT  */
  YYSYMBOL_GE = 10,                        /* GE  */
  YYSYMBOL_UMINUS = 11,                    /* UMINUS  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_FUNC = 15,                      /* FUNC  */
  YYSYMBOL_INPUT = 16,                     /* INPUT  */
  YYSYMBOL_OUTPUT = 17,                    /* OUTPUT  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_FOR = 19,                       /* FOR  */
  YYSYMBOL_SWITCH = 20,                    /* SWITCH  */
  YYSYMBOL_CASE = 21,                      /* CASE  */
  YYSYMBOL_DEFAULT = 22,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 23,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 24,                  /* CONTINUE  */
  YYSYMBOL_STRUCT = 25,                    /* STRUCT  */
  YYSYMBOL_INTEGER = 26,                   /* INTEGER  */
  YYSYMBOL_IDENTIFIER = 27,                /* IDENTIFIER  */
  YYSYMBOL_TEXT = 28,                      /* TEXT  */
  YYSYMBOL_CHARACTER = 29,                 /* CHARACTER  */
  YYSYMBOL_30_ = 30,                       /* '+'  */
  YYSYMBOL_31_ = 31,                       /* '-'  */
  YYSYMBOL_32_ = 32,                       /* '*'  */
  YYSYMBOL_33_ = 33,                       /* '/'  */
  YYSYMBOL_34_ = 34,                       /* '{'  */
  YYSYMBOL_35_ = 35,                       /* '}'  */
  YYSYMBOL_36_ = 36,                       /* ';'  */
  YYSYMBOL_37_ = 37,                       /* ','  */
  YYSYMBOL_38_ = 38,                       /* '['  */
  YYSYMBOL_39_ = 39,                       /* ']'  */
  YYSYMBOL_40_ = 40,                       /* '('  */
  YYSYMBOL_41_ = 41,                       /* ')'  */
  YYSYMBOL_42_ = 42,                       /* '='  */
  YYSYMBOL_43_ = 43,                       /* '.'  */
  YYSYMBOL_44_ = 44,                       /* '&'  */
  YYSYMBOL_45_ = 45,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_program = 47,                   /* program  */
  YYSYMBOL_global_declarations = 48,       /* global_declarations  */
  YYSYMBOL_struct_decl = 49,               /* struct_decl  */
  YYSYMBOL_struct_member_list = 50,        /* struct_member_list  */
  YYSYMBOL_struct_member = 51,             /* struct_member  */
  YYSYMBOL_declaration = 52,               /* declaration  */
  YYSYMBOL_type_specifier_value = 53,      /* type_specifier_value  */
  YYSYMBOL_variable_list = 54,             /* variable_list  */
  YYSYMBOL_var_decl = 55,                  /* var_decl  */
  YYSYMBOL_struct_specifier = 56,          /* struct_specifier  */
  YYSYMBOL_function = 57,                  /* function  */
  YYSYMBOL_function_head = 58,             /* function_head  */
  YYSYMBOL_parameter_list = 59,            /* parameter_list  */
  YYSYMBOL_statement = 60,                 /* statement  */
  YYSYMBOL_block = 61,                     /* block  */
  YYSYMBOL_declaration_list = 62,          /* declaration_list  */
  YYSYMBOL_statement_list = 63,            /* statement_list  */
  YYSYMBOL_assignment_statement = 64,      /* assignment_statement  */
  YYSYMBOL_lvalue_expr = 65,               /* lvalue_expr  */
  YYSYMBOL_access_chain = 66,              /* access_chain  */
  YYSYMBOL_access_item = 67,               /* access_item  */
  YYSYMBOL_expression = 68,                /* expression  */
  YYSYMBOL_argument_list = 69,             /* argument_list  */
  YYSYMBOL_expression_list = 70,           /* expression_list  */
  YYSYMBOL_input_statement = 71,           /* input_statement  */
  YYSYMBOL_output_statement = 72,          /* output_statement  */
  YYSYMBOL_return_statement = 73,          /* return_statement  */
  YYSYMBOL_if_statement = 74,              /* if_statement  */
  YYSYMBOL_loop_start = 75,                /* loop_start  */
  YYSYMBOL_loop_end = 76,                  /* loop_end  */
  YYSYMBOL_for_start = 77,                 /* for_start  */
  YYSYMBOL_for_end = 78,                   /* for_end  */
  YYSYMBOL_switch_start = 79,              /* switch_start  */
  YYSYMBOL_switch_end = 80,                /* switch_end  */
  YYSYMBOL_call_statement = 81,            /* call_statement  */
  YYSYMBOL_call_expression = 82,           /* call_expression  */
  YYSYMBOL_while_statement = 83,           /* while_statement  */
  YYSYMBOL_for_statement = 84,             /* for_statement  */
  YYSYMBOL_switch_statement = 85,          /* switch_statement  */
  YYSYMBOL_case_list = 86,                 /* case_list  */
  YYSYMBOL_case_clause = 87,               /* case_clause  */
  YYSYMBOL_default_clause = 88             /* default_clause  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   387

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  184

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


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
       2,     2,     2,     2,     2,     2,     2,     2,    44,     2,
      40,    41,    32,    30,    37,    31,    43,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,    36,
       2,    42,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    46,    46,    55,    56,    58,    60,    65,   108,   109,
     114,   140,   147,   152,   157,   165,   171,   180,   188,   196,
     207,   217,   223,   230,   238,   242,   247,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   266,   270,
     277,   284,   287,   293,   294,   301,   305,   315,   319,   326,
     330,   337,   341,   347,   351,   355,   359,   363,   367,   371,
     375,   379,   383,   387,   391,   395,   399,   403,   407,   411,
     423,   427,   435,   438,   441,   442,   449,   455,   461,   467,
     475,   479,   486,   495,   502,   511,   518,   525,   531,   553,
     579,   585,   591,   598,   599,   603,   610,   611
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "CHAR", "EQ",
  "NE", "LT", "LE", "GT", "GE", "UMINUS", "IF", "ELSE", "WHILE", "FUNC",
  "INPUT", "OUTPUT", "RETURN", "FOR", "SWITCH", "CASE", "DEFAULT", "BREAK",
  "CONTINUE", "STRUCT", "INTEGER", "IDENTIFIER", "TEXT", "CHARACTER",
  "'+'", "'-'", "'*'", "'/'", "'{'", "'}'", "';'", "','", "'['", "']'",
  "'('", "')'", "'='", "'.'", "'&'", "':'", "$accept", "program",
  "global_declarations", "struct_decl", "struct_member_list",
  "struct_member", "declaration", "type_specifier_value", "variable_list",
  "var_decl", "struct_specifier", "function", "function_head",
  "parameter_list", "statement", "block", "declaration_list",
  "statement_list", "assignment_statement", "lvalue_expr", "access_chain",
  "access_item", "expression", "argument_list", "expression_list",
  "input_statement", "output_statement", "return_statement",
  "if_statement", "loop_start", "loop_end", "for_start", "for_end",
  "switch_start", "switch_end", "call_statement", "call_expression",
  "while_statement", "for_statement", "switch_statement", "case_list",
  "case_clause", "default_clause", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-164)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-98)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -164,    14,   266,  -164,  -164,  -164,  -164,    -4,  -164,  -164,
    -164,   -12,  -164,  -164,   -11,     9,    12,    30,    41,  -164,
      32,     5,    36,  -164,  -164,   -12,  -164,    24,    39,     3,
    -164,   -12,    44,  -164,    53,    56,  -164,    67,  -164,    68,
    -164,  -164,  -164,  -164,  -164,  -164,   296,  -164,    52,    71,
      85,    20,    62,    73,    74,    79,    80,   -16,    62,  -164,
    -164,  -164,   217,    81,    82,    83,    86,    89,  -164,    91,
    -164,  -164,  -164,    62,    62,  -164,  -164,  -164,    15,  -164,
    -164,    62,    62,    62,   101,  -164,   354,  -164,   354,     4,
      62,  -164,  -164,    62,    55,   102,    -6,  -164,   135,  -164,
    -164,  -164,    62,  -164,  -164,  -164,  -164,   141,   148,    55,
    -164,  -164,   154,    -6,  -164,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    94,   191,   272,   354,    92,
      95,  -164,  -164,    62,   354,    56,  -164,    96,  -164,    77,
      77,    77,    77,    77,    77,     8,     8,  -164,  -164,    62,
     118,  -164,  -164,    62,   354,   123,    56,  -164,   347,  -164,
     354,    56,  -164,     4,  -164,  -164,  -164,   128,    76,  -164,
     144,   130,  -164,  -164,    56,   131,   317,   153,  -164,   317,
     241,  -164,  -164,   193
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,    22,    12,    13,     0,    23,     4,
       6,     0,    14,     5,     0,    20,    17,     0,     0,    15,
      26,     0,     0,    18,    11,     0,    24,     0,     0,     0,
       8,     0,     0,    16,     0,     0,    20,     0,     9,     0,
      19,    25,    41,    21,     7,    10,     0,    39,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    48,     0,    42,
      43,    36,     0,     0,     0,     0,     0,     0,    32,     0,
      34,    33,    35,     0,     0,    76,    71,    65,    48,    78,
      66,     0,     0,     0,     0,    70,    77,    67,    79,     0,
       0,    37,    38,     0,     0,     0,    47,    49,     0,    40,
      44,    27,     0,    28,    29,    31,    30,     0,     0,     0,
      57,    69,     0,    48,    68,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    74,     0,
      73,    51,    50,     0,    45,     0,    82,     0,    64,    58,
      59,    60,    61,    62,    63,    53,    54,    55,    56,     0,
       0,    52,    88,     0,    46,    80,     0,    89,     0,    86,
      75,     0,    83,     0,    93,    81,    90,     0,    96,    84,
       0,     0,    94,    87,     0,     0,     0,     0,    85,     0,
       0,    92,    91,     0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -164,  -164,  -164,  -164,  -164,   161,   137,   -10,  -164,   -13,
    -164,  -164,  -164,  -164,   -60,   -35,  -164,  -163,   -84,   -45,
    -164,    97,   -48,    93,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,  -164
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     9,    29,    30,    10,    11,    18,    19,
      12,    13,    14,    27,    60,    61,    46,    62,    63,    85,
      96,    97,   128,   129,   130,    65,    66,    67,    68,   156,
     166,   174,   182,   164,   177,    69,    87,    70,    71,    72,
     168,   172,   173
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    64,   100,    86,    88,   125,     5,     6,     5,     6,
      98,    31,    33,   180,     3,    16,   183,    64,    39,    31,
      17,    76,    93,    15,    94,   107,   108,    95,    28,    20,
      28,   113,    93,   110,   111,   112,    58,    95,    37,   114,
     123,   124,   126,    21,    64,   127,    77,    78,    79,    80,
      22,    81,    82,    93,   134,   109,    76,    23,    95,    26,
      83,    34,    32,    76,    84,    35,    36,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,    24,    25,   167,
      41,    77,    78,    40,    80,   154,    81,    82,    77,    78,
      42,    80,    73,    81,    82,    83,   -72,   170,   171,    84,
     155,   158,    83,    44,    45,   160,    84,   121,   122,   123,
     124,    74,    75,    89,    90,    91,    92,   101,    64,   103,
     100,   162,   104,   100,   102,   105,   165,   106,   113,   131,
     149,    64,   153,   152,    64,    64,   161,   157,    64,   178,
     115,   116,   117,   118,   119,   120,   115,   116,   117,   118,
     119,   120,   159,   115,   116,   117,   118,   119,   120,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   169,
     175,   121,   122,   123,   124,   176,   179,   133,   121,   122,
     123,   124,   135,    59,   121,   122,   123,   124,   181,   136,
      38,     0,     0,   132,    47,   138,   115,   116,   117,   118,
     119,   120,   137,     0,     0,    48,     0,    49,     0,    50,
      51,    52,    53,    54,   -95,   -95,    55,    56,    47,     0,
      57,   121,   122,   123,   124,    58,     0,    42,   -95,    48,
       0,    49,   150,    50,    51,    52,    53,    54,     0,     0,
      55,    56,    47,     0,    57,     0,     0,     0,     0,    58,
       0,    42,    99,    48,     0,    49,     0,    50,    51,    52,
      53,    54,     0,     0,    55,    56,    -2,     4,    57,     5,
       6,     0,     0,    58,     0,    42,   -97,   115,   116,   117,
     118,   119,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     0,     8,     0,     0,     0,    47,     0,     5,
       6,     0,   121,   122,   123,   124,     0,     0,    48,     0,
      49,   151,    50,    51,    52,    53,    54,     0,    47,    55,
      56,    28,     0,    57,     0,     0,     0,     0,    58,    48,
      42,    49,     0,    50,    51,    52,    53,    54,     0,     0,
      55,    56,     0,     0,    57,     0,     0,     0,     0,    58,
       0,    42,   115,   116,   117,   118,   119,   120,     0,   115,
     116,   117,   118,   119,   120,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   121,   122,   123,
     124,     0,     0,   163,   121,   122,   123,   124
};

static const yytype_int16 yycheck[] =
{
      35,    46,    62,    51,    52,    89,     3,     4,     3,     4,
      58,    21,    25,   176,     0,    27,   179,    62,    31,    29,
      32,     1,    38,    27,    40,    73,    74,    43,    25,    40,
      25,    27,    38,    81,    82,    83,    32,    43,    35,    84,
      32,    33,    90,    34,    89,    93,    26,    27,    28,    29,
      38,    31,    32,    38,   102,    40,     1,    27,    43,    27,
      40,    37,    26,     1,    44,    41,    27,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,    36,    37,   163,
      27,    26,    27,    39,    29,   133,    31,    32,    26,    27,
      34,    29,    40,    31,    32,    40,    41,    21,    22,    44,
     135,   149,    40,    36,    36,   153,    44,    30,    31,    32,
      33,    40,    27,    40,    40,    36,    36,    36,   163,    36,
     180,   156,    36,   183,    42,    36,   161,    36,    27,    27,
      36,   176,    37,    41,   179,   180,    13,    41,   183,   174,
       5,     6,     7,     8,     9,    10,     5,     6,     7,     8,
       9,    10,    34,     5,     6,     7,     8,     9,    10,     5,
       6,     7,     8,     9,    10,    30,    31,    32,    33,    41,
      26,    30,    31,    32,    33,    45,    45,    42,    30,    31,
      32,    33,    41,    46,    30,    31,    32,    33,    35,    41,
      29,    -1,    -1,    96,     1,    41,     5,     6,     7,     8,
       9,    10,   109,    -1,    -1,    12,    -1,    14,    -1,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     1,    -1,
      27,    30,    31,    32,    33,    32,    -1,    34,    35,    12,
      -1,    14,    41,    16,    17,    18,    19,    20,    -1,    -1,
      23,    24,     1,    -1,    27,    -1,    -1,    -1,    -1,    32,
      -1,    34,    35,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    -1,    -1,    23,    24,     0,     1,    27,     3,
       4,    -1,    -1,    32,    -1,    34,    35,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    27,    -1,    -1,    -1,     1,    -1,     3,
       4,    -1,    30,    31,    32,    33,    -1,    -1,    12,    -1,
      14,    39,    16,    17,    18,    19,    20,    -1,     1,    23,
      24,    25,    -1,    27,    -1,    -1,    -1,    -1,    32,    12,
      34,    14,    -1,    16,    17,    18,    19,    20,    -1,    -1,
      23,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    32,
      -1,    34,     5,     6,     7,     8,     9,    10,    -1,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    36,    30,    31,    32,    33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    47,    48,     0,     1,     3,     4,    25,    27,    49,
      52,    53,    56,    57,    58,    27,    27,    32,    54,    55,
      40,    34,    38,    27,    36,    37,    27,    59,    25,    50,
      51,    53,    26,    55,    37,    41,    27,    35,    51,    55,
      39,    27,    34,    61,    36,    36,    62,     1,    12,    14,
      16,    17,    18,    19,    20,    23,    24,    27,    32,    52,
      60,    61,    63,    64,    65,    71,    72,    73,    74,    81,
      83,    84,    85,    40,    40,    27,     1,    26,    27,    28,
      29,    31,    32,    40,    44,    65,    68,    82,    68,    40,
      40,    36,    36,    38,    40,    43,    66,    67,    68,    35,
      60,    36,    42,    36,    36,    36,    36,    68,    68,    40,
      68,    68,    68,    27,    65,     5,     6,     7,     8,     9,
      10,    30,    31,    32,    33,    64,    68,    68,    68,    69,
      70,    27,    67,    42,    68,    41,    41,    69,    41,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    36,
      41,    39,    41,    37,    68,    61,    75,    41,    68,    34,
      68,    13,    61,    36,    79,    61,    76,    64,    86,    41,
      21,    22,    87,    88,    77,    26,    45,    80,    61,    45,
      63,    35,    78,    63
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    48,    48,    49,    50,    50,
      51,    52,    53,    53,    53,    54,    54,    55,    55,    55,
      56,    57,    57,    58,    59,    59,    59,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      61,    62,    62,    63,    63,    64,    64,    65,    65,    66,
      66,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    70,    70,    71,    72,    72,    73,
      74,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    86,    87,    88,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     6,     1,     2,
       3,     3,     1,     1,     1,     1,     3,     1,     2,     4,
       2,     5,     1,     1,     1,     3,     0,     2,     2,     2,
       2,     2,     1,     1,     1,     1,     1,     2,     2,     1,
       4,     0,     2,     1,     2,     3,     4,     2,     1,     1,
       2,     2,     3,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     2,     2,
       1,     1,     0,     1,     1,     3,     2,     2,     2,     2,
       5,     7,     0,     0,     0,     0,     0,     0,     4,     4,
       7,    11,    10,     0,     2,     4,     0,     3
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
  case 2: /* program: global_declarations  */
#line 47 "mini.y"
{
    tac_last = (yyvsp[0].tac);
    tac_complete();
}
#line 1329 "mini.y.c"
    break;

  case 3: /* global_declarations: %empty  */
#line 55 "mini.y"
    { (yyval.tac) = NULL; }
#line 1335 "mini.y.c"
    break;

  case 4: /* global_declarations: global_declarations struct_decl  */
#line 57 "mini.y"
    { (yyval.tac) = (yyvsp[-1].tac); }
#line 1341 "mini.y.c"
    break;

  case 5: /* global_declarations: global_declarations function  */
#line 59 "mini.y"
    { (yyval.tac) = join_tac((yyvsp[-1].tac), (yyvsp[0].tac)); }
#line 1347 "mini.y.c"
    break;

  case 6: /* global_declarations: global_declarations declaration  */
#line 61 "mini.y"
    { (yyval.tac) = join_tac((yyvsp[-1].tac), (yyvsp[0].tac)); }
#line 1353 "mini.y.c"
    break;

  case 7: /* struct_decl: STRUCT IDENTIFIER '{' struct_member_list '}' ';'  */
#line 66 "mini.y"
    {
        SYM *tag = lookup_sym(sym_tab_global, (yyvsp[-4].string));
        if (tag) {
            error("struct '%s' redefined", (yyvsp[-4].string));
        }
        tag = mk_sym();
        tag->type = SYM_STRUCT_TAG;
        tag->name = (yyvsp[-4].string);
        
        printf("=== Defining struct %s ===\n", (yyvsp[-4].string));
        
        tag->etc = (yyvsp[-2].tac);
        
        printf("Final struct layout verification:\n");
        int offset = 0;
        for (TAC *p = (TAC*)tag->etc; p; p = p->prev) {
            if (p->a && p->a->name) {
                int member_size = 4;
                if (p->a->is_array) {
                    if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
                        int element_size = calculate_struct_size(p->a->struct_tag);
                        member_size = p->a->array_size * element_size;
                    } else {
                        member_size = p->a->array_size * 4;
                    }
                } else if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
                    member_size = calculate_struct_size(p->a->struct_tag);
                }
                printf("  %s: offset=%d, size=%d\n", p->a->name, offset, member_size);
                offset += member_size;
            }
        }
        printf("Total struct size: %d\n", offset);
        printf("=== End struct %s ===\n\n", (yyvsp[-4].string));
        
        insert_sym(&sym_tab_global, tag);
    }
#line 1395 "mini.y.c"
    break;

  case 9: /* struct_member_list: struct_member_list struct_member  */
#line 110 "mini.y"
    { (yyval.tac) = join_tac((yyvsp[-1].tac), (yyvsp[0].tac)); }
#line 1401 "mini.y.c"
    break;

  case 10: /* struct_member: type_specifier_value var_decl ';'  */
#line 115 "mini.y"
    {
        SYM *member_sym = mk_sym();
        member_sym->name = strdup((yyvsp[-1].decl).name);
        if (!member_sym->name) {
            error("memory allocation failed for member name");
        }
        member_sym->type = SYM_VAR;
        member_sym->data_type = (yyvsp[-2].type_info).type;
        member_sym->is_ptr = (yyvsp[-1].decl).is_ptr;
        member_sym->is_array = (yyvsp[-1].decl).is_array;
        member_sym->array_size = (yyvsp[-1].decl).array_size;
        member_sym->struct_tag = (yyvsp[-2].type_info).struct_tag;
        
        SYM *type_sym = mk_sym();
        type_sym->type = ((yyvsp[-2].type_info).type == TYPE_INT) ? SYM_INT : 
                        ((yyvsp[-2].type_info).type == TYPE_CHAR) ? SYM_CHAR : SYM_STRUCT_TAG;
        
        TAC *member_tac = mk_tac(TAC_UNDEF, member_sym, type_sym, NULL);
        if (!member_tac) {
            error("memory allocation failed for member TAC");
        }
        (yyval.tac) = member_tac;
    }
#line 1429 "mini.y.c"
    break;

  case 11: /* declaration: type_specifier_value variable_list ';'  */
#line 141 "mini.y"
{
    (yyval.tac) = (yyvsp[-1].tac);
}
#line 1437 "mini.y.c"
    break;

  case 12: /* type_specifier_value: INT  */
#line 148 "mini.y"
    {
        (yyval.type_info).type = TYPE_INT;
        (yyval.type_info).struct_tag = NULL;
    }
#line 1446 "mini.y.c"
    break;

  case 13: /* type_specifier_value: CHAR  */
#line 153 "mini.y"
    {
        (yyval.type_info).type = TYPE_CHAR;
        (yyval.type_info).struct_tag = NULL;
    }
#line 1455 "mini.y.c"
    break;

  case 14: /* type_specifier_value: struct_specifier  */
#line 158 "mini.y"
    {
        (yyval.type_info).type = TYPE_STRUCT;
        (yyval.type_info).struct_tag = (yyvsp[0].sym);
    }
#line 1464 "mini.y.c"
    break;

  case 15: /* variable_list: var_decl  */
#line 166 "mini.y"
    {
        int dt = (yyvsp[-1].type_info).type;
        SYM *st = (yyvsp[-1].type_info).struct_tag;
        (yyval.tac) = declare_typed_var_ext((yyvsp[0].decl).name, dt, (yyvsp[0].decl).is_ptr, (yyvsp[0].decl).is_array, (yyvsp[0].decl).array_size, st);
    }
#line 1474 "mini.y.c"
    break;

  case 16: /* variable_list: variable_list ',' var_decl  */
#line 172 "mini.y"
    {
        int dt = (yyvsp[-3].type_info).type;
        SYM *st = (yyvsp[-3].type_info).struct_tag;
        (yyval.tac) = join_tac((yyvsp[-2].tac), declare_typed_var_ext((yyvsp[0].decl).name, dt, (yyvsp[0].decl).is_ptr, (yyvsp[0].decl).is_array, (yyvsp[0].decl).array_size, st));
    }
#line 1484 "mini.y.c"
    break;

  case 17: /* var_decl: IDENTIFIER  */
#line 181 "mini.y"
    {
        (yyval.decl).name = (yyvsp[0].string);
        (yyval.decl).is_ptr = 0;
        (yyval.decl).is_array = 0;
        (yyval.decl).array_size = 0;
        (yyval.decl).struct_tag = NULL;
    }
#line 1496 "mini.y.c"
    break;

  case 18: /* var_decl: '*' IDENTIFIER  */
#line 189 "mini.y"
    {
        (yyval.decl).name = (yyvsp[0].string);
        (yyval.decl).is_ptr = 1;
        (yyval.decl).is_array = 0;
        (yyval.decl).array_size = 0;
        (yyval.decl).struct_tag = NULL;
    }
#line 1508 "mini.y.c"
    break;

  case 19: /* var_decl: IDENTIFIER '[' INTEGER ']'  */
#line 197 "mini.y"
    {
        (yyval.decl).name = (yyvsp[-3].string);
        (yyval.decl).is_ptr = 0;
        (yyval.decl).is_array = 1;
        (yyval.decl).array_size = atoi((yyvsp[-1].string));
        (yyval.decl).struct_tag = NULL;
    }
#line 1520 "mini.y.c"
    break;

  case 20: /* struct_specifier: STRUCT IDENTIFIER  */
#line 208 "mini.y"
    {
        SYM *tag = lookup_sym(sym_tab_global, (yyvsp[0].string));
        if (!tag | tag->type != SYM_STRUCT_TAG) {
            error("undefined struct '%s'", (yyvsp[0].string));
        }
        (yyval.sym) = tag;
    }
#line 1532 "mini.y.c"
    break;

  case 21: /* function: function_head '(' parameter_list ')' block  */
#line 218 "mini.y"
{
    (yyval.tac)=do_func((yyvsp[-4].sym), (yyvsp[-2].tac), (yyvsp[0].tac));
    scope=0;
    sym_tab_local=NULL;
}
#line 1542 "mini.y.c"
    break;

  case 22: /* function: error  */
#line 224 "mini.y"
{
    error("Bad function syntax");
    (yyval.tac)=NULL;
}
#line 1551 "mini.y.c"
    break;

  case 23: /* function_head: IDENTIFIER  */
#line 231 "mini.y"
{
    (yyval.sym)=declare_func((yyvsp[0].string));
    scope=1;
    sym_tab_local=NULL;
}
#line 1561 "mini.y.c"
    break;

  case 24: /* parameter_list: IDENTIFIER  */
#line 239 "mini.y"
{
    (yyval.tac)=declare_para((yyvsp[0].string));
}
#line 1569 "mini.y.c"
    break;

  case 25: /* parameter_list: parameter_list ',' IDENTIFIER  */
#line 243 "mini.y"
{
    (yyval.tac)=join_tac((yyvsp[-2].tac), declare_para((yyvsp[0].string)));
}
#line 1577 "mini.y.c"
    break;

  case 26: /* parameter_list: %empty  */
#line 247 "mini.y"
{
    (yyval.tac)=NULL;
}
#line 1585 "mini.y.c"
    break;

  case 37: /* statement: BREAK ';'  */
#line 263 "mini.y"
{
    (yyval.tac) = do_break();
}
#line 1593 "mini.y.c"
    break;

  case 38: /* statement: CONTINUE ';'  */
#line 267 "mini.y"
{
    (yyval.tac) = do_continue();
}
#line 1601 "mini.y.c"
    break;

  case 39: /* statement: error  */
#line 271 "mini.y"
{
    error("Bad statement syntax");
    (yyval.tac)=NULL;
}
#line 1610 "mini.y.c"
    break;

  case 40: /* block: '{' declaration_list statement_list '}'  */
#line 278 "mini.y"
{
    (yyval.tac)=join_tac((yyvsp[-2].tac), (yyvsp[-1].tac));
}
#line 1618 "mini.y.c"
    break;

  case 41: /* declaration_list: %empty  */
#line 284 "mini.y"
{
    (yyval.tac)=NULL;
}
#line 1626 "mini.y.c"
    break;

  case 42: /* declaration_list: declaration_list declaration  */
#line 288 "mini.y"
{
    (yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1634 "mini.y.c"
    break;

  case 44: /* statement_list: statement_list statement  */
#line 295 "mini.y"
{
    (yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1642 "mini.y.c"
    break;

  case 45: /* assignment_statement: lvalue_expr '=' expression  */
#line 302 "mini.y"
    {
        (yyval.tac) = do_lvalue_assign((yyvsp[-2].lvalue), (yyvsp[0].exp));
    }
#line 1650 "mini.y.c"
    break;

  case 46: /* assignment_statement: '*' expression '=' expression  */
#line 306 "mini.y"
    {
        if (!(yyvsp[-2].exp)->ret->is_ptr) error("assign to non-pointer");
        TAC *code = mk_tac(TAC_STORE, (yyvsp[-2].exp)->ret, (yyvsp[0].exp)->ret, NULL);
        code->prev = join_tac((yyvsp[-2].exp)->tac, (yyvsp[0].exp)->tac);
        (yyval.tac) = code;
    }
#line 1661 "mini.y.c"
    break;

  case 47: /* lvalue_expr: IDENTIFIER access_chain  */
#line 316 "mini.y"
    {
        (yyval.lvalue) = mk_lvalue((yyvsp[-1].string), (yyvsp[0].access_node));
    }
#line 1669 "mini.y.c"
    break;

  case 48: /* lvalue_expr: IDENTIFIER  */
#line 320 "mini.y"
    {
        (yyval.lvalue) = mk_lvalue((yyvsp[0].string), NULL);
    }
#line 1677 "mini.y.c"
    break;

  case 49: /* access_chain: access_item  */
#line 327 "mini.y"
    {
        (yyval.access_node) = (yyvsp[0].access_node);
    }
#line 1685 "mini.y.c"
    break;

  case 50: /* access_chain: access_chain access_item  */
#line 331 "mini.y"
    {
        (yyval.access_node) = append_access((yyvsp[-1].access_node), (yyvsp[0].access_node));
    }
#line 1693 "mini.y.c"
    break;

  case 51: /* access_item: '.' IDENTIFIER  */
#line 338 "mini.y"
    {
        (yyval.access_node) = mk_access_member((yyvsp[0].string));
    }
#line 1701 "mini.y.c"
    break;

  case 52: /* access_item: '[' expression ']'  */
#line 342 "mini.y"
    {
        (yyval.access_node) = mk_access_index((yyvsp[-1].exp));
    }
#line 1709 "mini.y.c"
    break;

  case 53: /* expression: expression '+' expression  */
#line 348 "mini.y"
{
    (yyval.exp)=do_bin(TAC_ADD, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1717 "mini.y.c"
    break;

  case 54: /* expression: expression '-' expression  */
#line 352 "mini.y"
{
    (yyval.exp)=do_bin(TAC_SUB, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1725 "mini.y.c"
    break;

  case 55: /* expression: expression '*' expression  */
#line 356 "mini.y"
{
    (yyval.exp)=do_bin(TAC_MUL, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1733 "mini.y.c"
    break;

  case 56: /* expression: expression '/' expression  */
#line 360 "mini.y"
{
    (yyval.exp)=do_bin(TAC_DIV, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1741 "mini.y.c"
    break;

  case 57: /* expression: '-' expression  */
#line 364 "mini.y"
{
    (yyval.exp)=do_un(TAC_NEG, (yyvsp[0].exp));
}
#line 1749 "mini.y.c"
    break;

  case 58: /* expression: expression EQ expression  */
#line 368 "mini.y"
{
    (yyval.exp)=do_cmp(TAC_EQ, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1757 "mini.y.c"
    break;

  case 59: /* expression: expression NE expression  */
#line 372 "mini.y"
{
    (yyval.exp)=do_cmp(TAC_NE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1765 "mini.y.c"
    break;

  case 60: /* expression: expression LT expression  */
#line 376 "mini.y"
{
    (yyval.exp)=do_cmp(TAC_LT, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1773 "mini.y.c"
    break;

  case 61: /* expression: expression LE expression  */
#line 380 "mini.y"
{
    (yyval.exp)=do_cmp(TAC_LE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1781 "mini.y.c"
    break;

  case 62: /* expression: expression GT expression  */
#line 384 "mini.y"
{
    (yyval.exp)=do_cmp(TAC_GT, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1789 "mini.y.c"
    break;

  case 63: /* expression: expression GE expression  */
#line 388 "mini.y"
{
    (yyval.exp)=do_cmp(TAC_GE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1797 "mini.y.c"
    break;

  case 64: /* expression: '(' expression ')'  */
#line 392 "mini.y"
{
    (yyval.exp)=(yyvsp[-1].exp);
}
#line 1805 "mini.y.c"
    break;

  case 65: /* expression: INTEGER  */
#line 396 "mini.y"
{
    (yyval.exp)=mk_exp(NULL, mk_const(atoi((yyvsp[0].string))), NULL);
}
#line 1813 "mini.y.c"
    break;

  case 66: /* expression: CHARACTER  */
#line 400 "mini.y"
{
    (yyval.exp) = mk_exp(NULL, mk_char_const((yyvsp[0].string)[0]), NULL);
}
#line 1821 "mini.y.c"
    break;

  case 67: /* expression: call_expression  */
#line 404 "mini.y"
{
    (yyval.exp)=(yyvsp[0].exp);
}
#line 1829 "mini.y.c"
    break;

  case 68: /* expression: '&' lvalue_expr  */
#line 408 "mini.y"
{
    (yyval.exp) = do_lvalue_addr((yyvsp[0].lvalue));
}
#line 1837 "mini.y.c"
    break;

  case 69: /* expression: '*' expression  */
#line 412 "mini.y"
{
    if (!(yyvsp[0].exp)->ret->is_ptr) {
        error("dereference of non-pointer");
    }
    SYM *tmp = mk_tmp();
    tmp->data_type = (yyvsp[0].exp)->ret->data_type;
    tmp->is_ptr = 0;
    TAC *code = mk_tac(TAC_DEREF, tmp, (yyvsp[0].exp)->ret, NULL);
    code->prev = (yyvsp[0].exp)->tac;
    (yyval.exp) = mk_exp(NULL, tmp, code);
}
#line 1853 "mini.y.c"
    break;

  case 70: /* expression: lvalue_expr  */
#line 424 "mini.y"
{
    (yyval.exp) = do_lvalue_access((yyvsp[0].lvalue));
}
#line 1861 "mini.y.c"
    break;

  case 71: /* expression: error  */
#line 428 "mini.y"
{
    error("Bad expression syntax");
    (yyval.exp)=mk_exp(NULL, NULL, NULL);
}
#line 1870 "mini.y.c"
    break;

  case 72: /* argument_list: %empty  */
#line 435 "mini.y"
{
    (yyval.exp)=NULL;
}
#line 1878 "mini.y.c"
    break;

  case 75: /* expression_list: expression_list ',' expression  */
#line 443 "mini.y"
{
    (yyvsp[0].exp)->next=(yyvsp[-2].exp);
    (yyval.exp)=(yyvsp[0].exp);
}
#line 1887 "mini.y.c"
    break;

  case 76: /* input_statement: INPUT IDENTIFIER  */
#line 450 "mini.y"
{
    (yyval.tac)=do_input(get_var((yyvsp[0].string)));
}
#line 1895 "mini.y.c"
    break;

  case 77: /* output_statement: OUTPUT expression  */
#line 456 "mini.y"
{
    TAC *output_tac = mk_tac(TAC_OUTPUT, (yyvsp[0].exp)->ret, NULL, NULL);
    output_tac->prev = (yyvsp[0].exp)->tac;
    (yyval.tac) = output_tac;
}
#line 1905 "mini.y.c"
    break;

  case 78: /* output_statement: OUTPUT TEXT  */
#line 462 "mini.y"
{
    (yyval.tac)=do_output(mk_text((yyvsp[0].string)));
}
#line 1913 "mini.y.c"
    break;

  case 79: /* return_statement: RETURN expression  */
#line 468 "mini.y"
{
    TAC *t=mk_tac(TAC_RETURN, (yyvsp[0].exp)->ret, NULL, NULL);
    t->prev=(yyvsp[0].exp)->tac;
    (yyval.tac)=t;
}
#line 1923 "mini.y.c"
    break;

  case 80: /* if_statement: IF '(' expression ')' block  */
#line 476 "mini.y"
{
    (yyval.tac)=do_if((yyvsp[-2].exp), (yyvsp[0].tac));
}
#line 1931 "mini.y.c"
    break;

  case 81: /* if_statement: IF '(' expression ')' block ELSE block  */
#line 480 "mini.y"
{
    (yyval.tac)=do_test((yyvsp[-4].exp), (yyvsp[-2].tac), (yyvsp[0].tac));
}
#line 1939 "mini.y.c"
    break;

  case 82: /* loop_start: %empty  */
#line 486 "mini.y"
{
    (yyval.sym) = mk_label(mk_lstr(next_label++));
    // 创建一个临时的 continue 标签（占位符，稍后会被更新）
    SYM *temp_continue = mk_label(mk_lstr(next_label++));
    push_loop_context((yyval.sym), temp_continue);
}
#line 1950 "mini.y.c"
    break;

  case 83: /* loop_end: %empty  */
#line 495 "mini.y"
{
    pop_break_label();
    (yyval.tac) = NULL;
}
#line 1959 "mini.y.c"
    break;

  case 84: /* for_start: %empty  */
#line 502 "mini.y"
{
    (yyval.sym) = mk_label(mk_lstr(next_label++));
    // 创建一个临时的 continue 标签（占位符，稍后会被更新）
    SYM *temp_continue = mk_label(mk_lstr(next_label++));
    push_loop_context((yyval.sym), temp_continue);
}
#line 1970 "mini.y.c"
    break;

  case 85: /* for_end: %empty  */
#line 511 "mini.y"
{
    pop_break_label();
    (yyval.tac) = NULL;
}
#line 1979 "mini.y.c"
    break;

  case 86: /* switch_start: %empty  */
#line 518 "mini.y"
{
    (yyval.sym) = mk_label(mk_lstr(next_label++));
    push_break_label((yyval.sym));
}
#line 1988 "mini.y.c"
    break;

  case 87: /* switch_end: %empty  */
#line 525 "mini.y"
{
    pop_break_label();
    (yyval.tac) = NULL;
}
#line 1997 "mini.y.c"
    break;

  case 88: /* call_statement: IDENTIFIER '(' argument_list ')'  */
#line 532 "mini.y"
{
    TAC *args_tac = NULL;
    EXP *arg = (yyvsp[-1].exp);
    while (arg) {
        TAC *actual = mk_tac(TAC_ACTUAL, arg->ret, NULL, NULL);
        actual->prev = join_tac(args_tac, arg->tac);
        args_tac = actual;
        arg = arg->next;
    }
    
    SYM *func = get_func((yyvsp[-3].string));
    if (!func) {
        error("undefined function '%s'", (yyvsp[-3].string));
    }
    
    TAC *call_tac = mk_tac(TAC_CALL, NULL, func, NULL);
    call_tac->prev = args_tac;
    (yyval.tac) = call_tac;
}
#line 2021 "mini.y.c"
    break;

  case 89: /* call_expression: IDENTIFIER '(' argument_list ')'  */
#line 554 "mini.y"
{
    TAC *args_tac = NULL;
    EXP *arg = (yyvsp[-1].exp);
    while (arg) {
        TAC *actual = mk_tac(TAC_ACTUAL, arg->ret, NULL, NULL);
        actual->prev = join_tac(args_tac, arg->tac);
        args_tac = actual;
        arg = arg->next;
    }
    
    SYM *func = get_func((yyvsp[-3].string));
    if (!func) {
        error("undefined function '%s'", (yyvsp[-3].string));
    }
    
    SYM *ret_var = mk_tmp();
    ret_var->data_type = TYPE_INT;
    
    TAC *call_tac = mk_tac(TAC_CALL, ret_var, func, NULL);
    call_tac->prev = args_tac;
    
    (yyval.exp) = mk_exp(NULL, ret_var, call_tac);
}
#line 2049 "mini.y.c"
    break;

  case 90: /* while_statement: WHILE '(' expression ')' loop_start block loop_end  */
#line 580 "mini.y"
{
    (yyval.tac) = do_while_with_context((yyvsp[-4].exp), (yyvsp[-1].tac), (yyvsp[-2].sym), (yyvsp[0].tac));
}
#line 2057 "mini.y.c"
    break;

  case 91: /* for_statement: FOR '(' assignment_statement ';' expression ';' assignment_statement ')' for_start block for_end  */
#line 586 "mini.y"
{
    (yyval.tac) = do_for_with_context((yyvsp[-8].tac), (yyvsp[-6].exp), (yyvsp[-4].tac), (yyvsp[-1].tac), (yyvsp[-2].sym), (yyvsp[0].tac));
}
#line 2065 "mini.y.c"
    break;

  case 92: /* switch_statement: SWITCH '(' expression ')' '{' switch_start case_list default_clause switch_end '}'  */
#line 592 "mini.y"
{
    (yyval.tac) = do_switch_with_context((yyvsp[-7].exp), (yyvsp[-3].tac), (yyvsp[-2].tac), (yyvsp[-4].sym), (yyvsp[-1].tac));
}
#line 2073 "mini.y.c"
    break;

  case 93: /* case_list: %empty  */
#line 598 "mini.y"
                                { (yyval.tac) = NULL; }
#line 2079 "mini.y.c"
    break;

  case 94: /* case_list: case_list case_clause  */
#line 599 "mini.y"
                                { (yyval.tac) = join_tac((yyvsp[-1].tac), (yyvsp[0].tac)); }
#line 2085 "mini.y.c"
    break;

  case 95: /* case_clause: CASE INTEGER ':' statement_list  */
#line 604 "mini.y"
    {
        (yyval.tac) = do_case(atoi((yyvsp[-2].string)), (yyvsp[0].tac));
    }
#line 2093 "mini.y.c"
    break;

  case 96: /* default_clause: %empty  */
#line 610 "mini.y"
                                { (yyval.tac) = NULL; }
#line 2099 "mini.y.c"
    break;

  case 97: /* default_clause: DEFAULT ':' statement_list  */
#line 612 "mini.y"
    {
        (yyval.tac) = do_default((yyvsp[0].tac));
    }
#line 2107 "mini.y.c"
    break;


#line 2111 "mini.y.c"

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

#line 617 "mini.y"


void yyerror(char* msg) 
{
    fprintf(stderr, "%s: line %d\n", msg, yylineno);
    exit(0);
}
