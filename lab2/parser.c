/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.bison" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "expr.h"
#include "decl.h"
#include "type.h"
#include "stmt.h"
#include "symbol.h"
#include "param_list.h"


extern char *yytext;
extern int yylex();
int yyerror( char *str);

struct decl * decl_create( char *name,struct type *type,struct expr *value,struct stmt *code,struct decl *next )
{
    struct decl *e = malloc(sizeof(*e));
    e->name = name;
    e->type = type;
    e->value = value;
    e->code = code;
    e->next = next;
    return e;
}

struct expr * expr_create_integer_literal(int literal_value){
	struct expr *e = malloc(sizeof(*e));
	e->kind=EXPR_INTEGER_LITERAL;
	e->literal_value=literal_value;
	return e;
}

struct expr * expr_create_boolean_literal( int c ){
    
    struct expr *e = malloc(sizeof(*e));
    e->kind=EXPR_BOOLEAN_LITERAL;
    e->literal_value=c;
    return e;
}

struct expr * expr_create_char_literal( char c ){
    struct expr *e = malloc(sizeof(*e));
    e->kind=EXPR_CHAR_LITERAL;
    e->literal_value=c;
    return e;
}
struct expr * expr_create_string_literal( const char *str ){
    struct expr *e = malloc(sizeof(*e));
    e->kind=EXPR_STRING_LITERAL;
    char * newStr = malloc(sizeof(str)-1);
    memcpy(newStr,str+1, strlen(str)-2);
    newStr[strlen(newStr)]='\0';
    e->string_literal=newStr;
    return e;
}

struct expr * expr_create_name( const char *n ) {
    struct expr *d = malloc(sizeof(*d));
	d->kind = EXPR_NAME;
    d->name = n;
	return d;
}

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right )
{
	struct expr *d = malloc(sizeof(*d));
	d->kind = kind;
	d->left = left;
	d->right = right;
	return d;
}

struct type * type_create( type_t kind, struct type *subtype, struct param_list *params )
{
    struct type *t = malloc(sizeof(*t));
    t->kind=kind;
    t->subtype=subtype;
    t->params=params;
    return t;
}

struct stmt * stmt_create( stmt_t kind, struct decl *decl, struct expr *init_expr, struct expr *expr, struct expr *next_expr, struct stmt *body, struct stmt *else_body, struct stmt *next ){
    struct stmt *s = malloc(sizeof(*s));
    s->kind=kind;
    s->decl=decl;
    s->init_expr=init_expr;
    s->expr=expr;
    s->next_expr=next_expr;
    s->body=body;
    s->else_body=else_body;
    s->next=next;
    return s;
}

struct param_list * param_list_create( char *name, struct type *type, struct param_list *next ){
    struct param_list *p = malloc(sizeof(*p));
    p->name=name;
    p->type=type;
    p->next=next;
    return p;
}
struct param_list * param_list_copy(struct param_list *l) {

  if (l == NULL) return NULL;

  struct param_list *head = param_list_create(l->name, type_copy(l->type), NULL);
  struct param_list *curr = head;

  while (l->next != NULL) {
    l = l->next;
    curr->next = param_list_create(l->name, type_copy(l->type), NULL);
    curr = curr->next;
  }

  return head;
}
void param_list_delete(struct param_list *l) {

  if (l == NULL) return;

  type_delete(l->type);
  param_list_delete(l->next);
  free(l);
}


struct decl* parser_result;

