%{
#include <stdio.h>

int single_line_count = 0;
int multi_line_count = 0;
%}

/* Exclusive start condition for multi-line comment state */
%x MULTI_LINE_COMMENT

%%

"//" Consider single-line comments until newline
"//".* {
    single_line_count++;
    printf("Single-Line Comment #%d: %s\n", single_line_count, yytext);
}

"/*" Begin multi-line comment state
"/*" {
    multi_line_count++;
    printf("Multi-Line Comment #%d: %s", multi_line_count, yytext);
    BEGIN(MULTI_LINE_COMMENT);
}

<MULTI_LINE_COMMENT>"*/" {
    printf("%s\n", yytext);
    BEGIN(INITIAL);
}

<MULTI_LINE_COMMENT>.|\n {
    printf("%s", yytext);
}

.|\n { /* Ignore non-comment characters */ }

%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *fp = fopen(argv[1], "r");
        if (!fp) {
            perror("File opening failed");
            return 1;
        }
        yyin = fp;
    }

    yylex();

    printf("\n--- SUMMARY ---\n");
    printf("Total Single-Line Comments: %d\n", single_line_count);
    printf("Total Multi-Line Comments : %d\n", multi_line_count);
    printf("Total Comments Found      : %d\n", single_line_count + multi_line_count);

    return 0;
}