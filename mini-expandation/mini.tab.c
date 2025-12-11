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


#line 82 "mini.tab.c"

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


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    CHAR = 259,                    /* CHAR  */
    EQ = 260,                      /* EQ  */
    NE = 261,                      /* NE  */
    LT = 262,                      /* LT  */
    LE = 263,                      /* LE  */
    GT = 264,                      /* GT  */
    GE = 265,                      /* GE  */
    UMINUS = 266,                  /* UMINUS  */
    IF = 267,                      /* IF  */
    ELSE = 268,                    /* ELSE  */
    WHILE = 269,                   /* WHILE  */
    FUNC = 270,                    /* FUNC  */
    INPUT = 271,                   /* INPUT  */
    OUTPUT = 272,                  /* OUTPUT  */
    RETURN = 273,                  /* RETURN  */
    FOR = 274,                     /* FOR  */
    SWITCH = 275,                  /* SWITCH  */
    CASE = 276,                    /* CASE  */
    DEFAULT = 277,                 /* DEFAULT  */
    BREAK = 278,                   /* BREAK  */
    STRUCT = 279,                  /* STRUCT  */
    DEREF = 280,                   /* DEREF  */
    INTEGER = 281,                 /* INTEGER  */
    IDENTIFIER = 282,              /* IDENTIFIER  */
    TEXT = 283,                    /* TEXT  */
    CHARACTER = 284                /* CHARACTER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "mini.y"

    char character;
    char *string;
    SYM *sym;
    TAC *tac;
    EXP *exp;
    int integer;
    struct { char *name; int is_ptr; int is_array; int array_size; } decl;

#line 168 "mini.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



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
  YYSYMBOL_STRUCT = 24,                    /* STRUCT  */
  YYSYMBOL_DEREF = 25,                     /* DEREF  */
  YYSYMBOL_INTEGER = 26,                   /* INTEGER  */
  YYSYMBOL_IDENTIFIER = 27,                /* IDENTIFIER  */
  YYSYMBOL_TEXT = 28,                      /* TEXT  */
  YYSYMBOL_CHARACTER = 29,                 /* CHARACTER  */
  YYSYMBOL_30_ = 30,                       /* '+'  */
  YYSYMBOL_31_ = 31,                       /* '-'  */
  YYSYMBOL_32_ = 32,                       /* '*'  */
  YYSYMBOL_33_ = 33,                       /* '/'  */
  YYSYMBOL_34_ = 34,                       /* '.'  */
  YYSYMBOL_35_ = 35,                       /* '{'  */
  YYSYMBOL_36_ = 36,                       /* '}'  */
  YYSYMBOL_37_ = 37,                       /* ';'  */
  YYSYMBOL_38_ = 38,                       /* ','  */
  YYSYMBOL_39_ = 39,                       /* '['  */
  YYSYMBOL_40_ = 40,                       /* ']'  */
  YYSYMBOL_41_ = 41,                       /* '('  */
  YYSYMBOL_42_ = 42,                       /* ')'  */
  YYSYMBOL_43_ = 43,                       /* '='  */
  YYSYMBOL_44_ = 44,                       /* '&'  */
  YYSYMBOL_45_ = 45,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_program = 47,                   /* program  */
  YYSYMBOL_function_declaration_list = 48, /* function_declaration_list  */
  YYSYMBOL_struct_var_list = 49,           /* struct_var_list  */
  YYSYMBOL_function_declaration = 50,      /* function_declaration  */
  YYSYMBOL_struct_definition = 51,         /* struct_definition  */
  YYSYMBOL_struct_member_list = 52,        /* struct_member_list  */
  YYSYMBOL_struct_member = 53,             /* struct_member  */
  YYSYMBOL_declaration = 54,               /* declaration  */
  YYSYMBOL_type_specifier_value = 55,      /* type_specifier_value  */
  YYSYMBOL_variable_list = 56,             /* variable_list  */
  YYSYMBOL_var_decl = 57,                  /* var_decl  */
  YYSYMBOL_function = 58,                  /* function  */
  YYSYMBOL_function_head = 59,             /* function_head  */
  YYSYMBOL_parameter_list = 60,            /* parameter_list  */
  YYSYMBOL_statement = 61,                 /* statement  */
  YYSYMBOL_block = 62,                     /* block  */
  YYSYMBOL_declaration_list = 63,          /* declaration_list  */
  YYSYMBOL_statement_list = 64,            /* statement_list  */
  YYSYMBOL_assignment_statement = 65,      /* assignment_statement  */
  YYSYMBOL_expression = 66,                /* expression  */
  YYSYMBOL_argument_list = 67,             /* argument_list  */
  YYSYMBOL_expression_list = 68,           /* expression_list  */
  YYSYMBOL_input_statement = 69,           /* input_statement  */
  YYSYMBOL_output_statement = 70,          /* output_statement  */
  YYSYMBOL_return_statement = 71,          /* return_statement  */
  YYSYMBOL_if_statement = 72,              /* if_statement  */
  YYSYMBOL_loop_start = 73,                /* loop_start  */
  YYSYMBOL_loop_end = 74,                  /* loop_end  */
  YYSYMBOL_for_start = 75,                 /* for_start  */
  YYSYMBOL_for_end = 76,                   /* for_end  */
  YYSYMBOL_switch_start = 77,              /* switch_start  */
  YYSYMBOL_switch_end = 78,                /* switch_end  */
  YYSYMBOL_call_statement = 79,            /* call_statement  */
  YYSYMBOL_call_expression = 80,           /* call_expression  */
  YYSYMBOL_while_statement = 81,           /* while_statement  */
  YYSYMBOL_for_statement = 82,             /* for_statement  */
  YYSYMBOL_switch_statement = 83,          /* switch_statement  */
  YYSYMBOL_case_list = 84,                 /* case_list  */
  YYSYMBOL_case_clause = 85,               /* case_clause  */
  YYSYMBOL_default_clause = 86             /* default_clause  */
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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   470

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  191

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
      41,    42,    32,    30,    38,    31,    34,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,    37,
       2,    43,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
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
       0,    42,    42,    49,    50,    56,    61,    62,    63,    66,
      83,    84,    90,   103,   107,   131,   132,   136,   140,   146,
     153,   160,   169,   175,   182,   190,   194,   199,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   218,
     225,   232,   235,   241,   242,   249,   253,   261,   289,   323,
     327,   331,   335,   339,   343,   347,   351,   355,   359,   363,
     367,   371,   375,   379,   413,   449,   453,   457,   469,   482,
     490,   493,   496,   497,   504,   510,   520,   526,   534,   538,
     545,   552,   559,   566,   573,   580,   586,   592,   598,   604,
     610,   617,   618,   622,   629,   630
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
  "STRUCT", "DEREF", "INTEGER", "IDENTIFIER", "TEXT", "CHARACTER", "'+'",
  "'-'", "'*'", "'/'", "'.'", "'{'", "'}'", "';'", "','", "'['", "']'",
  "'('", "')'", "'='", "'&'", "':'", "$accept", "program",
  "function_declaration_list", "struct_var_list", "function_declaration",
  "struct_definition", "struct_member_list", "struct_member",
  "declaration", "type_specifier_value", "variable_list", "var_decl",
  "function", "function_head", "parameter_list", "statement", "block",
  "declaration_list", "statement_list", "assignment_statement",
  "expression", "argument_list", "expression_list", "input_statement",
  "output_statement", "return_statement", "if_statement", "loop_start",
  "loop_end", "for_start", "for_end", "switch_start", "switch_end",
  "call_statement", "call_expression", "while_statement", "for_statement",
  "switch_statement", "case_list", "case_clause", "default_clause", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-178)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-96)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      62,  -178,  -178,  -178,   -19,  -178,    34,   161,  -178,  -178,
    -178,   -17,  -178,    -2,    37,  -178,  -178,    29,    25,    74,
    -178,    54,  -178,   173,    48,    61,  -178,  -178,   -17,  -178,
      42,    13,  -178,   -17,  -178,    50,  -178,    67,    70,    59,
    -178,    65,  -178,  -178,  -178,  -178,  -178,  -178,   122,   436,
      68,    79,    97,    47,    66,    86,    90,    96,   108,  -178,
      60,  -178,    66,    66,    66,   110,  -178,  -178,  -178,   155,
     107,   400,   113,   115,   118,  -178,   131,  -178,  -178,  -178,
    -178,    66,    66,  -178,  -178,   -20,  -178,    66,   406,   406,
     248,    66,  -178,   120,    66,   241,    66,   136,   -29,   288,
    -178,  -178,  -178,  -178,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,   156,  -178,  -178,  -178,  -178,   294,
     301,    66,   241,   136,   165,    89,   157,   307,   345,   406,
     151,   159,   406,    66,  -178,    84,    84,    84,    84,    84,
      84,   126,   126,   136,   136,   152,    70,  -178,   356,   167,
    -178,    66,   163,   160,   164,    66,   406,    66,   197,    70,
    -178,  -178,   392,  -178,    66,   406,   406,    70,  -178,   248,
    -178,   406,  -178,  -178,   170,   158,  -178,   187,   171,  -178,
    -178,    70,   176,   221,   182,  -178,   221,   188,  -178,  -178,
       6
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    23,    15,    16,     0,    24,     0,     0,     3,     8,
       7,     0,     6,     0,     0,     1,     4,    19,     0,     0,
      17,    27,     5,     0,     0,     0,    20,    13,     0,    25,
       0,     0,    10,     0,    14,     0,    18,     0,     0,     0,
      11,     0,    21,    26,    41,    22,     9,    12,     0,    39,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    65,     0,     0,     0,     0,    42,    43,    37,     0,
       0,     0,     0,     0,     0,    33,     0,    66,    35,    34,
      36,     0,     0,    74,    69,    62,    76,     0,    75,    77,
       0,     0,    38,     0,     0,     0,     0,    53,    68,     0,
      67,    40,    44,    28,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,    30,    32,    31,     0,
       0,     0,     0,    68,     0,    62,     0,     0,     0,    72,
       0,    71,    45,     0,    60,    54,    55,    56,    57,    58,
      59,    49,    50,    51,    52,    64,     0,    80,     0,     0,
      64,     0,     0,    63,    87,     0,    46,     0,    78,     0,
      63,    87,     0,    84,     0,    73,    48,     0,    81,     0,
      91,    47,    79,    88,     0,    94,    82,     0,     0,    92,
      85,     0,     0,     0,     0,    83,     0,     0,    90,    89,
       0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,  -178,  -178,   218,  -178,  -178,   195,   179,    46,
    -178,    18,  -178,  -178,  -178,   -68,   -38,  -178,  -177,   -86,
     -51,   106,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     6,     7,    24,     8,     9,    31,    32,    10,    11,
      19,    20,    12,    13,    30,    67,    68,    48,    69,    70,
      71,   130,   131,    72,    73,    74,    75,   159,   173,   181,
     189,   170,   184,    76,    77,    78,    79,    80,   175,   179,
     180
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,   102,    88,    89,   126,   124,   187,    49,    14,   190,
      17,    97,    98,    99,   133,    18,     2,     3,    50,   121,
      51,   122,    52,    53,    54,    55,    56,   -93,   -93,    57,
     119,   120,    59,    60,    15,    61,   123,    62,    63,    21,
     127,    44,   -93,   128,   129,   132,    36,    64,    84,    39,
      65,    41,    26,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,     1,    22,     2,     3,    84,    25,    33,
     148,   129,    23,    59,    85,    86,    61,    33,    62,    87,
      37,    29,   156,   174,    38,    34,     4,    35,    64,     5,
      42,    65,    59,    85,    43,    61,    46,    62,    87,    94,
     162,    95,    47,    96,   165,    44,   166,    64,   158,    81,
      65,    27,    28,   171,   110,   111,   112,   113,   124,   102,
      82,   168,   102,    49,    83,     2,     3,    90,    94,   172,
     122,    91,    96,    92,    50,    93,    51,   100,    52,    53,
      54,    55,    56,   185,   103,    57,    58,    22,    59,    60,
     115,    61,   116,    62,    63,   117,    49,    44,   112,   113,
     124,    -2,     1,    64,     2,     3,    65,    50,   118,    51,
     124,    52,    53,    54,    55,    56,     2,     3,    57,   177,
     178,    59,    60,   145,    61,     4,    62,    63,     5,    49,
      44,   101,   150,   154,   151,   157,    64,   155,   163,    65,
      50,   -86,    51,   164,    52,    53,    54,    55,    56,   161,
     167,    57,   176,   182,    59,    60,   183,    61,   188,    62,
      63,   186,    49,    44,   -95,    16,    40,    66,   149,    64,
       0,     0,    65,    50,     0,    51,     0,    52,    53,    54,
      55,    56,    84,     0,    57,     0,     0,    59,    60,    84,
      61,     0,    62,    63,     0,     0,    44,     0,     0,     0,
       0,     0,    64,     0,     0,    65,     0,    59,    85,     0,
      61,     0,    62,    87,    59,   125,     0,    61,     0,    62,
      63,     0,    64,   -70,     0,    65,     0,     0,     0,    64,
       0,     0,    65,   104,   105,   106,   107,   108,   109,   104,
     105,   106,   107,   108,   109,     0,   104,   105,   106,   107,
     108,   109,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   124,     0,   110,   111,   112,   113,   124,     0,
     134,   110,   111,   112,   113,   124,   146,   110,   111,   112,
     113,   124,     0,   147,     0,     0,     0,     0,     0,   152,
     104,   105,   106,   107,   108,   109,     0,     0,     0,     0,
       0,   104,   105,   106,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   124,
       0,     0,     0,     0,     0,   153,   110,   111,   112,   113,
     124,     0,     0,     0,     0,     0,   160,   104,   105,   106,
     107,   108,   109,     0,     0,   104,   105,   106,   107,   108,
     109,   104,   105,   106,   107,   108,   109,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   124,     0,     0,   169,
     110,   111,   112,   113,   114,     0,   110,   111,   112,   113,
     124,   -69,   -69,   -69,   -69,   -69,   -69,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -69,     0,     0,   -69,
     -69
};

