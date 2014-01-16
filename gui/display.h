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


void Display_Init(BoardLayout layout,EColor color); 	
										// Affichage du départ : tuiles sur les cotes
									 	// Il y aura un affichage de tableaux de pieces du jeu à gauche pour les rouges
										//													   à droite pour les bleus
										// pour permettre au joueur de placer 
										// ses pieces : il n'y a pas besoin de creer de tableaux en mémoire je crois.
										// color =2 : Joueur 1l,  color =3 : Joueur 2 , color=1 : Suppression Aff J1 + J2.

										// on ne peut pas utiliser les tab redOut et blueOut pour le début car il faudrait pouvoir tester
										// a quel stade du jeu on est (init ou pas) sinon le joueur peut reprendre ses pions après qu'ils
										// aient été éliminés ! il faut donc deux fonctions
 
void Display_PieceInit(EPiece Piece, SPos posPiece, BoardLayout layout,EColor color); // affichage d'une piece


void Display_ReinitDisplayBoard(BoardLayout layout); // Réinit Aff plateau

 //fonction de test de retour EPiece
void Display_EPieceTest(EPiece Pieces[4][10]);
 
void Display_BoardPlayer(BoardLayout layout, EPlayer player);

/*



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