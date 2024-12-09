#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen_support.h"
#include "expr.h"
#include "stmt.h"
#include "decl.h"
#include "symbol.h"

int data_label_emitted = 0;

int decl_codegen_called_by_stmt = 0;

const char * symbol_codegen (struct symbol * s){
    ///this function returns the exact location of given symbol (i.e. MOVQ -8(%rbp), %rbx)
    
    char * symbol_location = (char*)malloc(99 * sizeof(char));
    sprintf(symbol_location,"%d(%%rbp)", s->which*8);
    return symbol_location;
}

void expr_codegen(struct expr * e){
    if (!e) return ;

    int set_true_label;
    int set_false_label;
    int exit_label;
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
            printf("MOVQ $%d ,%s \n",e->literal_value,scratch_name(e->reg));
            break;
        case EXPR_BOOLEAN_LITERAL:
            e->reg = scratch_alloc();
            printf("MOVQ $%d ,%s \n",e->literal_value,scratch_name(e->reg));
            break;
        case EXPR_CHAR_LITERAL:
            e->reg = scratch_alloc();
            printf("MOVQ $%d ,%s \n",e->literal_value,scratch_name(e->reg));
            break;
        case EXPR_STRING_LITERAL:
            break;
        case EXPR_CALL:
            struct expr * argument = e->right;
            int argument_counter = 0;
            while (argument && argument_counter < 3){
                if (argument_counter ==0){
                    printf("MOVQ %s %%rdi\n",scratch_name(argument->left->reg));
                } else if (argument_counter==1){
                    printf("MOVQ %s %%rsi\n",scratch_name(argument->left->reg));
                } else if (argument_counter==2){
                    printf("MOVQ %s %%rdx\n",scratch_name(argument->left->reg));
                }
                argument_counter++;
                argument = argument->right;
            }
            printf("JMP .%s",e->left->name);
            e->reg=scratch_alloc;
            printf("MOVQ %%rax, %s",scratch_name(e->reg));
            break;
        case EXPR_ARG:
            expr_codegen(e->left);
            expr_codegen(e->right);
            //printf("")
            break;
        case EXPR_SUBSCRIPT:
            break;
        case EXPR_AND:
            expr_codegen(e->left);
            expr_codegen(e->right);
            printf("CMP $1, %s\n", scratch_name(e->left->reg));
            set_false_label=label_create();
            exit_label = label_create();
            printf("JNE %s\n",label_name(set_false_label));
            printf("CMP $1, %s\n", scratch_name(e->right->reg));
            printf("JNE %s\n",label_name(set_false_label));
            printf("MOVQ $1, %s",scratch_name(e->right->reg)); //set true
            printf("JMP %s\n", label_name(exit_label));
            printf("%s:\n",label_name(set_false_label));
            printf("MOVQ $0, %s", e->right->reg); //set false
            printf("%s:\n",label_name(exit_label));
            scratch_free(e->left->reg);
            break;
        case EXPR_OR:
            expr_codegen(e->left);
            expr_codegen(e->right);
            printf("CMP $1, %s\n", scratch_name(e->left->reg));
            set_true_label=label_create();
            exit_label = label_create();
            printf("JE %s\n",label_name(set_true_label));
            printf("CMP $1, %s\n", scratch_name(e->right->reg));
            printf("JE %s\n",label_name(set_true_label));
            printf("MOVQ $0, %s",scratch_name(e->right->reg)); //set false
            printf("JMP %s\n", label_name(exit_label));
            printf("%s:\n",label_name(set_true_label));
            printf("MOVQ $1, %s", e->right->reg); //set true
            printf("%s:\n",label_name(exit_label));
            scratch_free(e->left->reg);
            break;
        case EXPR_NOT:
            expr_codegen(e->left);
            printf("CMP $0, %s\n", scratch_name(e->left->reg));
            set_true_label=label_create();
            exit_label = label_create();
            printf("JE %s\n",label_name(set_true_label));
            printf("MOVQ $0, %s",scratch_name(e->left->reg)); //set false
            printf("JMP %s\n", label_name(exit_label));
            printf("%s:\n",label_name(set_true_label));
            printf("MOVQ $1, %s", e->left->reg); //set true
            printf("%s:\n",label_name(exit_label));

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
            expr_codegen(e->left);
            expr_codegen(e->right);
            printf("CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            set_true_label=label_create();
            exit_label = label_create();
            printf("JL %s\n",label_name(set_true_label));
            printf("MOVQ $0 ,%s\n",scratch_name(e->right->reg)); //set to false
            printf("JMP %s\n",label_name(exit_label));
            printf("%s:\n",label_name(set_true_label));
            printf("MOVQ $1 ,%s\n",scratch_name(e->right->reg)); //set to true
            printf("%s:\n",label_name(exit_label));
            scratch_free(e->left->reg);
            break;
        case EXPR_GT:
            expr_codegen(e->left);
            expr_codegen(e->right);
            printf("CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            set_true_label=label_create();
            exit_label = label_create();
            printf("JG %s\n",label_name(set_true_label));
            printf("MOVQ $0, %s\n",scratch_name(e->right->reg)); //set to false
            printf("JMP %s\n",label_name(exit_label));
            printf("%s:\n",label_name(set_true_label));
            printf("MOVQ $1, %s\n",scratch_name(e->right->reg)); //set to true
            printf("%s:\n",label_name(exit_label));
            scratch_free(e->left->reg);
            break;
        case EXPR_LTE:
            expr_codegen(e->right);
            printf("CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            set_true_label=label_create();
            exit_label = label_create();
            printf("JLE %s\n",label_name(set_true_label));
            printf("MOVQ $0, %s\n",scratch_name(e->right->reg)); //set to false
            printf("JMP %s\n",label_name(exit_label));
            printf("%s:\n",label_name(set_true_label));
            printf("MOVQ $1, %s\n",scratch_name(e->right->reg)); //set to true
            printf("%s:\n",label_name(exit_label));
            scratch_free(e->left->reg);
            break;
        case EXPR_GTE:
            expr_codegen(e->right);
            printf("CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            set_true_label=label_create();
            exit_label = label_create();
            printf("JGE %s\n",label_name(set_true_label));
            printf("MOVQ $0, %s\n",scratch_name(e->right->reg)); //set to false
            printf("JMP %s\n",label_name(exit_label));
            printf("%s:\n",label_name(set_true_label));
            printf("MOVQ $1, %s\n",scratch_name(e->right->reg)); //set to true
            printf("%s:\n",label_name(exit_label));
            scratch_free(e->left->reg);
            break;
        case EXPR_EQ:
            expr_codegen(e->right);
            printf("CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            set_true_label=label_create();
            exit_label = label_create();
            printf("JE %s\n",label_name(set_true_label));
            printf("MOVQ $0 ,%s\n",scratch_name(e->right->reg)); //set to false
            printf("JMP %s\n",label_name(exit_label));
            printf("%s:\n",label_name(set_true_label));
            printf("MOVQ $1 ,%s\n",scratch_name(e->right->reg)); //set to true
            printf("%s:\n",label_name(exit_label));
            scratch_free(e->left->reg);
            break;
        case EXPR_NEQ:
            expr_codegen(e->right);
            printf("CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            set_true_label=label_create();
            exit_label = label_create();
            printf("JNE %s\n",label_name(set_true_label));
            printf("MOVQ $0, %s\n",scratch_name(e->right->reg)); //set to false
            printf("JMP %s\n",label_name(exit_label));
            printf("%s:\n",label_name(set_true_label));
            printf("MOVQ $1, %s\n",scratch_name(e->right->reg)); //set to true
            printf("%s:\n",label_name(exit_label));
            scratch_free(e->left->reg);
            break;
        case EXPR_INCR:
            expr_codegen(e->left);
            printf("INCQ, %s\n",scratch_name(e->left->reg));
            //printf("MOVQ %s ,%s\n",scratch_name(e->right->reg), symbol_codegen(e->left->symbol)); 
            e->reg = e->left->reg;
            scratch_free(e->left->reg);
            break;
        case EXPR_DECR:
            expr_codegen(e->left);
            printf("DECQ, %s\n",scratch_name(e->left->reg));
            //printf("MOVQ %s ,%s\n",scratch_name(e->right->reg), symbol_codegen(e->left->symbol)); 
            e->reg = e->left->reg;
            scratch_free(e->left->reg);
            break;
        case EXPR_ARR:
            expr_codegen(e->left);
            e->reg = e->left->reg;
            break;
    }
}

void stmt_codegen( struct stmt *s )
{
    if(!s) return;
    int else_label;
    int done_label;
    int loop_label;
    switch(s->kind) {
        case STMT_EXPR:
            expr_codegen(s->expr);
            scratch_free(s->expr->reg);
            break;
        case STMT_DECL:
            decl_codegen_called_by_stmt=1;
            decl_codegen(s->decl);
            decl_codegen_called_by_stmt=0;
            break;
        case STMT_RETURN:
            expr_codegen(s->expr);
            printf("MOVQ %s, %%rax\n",scratch_name(s->expr->reg));
            printf("JMP .%s_epilogue\n",s->decl->name);
            scratch_free(s->expr->reg);
            break;
        case STMT_IF:
            else_label = label_create();
            done_label = label_create();
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
            else_label = label_create();
            done_label = label_create();
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
        case STMT_FOR:
            loop_label = label_create();
            done_label = label_create();

            //init expr
            if(s->init_expr){
                expr_codegen(s->init_expr);
                scratch_free(s->init_expr->reg);
            }
            printf("%s:\n",label_name(loop_label));
            
            // condition expr
            if(s->expr){
                expr_codegen(s->expr);
                printf("CMP $0, %s\n",scratch_name(s->expr->reg));
                scratch_free(s->expr->reg);
                printf("JE %s\n",label_name(done_label));
            }

            // body 
            if (s->body){
                stmt_codegen(s->body);
            }

            //next expr
            if(s->next_expr){
                expr_codegen(s->next_expr);
                //s->expr->reg=s->next_expr->reg;
                scratch_free(s->next_expr->reg);
            }
            printf("JMP %s\n",label_name(loop_label));
            printf("%s:\n",label_name(done_label));
            break;
        case STMT_PRINT:
            break;
        case STMT_BLOCK:
            stmt_codegen(s->body);
            break;
    }
    stmt_codegen(s->next);
}

void decl_codegen(struct decl * d){
    // function epilogues must have unique labels so that return statemtnts can jump there easily
    if (!d) return;
    
    //printf("%d\n",d->type->kind);
    if (d->type->kind == TYPE_FUNCTION){
       // printf("in type func of decl codegen\n");

        if (d->code /*if this is the function defintion*/){
            //if you have more than three parameters, you are out of luck with our compiler
            printf(".%s:\n", d->name);

            printf("PUSHQ %%rbp\n");
            printf("MOVQ %%rsp, %%rbp\n");

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
    } else {
        if (decl_codegen_called_by_stmt == 0 && data_label_emitted == 0){
            data_label_emitted++;
            printf(".data\n");
        }
        if (decl_codegen_called_by_stmt == 0){
            printf("%s: ", d->name);
            if (d->type->kind==TYPE_STRING){
                printf(".string ");
                if (d->value){
                    printf("\"%s\"\n",d->value->string_literal);
                } else{
                    printf("\n");
                }
            } else if (d->type->kind != TYPE_ARRAY){
                printf(".quad ");
                if (d->value){
                    printf("%d\n",d->value->literal_value);
                } else{
                    printf("\n");
                }
            } else {
                if (d->type->subtype->kind==TYPE_STRING){
                    printf(".string");
                    struct expr * arg  = d->value;
                    int goneAround =0;
                    while (arg&&arg->left){
                        if (goneAround !=0){
                            printf(",");
                        }
                        printf(" \"%s\"",arg->left->string_literal);
                        goneAround=1;
                        arg=arg->right;
                    }
                    printf("\n");
                } else {
                    printf(".string");
                    struct expr * arg  = d->value;
                    int goneAround =0;
                    while (arg&&arg->left){
                        if (goneAround !=0){
                            printf(",");
                        }
                        printf(" %d",arg->left->literal_value);
                        goneAround=1;
                        arg=arg->right;
                    }
                    printf("\n");
                } 
            }
        } else {
            if (d->value){
                expr_codegen(d->value);
                printf("MOVQ %s, %s\n",scratch_name(d->value->reg),symbol_codegen(d->symbol));
                scratch_free(d->value->reg);
            }
        }
        
    }
    decl_codegen(d->next);
}

