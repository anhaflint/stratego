#include <stdio.h>
#include <stdlib.h>

#include "../structure.h"
#include "game.h"
#include "../stratego.h"

//gcc -Wall mainTestGame.c  game.c -o test
int main(int argc, char* argv[])
{
	SGameConfig gameConfig;
	gameConfig.Mode = DetectGameMode(argc, argv);
	EPlayer player1, player2;
	/*if(gamemode == IA_IA)
	{
		pfInitLibrary j1InitLibrary = InitLibrary;
	}*/
	Game_InitPlayer(&player1, &player2, &gameConfig);
	printf("la config est %d\n", gameConfig.Mode);
	printf("la couleur du joueur 1 est %d\n", gameConfig.ColorPlayer1);
	return 0;
}