static const yytype_int16 yycheck[] =
{
      38,    69,    53,    54,    90,    34,   183,     1,    27,   186,
      27,    62,    63,    64,    43,    32,     3,     4,    12,    39,
      14,    41,    16,    17,    18,    19,    20,    21,    22,    23,
      81,    82,    26,    27,     0,    29,    87,    31,    32,    41,
      91,    35,    36,    94,    95,    96,    28,    41,     1,    36,
      44,    33,    27,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     1,    27,     3,     4,     1,    39,    23,
     121,   122,    35,    26,    27,    28,    29,    31,    31,    32,
      38,    27,   133,   169,    42,    37,    24,    26,    41,    27,
      40,    44,    26,    27,    27,    29,    37,    31,    32,    39,
     151,    41,    37,    43,   155,    35,   157,    41,   146,    41,
      44,    37,    38,   164,    30,    31,    32,    33,    34,   187,
      41,   159,   190,     1,    27,     3,     4,    41,    39,   167,
      41,    41,    43,    37,    12,    27,    14,    27,    16,    17,
      18,    19,    20,   181,    37,    23,    24,    27,    26,    27,
      37,    29,    37,    31,    32,    37,     1,    35,    32,    33,
      34,     0,     1,    41,     3,     4,    44,    12,    37,    14,
      34,    16,    17,    18,    19,    20,     3,     4,    23,    21,
      22,    26,    27,    27,    29,    24,    31,    32,    27,     1,
      35,    36,    27,    42,    37,    43,    41,    38,    35,    44,
      12,    37,    14,    43,    16,    17,    18,    19,    20,    42,
      13,    23,    42,    26,    26,    27,    45,    29,    36,    31,
      32,    45,     1,    35,    36,     7,    31,    48,   122,    41,
      -1,    -1,    44,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,     1,    -1,    23,    -1,    -1,    26,    27,     1,
      29,    -1,    31,    32,    -1,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    44,    -1,    26,    27,    -1,
      29,    -1,    31,    32,    26,    27,    -1,    29,    -1,    31,
      32,    -1,    41,    42,    -1,    44,    -1,    -1,    -1,    41,
      -1,    -1,    44,     5,     6,     7,     8,     9,    10,     5,
       6,     7,     8,     9,    10,    -1,     5,     6,     7,     8,
       9,    10,     5,     6,     7,     8,     9,    10,    30,    31,
      32,    33,    34,    -1,    30,    31,    32,    33,    34,    -1,
      42,    30,    31,    32,    33,    34,    42,    30,    31,    32,
      33,    34,    -1,    42,    -1,    -1,    -1,    -1,    -1,    42,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    40,     5,     6,     7,
       8,     9,    10,    -1,    -1,     5,     6,     7,     8,     9,
      10,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    -1,    -1,    37,
      30,    31,    32,    33,    34,    -1,    30,    31,    32,    33,
      34,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    33,
      34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,    24,    27,    47,    48,    50,    51,
      54,    55,    58,    59,    27,     0,    50,    27,    32,    56,
      57,    41,    27,    35,    49,    39,    27,    37,    38,    27,
      60,    52,    53,    55,    37,    26,    57,    38,    42,    36,
      53,    57,    40,    27,    35,    62,    37,    37,    63,     1,
      12,    14,    16,    17,    18,    19,    20,    23,    24,    26,
      27,    29,    31,    32,    41,    44,    54,    61,    62,    64,
      65,    66,    69,    70,    71,    72,    79,    80,    81,    82,
      83,    41,    41,    27,     1,    27,    28,    32,    66,    66,
      41,    41,    37,    27,    39,    41,    43,    66,    66,    66,
      27,    36,    61,    37,     5,     6,     7,     8,     9,    10,
      30,    31,    32,    33,    34,    37,    37,    37,    37,    66,
      66,    39,    41,    66,    34,    27,    65,    66,    66,    66,
      67,    68,    66,    43,    42,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    27,    42,    42,    66,    67,
      27,    37,    42,    40,    42,    38,    66,    43,    62,    73,
      40,    42,    66,    35,    43,    66,    66,    13,    62,    37,
      77,    66,    62,    74,    65,    84,    42,    21,    22,    85,
      86,    75,    26,    45,    78,    62,    45,    64,    36,    76,
      64
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    50,    50,    50,    51,
      52,    52,    53,    54,    54,    55,    55,    56,    56,    57,
      57,    57,    58,    58,    59,    60,    60,    60,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      62,    63,    63,    64,    64,    65,    65,    65,    65,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      67,    67,    68,    68,    69,    70,    70,    71,    72,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    84,    85,    86,    86
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     6,
       1,     2,     3,     3,     4,     1,     1,     1,     3,     1,
       2,     4,     5,     1,     1,     1,     3,     0,     2,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     2,     1,
       4,     0,     2,     1,     2,     3,     4,     6,     5,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     4,     3,     1,     1,     2,     2,     1,
       0,     1,     1,     3,     2,     2,     2,     2,     5,     7,
       0,     0,     0,     0,     0,     0,     4,     4,     7,    11,
      10,     0,     2,     4,     0,     3
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
  case 2: /* program: function_declaration_list  */
#line 43 "mini.y"
{
	tac_last=(yyvsp[0].tac);
	tac_complete();
}
#line 1425 "mini.tab.c"
    break;

  case 4: /* function_declaration_list: function_declaration_list function_declaration  */
#line 51 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1433 "mini.tab.c"
    break;

  case 5: /* struct_var_list: IDENTIFIER  */
#line 57 "mini.y"
{
    (yyval.string) = (yyvsp[0].string);
}
#line 1441 "mini.tab.c"
    break;

  case 9: /* struct_definition: STRUCT IDENTIFIER '{' struct_member_list '}' ';'  */
#line 67 "mini.y"
{
    // $2 是结构体名（如 "student"）
    // $4 是总大小（由 struct_member_list 返回）
    SYM *st = mk_sym();
    st->type = SYM_STRUCT;
    st->name = (yyvsp[-4].string);
    st->value = (yyvsp[-2].integer);  // 存储结构体总大小（字节）
    // 检查是否重定义
    if (lookup_sym(sym_tab_global, (yyvsp[-4].string))) {
        error("struct '%s' redefined", (yyvsp[-4].string));
    }
    insert_sym(&sym_tab_global, st);
    (yyval.tac) = NULL;
}
#line 1460 "mini.tab.c"
    break;

  case 11: /* struct_member_list: struct_member_list struct_member  */
#line 85 "mini.y"
{
    (yyval.integer) = (yyvsp[-1].integer) + (yyvsp[0].integer);
}
#line 1468 "mini.tab.c"
    break;

  case 12: /* struct_member: type_specifier_value var_decl ';'  */
#line 91 "mini.y"
{
    // 计算该成员的大小
    int size;
    if ((yyvsp[-1].decl).is_array) {
        size = (yyvsp[-1].decl).array_size * 4;  // 简化：int/char 都按 4 字节
    } else {
        size = 4;
    }
    (yyval.integer) = size;
}
#line 1483 "mini.tab.c"
    break;

  case 13: /* declaration: type_specifier_value variable_list ';'  */
#line 104 "mini.y"
{
    (yyval.tac) = (yyvsp[-1].tac);
}
#line 1491 "mini.tab.c"
    break;

  case 14: /* declaration: STRUCT IDENTIFIER struct_var_list ';'  */
#line 108 "mini.y"
{
    SYM *st_def = lookup_sym(sym_tab_global, (yyvsp[-2].string));
    if (!st_def || st_def->type != SYM_STRUCT) {
        error("undefined struct '%s'", (yyvsp[-2].string));
    }
    int size = st_def->value;
    TAC *code = NULL;
    // 假设 struct_var_list 返回一个名字列表（我们用简单方式处理）
    // 为简化，我们让 struct_var_list 只支持一个变量
    char *name = (yyvsp[-1].string);
    SYM *sym = mk_sym();
    sym->type = SYM_VAR;
    sym->name = name;
    sym->is_struct = 1;
    sym->struct_name = (yyvsp[-2].string);  // 保存结构体类型名
    sym->size = size;       // 总大小
    sym->scope = scope;
    sym->offset = -1;
    if (scope) insert_sym(&sym_tab_local, sym);
    else insert_sym(&sym_tab_global, sym);
    (yyval.tac) = mk_tac(TAC_VAR, sym, NULL, NULL);
}
#line 1518 "mini.tab.c"
    break;

  case 15: /* type_specifier_value: INT  */
#line 131 "mini.y"
                            { (yyval.integer) = TYPE_INT; }
#line 1524 "mini.tab.c"
    break;

  case 16: /* type_specifier_value: CHAR  */
#line 132 "mini.y"
                            { (yyval.integer) = TYPE_CHAR; }
#line 1530 "mini.tab.c"
    break;

  case 17: /* variable_list: var_decl  */
#line 137 "mini.y"
    {
        (yyval.tac) = declare_typed_var_ext((yyvsp[0].decl).name, (yyvsp[-1].integer), (yyvsp[0].decl).is_ptr, (yyvsp[0].decl).is_array, (yyvsp[0].decl).array_size);
    }
#line 1538 "mini.tab.c"
    break;

  case 18: /* variable_list: variable_list ',' var_decl  */
#line 141 "mini.y"
    {
        (yyval.tac) = join_tac((yyvsp[-2].tac), declare_typed_var_ext((yyvsp[0].decl).name, (yyvsp[-3].integer), (yyvsp[0].decl).is_ptr, (yyvsp[0].decl).is_array, (yyvsp[0].decl).array_size));
    }
#line 1546 "mini.tab.c"
    break;

  case 19: /* var_decl: IDENTIFIER  */
#line 147 "mini.y"
{
    (yyval.decl).name = (yyvsp[0].string);
    (yyval.decl).is_ptr = 0;
    (yyval.decl).is_array = 0;
    (yyval.decl).array_size = 0;
}
#line 1557 "mini.tab.c"
    break;

  case 20: /* var_decl: '*' IDENTIFIER  */
#line 154 "mini.y"
{
    (yyval.decl).name = (yyvsp[0].string);
    (yyval.decl).is_ptr = 1;
    (yyval.decl).is_array = 0;
    (yyval.decl).array_size = 0;
}
#line 1568 "mini.tab.c"
    break;

  case 21: /* var_decl: IDENTIFIER '[' INTEGER ']'  */
#line 161 "mini.y"
{
    (yyval.decl).name = (yyvsp[-3].string);
    (yyval.decl).is_ptr = 0;
    (yyval.decl).is_array = 1;
    (yyval.decl).array_size = atoi((yyvsp[-1].string));
}
#line 1579 "mini.tab.c"
    break;

  case 22: /* function: function_head '(' parameter_list ')' block  */
#line 170 "mini.y"
{
	(yyval.tac)=do_func((yyvsp[-4].sym), (yyvsp[-2].tac), (yyvsp[0].tac));
	scope=0; /* Leave local scope. */
	sym_tab_local=NULL; /* Clear local symbol table. */
}
#line 1589 "mini.tab.c"
    break;

  case 23: /* function: error  */
#line 176 "mini.y"
{
	error("Bad function syntax");
	(yyval.tac)=NULL;
}
#line 1598 "mini.tab.c"
    break;

  case 24: /* function_head: IDENTIFIER  */
#line 183 "mini.y"
{
	(yyval.sym)=declare_func((yyvsp[0].string));
	scope=1; /* Enter local scope. */
	sym_tab_local=NULL; /* Init local symbol table. */
}
#line 1608 "mini.tab.c"
    break;

  case 25: /* parameter_list: IDENTIFIER  */
#line 191 "mini.y"
{
	(yyval.tac)=declare_para((yyvsp[0].string));
}
#line 1616 "mini.tab.c"
    break;

  case 26: /* parameter_list: parameter_list ',' IDENTIFIER  */
#line 195 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-2].tac), declare_para((yyvsp[0].string)));
}
#line 1624 "mini.tab.c"
    break;

  case 27: /* parameter_list: %empty  */
