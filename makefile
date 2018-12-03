all: shell.o
	gcc shell.o

clean:
	rm -f *~ *.gch* a.out *.o *.txt *#*

run:
	./a.out

shell.o: shell.c shell.h
	gcc -c shell.c
