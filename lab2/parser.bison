%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

extern char *yytext;
extern int yylex();
int yyerror( char *str);
%}

%token TOKEN_INTEGER_LITERAL
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_SEMI

%%

/* Here is the grammar: program is the start symbol. */

    program : expr TOKEN_SEMI
    ;

    expr : expr TOKEN_PLUS expr
    | expr TOKEN_MINUS term
    | term
    ;

    term : term TOKEN_MUL factor
    | term TOKEN_DIV factor
    | factor
    ;
    factor: TOKEN_MINUS factor
    | TOKEN_LPAREN expr TOKEN_RPAREN
    | TOKEN_INTEGER_LITERAL
    ;
%%

/* This function is called whenever the parser fails to parse the input */
int yyerror( char *s ) {
    printf("parse error: %s\n",s);
    return 1;
}