#line 199 "mini.y"
{
	(yyval.tac)=NULL;
}
#line 1632 "mini.tab.c"
    break;

  case 38: /* statement: BREAK ';'  */
#line 215 "mini.y"
{
    (yyval.tac) = do_break();
}
#line 1640 "mini.tab.c"
    break;

  case 39: /* statement: error  */
#line 219 "mini.y"
{
	error("Bad statement syntax");
	(yyval.tac)=NULL;
}
#line 1649 "mini.tab.c"
    break;

  case 40: /* block: '{' declaration_list statement_list '}'  */
#line 226 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-2].tac), (yyvsp[-1].tac));
}
#line 1657 "mini.tab.c"
    break;

  case 41: /* declaration_list: %empty  */
#line 232 "mini.y"
{
	(yyval.tac)=NULL;
}
#line 1665 "mini.tab.c"
    break;

  case 42: /* declaration_list: declaration_list declaration  */
#line 236 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1673 "mini.tab.c"
    break;

  case 44: /* statement_list: statement_list statement  */
#line 243 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1681 "mini.tab.c"
    break;

  case 45: /* assignment_statement: IDENTIFIER '=' expression  */
#line 250 "mini.y"
    {
        (yyval.tac) = do_assign(get_var((yyvsp[-2].string)), (yyvsp[0].exp));
    }
