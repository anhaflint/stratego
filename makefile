# Makefile final
# all : Permet de compiler l'interface et l'IA
# game : Permet de compiler l'interface du jeu
# lib : Permet de compiler l'IA
# clean : Permet de supprimer les fichiers.o
# mrproper : Permet de supprimer les exécutables et les fichiers .o

all: game lib clean

game:
	$(info Compilation de l'interface...)
	@gcc -Wall gui/initlib.c gui/main.c gui/game.c gui/display.c gui/event.c -lSDL -o stratego -ldl

lib:
	$(info Compilation de la librairie de stratégie...)
	@gcc -fPIC -c ia/updateData.c ia/analyzeBoard.c ia/decideMove.c ia/riskProbability.c ia/saveMove.c ia/api.c
	@gcc -shared -o libValentinPorchet-ArielNono.so updateData.o analyzeBoard.o decideMove.o riskProbability.o saveMove.o api.o

clean:
	$(info Nettoyage des fichiers objet)
	@rm -rf *.o

mrproper: clean
	$(info Nettoyage des fichiers objet et exécutable)
	@rm -rf stratego libValentinPorchet-ArielNono.so


