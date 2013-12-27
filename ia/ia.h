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
 	int caution;
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

//------------------------ Fonctions internes à l'IA -------------------------//

//----------- Fonctions utilisées à chaque tour de jeu -----------//

//----- updateData() -----//

/**
* Met à jour les données internes avec les nouvelles données fournies par l'arbitre
*@param const SGameState * const gameState
*        l'état du jeu courant
*/
void updateData(const SGameState * const gameState);

//----- analyzeBoard() -----//

/**
* Analyse des mouvements possibles sur le plateau par l'IA, stockage en interne
*/
void analyzeBoard();

/**
* Analyse le mouvement de (i,j) à (new_i, new_j), vérifiant si c'est en ligne
* @param unsigned int i
*   Ligne sur laquelle est la pièce dont le mouvement est à analyser
* @param unsigned int j
*   Colonne sur laquelle est la pièce dont le mouvement est à analyser
* @param int new_i
*   Ligne sur laquelle est la case sur laquelle on veut tester le mouvement
* @param int new_j
*   Colonne sur laquelle est la case sur laquelle on veut tester le mouvement
* @param int is_i
*   Vaut 1 si le déplacement à analyser est vertical, 0 sinon
* @param int lim
*   Limite de déplacement sur le plateau dans la direction du mouvement (0 ou 9)
* @param unsigned int* compteur
*   Compteur du nombre de mouvements possibles au total
*/
void addAnalyzedMove(unsigned int i, unsigned int j, int new_i, int new_j, int is_i, int lim, unsigned int* compteur);

//----- decideMove() -----//

/**
* Renvoie le mouvement à faire qui a été décidé par l'IA
* @param SGameState gameState
* 	l'état du jeu courant
* @return SMove
* 	mouvement à faire, décidé par l'IA
*/
SMove decideMove(const SGameState * const  gameState);

/**
* Donne l'information sur la pièce ennemie voisine pour évaluer le risque encouru si on effectue le mouvement
* @param myPiece est la pièce qui effectue le mouvement 
* @param enemyPiece est la pièce ennemie voisine à analyser pour donne un grade de risque au mouvement effectuer par myPiece
* @param evaluationType permet de savoir si on evalue la piece ennemie voisine ou si on attaque l'ennemi
*/
int attributionRank(EPiece myPiece,EPiece enemyPiece,bool evaluationType);

/**
* Classe les mouvements possibles en fonction du risque encouru
* @param riskedMoves est le tableau qui contient tous les movements courants risqués
* @param normalMoves est le tableau qui contient tous les movements courants  qui ne sont pas risqués
*/
void evaluateMoves(GroupMoves *normalMoves,GroupMoves *riskedMoves);

/**
* A commenter
*
*/
void globalEvaluation(GroupMoves *priorityMoves, GroupMoves riskedMoves);

/**
* A commenter
*
*/
SMove chooseMove(const SGameState * const gameState, GroupMoves moves);

//----- saveMove() -----//

/**
* Enregistre le plateau si on a fait un déplacement simple
* @param SGameState gameState
* 	l'état du jeu courant
*/
void saveMove(const SGameState * const gameState);

//----------- Fonctions utilisées à l'envoi d'un combat par l'arbitre -----------//

/**
* Calcule et fais les remplacements sur le plateau selon le 
* résultat de Piece A qui attaque Piece B
* @param EPiece PieceA
*	Pièce attaquante
* @param EPiece Piece B
*   Pièce attaquée
* @param SPos APos
*	Position de la pièce qui attaque
* @param Spos BPos
* 	Position de la pièce attaquée
*/
void analyseFight(EPiece PieceA, EPiece PieceB, SPos APos, SPos BPos);

/**
*  Renvoie le gagnant du combat dans lequel la pièce A attaque la pièce B (A != B)
* @param EPiece A
*  Pièce attaquante
* @param EPiece B
*  Pièce attaquée
* @return EPiece
*  Pièce gagnante du combat
*/
EPiece winnerFight(EPiece A, EPiece B);

//----------- Fonctions à supprimer si inutilisées à la fin -----------//

/**
* Vérification du mouvement décidé par l'IA
*/
void checkMove();

/**
* permet de savoir si pour une pièce à une position donnée,
* si on la deplace dans une direction donnée on est hors du tableau de jeu ou pas
* @param position 
	est la position qui déplacée dans la direction piecedirection est evaluée pour savoir si oui ou non on sort du tableau
* @param piecedirection 
	est la direction qu'on donne à une pièce initialement à la Position position 
	pour évaluer si à la nouvelle position obtenue reste dans le tableau
	exemple: position + left = position.col -1 , la nouvelle position à evaluer
*/
bool limiteUnachieved(SPos position, Direction piecedirection);