#line 1689 "mini.tab.c"
    break;

  case 46: /* assignment_statement: '*' expression '=' expression  */
#line 254 "mini.y"
    {
        // 生成：STO (Rptr), Rvalue
        if (!(yyvsp[-2].exp)->ret->is_ptr) error("assign to non-pointer");
        TAC *code = mk_tac(TAC_STORE, (yyvsp[-2].exp)->ret, (yyvsp[0].exp)->ret, NULL);
        code->prev = join_tac((yyvsp[-2].exp)->tac, (yyvsp[0].exp)->tac);
        (yyval.tac) = code;
    }
#line 1701 "mini.tab.c"
    break;

  case 47: /* assignment_statement: IDENTIFIER '[' expression ']' '=' expression  */
#line 262 "mini.y"
{
    SYM *arr = get_var((yyvsp[-5].string));
    if (!arr || !arr->is_array) {
        error("'%s' is not an array", (yyvsp[-5].string));
    }
    // 计算 &array[i] → ptr
    SYM *addr_tmp = mk_tmp();
    addr_tmp->is_ptr = 1;
    addr_tmp->data_type = arr->data_type;
    TAC *addr_tac = mk_tac(TAC_ADDR, addr_tmp, arr, NULL);

    SYM *scaled = mk_tmp();
    TAC *scale_tac = mk_tac(TAC_MUL, scaled, (yyvsp[-3].exp)->ret, mk_const(4));
    scale_tac->prev = (yyvsp[-3].exp)->tac;

    SYM *ptr = mk_tmp();
    ptr->is_ptr = 1;
    ptr->data_type = arr->data_type;
    TAC *add_tac = mk_tac(TAC_ADD, ptr, addr_tmp, scaled);
    add_tac->prev = join_tac(addr_tac, scale_tac);

    // 执行 *ptr = expr
    if (!(yyvsp[0].exp)->ret) error("invalid RHS");
    TAC *store_tac = mk_tac(TAC_STORE, ptr, (yyvsp[0].exp)->ret, NULL);
    store_tac->prev = join_tac(add_tac, (yyvsp[0].exp)->tac);
    (yyval.tac) = store_tac;
}
#line 1733 "mini.tab.c"
    break;

  case 48: /* assignment_statement: expression '.' IDENTIFIER '=' expression  */
