#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>

#include "../structure.h"
#include "game.h"
#include "display.h"
#include "event.h"
#include "../stratego.h"
#include "../ia/couleurs.h"


//gcc -Wall mainTestGame.c  game.c -o test
// gcc -Wall mainGeneral.c game.c display.c event.c -lSDL -o testGeneral





//--------------------------------------------------------------------------------------------
// Fonctions auxiliaires
//--------------------------------------------------------------------------------------------
void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                continuer = 0;
        }
    }
}


//--------------------------------------------------------------------------------------------
// Debut Fonctions TEST
//--------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1) // Si erreur :
    	{
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    	}
	
	// Déclarations des var. display + Init
	BoardLayout layout;
	BoardLayout_Init(&layout);
	SDL_Flip(layout.Screen);
	
	//Déclarations des var. event , + Epiece[4][10] à remplir+ entier pour une boucle.
	SDL_Event event;
    int continuer=1;


//Event_InitGameState(&event,&continuer,1,layout,PiecesRouges);
// Bleu 3 
// Rouge 2
	SGameConfig gameConfig;
	SGameState gameState;
	int i, j;
	SPos start, end; 
	SMove move;

	EPlayer player1, player2;
	//EPiece boardInit1[4][10]; // faux placement de pions pour tester cpygamestate
	//EPiece boardInit2[4][10];
	/*for(i=0; i<4; i++)
	{
		for(j=0; j<10; j++)
		{
			boardInit[i][j] = j;
		}
	}
	*/

	gameConfig.Mode = DetectGameMode(argc, argv);
	// initialisation des joueurs
	Game_InitPlayer(&player1, &player2, &gameConfig, 300);
	

	//Event_InitGameState(&event, &continuer, ECred, &layout, boardInit1); // Rouge // A MODIFIER PAR UN ECOLOR ET 2
	//Event_InitGameState(&event, &continuer, ECblue, &layout, boardInit2); // BLEU  // A MODIFIER PAR UN ECOLOR ET 3
	
	// initialisation du gamestate
	if (gameConfig.Mode == 3) return EXIT_FAILURE;

	Game_InitGameState(&gameState);
	// remplissage du gamestate avec les pions placés par les joueurs
	EPiece boardInit1[4][10] = {{11, 0, 8, 3, 0, 4, 0, 4, 5, 2},
                           {0, 7, 3, 3, 5, 0, 3, 3, 5, 2},
                           {4, 6, 6, 1, 6, 2, 4, 6, 0, 8},
                           {2, 7, 2, 9, 2, 2, 10, 7, 2, 5}};
	
    EPiece boardInit2[4][10] = {{11, 0, 8, 3, 0, 4, 0, 4, 5, 2},
                           {0, 7, 3, 3, 5, 0, 3, 3, 5, 2},
                           {4, 6, 6, 1, 6, 2, 4, 6, 0, 8},
                           {2, 7, 2, 9, 2, 2, 10, 7, 2, 5}};
	
	if(player1.Color == ECred) 
	{
		Game_CpyInitGameState(&gameState, &player1, boardInit1);
		Game_CpyInitGameState(&gameState, &player2, boardInit2);
	}
	else
	{
		Game_CpyInitGameState(&gameState, &player1, boardInit2);
		Game_CpyInitGameState(&gameState, &player2, boardInit1);
	}

	// Game_CpyInitGameState(&gameState, &player1, boardInit1);
	// Game_CpyInitGameState(&gameState, &player2, boardInit2);
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
    // int Game_CheckMove(SMove move, EPlayer player, SGameState gamestate, int position);
    // void Game_DoMove(SGameState* game,SMove move, EPlayer player); 
    // SBox Game_Fight(SBox player1, SBox player2);
	
	// Test scout mange espion : OK
	/*
	start.line = 3; start.col = 8; // scout
	end.line = 6; end.col = 8;
	*/
	
	// Test piece normale : OK
	/*
	start.line = 3; start.col = 1; // Piece n°7
	end.line = 5; end.col = 1;
	*/

	// Test selection invalide : OK
	/*
	start.line = 4; start.col = 2; // Lac
	end.line = 5; end.col = 1;
	*/

	// Test selection vide : OK
	/*
	start.line = 4; start.col = 1; // vide
	end.line = 5; end.col = 1;
	*/

	// Test déplacement en diagonale : OK 
	/*
	start.line = 9; start.col = 9; 
	end.line = 7; end.col = 8;
	*/
	/*	move.start = start; 
		move.end = end; 
	*/
	printf("-----------JOUEUR 1---: %d--------------\n", gameConfig.ColorPlayer1);
	DisplayPlayerGS(player1.Pboard);
	
	//Display_BoardPlayer(layout,player1);
	Display_lateralPieces(layout,player1.Color);
	Display_lateralPieces(layout,player2.Color);
	
	while( (player1.nbCoups!=0) || (continuer==0) )
	{
		Display_affPlayer(&layout,player1,1);
		Display_affPlayer(&layout,player2,1);
		// TEST SUPPRESSION TERMINEE Display_affPlayer(&layout,player2,0);

		Display_BoardPlayer(&layout,player1);
		Display_killedPieces(&layout,player1,gameState);
		Display_killedPieces(&layout,player2,gameState);
		DisplayPlayerGS(player1.Pboard);
		move=Event_IdMove(&event,player1, &continuer);
		Game_DoMove(&gameState, move, &player1, &player2);
		
		player1.nbPenalty++;
		player2.nbPenalty++;
		Display_Penalty(&layout,player1);
		Display_Penalty(&layout,player2);
		
		player1.nbCoups--;

	}

	printf("-----------JOUEUR 2----------------------\n");
	DisplayPlayerGS(player2.Pboard);

		Display_BoardPlayer(&layout,player2);
	pause(); // Permet de laisser la fenêtre affichée à l'écran


	printf("------------GAMESTATE--------------------\n");
	DisplayGS(gameState);
	printf("la config est %d\n", gameConfig.Mode);


	
	//Game_DoMove(&gameState, move, &player1, &player2);
	printf("------------GAMESTATE--APRES--MOUVEMENT----------------\n");
	DisplayGS(gameState);

    SDL_Quit(); // Libération de la SDL en mémoire
	return 0;
}



