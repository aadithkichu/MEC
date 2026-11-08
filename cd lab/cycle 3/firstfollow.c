#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n;
char prods[10][20];

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

        visited[i] = 1; // Mark production active on current expansion path

        while (prods[i][rhs] != '\0') {
            char temp[20];
            int temp_size = 0;
            int has_epsilon = 0;

            find_first(prods[i][rhs], temp, &temp_size, visited);

            for (int k = 0; k < temp_size; k++) {
                if (temp[k] == '$') {
                    has_epsilon = 1;
                } else {
                    add_to_set(result, size, temp[k]);
                }
            }

            if (!has_epsilon) break;

            rhs++;
            if (prods[i][rhs] == '\0') {
                add_to_set(result, size, '$');
            }
        }

        visited[i] = 0; // Unmark during backtracking
    }
}

void find_follow(char symbol, char result[], int *size, int visited[]) {
    // Start symbol receives '$' (end of input marker)
    if (prods[0][0] == symbol) {
        add_to_set(result, size, '$');
    }

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;

        int rhs = get_rhs_start(prods[i]);
        int len = strlen(prods[i]);

        for (int j = rhs; j < len; j++) {
            if (prods[i][j] != symbol) continue;

            int next = j + 1;
            int all_nullable = 1;

            while (next < len) {
                char temp[20];
                int temp_size = 0;
                int has_epsilon = 0;
                int first_visited[10] = {0};

                find_first(prods[i][next], temp, &temp_size, first_visited);

                for (int k = 0; k < temp_size; k++) {
                    if (temp[k] == '$') {
                        has_epsilon = 1;
                    } else {
                        add_to_set(result, size, temp[k]);
                    }
                }

                if (!has_epsilon) {
                    all_nullable = 0;
                    break;
                }
                next++;
            }

            // If symbol is at end OR all remaining RHS symbols derive epsilon
            if ((next == len || all_nullable) && prods[i][0] != symbol) {
                visited[i] = 1;
                find_follow(prods[i][0], result, size, visited);
                visited[i] = 0;
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter productions (e.g., E=E+T or E->E+T, use $ for epsilon):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prods[i]);
    }

    int choice;
    do {
        char target;
        printf("\nEnter element whose FIRST & FOLLOW is to be found: ");
        scanf(" %c", &target);

        char first_set[20], follow_set[20];
        int first_size = 0, follow_size = 0;
        int visited_first[10] = {0};
        int visited_follow[10] = {0};

        find_first(target, first_set, &first_size, visited_first);
        printf("First(%c) = { ", target);
        for (int i = 0; i < first_size; i++) {
            printf("%c ", first_set[i]);
        }
        printf("}\n");

        if (isupper(target)) {
            find_follow(target, follow_set, &follow_size, visited_follow);
            printf("Follow(%c) = { ", target);
            for (int i = 0; i < follow_size; i++) {
                printf("%c ", follow_set[i]);
            }
            printf("}\n");
        } else {
            printf("Follow(%c) is not defined for terminals.\n", target);
        }

        printf("Continue (1 to repeat / 0 to exit)? ");
        scanf("%d", &choice);
    } while (choice == 1);

    return 0;
}
