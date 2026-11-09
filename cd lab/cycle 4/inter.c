#include <stdio.h>
#include <string.h>
#include <ctype.h>

int prec(char c) {
    if (c=='*' || c=='/') return 2 ;
    if (c=='+' || c=='-') return 1 ;
    return 0 ;
}

int stack[20] , opstack[20], top = -1 , optop = -1 , counter = 0 ;

void pop() {
    char topc = opstack[optop--] ;
    char first = stack[top--] ;
    char second = stack[top--];
    if (isdigit(first) && isdigit(second)) printf("t%d = t%c %c t%c\n" , counter , second , topc , first) ;
    else if (isdigit(first)) printf("t%d = %c %c t%c\n" , counter , second , topc , first) ;
    else if (isdigit(second)) printf("t%d = t%c %c %c\n" , counter , second , topc , first) ;
    else printf("t%d = %c %c %c\n" , counter , second , topc , first) ;
    stack[++top] = counter+'0' ;
    counter++;
}

int main() {
    char input[20] ;
    scanf("%s",input);
    for (int i=0 ; i<strlen(input) ; i++) {
        if (isalpha(input[i])) stack[++top] = input[i] ;
        else {
            if (input[i]==')') {
                while (opstack[optop]!='(') {
                    pop();
                }
                optop--;
            }
            else if (input[i]=='(' || input[i]=='^') opstack[++optop] = input[i] ;
            else {
                while (optop>=0 && prec(opstack[optop]) >= prec(input[i])) {
                    pop();
                }
                opstack[++optop] = input[i] ;
            }
        }
    }
    while (optop>=0) {
        pop();
    }

    return 0;
}