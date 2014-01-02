#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../structure.h"
#include "display.h"
#include "event.h"
#include "../stratego.h"

//gcc -Wall mainTestDisplay.c display.c event.c -lSDL -o tdisp

int main()
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

// Appel de la fonction d'affichage pour le placement des pièces.
	//Display_Init(layout,1);
	//Display_Init(layout,2);
	//Display_Init(layout,3);       Enlever commentaire pour test supprimer aff latéral


// Rafraichissement
	SDL_Flip(layout.Screen);


//Déclarations des var. event , + Epiece[4][10] à remplir+ entier pour une boucle.
	SDL_Event event;
    int continuer=1;
    EPiece PiecesRouges[4][10];
    EPiece PiecesBleues[4][10];

while(continuer==1) // Tant que l'on quitte pas la fenêtre
{
    Event_InitGameState(&event,&continuer,1,layout,PiecesRouges); //affiche seulement la Position du clic pour le moment
	Event_InitGameState(&event,&continuer,2,layout,PiecesBleues); //affiche seulement la Position du clic pour le moment
	printf("Vous avez terminé le test, retour au placement des pions Rouges \n");
}

//Sortie de boucle :

    SDL_Quit(); // Libération de la SDL en mémoire
 
    return EXIT_SUCCESS; // => return 0;
}