#line 198 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "token.h".  */
#ifndef YY_YY_TOKEN_H_INCLUDED
# define YY_YY_TOKEN_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_INTEGER_LITERAL = 258,
    TOKEN_ADD = 259,
    TOKEN_SUBTRACT = 260,
    TOKEN_MULTIPLY = 261,
    TOKEN_DIVIDE = 262,
    TOKEN_MODULO = 263,
    TOKEN_EXPONENT = 264,
    TOKEN_NOT = 265,
    TOKEN_INCREMENT = 266,
    TOKEN_DECREMENT = 267,
    TOKEN_WHILE = 268,
    TOKEN_FOR = 269,
    TOKEN_CHAR = 270,
    TOKEN_BOOLEAN = 271,
    TOKEN_STRING = 272,
    TOKEN_INTEGER = 273,
    TOKEN_VOID = 274,
    TOKEN_TRUE = 275,
    TOKEN_FALSE = 276,
    TOKEN_ARRAY = 277,
    TOKEN_PRINT = 278,
    TOKEN_IF = 279,
    TOKEN_ELSE = 280,
    TOKEN_FUNCTION = 281,
    TOKEN_RETURN = 282,
    TOKEN_IDENT = 283,
    TOKEN_CHAR_LITERAL = 284,
    TOKEN_STRING_LITERAL = 285,
    TOKEN_EQ = 286,
    TOKEN_NE = 287,
    TOKEN_GE = 288,
    TOKEN_LE = 289,
    TOKEN_ASSIGNMENT = 290,
    TOKEN_GT = 291,
    TOKEN_LT = 292,
    TOKEN_COMMA = 293,
    TOKEN_COLON = 294,
    TOKEN_AND = 295,
    TOKEN_OR = 296,
    TOKEN_LB = 297,
    TOKEN_RB = 298,
    TOKEN_CLB = 299,
    TOKEN_CRB = 300,
    TOKEN_SLB = 301,
    TOKEN_SRB = 302,
    TOKEN_ERROR = 303,
    TOKEN_SEMICOLON = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 181 "parser.bison" /* yacc.c:355  */

struct decl *decl;
struct type *type;
struct stmt *stmt;
struct expr *expr;
struct param_list *param_list;
char *name;
int num;

