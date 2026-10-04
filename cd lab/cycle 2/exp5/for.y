%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%token FOR ID NUM INC DEC LE GE EQ NE

%left '+' '-'
%left '*' '/'

%%
start:
      forstmt '\n'    { printf("Valid FOR Statement\n"); exit(0); }
    ;

forstmt:
      FOR '(' init ';' condition ';' increment ')' body
    ;

init:
      ID '=' expr
    | /* empty */
    ;

condition:
      expr relop expr
    | /* empty */
    ;

increment:
      ID INC
    | INC ID
    | ID DEC
    | DEC ID
    | ID '=' expr
    | /* empty */
    ;

body:
      '{' stmt_list '}'
    | stmt
    | ';'
    ;

stmt_list:
      stmt_list stmt
    | /* empty */
    ;

stmt:
      ID '=' expr ';'
    | forstmt
    ;

expr:
      ID
    | NUM
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    ;

relop:
      '<' | '>' | LE | GE | EQ | NE
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
    exit(0);
}