#ifndef _GAME_H
	#define _GAME_H

#include "../structure.h"
#include <SDL/SDL.h>
#include "display.h"
#include "initlib.h"

//--------------------------------------------fonctions de gestion de jeu et arbitrage------------------------------------------------
// valables pour un joueur humain ou inhumain (pica)
/*
 * un match est composé de plusieurs jeux
 */


// Fonction de detection du mode de jeu
SGameMode DetectGameMode(int argc, char* argv[], StructIA *AIfunctions1, StructIA *AIfunctions2); 

// Procédures d'initialisation, de vérification des tableaux saisis par les joueurs et d'effacement d'une case du tableau
void Game_CpyInitGameState(SGameState* gamestate, EPlayer* player, EPiece boardInit[4][10]); 
void Game_InitPlayer(EPlayer* player1, EPlayer* player2, SGameConfig* gameconfig, int nbCoups); 
void Game_InitGameState(SGameState* gamestate);
int Game_CheckTab(EPiece boardInit[4][10]);
void Game_RazSBox(SBox *box);

// Initialisation du jeu pour le joueur humain (placement des pieces)
void Game_Begin(EPlayer *player1, EPlayer *player2, SGameState *game, SGameConfig *gameconfig, int nbCoups);


// Fonctions de verification de mouvements
int Game_CheckPosition(SPos start, EPlayer player, SGameState gamestate); 
int Game_CheckMove(SMove move, EPlayer *player, SGameState gamestate, int position);
SMove Player_NextMove(EPlayer player, SDL_Event *event, int *continuer);
SMove Game_TranslateMove(SMove move, EPlayer player, int etat);
SGameState* Game_SwitchGS(SGameState game, EPlayer player);

// Fonction qui effectue le mouvement
int Game_DoMove(SGameState* game,SMove move, EPlayer *MovingPlayer, EPlayer *Other, BoardLayout *layout, SGameConfig config, StructIA IA1, StructIA IA2); // OK 

// Fonction qui retourne le gagnant du combat
SBox Game_Fight(SBox player1, SBox player2); 

// Procédure de vérification de la fin du jeu
int Game_GotWinner(EPlayer player1, EPlayer player2, SGameState gamestate, int nbCoups);
int analyzeBoard(EPlayer player);
void addAnalyzedMove(unsigned int i, unsigned int j, int new_i, int new_j, int is_i, int lim, unsigned int* compteur, EColor enemyColor, EPlayer player);


// Initialisation du nombre de victoire des joueurs pour tout un match
void Game_Start(EPlayer *player1, EPlayer *player2, SGameConfig *config);

// Fin de match
int Game_EndMatch(EPlayer player1, EPlayer player2, SGameConfig config, SGameState gamestate, int nbCoups);

// Fonction de gestion des pénalités
void Game_AddPenalty(EPlayer *player, SMove nextmove);	// idée : variable statique ? allouées au début du programme et libérées à la fin



#endif