#line 298 "parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOKEN_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 315 "parser.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   353

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   204,   204,   207,   208,   211,   212,   213,   214,   215,
     216,   219,   220,   223,   224,   227,   228,   229,   230,   231,
     232,   233,   234,   237,   238,   243,   245,   246,   248,   249,
     252,   254,   255,   258,   259,   262,   265,   269,   270,   273,
     274,   275,   278,   281,   282,   283,   284,   285,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   306,   307,   309,   310,   313,   316,
     317,   319,   320,   321,   322,   323,   325,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   339,   341,   342
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_INTEGER_LITERAL", "TOKEN_ADD",
  "TOKEN_SUBTRACT", "TOKEN_MULTIPLY", "TOKEN_DIVIDE", "TOKEN_MODULO",
  "TOKEN_EXPONENT", "TOKEN_NOT", "TOKEN_INCREMENT", "TOKEN_DECREMENT",
  "TOKEN_WHILE", "TOKEN_FOR", "TOKEN_CHAR", "TOKEN_BOOLEAN",
  "TOKEN_STRING", "TOKEN_INTEGER", "TOKEN_VOID", "TOKEN_TRUE",
  "TOKEN_FALSE", "TOKEN_ARRAY", "TOKEN_PRINT", "TOKEN_IF", "TOKEN_ELSE",
  "TOKEN_FUNCTION", "TOKEN_RETURN", "TOKEN_IDENT", "TOKEN_CHAR_LITERAL",
  "TOKEN_STRING_LITERAL", "TOKEN_EQ", "TOKEN_NE", "TOKEN_GE", "TOKEN_LE",
  "TOKEN_ASSIGNMENT", "TOKEN_GT", "TOKEN_LT", "TOKEN_COMMA", "TOKEN_COLON",
  "TOKEN_AND", "TOKEN_OR", "TOKEN_LB", "TOKEN_RB", "TOKEN_CLB",
  "TOKEN_CRB", "TOKEN_SLB", "TOKEN_SRB", "TOKEN_ERROR", "TOKEN_SEMICOLON",
  "$accept", "program", "decl_list", "decl", "stmt_list", "stmt",
  "matched_stmt", "unmatched_stmt", "for", "assign_or_empty",
  "expr_or_empty", "assign", "param_list", "non_empty_param_list",
  "empty_param_list", "param", "type_array", "type_array_smaller",
  "type_func", "type", "expr", "args", "non_empty_args", "arg", "alpha",
  "term", "factor_bigger", "factor_smaller", "subscript",
  "can_be_empty_subscript", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF -148

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-148)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -12,   -35,    21,  -148,   -12,   130,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,    -6,   196,   -30,   -19,   -24,    77,  -148,
     -14,  -148,    27,   245,  -148,  -148,   273,  -148,  -148,     6,
    -148,  -148,   245,    59,  -148,    22,  -148,   245,    31,    28,
    -148,  -148,    41,   273,   273,   273,    13,   186,    20,  -148,
    -148,   245,   245,   227,    44,  -148,  -148,    59,   302,    42,
    -148,    53,    59,   -22,    27,  -148,  -148,  -148,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,  -148,   273,
     273,   273,   273,  -148,  -148,    51,   126,  -148,   108,  -148,
      47,   245,  -148,    55,  -148,  -148,   186,  -148,   186,   186,
     186,   186,   186,   186,   186,   186,   186,  -148,  -148,  -148,
    -148,  -148,    57,    59,    61,  -148,  -148,   177,   245,  -148,
    -148,    59,    62,   245,    67,   245,    19,   177,  -148,    65,
     177,  -148,  -148,  -148,    63,     2,   138,  -148,   245,    69,
     245,    52,    71,  -148,  -148,  -148,   245,  -148,    57,    72,
    -148,   291,  -148,   248,  -148,  -148,   302,  -148,   245,   177,
      73,   302,  -148,    89,   245,   177,    82,  -148,  -148,   177,
    -148
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     2,     4,     0,     1,     3,    46,    45,
      47,    44,    43,     0,     0,     0,     0,     0,     0,    42,
       0,     9,    35,     0,     5,    79,     0,    84,    85,    80,
      70,    69,     0,     0,    83,     0,    82,    65,     0,     0,
      32,    31,    33,     0,     0,     0,     0,    63,    75,    76,
      78,    65,     0,     0,     0,    37,    41,     0,    68,     0,
      64,    66,     0,     0,     0,    58,    59,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,     0,
       0,     0,     0,    60,    62,     0,     0,    77,     0,    38,
       0,    65,    36,     0,     8,    34,    48,    75,    49,    50,
      51,    54,    55,    52,    53,    56,    57,    71,    72,    73,
      74,    81,    88,     0,     0,    10,    67,    12,     0,    86,
      39,     0,     0,    65,     0,     0,    80,    12,    15,     0,
      12,    14,    13,    20,     0,     0,     0,    40,    27,     0,
       0,     0,     0,     7,    11,    17,     0,    16,    88,     0,
      26,     0,    21,     0,    18,    19,    30,    87,    29,     0,
       0,    28,    23,    14,    29,     0,     0,    22,    24,     0,
      25
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -148,  -148,   116,    60,   -64,  -147,  -139,   -39,  -148,  -148,
     -37,    -5,  -148,    68,  -148,  -148,  -148,   -54,  -148,    10,
     -23,   -50,  -148,  -148,  -148,   276,   165,   -16,  -148,    -9
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,   128,   129,   130,   131,   132,   133,   149,
     160,   134,    39,    40,    41,    42,    15,    55,    16,    56,
     135,    59,    60,    61,    34,    47,    48,    49,    36,   119
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      46,    85,    35,    89,     5,    20,    68,    69,    92,    53,
      50,    23,   162,    93,    58,    17,     1,    68,    69,    21,
     163,     6,   170,    22,    19,    24,   167,    94,    58,    86,
      37,    83,    84,    70,    71,    72,    73,   146,    74,    75,
      18,   116,    76,    77,    70,    71,    72,    73,    51,    74,
      75,   147,    52,    76,    77,    38,    68,    69,     5,   120,
       4,    51,    78,   142,     4,    52,   144,   137,    58,    57,
      62,    63,   114,   139,     8,     9,    10,    11,    12,    64,
      25,    54,    26,    70,    71,    72,    73,    90,    74,    75,
      88,    91,    76,    77,   111,   136,   115,    27,    28,   117,
      58,   154,   141,   118,   138,    29,    30,    31,   121,   140,
     143,    25,   145,    26,   165,   151,   155,   153,   152,    32,
       7,   158,   164,   156,    33,   169,   168,   166,    27,    28,
      68,    69,    95,   150,     0,   161,    29,    30,    31,   157,
       0,   161,    68,    69,     0,     8,     9,    10,    11,    12,
      32,     0,    13,     0,     0,   113,    14,    70,    71,    72,
      73,     0,    74,    75,     0,     0,    76,    77,     0,    70,
      71,    72,    73,   112,    74,    75,     0,     0,    76,    77,
      25,     0,    26,     0,     0,   148,     0,    43,    44,    45,
       0,   122,    79,    80,    81,    82,     0,    27,    28,     0,
     123,   124,     0,     0,   125,   126,    30,    31,    65,    66,
      67,     8,     9,    10,    11,    12,     0,     0,     0,    32,
       0,   127,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    68,    69,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,     0,   107,   108,   109,   110,    25,     0,
      26,     0,    68,    69,     0,    43,    44,    45,    70,    71,
      72,    73,     0,    74,    75,    27,    28,    76,    77,     0,
      87,     0,     0,    29,    30,    31,    25,     0,    26,    70,
      71,    72,    73,     0,    74,    75,     0,    32,    76,    77,
       0,   159,     0,    27,    28,    68,    69,     0,     0,     0,
       0,    29,    30,    31,     0,     0,    68,    69,     0,     0,
       0,     0,     0,     0,     0,    32,     0,     0,     0,     0,
       0,     0,    70,    71,    72,    73,   146,    74,    75,     0,
       0,    76,    77,    70,    71,    72,    73,     0,    74,    75,
       0,     0,    76,    77,    96,    98,    99,   100,   101,   102,
     103,   104,   105,   106
};

