#include <stdio.h>
#include <stdlib.h>

#include "../structure.h"
#include "game.h"
#include "../stratego.h"
#include "../ia/couleurs.h"

//gcc -Wall mainTestGame.c  game.c -o test



int main(int argc, char* argv[])
{
	SGameConfig gameConfig;
	SGameState gameState;
	int i, j;
	int returnpos;
	SPos start;
	EPlayer player1, player2;
	EPiece boardInit[4][10]; // faux placement de pions pour tester cpygamestate
	for(i=0; i<4; i++)
	{
		for(j=0; j<10; j++)
		{
			boardInit[i][j] = j;
		}
	}

	gameConfig.Mode = DetectGameMode(argc, argv);
	// initialisation des joueurs
	Game_InitPlayer(&player1, &player2, &gameConfig);
	// initialisation du gamestate
	if (gameConfig.Mode == 3) return EXIT_FAILURE;

	Game_InitGameState(&gameState);
	// remplissage du gamestate avec les pions placés par les joueurs
	Game_CpyGameState(&gameState, &player1, boardInit);
	Game_CpyGameState(&gameState, &player2, boardInit);
	// mise en place de pions sur le gamestate comme si on avait placé de pieces
	// joueur BLEU,  haut du tableau
	/*gameState.board[0][0].piece = EPflag; 
	gameState.board[0][1].piece = EPbomb;
	gameState.board[1][0].piece = EPbomb; 
	gameState.board[1][1].piece = EPscout;
	gameState.board[2][1].piece = EPmajor; 

	// joueur ROUGE, bas du tableau
	gameState.board[9][0].piece = EPflag; 
	gameState.board[9][1].piece = EPbomb;
	gameState.board[8][0].piece = EPbomb; 
	gameState.board[8][8].piece = EPscout;
	gameState.board[6][5].piece = EPmajor; 
    */
	
/*	player1.Color = ECblue;
	start.line = 7; start.col = 8;
	returnpos = Game_CheckPosition(start, player1, gameState);
*/
	printf("-----------JOUEUR 1---: %d--------------\n", gameConfig.ColorPlayer1);
	DisplayPlayerGS(player1.Pboard);
	printf("-----------JOUEUR 2----------------------\n");
	DisplayPlayerGS(player2.Pboard);
	printf("------------GAMESTATE--------------------\n");
	DisplayGS(gameState);
	printf("la config est %d\n", gameConfig.Mode);
	//printf("la position de depart est : %d\n", returnpos);

	return 0;
}

