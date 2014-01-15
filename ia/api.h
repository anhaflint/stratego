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

/* Enumération pour les direction
--> Si inutilisé à la fin, supprimer */
typedef enum{
	left=0,
	right,
	top,
	bottom,
}Direction;

//-------------------------- Fonctions de l'API IA --------------------------//

/**
 * Initialiser la librairie
 * @param char name[50]
 *	nom associé à la librairie
 */
void InitLibrary(char name[50]);

/**
 * Initialiser l'IA pour un match
 */
void StartMatch();

/**
 * Initialiser l'IA pour une manche (d'un match)
 * @param const EColor color
 *	couleur du joueur
 * @param EPiece boardInit[4][10]
 *	variable en sortie : initialisation du jeu pour un joueur (ligne 0 = ligne la plus proche du joueur)
 */
void StartGame(const EColor color,EPiece boardInit[4][10]);

 /**
 * Fin d'une manche (d'un match)
 */
void EndGame();

/**
 * Fin d'un match
 */
void EndMatch();

 /**
 * Prise de décision de la part de l'IA
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @return SMove
 *	mouvement à effectuer par l'IA
 */
SMove NextMove(const SGameState * const gameState);

 /**
 * Indication du résultat d'une attaque (résultat envoyé à tous les joueurs)
 * @param SPos armyPos
 *	position de l'élément de l'armée du joueur (attaquant ou attaquée)
 * @param EPiece armyPiece
 *	type de de l'élément de l'armée du joueur (attaquant ou attaquée)
 * @param SPos enemyPos
 *	position de l'élément de l'ennemi (attaquant ou attaquée)
 * @param EPiece enemyPiece
 *	type de de l'élément de l'ennemi (attaquant ou attaquée)
 */
void AttackResult(SPos armyPos,EPiece armyPiece,SPos enemyPos,EPiece enemyPiece);

 /**
 * Indication d'une pénalitée pour règle non respectée -> coup précédent annulé
 */
void Penalty();
