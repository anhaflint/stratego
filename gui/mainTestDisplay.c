#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../structure.h"
#include "display.h"
#include "../stratego.h"

//gcc -Wall mainTestDisplay.c  display.c -lSDL -o tdisp




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
            case SDL_QUIT:
                continuer = 0;
        }
    }
}



int main()
{

if (SDL_Init(SDL_INIT_VIDEO) == -1) // Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

	BoardLayout layout;
	BoardLayout_Init(&layout);
	Display_Init(layout,2);
	Display_Init(layout,1);


	SDL_Flip(layout.Screen);

    pause(); // Permet de laisser la fenêtre affichée à l'écran

    SDL_Quit(); // Libération de la SDL en mémoire
 
    return EXIT_SUCCESS;
}


