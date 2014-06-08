/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "syntax.y"

#include "stdio.h"
#include "syntax_tree.h"
#include "lex.yy.c"
#include "sys/ioctl.h"
#include "stdlib.h"
#include "stdarg.h"
#include "semantic.h"
#include "hash_table.h"
#include "assert.h"
#include "IR.h"
#include "mips.h"
//global table
InterCodes irtable = NULL;


/* Line 268 of yacc.c  */
#line 88 "syntax.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     ID = 260,
     SEMI = 261,
     COMMA = 262,
     ASSIGNOP = 263,
     RELOP = 264,
     PLUS = 265,
     MINUS = 266,
     STAR = 267,
     DIV = 268,
     AND = 269,
     OR = 270,
     NOT = 271,
     DOT = 272,
     TYPE = 273,
     LP = 274,
     RP = 275,
     LB = 276,
     RB = 277,
     LC = 278,
     RC = 279,
     STRUCT = 280,
     RETURN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     UNARY_MINUS = 285,
     LOWER_THAN_ELSE = 286,
     LOWER_THAN_error = 287
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 18 "syntax.y"

	int int_value;
	float float_value;
	char *str_value;
	NodePtr node_value;



/* Line 293 of yacc.c  */
#line 165 "syntax.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 190 "syntax.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   277

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNRULES -- Number of states.  */
#define YYNSTATES  126

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    13,    16,    20,    24,
      27,    29,    33,    35,    37,    43,    46,    48,    49,    51,
      53,    58,    63,    67,    70,    74,    76,    79,    84,    87,
      90,    91,    94,    96,   100,   106,   114,   120,   123,   126,
     127,   131,   135,   137,   141,   143,   147,   151,   155,   159,
     163,   167,   171,   175,   179,   183,   186,   189,   194,   198,
     203,   207,   209,   211,   213,   217,   222,   226
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      34,     0,    -1,    35,    -1,    36,    35,    -1,    -1,    38,
      37,     6,    -1,    38,     6,    -1,    38,    43,    46,    -1,
      38,    43,     6,    -1,     1,     6,    -1,    42,    -1,    42,
       7,    37,    -1,    18,    -1,    39,    -1,    25,    40,    23,
      49,    24,    -1,    25,    41,    -1,     5,    -1,    -1,     5,
      -1,     5,    -1,    42,    21,     3,    22,    -1,     5,    19,
      44,    20,    -1,     5,    19,    20,    -1,     1,    20,    -1,
      45,     7,    44,    -1,    45,    -1,    38,    42,    -1,    23,
      49,    47,    24,    -1,     1,    24,    -1,    48,    47,    -1,
      -1,    53,     6,    -1,    46,    -1,    26,    53,     6,    -1,
      27,    19,    53,    20,    48,    -1,    27,    19,    53,    20,
      48,    28,    48,    -1,    29,    19,    53,    20,    48,    -1,
       1,     6,    -1,    50,    49,    -1,    -1,    38,    51,     6,
      -1,    38,     1,     6,    -1,    52,    -1,    52,     7,    51,
      -1,    42,    -1,    42,     8,    53,    -1,    53,     8,    53,
      -1,    53,    14,    53,    -1,    53,    15,    53,    -1,    53,
       9,    53,    -1,    53,    10,    53,    -1,    53,    11,    53,
      -1,    53,    12,    53,    -1,    53,    13,    53,    -1,    19,
      53,    20,    -1,    11,    53,    -1,    16,    53,    -1,     5,
      19,    54,    20,    -1,     5,    19,    20,    -1,    53,    21,
      53,    22,    -1,    53,    17,     5,    -1,     5,    -1,     3,
      -1,     4,    -1,    19,     1,    20,    -1,    53,    21,     1,
      22,    -1,    53,     7,    54,    -1,    53,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    62,    62,    69,    74,    80,    85,    90,    95,   100,
     102,   107,   115,   120,   126,   131,   137,   142,   148,   156,
     161,   167,   172,   177,   179,   184,   190,   198,   203,   205,
     210,   216,   221,   226,   231,   236,   241,   246,   253,   258,
     264,   269,   271,   276,   282,   287,   295,   300,   305,   310,
     315,   320,   325,   330,   335,   340,   345,   350,   355,   360,
     365,   370,   375,   380,   385,   386,   388,   393
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "NOT",
  "DOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "UNARY_MINUS", "LOWER_THAN_ELSE",
  "LOWER_THAN_error", "$accept", "Program", "ExtDefList", "ExtDef",
  "ExtDecList", "Specifier", "StructSpecifier", "OptTag", "Tag", "VarDec",
  "FunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt", "DefList",
  "Def", "DecList", "Dec", "Exp", "Args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    36,    36,
      37,    37,    38,    38,    39,    39,    40,    40,    41,    42,
      42,    43,    43,    43,    44,    44,    45,    46,    46,    47,
      47,    48,    48,    48,    48,    48,    48,    48,    49,    49,
      50,    50,    51,    51,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    54,    54
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     2,
       1,     3,     1,     1,     5,     2,     1,     0,     1,     1,
       4,     4,     3,     2,     3,     1,     2,     4,     2,     2,
       0,     2,     1,     3,     5,     7,     5,     2,     2,     0,
       3,     3,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     4,     3,     4,
       3,     1,     1,     1,     3,     4,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    12,    17,     0,     2,     0,     0,    13,     9,
      18,     0,    15,     1,     3,     0,    19,     6,     0,    10,
       0,    39,    23,     0,     5,     0,     0,     0,     8,    39,
       7,     0,     0,    39,    22,     0,     0,    25,    19,    11,
       0,    28,     0,     0,    44,     0,    42,    14,    38,    26,
      21,     0,    20,     0,    62,    63,    61,     0,     0,     0,
       0,     0,     0,    32,     0,     0,     0,    41,     0,    40,
       0,    24,    37,     0,    55,    56,     0,     0,     0,     0,
       0,    27,    29,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,    43,    58,    67,     0,    64,
      54,    33,     0,     0,    46,    49,    50,    51,    52,    53,
      47,    48,    60,     0,     0,     0,    57,     0,     0,    65,
      59,    66,    34,    36,     0,    35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    18,    31,     8,    11,    12,    19,
      20,    36,    37,    63,    64,    65,    32,    33,    45,    46,
      66,    98
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -78
static const yytype_int16 yypact[] =
{
      71,    32,   -78,    34,    48,   -78,    71,    80,   -78,   -78,
      26,    27,   -78,   -78,   -78,    36,    40,   -78,    56,    -2,
      14,    -8,   -78,   -11,   -78,    70,    85,    68,   -78,    -8,
     -78,    20,    69,    -8,   -78,    70,    74,    95,   -78,   -78,
      84,   -78,    41,   102,     5,   107,   110,   -78,   -78,   109,
     -78,    -8,   -78,     0,   -78,   -78,   113,   118,   118,    79,
     118,   127,   129,   -78,   104,    41,   130,   -78,   118,   -78,
      70,   -78,   -78,   100,    57,    57,   140,   188,   144,   118,
     118,   -78,   -78,   -78,   118,   118,   118,   118,   118,   118,
     118,   118,   128,    96,   230,   -78,   -78,   159,   142,   -78,
     -78,   -78,   202,   216,   230,   114,    97,    97,    57,    57,
     256,   243,   -78,   141,   173,   118,   -78,    50,    50,   -78,
     -78,   -78,   121,   -78,    50,   -78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -78,   -78,   158,   -78,   150,    12,   -78,   -78,   -78,   -27,
     -78,   126,   -78,   169,   139,   -77,    58,   -78,   108,   -78,
     -57,    64
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -31
static const yytype_int8 yytable[] =
{
      74,    75,    77,    78,    44,    25,    72,     2,    49,    34,
       2,    94,     7,    68,     3,    27,    97,     3,     7,    26,
      28,    43,   102,   103,    41,    38,    26,   104,   105,   106,
     107,   108,   109,   110,   111,    35,   114,    29,     9,    10,
     122,   123,    53,    44,    54,    55,    56,   125,    13,   -16,
      21,    53,    57,    54,    55,    56,    22,    58,    97,    23,
      59,    57,    24,    35,    29,   -30,    58,    60,    61,    59,
      62,    -4,     1,    29,    92,    38,    60,    61,    93,    62,
      76,    15,    54,    55,    56,    16,    17,    42,    40,     2,
      57,    48,    41,    47,    50,    58,     3,   113,    59,    54,
      55,    56,    51,    54,    55,    56,    52,    57,    67,    88,
      89,    57,    58,    69,    92,    59,    58,    70,    93,    59,
      96,    54,    55,    56,    86,    87,    88,    89,    81,    57,
      26,    92,    73,   112,    58,    93,    83,    59,    84,    85,
      86,    87,    88,    89,    90,    91,    79,    92,    80,   124,
     101,    93,    84,    85,    86,    87,    88,    89,    90,    91,
      99,    92,   116,   119,    14,    93,   115,    84,    85,    86,
      87,    88,    89,    90,    91,    39,    92,    71,    95,   121,
      93,    84,    85,    86,    87,    88,    89,    90,    91,    30,
      92,     0,     0,     0,    93,   120,    84,    85,    86,    87,
      88,    89,    90,    91,    82,    92,     0,     0,   100,    93,
      84,    85,    86,    87,    88,    89,    90,    91,     0,    92,
       0,     0,   117,    93,    84,    85,    86,    87,    88,    89,
      90,    91,     0,    92,     0,     0,   118,    93,    84,    85,
      86,    87,    88,    89,    90,    91,     0,    92,     0,     0,
       0,    93,    85,    86,    87,    88,    89,    90,     0,     0,
      92,     0,     0,     0,    93,    85,    86,    87,    88,    89,
       0,     0,     0,    92,     0,     0,     0,    93
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-78))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      57,    58,    59,    60,    31,     7,     6,    18,    35,    20,
      18,    68,     0,     8,    25,     1,    73,    25,     6,    21,
       6,     1,    79,    80,    24,     5,    21,    84,    85,    86,
      87,    88,    89,    90,    91,    23,    93,    23,     6,     5,
     117,   118,     1,    70,     3,     4,     5,   124,     0,    23,
      23,     1,    11,     3,     4,     5,    20,    16,   115,    19,
      19,    11,     6,    51,    23,    24,    16,    26,    27,    19,
      29,     0,     1,    23,    17,     5,    26,    27,    21,    29,
       1,     1,     3,     4,     5,     5,     6,    29,     3,    18,
      11,    33,    24,    24,    20,    16,    25,     1,    19,     3,
       4,     5,     7,     3,     4,     5,    22,    11,     6,    12,
      13,    11,    16,     6,    17,    19,    16,     7,    21,    19,
      20,     3,     4,     5,    10,    11,    12,    13,    24,    11,
      21,    17,    19,     5,    16,    21,     6,    19,     8,     9,
      10,    11,    12,    13,    14,    15,    19,    17,    19,    28,
       6,    21,     8,     9,    10,    11,    12,    13,    14,    15,
      20,    17,    20,    22,     6,    21,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    25,    17,    51,    70,   115,
      21,     8,     9,    10,    11,    12,    13,    14,    15,    20,
      17,    -1,    -1,    -1,    21,    22,     8,     9,    10,    11,
      12,    13,    14,    15,    65,    17,    -1,    -1,    20,    21,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    17,
      -1,    -1,    20,    21,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    17,    -1,    -1,    20,    21,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    17,    -1,    -1,
      -1,    21,     9,    10,    11,    12,    13,    14,    -1,    -1,
      17,    -1,    -1,    -1,    21,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    18,    25,    34,    35,    36,    38,    39,     6,
       5,    40,    41,     0,    35,     1,     5,     6,    37,    42,
      43,    23,    20,    19,     6,     7,    21,     1,     6,    23,
      46,    38,    49,    50,    20,    38,    44,    45,     5,    37,
       3,    24,    49,     1,    42,    51,    52,    24,    49,    42,
      20,     7,    22,     1,     3,     4,     5,    11,    16,    19,
      26,    27,    29,    46,    47,    48,    53,     6,     8,     6,
       7,    44,     6,    19,    53,    53,     1,    53,    53,    19,
      19,    24,    47,     6,     8,     9,    10,    11,    12,    13,
      14,    15,    17,    21,    53,    51,    20,    53,    54,    20,
      20,     6,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,     5,     1,    53,     7,    20,    20,    20,    22,
      22,    54,    48,    48,    28,    48
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 62 "syntax.y"
    {
				//printf("Program -> ExtDefList\n");
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "Program", (yyloc).first_line);
				root = (yyval.node_value);
			}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 69 "syntax.y"
    {
				//printf("ExtDefList -> ExtDef ExtDefList\n");
				(yyval.node_value) = create_tree(2, (yyvsp[(1) - (2)].node_value), (yyvsp[(2) - (2)].node_value));
				set_content(&(yyval.node_value), "ExtDefList", (yyloc).first_line);
			}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 74 "syntax.y"
    {
				//printf("ExtDefList -> NULL\n");
				(yyval.node_value) = create_tree(1, NULL);
				set_content(&(yyval.node_value), "null", (yyloc).first_line);	
			}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 80 "syntax.y"
    {
				//printf("ExtDef -> Specifier ExtDecList SEMI\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "ExtDef", (yyloc).first_line);
			}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 85 "syntax.y"
    {
				//printf("ExtDef -> Specifier SEMI\n");
				(yyval.node_value) = create_tree(2, (yyvsp[(1) - (2)].node_value), (yyvsp[(2) - (2)].node_value));
				set_content(&(yyval.node_value), "ExtDef", (yyloc).first_line);
			}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 90 "syntax.y"
    {
				//printf("ExtDef -> Specifier FunDec CompSt\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "ExtDef", (yyloc).first_line);
			}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 95 "syntax.y"
    {
				//printf("ExtDef -> Specifier FunDec CompSt\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "ExtDef", (yyloc).first_line);
			}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 100 "syntax.y"
    {}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 102 "syntax.y"
    {
				//printf("ExtDecList -> VarDec\n");
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "ExtDecList", (yyloc).first_line);
			}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 107 "syntax.y"
    {
				//printf("ExtDecList -> VarDec COMMA ExtDecList\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "ExtDecList", (yyloc).first_line);
			}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 115 "syntax.y"
    {
				//printf("Specifier -> TYPE(%s)\n", $1->content.str_value);
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "Specifier", (yyloc).first_line);
			}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 120 "syntax.y"
    {
				//printf("Specifier -> StructSpecifier\n");
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "Specifier", (yyloc).first_line);
			}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 126 "syntax.y"
    {
				//printf("StructSpecifier -> STRUCT OptTag LC DefList RC\n"); 
				(yyval.node_value) = create_tree(5, (yyvsp[(1) - (5)].node_value), (yyvsp[(2) - (5)].node_value), (yyvsp[(3) - (5)].node_value), (yyvsp[(4) - (5)].node_value), (yyvsp[(5) - (5)].node_value));
				set_content(&(yyval.node_value), "StructSpecifier", (yyloc).first_line);
			}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 131 "syntax.y"
    {
				//printf("StructSpecifier -> STRUCT Tag\n");
				(yyval.node_value) = create_tree(2, (yyvsp[(1) - (2)].node_value), (yyvsp[(2) - (2)].node_value));
				set_content(&(yyval.node_value), "StructSpecifier", (yyloc).first_line);
			}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 137 "syntax.y"
    {
				//printf("OptTag -> ID(%s)\n", $1->content.str_value);
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "OptTag", (yyloc).first_line);
			}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 142 "syntax.y"
    {
				//printf("OptTag -> NULL\n");
				(yyval.node_value) = create_tree(1, NULL);
				set_content(&(yyval.node_value), "null", (yyloc).first_line);
			}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 148 "syntax.y"
    {
				//printf("Tag -> ID(%s)\n", $1->content.str_value);
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "Tag", (yyloc).first_line);
			}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 156 "syntax.y"
    {
				//printf("VarDec -> ID(%s)\n", $1->content.str_value);
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "VarDec", (yyloc).first_line);
			}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 161 "syntax.y"
    {
				//printf("VarDec -> VarDec LB INT RB\n");
				(yyval.node_value) = create_tree(4, (yyvsp[(1) - (4)].node_value), (yyvsp[(2) - (4)].node_value), (yyvsp[(3) - (4)].node_value), (yyvsp[(4) - (4)].node_value));
				set_content(&(yyval.node_value), "VarDec", (yyloc).first_line);
			}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 167 "syntax.y"
    {
				//printf("FunDec -> ID LP VarList RP\n");
				(yyval.node_value) = create_tree(4, (yyvsp[(1) - (4)].node_value), (yyvsp[(2) - (4)].node_value), (yyvsp[(3) - (4)].node_value), (yyvsp[(4) - (4)].node_value));
				set_content(&(yyval.node_value), "FunDec", (yyloc).first_line);
			}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 172 "syntax.y"
    {
				//printf("FunDec -> ID LP RP\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "FunDec", (yyloc).first_line);
			}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 177 "syntax.y"
    {}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 179 "syntax.y"
    {
				//printf("VarList -> ParamDec COMMA VarList\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "VarList", (yyloc).first_line);
			}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 184 "syntax.y"
    {
				//printf("VarList -> ParamDec\n");
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "VarList", (yyloc).first_line);
			}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 190 "syntax.y"
    {
				//printf("ParamDec -> Specifier VarDec\n");
				(yyval.node_value) = create_tree(2, (yyvsp[(1) - (2)].node_value), (yyvsp[(2) - (2)].node_value));
				set_content(&(yyval.node_value), "ParamDec", (yyloc).first_line);
			}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 198 "syntax.y"
    {
				//printf("CompSt -> LC DefList StmtList RC\n");
				(yyval.node_value) = create_tree(4, (yyvsp[(1) - (4)].node_value), (yyvsp[(2) - (4)].node_value), (yyvsp[(3) - (4)].node_value), (yyvsp[(4) - (4)].node_value));
				set_content(&(yyval.node_value), "CompSt", (yyloc).first_line);
			}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 203 "syntax.y"
    {}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 205 "syntax.y"
    {
				//printf("StmtList -> Stmt StmtList\n");
				(yyval.node_value) = create_tree(2, (yyvsp[(1) - (2)].node_value), (yyvsp[(2) - (2)].node_value));
				set_content(&(yyval.node_value), "StmtList", (yyloc).first_line);
			}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 210 "syntax.y"
    {
				//printf("StmtList -> NULL\n");
				(yyval.node_value) = create_tree(1, NULL);
				set_content(&(yyval.node_value), "null", (yyloc).first_line);
			}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 216 "syntax.y"
    {
				//printf("Stmt -> Exp SEMI\n");
				(yyval.node_value) = create_tree(2, (yyvsp[(1) - (2)].node_value), (yyvsp[(2) - (2)].node_value));
				set_content(&(yyval.node_value), "Stmt", (yyloc).first_line);
			}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 221 "syntax.y"
    {
				//printf("Stmt -> CompSt\n");
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "Stmt", (yyloc).first_line);
			}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 226 "syntax.y"
    {
				//printf("Stmt -> RETURN Exp SEMI\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Stmt", (yyloc).first_line);
			}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 231 "syntax.y"
    {
				//printf("Stmt -> IF LP Exp RP Stmt\n");
				(yyval.node_value) = create_tree(5, (yyvsp[(1) - (5)].node_value), (yyvsp[(2) - (5)].node_value), (yyvsp[(3) - (5)].node_value), (yyvsp[(4) - (5)].node_value), (yyvsp[(5) - (5)].node_value));
				set_content(&(yyval.node_value), "Stmt", (yyloc).first_line);
			}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 236 "syntax.y"
    {
				//printf("Stmt -> IF LP Exp RP Stmt ELSE Stmt\n");
				(yyval.node_value) = create_tree(7, (yyvsp[(1) - (7)].node_value), (yyvsp[(2) - (7)].node_value), (yyvsp[(3) - (7)].node_value), (yyvsp[(4) - (7)].node_value), (yyvsp[(5) - (7)].node_value), (yyvsp[(6) - (7)].node_value), (yyvsp[(7) - (7)].node_value));
				set_content(&(yyval.node_value), "Stmt", (yyloc).first_line);
			}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 241 "syntax.y"
    {
				//printf("Stmt -> WHILE LP Exp RP Stmt\n");
				(yyval.node_value) = create_tree(5, (yyvsp[(1) - (5)].node_value), (yyvsp[(2) - (5)].node_value), (yyvsp[(3) - (5)].node_value), (yyvsp[(4) - (5)].node_value), (yyvsp[(5) - (5)].node_value));
				set_content(&(yyval.node_value), "Stmt", (yyloc).first_line);
			}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 246 "syntax.y"
    {}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 253 "syntax.y"
    {
				//printf("DefList -> Def DefList\n");
				(yyval.node_value) = create_tree(2, (yyvsp[(1) - (2)].node_value), (yyvsp[(2) - (2)].node_value));
				set_content(&(yyval.node_value), "DefList", (yyloc).first_line);
			}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 258 "syntax.y"
    {
				//printf("DefList -> NULL\n");
				(yyval.node_value) = create_tree(1, NULL);
				set_content(&(yyval.node_value), "null", (yyloc).first_line);
			}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 264 "syntax.y"
    {
				//printf("Def -> Specifier DecList SEMI\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Def", (yyloc).first_line);
			}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 269 "syntax.y"
    {}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 271 "syntax.y"
    {
				//printf("DecList -> Dec\n");
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "DecList", (yyloc).first_line);
			}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 276 "syntax.y"
    {
				//printf("DecList -> Dec COMMA DecList\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "DecList", (yyloc).first_line);
			}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 282 "syntax.y"
    {
				//printf("Dec -> VarDec\n");
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "Dec", (yyloc).first_line);
			}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 287 "syntax.y"
    {
				//printf("Dec -> VarDec ASSIGNOP Exp\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Dec", (yyloc).first_line);
			}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 295 "syntax.y"
    {
				//printf("Exp -> Exp ASSIGNOP Exp\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 300 "syntax.y"
    {
				//printf("Exp -> Exp AND Exp\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 305 "syntax.y"
    {
				//printf("Exp -> Exp OR Exp\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 310 "syntax.y"
    {
				//printf("Exp -> Exp RELOP Exp\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 315 "syntax.y"
    {
				//printf("Exp -> Exp PLUS Exp\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 320 "syntax.y"
    {
				//printf("Exp -> Exp MINUS Exp\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 325 "syntax.y"
    {
				//printf("Exp -> Exp STAR Exp\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 330 "syntax.y"
    {
				//printf("Exp -> Exp DIV Exp\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 335 "syntax.y"
    {
				//printf("Exp -> LP Exp RP\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 340 "syntax.y"
    {
				//printf("Exp -> Exp MINUS Exp\n");
				(yyval.node_value) = create_tree(2, (yyvsp[(1) - (2)].node_value), (yyvsp[(2) - (2)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 345 "syntax.y"
    {
				//printf("Exp -> NOT Exp\n");
				(yyval.node_value) = create_tree(2, (yyvsp[(1) - (2)].node_value), (yyvsp[(2) - (2)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 350 "syntax.y"
    {
				//printf("Exp -> ID LP Args RP\n");
				(yyval.node_value) = create_tree(4, (yyvsp[(1) - (4)].node_value), (yyvsp[(2) - (4)].node_value), (yyvsp[(3) - (4)].node_value), (yyvsp[(4) - (4)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 355 "syntax.y"
    {
				//printf("Exp -> ID LP RP\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 360 "syntax.y"
    {
				//printf("Exp -> Exp LB Exp RB\n");
				(yyval.node_value) = create_tree(4, (yyvsp[(1) - (4)].node_value), (yyvsp[(2) - (4)].node_value), (yyvsp[(3) - (4)].node_value), (yyvsp[(4) - (4)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 365 "syntax.y"
    {
				//printf("Exp -> Exp DOT ID\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 370 "syntax.y"
    {
				//printf("Exp -> ID(%s)\n", $1->content.str_value);
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 375 "syntax.y"
    {
				//printf("Exp -> INT(%d)\n", $1->content.int_value);
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 380 "syntax.y"
    {
				//printf("Exp -> FLOAT(%f)\n", $1->content.float_value);
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "Exp", (yyloc).first_line);
			}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 385 "syntax.y"
    {}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 386 "syntax.y"
    {}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 388 "syntax.y"
    {
				//printf("Args -> Exp COMMA Args\n");
				(yyval.node_value) = create_tree(3, (yyvsp[(1) - (3)].node_value), (yyvsp[(2) - (3)].node_value), (yyvsp[(3) - (3)].node_value));
				set_content(&(yyval.node_value), "Args", (yyloc).first_line);
			}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 393 "syntax.y"
    {
				//printf("Args -> Exp\n");
				(yyval.node_value) = create_tree(1, (yyvsp[(1) - (1)].node_value));
				set_content(&(yyval.node_value), "Args", (yyloc).first_line);
			}
    break;



/* Line 1806 of yacc.c  */
#line 2296 "syntax.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 400 "syntax.y"



int gen_ir(NodePtr node , int level){
	InterCodes icode;
	//if(level == 0) printf("------------------------\n");
	if(strcmp(node->content.name, "null") == 0) return 0;
	else if(strcmp(node->content.name, "Exp") == 0){
		icode = translate_Exp(node, NULL);
		irtable = link_ir(irtable, icode);
		return 0;
	}
	else if(strcmp(node->content.name, "Stmt") == 0){
		icode = translate_Stmt(node);
		irtable = link_ir(irtable, icode);
		return 0;
	}
	else if(strcmp(node->content.name, "ExtDef") == 0){
		icode = translate_Extdef(node);
		irtable = link_ir(irtable, icode);
		return 0;
	}
	return 1;
}


int semantic(NodePtr node, int level){
	int num;
	int i;
	NodePtr child;
	TypePtr type = (TypePtr)malloc(sizeof(struct Type_));
	FieldList *list = (FieldList *)malloc(20*sizeof(FieldList));
	//struct_id = 0;

	if(level == 0) printf("------------------------\n");
	//if(node == NULL) return 0;//???
	if(strcmp(node->content.name, "null") == 0) return 0;
	else if(strcmp(node->content.name, "RETURN") == 0){
		//return_handler(node->next_sibling);
		TypePtr type = (TypePtr)malloc(sizeof(struct Type_));
		type = exp_handler(node->next_sibling);
		FieldList fun = hash_get(curr_func);	
		TypePtr returnType = fun->type->u.func.retype;
		if(type_handler(type, returnType) == 0)
			printf("Error Type 8 at line %d: The return type mismatched\n", node->content.lineno);
		//return 0;
	}
	else if(strcmp(node->content.name, "Exp") == 0 && node->first_child->flag != 1){
		type = exp_handler(node->first_child);
		if(type == NULL) 
			return 0;
	}
	else if(strcmp(node->content.name, "Def") == 0){
		num = def_handler(node, list, 0, 0);
		//if(num == 0) return 1;
		for(i=0; i<num; i++){
			if(hash_get(list[i]->name) != NULL){
				printf("Error type 3 at line %d: Redefined variable '%s'\n", node->content.lineno, list[i]->name);
			}
			else
				hash_put(list[i]);
		}
		return 1;
	}
	else if(strcmp(node->content.name, "ExtDef") == 0){
		num = extdef_handler(node, list, 0);
		if(num == 0) return 1;
		for(i=0; i<num; i++){
			if(hash_get(list[i]->name) != NULL){
				printf("Error type 3 at line %d: Redefined variable '%s'\n", node->content.lineno, list[i]->name);
			}
			else
				hash_put(list[i]);
		}
		return 1;
	}
	return 1;
}


//traverse the tree from level(defined depth)
void traverse(int (*func)(NodePtr, int), NodePtr root, int level) {
	//Node is not empty
	if ((*func)(root, level) == 1) {
		if (root->first_child != NULL)
			traverse(func, root->first_child, level+1);
    		if (root->next_sibling != NULL)
			traverse(func, root->next_sibling, level);
	}
	//Node is empty, so has no children
	else {
		if (root->next_sibling != NULL)
			traverse(func, root->next_sibling, level);
	}
}

//create subtree with variable number of arguments
NodePtr create_tree(int num, ...) {
	NodePtr parent = (NodePtr)malloc(sizeof(Node));
	parent->first_child = NULL;
	parent->next_sibling = NULL;
	parent->level = 0;
	parent->content.type = NIL_T;

	NodePtr child, sibling;
	va_list arg_ptr;
	va_start(arg_ptr, num);
	int i;
	for (i=1; i<=num; ++i) {
		child = va_arg(arg_ptr, NodePtr);//node to be inserted
		NodePtr child_tmp;
		NodePtr child_tmp_p;
		if (parent == NULL || child == NULL) return parent;
		child_tmp = parent->first_child;
		//this node does not have children
		if (child_tmp == NULL) {
			parent->first_child = child;
			continue;
		}
		//this node has children, so find a null position to insert
		while (child_tmp != NULL) {
			child_tmp_p = child_tmp;
			child_tmp = child_tmp->next_sibling;
		}
		child_tmp_p->next_sibling = child;
	}
	va_end(arg_ptr);
	return parent;
}

//set the name and lineno of a node
void set_content(NodePtr* ptr, char* name, int lineno) {
	(*ptr)->content.name = name;
	(*ptr)->content.lineno = lineno;
}

//print a node
int print_node(NodePtr node, int level) {
	int i;
	if(level == 0) printf("------------------------\n");
	if(strcmp(node->content.name, "null") == 0) return 0;
	else {
		for(i=0; i<level; ++i) printf("  ");
		printf("%s", node->content.name);
		if(node->content.type == NIL_T)
			printf(" (%d)\n", node->content.lineno);
		else if(node->content.type == STR_T)
			printf(": %s\n", node->content.str_value);
		else if(node->content.type == INT_T)
			printf(": %d\n", node->content.int_value);
		else if(node->content.type == FLOAT_T)
			printf(": %f\n", node->content.float_value);
		else printf("\n");
	}
	return 1;
}

int main(int argc, char** argv) {
	int i;
	curr_func = (char *)malloc(20);
	//int totchars=0, totwords=0, totlines=0;
	if (argc < 2) { /* just read stdin */
		yylex();
	}
	for (i=1; i<argc-1; i++) {
		FILE *f = fopen(argv[i], "r");
		if (!f) {
			perror(argv[i]);
			return 1;
		}
		//FILE *fp2 = fopen(argv[i], "w+");
		yyrestart(f);
		//yylex();
		yyparse();
		fclose(f);
	}
	fp2 = fopen(argv[2], "a+");
	if(error_num == 0) {
		//traverse(&print_node, root, 0);
		add_read_write();
		traverse(&semantic, root, 0);
		declare_handler();
		traverse(&gen_ir, root, 0);
		optimize_ir(&irtable);
		optimize_ir(&irtable);
		output_ir(irtable);
		//output_read_write();
		gen_mips(irtable);
	}
}


yyerror(char* msg){
	error_num++;
	fprintf(stderr, "Error type B at line %d: Syntax error\n", yylineno);
} 

