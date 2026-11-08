#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int n;
char prods[10][20];
char input[50];
int max_ptr = 0;

int get_rhs_start(const char *prod) {
    if (prod[1] == '-' && prod[2] == '>') return 3;
    return 2;
}

int parse_symbol(char symbol, int *ptr);
int parse_non_terminal(char symbol, int *ptr);

int parse_symbol(char symbol, int *ptr) {
    if (*ptr > max_ptr) max_ptr = *ptr;

    if (!isupper(symbol)) {
        if (symbol == '$') return 1; // Epsilon match

        if (input[*ptr] == symbol) {
            (*ptr)++; // Match terminal
            if (*ptr > max_ptr) max_ptr = *ptr;
            return 1;
        }
        return 0; // Mismatch
    }
    return parse_non_terminal(symbol, ptr);
}

int parse_non_terminal(char symbol, int *ptr) {
    int initial_ptr = *ptr;

    for (int i = 0; i < n; i++) {
        if (prods[i][0] != symbol) continue;

        *ptr = initial_ptr; // Reset pointer for this alternative
        int rhs = get_rhs_start(prods[i]);
        int success = 1;

        int curr = rhs;
        while (prods[i][curr] != '\0') {
            if (prods[i][curr] == '$') break;

            if (!parse_symbol(prods[i][curr], ptr)) {
                success = 0;
                break;
            }
            curr++;
        }

        if (success) {
            printf("Applied: %c -> %s\n", symbol, prods[i] + rhs);
            return 1;
        }
    }

    *ptr = initial_ptr; // Reset on failure
    return 0;
}

int main() {
    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter productions (e.g., S->cAd, A->ab, A->a, use $ for epsilon):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prods[i]);
    }

    printf("\nEnter input expression: ");
    scanf("%s", input);

    int ptr = 0;
    max_ptr = 0;
    char start_symbol = prods[0][0];

    printf("\n--- Recursive Descent Derivation ---\n");
    if (parse_non_terminal(start_symbol, &ptr) && input[ptr] == '\0') {
        printf("\nResult: Input String Successfully Parsed!\n");
    } else {
        printf("\nResult: Syntax Error near index %d ('%c')\n", max_ptr, input[max_ptr]);
    }

    return 0;
}