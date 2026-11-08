#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char stack[50], ip[50], opt[10][10][2], ter[10];
    int i, j, k, n, top = 0, col = -1, row = -1;

    printf("Enter the no. of terminals: ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter the terminals (e.g., i+*$): ");
    scanf("%s", ter);

    printf("\nEnter the precedence table values (<, >, =):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Value for %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }

    printf("\n**** OPERATOR PRECEDENCE TABLE ****\n");
    for (i = 0; i < n; i++) {
        printf("\t%c", ter[i]);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("\n%c", ter[i]);
        for (j = 0; j < n; j++) {
            printf("\t%c", opt[i][j][0]);
        }
    }
    printf("\n\n");

    stack[top] = '$';
    stack[top + 1] = '\0';

    printf("Enter the input string (ending with $): ");
    scanf("%s", ip);

    i = 0;
    printf("\n%-20s %-20s %-20s\n", "STACK", "INPUT STRING", "ACTION");

    while (i < strlen(ip)) {
        // Print current stack and input state
        for (k = 0; k <= top; k++) printf("%c", stack[k]);
        printf("\t\t\t");
        for (k = i; k < strlen(ip); k++) printf("%c", ip[k]);
        printf("\t\t\t");

        // Find top-most terminal on the stack
        int get_top_ter = top;
        while (get_top_ter >= 0) {
            int found = 0;
            for (k = 0; k < n; k++) {
                if (stack[get_top_ter] == ter[k]) {
                    col = k;
                    found = 1;
                    break;
                }
            }
            if (found) break;
            get_top_ter--;
        }

        // Find current input symbol in terminals
        row = -1;
        for (k = 0; k < n; k++) {
            if (ip[i] == ter[k]) {
                row = k;
                break;
            }
        }

        if (col == -1 || row == -1) {
            printf("Error: Invalid terminal symbol encountered.\n");
            break;
        }

        if (stack[top] == '$' && ip[i] == '$') {
            printf("String is accepted\n");
            break;
        } 
        else if (opt[col][row][0] == '<' || opt[col][row][0] == '=') {
            stack[++top] = opt[col][row][0];
            stack[++top] = ip[i];
            stack[top + 1] = '\0';
            printf("Shift %c\n", ip[i]);
            i++;
        } 
        else if (opt[col][row][0] == '>') {
            while (top > 0 && stack[top] != '<') {
                --top;
            }
            if (top > 0) {
                --top; // Remove '<'
            }
            stack[top + 1] = '\0';
            printf("Reduce\n");
        } 
        else {
            printf("String is not accepted\n");
            break;
        }
    }

    return 0;
}
