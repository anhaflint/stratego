#include "event.h"
#include <stdio.h>
#include <string.h>

SMove Event_Boardclick(SGameState gamestate){

	SDL_Event event;

	while (continuer)
{
     switch(event.type)
   {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONUP:
            positionZozor.x = event.button.x;
           positionZozor.y = event.button.y;
           break;
   }

}
