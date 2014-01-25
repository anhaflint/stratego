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


                                        // make main

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


 //-------------------------------DEBUT--------------------------------

int main(int argc, char *argv[])
{
// Démarrage de la SDL---------------------------------------------------------------------------------------
    if (SDL_Init(SDL_INIT_VIDEO) == -1) // Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    // TRAITEMENT DES ARGUMENTS 
            // APPEL d'une fonction pour IA HUMAIN

            // APPEL d'une fonction pour IA IA














    pause();



    SDL_Quit(); // Libération de la SDL en mémoire
    return EXIT_SUCCESS;
} // End Main

