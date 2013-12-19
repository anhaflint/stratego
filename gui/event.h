#ifndef _EVENT_H
	#define _EVENT_H

/ ------------------------------------------fonctions à utiliser pour gèrer un joueur humain----------------------------------------

SMove Event_Boardclick(SGameState gamestate); 	// Fonction d'interprétation des évents. 
												// Traduction de la position de la souris en pixels -> [i,j]
		//pas besoin de passer l'event en paramètre car c'est une variable locale à la fonction
