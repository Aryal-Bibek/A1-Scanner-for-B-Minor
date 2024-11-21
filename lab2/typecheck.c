#include <stdio.h>
#include <stdlib.h>
#include "typecheck.h"

#define DEBUG (0)

int isThereError=0;

int type_equals( struct type *a, struct type *b ){
  if( a->kind == b->kind ) {
  if( is_atomic(a) && is_atomic(b) ){
    return 1;
  } else if (a->kind == TYPE_ARRAY && b->kind == TYPE_ARRAY) {
    return type_equals(a->subtype, b->subtype);
  } else if (a->kind == TYPE_FUNCTION && b->kind == TYPE_FUNCTION) {
      struct param_list* pla = a->params;
      struct param_list* plb = b->params;

      while (1) {
        if (pla == NULL && plb == NULL) break;
        else if ((pla != NULL && plb == NULL) || (pla == NULL && plb != NULL)) return 0;
        if (!type_equals(pla->type, plb->type)) return 0;

        pla = pla->next;
        plb = plb->next;	
      }

      return type_equals(a->subtype, b->subtype);
  }
  } else {
    return 0;
  }
}
int is_atomic(struct type* a) {
  return (a->kind == TYPE_BOOLEAN || a->kind == TYPE_CHARACTER || a->kind == TYPE_INTEGER || a->kind == TYPE_STRING);
}

struct type * type_copy( struct type *t ){
  if (!t) return NULL;
  return type_create(t->kind, type_copy(t->subtype), param_list_copy(t->params));
}

void type_delete( struct type *t ){
  if (!t) return;
  param_list_delete(t->params);
  type_delete(t->subtype);
  free(t);
}

