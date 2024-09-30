#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "helper.h"

/* You may use this file to add any helper functions you need. */

void printToken(int token, int line, char *text){
    switch(token){
     case 0:
        printf("TOKEN_EOF\n");
        break;
    
    case 1:
        printf("TOKEN_ADD\n");
        break;

    case 2:
        printf("TOKEN_MULTIPLY\n");
        break;

    case 3:
        printf("TOKEN_SUBTRACT\n");
        break;

    case 4:
        printf("TOKEN_DIVIDE\n");
        break;

    case 5:
        printf("TOKEN_MODULO\n");
        break;

    case 6:
        printf("TOKEN_EXPONENT\n");
        break;

    case 7:
        printf("TOKEN_NOT\n");
        break;

    case 8:
        printf("TOKEN_INCREMENT\n");
        break;

    case 9:
        printf("TOKEN_DECREMENT\n");
        break;

    case 10:
        printf("TOKEN_WHILE\n");
        break;

    case 11:
        printf("TOKEN_FOR\n");
        break;

    case 12:
        if(strlen(text) > 256){
            printf("TOKEN_ERROR, identifier exceeds 256 characters %s at line %d\n",text,line);
            exit(1);
        }
        else{
            printf("TOKEN_IDENT: %s\n", text);
            break;
        }

    case 13:
        printf("TOKEN_INTEGER_LITERAL: %s\n", text);
        break;

    case 14:
        printf("TOKEN_BOOLEAN\n");
        break;

    case 15:
        printf("TOKEN_STRING\n");
        break;

    case 16:
        printf("TOKEN_CHAR\n");
        break;

    case 17:
        printf("TOKEN_INTEGER\n");
        break;

    case 18:
        printf("TOKEN_VOID\n");
        break;

    case 19:
        printf("TOKEN_TRUE\n");
        break;

    case 20:
        printf("TOKEN_FALSE\n");
        break;

    case 21:
        printf("TOKEN_ARRAY\n");
        break;

    case 22:
        if(text[1] == '\\'){
            printf("TOKEN_CHAR_LITERAL: %c%c\n",text[1],text[2]);
            break;
        }
        else{
            printf("TOKEN_CHAR_LITERAL: %c\n",text[1]);
            break;
        }
    case 23:
        char unquoted_string[300];
        strncpy(unquoted_string, text +1 , strlen(text) -2);
        unquoted_string[strlen(text) - 2] = '\0';
        printf("TOKEN_STRING_LITERAL: %s\n",unquoted_string);
        break;

    case 24:
        printf("TOKEN_PRINT\n");
        break;

    case 25:
        printf("TOKEN_IF\n");
        break;

    case 26:
        printf("TOKEN_ELSE\n");
        break;

    case 27:
        printf("TOKEN_FUNCTION\n");
        break;

    case 28:
        printf("TOKEN_RETURN\n");
        break;

    case 29:
        printf("TOKEN_EQ\n");
        break;

    case 30:
        printf("TOKEN_NE\n");
        break;

    case 31:
        printf("TOKEN_GE\n");
        break;

    case 32:
        printf("TOKEN_LE\n");
        break;

    case 33:
        printf("TOKEN_ASSIGNMENT\n");
        break;

    case 34:
        printf("TOKEN_GT\n");
        break;

    case 35:
        printf("TOKEN_LT\n");
        break;

    case 36:
        printf("TOKEN_SEMICOLON\n");
        break;

    case 37:
        printf("TOKEN_AND\n");
        break;

    case 38:
        printf("TOKEN_OR\n");
        break;

    case 39:
        printf("TOKEN_LB\n");
        break;

    case 40:
        printf("TOKEN_RB\n");
        break;

    case 41:
        printf("TOKEN_CLB\n");
        break;

    case 42:
        printf("TOKEN_CRB\n");
        break;
    
     case 43:
        printf("TOKEN_SLB\n");
        break;
    
     case 44:
        printf("TOKEN_SRB\n");
        break;
    
    case 45:
        printf("TOKEN_COLON\n");
        break;

    case 46:
        printf("TOKEN_COMMA\n");    
        break;

     case 100:
        printf("TOKEN_ERROR, unexpected character %s at line %d\n",text,line);
        exit(1);
}
}
