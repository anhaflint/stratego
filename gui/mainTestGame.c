#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>

#include "../structure.h"
#include "game.h"
#include "../stratego.h"
#include "../ia/couleurs.h"
#include "display.h"
#include "event.h"

//gcc -Wall mainTestGame.c  game.c -o test



int main(int argc, char* argv[])
{
//	SGameConfig gameConfig;
//	SGameState gameState;
	//int i, j;
//	SPos start, end; 
//	SMove move; 


//	EPlayer player1, player2;
//	Game_Start(&player1, &player2);

	/*
	EPiece boardInit[4][10]; // faux placement de pions pour tester cpygamestate
	for(i=0; i<4; i++)
	{
		for(j=0; j<10; j++)
		{
			boardInit[i][j] = j;
		}
	}
	*/
/*	strcpy(gameConfig.Player1Name, "Joueur1");
	strcpy(gameConfig.Player2Name, "Joueur2");
	player1.winnings += 14;
	player2.winnings += 14; 
	vainqueur = Game_End(player1, player2, gameConfig);
	*/
	// gameConfig.Mode = DetectGameMode(argc, argv);
	// initialisation des joueurs
/*	Game_InitPlayer(&player1, &player2, &gameConfig, 300);
	player2.Color = ECred;
	player1.Color = ECblue;
	// initialisation du gamestate
	// if (gameConfig.Mode == 3) return EXIT_FAILURE;

	Game_InitGameState(&gameState);
	// remplissage du gamestate avec les pions placés par les joueurs
	EPiece initBoard[4][10] = {{11, 0, 8, 3, 0, 4, 0, 4, 5, 2},
						 		{0, 7, 3, 3, 5, 0, 3, 3, 5, 2},
						 		{4, 6, 6, 1, 6, 2, 4, 6, 0, 8},
						 		{2, 2, 7, 9, 2, 2, 10, 7, 2, 5}};
	Game_CpyInitGameState(&gameState, &player1, initBoard);
	Game_CpyInitGameState(&gameState, &player2, initBoard);
*/	
/*	// mise en place de pions sur le gamestate comme si on avait placé de pieces
	// joueur BLEU,  haut du tableau
	gameState.board[0][0].piece = EPflag; 
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
	
//	start.line = 3 ; start.col = 4; // scout
//	end.line = 6; end.col = 4;
	
	
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
/*		move.start = start; 
		move.end = end; 

	printf("-----------JOUEUR 1---: %d--------------\n", gameConfig.ColorPlayer1);
	DisplayPlayerGS(player1.Pboard);
	printf("-----------JOUEUR 2----------------------\n");
	DisplayPlayerGS(player2.Pboard);
	printf("------------GAMESTATE--------------------\n");
	DisplayGS(gameState);
	printf("la config est %d\n", gameConfig.Mode);


	Game_DoMove(&gameState, move, &player2, &player1);
	printf("-----------------------------------------GAMESTATE--APRES--MOUVEMENT-----------------------------------------\n");
	printf("-----------JOUEUR 1---: %d--------------\n", gameConfig.ColorPlayer1);
	DisplayPlayerGS(player1.Pboard);
	printf("-----------JOUEUR 2----------------------\n");
	DisplayPlayerGS(player2.Pboard);
	printf("------------GAMESTATE--------------------\n");
	DisplayGS(gameState);
*/
	//printf("le gagnant est : %s\n", vainqueur);
// ============================ test jeu==========================================
	SGameConfig gameconfig;
	SGameState gamestate;
	EPlayer player1, player2;
	// EPiece boardInit[4][10]; // Tableau temporaire rempli par les joueurs
	int GameWinner, MatchWinner;
	SMove move;
	EPiece boardInit[4][10] = {{11, 0, 8, 3, 0, 4, 0, 4, 5, 2},
                           {0, 7, 3, 3, 5, 0, 3, 3, 5, 2},
                           {4, 6, 6, 1, 6, 2, 4, 6, 0, 8},
                           {2, 7, 2, 9, 2, 2, 10, 7, 2, 5}};


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




//Initialisation du nombre de coups maximal pour les joueurs
	int nbCoups = atoi(argv[1]);

// Initialisation du nombre de victoires et début du match
	Game_Start(&player1, &player2);

// Initialisation des gamestates joueurs et du gamestate général pour le premier jeu
	Game_Begin(&player1, &player2, &gamestate, &gameconfig, nbCoups);

	while( (MatchWinner = Game_EndMatch(player1,  player2, gameconfig, gamestate, nbCoups)) == 0) 
	{ // Boucle pour finir le match
		//Premier placement des pions des joueurs
		if(player1.Color == ECred)
		{ // Si le premier joueur est rouge alors : 
			//Le joueur rouge saisi le placement de ses pions et valide
				Event_InitGameState(&event, &continuer, ECred, &layout, boardInit);
				// Copie du placement des pions du joueur dans les gamestates
				Game_CpyInitGameState(&gamestate, &player1, boardInit);
			//Le joueur bleu saisi le placement de ses pions et valide
				Event_InitGameState(&event, &continuer, ECblue, &layout, boardInit);
				Game_CpyInitGameState(&gamestate, &player2, boardInit);

		}
		else // Le joueur 1 est bleu
		{
			//Le joueur rouge saisi le placement de ses pions et valide
				Event_InitGameState(&event, &continuer, ECred, &layout, boardInit);
				// Copie du placement des pions du joueur dans les gamestates
				Game_CpyInitGameState(&gamestate, &player2, boardInit);
			//Le joueur bleu saisi le placement de ses pions et valide
				Event_InitGameState(&event, &continuer, ECblue, &layout, boardInit);
				Game_CpyInitGameState(&gamestate, &player1, boardInit);
		}

		//Les gamestates joueurs + général sont remplis des pièces des joueurs : le jeu peut commencer
		while( (GameWinner = Game_GotWinner(player1, player2, gamestate, nbCoups)) == 0) // tant que le jeu n'a pas de gagnant
		{
			/*jeu*/
			// Le joueur rouge commence
			printf("au joueur rouge\n");
			if(player1.Color == ECred)
			{
				Display_BoardPlayer(&layout,player1);
				//DisplayPlayerGS(player1.Pboard);
				move=Event_IdMove(&event,player1, &continuer);
				Game_DoMove(&gamestate, move, &player1, &player2);

				// Au tour du joueur 2 de jouer
				Display_BoardPlayer(&layout,player2);
				move=Event_IdMove(&event,player2, &continuer);
				Game_DoMove(&gamestate, move, &player2, &player1);
			}
			else
			{
				// Au tour du joueur 2 rouge de jouer
				Display_BoardPlayer(&layout,player2);
				move=Event_IdMove(&event,player2, &continuer);
				Game_DoMove(&gamestate, move, &player2, &player1);
				Display_BoardPlayer(&layout,player2);

				// Au tour du joueur bleu de jouer
				Display_BoardPlayer(&layout,player1);
				move=Event_IdMove(&event,player1, &continuer);
				Game_DoMove(&gamestate, move, &player1, &player2);
				Display_BoardPlayer(&layout,player1);

			}


		}

		// incrémenation des compteurs de victoire
		if (GameWinner == 1)
			player1.winnings ++;
		else
			player2.winnings ++;

		// Réinitialisation des gamestates
		Game_Begin(&player1, &player2, &gamestate, &gameconfig, nbCoups);

	}



	return 0;
}

