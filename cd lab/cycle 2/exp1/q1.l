%{
#include <stdio.h>
%}

%%
.*AADI.*\n   { printf("NOT ACCEPTED (Contains AADI)\n"); }
.*\n         { printf("ACCEPTED (Does not contain AADI)\n"); }
%%

int main()
{
    printf("Enter a string: ");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}