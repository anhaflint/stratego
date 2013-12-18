/ ------------------------------------------fonctions à utiliser pour gèrer un joueur humain----------------------------------------

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
