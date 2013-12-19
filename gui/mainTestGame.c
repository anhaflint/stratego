#include <stdio.h>
#include <stdlib.h>
#include "game.h"


//gcc -Wall mainTestGame.c  game.c -o test
int main(int argc, char* argv[])
{
	SGameMode gamemode;
	gamemode = DetectGameMode(argc, argv);
	printf("%d\n", gamemode);
	return 0;
}