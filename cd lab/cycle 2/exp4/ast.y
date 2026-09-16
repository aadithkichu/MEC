%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char data[20];
    struct node *left;
    struct node *right;
};

struct node *createNode(char *data,
                        struct node *left,
                        struct node *right);

void preorder(struct node *root);

int yylex();
void yyerror(char *s);
%}

%union
{
    char *str;
    struct node *node;
}

%token <str> ID
%type <node> E T F

%left '+' '-'
%left '*' '/'

%%
start:
      E '\n'
      {
          printf("Abstract Syntax Tree:\n");
          preorder($1);
          printf("\n");
      }
    ;

E:
      E '+' T
      {
          $$ = createNode("+", $1, $3);
      }
    | E '-' T
      {
          $$ = createNode("-", $1, $3);
      }
    | T
      {
          $$ = $1;
      }
    ;

T:
      T '*' F
      {
          $$ = createNode("*", $1, $3);
      }
    | T '/' F
      {
          $$ = createNode("/", $1, $3);
      }
    | F
      {
          $$ = $1;
      }
    ;

F:
      '(' E ')'
      {
          $$ = $2;
      }
    | ID
      {
          $$ = createNode($1, NULL, NULL);
      }
    ;
%%

struct node *createNode(char *data,
                         struct node *left,
                         struct node *right)
{
    struct node *newnode;

    newnode = (struct node *)malloc(sizeof(struct node));

    strcpy(newnode->data, data);
    newnode->left = left;
    newnode->right = right;

    return newnode;
}

void preorder(struct node *root)
{
    if(root != NULL)
    {
        printf("%s ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main()
{
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    printf("Invalid Expression\n");
}