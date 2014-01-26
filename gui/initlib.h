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


//procédure d'initialisation des pointeurs de fonction des librairies
void InitStructIA(StructIA *AIfunctions);

//procédure de libération de la mémoire
void freeIA(StructIA *AIfunctions);

//fonction de chargement des IA
int LoadAI(StructIA *AIfunctions, char* path);

#endif