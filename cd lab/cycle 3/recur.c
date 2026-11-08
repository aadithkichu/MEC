#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int n;
char prods[10][20];
char input[50];
int ptr = 0;

void add_to_set(char set[], int *size, char val) {
    for (int i = 0; i < *size; i++) {
        if (set[i] == val) return;
    }
    set[(*size)++] = val;
}

int get_rhs_start(const char *prod) {
    if (prod[1] == '-' && prod[2] == '>') return 3;
    return 2;
}

// Compute FIRST set for a non-terminal symbol
void find_first(char symbol, char result[], int *size, int visited[]) {
    if (!isupper(symbol)) {
        add_to_set(result, size, symbol);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (prods[i][0] != symbol || visited[i]) continue;

        int rhs = get_rhs_start(prods[i]);
        if (prods[i][rhs] == '$') {
            add_to_set(result, size, '$');
            continue;
        }

        visited[i] = 1;
        while (prods[i][rhs] != '\0') {
            char temp[20];
            int temp_size = 0, has_epsilon = 0;

            find_first(prods[i][rhs], temp, &temp_size, visited);

            for (int k = 0; k < temp_size; k++) {
                if (temp[k] == '$') has_epsilon = 1;
                else add_to_set(result, size, temp[k]);
            }

            if (!has_epsilon) break;
            rhs++;
            if (prods[i][rhs] == '\0') add_to_set(result, size, '$');
        }
        visited[i] = 0;
    }
}

// Compute FIRST set for an entire RHS string (e.g. FIRST of "TE'")
void find_first_of_string(const char *str, char result[], int *size) {
    if (str[0] == '$' || str[0] == '\0') {
        add_to_set(result, size, '$');
        return;
    }

    int curr = 0;
    while (str[curr] != '\0') {
        char temp[20];
        int temp_size = 0, has_eps = 0;
        int visited[10] = {0};

        find_first(str[curr], temp, &temp_size, visited);

        for (int k = 0; k < temp_size; k++) {
            if (temp[k] == '$') has_eps = 1;
            else add_to_set(result, size, temp[k]);
        }

        if (!has_eps) break;
        curr++;
        if (str[curr] == '\0') add_to_set(result, size, '$');
    }
}

// Forward declaration of recursive parser engine
int parse_non_terminal(char symbol);

// Parse a single symbol (Terminal or Non-Terminal) recursively
int parse_symbol(char symbol) {
    if (!isupper(symbol)) {
        // Terminal Matching Step
        if (symbol == '$') return 1; // Epsilon match

        if (input[ptr] == symbol) {
            printf("Matched Terminal '%c' at index %d\n", symbol, ptr);
            ptr++; // Advance input pointer
            return 1;
        } else {
            return 0; // Terminal mismatch
        }
    } else {
        // Non-Terminal Recursive Descent Call
        return parse_non_terminal(symbol);
    }
}

// Universal Recursive Descent Engine for Non-Terminals
int parse_non_terminal(char symbol) {
    char curr_char = input[ptr];

    for (int i = 0; i < n; i++) {
        if (prods[i][0] != symbol) continue;

        int rhs = get_rhs_start(prods[i]);
        char first_set[20];
        int first_size = 0;

        find_first_of_string(prods[i] + rhs, first_set, &first_size);

        // Check if current input character matches FIRST(RHS)
        int matches = 0;
        int is_nullable = 0;

        for (int k = 0; k < first_size; k++) {
            if (first_set[k] == curr_char) matches = 1;
            if (first_set[k] == '$') is_nullable = 1;
        }

        // If current input token matches FIRST(RHS) OR if RHS is nullable and input hits end/fallback
        if (matches || (is_nullable && curr_char == '\0')) {
            printf("Expand: %c -> %s\n", symbol, prods[i] + rhs);

            // Execute recursive calls symbol-by-symbol down the RHS
            int curr = rhs;
            while (prods[i][curr] != '\0') {
                if (prods[i][curr] == '$') break; // Epsilon rule: nothing to parse

                if (!parse_symbol(prods[i][curr])) {
                    return 0; // Recursive branch failed
                }
                curr++;
            }
            return 1; // Successfully expanded and parsed this non-terminal
        }
    }
    return 0; // No valid production rule matched
}

int main() {
    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter productions (e.g., E->TR, R->+TR, R->$ for epsilon):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prods[i]);
    }

    printf("\nEnter expression to parse: ");
    scanf("%s", input);

    printf("\n--- Recursive Descent Parsing Derivation ---\n");
    char start_symbol = prods[0][0];

    ptr = 0;
    if (parse_non_terminal(start_symbol) && input[ptr] == '\0') {
        printf("\nResult: Input String Successfully Parsed!\n");
    } else {
        printf("\nResult: Syntax Error at index %d ('%c')\n", ptr, input[ptr]);
    }

    return 0;
}
