#ifndef TYPE_H
#define TYPE_H

#include "param_list.h"

typedef enum {
	TYPE_VOID,
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_FUNCTION,
} type_t;

struct type {
	type_t kind;
	struct param_list *params;
	struct type *subtype;
	int array_size;
};

struct type * type_create( type_t kind, struct type *subtype, struct param_list *params );

#endif