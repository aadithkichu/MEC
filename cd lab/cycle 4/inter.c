#include <ctype.h>
#include <stdio.h>

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int main() {
    char expr[50] = "a+b*c", result_var[] = "x";
    char op_stack[20], val_stack[20][10];
    int op_top = -1, val_top = -1, t = 1;

    printf("Input Expression: %s = %s\n\n", result_var, expr);
    printf("Generated Intermediate Code (Three-Address Code):\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; expr[i]; i++) {
        if (isalnum(expr[i])) {
            // Push operand directly to val_stack as string
            val_top++;
            val_stack[val_top][0] = expr[i];
            val_stack[val_top][1] = '\0';
        } else {
            // Process higher or equal precedence operators
            while (op_top != -1 && precedence(op_stack[op_top]) >= precedence(expr[i])) {
                printf("t%d = %s %c %s\n", t, val_stack[val_top - 1], op_stack[op_top--], val_stack[val_top]);
                sprintf(val_stack[--val_top], "t%d", t++);
            }
            op_stack[++op_top] = expr[i];
        }
    }

    // Flush remaining operators
    while (op_top != -1) {
        printf("t%d = %s %c %s\n", t, val_stack[val_top - 1], op_stack[op_top--], val_stack[val_top]);
        sprintf(val_stack[--val_top], "t%d", t++);
    }

    printf("%s = %s\n", result_var, val_stack[val_top]);
    return 0;
}
