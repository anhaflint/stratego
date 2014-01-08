#include "event.h"

void Event_InitGameState(SDL_Event *event, int *continuer,int color,BoardLayout layout, EPiece Pieces[4][10]){

EPiece PieceSelectionnee;


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

              PieceSelectionnee=Event_IdPiece_Init(event->button.x,event->button.y,1);
              
              if (PieceSelectionnee!=EPnone){

                printf("Vous avez cliqué en %d,%d : Un Espace Rouge \n",event->button.x,event->button.y );
                printf("Val pièce cliquée : %d \n",PieceSelectionnee);
                placement--;
                printf("Il vous reste %d placement à faire \n",placement);
              }
              
              else{

                printf("Vous avez cliqué en %d,%d : INCORRECT \n",event->button.x,event->button.y );
                printf("Veuillez cliquer sur une case rouge ou une case du plateau \n" );

              }            
            }


            if(color==2){

             PieceSelectionnee=Event_IdPiece_Init(event->button.x,event->button.y,2);

              if (PieceSelectionnee!=EPnone){
                printf("Vous avez cliqué en %d,%d : Un Espace Bleu \n",event->button.x,event->button.y );
                
                printf("Val pièce cliquée : %d \n",PieceSelectionnee);
                placement--;
                printf("Il vous reste %d placement à faire \n",placement);
              }

              else{
                printf("Vous avez cliqué en %d,%d : INCORRECT \n",event->button.x,event->button.y );
                printf("Veuillez cliquer sur une case bleu ou une case du plateau \n" );

              }            
            }
           break;
   }
}
Display_Init(layout,3); // On efface l'affichage des tuiles car Placement terminé
}

EPiece Event_IdPiece_Init(int x,int y,int color){

int noPiece;

// TRAITEMENT SUR X

  if (color==1){                 // Si c'est un placement rouge

    if ( (x<10)||(x>50)) {          // Le clic n'est pas centrée sur les pièces en X C [10:50]

      return EPnone;   
      }       // La coordonnée X ne correspont à aucune pièce.
  }

  if (color==2){               // Si c'est un placement bleu
    
    if ( (x<710)||(x>750)) {        // Le clic est centrée sur les pièces en X C [710:750]

      return EPnone;          // La coordonnée X ne correspont à aucune pièce.

    }
  }

// TRAITEMENT SUR Y

  for (noPiece=0;noPiece<12;noPiece++){
      
    if (   ( y>=33+noPiece*(5+40) )    &&   ( y<=73+noPiece*(5+40) )     ) {
                                          // La première case est en y C [33:73] auquel on ajoute 60 pour passer
                                          // d'une pièce à l'autre, 5 pour l'écart entre les pièces et 40 pour 
                                          // la taille de la pièce

    break;
    }

  }

            printf("Le numéro pièce est : %d\n", noPiece);
   switch(noPiece){

          case 0:
            return EPspy;
            break;

          case 1:
            return EPscout;
            break;

          case 2:
            return EPminer;
            break;

          case 3:
            return EPsergeant;
            break;

          case 4:
            return EPlieutenant;
            break;

          case 5:
            return EPcaptain;
            break;

          case 6:
            return EPmajor;
            break;

          case 7:
            return EPcolonel;
            break;

          case 8:
            return EPgeneral;
            break;
            
          case 9:
            return EPmarshal;
            break;

          case 10:
            return EPbomb;
            break;

          case 11:
            return EPflag;
            break;

        }
        return EPnone;
}

/* SPos Event_IdBoard(int x,int y){

}
*/



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

