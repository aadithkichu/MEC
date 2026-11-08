#include <stdio.h>
#include <string.h>

int main() {
    int n;
    char ter[10];
    char opt[10][10]; // Clean 2D array for single operator characters (<, >, =)

    printf("Enter the no. of terminals :\n");
    scanf("%d", &n);

    printf("\nEnter the terminals :\n");
    scanf("%s", ter);

    printf("\nEnter the table values (<, >, =):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Value for %c %c: ", ter[i], ter[j]);
            // Read single character directly (space before %c skips whitespace/newlines)
            scanf(" %c", &opt[i][j]);
        }
    }

    printf("\n**** OPERATOR PRECEDENCE TABLE ****\n");
    for (int i = 0; i < n; i++) {
        printf("\t%c", ter[i]);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("\n%c", ter[i]);
        for (int j = 0; j < n; j++) {
            printf("\t%c", opt[i][j]);
        }
    }
    printf("\n\n");

    char stack[50];
    int top = 0;
    stack[top] = '$';

    char ip[50];
    printf("Enter the input string: ");
    scanf("%s", ip);

    int i = 0;
    printf("\n%-20s %-20s %-20s\n", "STACK", "INPUT STRING", "ACTION");

    while (i < strlen(ip)) {
        // Print stack (filtering out hidden internal relation markers '<' and '=')
        printf("\n");
        for (int k = 0; k <= top; k++) {
            if (stack[k] != '<' && stack[k] != '=') {
                printf("%c", stack[k]);
            }
        }
        printf("\t\t\t%s\t\t\t", ip + i);

        // Find terminal indices for stack[top] and ip[i]
        int row = -1, col = -1;
        for (int k = 0; k < n; k++) {
            if (stack[top] == ter[k]) row = k;
            if (ip[i] == ter[k]) col = k;
        }

        // Accept condition
        if (stack[top] == '$' && ip[i] == '$') {
            printf("String is accepted\n");
            break;
        }

        char rel = opt[row][col];

        // Shift condition
        if (rel == '<' || rel == '=') {
            printf("Shift %c", ip[i]);
            stack[++top] = rel;   // Push precedence marker
            stack[++top] = ip[i]; // Push terminal
            i++;
        } 
        // Reduce condition
        else if (rel == '>') {
            printf("Reduce");
            while (top > 0 && stack[top] != '<') {
                top--;
            }
            if (top > 0) top--; // Pop the '<' marker itself
        } 
        // Invalid relation / Reject condition
        else {
            printf("String is not accepted\n");
            break;
        }
    }

    return 0;
}
