#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
                                        // Forme d'Appel ./game 1 libtrobi1.so
                                        // Compil gcc -Wall main.c -lSDL -o main
void pause();

int main(int argc, char *argv[])
{
// Démarrage de la SDL---------------------------------------------------------------------------------------
    if (SDL_Init(SDL_INIT_VIDEO) == -1) // Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

//Declaration des surfaces-----------------------------------------------------------------------------------
/**
 * ecran : surface de l'ecran
 * imageDeFond : Surface de l'image en background
 * tuileA : tuile représentant le joueur A
 * tuileT : tuile représentant le joueur T
 */ 
    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *tuileA= NULL, *tuileT=NULL; //Surfaces
    SDL_Rect positionFond, plateauaff[10][10];   	//Position relative des images (point supérieur gauche de la surface)
 
    //Background
    positionFond.x = 0;
    positionFond.y = 0;
    
//WINDOW SETUP----------------------------------------------------------------------------------------------
    ecran=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Setup de la surface de l'ecran
    SDL_WM_SetCaption("Stratego's Creed", "SC"); //Affichage des infos de la fenêtre
    //Quick Background Display
    imageDeFond = SDL_LoadBMP("images/venice2.bmp"); 
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
 
   
    
//---------SETUP POSITIONS TUILES + AFFICHAGE-------------------------------------------------
    int i,j; // Compteur pour boucles
    tuileA = SDL_LoadBMP("images/tuileA.bmp"); // Charge image d'une tuileA
    tuileT = SDL_LoadBMP("images/tuileT.bmp"); // Charge image d'une tuileT
    for (i=0;i<10;i++)
    {                                // POUR UNE COLONNE : 0----------------9
        for (j=0;j<4;j++)
        {                        // POUR UNE LIGNE : 0---3
        	//Tuiles A--------------------------------------------------------
                plateauaff[i][j].x = 155+50*i; // 155 : abcisse de début de plateau
                plateauaff[i][j].y = 355+50*j; // 355 : ordonnée de début du plateau
                SDL_BlitSurface(tuileA, NULL, ecran, &plateauaff[i][j]); 
                //Tuiles T--------------------------------------------------------
                plateauaff[i][9-j].x = 155+50*i; // (9-j) = {9, 8, 7, 6}
                plateauaff[i][9-j].y = 55+50*j;  // j = {0, 1, 2, 3}
                SDL_BlitSurface(tuileT, NULL, ecran, &plateauaff[i][9-j]);
        }
    }
//--------------------------------------------------------------------------------------------
  
    SDL_Flip(ecran);

    pause(); // Permet de laisser la fenêtre affichée à l'écran

    SDL_Quit(); // Libération de la SDL en mémoire
    return EXIT_SUCCESS;
} // End Main

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
