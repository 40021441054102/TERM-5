%{
#include <stdio.h>
%}

%option noyywrap

num     [0-9]+
id      [a-zA-Z_][a-zA-Z_0-9]*

%%

"real"          { printf("TYPE_REAL\n"); }
"integer"       { printf("TYPE_INTEGER\n"); }
"char"          { printf("TYPE_CHAR\n"); }
"array"         { printf("TYPE_ARRAY\n"); }
"simple"        { printf("TYPE_SIMPLE\n"); }
"type"          { printf("TYPE_TYPE\n"); }
"of"            { printf("TYPE_OF\n"); }
"["             { printf("TYPE_OPEN_BRACKET\n"); }
"]"             { printf("TYPE_CLOSE_BRACKET\n"); }
"^"             { printf("TYPE_POINTER\n"); }
"_"             { printf("TYPE_DOTDOT\n"); }
{id}            { printf("TYPE_ID\n"); }
{num}           { printf("TYPE_NUM\n"); }
\n              { /* Ignore newline characters */ }
.               { /* Ignore all other characters */ }

%%

int main() {
    yylex();
    return 0;
}
