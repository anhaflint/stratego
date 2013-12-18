
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

// fonction d'initialisation de la structure contenant toutes les images à utiliser
void BoardLayout_Init(BoardLayout layout);

void Display_Init(BoardLayout layout); 	
										// Affichage du départ : image de fond, tuiles sur les cotes

// fonction d'affichage du plateau pendant le jeu

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

//fonction de detection du mode de jeu
 
int DetectGameMode(int NbJoueur);


// procédure d'initialisation des variables de la structure joueur 

void Game_InitPlayer();	
// procédure d'initialisation de l'etat du jeu

void Game_InitGameState(SGameState* gamestate);


// fonction pour vérifier si la pièce de départ est bien placée 
int Game_CheckPosition(SPos start);


// fonction pour vérifier si un mouvement est valide

int Game_CheckMove(SMove move);


// procédure pour effectuer le mouvement
void Game_DoMove(SGameState* game,SMove move); 


// procédure de vérification de la fin du jeu

void Game_End(SGameState gamestate, const EColor color); 



void Game_EndMatch(); 	// "Voulez-vous rejouer ?" "O/n" si oui, incrementation d'un compteur de jeux 
					  	//pour savoir à la fin du match qui a gagné, sinon, on arrête et on donne le gagnant du match

void Game_AddPenalty();	// idée : variable statique ? allouées au début du programme et libérées à la fin

// procédure de recopie des tableaux des joueurs dans le tableau de l'arbitre à l'initialisation

void Game_CpyGameState(SGameState* gamestate, const EColor color, EPiece boardInit[4][10]);


//------------------
//Events et Acquisitions
//------------------




// ------------------------------------------fonctions à utiliser pour gèrer un joueur humain----------------------------------------

SMove Event_Boardclick(SGameState gamestate); // Fonction d'interprétation des évents. 
										// Traduction de la position de la souris en pixels -> [i,j]
void Game_Begin(const EColor color, EPiece boardInit[4][10]);

fonction de demande du prochain mouvement au joueur humain

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
