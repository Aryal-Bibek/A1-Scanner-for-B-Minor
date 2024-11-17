
%{
#include "token.h"
#include "helper.h"
%}

%option nounput
%option noinput
%option yylineno

DIGIT  [0-9]
LETTER [a-zA-Z]
SYMBOL   [!@#$%^&*()_+.\/|:;,{}[`~\]><= ]
ESCAPE \\[abcefntrv?0-9'"]

%%
(" "|\t|\n|\/\/.*|\/\*(.|\\n)*\*\/)  {}/* skip whitespace */

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
(_|{LETTER})(_|{LETTER}|{DIGIT})*                                    { yylval.name = strdup(yytext);return TOKEN_IDENT; }
{DIGIT}+                        { yylval.num = strdup(yytext);return TOKEN_INTEGER_LITERAL; }
\'({LETTER}|{DIGIT}|{SYMBOL}|\\.)\' {
    yylval.name = strdup(yytext);
    return TOKEN_CHAR_LITERAL;}
\"({LETTER}|{DIGIT}|{SYMBOL}|'|\\|\\\"|\\\?){0,256}\" {
    yylval.name=strdup(yytext);
    return TOKEN_STRING_LITERAL;}
==                              { return TOKEN_EQ;}
!=                              { return TOKEN_NE;}
>=                              { return TOKEN_GE;}
\<=                             { return TOKEN_LE;}
=                               { return TOKEN_ASSIGNMENT;}
>                               { return TOKEN_GT;}
\<                              { return TOKEN_LT;}
,                               { return TOKEN_COMMA;}
:                               { return TOKEN_COLON;}
;                               { return TOKEN_SEMICOLON;}
&&                              { return TOKEN_AND;}
\|\|                            { return TOKEN_OR;}
\(                              { return TOKEN_LB;}    
\)                              { return TOKEN_RB;}
\{                              { return TOKEN_CLB;}
\}                              { return TOKEN_CRB;}
\[                              { return TOKEN_SLB;}
\]                              { return TOKEN_SRB;}
.                               { return TOKEN_ERROR;}
%%

int yywrap() { return 1; }
