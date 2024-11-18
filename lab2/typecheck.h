#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "type.h"
#include "expr.h"
#include "decl.h"
#include "stmt.h"
#include "type.h"
#include "param_list.h"

struct type *expr_typecheck(struct expr *e);
void stmt_typecheck(struct stmt *s);
void decl_typecheck(struct decl *d);

#endif