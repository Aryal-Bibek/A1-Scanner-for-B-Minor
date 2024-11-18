/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 181 "parser.bison" /* yacc.c:1909  */

struct decl *decl;
struct type *type;
struct stmt *stmt;
struct expr *expr;
struct param_list *param_list;
char *name;
int num;

#line 114 "token.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOKEN_H_INCLUDED  */
