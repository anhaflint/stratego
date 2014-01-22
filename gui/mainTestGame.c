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
#include "initlib.h"

//gcc -Wall mainTestGame.c  game.c -o test



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


void Display(BoardLayout *layout, EPlayer player1, EPlayer player2, SGameState gamestate, int mode, int joueur)
{
	Display_killedPieces(layout, player1, gamestate);
	Display_killedPieces(layout, player2, gamestate);
	Display_BoardPlayer(layout,player1);
	//Display_affPlayer(layout,player1, mode);
	Display_affPlayer(layout,mode, joueur);

}

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
	
	StructIA AIfunctions1, AIfunctions2;
	SGameConfig gameconfig;
	SGameState gamestate;
	EPlayer player1, player2;
	int i; 
	printf("lalalaal1\n");

	InitStructIA(&AIfunctions1);
	InitStructIA(&AIfunctions2);
	printf("lalalalalalalalalala\n");
//SGameMode DetectGameMode(int argc, char* argv[], StructIA *AIfunctions1, StructIA *AIfunctions2)
	gameconfig.Mode = DetectGameMode(argc, argv, &AIfunctions1, &AIfunctions2);
	if (gameconfig.Mode == 3) return EXIT_FAILURE;
	printf("je pue l'oignon\n");
	// EPiece boardInit[4][10]; // Tableau temporaire rempli par les joueurs
	int GameWinner, MatchWinner = 0;
	SMove move;
	EPiece boardInit1[4][10] = {{11, 0, 8, 3, 0, 4, 0, 4, 5, 2},
                           {0, 7, 3, 3, 5, 0, 3, 3, 5, 2},
                           {4, 6, 6, 1, 6, 2, 4, 6, 0, 8},
                           {2, 7, 2, 9, 2, 2, 10, 7, 2, 5}};
    EPiece boardInit2[4][10];


	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1) // Si erreur :
    	{
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    	}
    	printf("lalala2\n");
	
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
	Game_Start(&player1, &player2, &gameconfig);

// Initialisation des gamestates joueurs et du gamestate général pour le premier jeu
	Game_Begin(&player1, &player2, &gamestate, &gameconfig, nbCoups);


printf("--------------------DEBUT DU MATCH----------------------------------------------------------------------------------\n");
	while( MatchWinner == 0) 
	{ // Boucle pour finir le match
		//Premier placement des pions des joueurs
		printf("------------------------------DEBUT DU JEU--------------------------------------------------------------------\n");
		// Affichage des indices J1 et J2
		//Display_affPlayer(&layout,player1,1);
		//Display_affPlayer(&layout,player2,1);

		//Affichage des pieces latérales
		Display_lateralPieces(layout,player1.Color);
		Display_lateralPieces(layout,player2.Color);
		printf("le mode est %d\n",gameconfig.Mode );

		if(gameconfig.Mode == IA_HUMAN)  // L'IA est le joueur2
		{
			printf("LALALA\n");
			AIfunctions1.InitLibrary(gameconfig.Player2Name);
			AIfunctions1.StartGame(player2.Color, boardInit2);
			printf("si ia\n");
		}
		if(player1.Color == ECred)
		{ // Si le premier joueur est rouge alors :


			//Le joueur rouge saisi le placement de ses pions et valide
				//Event_InitGameState(&event, &continuer, ECred, &layout, boardInit);
				// Copie du placement des pions du joueur dans les gamestates
				Game_CpyInitGameState(&gamestate, &player1, boardInit1);
			//Le joueur bleu saisi le placement de ses pions et valide
				//Event_InitGameState(&event, &continuer, ECblue, &layout, boardInit);
				Game_CpyInitGameState(&gamestate, &player2, boardInit2);

		}
		else // Le joueur 1 est bleu
		{
			//Le joueur rouge saisi le placement de ses pions et valide
				//Event_InitGameState(&event, &continuer, ECred, &layout, boardInit);
				// Copie du placement des pions du joueur dans les gamestates
				Game_CpyInitGameState(&gamestate, &player2, boardInit2);
			//Le joueur bleu saisi le placement de ses pions et valide
				//Event_InitGameState(&event, &continuer, ECblue, &layout, boardInit);
				Game_CpyInitGameState(&gamestate, &player1, boardInit1);
		}
		printf("================LA COULEUR DE L'IA EST============================================================ %d\n", player2.Color);

		//Les gamestates joueurs + général sont remplis des pièces des joueurs : le jeu peut commencer
		while( (GameWinner = Game_GotWinner(player1, player2, gamestate, nbCoups)) == 0) // tant que le jeu n'a pas de gagnant
		//for(i=0; i<1; i++)
		{
			/*jeu*/
			// Le joueur rouge commence
				Display_killedPieces(&layout, player1, gamestate);
				Display_killedPieces(&layout, player2, gamestate);
			printf("au joueur rouge\n");
			if(player1.Color == ECred)
			{
				//joueur 1
				Display(&layout, player1, player2, gamestate, 1, 1);
				move=Event_IdMove(&event,player1, &continuer);
				Game_DoMove(&gamestate, move, &player1, &player2, &layout);
				printf("la pénalité du joueur est %d\n", player1.nbPenalty);
				Display(&layout, player1, player2, gamestate, 2, 1);
				

				//joueur 2
				Display(&layout, player2, player1, gamestate, 1, 2);
				if(gameconfig.Mode == IA_HUMAN)
				{
					move = AIfunctions1.NextMove(&gamestate);
				}else
				{
					move=Event_IdMove(&event,player2, &continuer);
				}
				
				Game_DoMove(&gamestate, move, &player2, &player1, &layout);
				printf("la pénalité du joueur est %d\n", player2.nbPenalty);
				Display(&layout, player2, player1, gamestate, 2, 2);
				pause();
			}
			else
			{
				//joueur 2
				Display(&layout, player2, player1, gamestate, 1, 2);
				if(gameconfig.Mode == IA_HUMAN)
				{
					move = AIfunctions1.NextMove(&gamestate);
				}else
				{
					move=Event_IdMove(&event,player2, &continuer);
				}
				
				Game_DoMove(&gamestate, move, &player2, &player1, &layout);
				printf("la pénalité du joueur est %d\n", player2.nbPenalty);
				Display(&layout, player2, player1, gamestate, 2, 2);
				pause();

				//joueur 1
				Display(&layout, player1, player2, gamestate, 1, 1);
				move=Event_IdMove(&event,player1, &continuer);
				Game_DoMove(&gamestate, move, &player1, &player2, &layout);
				Display(&layout, player1, player2, gamestate, 2, 1);
			}
				


		}

		// incrémenation des compteurs de victoire
		/*if (GameWinner == 1)
		{
			printf("GameWinner = 1\n");
			player1.winnings ++;
		}
		else
		{
			printf("GameWinner = 2\n");
			player2.winnings ++;
		}*/



		// Réinitialisation des gamestates
		Game_Begin(&player1, &player2, &gamestate, &gameconfig, nbCoups);

		printf("le nombre de jeux est %d\n",gameconfig.nbJeux - 1);
		if(gameconfig.nbJeux == 3)
		{
			
			player1.winnings = 2;
			player2.winnings = 1;
		}
		MatchWinner = Game_EndMatch(player1,  player2, gameconfig, gamestate, nbCoups);
	}



	return 0;
}




