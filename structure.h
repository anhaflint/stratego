#include <stdbool.h>

// structures
#ifndef _STRUCTURE_H
	#define _STRUCTURE_H

// Etat d'une case du jeu
typedef enum
{
	ECnone,
	EClake,
	ECred,
	ECblue
} EColor;

typedef enum
{
	EPbomb=0,
	EPspy,
	EPscout,
	EPminer,
	EPsergeant,
	EPlieutenant,
	EPcaptain,
	EPmajor,
	EPcolonel,
	EPgeneral,
	EPmarshal,
	EPflag, // 11
	EPnone,// 12
} EPiece;

typedef struct
{
	EColor content;
	EPiece piece;
} SBox;


// Structure de représentation du jeu avec son plateau
typedef struct
{
	SBox board[10][10];	// Tableau du jeu de 10 cases par 10. dim1=ligne dim2=colonne
	unsigned int redOut[11];	// Tableau de comptage des pièces rouges éliminées (indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10
	unsigned int blueOut[11];	// Tableau de comptage des pièces bleues éliminées (indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10
} SGameState;

// Structure de représentation d'un mouvement
typedef struct
{
	int line;
	int col;
} SPos;

// Structure de représentation d'un mouvement
typedef struct
{
	SPos start;
	SPos end;
} SMove;


typedef struct {
	unsigned int nbPenalty;	// nombre de pénalités du joueur
	EColor Color;		// couleur du joueur (const pour éviter la triche)
	SBox Pboard[10][10]; // tableau qui comprend la copie du gamestate dans le bon sens pour le joueur
	int nbCoups; 
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
	char Player1Name[16];
	char Player2Name[16];
	SGameMode Mode; 
	EColor ColorPlayer1;
}SGameConfig;

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