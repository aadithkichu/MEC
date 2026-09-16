%{
#include <stdio.h>
%}

%%
.*AADI.*    { printf("String contains AADI - NOT ACCEPTED\n"); }
.*          { printf("String does not contain AADI - ACCEPTED\n"); }
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