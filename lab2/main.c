#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "token.h"
#include "helper.h"

// Generated by scanner.flex
extern FILE *yyin;   // Input file for the scanner to use.
extern int yylex();  // Scans text, returns 0 on EOF.
extern int yylineno; // Line number of the last scanned text.
extern char *yytext; // Actual text scanned
extern int yyparse();

//void run_scan(const char *filename);

void run_parse(const char *filename);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s -scan sourcefile.bminor\n", argv[0]);
        exit(1);
    }

    const char *option = argv[1];
    const char *filename = argv[2];

    if (strcmp(option, "-scan") == 0)
    {
        //run_scan(filename);
    }
	else if (strcmp(option, "-parse") == 0)
	{
		run_parse(filename);
	}
    else if(strcmp(option, "-resolve") == 0)
    {
        run_resolve(filename);
    }
    else
    {
        fprintf(stderr, "Unknown option: %s\n", option);
        exit(1);
    }

    return 0;
}

void run_resolve(const char *filename)
{
	FILE* file = fopen(filename, "r");
	if (file != NULL){
		yyin=file;
		int i=0;
		i=yyparse();
		resolve_tree();
	}
}


void run_parse(const char *filename)
{
	FILE* file = fopen(filename, "r");
	if (file != NULL){
		yyin=file;
		int i=0;
		i=yyparse();
		printf("yyparse return %d\n",i);
	}
}

/*void run_scan(const char *filename)
{
    FILE* file = fopen(filename, "r");
    if (file != NULL){
        yyin = file;
        
        token_t token;
        while((token = yylex()) != 0){
            
       
        printToken(token,yylineno,yytext);

        }
    }
    else {
    printf("File reading error\n");
    }
}*/
