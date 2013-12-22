#include <stdio.h>
#include <stdlib.h>

#include "../structure.h"
#include "game.h"
#include "../stratego.h"

//gcc -Wall mainTestGame.c  game.c -o test



int main(int argc, char* argv[])
{
	SGameConfig gameConfig;
	SGameState gameState;
	//EPlayer player1, player2;

	gameConfig.Mode = DetectGameMode(argc, argv);
	//Game_InitPlayer(&player1, &player2, &gameConfig);
	Game_InitGameState(&gameState);


	DisplayGS(gameState);
	printf("la config est %d\n", gameConfig.Mode);
//	printf("la couleur du joueur 1 est %d\n", gameConfig.ColorPlayer1);
	return 0;
}

