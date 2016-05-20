default: skip
skipList.o: skipList.c skipList.h 
	gcc -Wall -ansi -c skipList.c	
skip: skipList.o
	gcc -Wall -ansi -o skip skipList.o main.c
clean:
	rm *.o