#line 290 "mini.y"
{
    SYM *base = (yyvsp[-4].exp)->ret;
    char *member = (yyvsp[-2].string);
    EXP *rhs = (yyvsp[0].exp);

    if (!base || !base->is_struct) {
        error("left operand of '.' is not a struct");
    }

    int offset = get_struct_member_offset(base->struct_name, member);
    if (offset == -1) {
        error("unknown struct member '%s'", member);
    }

    // 计算成员地址：&base + offset
    SYM *base_addr = mk_tmp();
    base_addr->is_ptr = 1;
    TAC *addr_tac = mk_tac(TAC_ADDR, base_addr, base, NULL);

    SYM *off_sym = mk_const(offset);
    SYM *member_addr = mk_tmp();
    member_addr->is_ptr = 1;
    TAC *add_tac = mk_tac(TAC_ADD, member_addr, base_addr, off_sym);
    add_tac->prev = addr_tac;

    // 执行 *member_addr = rhs
    TAC *store_tac = mk_tac(TAC_STORE, member_addr, rhs->ret, NULL);
    store_tac->prev = join_tac(add_tac, rhs->tac);

    (yyval.tac) = store_tac;
}
#line 1769 "mini.tab.c"
    break;

  case 49: /* expression: expression '+' expression  */
#line 324 "mini.y"
{
	(yyval.exp)=do_bin(TAC_ADD, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1777 "mini.tab.c"
    break;

  case 50: /* expression: expression '-' expression  */
#line 328 "mini.y"
{
	(yyval.exp)=do_bin(TAC_SUB, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1785 "mini.tab.c"
    break;

  case 51: /* expression: expression '*' expression  */
#line 332 "mini.y"
{
	(yyval.exp)=do_bin(TAC_MUL, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1793 "mini.tab.c"
    break;

  case 52: /* expression: expression '/' expression  */
#line 336 "mini.y"
{
	(yyval.exp)=do_bin(TAC_DIV, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1801 "mini.tab.c"
    break;

  case 53: /* expression: '-' expression  */
#line 340 "mini.y"
{
	(yyval.exp)=do_un(TAC_NEG, (yyvsp[0].exp));
}
#line 1809 "mini.tab.c"
    break;

  case 54: /* expression: expression EQ expression  */
#line 344 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_EQ, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1817 "mini.tab.c"
    break;

  case 55: /* expression: expression NE expression  */
#line 348 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_NE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1825 "mini.tab.c"
    break;

  case 56: /* expression: expression LT expression  */
#line 352 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_LT, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1833 "mini.tab.c"
    break;

  case 57: /* expression: expression LE expression  */
#line 356 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_LE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1841 "mini.tab.c"
    break;

  case 58: /* expression: expression GT expression  */
#line 360 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_GT, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1849 "mini.tab.c"
    break;

  case 59: /* expression: expression GE expression  */
#line 364 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_GE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1857 "mini.tab.c"
    break;

  case 60: /* expression: '(' expression ')'  */
#line 368 "mini.y"
{
	(yyval.exp)=(yyvsp[-1].exp);
}
#line 1865 "mini.tab.c"
    break;

  case 61: /* expression: INTEGER  */
#line 372 "mini.y"
{
	(yyval.exp)=mk_exp(NULL, mk_const(atoi((yyvsp[0].string))), NULL);
}
#line 1873 "mini.tab.c"
    break;

  case 62: /* expression: IDENTIFIER  */
#line 376 "mini.y"
{
	(yyval.exp)=mk_exp(NULL, get_var((yyvsp[0].string)), NULL);
}
#line 1881 "mini.tab.c"
    break;

  case 63: /* expression: IDENTIFIER '[' expression ']'  */
#line 380 "mini.y"
{
    SYM *arr = get_var((yyvsp[-3].string));
    if (!arr || !arr->is_array) {
        error("'%s' is not an array", (yyvsp[-3].string));
    }
    // array[i] → *(array + i)
    // 先取 array 的地址（即 array 的 offset 或 label）
    SYM *addr_tmp = mk_tmp();
    addr_tmp->is_ptr = 1;
    addr_tmp->data_type = arr->data_type;

    TAC *addr_tac = mk_tac(TAC_ADDR, addr_tmp, arr, NULL);

    // 计算 addr + i * 4（假设每个元素 4 字节）
    SYM *scaled = mk_tmp();
    TAC *scale_tac = mk_tac(TAC_MUL, scaled, (yyvsp[-1].exp)->ret, mk_const(4));
    scale_tac->prev = (yyvsp[-1].exp)->tac;

    SYM *ptr = mk_tmp();
    ptr->is_ptr = 1;
    ptr->data_type = arr->data_type;
    TAC *add_tac = mk_tac(TAC_ADD, ptr, addr_tmp, scaled);
    add_tac->prev = join_tac(addr_tac, scale_tac);

    // 解引用：*ptr
    SYM *val = mk_tmp();
    val->is_ptr = 0;
    val->data_type = arr->data_type;
    TAC *deref_tac = mk_tac(TAC_DEREF, val, ptr, NULL);
    deref_tac->prev = add_tac;

    (yyval.exp) = mk_exp(NULL, val, deref_tac);
}
#line 1919 "mini.tab.c"
    break;

  case 64: /* expression: expression '.' IDENTIFIER  */
#line 414 "mini.y"
{
    SYM *base = (yyvsp[-2].exp)->ret;
    char *member = (yyvsp[0].string);

    if (!base || !base->is_struct) {
        error("left operand of '.' is not a struct");
    }

    int offset = get_struct_member_offset(base->struct_name, member);
    if (offset == -1) {
        error("unknown struct member '%s'", member);
    }
    
    // 计算 &base + offset → 地址
    SYM *base_addr = mk_tmp();
    base_addr->is_ptr = 1;
    TAC *addr_tac = mk_tac(TAC_ADDR, base_addr, base, NULL);

    SYM *off_sym = mk_const(offset);
    SYM *member_addr = mk_tmp();
    member_addr->is_ptr = 1;
    TAC *add_tac = mk_tac(TAC_ADD, member_addr, base_addr, off_sym);
    add_tac->prev = addr_tac;

    // 解引用得到值
    SYM *val = mk_tmp();
    val->is_ptr = 0;
// 查找成员类型
int member_type = get_struct_member_type(base->struct_name, member);
val->data_type = member_type;  // ← 关键！
    TAC *deref_tac = mk_tac(TAC_DEREF, val, member_addr, NULL);
    deref_tac->prev = add_tac;

    (yyval.exp) = mk_exp(NULL, val, deref_tac);
}
#line 1959 "mini.tab.c"
    break;

  case 65: /* expression: CHARACTER  */
#line 450 "mini.y"
{
    (yyval.exp) = mk_exp(NULL, mk_char_const((yyvsp[0].string)[0]), NULL);
}
#line 1967 "mini.tab.c"
    break;

  case 66: /* expression: call_expression  */
#line 454 "mini.y"
{
	(yyval.exp)=(yyvsp[0].exp);
}
#line 1975 "mini.tab.c"
    break;

  case 67: /* expression: '&' IDENTIFIER  */
#line 458 "mini.y"
{
    SYM *var = get_var((yyvsp[0].string));
    if (!var) { error("undefined variable"); }
    // 创建一个临时变量，保存地址（即 var 的 offset 或 label）
    SYM *tmp = mk_tmp();
    tmp->data_type = var->data_type; // 指向的类型
    tmp->is_ptr = 1;
    // TAC 中用特殊操作表示“取地址”
    TAC *code = mk_tac(TAC_ADDR, tmp, var, NULL);
    (yyval.exp) = mk_exp(NULL, tmp, code);
}
#line 1991 "mini.tab.c"
    break;

  case 68: /* expression: '*' expression  */
#line 470 "mini.y"
    {
        // $2 必须是指针类型
        if (!(yyvsp[0].exp)->ret->is_ptr) {
            error("dereference of non-pointer");
        }
        SYM *tmp = mk_tmp();
        tmp->data_type = (yyvsp[0].exp)->ret->data_type; // 指向的类型
        tmp->is_ptr = 0;
        TAC *code = mk_tac(TAC_DEREF, tmp, (yyvsp[0].exp)->ret, NULL);
        code->prev = (yyvsp[0].exp)->tac;
        (yyval.exp) = mk_exp(NULL, tmp, code);
    }
#line 2008 "mini.tab.c"
    break;

  case 69: /* expression: error  */
#line 483 "mini.y"
{
	error("Bad expression syntax");
	(yyval.exp)=mk_exp(NULL, NULL, NULL);
}
#line 2017 "mini.tab.c"
    break;

  case 70: /* argument_list: %empty  */
#line 490 "mini.y"
{
	(yyval.exp)=NULL;
}
#line 2025 "mini.tab.c"
    break;

  case 73: /* expression_list: expression_list ',' expression  */
#line 498 "mini.y"
{
	(yyvsp[0].exp)->next=(yyvsp[-2].exp);
	(yyval.exp)=(yyvsp[0].exp);
}
#line 2034 "mini.tab.c"
    break;

  case 74: /* input_statement: INPUT IDENTIFIER  */
#line 505 "mini.y"
{
	(yyval.tac)=do_input(get_var((yyvsp[0].string)));
}
#line 2042 "mini.tab.c"
    break;

  case 75: /* output_statement: OUTPUT expression  */
#line 511 "mini.y"
{
	// $2 是 EXP* 类型，包含表达式的计算代码 ($2->tac) 和结果符号 ($2->ret)
	// 创建 TAC_OUTPUT 指令
	TAC *output_tac = mk_tac(TAC_OUTPUT, (yyvsp[0].exp)->ret, NULL, NULL);
	// 将输出指令的前置链连接到表达式的代码链上
	output_tac->prev = (yyvsp[0].exp)->tac;
	// 整个 output_statement 的 TAC 链就是这个 output 指令
	(yyval.tac) = output_tac;
}
#line 2056 "mini.tab.c"
    break;

  case 76: /* output_statement: OUTPUT TEXT  */
#line 521 "mini.y"
{
	(yyval.tac)=do_output(mk_text((yyvsp[0].string)));
}
#line 2064 "mini.tab.c"
    break;

  case 77: /* return_statement: RETURN expression  */
#line 527 "mini.y"
{
	TAC *t=mk_tac(TAC_RETURN, (yyvsp[0].exp)->ret, NULL, NULL);
	t->prev=(yyvsp[0].exp)->tac;
	(yyval.tac)=t;
}
#line 2074 "mini.tab.c"
    break;

  case 78: /* if_statement: IF '(' expression ')' block  */
#line 535 "mini.y"
{
	(yyval.tac)=do_if((yyvsp[-2].exp), (yyvsp[0].tac));
}
#line 2082 "mini.tab.c"
    break;

  case 79: /* if_statement: IF '(' expression ')' block ELSE block  */
#line 539 "mini.y"
{
	(yyval.tac)=do_test((yyvsp[-4].exp), (yyvsp[-2].tac), (yyvsp[0].tac));
}
#line 2090 "mini.tab.c"
    break;

  case 80: /* loop_start: %empty  */
#line 545 "mini.y"
{
    (yyval.sym) = mk_label(mk_lstr(next_label++));
    push_break_label((yyval.sym));
}
#line 2099 "mini.tab.c"
    break;

  case 81: /* loop_end: %empty  */
#line 552 "mini.y"
{
    pop_break_label();
    (yyval.tac) = NULL;
}
#line 2108 "mini.tab.c"
    break;

  case 82: /* for_start: %empty  */
#line 559 "mini.y"
{
    (yyval.sym) = mk_label(mk_lstr(next_label++));
    push_break_label((yyval.sym));
}
#line 2117 "mini.tab.c"
    break;

  case 83: /* for_end: %empty  */
#line 566 "mini.y"
{
    pop_break_label();
    (yyval.tac) = NULL;
}
#line 2126 "mini.tab.c"
    break;

  case 84: /* switch_start: %empty  */
#line 573 "mini.y"
{
    (yyval.sym) = mk_label(mk_lstr(next_label++));
    push_break_label((yyval.sym));
}
#line 2135 "mini.tab.c"
    break;

  case 85: /* switch_end: %empty  */
#line 580 "mini.y"
{
    pop_break_label();
    (yyval.tac) = NULL;
}
#line 2144 "mini.tab.c"
    break;

  case 86: /* call_statement: IDENTIFIER '(' argument_list ')'  */
#line 587 "mini.y"
{
	(yyval.tac)=do_call((yyvsp[-3].string), (yyvsp[-1].exp));
}
#line 2152 "mini.tab.c"
    break;

  case 87: /* call_expression: IDENTIFIER '(' argument_list ')'  */
#line 593 "mini.y"
{
	(yyval.exp)=do_call_ret((yyvsp[-3].string), (yyvsp[-1].exp));
}
#line 2160 "mini.tab.c"
    break;

  case 88: /* while_statement: WHILE '(' expression ')' loop_start block loop_end  */
#line 599 "mini.y"
{
    (yyval.tac) = do_while_with_context((yyvsp[-4].exp), (yyvsp[-1].tac), (yyvsp[-2].sym), (yyvsp[0].tac));
}
#line 2168 "mini.tab.c"
    break;

  case 89: /* for_statement: FOR '(' assignment_statement ';' expression ';' assignment_statement ')' for_start block for_end  */
#line 605 "mini.y"
{
    (yyval.tac) = do_for_with_context((yyvsp[-8].tac), (yyvsp[-6].exp), (yyvsp[-4].tac), (yyvsp[-1].tac), (yyvsp[-2].sym), (yyvsp[0].tac));
}
#line 2176 "mini.tab.c"
    break;

  case 90: /* switch_statement: SWITCH '(' expression ')' '{' switch_start case_list default_clause switch_end '}'  */
#line 611 "mini.y"
{
    (yyval.tac) = do_switch_with_context((yyvsp[-7].exp), (yyvsp[-3].tac), (yyvsp[-2].tac), (yyvsp[-4].sym), (yyvsp[-1].tac));
}
#line 2184 "mini.tab.c"
    break;

  case 91: /* case_list: %empty  */
#line 617 "mini.y"
                                { (yyval.tac) = NULL; }
#line 2190 "mini.tab.c"
    break;

  case 92: /* case_list: case_list case_clause  */
#line 618 "mini.y"
                                { (yyval.tac) = join_tac((yyvsp[-1].tac), (yyvsp[0].tac)); }
#line 2196 "mini.tab.c"
    break;

  case 93: /* case_clause: CASE INTEGER ':' statement_list  */
#line 623 "mini.y"
    {
        (yyval.tac) = do_case(atoi((yyvsp[-2].string)), (yyvsp[0].tac));
    }
#line 2204 "mini.tab.c"
    break;

  case 94: /* default_clause: %empty  */
#line 629 "mini.y"
                                { (yyval.tac) = NULL; }
#line 2210 "mini.tab.c"
    break;

  case 95: /* default_clause: DEFAULT ':' statement_list  */
#line 631 "mini.y"
    {
        (yyval.tac) = do_default((yyvsp[0].tac));
    }
#line 2218 "mini.tab.c"
    break;


#line 2222 "mini.tab.c"

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

#line 636 "mini.y"


void yyerror(char* msg) 
{
	fprintf(stderr, "%s: line %d\n", msg, yylineno);
	exit(0);
}
