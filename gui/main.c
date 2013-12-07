#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
                                        // Forme d'Appel ./game 1 libtrobi1.so
                                        // Compil gcc -Wall main.c -lSDL -o main
void pause();

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *tuileA= NULL, *tuileT=NULL; // Surface ( images )
    SDL_Rect positionFond, plateauaff[10][10];							// Position relative des images
 
    positionFond.x = 0;
    positionFond.y = 0;

    ecran=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Stratego's Creed", "SC");
    imageDeFond = SDL_LoadBMP("images/venice2.bmp"); // test affichage du fond cadrié
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    
    
    //---------TUILES
    int i,j; // Compteur pour boucles
    tuileA = SDL_LoadBMP("images/tuileA.bmp"); // Charge image d'une tuileA
    tuileT = SDL_LoadBMP("images/tuileT.bmp"); // Charge image d'une tuileT
    for (i=0;i<10;i++)
    {				// POUR UNE LIGNE : 0----------------9
    	for (j=0;j<4;j++)
	{			// POUR UNE COLONNE : 0---3
    		plateauaff[i][j].x = 155+50*i;
    		plateauaff[i][j].y = 355+50*j;
		SDL_BlitSurface(tuileA, NULL, ecran, &plateauaff[i][j]); 	// Aff tuileA
    	}
    }
    
    
    
    for (i=0;i<10;i++)
    {				// POUR UNE LIGNE : 0---------------9
    	for (j=9;j>5;j--)
	{			// POUR UNE COLONNE : 9-----5
    		plateauaff[i][j].x = 155+50*i;		
    		plateauaff[i][j].y = 55+50*(9-j);		// 9-j = 0 1 2 3
		SDL_BlitSurface(tuileT, NULL, ecran, &plateauaff[i][j]);	// Aff tuileT
    	}
    }

    
    //-------------

    
    
    
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
