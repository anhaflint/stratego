
//-------------------------------------------------------------
//                   API DU BINOME GUI
//-------------------------------------------------------------





//------------------
//Affichages
//------------------
void display_init();
void display_piece();
void display_cpybg();

//------------------
//Jeu Vérif - Move
//------------------
int game_checkposition(SPos start);						// Vérifier si la pièce de départ est bien placée 
int game_checkmove(SMove move); 						// Vérifier si un mouvement est valide
void game_domove(SGameState* game,SMove move);	// Effectuer le mouvement


void game_match(const EColor color);

void game_begin(EPiece boardInit[4][10]);

void game_end();

void game_endMatch();

void game_addpenalty();

//------------------
//Events et Acquisitions
//------------------

// ---JOUEUR---

SMove event_boardclick(<Etat du jeu>,SDL_Event *event); 
// Fonction d'interprétation des évents. Traduction de la position de la souris en pixels -> [i,j]

//------IA ----
typedef SMove (*pfNextMove)(const SGameState * const); //