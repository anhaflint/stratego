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

if (SDL_Init(SDL_INIT_VIDEO) == -1) // Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

	BoardLayout layout;
	BoardLayout_Init(&layout);
	Display_Init(layout,1);
	Display_Init(layout,2);
	//Display_Init(layout,3);       Enlever commentaire pour test supprimer aff latéral

	SDL_Flip(layout.Screen);

	SDL_Event event;
    int continuer=1;

while(continuer==1)
{
     SDL_WaitEvent(&event);
     Event_InitGameState(&event,&continuer); //affiche seulement la position du clic pour le moment

}
    SDL_Quit(); // Libération de la SDL en mémoire
 
    return EXIT_SUCCESS;
}


