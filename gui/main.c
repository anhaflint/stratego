#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void pause();

int main(int argc, char *argv[])
{

	if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    SDL_Surface *ecran = NULL, *imageDeFond = NULL;
    SDL_Rect positionFond;
 
    positionFond.x = 0;
    positionFond.y = 0;

    ecran=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Stratego's Creed", "SC");
    imageDeFond = SDL_LoadBMP("venice.bmp");

    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_Flip(ecran);

    pause();

	SDL_Quit();
	return EXIT_SUCCESS;
}

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