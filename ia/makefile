all: main clean

main: main.o
	gcc -o main main.o

main.o: main_ia.c
	gcc -Wall -c main_ia.c -o main.o

clean:
	rm -rf *.o

mrproper: clean
	rm -rf main