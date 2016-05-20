default: all
Program1 : Program1.c
	gcc -Wall -ansi -o Program1 Program1.c
Program2 : Program2.c
	gcc -Wall -ansi -o Program2 Program2.c
Program3 : Program3.c
	gcc -Wall -ansi -o Program3 Program3.c
Program4 : Program4.c
	gcc -Wall -ansi -o Program4 Program4.c
Program5 : Program5.c
	gcc -Wall -ansi -o Program5 Program5.c
Program6 : Program6.c
	gcc -Wall -ansi -o Program6 Program6.c
all:
	gcc -Wall -ansi -o Program1 Program1.c
	gcc -Wall -ansi -o Program2 Program2.c
	gcc -Wall -ansi -o Program3 Program3.c
	gcc -Wall -ansi -o Program4 Program4.c
	gcc -Wall -ansi -o Program5 Program5.c
	gcc -Wall -ansi -o Program6 Program6.c
