#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#ifndef _DISPLAY_H
	#define _DISPLAY_H



typedef struct
{
SDL_Rect     position;  	//Position relative d'une case ainsi que sa surface "image" associé 
SDL_Surface  *cellaff;		//																	
}Cell;						// Utile pour connaître le remplissage de chaqune des cases | NULL => Background
							//															| tuileA ou tuileT


typedef struct
{
	SDL_Rect PiecesLayout[26];  // Position des différentes images sur le patron d'images final
	SDL_Surface *Patron;			// Stockage du patron d'images
	SDL_Surface *Background;    // Image de fond 
	SDL_Surface *Screen;		// Surface de l'ecran
	SDL_Surface *Fight; 		// Stocke image affichée lors d'un combat si jamais on en met une
	Cell DisplayTab[10][10];	// Tableau contenant les positions/affichages des pions
}BoardLayout;


/* fonction d'nitialisation de la structure contenant toutes les images à utiliser
 * @param BoardLayout layout
 * 			images du jeu
 * 			à passer par adresse &layout
 *			fonction dans laquelle on loadera tous les positions des BMP de la surface Patron
 */
void BoardLayout_Init(BoardLayout* layout);

//-----------------------------------------------------------------------------------------------

/*
void Display_Init(BoardLayout layout,int noJoueur); 	
										// Affichage du départ : tuiles sur les cotes
									 	// Il y aura un affichage de tableaux de pieces du jeu à gauche pour permettre au joueur de placer 
										// ses pieces : il n'y a pas besoin de creer de tableaux en mémoire je crois.
										// on ne peut pas utiliser les tab redOut et blueOut pour le début car il faudrait pouvoir tester
										// a quel stade du jeu on est (init ou pas) sinon le joueur peut reprendre ses pions après qu'ils
										// aient été éliminés ! il faut donc deux fonctions
 

 //fonction d'affichage du plateau pendant le jeu
 * @param SDL_Surface* window 
 *		surface sur laquelle on va blitter les éléments dans la fonction
 * @param SGameState gamestate
 * 		état du jeu à afficher
 //
void Display_Board(BoardLayout layout, SGameState gamestate);

void Display_Fight(SDL_Surface* piece, BoardLayout layout);
//
 * @param EPiece pice 
 *		piece à afficher
 *	Devra prendre en compte le fait que la pièce retournée est temporairement affichée pour une suivante.
 //

void Display_Piece(SGameState gamestate, SPos posPiece, BoardLayout layout); // affichage d'une piece

void Display_CpyBg(BoardLayout layout, SPos posPiece); // affichage du background sur une petite partie du plateau
*/

#endif