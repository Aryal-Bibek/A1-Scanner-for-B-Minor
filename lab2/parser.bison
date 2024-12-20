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
%}

%token <num> TOKEN_INTEGER_LITERAL
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
%token <name> TOKEN_CHAR_LITERAL
%token <name> TOKEN_STRING_LITERAL
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
struct expr *expr;
struct param_list *param_list;
char *name;
int num;
};

%type <decl> program decl_list decl 
%type <type> type type_func type_array type_array_smaller
%type <stmt> stmt_list stmt for unmatched_stmt matched_stmt
%type <param_list> param_list param empty_param_list non_empty_param_list
%type <expr> expr arg args assign term factor_bigger factor_smaller alpha expr_or_empty assign_or_empty non_empty_args subscript can_be_empty_subscript



%%


/* Here is the grammar: program is the start symbol. */

    program : decl_list {parser_result=$1;printf("\nparsing tree\n");decl_print($1);printf("\ndone printing tree\n");}
    ;

    decl_list : decl decl_list { $$ = $1; $1->next = $2; }
    | {$$ = 0; }
    ;

    decl : TOKEN_IDENT TOKEN_COLON type TOKEN_SEMICOLON { $$ = decl_create($1,$3,0,0,0); }
    | TOKEN_IDENT TOKEN_COLON type TOKEN_ASSIGNMENT expr TOKEN_SEMICOLON { $$ = decl_create($1,$3,$5,0,0);}
    | TOKEN_IDENT TOKEN_COLON type_func TOKEN_LB param_list TOKEN_RB TOKEN_ASSIGNMENT TOKEN_CLB stmt_list TOKEN_CRB{$3->params=$5;$$ =decl_create($1,$3,0,$9,0);}
    | TOKEN_IDENT TOKEN_COLON type_func TOKEN_LB param_list TOKEN_RB TOKEN_SEMICOLON{$3->params=$5;$$ =decl_create($1,$3,0,0,0);}
    | TOKEN_IDENT TOKEN_COLON type_array TOKEN_SEMICOLON {$$ = decl_create($1,$3,0,0,0);}
    | TOKEN_IDENT TOKEN_COLON type_array TOKEN_ASSIGNMENT TOKEN_CLB args TOKEN_CRB TOKEN_SEMICOLON {$$ = decl_create($1,$3,$6,0,0);}
    ;

    stmt_list : stmt stmt_list {$$=$1;$1->next=$2;}
    | {$$=0;}
    ;

    stmt : unmatched_stmt {$$=$1;}
    | matched_stmt {$$=$1;}
    ;

    matched_stmt: decl {$$=stmt_create(STMT_DECL,$1,0,0,0,0,0,0 );}
    | expr TOKEN_SEMICOLON {$$=stmt_create(STMT_EXPR,0, 0,$1,0,0,0,0);}
    | assign TOKEN_SEMICOLON {$$=stmt_create(STMT_EXPR,0,0,$1,0,0,0,0);}
    | TOKEN_RETURN expr TOKEN_SEMICOLON {$$ = stmt_create(STMT_RETURN, 0,0, $2,0,0,0,0);}
    | TOKEN_CLB stmt_list TOKEN_CRB {$$=stmt_create(STMT_BLOCK,0,0,0,0,$2,0,0);}
    | for {$$=$1;}
    | TOKEN_PRINT args TOKEN_SEMICOLON {$$ = stmt_create(STMT_PRINT, 0,0,$2,0,0,0,0);}
    | TOKEN_IF TOKEN_LB expr TOKEN_RB matched_stmt TOKEN_ELSE matched_stmt {$$ = stmt_create(STMT_IF_ELSE,0,0,$3,0,$5,$7,0);}
    ;

    unmatched_stmt: TOKEN_IF TOKEN_LB expr TOKEN_RB stmt {$$ = stmt_create(STMT_IF,0,0,$3,0,$5,0,0);}
    | TOKEN_IF TOKEN_LB expr TOKEN_RB matched_stmt TOKEN_ELSE unmatched_stmt {$$ = stmt_create(STMT_IF_ELSE,0,0,$3,0,$5,$7,0);}
    ;



    for : TOKEN_FOR TOKEN_LB assign_or_empty TOKEN_SEMICOLON expr_or_empty  TOKEN_SEMICOLON expr_or_empty  TOKEN_RB stmt {$$=stmt_create(STMT_FOR,0,$3,$5,$7,$9,0,0);}
    ;
    assign_or_empty : assign {$$=$1;}
    | {$$=0;}
    ;
    expr_or_empty : expr {$$=$1;}
    | {$$=0;}
    ;

    assign: expr TOKEN_ASSIGNMENT expr {$$ = expr_create(EXPR_ASSIGN,  $1, $3);}
    ;
    param_list: empty_param_list {$$=$1;}
    | non_empty_param_list {$$=$1;}
    ;

    non_empty_param_list: param {$$ = $1;}
    | param TOKEN_COMMA non_empty_param_list {$$ = $1; $1->next=$3;}
    ;

    empty_param_list : {$$=0;}
    ;

    param: TOKEN_IDENT TOKEN_COLON type_array_smaller {$$=param_list_create($1,$3, 0);}
    ;


    type_array: TOKEN_ARRAY TOKEN_SLB TOKEN_SRB type_array_smaller {$$=type_create(TYPE_ARRAY, $4,0);}
    | TOKEN_ARRAY TOKEN_SLB factor_smaller TOKEN_SRB type_array_smaller {$$=type_create(TYPE_ARRAY, $5,0);$$->array_size=$3->literal_value;}
    ;

    type_array_smaller :  TOKEN_ARRAY TOKEN_SLB TOKEN_SRB type_array_smaller {$$=type_create(TYPE_ARRAY, $4,0);}
    | TOKEN_ARRAY TOKEN_SLB factor_smaller TOKEN_SRB type_array_smaller {$$=type_create(TYPE_ARRAY, $5,0);$$->array_size=$3->literal_value;}
    | type {$$=$1;}
    ;

    type_func : TOKEN_FUNCTION type {$$= type_create(TYPE_FUNCTION,$2,0);}
    ;

    type: TOKEN_VOID {$$ = type_create(TYPE_VOID,  0,0);}
    | TOKEN_INTEGER {$$ = type_create(TYPE_INTEGER,  0,0); }
    | TOKEN_BOOLEAN {$$ = type_create(TYPE_BOOLEAN,  0,0);}
    | TOKEN_CHAR {$$ = type_create(TYPE_CHARACTER,  0,0);}
    | TOKEN_STRING {$$ = type_create(TYPE_STRING,  0,0);}
    ;

    expr : expr TOKEN_ADD term {$$= expr_create(EXPR_ADD,$1,$3);} 
    | expr TOKEN_SUBTRACT term {$$= expr_create(EXPR_SUB,$1,$3);} 
    | expr TOKEN_EQ term {$$= expr_create(EXPR_EQ,$1,$3);}
    | expr TOKEN_NE term {$$= expr_create(EXPR_NEQ,$1,$3);}
    | expr TOKEN_GT term {$$= expr_create(EXPR_GT,$1,$3);}
    | expr TOKEN_LT term {$$= expr_create(EXPR_LT,$1,$3);}
    | expr TOKEN_GE term {$$= expr_create(EXPR_GTE,$1,$3);}
    | expr TOKEN_LE term {$$= expr_create(EXPR_LTE,$1,$3);}
    | expr TOKEN_AND term {$$ = expr_create(EXPR_AND,$1,$3);}
    | expr TOKEN_OR term {$$ = expr_create(EXPR_OR,$1,$3);}
    | TOKEN_NOT factor_bigger {$$=expr_create(EXPR_NOT,$2,0);}
    | TOKEN_INCREMENT factor_bigger {$$=expr_create(EXPR_INCR,$2,0);}
    | factor_bigger TOKEN_INCREMENT {$$=expr_create(EXPR_INCR,$1,0);}
    | TOKEN_DECREMENT factor_bigger {$$=expr_create(EXPR_DECR,$2,0);}
    | factor_bigger TOKEN_DECREMENT {$$=expr_create(EXPR_DECR,$1,0);}
    | term {$$=$1;}
    ;

    args : non_empty_args {$$=$1;}
    | {$$=0;}

    non_empty_args : arg {$$= $1;}
    |arg TOKEN_COMMA args {$$=$1;$$= expr_create(EXPR_ARG,$1,0); $1->right =$3;}
    ; 

    arg: expr{$$=expr_create(EXPR_ARG,$1,0);}
    ;

    alpha: TOKEN_STRING_LITERAL {$$=expr_create_string_literal($1);}
    | TOKEN_CHAR_LITERAL {$$ = expr_create_char_literal($1[1]);}

    term : term TOKEN_MULTIPLY factor_bigger {$$= expr_create(EXPR_MUL,$1, $3);}
    | term TOKEN_DIVIDE factor_bigger {$$=expr_create(EXPR_DIV,$1, $3);}
    | term TOKEN_MODULO factor_bigger {$$= expr_create(EXPR_MOD, $1, $3);}
    | term TOKEN_EXPONENT factor_bigger {$$= expr_create(EXPR_EXP,$1,$3);}
    | factor_bigger {$$=$1;}
    ;
    factor_bigger : factor_smaller {$$=$1;}
    ;

    factor_smaller: TOKEN_LB expr TOKEN_RB {$$=$2;}
    | TOKEN_SUBTRACT factor_smaller {$$=expr_create(EXPR_MUL, expr_create_integer_literal(-1), $2);} 
    | TOKEN_INTEGER_LITERAL {$$=expr_create_integer_literal(atoi($1));}
    | TOKEN_IDENT {$$=expr_create_name($1);}
    | TOKEN_IDENT TOKEN_LB args TOKEN_RB {$$= expr_create(EXPR_CALL, expr_create_name($1), $3);}
    | subscript {$$=$1;}
    | alpha {$$=$1;}
    | TOKEN_TRUE {$$ = expr_create_boolean_literal(1);}
    | TOKEN_FALSE {$$ = expr_create_boolean_literal(0);}
    ;

    subscript : TOKEN_IDENT TOKEN_SLB expr TOKEN_SRB can_be_empty_subscript {$$ = expr_create(EXPR_SUBSCRIPT,expr_create_name($1),$3);}
    ;
    can_be_empty_subscript: TOKEN_SLB expr TOKEN_SRB can_be_empty_subscript {$$=expr_create(EXPR_SUBSCRIPT,0,$2);}
    | {$$=0;}
    ;
    
%%

/* This function is called whenever the parser fails to parse the input */
int yyerror( char *s ) {
    printf("parse error: %s\n",s);
    exit (1);
    //return 1;
}

