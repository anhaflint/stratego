#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../structure.h"
#include "display.h"

#ifndef _EVENT_H
	#define _EVENT_H

// ------------------------------------------fonctions à utiliser pour gèrer un joueur humain----------------------------------------


void Event_InitGameState(SDL_Event *event, int *continuer,EColor color,BoardLayout *layout, EPiece Pieces[4][10]);
/* Fonction appellé en boucle pour Analyse du Placement Inital des Pieces
	Paramètres : -Un Event
	 			 -un entier responsable de la sortie ou non de la boucle d'appel.
	 			 -un entier EColor pour traiter le placement des pions de la couleur :  ECred : rouge
	 			 																		ECblue: bleu
	 			 																		ECnone: réinit
	Renvoi : Un tab de pieces pour un joueur
	*/

EPiece Event_IdPiece_Init(int x,int y, EColor color);

/*
		// Traduction de la position de la souris pixels => EPiece -- Placement
		
*/


SPos Event_IdBoard(int x,int y);

/*
		// Traduction de la position de la souris en pixels -> [i,j]
		
*/

SMove Event_IdMove(SDL_Event *event, SGameState gameState, EPlayer player,int *continuer);

#endif