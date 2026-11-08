#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n;
char prods[10][20];
char input[50];

int parse_symbol(char symbol, int *ptr);
int parse_non_terminal(char symbol, int *ptr);

// Parses a single character (Terminal vs Non-Terminal)
int parse_symbol(char symbol, int *ptr) {
    // 1. Epsilon match
    if (symbol == '$') return 1;

    // 2. Terminal match
    if (!isupper(symbol)) {
        if (input[*ptr] == symbol) {
            (*ptr)++; // Move input pointer forward
            return 1;
        }
        return 0; // Mismatch
    }

    // 3. Non-Terminal (Uppercase letter)
    return parse_non_terminal(symbol, ptr);
}

// Tries productions matching the non-terminal symbol
int parse_non_terminal(char symbol, int *ptr) {
    int start_ptr = *ptr; // Save starting position to rewind if a rule fails

    for (int i = 0; i < n; i++) {
        // Skip productions that don't match the non-terminal
        if (prods[i][0] != symbol) continue;

        *ptr = start_ptr; // Reset pointer for this attempt
        int success = 1;

        // Print Top-Down step immediately when expanding
        printf("Applied: %c -> %s\n", symbol, &prods[i][3]);

        // Loop through RHS symbols starting after '->' (index 3)
        for (int j = 3; prods[i][j] != '\0'; j++) {
            if (!parse_symbol(prods[i][j], ptr)) {
                success = 0;
                break; // Stop checking this rule if any symbol fails
            }
        }

        if (success) return 1; // Successfully parsed this rule
    }

    *ptr = start_ptr; // Rewind pointer if no rules match
    return 0;
}

int main() {
    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter productions (e.g., E->TX, X->+TX, X->$):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prods[i]);
    }

    printf("\nEnter input expression: ");
    scanf("%s", input);

    int ptr = 0;
    char start_symbol = prods[0][0];

    printf("\n--- Recursive Descent Derivation (Top-Down) ---\n");
    if (parse_non_terminal(start_symbol, &ptr) && input[ptr] == '\0') {
        printf("\nResult: Input String Successfully Parsed!\n");
    } else {
        printf("\nResult: Syntax Error at index %d ('%c')\n", ptr, input[ptr]);
    }

    return 0;
}
