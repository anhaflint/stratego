#ifndef _DISPLAY_H
	#define _DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


// DECLARATION D'UNE CELLULE : CASE DU PLATEAU
typedef struct
{
SDL_Rect     position;  	//Position relative d'une case 
EPiece  	 cellaff;
EColor		 cellcol;		//																	
}Cell;						// Utile pour connaître le remplissage de chaqune des cases Couleurs/Pieces | NULL => Background
							//															


typedef struct
{
	SDL_Rect PiecesLayout[26];  // Position des différentes images sur le patron d'images final
	SDL_Rect RECTredOut[11];	// Tableau de rect . comptage des pièces rouges éliminées (indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10)
	SDL_Rect RECTblueOut[11];	// Tableau de rect . comptage des pièces bleues éliminées (indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10)
	SDL_Surface *Patron;		// Stockage du patron d'images
	SDL_Surface *Background;    // Image de fond 
	SDL_Surface	*Placement;		// Image grisée
	SDL_Surface *Penalty;		// Image Pénalité
	SDL_Surface *J1;			// Image jeton J1
	SDL_Surface *J2;			// Image jeton J2
	SDL_Surface *Killed;		// Patron des nombres ( aff nombre pièces éliminées)
	SDL_Surface *Screen;		// Surface de l'ecran
	SDL_Surface *Fight; 		// Stocke image affichée lors d'un combat si jamais on en met une
	//SDL_Surface *New;			// Image Nouveau Jeu
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


void Display_Init(BoardLayout layout,EColor color,int nbPiecesRestantes[13]); 	
// Affichage du départ : tuiles sur les cotes
// Il y aura un affichage de tableaux de pieces du jeu à gauche pour les rouges
//													   à droite pour les bleues.
// color =2 : Rouge ,  color =3 : Bleu , color=1 : Suppression Aff J1 + J2.
// Tab : pieces restantes : pour affichage du filtre noir, car plus de pieces plaçables
 
 // affichage d'une piece
void Display_PieceInit(EPiece Piece, SPos posPiece, BoardLayout *layout,EColor color); 

// affichage combat
void Display_fight(SMove moveaff,SGameState game,EPlayer *player, BoardLayout *layout); 

//affichage latéral des pièces durant le jeu
void Display_lateralPieces(BoardLayout layout,EColor color);

// affichage d'une pénalité
void Display_Penalty(BoardLayout *layout,EPlayer player); 

// affichage d'un tour de jeu
void Display_affPlayer(BoardLayout *layout, int joueur);

// affichage du nombre de pièces éliminées
void Display_killedPieces(BoardLayout *layout,EPlayer player,SGameState gamestate);

// réinitialisation du plateau
void Display_ReinitDisplayBoard(BoardLayout layout); // Réinit Aff plateau

// fonction affichage d'un plateau de jeu joueur
void Display_BoardPlayer(BoardLayout *layout, EPlayer player);

 //fonction de test de retour EPiece
void Display_EPieceTest(EPiece Pieces[4][10]);

#endif