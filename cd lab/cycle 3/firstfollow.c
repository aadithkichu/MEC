#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n;
char a[10][20]; // Grammar productions (e.g., E=E+T or E->E+T)

void addToSet(char set[], int *size, char c) {
    for (int k = 0; k < *size; k++) {
        if (set[k] == c) return; // Avoid duplicates
    }
    set[(*size)++] = c;
}

void findFirst(char c, char result[], int *resSize) {
    // If terminal, FIRST is the symbol itself
    if (!isupper(c)) {
        addToSet(result, resSize, c);
        return;
    }

    for (int k = 0; k < n; k++) {
        if (a[k][0] == c) {
            int rhsIdx = 2; // RHS starts after '=' or '->'
            if (a[k][1] == '-' && a[k][2] == '>') rhsIdx = 3;

            // Handle epsilon production directly
            if (a[k][rhsIdx] == '$') {
                addToSet(result, resSize, '$');
                continue;
            }

            // Loop through RHS symbols to handle nullable chains
            while (a[k][rhsIdx] != '\0') {
                char subResult[20];
                int subSize = 0;

                findFirst(a[k][rhsIdx], subResult, &subSize);

                int hasEpsilon = 0;
                for (int s = 0; s < subSize; s++) {
                    if (subResult[s] == '$') {
                        hasEpsilon = 1;
                    } else {
                        addToSet(result, resSize, subResult[s]);
                    }
                }

                // Stop if current symbol is not nullable
                if (!hasEpsilon) break;

                rhsIdx++;
                // If all RHS symbols were nullable, add epsilon
                if (a[k][rhsIdx] == '\0') {
                    addToSet(result, resSize, '$');
                }
            }
        }
    }
}

void findFollow(char c, char result[], int *resSize, int visited[]) {
    // Check for recursion loops in FOLLOW computation
    for (int k = 0; k < n; k++) {
        if (a[k][0] == c && visited[k]) return;
    }

    // Start symbol gets '$'
    if (a[0][0] == c) {
        addToSet(result, resSize, '$');
    }

    for (int i = 0; i < n; i++) {
        int startRhs = (a[i][1] == '-' && a[i][2] == '>') ? 3 : 2;
        int len = strlen(a[i]);

        for (int j = startRhs; j < len; j++) {
            if (a[i][j] == c) {
                int nextIdx = j + 1;
                int allNullable = 1;

                while (nextIdx < len) {
                    char firstOfNext[20];
                    int firstSize = 0;

                    findFirst(a[i][nextIdx], firstOfNext, &firstSize);

                    int hasEpsilon = 0;
                    for (int s = 0; s < firstSize; s++) {
                        if (firstOfNext[s] == '$') {
                            hasEpsilon = 1;
                        } else {
                            addToSet(result, resSize, firstOfNext[s]);
                        }
                    }

                    if (!hasEpsilon) {
                        allNullable = 0;
                        break;
                    }
                    nextIdx++;
                }

                // If symbol is at end or remaining symbols are nullable, add FOLLOW(LHS)
                if ((nextIdx == len || allNullable) && a[i][0] != c) {
                    visited[i] = 1;
                    findFollow(a[i][0], result, resSize, visited);
                    visited[i] = 0;
                }
            }
        }
    }
}

int main() {
    int z;
    char c;

    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter productions (e.g., E=E+T or E->E+T, use $ for epsilon):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", a[i]);
    }

    do {
        printf("\nEnter element whose FIRST & FOLLOW is to be found: ");
        scanf(" %c", &c);

        char firstSet[20], followSet[20];
        int firstSize = 0, followSize = 0;
        int visited[10] = {0};

        findFirst(c, firstSet, &firstSize);
        printf("First(%c) = { ", c);
        for (int i = 0; i < firstSize; i++) {
            printf("%c ", firstSet[i]);
        }
        printf("}\n");

        if (isupper(c)) {
            findFollow(c, followSet, &followSize, visited);
            printf("Follow(%c) = { ", c);
            for (int i = 0; i < followSize; i++) {
                printf("%c ", followSet[i]);
            }
            printf("}\n");
        } else {
            printf("Follow(%c) is not defined for terminals.\n", c);
        }

        printf("Continue (1 to repeat / 0 to exit)? ");
        scanf("%d", &z);
    } while (z == 1);

    return 0;
}