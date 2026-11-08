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
Enter number of productions: 8
Enter productions (e.g., E=E+T or E->E+T, use $ for epsilon):
E=TR
R=+TR
R=$
T=FY
Y=*FY
Y=$
F=(E)
F=i

Enter element whose FIRST & FOLLOW is to be found: E
First(E) = { ( i }
Follow(E) = { $ ) }
Continue (1 to repeat / 0 to exit)? 1

Enter element whose FIRST & FOLLOW is to be found: R
First(R) = { + $ }
Follow(R) = { $ ) }
Continue (1 to repeat / 0 to exit)? 1

Enter element whose FIRST & FOLLOW is to be found: T
First(T) = { ( i }
Follow(T) = { + $ ) }
Continue (1 to repeat / 0 to exit)? 1

Enter element whose FIRST & FOLLOW is to be found: Y
First(Y) = { * $ }
Follow(Y) = { + $ ) }
Continue (1 to repeat / 0 to exit)? 1

Enter element whose FIRST & FOLLOW is to be found: F
First(F) = { ( i }
Follow(F) = { * + $ ) }
Continue (1 to repeat / 0 to exit)? 1

Enter element whose FIRST & FOLLOW is to be found: i
First(i) = { i }
Follow(i) is not defined for terminals.
Continue (1 to repeat / 0 to exit)? 0
```
```
mec@ccf-8:~/Documents/CS7B/cycle3$ ./a.out

Grammar without left recursion
		 E->TE' 
		 E'->+TE'|e 
		 T->FT' 
		 T'->*FT'|e 
		 F->(E)|i
 Enter the input expression: i+i*i
Expressions	 Sequence of production rules
E=TE'                      E->TE'
E=FT'E'                    T->FT'
E=iT'E'                    F->i
E=ieE'                     T'->e
E=i+TE'                    E'->+TE'
E=i+FT'E'                  T->FT'
E=i+iT'E'                  F->i
E=i+i*FT'E'                T'->*FT'
E=i+i*iT'E'                F->i
E=i+i*ieE'                 T'->e
E=i+i*ie                   E'->e

E=i+i*i

```
```
mec@CL-1-43:~/CS7B/cycle 3$ ./a.out
GRAMMAR is E->E+E 
 E->E*E 
 E->(E) 
 E->id
enter input string: 
id+id*id
stack 	 input 	 action

$id	  +id*id$	SHIFT->id
$E	  +id*id$	REDUCE TO E
$E+	   id*id$	SHIFT->symbols
$E+id	     *id$	SHIFT->id
$E+E	     *id$	REDUCE TO E
$E	     *id$	REDUCE TO E
$E*	      id$	SHIFT->symbols
$E*id	        $	SHIFT->id
$E*E	        $	REDUCE TO E
$E	        $	REDUCE TO E
```
