```
mec@ccf-8:~/Documents/CS7B/operprec$ ./a.out
Enter the no. of terminals :
2

Enter the terminals :
+$

Enter the table values :
Enter the value for + +: >
Enter the value for + $: >
Enter the value for $ +: <
Enter the value for $ $: =

**** OPERATOR PRECEDENCE TABLE ****
	+	$

+	>	>
$	<	=
Enter the input string: +$

STACK			INPUT STRING			ACTION

$			+$			Shift +
$<+			$			Reduce
$			$			String is accepted

```

```
mec@ccf-8:~/Documents/CS7B/cycle3$ ./a.out
Enter the no of productions:
2
Enter the productions:
S=aA
A=b
Enter the elements whose first & follow is to be found: S
First(S)={a}
Follow(S)={$}
Continue(0/1)? 0
```
