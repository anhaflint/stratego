#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#ifndef _EVENT_H
	#define _EVENT_H

// ------------------------------------------fonctions à utiliser pour gèrer un joueur humain----------------------------------------


void Event_InitGameState(SDL_Event *event, int *continuer);
/* Fonction appellé en boucle pour Analyse du Placement Inital des Pieces
	Paramètres : Un Event, et un entier responsable de la sortie ou non de la boucle d'appel.
	*/




/*
SMove Event_Boardclick(SGameState gamestate); 	// Fonction d'interprétation des évents. 
												// Traduction de la position de la souris en pixels -> [i,j]
		//pas besoin de passer l'event en paramètre car c'est une variable locale à la fonction
*/

#endif