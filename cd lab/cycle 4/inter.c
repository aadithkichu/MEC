#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp1, *fp2;
    char op[5], arg1[10], arg2[10], result[10];

    // Open input file for reading
    fp1 = fopen("input.txt", "r");
    if (fp1 == NULL) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }

    // Open output file for writing
    fp2 = fopen("output.txt", "w");
    if (fp2 == NULL) {
        printf("Error: Could not open output.txt\n");
        fclose(fp1);
        return 1;
    }

    // Read quadruples format: (operator, arg1, arg2, result)
    // Ensures exactly 4 items are read per iteration to avoid duplication loops
    while (fscanf(fp1, "%s %s %s %s", op, arg1, arg2, result) == 4) {
        if (strcmp(op, "+") == 0) {
            fprintf(fp2, "MOV R0, %s\n", arg1);
            fprintf(fp2, "ADD R0, %s\n", arg2);
            fprintf(fp2, "MOV %s, R0\n", result);
        } 
        else if (strcmp(op, "*") == 0) {
            fprintf(fp2, "MOV R0, %s\n", arg1);
            fprintf(fp2, "MUL R0, %s\n", arg2);
            fprintf(fp2, "MOV %s, R0\n", result);
        } 
        else if (strcmp(op, "-") == 0) {
            fprintf(fp2, "MOV R0, %s\n", arg1);
            fprintf(fp2, "SUB R0, %s\n", arg2);
            fprintf(fp2, "MOV %s, R0\n", result);
        } 
        else if (strcmp(op, "/") == 0) {
            fprintf(fp2, "MOV R0, %s\n", arg1);
            fprintf(fp2, "DIV R0, %s\n", arg2);
            fprintf(fp2, "MOV %s, R0\n", result);
        } 
        else if (strcmp(op, "=") == 0) {
            fprintf(fp2, "MOV R0, %s\n", arg1);
            fprintf(fp2, "MOV %s, R0\n", result);
        }
    }

    // Close files
    fclose(fp1);
    fclose(fp2);

    printf("Target assembly code successfully generated in output.txt\n");
    return 0;
}