struct type * expr_typecheck( struct expr *e ){
  if(!e) return 0;
  if DEBUG printf("got in expr typecheck\n");
  struct type *lt = expr_typecheck(e->left);
  if DEBUG printf("got past left \n");
  struct type *rt = expr_typecheck(e->right);
  if DEBUG printf("got past right %d \n", e->kind);
  struct type *result = NULL;
  switch(e->kind) {
    case EXPR_INTEGER_LITERAL:
      result = type_create(TYPE_INTEGER,0,0);
      break;
    case EXPR_STRING_LITERAL:
      result = type_create(TYPE_STRING,0,0);
      break;
    case EXPR_CHAR_LITERAL:
      result = type_create(TYPE_CHARACTER, 0, 0);
      break;
    case EXPR_BOOLEAN_LITERAL:
      result = type_create(TYPE_BOOLEAN, 0, 0);
      break;
    case EXPR_SUB:
      if( lt->kind!=TYPE_INTEGER || rt->kind!=TYPE_INTEGER ) {
        fprintf(stderr, "error: cannot substract\n");
        isThereError=1;
      }
      result = type_create(TYPE_INTEGER,0,0);
      break;
    case EXPR_MUL:
      if( lt->kind!=TYPE_INTEGER || rt->kind!=TYPE_INTEGER ) {
        fprintf(stderr, "error: cannot multiply\n");
        isThereError=1;
      }
      result = type_create(TYPE_INTEGER,0,0);
      break;
    case EXPR_DIV:
      if( lt->kind!=TYPE_INTEGER || rt->kind!=TYPE_INTEGER ) {
        fprintf(stderr, "error: cannot divide\n");
        isThereError=1;
      }
      result = type_create(TYPE_INTEGER,0,0);
      break;
    case EXPR_MOD:
      if( lt->kind!=TYPE_INTEGER || rt->kind!=TYPE_INTEGER ) {
        fprintf(stderr, "error: cannot add\n");
        isThereError=1;
      }
      result = type_create(TYPE_INTEGER,0,0);
      break;
    case EXPR_ADD:
      if( lt->kind!=TYPE_INTEGER || rt->kind!=TYPE_INTEGER ) {
        fprintf(stderr, "error: cannot add\n");
        isThereError=1;
      }
      result = type_create(TYPE_INTEGER,0,0);
      break;
    case EXPR_LT:
      if(!type_equals(lt,rt)) {
        fprintf(stderr, "error: operands must be of the same type for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
        isThereError=1;
      }
      if(lt->kind==TYPE_VOID || lt->kind==TYPE_ARRAY || lt->kind==TYPE_FUNCTION) {
        fprintf(stderr, "error: unsupported types for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
        isThereError=1;
      }
      result = type_create(TYPE_BOOLEAN,0,0);
      break;
    case EXPR_GT:
      if(!type_equals(lt,rt)) {
        fprintf(stderr, "error: operands must be of the same type for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
          isThereError=1;
      }
      if(lt->kind==TYPE_VOID || lt->kind==TYPE_ARRAY || lt->kind==TYPE_FUNCTION) {
        fprintf(stderr, "error: unsupported types for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
          isThereError=1;
      }
      result = type_create(TYPE_BOOLEAN,0,0);
      break;
    case EXPR_LTE:
      if(!type_equals(lt,rt)) {
        fprintf(stderr, "error: operands must be of the same type for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
        isThereError=1;
      }
      if(lt->kind==TYPE_VOID || lt->kind==TYPE_ARRAY || lt->kind==TYPE_FUNCTION) {
        fprintf(stderr, "error: unsupported types for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
        isThereError=1;
      }
      result = type_create(TYPE_BOOLEAN,0,0);
      break;
    case EXPR_GTE:
      if(!type_equals(lt,rt)) {
        fprintf(stderr, "error: operands must be of the same type for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
        isThereError=1;
      }
      if(lt->kind==TYPE_VOID || lt->kind==TYPE_ARRAY || lt->kind==TYPE_FUNCTION) {
        fprintf(stderr, "error: unsupported types for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
        isThereError=1;
      }
      result = type_create(TYPE_BOOLEAN,0,0);
      break;
    case EXPR_EQ:
      if(!type_equals(lt,rt)) {
        fprintf(stderr, "error: operands must be of the same type for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
        isThereError=1;
      }
      if(lt->kind==TYPE_VOID || lt->kind==TYPE_ARRAY || lt->kind==TYPE_FUNCTION) {
        fprintf(stderr, "error: unsupported types for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
        isThereError=1;
      }
      result = type_create(TYPE_BOOLEAN,0,0);
      break;
    case EXPR_NEQ:
      if(!type_equals(lt,rt)) {
        fprintf(stderr, "error: operands must be of the same type for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
        isThereError=1;
      }
      if(lt->kind==TYPE_VOID || lt->kind==TYPE_ARRAY || lt->kind==TYPE_FUNCTION) {
        fprintf(stderr, "error: unsupported types for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
        isThereError=1;
      }
      result = type_create(TYPE_BOOLEAN,0,0);
      break;
    case EXPR_INCR:
      if (lt->kind != TYPE_INTEGER) {
        fprintf(stderr, "error: operand must be an integer for operation %s\n", e->kind == EXPR_INCR ? "increment" : "decrement");
        isThereError=1;
      }
      result = type_copy(lt);
      break;
    case EXPR_DECR:
      if (lt->kind != TYPE_INTEGER) {
        fprintf(stderr, "error: operand must be an integer for operation %s\n", e->kind == EXPR_INCR ? "increment" : "decrement");
        isThereError=1;
      }
      result = type_copy(lt);
      break;
    case EXPR_AND:
      if (lt->kind != TYPE_BOOLEAN || rt->kind != TYPE_BOOLEAN) {
        fprintf(stderr, "Error: operands must be boolean for operation %s\n", e->kind == EXPR_AND ? "AND" : "OR");
        isThereError=1;
      }
      result = type_create(TYPE_BOOLEAN, 0, 0);
      break;  
    case EXPR_OR:
      if (lt->kind != TYPE_BOOLEAN || rt->kind != TYPE_BOOLEAN) {
        fprintf(stderr, "Error: operands must be boolean for operation %s\n", e->kind == EXPR_AND ? "AND" : "OR");
        isThereError=1;
      }
      result = type_create(TYPE_BOOLEAN, 0, 0);
      break;  
    case EXPR_NOT:
      if (lt->kind != TYPE_BOOLEAN) {
          fprintf(stderr, "Error: operand must be boolean for NOT operation\n");
        isThereError=1;
      }
      result = type_create(TYPE_BOOLEAN, 0, 0); 
      break; 
    case EXPR_ASSIGN:
      if (lt->kind != TYPE_INTEGER && lt->kind != TYPE_BOOLEAN && lt->kind != TYPE_STRING && lt->kind != TYPE_CHARACTER && lt->kind != TYPE_ARRAY) {
          fprintf(stderr, "Error: left-hand side must be a variable (lvalue) for assignment %d\n", lt->kind);
          isThereError=1;
      }
      struct type * type_of_right_side =rt;
      if (rt->kind  == TYPE_FUNCTION){
        type_of_right_side = rt->subtype;
      } 
      if (!type_equals(lt, type_of_right_side)) {
        fprintf(stderr, "Error: mismatched types in assignment\n");
        isThereError=1;
      }
      result = type_copy(lt);
      break;
    case EXPR_NAME:
      if DEBUG printf("expr name \n");
      result = type_copy(e->symbol->type);
      if DEBUG printf("expr name survived\n");
      break;
    case EXPR_CALL:
      //TODO: fix call - should check if arguments match parameters of function
      if DEBUG printf("func called\n");
      result = type_copy(lt->subtype);
      if DEBUG printf("func called survived\n"); 
      break;
    case EXPR_ARG:
      result = type_copy(lt); 
      break;
    case EXPR_ARR:
      if (lt->kind != TYPE_INTEGER) {
          fprintf(stderr, "Error: array size must be an integer\n");
          isThereError=1;
      }
      result = type_create(TYPE_ARRAY, lt, 0); 
      break;
    case EXPR_SUBSCRIPT:
      if (lt->kind != TYPE_ARRAY) {
          fprintf(stderr, "Error: left-hand side must be an array for subscript\n");
          isThereError=1;
      }
      if (rt->kind != TYPE_INTEGER && !(rt->kind == TYPE_FUNCTION && rt->subtype->kind == TYPE_INTEGER)) {
          fprintf(stderr, "Error: index must be an integer for subscript\n");
          isThereError=1;
      }
      if DEBUG printf("subscripting\n");
      result = type_copy(lt->subtype); 
      if DEBUG printf("subscripting survived\n");
      break;
    default:
      fprintf(stderr, "Error: unsupported expression type %d\n", e->kind);
      isThereError=1;
      result = NULL;
      break;
  }
  type_delete(lt);
  type_delete(rt);
  return result;
}

void decl_typecheck( struct decl *d ){
  if DEBUG printf("I am in decl typecheck\n");
  if (!d){
    if DEBUG printf("decl is null\n");
    return ;
  } else {
    if DEBUG printf("%s\n", d->name);
  }
  if(d->value) {
    if DEBUG printf("got in if \n");
    
    if DEBUG printf("got past expr typecheck\n");
    if (d->type->kind == TYPE_ARRAY){
      struct expr* assigned_value = d->value;
      while (assigned_value){
        if (!type_equals(expr_typecheck(assigned_value), d->type->subtype)){
          fprintf(stderr, "Error: type mismatch for variables of array\n");
          isThereError=1;
        }
        assigned_value  = assigned_value->right;
      }
    } else {
      struct type *t;
      t = expr_typecheck(d->value);
      if(!type_equals(t,d->symbol->type)) {
        fprintf(stderr, "Error: type mismatch for variable %d \n", t->kind);
        isThereError=1;
      }
    }
  }
  if(d->code) {
    stmt_typecheck(d->code);
  }
  decl_typecheck(d->next);
}

void stmt_typecheck( struct stmt *s ){
  if (!s) return;
  struct type *t;
  switch(s->kind) {
    case STMT_EXPR:
      t = expr_typecheck(s->expr);
      type_delete(t);
      break;
    case STMT_IF_ELSE:
      t = expr_typecheck(s->expr);
      if(t->kind!=TYPE_BOOLEAN) {
        fprintf(stderr, "error: condition in if-else statement must be of boolean type\n");
        isThereError=1;
      }
      type_delete(t);
      stmt_typecheck(s->body);
      stmt_typecheck(s->else_body);
      break;
    case STMT_DECL:
      decl_typecheck(s->decl);
      break;
    case STMT_IF:
      t = expr_typecheck(s->expr);
      if (t->kind != TYPE_BOOLEAN) {
        fprintf(stderr, "error: condition in if statement must be of boolean type,\n");
        isThereError=1;
      }
      type_delete(t);
      stmt_typecheck(s->body);
      break;
    case STMT_FOR:
      if (s->init_expr != NULL) {
        t = expr_typecheck(s->init_expr);
        type_delete(t);
      }
      t = expr_typecheck(s->expr);
      if (t->kind != TYPE_BOOLEAN) {
        fprintf(stderr, "error: condition in for loop must be of boolean type,\n");
        isThereError=1;
      }
      type_delete(t);
      if (s->next_expr != NULL) {
        t = expr_typecheck(s->next_expr);
        type_delete(t);
      }
      stmt_typecheck(s->body);
      break;
    case STMT_PRINT:
      t = expr_typecheck(s->expr);
      if DEBUG ("got past print expr\n");
      if (t->kind == TYPE_VOID) {
        fprintf(stderr, "error: cannot print expression of type void\n");
        isThereError=1;
      }
      
      type_delete(t);
      break;
    case STMT_RETURN:
      if (s->expr != NULL) {
          t = expr_typecheck(s->expr);
          if (t->kind != s->decl->type->subtype->kind) {
            fprintf(stderr, "error: return type mismatch: \n");
            isThereError=1;
          }
          type_delete(t);
      } else {
          if (s->decl->type->subtype->kind != TYPE_VOID) {
            fprintf(stderr, "error: return value expected, but none provided\n");
            isThereError=1;
          }
      }
      break;
    case STMT_BLOCK:
      stmt_typecheck(s->body);
      break;
    default:
      fprintf(stderr, "error: Unknown statement kind '%d'\n", s->kind);
      isThereError=1;
      break;
  }
  stmt_typecheck(s->next);
}
