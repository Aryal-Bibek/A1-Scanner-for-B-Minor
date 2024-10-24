%{
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
%token <name> TOKEN_IDENT
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

%union {
struct decl *decl;
struct type *type;
struct stmt *stmt;
struct param_list *param_list;
char *name;
};

%type <decl> program decl_list decl 
%type <type> type type_func
%type <stmt> stmt_list stmt
%type <param_list> param_list param
%type <name> name 



%%


/* Here is the grammar: program is the start symbol. */

    program : decl_list {parser_result=$1;printf("\nparsing tree\n");decl_print($1);printf("\ndone printing tree\n");}
    ;

    decl_list : decl decl_list { $$ = $1; $1->next = $2; }
    | { printf("epsilon decl list\n");$$ = 0; }
    ;

    decl : name TOKEN_COLON type TOKEN_SEMICOLON { $$ = decl_create($1,$3,0,0,0); printf("decl creat name is %s\n", $$->name); }
    /*| name TOKEN_COLON type TOKEN_ASSIGNMENT expr TOKEN_SEMICOLON { $$ = decl_create($1,$3,$5,0,0); }*/
    | name TOKEN_COLON type_func TOKEN_LB param_list TOKEN_RB TOKEN_ASSIGNMENT TOKEN_CLB stmt_list TOKEN_CRB{$3->params=$5;$$ =decl_create($1,$3,0,$9,0);}
    ;

    stmt_list : stmt stmt_list {$$=$1;$1->next=$2;}
    | {$$=0;}
    ;

    stmt: decl {$$=stmt_create(STMT_DECL,$1,0,0,0,0,0,0 );}
    ;

    param_list: param param_list {$$ = $1; $1->next=$2;}
    | {$$=0;}
    ;

    param: name TOKEN_COLON type {$$=param_list_create($1,$3, 0);}
    | TOKEN_COMMA name TOKEN_COLON type {$$=param_list_create($2,$4, 0);}
    ;

    name: TOKEN_IDENT {printf("name $1=%s\n",$1);$$=$1;}
    ;

    type_func : TOKEN_FUNCTION type {$$= type_create(TYPE_FUNCTION,$2,0);printf("Function type\n");}
    ;

    type: TOKEN_VOID {printf("type = void");$$ = type_create(TYPE_VOID,  NULL,NULL);}
    | TOKEN_INTEGER {$$ = type_create(TYPE_INTEGER,  NULL,NULL); printf("integer\n");}
    | TOKEN_BOOLEAN {$$ = type_create(TYPE_BOOLEAN,  NULL,NULL);}
    | TOKEN_CHAR {$$ = type_create(TYPE_CHARACTER,  NULL,NULL);}
    | TOKEN_STRING {$$ = type_create(TYPE_STRING,  NULL,NULL);}
    ;

    

    /*


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
    */
%%

/* This function is called whenever the parser fails to parse the input */
int yyerror( char *s ) {
    printf("parse error: %s\n",s);
    return 1;
}

