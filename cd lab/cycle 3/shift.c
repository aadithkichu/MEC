#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int num_prods;
char prods[10][20];
char input[50];
char stack[50];
int top = -1;
int ptr = 0;

// Helper to get the start index of RHS (handles S->cAd or S=cAd)
int get_rhs_start(const char *prod) {
    if (prod[1] == '-' && prod[2] == '>') return 3;
    return 2;
}

void print_step(const char *action) {
    stack[top + 1] = '\0';
    printf("$%-15s\t%-15s$\t%s\n", stack, input + ptr, action);
}

void push(char c) {
    stack[++top] = c;
}

void pop(int count) {
    top -= count;
}

// Scans user productions and reduces if RHS matches strictly AT THE TOP of the stack
int reduce() {
    for (int i = 0; i < num_prods; i++) {
        char lhs = prods[i][0];
        int rhs_start = get_rhs_start(prods[i]);
        char *rhs = prods[i] + rhs_start;
        int rhs_len = strlen(rhs);

        // Skip epsilon production ($) in top-of-stack handle checking
        if (rhs_len == 1 && rhs[0] == '$') continue;

        // Check if stack has enough symbols and top of stack matches RHS
        if (top + 1 >= rhs_len) {
            int match = 1;
            for (int k = 0; k < rhs_len; k++) {
                if (stack[top - rhs_len + 1 + k] != rhs[k]) {
                    match = 0;
                    break;
                }
            }

            if (match) {
                pop(rhs_len);
                push(lhs);
                
                char action_msg[50];
                snprintf(action_msg, sizeof(action_msg), "reduce by %c -> %s", lhs, rhs);
                print_step(action_msg);
                return 1; // Reduction made
            }
        }
    }
    return 0; // No handle found at top of stack
}

int main() {
    printf("Enter number of productions: ");
    if (scanf("%d", &num_prods) != 1) return 0;

    printf("Enter productions (e.g., S->cAd, A->ab, A->a, use $ for epsilon):\n");
    for (int i = 0; i < num_prods; i++) {
        scanf("%s", prods[i]);
    }

    printf("\nEnter input expression: ");
    scanf("%s", input);

    char start_symbol = prods[0][0];

    printf("\n%-16s\t%-16s\t%s\n", "STACK", "INPUT", "ACTION");
    printf("---------------------------------------------------\n");
    print_step("initial");

    while (1) {
        // Step 1: Reduce repeatedly as long as top of stack matches any production RHS
        while (reduce());

        // Step 2: Accept condition (Stack contains ONLY start_symbol and input is fully read)
        if (top == 0 && stack[0] == start_symbol && input[ptr] == '\0') {
            print_step("accept");
            printf("\nResult: Input String Successfully Parsed!\n");
            break;
        }

        // Step 3: Shift next token from input onto stack
        if (input[ptr] != '\0') {
            push(input[ptr++]);
            print_step("shift");
        } else {
            printf("\nResult: Syntax Error near index %d ('%c')\n", ptr, input[ptr]);
            break;
        }
    }

    return 0;
}   