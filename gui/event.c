#include "event.h"

void Event_InitGameState(SDL_Event *event, int *continuer){

switch(event->type)
   {
        case SDL_QUIT:
            continuer=0;
            break;
        case SDL_MOUSEBUTTONUP:
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

