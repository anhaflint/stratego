# Makefile final
# all : Permet de compiler l'interface et l'IA
# game : Permet de compiler l'interface du jeu
# lib : Permet de compiler l'IA
# clean : Permet de supprimer les fichiers.o
# mrproper : Permet de supprimer les exécutables et les fichiers .o

all: game lib clean

game:
	gcc -Wall gui/initlib.c gui/mainTestGame.c gui/game.c gui/display.c gui/event.c -lSDL -o ref -ldl

lib:
	gcc -fPIC -c ia/updateData.c ia/analyzeBoard.c ia/decideMove.c ia/riskProbability.c ia/saveMove.c ia/api.c
	gcc -shared -o libValentinPorchet-ArielNono.so updateData.o analyzeBoard.o decideMove.o riskProbability.o saveMove.o api.o


clean:
	rm -rf *.o

mrproper: clean
	rm -rf main libValentinPorchet-ArielNono.so


