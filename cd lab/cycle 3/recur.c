#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n;
char prods[10][20];
char input[50];
char current_form[100];

int parse_symbol(char symbol, int *ptr);
int parse_non_terminal(char symbol, int *ptr);

void replace_leftmost(char symbol, const char *rhs) {
    char temp[100] = "";
    int len = strlen(current_form);
    int replaced = 0;

    for (int i = 0; i < len; i++) {
        if (current_form[i] == symbol && !replaced) {
            if (strcmp(rhs, "$") != 0) {
                strcat(temp, rhs);
            }
            replaced = 1;
        } else {
            int cur_len = strlen(temp);
            temp[cur_len] = current_form[i];
            temp[cur_len + 1] = '\0';
        }
    }
    strcpy(current_form, temp);
}

int parse_symbol(char symbol, int *ptr) {
    if (symbol == '$') return 1;

    if (!isupper(symbol)) {
        if (input[*ptr] == symbol) {
            (*ptr)++;
            return 1;
        }
        return 0;
    }

    return parse_non_terminal(symbol, ptr);
}

int parse_non_terminal(char symbol, int *ptr) {
    int start_ptr = *ptr;

    for (int i = 0; i < n; i++) {
        if (prods[i][0] != symbol) continue;

        *ptr = start_ptr;
        int success = 1;

        // Save state of derivation string in case this rule fails
        char backup_form[100];
        strcpy(backup_form, current_form);

        // Replace leftmost occurrence of 'symbol' with RHS
        replace_leftmost(symbol, &prods[i][3]);
        printf("=> %s\n", current_form);

        for (int j = 3; prods[i][j] != '\0'; j++) {
            if (!parse_symbol(prods[i][j], ptr)) {
                success = 0;
                break;
            }
        }

        if (success) return 1;

        // Restore derivation string on failure
        strcpy(current_form, backup_form);
    }

    *ptr = start_ptr;
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

    current_form[0] = start_symbol;
    current_form[1] = '\0';

    printf("\n--- Sentential Form Derivation ---\n");
    printf("%s\n", current_form);

    if (parse_non_terminal(start_symbol, &ptr) && input[ptr] == '\0') {
        printf("\nResult: Input String Successfully Parsed!\n");
    } else {
        printf("\nResult: Syntax Error at index %d ('%c')\n", ptr, input[ptr]);
    }

    return 0;
}
