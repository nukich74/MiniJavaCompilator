/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "parser.y"

#include <iostream>
#include <common.h>
#include <PrettyPrinterVisitor.h>
#include <SymbolTableConstructor.h>

extern "C" int yylex();
extern "C" int yyparse();
void yyerror(const char *);

/* Line 371 of yacc.c  */
#line 79 "parser.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.hpp".  */
#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     UMINUS = 258,
     CLASS = 259,
     PUBLIC = 260,
     STATIC = 261,
     VOID = 262,
     MAIN = 263,
     EXTENDS = 264,
     RETURN = 265,
     ELSE = 266,
     IF = 267,
     WHILE = 268,
     SYSTEM_OUT_PRINTLN = 269,
     LENGTH = 270,
     TRUE = 271,
     FALSE = 272,
     NEW = 273,
     THIS = 274,
     ID = 275,
     INTEGER_LITERAL = 276,
     STRING = 277,
     BOOLEAN = 278,
     INT = 279
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 14 "parser.y"

	int ival;
	char sval[255];
	void* pval;


/* Line 387 of yacc.c  */
#line 153 "parser.tab.cpp"
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

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
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

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 194 "parser.tab.cpp"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
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
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   438

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNRULES -- Number of states.  */
#define YYNSTATES  199

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    10,     2,     2,     2,     2,     2,     2,
      37,    38,     8,     6,    41,     7,    12,     9,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
       3,     5,     4,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    13,     2,    14,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    39,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,    11,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    31,    50,    55,
      61,    68,    74,    81,    89,    98,   106,   108,   111,   115,
     119,   121,   124,   136,   149,   163,   176,   187,   199,   212,
     224,   227,   231,   235,   240,   242,   246,   248,   250,   252,
     255,   260,   268,   274,   277,   281,   289,   295,   298,   302,
     306,   310,   314,   318,   321,   326,   330,   337,   343,   345,
     347,   349,   351,   353,   359,   364,   367,   371,   373,   376,
     379
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    45,    -1,    45,    44,    -1,    46,    -1,
      44,    46,    -1,    15,    31,    36,    16,    17,    18,    19,
      37,    33,    13,    14,    31,    38,    36,    54,    39,    39,
      -1,    15,    31,    36,    16,    17,    18,    19,    37,    33,
      13,    14,    31,    38,    36,    54,     1,    39,    39,    -1,
      15,    31,    36,    39,    -1,    15,    31,    36,    47,    39,
      -1,    15,    31,    36,    47,    49,    39,    -1,    15,    31,
      36,    49,    39,    -1,    15,    31,    20,    31,    36,    39,
      -1,    15,    31,    20,    31,    36,    47,    39,    -1,    15,
      31,    20,    31,    36,    47,    49,    39,    -1,    15,    31,
      20,    31,    36,    49,    39,    -1,    48,    -1,    47,    48,
      -1,    53,    31,    40,    -1,    53,     1,    40,    -1,    50,
      -1,    49,    50,    -1,    16,    53,    31,    37,    51,    38,
      36,    21,    56,    40,    39,    -1,    16,    53,    31,    37,
      51,    38,    36,    47,    21,    56,    40,    39,    -1,    16,
      53,    31,    37,    51,    38,    36,    47,    54,    21,    56,
      40,    39,    -1,    16,    53,    31,    37,    51,    38,    36,
      54,    21,    56,    40,    39,    -1,    16,    53,    31,    37,
      38,    36,    21,    56,    40,    39,    -1,    16,    53,    31,
      37,    38,    36,    47,    21,    56,    40,    39,    -1,    16,
      53,    31,    37,    38,    36,    47,    54,    21,    56,    40,
      39,    -1,    16,    53,    31,    37,    38,    36,    54,    21,
      56,    40,    39,    -1,    53,    31,    -1,    53,    31,    52,
      -1,    41,    53,    31,    -1,    52,    41,    53,    31,    -1,
      35,    -1,    35,    13,    14,    -1,    34,    -1,    31,    -1,
      55,    -1,    54,    55,    -1,    31,     5,    56,    40,    -1,
      31,    13,    56,    14,     5,    56,    40,    -1,    25,    37,
      56,    38,    40,    -1,    36,    39,    -1,    36,    54,    39,
      -1,    23,    37,    56,    38,    55,    22,    55,    -1,    24,
      37,    56,    38,    55,    -1,     1,    40,    -1,    25,     1,
      40,    -1,    56,     8,    56,    -1,    56,     6,    56,    -1,
      56,     9,    56,    -1,    56,     7,    56,    -1,     7,    56,
      -1,    56,    13,    56,    14,    -1,    56,    12,    26,    -1,
      56,    12,    31,    37,    57,    38,    -1,    56,    12,    31,
      37,    38,    -1,    32,    -1,    27,    -1,    28,    -1,    31,
      -1,    30,    -1,    29,    35,    13,    56,    14,    -1,    29,
      31,    37,    38,    -1,    10,    56,    -1,    37,    56,    38,
      -1,    56,    -1,    56,    58,    -1,    41,    56,    -1,    58,
      41,    56,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    76,    76,    77,    80,    81,    84,    85,    87,    88,
      89,    90,    91,    92,    93,    94,    97,    98,   101,   102,
     105,   106,   109,   110,   111,   112,   113,   114,   115,   116,
     119,   120,   123,   124,   127,   128,   129,   130,   133,   134,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   169,   170,   173,
     174
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'<'", "'>'", "'='", "'+'", "'-'", "'*'",
  "'/'", "'!'", "UMINUS", "'.'", "'['", "']'", "CLASS", "PUBLIC", "STATIC",
  "VOID", "MAIN", "EXTENDS", "RETURN", "ELSE", "IF", "WHILE",
  "SYSTEM_OUT_PRINTLN", "LENGTH", "TRUE", "FALSE", "NEW", "THIS", "ID",
  "INTEGER_LITERAL", "STRING", "BOOLEAN", "INT", "'{'", "'('", "')'",
  "'}'", "';'", "','", "$accept", "Program", "ClassDecls", "MainClass",
  "ClassDecl", "VarDecls", "VarDecl", "MethodDecls", "MethodDecl",
  "FormalList", "FormalRest", "Type", "Statements", "Statement", "Exp",
  "ExpList", "ExpRest", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    60,    62,    61,    43,    45,    42,    47,
      33,   258,    46,    91,    93,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   123,    40,    41,   125,
      59,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    47,    47,    48,    48,
      49,    49,    50,    50,    50,    50,    50,    50,    50,    50,
      51,    51,    52,    52,    53,    53,    53,    53,    54,    54,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    57,    57,    58,
      58
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,    17,    18,     4,     5,
       6,     5,     6,     7,     8,     7,     1,     2,     3,     3,
       1,     2,    11,    12,    13,    12,    10,    11,    12,    11,
       2,     3,     3,     4,     1,     3,     1,     1,     1,     2,
       4,     7,     5,     2,     3,     7,     5,     2,     3,     3,
       3,     3,     3,     2,     4,     3,     6,     5,     1,     1,
       1,     1,     1,     5,     4,     2,     3,     1,     2,     2,
       3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     3,     4,     0,
       0,     5,     0,     0,     0,     0,     0,     0,    37,    36,
      34,     8,     0,    16,     0,    20,     0,     0,     0,     0,
       0,     9,    17,     0,    11,    21,     0,     0,     0,    12,
       0,     0,     0,    35,    10,    19,    18,     0,    13,     0,
      15,     0,     0,    14,     0,     0,     0,     0,     0,     0,
      30,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,    38,     0,     0,    31,     0,    47,     0,     0,    59,
      60,     0,    62,    61,    58,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    43,     0,     0,     0,     0,    39,
       0,     0,     0,     0,     0,     0,    53,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      48,     0,     0,     0,    44,     0,     0,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,    66,    50,    52,
      49,    51,    55,     0,     0,    26,     0,     0,     0,    40,
       0,     0,     0,     0,     0,     0,     0,     0,    33,     0,
      64,     0,     0,    54,     0,    46,    42,     0,    27,     0,
      29,    22,     0,     0,     0,     0,     0,    63,    57,    67,
       0,     0,     0,    28,    23,     0,    25,     0,     6,     0,
      68,    56,    45,    41,    24,     7,    69,     0,    70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,     3,     8,    22,    23,    24,    25,    55,
      74,    26,    70,    71,    86,   180,   190
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -78
static const yytype_int16 yypact[] =
{
     -12,   -19,    18,    15,    21,   -78,    33,    15,   -78,    44,
      72,   -78,    60,    36,   309,    89,    80,   149,   -78,   -78,
     109,   -78,   352,   -78,   -11,   -78,    16,   111,   354,   107,
     126,   -78,   -78,     6,   -78,   -78,   108,   116,   129,   -78,
     364,    32,   137,   -78,   -78,   -78,   -78,   168,   -78,    45,
     -78,    34,   174,   -78,   171,   178,   161,   195,   100,   182,
     169,   188,   185,   347,   191,   192,     3,    11,    50,   118,
     172,   -78,   136,   149,   186,   198,   -78,   347,   347,   -78,
     -78,    78,   -78,   -78,   -78,   347,   233,   347,   347,   203,
     347,   347,   347,    11,   -78,    75,   347,   181,   347,   -78,
     347,   154,   190,   213,   149,   215,    84,    84,   228,   239,
     120,   347,   347,   347,   347,   155,   347,   257,   138,   156,
     -78,   323,   241,   398,   -78,   249,   347,   262,   270,   347,
     199,   347,   -78,   236,    19,   234,   347,   -78,   251,   251,
      84,    84,   -78,   243,   407,   -78,    19,    19,   248,   -78,
     292,   261,   278,   264,   265,   286,   347,   299,   -78,    79,
     -78,   416,   335,   -78,   279,   -78,   -78,   347,   -78,   294,
     -78,   -78,   295,   307,   298,   159,   302,   -78,   -78,   225,
     271,    19,   315,   -78,   -78,   310,   -78,   311,   -78,   347,
     276,   -78,   -78,   -78,   -78,   -78,   425,   347,   425
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -78,   -78,   -78,   -78,   331,   -26,   -13,    65,    29,   -78,
     -78,   -10,   -43,   -64,   -77,   -78,   -78
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
     106,   107,    40,     1,    89,    17,    99,    29,   110,    32,
     118,   119,     4,   121,   122,   123,    91,    36,     5,   125,
      62,   127,    17,   128,    92,    95,    97,    32,    34,   102,
       6,    99,    69,    99,   138,   139,   140,   141,    99,   144,
      90,    56,    64,    65,    66,    44,   101,    37,    17,   152,
      93,    62,   155,    35,   157,    68,    32,     9,   130,   161,
      12,    17,    35,   103,    10,    18,    99,    16,    19,    20,
      35,    50,    54,    64,    65,    66,    62,    15,    35,   173,
     175,    93,   164,   165,    53,   179,    68,    33,    32,    94,
     182,   159,    13,    41,   133,    99,   115,   116,    64,    65,
      66,    62,    64,    65,    66,    49,    93,    27,    14,   108,
      93,    68,   196,   109,   124,    68,    28,   192,   176,    62,
     198,    63,    30,    64,    65,    66,   111,   112,   113,   114,
      38,    67,   115,   116,    19,    20,    68,    62,    42,    96,
      43,    64,    65,    66,   111,   112,   113,   114,    45,    67,
     115,   116,    19,    20,    68,    62,    46,   100,   137,    64,
      65,    66,   111,   112,   113,   114,    47,    67,   115,   116,
      19,    20,    68,    62,    51,   129,   146,    64,    65,    66,
      18,   142,    62,    19,    20,    67,   143,    57,    19,    20,
      68,    62,    60,    98,   147,    64,    65,    66,   187,    76,
      62,    52,   126,    93,    64,    65,    66,    58,    68,    61,
      73,   131,    93,    64,    65,    66,    59,    68,    72,    75,
     156,    93,    64,    65,    66,    76,    68,   104,    87,    88,
      93,   111,   112,   113,   114,    68,   105,   115,   116,   111,
     112,   113,   114,   120,   132,   115,   116,   111,   112,   113,
     114,   134,   136,   115,   116,   111,   112,   113,   114,   113,
     114,   115,   116,   115,   116,   135,   189,   158,   111,   112,
     113,   114,   160,   117,   115,   116,   111,   112,   113,   114,
     162,   149,   115,   116,   111,   112,   113,   114,   166,   151,
     115,   116,   111,   112,   113,   114,   145,   167,   115,   116,
     168,   181,   153,   170,   171,   111,   112,   113,   114,   191,
     154,   115,   116,   111,   112,   113,   114,   197,   169,   115,
     116,   111,   112,   113,   114,    17,   172,   115,   116,   111,
     112,   113,   114,   183,   184,   115,   116,   186,    11,   174,
      18,   188,    77,    19,    20,    78,     0,   185,    21,   194,
     195,     0,     0,     0,    77,   193,     0,    78,     0,     0,
       0,   148,    79,    80,    81,    82,    83,    84,    17,     0,
      17,     0,    85,   178,    79,    80,    81,    82,    83,    84,
      17,     0,     0,    18,    85,    18,    19,    20,    19,    20,
       0,    31,     0,    39,     0,    18,     0,     0,    19,    20,
       0,     0,     0,    48,   111,   112,   113,   114,     0,     0,
     115,   116,   150,   111,   112,   113,   114,     0,     0,   115,
     116,   163,   111,   112,   113,   114,     0,     0,   115,   116,
     177,   111,   112,   113,   114,     0,     0,   115,   116
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-78)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      77,    78,    28,    15,     1,    16,    70,    17,    85,    22,
      87,    88,    31,    90,    91,    92,     5,     1,     0,    96,
       1,    98,    16,   100,    13,    68,    69,    40,    39,    72,
      15,    95,    58,    97,   111,   112,   113,   114,   102,   116,
      37,    51,    23,    24,    25,    39,    72,    31,    16,   126,
      31,     1,   129,    24,   131,    36,    69,    36,   101,   136,
      16,    16,    33,    73,    31,    31,   130,    31,    34,    35,
      41,    39,    38,    23,    24,    25,     1,    17,    49,   156,
       1,    31,   146,   147,    39,   162,    36,    22,   101,    39,
     167,   134,    20,    28,   104,   159,    12,    13,    23,    24,
      25,     1,    23,    24,    25,    40,    31,    18,    36,    31,
      31,    36,   189,    35,    39,    36,    36,   181,    39,     1,
     197,    21,    13,    23,    24,    25,     6,     7,     8,     9,
      19,    31,    12,    13,    34,    35,    36,     1,    31,    21,
      14,    23,    24,    25,     6,     7,     8,     9,    40,    31,
      12,    13,    34,    35,    36,     1,    40,    21,    38,    23,
      24,    25,     6,     7,     8,     9,    37,    31,    12,    13,
      34,    35,    36,     1,    37,    21,    38,    23,    24,    25,
      31,    26,     1,    34,    35,    31,    31,    13,    34,    35,
      36,     1,    31,    21,    38,    23,    24,    25,    39,    40,
       1,    33,    21,    31,    23,    24,    25,    36,    36,    14,
      41,    21,    31,    23,    24,    25,    38,    36,    36,    31,
      21,    31,    23,    24,    25,    40,    36,    41,    37,    37,
      31,     6,     7,     8,     9,    36,    38,    12,    13,     6,
       7,     8,     9,    40,    31,    12,    13,     6,     7,     8,
       9,    36,    13,    12,    13,     6,     7,     8,     9,     8,
       9,    12,    13,    12,    13,    37,    41,    31,     6,     7,
       8,     9,    38,    40,    12,    13,     6,     7,     8,     9,
      37,    40,    12,    13,     6,     7,     8,     9,    40,    40,
      12,    13,     6,     7,     8,     9,    39,     5,    12,    13,
      39,    22,    40,    39,    39,     6,     7,     8,     9,    38,
      40,    12,    13,     6,     7,     8,     9,    41,    40,    12,
      13,     6,     7,     8,     9,    16,    40,    12,    13,     6,
       7,     8,     9,    39,    39,    12,    13,    39,     7,    40,
      31,    39,     7,    34,    35,    10,    -1,    40,    39,    39,
      39,    -1,    -1,    -1,     7,    40,    -1,    10,    -1,    -1,
      -1,    38,    27,    28,    29,    30,    31,    32,    16,    -1,
      16,    -1,    37,    38,    27,    28,    29,    30,    31,    32,
      16,    -1,    -1,    31,    37,    31,    34,    35,    34,    35,
      -1,    39,    -1,    39,    -1,    31,    -1,    -1,    34,    35,
      -1,    -1,    -1,    39,     6,     7,     8,     9,    -1,    -1,
      12,    13,    14,     6,     7,     8,     9,    -1,    -1,    12,
      13,    14,     6,     7,     8,     9,    -1,    -1,    12,    13,
      14,     6,     7,     8,     9,    -1,    -1,    12,    13
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    15,    43,    45,    31,     0,    15,    44,    46,    36,
      31,    46,    16,    20,    36,    17,    31,    16,    31,    34,
      35,    39,    47,    48,    49,    50,    53,    18,    36,    53,
      13,    39,    48,    49,    39,    50,     1,    31,    19,    39,
      47,    49,    31,    14,    39,    40,    40,    37,    39,    49,
      39,    37,    33,    39,    38,    51,    53,    13,    36,    38,
      31,    14,     1,    21,    23,    24,    25,    31,    36,    47,
      54,    55,    36,    41,    52,    31,    40,     7,    10,    27,
      28,    29,    30,    31,    32,    37,    56,    37,    37,     1,
      37,     5,    13,    31,    39,    54,    21,    54,    21,    55,
      21,    47,    54,    53,    41,    38,    56,    56,    31,    35,
      56,     6,     7,     8,     9,    12,    13,    40,    56,    56,
      40,    56,    56,    56,    39,    56,    21,    56,    56,    21,
      54,    21,    31,    53,    36,    37,    13,    38,    56,    56,
      56,    56,    26,    31,    56,    39,    38,    38,    38,    40,
      14,    40,    56,    40,    40,    56,    21,    56,    31,    54,
      38,    56,    37,    14,    55,    55,    40,     5,    39,    40,
      39,    39,    40,    56,    40,     1,    39,    14,    38,    56,
      57,    22,    56,    39,    39,    40,    39,    39,    39,    41,
      58,    38,    55,    40,    39,    39,    56,    41,    56
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

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;


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

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
/* Line 1792 of yacc.c  */
#line 76 "parser.y"
    { (yyval.pval) = new CProgram( static_cast<CMainClass*>( (yyvsp[(1) - (1)].pval) ), 0 ); CPrettyPrinterVisitor visitor; CMainClass* main = static_cast<CMainClass*>( (yyval.pval) ); main->accept( visitor ); CSymbolTableConstructor table; main->accept( table ); delete main;  }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 77 "parser.y"
    { (yyval.pval) = new CProgram( static_cast<CMainClass*>( (yyvsp[(1) - (2)].pval) ), static_cast<CClassDeclList*>( (yyvsp[(2) - (2)].pval) ) ); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 80 "parser.y"
    { (yyval.pval) = new CClassDeclList( 0, static_cast<CClassDecl*>( (yyvsp[(1) - (1)].pval) ) ); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 81 "parser.y"
    { (yyval.pval) = new CClassDeclList( static_cast<CClassDeclList*>( (yyvsp[(1) - (2)].pval) ), static_cast<CClassDecl*>( (yyvsp[(2) - (2)].pval) ) ); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 84 "parser.y"
    { (yyval.pval) = new CMainClass( (yyvsp[(2) - (17)].sval), (yyvsp[(12) - (17)].sval), static_cast<CStatementList*>( (yyvsp[(15) - (17)].pval) ) ); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 85 "parser.y"
    { std::cout << "Syntax error : incorrect symbols in Main function in line : " << (yylsp[(16) - (18)]).first_line << std::endl; }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 87 "parser.y"
    { (yyval.pval) = new CClassDecl( (yyvsp[(2) - (4)].sval), 0, 0, 0 ); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 88 "parser.y"
    { (yyval.pval) = new CClassDecl( (yyvsp[(2) - (5)].sval), static_cast<CVarDeclList*>( (yyvsp[(4) - (5)].pval) ), 0, 0 ); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 89 "parser.y"
    { (yyval.pval) = new CClassDecl( (yyvsp[(2) - (6)].sval), static_cast<CVarDeclList*>(yyvsp[(4) - (6)].pval), static_cast<CMethodDeclList*>( (yyvsp[(5) - (6)].pval) ), 0 ); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 90 "parser.y"
    { (yyval.pval) = new CClassDecl( (yyvsp[(2) - (5)].sval), 0, static_cast<CMethodDeclList*>( (yyvsp[(4) - (5)].pval) ), 0 ); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 91 "parser.y"
    { (yyval.pval) = new CClassDecl( (yyvsp[(2) - (6)].sval), 0, 0, (yyvsp[(4) - (6)].sval) ); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 92 "parser.y"
    { (yyval.pval) = new CClassDecl( (yyvsp[(2) - (7)].sval), static_cast<CVarDeclList*>( (yyvsp[(6) - (7)].pval) ), 0, (yyvsp[(4) - (7)].sval) ); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 93 "parser.y"
    { (yyval.pval) = new CClassDecl( (yyvsp[(2) - (8)].sval), static_cast<CVarDeclList*>( (yyvsp[(6) - (8)].pval) ), static_cast<CMethodDeclList*>( (yyvsp[(7) - (8)].pval) ), (yyvsp[(4) - (8)].sval) ); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 94 "parser.y"
    { (yyval.pval) = new CClassDecl( (yyvsp[(2) - (7)].sval), 0, static_cast<CMethodDeclList*>( (yyvsp[(6) - (7)].pval) ), (yyvsp[(4) - (7)].sval) ); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 97 "parser.y"
    { (yyval.pval) = new CVarDeclList( 0, static_cast<CVarDecl*>( (yyvsp[(1) - (1)].pval) ) ); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 98 "parser.y"
    { (yyval.pval) = new CVarDeclList( static_cast<CVarDeclList*>( (yyvsp[(1) - (2)].pval) ) , static_cast<CVarDecl*>( (yyvsp[(2) - (2)].pval) ) ); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 101 "parser.y"
    { (yyval.pval) = new CVarDecl( static_cast<CType*>( (yyvsp[(1) - (3)].pval) ), (yyvsp[(2) - (3)].sval) ); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 102 "parser.y"
    { std::cout << "Syntax error : incorrect variable definition in line : " << (yylsp[(2) - (3)]).first_line << std::endl; }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 105 "parser.y"
    { (yyval.pval) = new CMethodDeclList( 0, static_cast<CMethodDecl*>( (yyvsp[(1) - (1)].pval) ) ); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 106 "parser.y"
    { (yyval.pval) = new CMethodDeclList( static_cast<CMethodDeclList*>( (yyvsp[(1) - (2)].pval) ), static_cast<CMethodDecl*>( (yyvsp[(2) - (2)].pval) ) ); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 109 "parser.y"
    { (yyval.pval) = new CMethodDecl( static_cast<CType*>( (yyvsp[(2) - (11)].pval) ), (yyvsp[(3) - (11)].sval), static_cast<CFormalList*>( (yyvsp[(5) - (11)].pval) ), 0, 0, static_cast<IExp*>( (yyvsp[(9) - (11)].pval) ) ); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 110 "parser.y"
    { (yyval.pval) = new CMethodDecl( static_cast<CType*>( (yyvsp[(2) - (12)].pval) ), (yyvsp[(3) - (12)].sval), static_cast<CFormalList*>( (yyvsp[(5) - (12)].pval) ), static_cast<CVarDeclList*>( (yyvsp[(8) - (12)].pval) ), 0, static_cast<IExp*>( (yyvsp[(10) - (12)].pval) ) ); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 111 "parser.y"
    { (yyval.pval) = new CMethodDecl( static_cast<CType*>( (yyvsp[(2) - (13)].pval) ), (yyvsp[(3) - (13)].sval), static_cast<CFormalList*>( (yyvsp[(5) - (13)].pval) ), static_cast<CVarDeclList*>( (yyvsp[(8) - (13)].pval) ), static_cast<CStatementList*>( (yyvsp[(9) - (13)].pval) ), static_cast<IExp*>( (yyvsp[(11) - (13)].pval) ) ); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 112 "parser.y"
    { (yyval.pval) = new CMethodDecl( static_cast<CType*>( (yyvsp[(2) - (12)].pval) ), (yyvsp[(3) - (12)].sval), static_cast<CFormalList*>( (yyvsp[(5) - (12)].pval) ), 0, static_cast<CStatementList*>( (yyvsp[(8) - (12)].pval) ), static_cast<IExp*>( (yyvsp[(10) - (12)].pval) ) ); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 113 "parser.y"
    { (yyval.pval) = new CMethodDecl( static_cast<CType*>( (yyvsp[(2) - (10)].pval) ), (yyvsp[(3) - (10)].sval), 0, 0, 0, static_cast<IExp*>( (yyvsp[(8) - (10)].pval) ) ); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 114 "parser.y"
    { (yyval.pval) = new CMethodDecl( static_cast<CType*>( (yyvsp[(2) - (11)].pval) ), (yyvsp[(3) - (11)].sval), 0, static_cast<CVarDeclList*>( (yyvsp[(7) - (11)].pval) ), 0, static_cast<IExp*>( (yyvsp[(9) - (11)].pval) ) ); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 115 "parser.y"
    { (yyval.pval) = new CMethodDecl( static_cast<CType*>( (yyvsp[(2) - (12)].pval) ), (yyvsp[(3) - (12)].sval), 0, static_cast<CVarDeclList*>( (yyvsp[(7) - (12)].pval) ), static_cast<CStatementList*>( (yyvsp[(8) - (12)].pval) ), static_cast<IExp*>( (yyvsp[(10) - (12)].pval) ) ); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 116 "parser.y"
    { (yyval.pval) = new CMethodDecl( static_cast<CType*>( (yyvsp[(2) - (11)].pval) ), (yyvsp[(3) - (11)].sval), 0, 0, static_cast<CStatementList*>( (yyvsp[(7) - (11)].pval) ), static_cast<IExp*>( (yyvsp[(9) - (11)].pval) ) ); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 119 "parser.y"
    { (yyval.pval) = new CFormalList( 0, static_cast<CType*>( (yyvsp[(1) - (2)].pval) ), (yyvsp[(2) - (2)].sval) ); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 120 "parser.y"
    { (yyval.pval) = new CFormalList( static_cast<CFormalList*>( (yyvsp[(3) - (3)].pval) ), static_cast<CType*>( (yyvsp[(1) - (3)].pval) ), (yyvsp[(2) - (3)].sval) ); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 123 "parser.y"
    { (yyval.pval) = new CFormalList( 0, static_cast<CType*>( (yyvsp[(2) - (3)].pval) ), (yyvsp[(3) - (3)].sval) ); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 124 "parser.y"
    { (yyval.pval) = new CFormalList( static_cast<CFormalList*>( (yyvsp[(1) - (4)].pval) ), static_cast<CType*>( (yyvsp[(3) - (4)].pval) ), (yyvsp[(4) - (4)].sval) ); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 127 "parser.y"
    { (yyval.pval) = new CType( "int" ); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 128 "parser.y"
    { (yyval.pval) = new CType( "int[]" ); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 129 "parser.y"
    { (yyval.pval) = new CType( "bool" ); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 130 "parser.y"
    { (yyval.pval) = new CType( (yyvsp[(1) - (1)].sval) ); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 133 "parser.y"
    { (yyval.pval) = new CStatementList( 0, static_cast<IStatement*>( (yyvsp[(1) - (1)].pval) ) ); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 134 "parser.y"
    { (yyval.pval) = new CStatementList( static_cast<CStatementList*>( (yyvsp[(1) - (2)].pval) ), static_cast<IStatement*>( (yyvsp[(2) - (2)].pval) ) ); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 137 "parser.y"
    { (yyval.pval) = new CAssignStatement( (yyvsp[(1) - (4)].sval), 0, static_cast<IExp*>( (yyvsp[(3) - (4)].pval) ) ); }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 138 "parser.y"
    { (yyval.pval) = new CAssignStatement( (yyvsp[(1) - (7)].sval), static_cast<IExp*>( (yyvsp[(3) - (7)].pval) ), static_cast<IExp*>( (yyvsp[(6) - (7)].pval) ) ); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 139 "parser.y"
    { (yyval.pval) = new CPrintStatement( static_cast<IExp*>( (yyvsp[(3) - (5)].pval) ) ); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 140 "parser.y"
    { (yyval.pval) = new CCurlyBraceStatement( 0 ); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 141 "parser.y"
    { (yyval.pval) = new CCurlyBraceStatement( static_cast<IStatementList*>( (yyvsp[(2) - (3)].pval) ) ); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 142 "parser.y"
    { (yyval.pval) = new CIfStatement( static_cast<IExp*>( (yyvsp[(3) - (7)].pval) ), static_cast<IStatement*>( (yyvsp[(5) - (7)].pval) ), static_cast<IStatement*>( (yyvsp[(7) - (7)].pval) ) ); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 143 "parser.y"
    { (yyval.pval) = new CWhileStatement( static_cast<IExp*>( (yyvsp[(3) - (5)].pval) ), static_cast<IStatement*>( (yyvsp[(5) - (5)].pval) ) ); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 144 "parser.y"
    { std::cout << "Syntax error : incorrect statement in line :" << (yylsp[(1) - (2)]).first_line << std::endl; }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 145 "parser.y"
    { std::cout << "Syntax error : incorrect Println-statement in line : " << (yylsp[(2) - (3)]).first_line << std::endl; }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 149 "parser.y"
    { (yyval.pval) = new CExpBinOpExp( static_cast<IExp*>( (yyvsp[(1) - (3)].pval) ), '*', static_cast<IExp*>( (yyvsp[(3) - (3)].pval) ) ); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 150 "parser.y"
    { (yyval.pval) = new CExpBinOpExp( static_cast<IExp*>( (yyvsp[(1) - (3)].pval) ), '+', static_cast<IExp*>( (yyvsp[(3) - (3)].pval) ) ); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 151 "parser.y"
    { (yyval.pval) = new CExpBinOpExp( static_cast<IExp*>( (yyvsp[(1) - (3)].pval) ), '/', static_cast<IExp*>( (yyvsp[(3) - (3)].pval) ) ); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 152 "parser.y"
    { (yyval.pval) = new CExpBinOpExp( static_cast<IExp*>( (yyvsp[(1) - (3)].pval) ), '-', static_cast<IExp*>( (yyvsp[(3) - (3)].pval) ) ); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 153 "parser.y"
    { (yyval.pval) = new CUnMinExp( static_cast<IExp*>( (yyvsp[(2) - (2)].pval) ) ); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 154 "parser.y"
    { (yyval.pval) = new CExpWithIndex( static_cast<IExp*>( (yyvsp[(1) - (4)].pval) ), static_cast<IExp*>( (yyvsp[(3) - (4)].pval) ) ); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 155 "parser.y"
    { (yyval.pval) = new CExpDotLength( static_cast<IExp*>( (yyvsp[(1) - (3)].pval) ) ); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 156 "parser.y"
    { (yyval.pval) = new CExpIdExpList( static_cast<IExp*>( (yyvsp[(1) - (6)].pval) ), (yyvsp[(3) - (6)].sval), static_cast<IExpList*>( (yyvsp[(5) - (6)].pval) ) ); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 157 "parser.y"
    { (yyval.pval) = new CExpIdVoidExpList( static_cast<IExp*>( (yyvsp[(1) - (5)].pval) ), (yyvsp[(3) - (5)].sval) ) ; }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 158 "parser.y"
    { (yyval.pval) = new CIntegerLiteral( (yyvsp[(1) - (1)].ival) ); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 159 "parser.y"
    { (yyval.pval) = new CTrue(); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 160 "parser.y"
    { (yyval.pval) = new CFalse(); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 161 "parser.y"
    { (yyval.pval) = new CId( (yyvsp[(1) - (1)].sval) ); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 162 "parser.y"
    { (yyval.pval) = new CThis(); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 163 "parser.y"
    { (yyval.pval) = new CNewIntExpIndex( static_cast<IExp*>( (yyvsp[(4) - (5)].pval) ) ); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 164 "parser.y"
    { (yyval.pval) = new CNewId( (yyvsp[(2) - (4)].sval) ); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 165 "parser.y"
    { (yyval.pval) = new CNotExp( static_cast<IExp*>( (yyvsp[(2) - (2)].pval) ) ); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 166 "parser.y"
    { (yyval.pval) = new CExpInBrackets( static_cast<IExp*>( (yyvsp[(2) - (3)].pval) ) ); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 169 "parser.y"
    { (yyval.pval) = new CExpList( 0, static_cast<IExp*>( (yyvsp[(1) - (1)].pval) ) ); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 170 "parser.y"
    { (yyval.pval) = new CExpList( static_cast<CExpList*>( (yyvsp[(2) - (2)].pval) ), static_cast<IExp*>( (yyvsp[(1) - (2)].pval) ) ); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 173 "parser.y"
    { (yyval.pval) = new CExpList( 0, static_cast<IExp*>( (yyvsp[(2) - (2)].pval) ) ); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 174 "parser.y"
    { (yyval.pval) = new CExpList( static_cast<CExpList*>( (yyvsp[(1) - (3)].pval) ), static_cast<IExp*>( (yyvsp[(3) - (3)].pval) ) ); }
    break;


/* Line 1792 of yacc.c  */
#line 2124 "parser.tab.cpp"
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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

#if !defined yyoverflow || YYERROR_VERBOSE
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


/* Line 2055 of yacc.c  */
#line 177 "parser.y"


void yyerror( const char* str )
{
	std::cout << str << std::endl;
}