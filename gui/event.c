#include "event.h"

void Event_InitGameState(SDL_Event *event, int *continuer,int color,BoardLayout layout, EPiece Pieces[4][10]){

// Affichage des pièces

if(color==1){
  Display_Init(layout,1); // On affiche les pieces rouges latéralement à gauche
  printf("Début de la phase de placement Rouge \n");
}
if(color==2){
Display_Init(layout,2); // On affiche les pieces bleue latéralement à doite
  printf("Début de la phase de placement Bleu \n");
  }

// Debut phase de placement

int placement=40;           // nombre de pièces à placer


while (placement!=0){       // Tant que le placement n'est pas fini

SDL_WaitEvent(event);      // Capture d'un évent(clic)

// On analyse le type d'event reçu
switch(event->type)
   {
        case SDL_QUIT:          // Si l'on quitte la fenêtre, on quitte la boucle, donc le jeu.
            printf("Vous quittez le jeu...\n");
            *continuer=0;
            placement=0;         // Placement fini prématurément
            Pieces=NULL;
            
            break;

        case SDL_MOUSEBUTTONUP: // Si il y a un clic, on affiche les positions x y du pointeur de la souris
                                // A changer bientôt par une analyse des coordonnées pour affectation d'une pièce dans un Game State par ex.
            if(color==1){

              
              if (event->button.x<=100){

                printf("Vous avez cliquer en %d,%d : Un Espace Rouge \n",event->button.x,event->button.y );
                placement--;
                printf("Il vous reste %d placement à faire \n",placement);
              }
              else{printf("Vous avez cliquer en %d,%d : Un Espace INCORRECT \n",event->button.x,event->button.y );

              }            
            }


            if(color==2){


              if (event->button.x>=700){
                printf("Vous avez cliquer en %d,%d : Un Espace Bleu \n",event->button.x,event->button.y );
                placement--;
                printf("Il vous reste %d placement à faire \n",placement);
              }
              else{printf("Vous avez cliquer en %d,%d : Un Espace INCORRECT \n",event->button.x,event->button.y );

              }            
            }
           break;
   }
}
Display_Init(layout,3); // On efface l'affichage des tuiles car Placement terminé
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

