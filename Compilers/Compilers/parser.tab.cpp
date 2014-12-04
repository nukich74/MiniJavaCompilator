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
#include <memory>
#include <common.h>
#include <Location.h>
extern "C" int yylex();
using std::make_shared;
using std::shared_ptr;

void yyerror( std::shared_ptr<CProgram>&, int*, const char *);

/* Line 371 of yacc.c  */
#line 80 "parser.tab.cpp"

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
/* "%code requires" blocks.  */
/* Line 387 of yacc.c  */
#line 13 "parser.y"
 #include <common.h> 
/* Line 387 of yacc.c  */
#line 15 "parser.y"
 #include <memory> 

/* Line 387 of yacc.c  */
#line 118 "parser.tab.cpp"

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
#line 23 "parser.y"

	int ival;
	char sval[255];
	CProgram* program;
	CMainClass* mainClass;
	CClassDeclList* classDecls;
	CClassDecl* classDecl;
	CStatementList* statements;
	IStatement* statement;
	CVarDeclList* varDecls;
	CVarDecl* varDecl;
	CMethodDeclList* methodDecls;
	CMethodDecl* methodDecl;
	CType* type;
	CFormalList* formalList;
	CExpList* expList;
	IExp* exp;


/* Line 387 of yacc.c  */
#line 177 "parser.tab.cpp"
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
int yyparse (std::shared_ptr<CProgram>& root, int* hasError);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 218 "parser.tab.cpp"

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
#define YYLAST   528

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNRULES -- Number of states.  */
#define YYNSTATES  203

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
       2,     2,     2,    11,     2,     2,     2,     2,     3,     2,
      38,    39,     9,     7,    42,     8,    13,    10,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
       4,     6,     5,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    14,     2,    15,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    40,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,    12,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36
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
     306,   310,   314,   318,   322,   326,   329,   334,   338,   345,
     351,   353,   355,   357,   359,   361,   367,   372,   375,   379,
     381,   384,   387
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    46,    -1,    46,    45,    -1,    47,    -1,
      45,    47,    -1,    16,    32,    37,    17,    18,    19,    20,
      38,    34,    14,    15,    32,    39,    37,    55,    40,    40,
      -1,    16,    32,    37,    17,    18,    19,    20,    38,    34,
      14,    15,    32,    39,    37,    55,     1,    40,    40,    -1,
      16,    32,    37,    40,    -1,    16,    32,    37,    48,    40,
      -1,    16,    32,    37,    48,    50,    40,    -1,    16,    32,
      37,    50,    40,    -1,    16,    32,    21,    32,    37,    40,
      -1,    16,    32,    21,    32,    37,    48,    40,    -1,    16,
      32,    21,    32,    37,    48,    50,    40,    -1,    16,    32,
      21,    32,    37,    50,    40,    -1,    49,    -1,    48,    49,
      -1,    54,    32,    41,    -1,    54,     1,    41,    -1,    51,
      -1,    50,    51,    -1,    17,    54,    32,    38,    52,    39,
      37,    22,    57,    41,    40,    -1,    17,    54,    32,    38,
      52,    39,    37,    48,    22,    57,    41,    40,    -1,    17,
      54,    32,    38,    52,    39,    37,    48,    55,    22,    57,
      41,    40,    -1,    17,    54,    32,    38,    52,    39,    37,
      55,    22,    57,    41,    40,    -1,    17,    54,    32,    38,
      39,    37,    22,    57,    41,    40,    -1,    17,    54,    32,
      38,    39,    37,    48,    22,    57,    41,    40,    -1,    17,
      54,    32,    38,    39,    37,    48,    55,    22,    57,    41,
      40,    -1,    17,    54,    32,    38,    39,    37,    55,    22,
      57,    41,    40,    -1,    54,    32,    -1,    54,    32,    53,
      -1,    42,    54,    32,    -1,    53,    42,    54,    32,    -1,
      36,    -1,    36,    14,    15,    -1,    35,    -1,    32,    -1,
      56,    -1,    55,    56,    -1,    32,     6,    57,    41,    -1,
      32,    14,    57,    15,     6,    57,    41,    -1,    26,    38,
      57,    39,    41,    -1,    37,    40,    -1,    37,    55,    40,
      -1,    24,    38,    57,    39,    56,    23,    56,    -1,    25,
      38,    57,    39,    56,    -1,     1,    41,    -1,    26,     1,
      41,    -1,    57,     9,    57,    -1,    57,     7,    57,    -1,
      57,    10,    57,    -1,    57,     8,    57,    -1,    57,     4,
      57,    -1,    57,     3,    57,    -1,     8,    57,    -1,    57,
      14,    57,    15,    -1,    57,    13,    27,    -1,    57,    13,
      32,    38,    58,    39,    -1,    57,    13,    32,    38,    39,
      -1,    33,    -1,    28,    -1,    29,    -1,    32,    -1,    31,
      -1,    30,    36,    14,    57,    15,    -1,    30,    32,    38,
      39,    -1,    11,    57,    -1,    38,    57,    39,    -1,    57,
      -1,    57,    59,    -1,    42,    57,    -1,    59,    42,    57,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   126,   126,   127,   130,   131,   134,   135,   137,   138,
     139,   140,   141,   142,   143,   144,   147,   148,   151,   152,
     155,   156,   159,   160,   161,   162,   163,   164,   165,   166,
     169,   170,   173,   174,   177,   178,   179,   180,   183,   184,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   221,
     222,   225,   226
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'&'", "'<'", "'>'", "'='", "'+'", "'-'",
  "'*'", "'/'", "'!'", "UMINUS", "'.'", "'['", "']'", "CLASS", "PUBLIC",
  "STATIC", "VOID", "MAIN", "EXTENDS", "RETURN", "ELSE", "IF", "WHILE",
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
       0,   256,   257,    38,    60,    62,    61,    43,    45,    42,
      47,    33,   258,    46,    91,    93,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   123,    40,    41,
     125,    59,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    44,    45,    45,    46,    46,    47,    47,
      47,    47,    47,    47,    47,    47,    48,    48,    49,    49,
      50,    50,    51,    51,    51,    51,    51,    51,    51,    51,
      52,    52,    53,    53,    54,    54,    54,    54,    55,    55,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    59,    59
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,    17,    18,     4,     5,
       6,     5,     6,     7,     8,     7,     1,     2,     3,     3,
       1,     2,    11,    12,    13,    12,    10,    11,    12,    11,
       2,     3,     3,     4,     1,     3,     1,     1,     1,     2,
       4,     7,     5,     2,     3,     7,     5,     2,     3,     3,
       3,     3,     3,     3,     3,     2,     4,     3,     6,     5,
       1,     1,     1,     1,     1,     5,     4,     2,     3,     1,
       2,     2,     3
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
       0,    38,     0,     0,    31,     0,    47,     0,     0,    61,
      62,     0,    64,    63,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    43,     0,     0,     0,     0,    39,
       0,     0,     0,     0,     0,     0,    55,    67,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,     0,     0,     0,    44,     0,     0,     0,
       0,     0,     0,     0,    32,     0,     0,     0,     0,    68,
      54,    53,    50,    52,    49,    51,    57,     0,     0,    26,
       0,     0,     0,    40,     0,     0,     0,     0,     0,     0,
       0,     0,    33,     0,    66,     0,     0,    56,     0,    46,
      42,     0,    27,     0,    29,    22,     0,     0,     0,     0,
       0,    65,    59,    69,     0,     0,     0,    28,    23,     0,
      25,     0,     6,     0,    70,    58,    45,    41,    24,     7,
      71,     0,    72
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,     3,     8,    22,    23,    24,    25,    55,
      74,    26,    70,    71,    86,   184,   194
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -78
static const yytype_int16 yypact[] =
{
      -9,   -27,    18,    17,    11,   -78,    23,    17,   -78,    33,
      10,   -78,    54,    43,    73,    46,    44,   101,   -78,   -78,
      70,   -78,   156,   -78,   -14,   -78,    26,    67,   215,    74,
      88,   -78,   -78,     3,   -78,   -78,    76,    82,    87,   -78,
     441,     5,    92,   -78,   -78,   -78,   -78,    77,   -78,    12,
     -78,   142,   100,   -78,   107,   143,   167,   187,   257,   196,
     194,   207,   199,   437,   203,   214,    15,    71,    75,   274,
     375,   -78,   290,   101,   195,   217,   -78,   437,   437,   -78,
     -78,    50,   -78,   -78,   -78,   437,   138,   437,   437,   212,
     437,   437,   437,    71,   -78,    94,   437,   384,   437,   -78,
     437,   306,   393,   225,   101,   224,   108,   108,   238,   266,
     341,   437,   437,   437,   437,   437,   437,   -23,   437,   244,
     349,   357,   -78,   365,   146,   475,   -78,   154,   437,   162,
     197,   437,   402,   437,   -78,   253,   412,   247,   437,   -78,
     176,   235,   184,   184,   108,   108,   -78,   249,   488,   -78,
     412,   412,   254,   -78,   282,   250,   205,   261,   262,   213,
     437,   221,   -78,   103,   -78,   501,   424,   -78,   280,   -78,
     -78,   437,   -78,   268,   -78,   -78,   273,   256,   277,    98,
     278,   -78,   -78,    60,   265,   412,   264,   -78,   -78,   279,
     -78,   281,   -78,   437,   287,   -78,   -78,   -78,   -78,   -78,
     514,   437,   514
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -78,   -78,   -78,   -78,   313,   -26,   -10,    38,    47,   -78,
     -78,   -11,   -44,   -53,   -77,   -78,   -78
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
     106,   107,    40,    17,   146,     4,    29,     1,   110,   147,
     120,   121,    32,   123,   124,   125,    89,    99,     5,   127,
      17,   129,    17,   130,    95,    97,    34,    36,   102,    17,
      32,    13,    69,     6,   140,   141,   142,   143,   144,   145,
      56,   148,    99,    44,    99,    50,   101,    14,     9,    99,
      12,   156,    53,    90,   159,    10,   161,   132,    37,    32,
      33,   165,   103,   111,   112,    27,    41,   113,   114,   115,
     116,    35,    15,   117,   118,    16,    62,    91,    49,    99,
      35,    28,   108,   177,    30,    92,   109,    38,    35,   183,
      17,    32,   163,   135,   186,    62,    35,   168,   169,    64,
      65,    66,   193,    43,   179,    18,    42,    93,    19,    20,
      99,    52,    68,    21,    57,    94,   200,    45,    64,    65,
      66,   117,   118,    46,   202,    47,    93,    64,    65,    66,
      51,    68,   196,    18,   126,    93,    19,    20,   191,    76,
      68,   111,   112,   180,    58,   113,   114,   115,   116,   111,
     112,   117,   118,   113,   114,   115,   116,   111,   112,   117,
     118,   113,   114,   115,   116,   111,   112,   117,   118,   113,
     114,   115,   116,    17,    18,   117,   118,    19,    20,   119,
     112,    54,    59,   113,   114,   115,   116,   153,    18,   117,
     118,    19,    20,   115,   116,   155,    31,   117,   118,    60,
     111,   112,    61,   157,   113,   114,   115,   116,   111,   112,
     117,   118,   113,   114,   115,   116,   111,   112,   117,   118,
     113,   114,   115,   116,   111,   112,   117,   118,   113,   114,
     115,   116,    17,    72,   117,   118,    73,   104,   158,    75,
      76,    87,   113,   114,   115,   116,   173,    18,   117,   118,
      19,    20,    88,   122,   176,    39,   105,   134,    62,   111,
     112,   136,   178,   113,   114,   115,   116,   111,   112,   117,
     118,   113,   114,   115,   116,    62,   137,   117,   118,    63,
     138,    64,    65,    66,   149,   162,   164,   166,   171,    67,
     172,    62,    19,    20,    68,   170,    96,   189,    64,    65,
      66,   174,   175,   185,   195,   197,    67,    62,   187,    19,
      20,    68,   100,   188,    64,    65,    66,   190,   192,   198,
      11,   199,    67,     0,     0,    19,    20,    68,   131,   201,
      64,    65,    66,     0,     0,     0,     0,     0,    67,     0,
       0,    19,    20,    68,   111,   112,     0,     0,   113,   114,
     115,   116,   111,   112,   117,   118,   113,   114,   115,   116,
     111,   112,   117,   118,   113,   114,   115,   116,   111,   112,
     117,   118,   113,   114,   115,   116,    62,     0,   117,   118,
     139,     0,     0,     0,     0,    62,     0,     0,   150,     0,
       0,     0,     0,     0,    62,     0,   151,    98,     0,    64,
      65,    66,     0,    62,   152,     0,   128,    93,    64,    65,
      66,     0,    68,    62,     0,   133,    93,    64,    65,    66,
       0,    68,     0,     0,   160,    93,    64,    65,    66,     0,
      68,     0,    77,     0,    93,    78,    64,    65,    66,    68,
       0,     0,     0,     0,    93,    77,     0,     0,    78,    68,
       0,     0,    79,    80,    81,    82,    83,    84,    17,     0,
       0,     0,    85,   182,     0,    79,    80,    81,    82,    83,
      84,     0,     0,    18,     0,    85,    19,    20,   111,   112,
       0,    48,   113,   114,   115,   116,     0,     0,   117,   118,
     154,   111,   112,     0,     0,   113,   114,   115,   116,     0,
       0,   117,   118,   167,   111,   112,     0,     0,   113,   114,
     115,   116,     0,     0,   117,   118,   181,   111,   112,     0,
       0,   113,   114,   115,   116,     0,     0,   117,   118
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-78)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      77,    78,    28,    17,    27,    32,    17,    16,    85,    32,
      87,    88,    22,    90,    91,    92,     1,    70,     0,    96,
      17,    98,    17,   100,    68,    69,    40,     1,    72,    17,
      40,    21,    58,    16,   111,   112,   113,   114,   115,   116,
      51,   118,    95,    40,    97,    40,    72,    37,    37,   102,
      17,   128,    40,    38,   131,    32,   133,   101,    32,    69,
      22,   138,    73,     3,     4,    19,    28,     7,     8,     9,
      10,    24,    18,    13,    14,    32,     1,     6,    40,   132,
      33,    37,    32,   160,    14,    14,    36,    20,    41,   166,
      17,   101,   136,   104,   171,     1,    49,   150,   151,    24,
      25,    26,    42,    15,     1,    32,    32,    32,    35,    36,
     163,    34,    37,    40,    14,    40,   193,    41,    24,    25,
      26,    13,    14,    41,   201,    38,    32,    24,    25,    26,
      38,    37,   185,    32,    40,    32,    35,    36,    40,    41,
      37,     3,     4,    40,    37,     7,     8,     9,    10,     3,
       4,    13,    14,     7,     8,     9,    10,     3,     4,    13,
      14,     7,     8,     9,    10,     3,     4,    13,    14,     7,
       8,     9,    10,    17,    32,    13,    14,    35,    36,    41,
       4,    39,    39,     7,     8,     9,    10,    41,    32,    13,
      14,    35,    36,     9,    10,    41,    40,    13,    14,    32,
       3,     4,    15,    41,     7,     8,     9,    10,     3,     4,
      13,    14,     7,     8,     9,    10,     3,     4,    13,    14,
       7,     8,     9,    10,     3,     4,    13,    14,     7,     8,
       9,    10,    17,    37,    13,    14,    42,    42,    41,    32,
      41,    38,     7,     8,     9,    10,    41,    32,    13,    14,
      35,    36,    38,    41,    41,    40,    39,    32,     1,     3,
       4,    37,    41,     7,     8,     9,    10,     3,     4,    13,
      14,     7,     8,     9,    10,     1,    38,    13,    14,    22,
      14,    24,    25,    26,    40,    32,    39,    38,     6,    32,
      40,     1,    35,    36,    37,    41,    22,    41,    24,    25,
      26,    40,    40,    23,    39,    41,    32,     1,    40,    35,
      36,    37,    22,    40,    24,    25,    26,    40,    40,    40,
       7,    40,    32,    -1,    -1,    35,    36,    37,    22,    42,
      24,    25,    26,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    35,    36,    37,     3,     4,    -1,    -1,     7,     8,
       9,    10,     3,     4,    13,    14,     7,     8,     9,    10,
       3,     4,    13,    14,     7,     8,     9,    10,     3,     4,
      13,    14,     7,     8,     9,    10,     1,    -1,    13,    14,
      39,    -1,    -1,    -1,    -1,     1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    39,    22,    -1,    24,
      25,    26,    -1,     1,    39,    -1,    22,    32,    24,    25,
      26,    -1,    37,     1,    -1,    22,    32,    24,    25,    26,
      -1,    37,    -1,    -1,    22,    32,    24,    25,    26,    -1,
      37,    -1,     8,    -1,    32,    11,    24,    25,    26,    37,
      -1,    -1,    -1,    -1,    32,     8,    -1,    -1,    11,    37,
      -1,    -1,    28,    29,    30,    31,    32,    33,    17,    -1,
      -1,    -1,    38,    39,    -1,    28,    29,    30,    31,    32,
      33,    -1,    -1,    32,    -1,    38,    35,    36,     3,     4,
      -1,    40,     7,     8,     9,    10,    -1,    -1,    13,    14,
      15,     3,     4,    -1,    -1,     7,     8,     9,    10,    -1,
      -1,    13,    14,    15,     3,     4,    -1,    -1,     7,     8,
       9,    10,    -1,    -1,    13,    14,    15,     3,     4,    -1,
      -1,     7,     8,     9,    10,    -1,    -1,    13,    14
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    16,    44,    46,    32,     0,    16,    45,    47,    37,
      32,    47,    17,    21,    37,    18,    32,    17,    32,    35,
      36,    40,    48,    49,    50,    51,    54,    19,    37,    54,
      14,    40,    49,    50,    40,    51,     1,    32,    20,    40,
      48,    50,    32,    15,    40,    41,    41,    38,    40,    50,
      40,    38,    34,    40,    39,    52,    54,    14,    37,    39,
      32,    15,     1,    22,    24,    25,    26,    32,    37,    48,
      55,    56,    37,    42,    53,    32,    41,     8,    11,    28,
      29,    30,    31,    32,    33,    38,    57,    38,    38,     1,
      38,     6,    14,    32,    40,    55,    22,    55,    22,    56,
      22,    48,    55,    54,    42,    39,    57,    57,    32,    36,
      57,     3,     4,     7,     8,     9,    10,    13,    14,    41,
      57,    57,    41,    57,    57,    57,    40,    57,    22,    57,
      57,    22,    55,    22,    32,    54,    37,    38,    14,    39,
      57,    57,    57,    57,    57,    57,    27,    32,    57,    40,
      39,    39,    39,    41,    15,    41,    57,    41,    41,    57,
      22,    57,    32,    55,    39,    57,    38,    15,    56,    56,
      41,     6,    40,    41,    40,    40,    41,    57,    41,     1,
      40,    15,    39,    57,    58,    23,    57,    40,    40,    41,
      40,    40,    40,    42,    59,    39,    56,    41,    40,    40,
      57,    42,    57
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
      yyerror (root, hasError, YY_("syntax error: cannot back up")); \
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
		  Type, Value, Location, root, hasError); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, std::shared_ptr<CProgram>& root, int* hasError)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, root, hasError)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    std::shared_ptr<CProgram>& root;
    int* hasError;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (root);
  YYUSE (hasError);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, std::shared_ptr<CProgram>& root, int* hasError)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, root, hasError)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    std::shared_ptr<CProgram>& root;
    int* hasError;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, root, hasError);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, std::shared_ptr<CProgram>& root, int* hasError)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, root, hasError)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    std::shared_ptr<CProgram>& root;
    int* hasError;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , root, hasError);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, root, hasError); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, std::shared_ptr<CProgram>& root, int* hasError)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, root, hasError)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    std::shared_ptr<CProgram>& root;
    int* hasError;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (root);
  YYUSE (hasError);

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
yyparse (std::shared_ptr<CProgram>& root, int* hasError)
#else
int
yyparse (root, hasError)
    std::shared_ptr<CProgram>& root;
    int* hasError;
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
#line 126 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); root = make_shared<CProgram>( (yyvsp[(1) - (1)].mainClass), nullptr, location ); }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 127 "parser.y"
    { CLocation location( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); root = make_shared<CProgram>( (yyvsp[(1) - (2)].mainClass), (yyvsp[(2) - (2)].classDecls), location ); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 130 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.classDecls) = new CClassDeclList( 0, (yyvsp[(1) - (1)].classDecl), location ); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 131 "parser.y"
    { CLocation location( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.classDecls) = new CClassDeclList( (yyvsp[(1) - (2)].classDecls), (yyvsp[(2) - (2)].classDecl), location ); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 134 "parser.y"
    { CLocation location( (yylsp[(1) - (17)]).first_line, (yylsp[(1) - (17)]).first_column, (yylsp[(17) - (17)]).last_line, (yylsp[(17) - (17)]).last_column ); (yyval.mainClass) = new CMainClass( (yyvsp[(2) - (17)].sval), (yyvsp[(12) - (17)].sval), (yyvsp[(15) - (17)].statements), location ); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 135 "parser.y"
    { *hasError = 1; std::cout << "Syntax error : incorrect symbols in Main function from " << (yylsp[(16) - (18)]).first_line << ":" << (yylsp[(16) - (18)]).first_column << " to " << (yylsp[(16) - (18)]).last_line << ":" << (yylsp[(16) - (18)]).last_column << std::endl; }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 137 "parser.y"
    { CLocation location( (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column ); (yyval.classDecl) = new CClassDecl( (yyvsp[(2) - (4)].sval), 0, 0, "", location ); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 138 "parser.y"
    { CLocation location( (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column, (yylsp[(5) - (5)]).last_line, (yylsp[(5) - (5)]).last_column ); (yyval.classDecl) = new CClassDecl( (yyvsp[(2) - (5)].sval), (yyvsp[(4) - (5)].varDecls), 0, "", location ); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 139 "parser.y"
    { CLocation location( (yylsp[(1) - (6)]).first_line, (yylsp[(1) - (6)]).first_column, (yylsp[(6) - (6)]).last_line, (yylsp[(6) - (6)]).last_column ); (yyval.classDecl) = new CClassDecl( (yyvsp[(2) - (6)].sval), (yyvsp[(4) - (6)].varDecls), (yyvsp[(5) - (6)].methodDecls), "", location ); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 140 "parser.y"
    { CLocation location( (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column, (yylsp[(5) - (5)]).last_line, (yylsp[(5) - (5)]).last_column ); (yyval.classDecl) = new CClassDecl( (yyvsp[(2) - (5)].sval), 0, (yyvsp[(4) - (5)].methodDecls), "", location ); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 141 "parser.y"
    { CLocation location( (yylsp[(1) - (6)]).first_line, (yylsp[(1) - (6)]).first_column, (yylsp[(6) - (6)]).last_line, (yylsp[(6) - (6)]).last_column ); (yyval.classDecl) = new CClassDecl( (yyvsp[(2) - (6)].sval), 0, 0, (yyvsp[(4) - (6)].sval), location ); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 142 "parser.y"
    { CLocation location( (yylsp[(1) - (7)]).first_line, (yylsp[(1) - (7)]).first_column, (yylsp[(7) - (7)]).last_line, (yylsp[(7) - (7)]).last_column ); (yyval.classDecl) = new CClassDecl( (yyvsp[(2) - (7)].sval), (yyvsp[(6) - (7)].varDecls), 0, (yyvsp[(4) - (7)].sval), location ); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 143 "parser.y"
    { CLocation location( (yylsp[(1) - (8)]).first_line, (yylsp[(1) - (8)]).first_column, (yylsp[(8) - (8)]).last_line, (yylsp[(8) - (8)]).last_column ); (yyval.classDecl) = new CClassDecl( (yyvsp[(2) - (8)].sval), (yyvsp[(6) - (8)].varDecls), (yyvsp[(7) - (8)].methodDecls), (yyvsp[(4) - (8)].sval), location ); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 144 "parser.y"
    { CLocation location( (yylsp[(1) - (7)]).first_line, (yylsp[(1) - (7)]).first_column, (yylsp[(7) - (7)]).last_line, (yylsp[(7) - (7)]).last_column ); (yyval.classDecl) = new CClassDecl( (yyvsp[(2) - (7)].sval), 0, (yyvsp[(6) - (7)].methodDecls), (yyvsp[(4) - (7)].sval), location ); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 147 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.varDecls) = new CVarDeclList( 0, (yyvsp[(1) - (1)].varDecl), location ); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 148 "parser.y"
    { CLocation location( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.varDecls) = new CVarDeclList( (yyvsp[(1) - (2)].varDecls), (yyvsp[(2) - (2)].varDecl), location ); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 151 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.varDecl) = new CVarDecl( (yyvsp[(1) - (3)].type), (yyvsp[(2) - (3)].sval), location ); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 152 "parser.y"
    { *hasError = 1; std::cout << "Syntax error : incorrect variable definition from " << (yylsp[(2) - (3)]).first_line << ":" << (yylsp[(2) - (3)]).first_column << " to " << (yylsp[(2) - (3)]).last_line << ":" << (yylsp[(2) - (3)]).last_column << std::endl; }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 155 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.methodDecls) = new CMethodDeclList( 0, (yyvsp[(1) - (1)].methodDecl), location ); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 156 "parser.y"
    { CLocation location( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.methodDecls) = new CMethodDeclList( (yyvsp[(1) - (2)].methodDecls), (yyvsp[(2) - (2)].methodDecl), location ); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 159 "parser.y"
    { CLocation location( (yylsp[(1) - (11)]).first_line, (yylsp[(1) - (11)]).first_column, (yylsp[(11) - (11)]).last_line, (yylsp[(11) - (11)]).last_column ); (yyval.methodDecl) = new CMethodDecl( (yyvsp[(2) - (11)].type), (yyvsp[(3) - (11)].sval), (yyvsp[(5) - (11)].formalList), 0, 0, (yyvsp[(9) - (11)].exp), location ); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 160 "parser.y"
    { CLocation location( (yylsp[(1) - (12)]).first_line, (yylsp[(1) - (12)]).first_column, (yylsp[(12) - (12)]).last_line, (yylsp[(12) - (12)]).last_column ); (yyval.methodDecl) = new CMethodDecl( (yyvsp[(2) - (12)].type), (yyvsp[(3) - (12)].sval), (yyvsp[(5) - (12)].formalList), (yyvsp[(8) - (12)].varDecls), 0, (yyvsp[(10) - (12)].exp), location ); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 161 "parser.y"
    { CLocation location( (yylsp[(1) - (13)]).first_line, (yylsp[(1) - (13)]).first_column, (yylsp[(13) - (13)]).last_line, (yylsp[(13) - (13)]).last_column ); (yyval.methodDecl) = new CMethodDecl( (yyvsp[(2) - (13)].type), (yyvsp[(3) - (13)].sval), (yyvsp[(5) - (13)].formalList), (yyvsp[(8) - (13)].varDecls), (yyvsp[(9) - (13)].statements), (yyvsp[(11) - (13)].exp), location ); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 162 "parser.y"
    { CLocation location( (yylsp[(1) - (12)]).first_line, (yylsp[(1) - (12)]).first_column, (yylsp[(12) - (12)]).last_line, (yylsp[(12) - (12)]).last_column ); (yyval.methodDecl) = new CMethodDecl( (yyvsp[(2) - (12)].type), (yyvsp[(3) - (12)].sval), (yyvsp[(5) - (12)].formalList), 0, (yyvsp[(8) - (12)].statements), (yyvsp[(10) - (12)].exp), location ); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 163 "parser.y"
    { CLocation location( (yylsp[(1) - (10)]).first_line, (yylsp[(1) - (10)]).first_column, (yylsp[(10) - (10)]).last_line, (yylsp[(10) - (10)]).last_column ); (yyval.methodDecl) = new CMethodDecl( (yyvsp[(2) - (10)].type), (yyvsp[(3) - (10)].sval), 0, 0, 0, (yyvsp[(8) - (10)].exp), location ); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 164 "parser.y"
    { CLocation location( (yylsp[(1) - (11)]).first_line, (yylsp[(1) - (11)]).first_column, (yylsp[(11) - (11)]).last_line, (yylsp[(11) - (11)]).last_column ); (yyval.methodDecl) = new CMethodDecl( (yyvsp[(2) - (11)].type), (yyvsp[(3) - (11)].sval), 0, (yyvsp[(7) - (11)].varDecls), 0, (yyvsp[(9) - (11)].exp), location ); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 165 "parser.y"
    { CLocation location( (yylsp[(1) - (12)]).first_line, (yylsp[(1) - (12)]).first_column, (yylsp[(12) - (12)]).last_line, (yylsp[(12) - (12)]).last_column ); (yyval.methodDecl) = new CMethodDecl( (yyvsp[(2) - (12)].type), (yyvsp[(3) - (12)].sval), 0, (yyvsp[(7) - (12)].varDecls), (yyvsp[(8) - (12)].statements), (yyvsp[(10) - (12)].exp), location ); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 166 "parser.y"
    { CLocation location( (yylsp[(1) - (11)]).first_line, (yylsp[(1) - (11)]).first_column, (yylsp[(11) - (11)]).last_line, (yylsp[(11) - (11)]).last_column ); (yyval.methodDecl) = new CMethodDecl( (yyvsp[(2) - (11)].type), (yyvsp[(3) - (11)].sval), 0, 0, (yyvsp[(7) - (11)].statements), (yyvsp[(9) - (11)].exp), location ); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 169 "parser.y"
    { CLocation location( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.formalList) = new CFormalList( 0, (yyvsp[(1) - (2)].type), (yyvsp[(2) - (2)].sval), location ); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 170 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.formalList) = new CFormalList( (yyvsp[(3) - (3)].formalList), (yyvsp[(1) - (3)].type), (yyvsp[(2) - (3)].sval), location ); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 173 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.formalList) = new CFormalList( 0, (yyvsp[(2) - (3)].type), (yyvsp[(3) - (3)].sval), location ); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 174 "parser.y"
    { CLocation location( (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column ); (yyval.formalList) = new CFormalList( (yyvsp[(1) - (4)].formalList), (yyvsp[(3) - (4)].type), (yyvsp[(4) - (4)].sval), location ); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 177 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.type) = new CType( "int", location ); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 178 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.type) = new CType( "int[]", location ); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 179 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.type) = new CType( "boolean", location ); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 180 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.type) = new CType( (yyvsp[(1) - (1)].sval), location ); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 183 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.statements) = new CStatementList( 0, (yyvsp[(1) - (1)].statement), location ); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 184 "parser.y"
    { CLocation location( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.statements) = new CStatementList( (yyvsp[(1) - (2)].statements), (yyvsp[(2) - (2)].statement), location ); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 187 "parser.y"
    { CLocation location( (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column ); (yyval.statement) = new CAssignStatement( (yyvsp[(1) - (4)].sval), 0, (yyvsp[(3) - (4)].exp), location ); }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 188 "parser.y"
    { CLocation location( (yylsp[(1) - (7)]).first_line, (yylsp[(1) - (7)]).first_column, (yylsp[(7) - (7)]).last_line, (yylsp[(7) - (7)]).last_column ); (yyval.statement) = new CAssignStatement( (yyvsp[(1) - (7)].sval), (yyvsp[(3) - (7)].exp), (yyvsp[(6) - (7)].exp), location ); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 189 "parser.y"
    { CLocation location( (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column, (yylsp[(5) - (5)]).last_line, (yylsp[(5) - (5)]).last_column ); (yyval.statement) = new CPrintStatement( (yyvsp[(3) - (5)].exp), location ); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 190 "parser.y"
    { CLocation location( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.statement) = new CCurlyBraceStatement( 0, location ); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 191 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.statement) = new CCurlyBraceStatement( (yyvsp[(2) - (3)].statements), location ); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 192 "parser.y"
    { CLocation location( (yylsp[(1) - (7)]).first_line, (yylsp[(1) - (7)]).first_column, (yylsp[(7) - (7)]).last_line, (yylsp[(7) - (7)]).last_column ); (yyval.statement) = new CIfStatement( (yyvsp[(3) - (7)].exp), (yyvsp[(5) - (7)].statement), (yyvsp[(7) - (7)].statement), location ); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 193 "parser.y"
    { CLocation location( (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column, (yylsp[(5) - (5)]).last_line, (yylsp[(5) - (5)]).last_column ); (yyval.statement) = new CWhileStatement( (yyvsp[(3) - (5)].exp), (yyvsp[(5) - (5)].statement), location ); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 194 "parser.y"
    { *hasError = 1; std::cout << "Syntax error : incorrect statement from " << (yylsp[(1) - (2)]).first_line << ":" << (yylsp[(1) - (2)]).first_column << " to " << (yylsp[(1) - (2)]).last_line << ":" << (yylsp[(1) - (2)]).last_column << std::endl; }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 195 "parser.y"
    { *hasError = 1; std::cout << "Syntax error : incorrect Println-statement from " << (yylsp[(2) - (3)]).first_line << ":" << (yylsp[(2) - (3)]).first_column << " to " << (yylsp[(2) - (3)]).last_line << ":" << (yylsp[(2) - (3)]).last_column << std::endl; }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 199 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.exp) = new CExpBinOpExp( (yyvsp[(1) - (3)].exp), '*', (yyvsp[(3) - (3)].exp), location ); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 200 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.exp) = new CExpBinOpExp( (yyvsp[(1) - (3)].exp), '+', (yyvsp[(3) - (3)].exp), location ); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 201 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.exp) = new CExpBinOpExp( (yyvsp[(1) - (3)].exp), '/', (yyvsp[(3) - (3)].exp), location ); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 202 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.exp) = new CExpBinOpExp( (yyvsp[(1) - (3)].exp), '-', (yyvsp[(3) - (3)].exp), location ); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 203 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.exp) = new CExpBinOpExp( (yyvsp[(1) - (3)].exp), '<', (yyvsp[(3) - (3)].exp), location ); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 204 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.exp) = new CExpBinOpExp( (yyvsp[(1) - (3)].exp), '&', (yyvsp[(3) - (3)].exp), location ); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 205 "parser.y"
    { CLocation location( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.exp) = new CUnMinExp( (yyvsp[(2) - (2)].exp), location ); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 206 "parser.y"
    { CLocation location( (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column ); (yyval.exp) = new CExpWithIndex( (yyvsp[(1) - (4)].exp), (yyvsp[(3) - (4)].exp), location ); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 207 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.exp) = new CExpDotLength( (yyvsp[(1) - (3)].exp), location ); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 208 "parser.y"
    { CLocation location( (yylsp[(1) - (6)]).first_line, (yylsp[(1) - (6)]).first_column, (yylsp[(6) - (6)]).last_line, (yylsp[(6) - (6)]).last_column ); (yyval.exp) = new CExpIdExpList( (yyvsp[(1) - (6)].exp), (yyvsp[(3) - (6)].sval), (yyvsp[(5) - (6)].expList), location ); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 209 "parser.y"
    { CLocation location( (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column, (yylsp[(5) - (5)]).last_line, (yylsp[(5) - (5)]).last_column ); (yyval.exp) = new CExpIdVoidExpList( (yyvsp[(1) - (5)].exp), (yyvsp[(3) - (5)].sval), location ) ; }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 210 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.exp) = new CIntegerLiteral( (yyvsp[(1) - (1)].ival), location ); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 211 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.exp) = new CTrue( location ); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 212 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.exp) = new CFalse( location ); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 213 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.exp) = new CId( (yyvsp[(1) - (1)].sval), location ); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 214 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.exp) = new CThis( location ); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 215 "parser.y"
    { CLocation location( (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column, (yylsp[(5) - (5)]).last_line, (yylsp[(5) - (5)]).last_column ); (yyval.exp) = new CNewIntExpIndex( (yyvsp[(4) - (5)].exp), location ); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 216 "parser.y"
    { CLocation location( (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column ); (yyval.exp) = new CNewId( (yyvsp[(2) - (4)].sval), location ); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 217 "parser.y"
    { CLocation location( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.exp) = new CNotExp( (yyvsp[(2) - (2)].exp), location ); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 218 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.exp) = new CExpInBrackets( (yyvsp[(2) - (3)].exp), location ); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 221 "parser.y"
    { CLocation location( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.expList) = new CExpList( 0, (yyvsp[(1) - (1)].exp), location ); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 222 "parser.y"
    { CLocation location( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.expList) = new CExpList( (yyvsp[(2) - (2)].expList), (yyvsp[(1) - (2)].exp), location ); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 225 "parser.y"
    { CLocation location( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.expList) = new CExpList( 0, (yyvsp[(2) - (2)].exp), location ); }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 226 "parser.y"
    { CLocation location( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.expList) = new CExpList( (yyvsp[(1) - (3)].expList), (yyvsp[(3) - (3)].exp), location ); }
    break;


/* Line 1792 of yacc.c  */
#line 2195 "parser.tab.cpp"
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
      yyerror (root, hasError, YY_("syntax error"));
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
        yyerror (root, hasError, yymsgp);
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
		      yytoken, &yylval, &yylloc, root, hasError);
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
		  yystos[yystate], yyvsp, yylsp, root, hasError);
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
  yyerror (root, hasError, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, root, hasError);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, root, hasError);
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
#line 229 "parser.y"


void yyerror( std::shared_ptr<CProgram>&, int*, const char* str )
{
	std::cout << str << std::endl;
}