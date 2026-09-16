%{
#include <stdio.h>

int yylex();
void yyerror(char *s);
%}

%token FOR ID NUM
%token INC DEC
%token LE GE EQ NE

%%
start:
      forstmt '\n'
      {
          printf("Valid FOR Statement\n");
      }
    ;

forstmt:
      FOR '(' init ';' condition ';' increment ')'
    ;

init:
      ID '=' expr
    ;

condition:
      expr relop expr
    ;

increment:
      ID INC
    | ID DEC
    | ID '=' expr
    ;

expr:
      ID
    | NUM
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    ;

relop:
      '<'
    | '>'
    | LE
    | GE
    | EQ
    | NE
    ;
%%

int main()
{
    printf("Enter a FOR statement: ");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    printf("Invalid FOR Statement\n");
}