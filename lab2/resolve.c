#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decl.h"
#include "stmt.h"
#include "expr.h"
#include "param_list.h"
#include "scope.h"
#include "symbol.h"

#define DEBUG (0)

extern struct decl *parser_result;

struct decl* calling_func;

extern int isThereError;

int param_num=0;

int local_num=0;

int resolve_tree(){
    scope_enter();
    decl_resolve(parser_result);
    scope_exit();
    return 0;
}

void decl_resolve(struct decl *d){
    if(!d) return;

    symbol_t kind = scope_level() > 1 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;
    if DEBUG printf("declaration of %s type %d\n", d->name, d->type->kind);
    if (!d->type){
        if DEBUG printf("no type %s\n", d->name);
    }
    int hasThereBeenFuncImplementation = 0;
    if (d->type->kind == TYPE_FUNCTION){
        if DEBUG printf("yeah this is a function declaration %s\n", d-> name);
        if (scope_level() > 1){
            fprintf(stderr, "Error: cannot declare functions outside of global scope %d\n");
            isThereError=1;
        }
        struct symbol *same_name_func = scope_lookup(d->name);
        if (same_name_func){
            if DEBUG printf("fuction prototype already declared %s\n", d-> name);
            if (type_equals(d->type, same_name_func->type)==0){
                fprintf(stderr,"function declaration differs from prototype\n");
                isThereError=1;
            }
        }
        if (d->code){
            if (same_name_func){
                if (same_name_func->which==1){
                    fprintf(stderr, "function has already been defined\n");
                    isThereError=1;
                }
            }
            hasThereBeenFuncImplementation =1;
        } else {
            if (same_name_func){
                if (same_name_func->which==1){
                    hasThereBeenFuncImplementation = 1;
                }
            }
        }
    }

    d->symbol = symbol_create(kind, d->type, d->name);
    if (d->type->kind == TYPE_FUNCTION && hasThereBeenFuncImplementation){
        d->symbol->which=1;
    } else if (scope_level() >1){
        d->symbol->which=local_num;
    }
    if (d->type->kind != TYPE_FUNCTION){
        expr_resolve(d->value);
    }
    scope_bind(d->name, d->symbol);

    if (d->code){
        scope_enter(); //entering param scope
        param_num=0;
        param_list_resolve(d->type->params);
        int tmp = local_num;
        struct decl *tmp_calling_func = calling_func;
        scope_enter(); //entering local scope
        
        calling_func = d;
        local_num=0;
        stmt_resolve(d->code);
        scope_exit(); // exiting local scope
        local_num=tmp;
        calling_func=tmp_calling_func;
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
            s->decl = calling_func;
            expr_resolve(s->expr);
            break;
        case STMT_PRINT:
            expr_resolve(s->expr);
            break;
        case STMT_BLOCK:
            int tmp = local_num;
            scope_enter();
            local_num=0;
            stmt_resolve(s->body);
            scope_exit();
            local_num=tmp;
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
        if (!e->symbol){
            printf("resolve error : %s is not defined\n", e->name);
            exit(1);
        } 
        switch(e->symbol->kind){
            case 0 : 
                printf("%s resolves to local %d\n", e->name, e->symbol->which);
                break;
            case 1 : 
                printf("%s resolves to param %d\n", e->name, e->symbol->which);
                break;
            default:
                printf("%s resolves to global %s\n", e->name, e->name);
                break;
        }
    } else {
        expr_resolve( e->left );
        expr_resolve( e->right );
    }
}
void param_list_resolve(struct param_list *p){
    if (!p) return;
    
    symbol_t kind = SYMBOL_PARAM;

    p->symbol = symbol_create(kind, p->type, p->name);
    p->symbol->which = param_num;
    param_num++;
    scope_bind(p->name, p->symbol);

    param_list_resolve(p->next);
}