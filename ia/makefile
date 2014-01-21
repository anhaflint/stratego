all: main clean

main: main.o
	gcc -o main main.o

main.o: main_ia.c
	gcc -Wall -c main_ia.c -o main.o

clean:
	rm -rf *.o

mrproper: clean
	rm -rf main

lib:
	gcc -fPIC -c updateData.c analyzeBoard.c decideMove.c riskProbability.c saveMove.c api.c
	gcc -shared -o libValAriel.so updateData.o analyzeBoard.o decideMove.o riskProbability.o saveMove.o api.o

