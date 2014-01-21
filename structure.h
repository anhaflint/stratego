// structures
#ifndef _STRUCTURE_H
	#define _STRUCTURE_H

#include <stdbool.h>
#include "stratego.h"
// Etat d'une case du jeu

typedef struct {
	unsigned int nbPenalty;	// nombre de pénalités du joueur
	EColor Color;		// couleur du joueur (const pour éviter la triche)
	SBox Pboard[10][10]; // tableau qui comprend la copie du gamestate dans le bon sens pour le joueur
	int nbCoups;
	int winnings; 
}EPlayer;


typedef enum
{
	HUMAN_HUMAN=0,
	IA_HUMAN,
	IA_IA,
	ERROR,
}SGameMode;

typedef struct 
{
	char Player1Name[50];
	char Player2Name[50];
	SGameMode Mode; 
	EColor ColorPlayer1;
	unsigned int nbJeux;
}SGameConfig;


/*typedef struct 
{
	SMove move;

};??*/
//----------------------- Structures et énumérations ------------------------//

/* Stockage en interne du plateau, avec
des informations supplémentaires sur les pièces */
typedef struct{
	SBox box;
	bool isVisible;
	bool isBomb;
}InfoPiece;

/* Structure stockant un mouvement et
son niveau de risque */
typedef struct{
	SMove move;
 	float caution;
}Mymove;

/* Structure contenant la liste des mouvements
possibles ainsi que leur nombre */
typedef struct{
 	Mymove listMoves[172];
 	int lenght_list;
}GroupMoves;

/* Enumération des différentes stratégies
utilisables par l'IA */
typedef enum{
	str_default=0,
	offensive,
	defensive,
	malicious,
	protective,
	risked,
	bluff,
	agressive,
	searchme,
}Strategy;

#endif