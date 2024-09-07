%{
#include <stdio.h>
%}

%option noyywrap

%%

[ \t\n]+         /* Skip whitespace */
select          { printf("SELECT\n"); }
from            { printf("FROM\n"); }
where           { printf("WHERE\n"); }
[[:alnum:]_]+   { printf("IDENTIFIER: %s\n", yytext); }
.               { /* Ignore other characters */ }

%%

int main() {
    yylex();
    return 0;
}
