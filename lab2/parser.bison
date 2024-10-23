%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "expr.h"


extern char *yytext;
extern int yylex();
int yyerror( char *str);

struct decl * decl_create( char *name,struct type *type,struct expr *value,struct stmt *code,struct decl *next )
{
    struct decl *d = malloc(sizeof(*d));
    d->name = name;
    d->type = type;
    d->value = value;
    d->code = code;
    d->next = next;
    return d;
}

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

struct type * type_create( type_t kind, struct type *subtype, struct param_list *params )
{
    stuct type *t = malloc(sizeof(*t));
    t->kind=kind;
    t->subtype=subtype;
    t->param_list=params;
}

struct decl* parser_result;
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

    program : decl_list { parser_result = $1; }
    ;

    decl_list : decl decl_list { $$ = $1; $1->next = $2; }
    | /* epsilon */ { $$ = 0; }
    ;

    decl : name TOKEN_COLON type TOKEN_SEMICOLON { $$ = decl_create($1,$3,0,0,0); }
    | name TOKEN_COLON type TOKEN_ASSIGNMENT expr TOKEN_SEMICOLON { $$ = decl_create($1,$3,$5,0,0); }
    | name TOKEN_COLON TOKEN_FUNCTION type TOKEN_LB param_list TOKEN_RB TOKEN_ASSIGNMENT TOKEN_CLB stmt_list TOKEN_CRB/*function*/
    ;

    stmt_list : stmt stmt_list
    | /*epsilon*/
    ;
    name: TOKEN_IDENT{$$=$1;}
    ;

    type: TOKEN_VOID {printf("type = void");$$ = type_create(TYPE_VOID,  NULL,NULL);}
    | TOKEN_INTEGER {$$ = type_create(TYPE_INTEGER,  NULL,NULL);}
    | TOKEN_BOOLEAN {$$ = type_create(TYPE_BOOLEAN,  NULL,NULL);}
    | TOKEN_CHAR {$$ = type_create(TYPE_CHARACTER,  NULL,NULL);}
    | TOKEN_STRING {$$ = type_create(TYPE_STRING,  NULL,NULL);}
    ;

    stmt:
    ;


    program : expr TOKEN_SEMICOLON{printf("P\n");expr_print($1,0,0);}
    ;

    expr : expr TOKEN_ADD term {printf("E + T. \n");$$= expr_create(EXPR_ADD,$1,$3);} 
    | expr TOKEN_SUBTRACT term {printf("E - T. \n");$$= expr_create(EXPR_SUB,$1,$3);} 
    | term {printf("E\n");$$=$1;}
    ;

    term : term TOKEN_MULTIPLY factor {printf("T * F\n");$$= expr_create(EXPR_MUL,$1, $3);}
    | term TOKEN_DIVIDE factor {printf("T / F\n");$$=expr_create(EXPR_DIV,$1, $3);}
    | factor {printf("T\n");$$=$1;}
    ;
    factor: TOKEN_SUBTRACT factor {printf("-F\n");$$= expr_create_integer_literal(atoi($1)*(-1));} 
    | TOKEN_LB expr TOKEN_RB {printf("(E) \n");} 
    | TOKEN_INTEGER_LITERAL {printf("F $1=%s\n",$1);$$=expr_create_integer_literal(atoi($1));}
    ;
%%

/* This function is called whenever the parser fails to parse the input */
int yyerror( char *s ) {
    printf("parse error: %s\n",s);
    return 1;
}

