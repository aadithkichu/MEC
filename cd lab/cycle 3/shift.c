#include <stdio.h>
#include <string.h>

int main() {
    int n, top = -1, ptr = 0, i, k, len, match;
    char prods[10][20], input[50], stack[50];

    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter productions (e.g., S->cAd):\n");
    for (i = 0; i < n; i++) scanf("%s", prods[i]);

    printf("Enter input expression: ");
    scanf("%s", input);

    printf("\n%-15s\t%-15s\t%s\n", "STACK", "INPUT", "ACTION");
    printf("---------------------------------------------------\n");

    stack[0] = '\0';
    printf("$%-14s\t%-14s$\tinitial\n", stack, input);

    while (1) {
        // Reduce phase
        do {
            match = 0;
            for (i = 0; i < n; i++) {
                char *rhs = prods[i] + 3; // Skip 'A->'
                len = strlen(rhs);

                if (len == 1 && rhs[0] == '$') continue;

                if (top + 1 >= len) {
                    match = 1;
                    for (k = 0; k < len; k++) {
                        if (stack[top - len + 1 + k] != rhs[k]) {
                            match = 0;
                            break;
                        }
                    }

                    if (match) {
                        top -= len;
                        stack[++top] = prods[i][0];
                        stack[top + 1] = '\0';
                        printf("$%-14s\t%-14s$\treduce by %s\n", stack, input + ptr, prods[i]);
                        break;
                    }
                }
            }
        } while (match);

        // Accept check
        if (top == 0 && stack[0] == prods[0][0] && input[ptr] == '\0') {
            printf("$%-14s\t%-14s$\taccept\n", stack, input + ptr);
            printf("\nResult: Input String Successfully Parsed!\n");
            break;
        }

        // Shift phase
        if (input[ptr] != '\0') {
            stack[++top] = input[ptr++];
            stack[top + 1] = '\0';
            printf("$%-14s\t%-14s$\tshift\n", stack, input + ptr);
        } else {
            printf("\nResult: Syntax Error near index %d ('%c')\n", ptr, input[ptr]);
            break;
        }
    }

    return 0;
}
