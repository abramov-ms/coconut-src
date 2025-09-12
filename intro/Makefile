all: main ub
	gcc main.o ub.o -fsanitize=undefined -o main

main: main.c
	gcc main.c -fsanitize=undefined -c -o main.o

ub: ub.c
	gcc ub.c -fsanitize=undefined -c -o ub.o

clean:
	rm -f ub.o main.o main
