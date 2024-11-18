#include <stdio.h>
#include <stdlib.h>
#include "typecheck.h"

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
  struct type *lt = expr_typecheck(e->left);
  struct type *rt = expr_typecheck(e->right);
  struct type *result;
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
    case EXPR_MUL:
    case EXPR_DIV:
    case EXPR_MOD:
    case EXPR_ADD:
      if( lt->kind!=TYPE_INTEGER || rt->kind!=TYPE_INTEGER ) {
        fprintf(stderr, "error: cannot add");
      }
      result = type_create(TYPE_INTEGER,0,0);
      break;
    case EXPR_LT:
    case EXPR_GT:
    case EXPR_LTE:
    case EXPR_GTE:
    case EXPR_EQ:
    case EXPR_NEQ:
      if(!type_equals(lt,rt)) {
        fprintf(stderr, "error: operands must be of the same type for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
      }
      if(lt->kind==TYPE_VOID || lt->kind==TYPE_ARRAY || lt->kind==TYPE_FUNCTION) {
        fprintf(stderr, "error: unsupported types for comparison in %s\n", 
          e->kind == EXPR_LT ? "<" :
          e->kind == EXPR_GT ? ">" :
          e->kind == EXPR_LTE ? "<=" :
          e->kind == EXPR_GTE ? ">=" :
          e->kind == EXPR_EQ ? "==" : "!=");
      }
      result = type_create(TYPE_BOOLEAN,0,0);
      break;
    case EXPR_INCR:
    case EXPR_DECR:
      if (lt->kind != TYPE_INTEGER) {
        fprintf(stderr, "error: operand must be an integer for operation %s\n", e->kind == EXPR_INCR ? "increment" : "decrement");
      }
      result = type_copy(lt);
      break;
    case EXPR_AND:
    case EXPR_OR:
      if (lt->kind != TYPE_BOOLEAN || rt->kind != TYPE_BOOLEAN) {
        fprintf(stderr, "Error: operands must be boolean for operation %s\n", e->kind == EXPR_AND ? "AND" : "OR");
      }
      result = type_create(TYPE_BOOLEAN, 0, 0);
      break;  
    case EXPR_NOT:
      if (lt->kind != TYPE_BOOLEAN) {
          fprintf(stderr, "Error: operand must be boolean for NOT operation\n");
      }
      result = type_create(TYPE_BOOLEAN, 0, 0); 
      break; 
    case EXPR_ASSIGN:
      if (lt->kind != TYPE_INTEGER && lt->kind != TYPE_BOOLEAN && lt->kind != TYPE_STRING && lt->kind != TYPE_CHARACTER) {
          fprintf(stderr, "Error: left-hand side must be a variable (lvalue) for assignment\n");
      }
      if (lt->kind != rt->kind) {
          fprintf(stderr, "Error: mismatched types in assignment");
      }
      result = type_copy(lt);
      break;
    case EXPR_NAME:
      result = type_copy(e->symbol->type);
      break;
    case EXPR_CALL:
      result = type_copy(e->symbol->type); 
      break;
    case EXPR_ARR:
      if (lt->kind != TYPE_INTEGER) {
          fprintf(stderr, "Error: array size must be an integer\n");
      }
      result = type_create(TYPE_ARRAY, 0, lt); 
      break;
    case EXPR_SUBSCRIPT:
      if (lt->kind != TYPE_ARRAY) {
          fprintf(stderr, "Error: left-hand side must be an array for subscript\n");
      }
      if (rt->kind != TYPE_INTEGER) {
          fprintf(stderr, "Error: index must be an integer for subscript\n");
      }
      result = type_copy(lt->subtype); 
      break;
    default:
      fprintf(stderr, "Error: unsupported expression type %d\n", e->kind);
      result = NULL;
      break;
  }
  type_delete(lt);
  type_delete(rt);
  return result;
}

void decl_typecheck( struct decl *d ){
  if(d->value) {
    struct type *t;
    t = expr_typecheck(d->value);
    if(!type_equals(t,d->symbol->type)) {
      fprintf(stderr, "Error: type mismatch for variable ");
    }
  }
  if(d->code) {
    stmt_typecheck(d->code);
  }
}

void stmt_typecheck( struct stmt *s ){
  struct type *t;
  switch(s->kind) {
    case STMT_EXPR:
      t = expr_typecheck(s->expr);
      type_delete(t);
      break;
    case STMT_IF_ELSE:
      t = expr_typecheck(s->expr);
      if(t->kind!=TYPE_BOOLEAN) {
        fprintf(stderr, "error: condition in if-else statement must be of boolean type");
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
        fprintf(stderr, "error: condition in if statement must be of boolean type,");
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
        fprintf(stderr, "error: condition in for loop must be of boolean type,");
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
      if (t->kind == TYPE_VOID) {
        fprintf(stderr, "error: cannot print expression of type void\n");
      }
      type_delete(t);
      break;
    case STMT_RETURN:
      if (s->expr != NULL) {
          t = expr_typecheck(s->expr);
          if (t->kind != s->decl->type->kind) {
            fprintf(stderr, "error: return type mismatch: ");
          }
          type_delete(t);
      } else {
          if (s->decl->type->kind != TYPE_VOID) {
            fprintf(stderr, "error: return value expected, but none provided\n");
          }
      }
      break;
    case STMT_BLOCK:
      for (struct stmt *stmt = s->body; stmt != NULL; stmt = stmt->next) {
          stmt_typecheck(stmt);
      }
      break;
    default:
      fprintf(stderr, "error: Unknown statement kind '%d'\n", s->kind);
      break;
  }
}
