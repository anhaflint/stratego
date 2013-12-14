//------------------------------- Structures --------------------------------//

typedef struct{
	SBox box;
	bool isVisible;
	bool isBomb;
}InfoPiece;

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

//------------------------ Fonctions internes à l'IA -------------------------//

/**
* Met à jour les données internes avec les nouvelles données fournies par l'arbitre
*@param SGameState gameState
*        l'état du jeu courant
*/
void updateData(gameState);

/**
* Analyse des mouvements possibles sur le plateau par l'IA, stockage en interne
*/
void analyzeBoard();

/**
* Renvoie le mouvement à faire qui a été décidé par l'IA
*@param SGameState gameState
*        l'état du jeu courant
*@return SMove
*        mouvement à faire, décidé par l'IA
*/
SMove decideMove(gameState);

/**
* Vérification du mouvement décidé par l'IA
*/
void checkMove();