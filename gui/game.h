
// ---- structure ----
typedef struct _Player {
	unsigned int NbPenalty;	// nombre de pénalités du joueur
	const EColor Color;		// couleur du joueur (const pour éviter la triche)
}Player;

typedef struct
{
	SBox board[10][10];	// Tableau du jeu de 10 cases par 10. dim1=ligne dim2=colonne
	unsigned int redOut[12];	// Tableau de comptage des pièces rouges éliminées (indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10
	unsigned int blueOut[12];	// Tableau de comptage des pièces bleues éliminées (indexées par la valeur de EPiece : RPflag=0, ..., EPbomb=11
} SGameState;

//--------------------------------------------fonctions de gestion de jeu et arbitrage------------------------------------------------
// valables pour un joueur humain ou inhumain (pica)
/*
 * un match est composé de plusieurs jeux
 */

/* fonction de detection du mode de jeu
 * @param int NbJoueur
 *			nombre de joueurs humains detectés via argv[1]=j j={0,1,2}
 *			si argv[1]==0 : IA vs IA
 *			si argv[1]==1 : P vs IA
 *			si argv[1]==2 : PVP
 * @return value : entier pour faire des tests logiques dans le main
 */
int DetectGameMode(int NbJoueur);


/* procédure d'initialisation des variables de la structure joueur 
 * au début de chaque jeu
 * initialise les deux joueurs en même temps 
 */
void Game_InitPlayer();	
/* procédure d'initialisation de l'etat du jeu
 * @param SGameStae* gamestate
 *			pointeur vers l'etat du jeu
 */
void Game_InitGameState(SGameState* gamestate);


/* fonction pour vérifier si la pièce de départ est bien placée 
 * @param : SPos start
 * 			position de départ du mouvement
 * @return value : entier pour connaitre la validité de la position
 */
int Game_CheckPosition(SPos start);


/* fonction pour vérifier si un mouvement est valide
 * @param : SMove move
 * 			position de début et fin du mouvement à vérifier
 * @Return Value : entier pour connaitre la validité du mouvement
 */
int Game_CheckMove(SMove move);


/* procédure pour effectuer le mouvement
 * @param SGameState* game
 * 			pointeur vers l'état du jeu afin de modifier les differents tableaux
 * @param SMove move
 * 			mouvement à effectuer (mouvement valide, invalide, ou combat)
 */
void Game_DoMove(SGameState* game,SMove move); 


/* procédure de vérification de la fin du jeu
 * @param : SGameState gamestate
 * 			permet de vérifier les pions présents sur le plateau
 * @param : const EColor color
 *			permet de savoir quel joueur on doit vérifier (peut etre inutile)
 * condition de fin d'un jeu : un joueur n'a plus de drapeau (perdu) ou plus de pieces mobiles
 * par exemple si plus que des bombes + flag en jeu, ou si toutes les pièces mobiles sont entourées par des bombes
 */
void Game_End(SGameState gamestate, const EColor color); 



void Game_EndMatch(); 	// "Voulez-vous rejouer ?" "O/n" si oui, incrementation d'un compteur de jeux 
					  	//pour savoir à la fin du match qui a gagné, sinon, on arrête et on donne le gagnant du match

void Game_AddPenalty();	// idée : variable statique ? allouées au début du programme et libérées à la fin

/* procédure de recopie des tableaux des joueurs dans le tableau de l'arbitre à l'initialisation
 * @param SGameState gamestate
 * 				Etat du jeu à modifier
 * @param const EColor color
 * 				couleur du joueur pour lequel on passe le tableau
 * @param EPiece boardInit[4][10]
 *				tableau initialisé du joueur 
 */
void Game_CpyGameState(SGameState* gamestate, const EColor color, EPiece boardInit[4][10]);

