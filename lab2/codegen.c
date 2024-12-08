#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen_support.h"
#include "expr.h"
#include "stmt.h"
#include "decl.h"
#include "symbol.h"

const char * symbol_codegen (struct symbol * s){
    ///TODO : this function returns the exact location of given symbol (i.e. MOVQ -8(%rbp), %rbx)
    const char *  hi;
    
    return hi;
}

void expr_codegen(struct expr * e){
    if (!e) return ;

    switch (e->kind){
        // Leaf node: allocate register and load value.
        case EXPR_NAME:
            e->reg = scratch_alloc();
            printf("MOVQ %s, %s\n",symbol_codegen(e->symbol),scratch_name(e->reg));
            break;

        // Interior node: generate children, then add them.
        case EXPR_ADD:
            expr_codegen(e->left);
            expr_codegen(e->right);
            printf("ADDQ %s, %s\n",scratch_name(e->left->reg),scratch_name(e->right->reg));
            e->reg = e->right->reg;
            scratch_free(e->left->reg);
            break;

        case EXPR_ASSIGN:
            expr_codegen(e->left);
            printf("MOVQ %s, %s\n", scratch_name(e->left->reg), symbol_codegen(e->right->symbol));
            e->reg = e->left->reg;
            break;

        // TODO : add the rest of the cases.
        case EXPR_SUB:
            expr_codegen(e->left);
            expr_codegen(e->right);
            printf("SUBQ %s, %s\n",scratch_name(e->left->reg),scratch_name(e->right->reg));
            e->reg = e->right->reg;
            scratch_free(e->left->reg);
            break;
        case EXPR_MUL:
            expr_codegen(e->left);
            expr_codegen(e->right);
            printf("MOVQ %s %%rax\n",scratch_name(e->left->reg));
            printf("IMULQ %s\n", scratch_name(e->right->reg));
            printf("MOVQ %%rax %s\n",scratch_name(e->right->reg));
            scratch_free(e->left->reg);
            break;
        case EXPR_DIV:
            expr_codegen(e->left);
            expr_codegen(e->right);
            printf("MOVQ %s %%rax\n",scratch_name(e->left->reg));
            printf("CQO\n");
            printf("IDIVQ %s\n", scratch_name(e->right->reg));
            printf("MOVQ %%rax %s\n",scratch_name(e->right->reg));
            scratch_free(e->left->reg);
            break;
        case EXPR_INTEGER_LITERAL:
            e->reg = scratch_alloc();
            printf("MOVQ %s, $%d\n",scratch_name(e->reg),e->literal_value);
            break;
        case EXPR_BOOLEAN_LITERAL:
            break;
        case EXPR_CHAR_LITERAL:
            break;
        case EXPR_STRING_LITERAL:
            break;
        case EXPR_CALL:
            break;
        case EXPR_ARG:
            break;
        case EXPR_SUBSCRIPT:
            break;
        case EXPR_AND:
            break;
        case EXPR_OR:
            break;
        case EXPR_NOT:
            break;
        case EXPR_EXP:
            break;
        case EXPR_MOD:
            expr_codegen(e->left);
            expr_codegen(e->right);
            printf("MOVQ %s %%rax\n",scratch_name(e->left->reg));
            printf("CQO\n");
            printf("IDIVQ %s\n", scratch_name(e->right->reg));
            printf("MOVQ %%rdx %s\n",scratch_name(e->right->reg));
            scratch_free(e->left->reg);
            break;
        case EXPR_LT:
            break;
        case EXPR_GT:
            break;
        case EXPR_LTE:
            break;
        case EXPR_GTE:
            break;
        case EXPR_EQ:
            break;
        case EXPR_NEQ:
            break;
        case EXPR_INCR:
            break;
        case EXPR_DECR:
            break;
        case EXPR_ARR:
            break;
    }
}

void stmt_codegen( struct stmt *s )
{
    if(!s) return;
    switch(s->kind) {
        case STMT_EXPR:
            expr_codegen(s->expr);
            scratch_free(s->expr->reg);
            break;
        case STMT_DECL:
            decl_codegen(s->decl);
            break;
        case STMT_RETURN:
            expr_codegen(s->expr);
            printf("MOVQ %s, %%rax\n",scratch_name(s->expr->reg));
            printf("JMP .%s_epilogue\n",s->decl->name);
            scratch_free(s->expr->reg);
            break;
        case STMT_IF:
            int else_label = label_create();
            int done_label = label_create();
            expr_codegen(s->expr);
            printf("CMP $0, %s\n",scratch_name(s->expr->reg));
            scratch_free(s->expr->reg);
            printf("JE %s\n",label_name(else_label));
            stmt_codegen(s->body);
            printf("JMP %s\n",label_name(done_label));
            printf("%s:\n",label_name(else_label));
            stmt_codegen(s->else_body);
            printf("%s:\n",label_name(done_label));
            break;

	    case STMT_IF_ELSE:
            break;
        case STMT_FOR:
            break;
        case STMT_PRINT:
            break;
        case STMT_BLOCK:
            break;
    }
    stmt_codegen(s->next);
}

void decl_codegen(struct decl * d){
    // function epilogues must have unique labels so that return statemtnts can jump there easily
    if (!d) return;
    
    printf("%d\n",d->type->kind);
    if (d->type->kind == TYPE_FUNCTION){
        printf("in type func of decl codegen\n");
        /*
        pushq %rbp # save the base pointer
movq %rsp, %rbp # set new base pointer
pushq %rdi # save first argument on the stack
pushq %rsi # save second argument on the stack
pushq %rdx # save third argument on the stack
subq $16, %rsp # allocate two more local variables
pushq %rbx # save callee-saved registers
pushq %r12
pushq %r13
pushq %r14
pushq %r15

### body of function goes here ###
popq %r15 # restore callee-saved registers
popq %r14
popq %r13
popq %r12
popq %rbx
movq %rbp, %rsp # reset stack pointer
popq %rbp # recover previous base pointer
ret # return to the caller
        
        */

        printf("PUSHQ %%rbp\n");
        printf("MOVQ %%rsp, %%rbp\n");
        /*while
        printf("MOVQ %s",)*/

        printf("PUSHQ %%rdi\n");
        printf("PUSHQ %%rsi\n");
        printf("PUSHQ %%rdx\n");
        printf("SUBQ $16, %%rsp\n");
        printf("PUSHQ %%rbx\n");
        printf("PUSHQ %%r10\n");
        printf("PUSHQ %%r11\n");
        printf("PUSHQ %%r12\n");
        printf("PUSHQ %%r13\n");
        printf("PUSHQ %%r14\n");
        printf("PUSHQ %%r15\n");

        stmt_codegen(d->code);
        printf(".%s_epilogue:\n", d->name);
        printf("POPQ %%r15\n");
        printf("POPQ %%r14\n");
        printf("POPQ %%r13\n");
        printf("POPQ %%r12\n");
        printf("POPQ %%r11\n");
        printf("POPQ %%r10\n");
        printf("POPQ %%rbx\n");
        printf("MOVQ %%rbp, %%rsp\n");
        printf("POPQ %%rbp\n");
        printf("RET\n");
    }
    decl_codegen(d->next);
}

