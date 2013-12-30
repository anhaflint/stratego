#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../structure.h"
#include "display.h"
#include "../stratego.h"

//gcc -Wall mainTestDisplay.c  display.c -lSDL -o tdisp



int main()
{

	BoardLayout layout;
	BoardLayout_Init(&layout);
	//Display_Init(layout,int noJoueur);

	return 0;
}

