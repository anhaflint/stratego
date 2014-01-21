all:
	gcc -Wall mainGeneral.c game.c display.c event.c -lSDL -o testGeneral
reftest: 
	gcc -Wall initlib.c mainTestGame.c  game.c display.c event.c -lSDL -o ref -ldl
gui:
	gcc -Wall mainTestDisplay.c display.c event.c -lSDL -o tdisp
ref: 
	gcc -Wall mainTestGame.c  game.c -o test