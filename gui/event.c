#include "event.h"

void Event_InitGameState(SDL_Event *event, int *continuer){


// On analyse le type d'event reçu
switch(event->type)
   {
        case SDL_QUIT:    // Si l'on quitte la fenêtre, on quitte la boucle, donc le jeu.
            *continuer=0;
            break;
        case SDL_MOUSEBUTTONUP: // Si il y a un clic, on affiche les positions x y du pointeur de la souris
                                // A changer bientôt par une analyse des coordonnées pour affectation d'une pièce dans un Game State par ex.
            printf("Vous avez cliquer en %d,%d \n",event->button.x,event->button.y );
           break;
   }
}

/*
SMove Event_Boardclick(SGameState gamestate){

	SDL_Event event;
  int continuer=0;

while(continuer=0)) {
{
     SDL_WaitEvent(&test_event);

     switch(event.type)
   {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONUP:
            printfpositionZozor.x = event.button.x;
            positionZozor.y = event.button.y;
           break;
   }

}
*/

