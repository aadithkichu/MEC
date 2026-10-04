#include <stdio.h>

int n, noalpha, n_final;
int e_adj[20][20];         // e_adj[u][v] = 1 for epsilon transition
int trans[20][10][20];     // trans[u][sym_idx][v] = 1 for symbol transition
int e_close[20][20];       // e_close[i][j] = 1 if qj is in e-closure(qi)
int is_final[20];          // Stores original final states
char alpha[10];

// DFS to compute epsilon-closure for a state
void dfs(int start, int curr) {
    e_close[start][curr] = 1;
    for (int i = 1; i <= n; i++) {
        if (e_adj[curr][i] && !e_close[start][i]) {
            dfs(start, i);
        }
    }
}

int main() {
    int t;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of alphabets (excluding 'e'): ");
    scanf("%d", &noalpha);
    printf("Enter alphabets: ");
    for (int i = 0; i < noalpha; i++) {
        scanf(" %c", &alpha[i]);
    }

    printf("Enter number of transitions: ");
    scanf("%d", &t);
    printf("Enter transitions (format: from symbol to):\n");
    for (int i = 0; i < t; i++) {
        int u, v;
        char sym;
        scanf("%d %c %d", &u, &sym, &v);

        if (sym == 'e' || sym == 'E') {
            e_adj[u][v] = 1;
        } else {
            for (int a = 0; a < noalpha; a++) {
                if (alpha[a] == sym) trans[u][a][v] = 1;
            }
        }
    }

    printf("Enter number of final states: ");
    scanf("%d", &n_final);
    printf("Enter final states: ");
    for (int i = 0; i < n_final; i++) {
        int f;
        scanf("%d", &f);
        is_final[f] = 1;
    }

    // Step 1: Compute e-closure for all states
    for (int i = 1; i <= n; i++) {
        dfs(i, i);
    }

    // Step 2: Compute delta'(q, a) = e-closure( delta( e-closure(q), a ) )
    printf("\n--- Transitions of NFA without Epsilon ---\n");
    for (int i = 1; i <= n; i++) {
        for (int a = 0; a < noalpha; a++) {
            int result[20] = {0};

            for (int q = 1; q <= n; q++) {
                if (e_close[i][q]) {               // q in e-closure(i)
                    for (int r = 1; r <= n; r++) {
                        if (trans[q][a][r]) {      // r in delta(q, a)
                            for (int w = 1; w <= n; w++) {
                                if (e_close[r][w]) // w in e-closure(r)
                                    result[w] = 1;
                            }
                        }
                    }
                }
            }

            printf("delta'(q%d, %c) = { ", i, alpha[a]);
            for (int k = 1; k <= n; k++) {
                if (result[k]) printf("q%d ", k);
            }
            printf("}\n");
        }
    }

    // Step 3: Find new final states
    printf("\nNew Final States: { ");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (e_close[i][j] && is_final[j]) {
                printf("q%d ", i);
                break;
            }
        }
    }
    printf("}\n");

    return 0;
}