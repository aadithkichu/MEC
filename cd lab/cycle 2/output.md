```
aadith@aadith:~/Documents/MEC/cd lab/cycle 2/exp1$ gcc lex.yy.c -ll -o q1 && ./q1
Enter a string: helloAADIworld
String contains AADI - NOT ACCEPTED

helloworld
String does not contain AADI - ACCEPTED

```

```
aadith@aadith:~/Documents/MEC/cd lab/cycle 2/exp2$ yacc -d q2.y
lex q2.l
gcc y.tab.c lex.yy.c -ll -o q2
./q2
Enter a variable: helo
Valid Variable
2hi
Invalid Variable

```
```
aadith@aadith:~/Documents/MEC/cd lab/cycle 2/exp3$ yacc -d calc.y
lex calc.l
gcc y.tab.c lex.yy.c -ll -o calc
./calc
Enter an expression: 3*1
Result = 3
4++2
Invalid Expression

```
```
aadith@aadith:~/Documents/MEC/cd lab/cycle 2/exp4$ yacc -d ast.y
lex ast.l
gcc y.tab.c lex.yy.c -ll -o ast
./ast
Enter an expression: a+b*c-d
Abstract Syntax Tree:
- + a * b c d 
```
```
aadith@aadith:~/Documents/MEC/cd lab/cycle 2/exp5$ ./forcheck
Enter a FOR statement: for(i=0;i<10;i++)
Valid FOR Statement
for(i=0;i<10)
Invalid FOR Statement
```
