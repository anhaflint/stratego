#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../structure.h"
#include "display.h"

#ifndef _EVENT_H
	#define _EVENT_H

// ------------------------------------------fonctions à utiliser pour gèrer un joueur humain----------------------------------------


void Event_InitGameState(SDL_Event *event, int *continuer,int color,BoardLayout layout, EPiece Pieces[4][10]);
/* Fonction appellé en boucle pour Analyse du Placement Inital des Pieces
	Paramètres : -Un Event
	 			 -un entier responsable de la sortie ou non de la boucle d'appel.
	 			 -un entier pour traiter le placement des pions de la couleur : 1 : rouge
	 			 																2 : bleu
	 			 																3:  réinit
	Renvoi : Un tab de pieces pour un joueur
	*/

EPiece Event_IdPiece_Init(int x,int y, int color);

// SPos Event_IdBoard(int x,int y);


/*
SMove Event_Boardclick(SGameState gamestate); 	// Fonction d'interprétation des évents. 
												// Traduction de la position de la souris en pixels -> [i,j]
		//pas besoin de passer l'event en paramètre car c'est une variable locale à la fonction
*/

#endif