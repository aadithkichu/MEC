```
mec@CL-1-43:~/CS7B/cycle 4$ ./a.out
Input Expression: x = a+b*c

Generated Intermediate Code (Three-Address Code):
--------------------------------------------------
t1 = b * c
t2 = a + t1
x = t2
```

```
mec@CL-1-43:~/CS7B/cycle 4$ ./a.out
Enter the Three-Address Code (type 'exit' to terminate):
t1 = b * c
t2 = a + t1
x = t2
exit

--- Generated 8086 Assembly Code ---
.CODE
MAIN PROC
; 3AC: t1 = b * c
    MOV AX, b
    MOV BX, c
    MUL BX
    MOV t1, AX
; 3AC: t2 = a + t1
    MOV AX, a
    ADD AX, t1
    MOV t2, AX
; 3AC: x = t2
    MOV AX, t2
    MOV x, AX
    MOV AH, 4CH
    INT 21H
MAIN ENDP
END MAIN
```