static const yytype_int16 yycheck[] =
{
      23,    51,    18,    57,    39,    35,     4,     5,    62,    32,
      26,    35,   159,    35,    37,     5,    28,     4,     5,    49,
     159,     0,   169,    42,    14,    49,   165,    49,    51,    52,
      44,    11,    12,    31,    32,    33,    34,    35,    36,    37,
      46,    91,    40,    41,    31,    32,    33,    34,    42,    36,
      37,    49,    46,    40,    41,    28,     4,     5,    39,   113,
       0,    42,    49,   127,     4,    46,   130,   121,    91,    47,
      39,    43,    88,   123,    15,    16,    17,    18,    19,    38,
       3,    22,     5,    31,    32,    33,    34,    45,    36,    37,
      46,    38,    40,    41,    43,   118,    49,    20,    21,    44,
     123,    49,   125,    46,    42,    28,    29,    30,    47,    42,
      45,     3,    49,     5,    25,   138,    45,   140,    49,    42,
       4,    49,    49,   146,    47,    43,   165,   164,    20,    21,
       4,     5,    64,   138,    -1,   158,    28,    29,    30,   148,
      -1,   164,     4,     5,    -1,    15,    16,    17,    18,    19,
      42,    -1,    22,    -1,    -1,    47,    26,    31,    32,    33,
      34,    -1,    36,    37,    -1,    -1,    40,    41,    -1,    31,
      32,    33,    34,    47,    36,    37,    -1,    -1,    40,    41,
       3,    -1,     5,    -1,    -1,    47,    -1,    10,    11,    12,
      -1,    14,     6,     7,     8,     9,    -1,    20,    21,    -1,
      23,    24,    -1,    -1,    27,    28,    29,    30,    43,    44,
      45,    15,    16,    17,    18,    19,    -1,    -1,    -1,    42,
      -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     4,     5,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    79,    80,    81,    82,     3,    -1,
       5,    -1,     4,     5,    -1,    10,    11,    12,    31,    32,
      33,    34,    -1,    36,    37,    20,    21,    40,    41,    -1,
      43,    -1,    -1,    28,    29,    30,     3,    -1,     5,    31,
      32,    33,    34,    -1,    36,    37,    -1,    42,    40,    41,
      -1,    43,    -1,    20,    21,     4,     5,    -1,    -1,    -1,
      -1,    28,    29,    30,    -1,    -1,     4,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    40,    41,    31,    32,    33,    34,    -1,    36,    37,
      -1,    -1,    40,    41,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    51,    52,    53,    39,     0,    52,    15,    16,
      17,    18,    19,    22,    26,    66,    68,    69,    46,    69,
      35,    49,    42,    35,    49,     3,     5,    20,    21,    28,
      29,    30,    42,    47,    74,    77,    78,    44,    28,    62,
      63,    64,    65,    10,    11,    12,    70,    75,    76,    77,
      77,    42,    46,    70,    22,    67,    69,    47,    70,    71,
      72,    73,    39,    43,    38,    76,    76,    76,     4,     5,
      31,    32,    33,    34,    36,    37,    40,    41,    49,     6,
       7,     8,     9,    11,    12,    71,    70,    43,    46,    67,
      45,    38,    67,    35,    49,    63,    75,    76,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    76,    76,    76,
      76,    43,    47,    47,    77,    49,    71,    44,    46,    79,
      67,    47,    14,    23,    24,    27,    28,    44,    53,    54,
      55,    56,    57,    58,    61,    70,    70,    67,    42,    71,
      42,    70,    54,    45,    54,    49,    35,    49,    47,    59,
      61,    70,    49,    70,    49,    45,    70,    79,    49,    43,
      60,    70,    55,    56,    49,    25,    60,    56,    57,    43,
      55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    54,    54,    55,    55,    56,    56,    56,    56,    56,
      56,    56,    56,    57,    57,    58,    59,    59,    60,    60,
      61,    62,    62,    63,    63,    64,    65,    66,    66,    67,
      67,    67,    68,    69,    69,    69,    69,    69,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    72,    72,    73,    74,
      74,    75,    75,    75,    75,    75,    76,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    78,    79,    79
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     4,     6,    10,     7,     4,
       8,     2,     0,     1,     1,     1,     2,     2,     3,     3,
       1,     3,     7,     5,     7,     9,     1,     0,     1,     0,
       3,     1,     1,     1,     3,     0,     3,     4,     5,     4,
       5,     1,     2,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     2,     1,     1,     0,     1,     3,     1,     1,
       1,     3,     3,     3,     3,     1,     1,     3,     2,     1,
       1,     4,     1,     1,     1,     1,     5,     4,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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
        case 2:
#line 204 "parser.bison" /* yacc.c:1646  */
    {parser_result=(yyvsp[0].decl);printf("\nparsing tree\n");decl_print((yyvsp[0].decl));printf("\ndone printing tree\n");}
#line 1554 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 207 "parser.bison" /* yacc.c:1646  */
    { (yyval.decl) = (yyvsp[-1].decl); (yyvsp[-1].decl)->next = (yyvsp[0].decl); }
#line 1560 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 208 "parser.bison" /* yacc.c:1646  */
    { printf("epsilon decl list\n");(yyval.decl) = 0; }
#line 1566 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 211 "parser.bison" /* yacc.c:1646  */
    { (yyval.decl) = decl_create((yyvsp[-3].name),(yyvsp[-1].type),0,0,0); printf("decl creat name is %s\n", (yyval.decl)->name); }
#line 1572 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 212 "parser.bison" /* yacc.c:1646  */
    { (yyval.decl) = decl_create((yyvsp[-5].name),(yyvsp[-3].type),(yyvsp[-1].expr),0,0);}
#line 1578 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 213 "parser.bison" /* yacc.c:1646  */
    {(yyvsp[-7].type)->params=(yyvsp[-5].param_list);(yyval.decl) =decl_create((yyvsp[-9].name),(yyvsp[-7].type),0,(yyvsp[-1].stmt),0);}
#line 1584 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 214 "parser.bison" /* yacc.c:1646  */
    {(yyvsp[-4].type)->params=(yyvsp[-2].param_list);(yyval.decl) =decl_create((yyvsp[-6].name),(yyvsp[-4].type),0,0,0);}
#line 1590 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 215 "parser.bison" /* yacc.c:1646  */
    {(yyval.decl) = decl_create((yyvsp[-3].name),(yyvsp[-1].type),0,0,0);}
#line 1596 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 216 "parser.bison" /* yacc.c:1646  */
    {(yyval.decl) = decl_create((yyvsp[-7].name),(yyvsp[-5].type),(yyvsp[-2].expr),0,0);}
#line 1602 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 219 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[-1].stmt);(yyvsp[-1].stmt)->next=(yyvsp[0].stmt);}
#line 1608 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 220 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt)=0;}
#line 1614 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 223 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].stmt);}
#line 1620 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 224 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].stmt);}
#line 1626 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 227 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt)=stmt_create(STMT_DECL,(yyvsp[0].decl),0,0,0,0,0,0 );}
#line 1632 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 228 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt)=stmt_create(STMT_EXPR,0, 0,(yyvsp[-1].expr),0,0,0,0);}
#line 1638 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 229 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt)=stmt_create(STMT_EXPR,0,0,(yyvsp[-1].expr),0,0,0,0);}
#line 1644 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 230 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt) = stmt_create(STMT_RETURN, 0,0, (yyvsp[-1].expr),0,0,0,0);}
#line 1650 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 231 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt)=stmt_create(STMT_BLOCK,0,0,0,0,(yyvsp[-1].stmt),0,0);}
#line 1656 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 232 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].stmt);}
#line 1662 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 233 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt) = stmt_create(STMT_PRINT, 0,0,(yyvsp[-1].expr),0,0,0,0);}
#line 1668 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 234 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt) = stmt_create(STMT_IF_ELSE,0,0,(yyvsp[-4].expr),0,(yyvsp[-2].stmt),(yyvsp[0].stmt),0);}
#line 1674 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 237 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt) = stmt_create(STMT_IF,0,0,(yyvsp[-2].expr),0,(yyvsp[0].stmt),0,0);}
#line 1680 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 238 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt) = stmt_create(STMT_IF_ELSE,0,0,(yyvsp[-4].expr),0,(yyvsp[-2].stmt),(yyvsp[0].stmt),0);}
#line 1686 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 243 "parser.bison" /* yacc.c:1646  */
    {(yyval.stmt)=stmt_create(STMT_FOR,0,(yyvsp[-6].expr),(yyvsp[-4].expr),(yyvsp[-2].expr),(yyvsp[0].stmt),0,0);}
#line 1692 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 245 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 1698 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 246 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=0;}
#line 1704 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 248 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 1710 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 249 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=0;}
#line 1716 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 252 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr) = expr_create(EXPR_ASSIGN,  (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1722 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 254 "parser.bison" /* yacc.c:1646  */
    {(yyval.param_list)=(yyvsp[0].param_list);}
#line 1728 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 255 "parser.bison" /* yacc.c:1646  */
    {(yyval.param_list)=(yyvsp[0].param_list);}
#line 1734 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 258 "parser.bison" /* yacc.c:1646  */
    {(yyval.param_list) = (yyvsp[0].param_list);}
#line 1740 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 259 "parser.bison" /* yacc.c:1646  */
    {(yyval.param_list) = (yyvsp[-2].param_list); (yyvsp[-2].param_list)->next=(yyvsp[0].param_list);}
#line 1746 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 262 "parser.bison" /* yacc.c:1646  */
    {(yyval.param_list)=0;}
#line 1752 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 265 "parser.bison" /* yacc.c:1646  */
    {(yyval.param_list)=param_list_create((yyvsp[-2].name),(yyvsp[0].type), 0);}
#line 1758 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 269 "parser.bison" /* yacc.c:1646  */
    {(yyval.type)=type_create(TYPE_ARRAY, (yyvsp[0].type),0);}
#line 1764 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 270 "parser.bison" /* yacc.c:1646  */
    {(yyval.type)=type_create(TYPE_ARRAY, (yyvsp[0].type),0);(yyval.type)->array_size=(yyvsp[-2].expr)->literal_value;}
#line 1770 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 273 "parser.bison" /* yacc.c:1646  */
    {(yyval.type)=type_create(TYPE_ARRAY, (yyvsp[0].type),0);}
#line 1776 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 274 "parser.bison" /* yacc.c:1646  */
    {(yyval.type)=type_create(TYPE_ARRAY, (yyvsp[0].type),0);(yyval.type)->array_size=(yyvsp[-2].expr)->literal_value;}
#line 1782 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 275 "parser.bison" /* yacc.c:1646  */
    {(yyval.type)=(yyvsp[0].type);}
#line 1788 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 278 "parser.bison" /* yacc.c:1646  */
    {(yyval.type)= type_create(TYPE_FUNCTION,(yyvsp[0].type),0);}
#line 1794 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 281 "parser.bison" /* yacc.c:1646  */
    {(yyval.type) = type_create(TYPE_VOID,  0,0);}
#line 1800 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 282 "parser.bison" /* yacc.c:1646  */
    {(yyval.type) = type_create(TYPE_INTEGER,  0,0); printf("integer\n");}
#line 1806 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 283 "parser.bison" /* yacc.c:1646  */
    {(yyval.type) = type_create(TYPE_BOOLEAN,  0,0);}
#line 1812 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 284 "parser.bison" /* yacc.c:1646  */
    {(yyval.type) = type_create(TYPE_CHARACTER,  0,0);}
#line 1818 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 285 "parser.bison" /* yacc.c:1646  */
    {(yyval.type) = type_create(TYPE_STRING,  0,0);}
#line 1824 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 288 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_ADD,(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1830 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 289 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_SUB,(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1836 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 290 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_EQ,(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1842 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 291 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_NEQ,(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1848 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 292 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_GT,(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1854 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 293 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_LT,(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1860 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 294 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_GTE,(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1866 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 295 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_LTE,(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1872 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 296 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr) = expr_create(EXPR_AND,(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1878 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 297 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr) = expr_create(EXPR_OR,(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1884 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 298 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create(EXPR_NOT,(yyvsp[0].expr),0);}
#line 1890 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 299 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create(EXPR_INCR,(yyvsp[0].expr),0);}
#line 1896 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 300 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create(EXPR_INCR,(yyvsp[-1].expr),0);}
#line 1902 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 301 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create(EXPR_DECR,(yyvsp[0].expr),0);}
#line 1908 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 302 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create(EXPR_DECR,(yyvsp[-1].expr),0);}
#line 1914 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 303 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 1920 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 306 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 1926 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 307 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=0;}
#line 1932 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 309 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= (yyvsp[0].expr);}
#line 1938 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 310 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[-2].expr);(yyval.expr)= expr_create(EXPR_ARG,(yyvsp[-2].expr),0); (yyvsp[-2].expr)->right =(yyvsp[0].expr);}
#line 1944 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 313 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create(EXPR_ARG,(yyvsp[0].expr),0);}
#line 1950 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 316 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create_string_literal((yyvsp[0].name));}
#line 1956 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 317 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr) = expr_create_char_literal((yyvsp[0].name)[1]);}
#line 1962 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 319 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_MUL,(yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1968 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 320 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create(EXPR_DIV,(yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1974 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 321 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_MOD, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1980 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 322 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_EXP,(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1986 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 323 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 1992 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 325 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 1998 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 328 "parser.bison" /* yacc.c:1646  */
    {printf("(E) \n");(yyval.expr)=(yyvsp[-1].expr);}
#line 2004 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 329 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create(EXPR_MUL, expr_create_integer_literal(-1), (yyvsp[0].expr));}
#line 2010 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 330 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create_integer_literal(atoi((yyvsp[0].num)));}
#line 2016 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 331 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create_name((yyvsp[0].name));}
#line 2022 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 332 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)= expr_create(EXPR_CALL, expr_create_name((yyvsp[-3].name)), (yyvsp[-1].expr));}
#line 2028 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 333 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 2034 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 334 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 2040 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 335 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr) = expr_create_boolean_literal(1);}
#line 2046 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 336 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr) = expr_create_boolean_literal(0);}
#line 2052 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 339 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr) = expr_create(EXPR_SUBSCRIPT,expr_create_name((yyvsp[-4].name)),(yyvsp[-2].expr));}
#line 2058 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 341 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=expr_create(EXPR_SUBSCRIPT,0,(yyvsp[-2].expr));}
#line 2064 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 342 "parser.bison" /* yacc.c:1646  */
    {(yyval.expr)=0;}
#line 2070 "parser.c" /* yacc.c:1646  */
    break;


#line 2074 "parser.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}
#line 345 "parser.bison" /* yacc.c:1906  */


/* This function is called whenever the parser fails to parse the input */
int yyerror( char *s ) {
    printf("parse error: %s\n",s);
    exit (1);
    //return 1;
}

