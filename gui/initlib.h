#ifndef _INITLIB_H
	#define _INITLIB_H

#include "../stratego.h"

typedef struct 
{
	void *lib;
	pfInitLibrary InitLibrary;
	pfStartMatch StartMatch;
	pfStartGame StartGame;
	pfEndGame EndGame;
	pfEndMatch EndMatch;
	pfNextMove NextMove; 
	pfAttackResult AttackResult;
	pfPenalty Penalty;
} StructIA;

void InitStructIA(StructIA *AIfunctions);
void freeIA(StructIA *AIfunctions);
int LoadAI(StructIA *AIfunctions, char* path);

#endif