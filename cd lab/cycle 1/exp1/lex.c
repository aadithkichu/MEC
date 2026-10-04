#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Just 5 common keywords for the exam
char keywords[5][10] = {"int", "float", "if", "else", "while"};

int isKeyword(char buffer[]) {
    for (int i = 0; i < 5; i++) {
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char ch, buffer[20];
    FILE *fp = fopen("input.txt", "r");
    int j = 0;

    if (fp == NULL) {
        printf("Error opening file\n");
        exit(0);
    }

    while ((ch = fgetc(fp)) != EOF) {
        // 1. Ignore spaces, tabs, and newlines
        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        // 2. Process Keywords and Identifiers
        if (isalpha(ch) || ch =='_') {
            buffer[j++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_')) {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            ungetc(ch, fp); // Return extra character back to stream
            j = 0;

            if (isKeyword(buffer))
                printf("%s : Keyword\n", buffer);
            else
                printf("%s : Identifier\n", buffer);
        }
        // 3. Process Numbers
        else if (isdigit(ch)) {
            buffer[j++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            ungetc(ch, fp);
            j = 0;

            printf("%s : Number\n", buffer);
        }
        // 4. Process Operators (Handles both 1-char and 2-char operators)
        else if (strchr("+-*/%=<>!", ch)) {
            char next = fgetc(fp);

            if (ch == '>' && next == '=')      printf(">= : Operator\n");
            else if (ch == '<' && next == '=') printf("<= : Operator\n");
            else if (ch == '=' && next == '=') printf("== : Operator\n");
            else if (ch == '!' && next == '=') printf("!= : Operator\n");
            else {
                ungetc(next, fp); // Put 'next' back if it's just a single operator like '>' or '+'
                printf("%c : Operator\n", ch);
            }
        }
        // 5. Process Delimiters
        else if (strchr(";,(){}", ch)) {
            printf("%c : Delimiter\n", ch);
        }
    }

    fclose(fp);
    return 0;
}