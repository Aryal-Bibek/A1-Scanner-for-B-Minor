%{
#include "token.h"
#include "helper.h"
%}

%option nounput
%option noinput
%option yylineno

DIGIT  [0-9]
LETTER [a-zA-Z]
%%
(" "|\t|\n|\/\/.*|\/*.*\*\/)  /* skip whitespace */

 \+                             { return TOKEN_ADD;}
 \*                             { return TOKEN_MULTIPLY;}
\-                               { return TOKEN_SUBTRACT;}
\/                               { return TOKEN_DIVIDE;}
%                               { return TOKEN_MODULO;}
\^                               { return TOKEN_EXPONENT;}
!                               { return TOKEN_NOT;}
\+\+                              { return TOKEN_INCREMENT;}
\-\-                              { return TOKEN_DECREMENT;}
while                           { return TOKEN_WHILE; }
for                             { return TOKEN_FOR;}
char                            { return TOKEN_CHAR;}
boolean                         { return TOKEN_BOOLEAN;}
string                          { return TOKEN_STRING;}
integer                         { return TOKEN_INTEGER;}
void                            { return TOKEN_VOID;}
true                            { return TOKEN_TRUE;}
false                           { return TOKEN_FALSE;}
array                           { return TOKEN_ARRAY;}
print                           { return TOKEN_PRINT;}
if                              { return TOKEN_IF;}
else                            { return TOKEN_ELSE;}
function                        { return TOKEN_FUNCTION;}
return                          { return TOKEN_RETURN;}
(_|{LETTER})(_|{LETTER}|{DIGIT})*                                    { return TOKEN_IDENT; }
{DIGIT}+                        { return TOKEN_INTEGER_LITERAL; }
\'({LETTER}|{DIGIT})\'         { return TOKEN_CHAR_LITERAL;}
\"({LETTER}|{DIGIT})*\"               { return TOKEN_STRING_LITERAL;}
==                              { return TOKEN_EQ;}
!=                              { return TOKEN_NE;}
>=                              { return TOKEN_GE;}
\<=                              { return TOKEN_LE;}
=                               { return TOKEN_ASSIGNMENT;}
>                               { return TOKEN_GT;}
\<                               { return TOKEN_LT;}
;                               { return TOKEN_SEMICOLON;}
&&                              { return TOKEN_AND;}
\|\|                            { return TOKEN_OR;}
\(                              { return TOKEN_LB;}    
\)                              { return TOKEN_RB;}
\{                              { return TOKEN_CLB;}
\}                              { return TOKEN_CRB;}
\[                              {return TOKEN_SLB;}
\]                              {return TOKEN_SRB;}
.                               { return TOKEN_ERROR;}
%%

int yywrap() { return 1; }