
//-------------------------------------------------------------
//                   API DU BINOME GUI
//-------------------------------------------------------------





//------------------
//Affichages du plateau au differentes phases du jeu
//------------------

typedef struct _BoardLayout
{
	SDL_Rect PiecesLayout[26];
	SDL_Surface *Background;    //image de fond
	SDL_Surface *Screen;		//surface de l'ecran
	SDL_Surface *Fight; 		//image affichee lors d'un combat si jamais on en met une
	SDL_Rect DisplayTab[10][10];//tableau contenant les positions des pions à afficher
	SDL_Surface *AllPieces;
}BoardLayout;


/* fonction d'initialisation de la structure contenant toutes les images à utiliser
 * @param BoardLayout layout
 * 			images du jeu
 * 			à passer par adresse &layout
 *			fonction dans laquelle on loadera tous les BMP dans la structure
 */
void BoardLayout_Init(BoardLayout layout);

/*
 * @param SDL_Surface* window 
 *		surface sur laquelle on va blitter les éléments dans la fonction
 */
void Display_Init(BoardLayout layout); 	
										// Affichage du départ : image de fond, tuiles sur les cotes
									 	// Il y aura un affichage de tableaux de pieces du jeu à gauche pour permettre au joueur de placer 
										// ses pieces : il n'y a pas besoin de creer de tableaux en mémoire je crois.
										// on ne peut pas utiliser les tab redOut et blueOut pour le début car il faudrait pouvoir tester
										// a quel stade du jeu on est (init ou pas) sinon le joueur peut reprendre ses pions après qu'ils
										// aient été éliminés ! il faut donc deux fonctions
/* fonction d'affichage du plateau pendant le jeu
 * @param SDL_Surface* window 
 *		surface sur laquelle on va blitter les éléments dans la fonction
 * @param SGameState gamestate
 * 		état du jeu à afficher
 */
void Display_Board(BoardLayout layout, SGameState gamestate);

void Display_Fight(SDL_Surface* piece);
/**
 * @param EPiece pice 
 *		piece à afficher
 */
void Display_Piece(EPiece piece); // affichage d'une piece
void Display_CpyBg(); // affichage du background sur une petite partie du plateau



//------------------
//Jeu Vérif - Move
//------------------




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


//------------------
//Events et Acquisitions
//------------------




// ------------------------------------------fonctions à utiliser pour gèrer un joueur humain----------------------------------------

SMove Event_Boardclick(SGameState gamestate); // Fonction d'interprétation des évents. 
										// Traduction de la position de la souris en pixels -> [i,j]
//pas besoin de passer l'event en paramètre car c'est une variable locale à la fonction
/* initialisation du jeu pour le jour humain (placement des pieces)
 * à ce moment là on ne verifie pas la validité des mouvements car il ne peut pas acceder au tableau du joueur adverse
 * @param const EColor color 
 * 				couleur du joueur 
 * @param EPiece boardInit[4][10]
 * 				tableau dans lequel le joueur va placer ses pions (on ne peut pas lui donner le gamestate)
 */
void Game_Begin(const EColor color, EPiece boardInit[4][10]);

/* fonction de demande du prochain mouvement au joueur humain
 * @param const SGameState * const gamestate
 * 			etat du jeu pour donner le mouvement à effectuer
 *			const SGameState* :		constance de la valeur pointée
 *			* conste gamestate :	constance de l'adresse contenue dans le pointeur 
 */
SMove Player_NextMove(const SGameState * const gamestate);




//-------------------------------------------------fonctions à utiliser pour gèrer l'IA ---------------------------------------------
typedef void (*pfInitLibrary)(char[50]);					// initialisation de la librairie de l'IA
typedef SMove (*pfNextMove)(const SGameState * const); 		// demande du prochain mouvement à l'IA
typedef void (*pfStartMatch)();								// Initialise l'IA pour tout un match
typedef void (*pfStartGame)(const EColor,EPiece[4][10]);	// L'IA place ses pions
typedef void (*pfEndGame)();								// Remise à Zero de l'IA entre deux jeux (plateaux, variables etc)
typedef void (*pfEndMatch)();								// Remise à Zero de l'IA entre deux matchs
typedef void (*pfAttackResult)(SPos,EPiece,SPos,EPiece);	// Indication du résultat d'une attaque (résultat envoyé à tous les joueurs)
typedef void (*pfPenalty)();								// Indication d'une pénalitée pour règle non respectée -> coup précédent annulé


// ----- structure generale du main()------
// main()
// {
//	// si IA vs IA 
//	game_IAvsIA();
//	// si IA vs Player
//	game_IAvsP();
//	// si PvP
//	game_PvP();	
//
//  return 0;
// }
