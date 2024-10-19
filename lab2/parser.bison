%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "expr.h"


extern char *yytext;
extern int yylex();
int yyerror( char *str);

struct expr * expr_create_integer_literal(int literal_value){
	struct expr *d = malloc(sizeof(*d));
	d->kind=EXPR_INTEGER_LITERAL;
	d->literal_value=literal_value;
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
%}

%token TOKEN_INTEGER_LITERAL
%token TOKEN_ADD
%token TOKEN_SUBTRACT
%token TOKEN_MULTIPLY
%token TOKEN_DIVIDE
%token TOKEN_MODULO
%token TOKEN_EXPONENT
%token TOKEN_NOT
%token TOKEN_INCREMENT
%token TOKEN_DECREMENT
%token TOKEN_WHILE
%token TOKEN_FOR
%token TOKEN_CHAR
%token TOKEN_BOOLEAN
%token TOKEN_STRING
%token TOKEN_INTEGER
%token TOKEN_VOID
%token TOKEN_TRUE
%token TOKEN_FALSE
%token TOKEN_ARRAY
%token TOKEN_PRINT
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_FUNCTION
%token TOKEN_RETURN
%token TOKEN_IDENT
%token TOKEN_CHAR_LITERAL
%token TOKEN_STRING_LITERAL
%token TOKEN_EQ
%token TOKEN_NE
%token TOKEN_GE
%token TOKEN_LE
%token TOKEN_ASSIGNMENT
%token TOKEN_GT
%token TOKEN_LT
%token TOKEN_COMMA
%token TOKEN_COLON
%token TOKEN_AND
%token TOKEN_OR
%token TOKEN_LB
%token TOKEN_RB
%token TOKEN_CLB
%token TOKEN_CRB
%token TOKEN_SLB
%token TOKEN_SRB
%token TOKEN_ERROR
%token TOKEN_SEMICOLON

%%


/* Here is the grammar: program is the start symbol. */

    program : expr TOKEN_SEMICOLON{printf("P\n");expr_print($1,0,0);}
    ;

    expr : expr TOKEN_ADD term {printf("E + T. \n");$$= expr_create(EXPR_ADD,$1,$3);} 
    | expr TOKEN_SUBTRACT term
    | term {printf("E\n");$$=$1;}
    ;

    term : term TOKEN_MULTIPLY factor
    | term TOKEN_DIVIDE factor
    | factor {printf("T\n");$$=$1;}
    ;
    factor: TOKEN_SUBTRACT factor
    | TOKEN_LB expr TOKEN_RB
    | TOKEN_INTEGER_LITERAL {printf("F $1=%d %s\n",$1,$1);$$=expr_create_integer_literal(atoi($1));}
    ;
%%

/* This function is called whenever the parser fails to parse the input */
int yyerror( char *s ) {
    printf("parse error: %s\n",s);
    return 1;
}

