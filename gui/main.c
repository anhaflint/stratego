#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>

#include "../structure.h"
#include "game.h"
#include "../stratego.h"
#include "display.h"
#include "event.h"
#include "initlib.h"

//--------------------------------------------------------------------------------------------
// Fonctions auxiliaires
//--------------------------------------------------------------------------------------------
void pause(int *continueGame)
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
                break;

            case SDL_QUIT:
            	continuer = 0;
            	*continueGame = 0;
            	break;
        }
    }
}


void Display(BoardLayout *layout, EPlayer player1, EPlayer player2, SGameState gamestate, int joueur)
{
	Display_killedPieces(layout, player1, gamestate);
	Display_killedPieces(layout, player2, gamestate);
	Display_BoardPlayer(layout,player1);
	Display_affPlayer(layout, joueur);
}

int main(int argc, char* argv[])
{
	
	StructIA AIfunctions1, AIfunctions2;
	SGameConfig gameconfig;
	SGameState gamestate, *GSjoueur;
	GSjoueur = malloc(sizeof(SGameState));
	EPlayer player1, player2;
	FILE* fichier = NULL; // Fichier de conservation des scores
	fichier = fopen("resultats.txt", "w");

	// initialisation des structure d'IA
	InitStructIA(&AIfunctions1);
	InitStructIA(&AIfunctions2);
	
	//SGameMode DetectGameMode(int argc, char* argv[], StructIA *AIfunctions1, StructIA *AIfunctions2)
	gameconfig.Mode = DetectGameMode(argc, argv, &AIfunctions1, &AIfunctions2);
	if (gameconfig.Mode == 3) return EXIT_FAILURE;
	
	// EPiece boardInit[4][10]; // Tableau temporaire rempli par les joueurs
	int GameWinner, MatchWinner = 0;
	SMove move;
	//EPiece boardInit1[4][10];
    EPiece boardInit2[4][10];
    EPiece boardInit1[4][10];

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
	Game_Start(&player1, &player2, &gameconfig);

	// Initialisation des gamestates joueurs et du gamestate général pour le premier jeu
	Game_Begin(&player1, &player2, &gamestate, &gameconfig, nbCoups);

	 // Boucle pour finir le match
		//Premier placement des pions des joueurs
		if((gameconfig.Mode == IA_HUMAN)||(gameconfig.Mode == IA_IA))  // L'IA est le joueur2
		{
			if (gameconfig.Mode == IA_HUMAN)
				Event_InitGameState(&event,&continuer,player1.Color,&layout,boardInit1); 

			AIfunctions1.InitLibrary(gameconfig.Player2Name);
			AIfunctions1.StartGame(player2.Color, boardInit2);
		}
		
		if (gameconfig.Mode == IA_IA)
		{
			AIfunctions2.InitLibrary(gameconfig.Player1Name);
			AIfunctions2.StartGame(player1.Color, boardInit1);
		}

		//Affichage des pieces latérales
		Display_lateralPieces(layout,player1.Color);
		Display_lateralPieces(layout,player2.Color);

		if(player1.Color == ECred)
		{ // Si le premier joueur est rouge alors :
				Game_CpyInitGameState(&gamestate, &player1, boardInit1);
				Game_CpyInitGameState(&gamestate, &player2, boardInit2);

		}
		else // Le joueur 1 est bleu
		{
				Game_CpyInitGameState(&gamestate, &player2, boardInit2);
				Game_CpyInitGameState(&gamestate, &player1, boardInit1);
		}
		
		while(((GameWinner = Game_GotWinner(player1, player2, gamestate, nbCoups)) == 0)&&(continuer)) // tant que le jeu n'a pas de gagnant
		{
			/*jeu*/
			// Le joueur rouge commence
				Display_killedPieces(&layout, player1, gamestate);
				Display_killedPieces(&layout, player2, gamestate);

			if(player1.Color == ECred)
			{
				//joueur 1
				Display(&layout, player1, player2, gamestate, 1);
				if(gameconfig.Mode == IA_HUMAN)
				{
					move=Event_IdMove(&event,player1, &continuer);
				}
				else // IA_IA
				{
					GSjoueur = Game_SwitchGS(gamestate, player1);
					move = AIfunctions2.NextMove(GSjoueur);					
				}
				
				if (continuer)
					Game_DoMove(&gamestate, move, &player1, &player2, &layout, gameconfig, AIfunctions1, AIfunctions2);
				Display(&layout, player1, player2, gamestate, 1);

				if(gameconfig.Mode == IA_IA) pause(&continuer);
				
				if((Game_GotWinner(player1, player2, gamestate, nbCoups)==0)&&(continuer))
				{
					//joueur 2
					Display(&layout, player2, player1, gamestate, 2);
					if((gameconfig.Mode == IA_HUMAN)||(gameconfig.Mode == IA_IA))
					{
						GSjoueur = Game_SwitchGS(gamestate, player2);
						move = AIfunctions1.NextMove(GSjoueur);
					}
					
					if (continuer)
						Game_DoMove(&gamestate, move, &player2, &player1, &layout, gameconfig, AIfunctions1, AIfunctions2);
					Display(&layout, player2, player1, gamestate, 2);
					pause(&continuer);
				}
			}
			else
			{ //joueur 2
				Display(&layout, player2, player1, gamestate, 2);
				if((gameconfig.Mode == IA_HUMAN)||(gameconfig.Mode == IA_IA))
				{
					GSjoueur = Game_SwitchGS(gamestate, player2);
					move = AIfunctions1.NextMove(GSjoueur);
				}
				
				if (continuer)
					Game_DoMove(&gamestate, move, &player2, &player1, &layout, gameconfig, AIfunctions1, AIfunctions2);
				Display(&layout, player2, player1, gamestate, 2);
				pause(&continuer);

				if((Game_GotWinner(player1, player2, gamestate, nbCoups)==0)&&(continuer))
				{
					//joueur 1
					Display(&layout, player1, player2, gamestate, 1);

					if (gameconfig.Mode == IA_HUMAN)
					{
						move=Event_IdMove(&event,player1, &continuer);
					}
					else
					{
						GSjoueur = Game_SwitchGS(gamestate, player1);
						move = AIfunctions2.NextMove(GSjoueur);
					}
					if(gameconfig.Mode == IA_IA) pause(&continuer);

					if (continuer)
						Game_DoMove(&gamestate, move, &player1, &player2, &layout, gameconfig, AIfunctions1, AIfunctions2);
					Display(&layout, player1, player2, gamestate, 1);
				}
			}
		}// while
		
		continuer = 0;

		MatchWinner = Game_EndMatch(player1,  player2, gameconfig, gamestate, nbCoups);

		if (fichier != NULL)
	    {
	    	fprintf(fichier, "Le gagnant du match est le joueur %d\n ", MatchWinner);
	    }

	// Libération de la mémoire occupée par les IA
	
	freeIA(&AIfunctions1);
	if(gameconfig.Mode == IA_IA)
		freeIA(&AIfunctions2);
	fclose(fichier);

	return 0;
}




