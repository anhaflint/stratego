
//-------------------------------------------------------------
//                   API DU BINOME GUI
//-------------------------------------------------------------





//------------------
//Affichages
//------------------
void display_init(); // Affichage du départ : image de fond, tuiles sur les cotes
void display_piece(); // affichage d'une piece
void display_cpybg(); // affichage du background sur une petite partie du plateau



//------------------
//Jeu Vérif - Move
//------------------




// ---- structure ----
typedef struct _Player {
	unsigned int NbPenalty;	// nombre de pénalités du joueur
	const EColor Color;		// couleur du joueur (const pour éviter la triche)
}Player;


//--------------------------------------------fonctions de gestion de jeu et arbitrage------------------------------------------------
// valables pour un joueur humain ou inhumain (pica)
/*
 * un match est composé de plusieurs jeux
 */

int DetectGameMode(int NbJoueur);		// si argv[1]==0 : IA vs IA
										// si argv[1]==1 : P vs IA
										// si argv[1]==2 : PVP
void game_initPlayer();					// initialisation des variables de la structure joueur au début de chaque jeu
										// initialise les deux joueurs en même temps 


int game_checkposition(SPos start);						// Vérifier si la pièce de départ est bien placée 
int game_checkmove(SMove move); 						// Vérifier si un mouvement est valide
void game_domove(SGameState* game,SMove move);			// Effectuer le mouvement
void game_end(); 	// condition de fin d'un jeu : un joueur n'a plus de drapeau (perdu) ou plus de pieces mobiles 
					// par exemple si plus que des bombes + flag en jeu, ou si toutes les pièces mobiles sont entourées par des bombes
void game_endMatch(); 	// "Voulez-vous rejouer ?" "O/n" si oui, incrementation d'un compteur de jeux 
					  	//pour savoir à la fin du match qui a gagné, sinon, on arrête et on donne le gagnant du match

void game_addpenalty();	// idée : variable statique ? allouées au début du programme et libérées à la fin





//------------------
//Events et Acquisitions
//------------------




// ------------------------------------------fonctions à utiliser pour gèrer un joueur humain----------------------------------------

SMove event_boardclick(<Etat du jeu>,SDL_Event *event); // Fonction d'interprétation des évents. 
														// Traduction de la position de la souris en pixels -> [i,j]

void game_begin(const EColor color, EPiece boardInit[4][10]); // initialisation du jeu pour le joueur humain



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