#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decl.h"
#include "stmt.h"
#include "expr.h"
#include "param_list.h"
#include "scope.h"
#include "symbol.h"

extern struct decl *parser_result;

void resolve_tree(){
    scope_enter();
    decl_resolve(parser_result);
    scope_exit();
}

void decl_resolve(struct decl *d){
    if(!d) return;

    symbol_t kind = scope_level() > 1 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;

    d->symbol = symbol_create(kind, d->type, d->name);

    expr_resolve(d->value);
    scope_bind(d->name, d->symbol);

    if (d->code){
        scope_enter(); //entering param scope
        param_list_resolve(d->type->params);
        scope_enter(); //entering local scope
        stmt_resolve(d->code);
        scope_exit(); // exiting local scope
        scope_exit(); //exiting param scope
    }

    decl_resolve(d->next);
}

void stmt_resolve(struct stmt *s){
    if (!s) return;
    switch(s->kind){
        case STMT_DECL:
            decl_resolve(s->decl);
            break;
        case STMT_EXPR:
            expr_resolve(s->expr);
            break;
        case STMT_IF: 
            expr_resolve(s->expr);
            scope_enter();
            stmt_resolve(s->body);
            scope_exit();
            break;
        case STMT_IF_ELSE:
            expr_resolve(s->expr);
            scope_enter();
            stmt_resolve(s->body);
            scope_exit();
            scope_enter();
            stmt_resolve(s->else_body);
            scope_exit();
            break;
        case STMT_FOR:
            expr_resolve(s->init_expr);
            expr_resolve(s->expr);
            expr_resolve(s->next_expr);
            scope_enter();
            stmt_resolve(s->body);
            scope_exit();
            break;
        case STMT_RETURN:
            expr_resolve(s->expr);
            break;
        case STMT_PRINT:
            expr_resolve(s->expr);
            break;
        case STMT_BLOCK:
            stmt_resolve(s->body);
            break;
        default:
            break;
    }
    stmt_resolve(s->next);
}

void expr_resolve(struct expr *e){
    if(!e) return;
    if( e->kind==EXPR_NAME ) {
        e->symbol = scope_lookup(e->name);
    } else {
        expr_resolve( e->left );
        expr_resolve( e->right );
    }
}
void param_list_resolve(struct param_list *p){
    if (!p) return;
    symbol_t kind = SYMBOL_PARAM;

    p->symbol = symbol_create(kind, p->type, p->name);
    scope_bind(p->name, p->symbol);

    param_list_resolve(p->next);
}