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

// procédure d'affichage 
void DisplayGS(SGameState gamestate); // OK, peut etre donner la couleur en parametre pour voir comment c'est affiché pour le joueur
void DisplayPlayerGS(SBox board[10][10]); // OK
SMove ScanM();

// fonction de detection du mode de jeu
SGameMode DetectGameMode(int argc, char* argv[], StructIA *AIfunctions1, StructIA *AIfunctions2); // OK

// procédures d'initialisation
// procédure de recopie des tableaux des joueurs dans le tableau de l'arbitre à l'initialisation et le gamestate des joueurs (dans le bon sens)	
void Game_CpyInitGameState(SGameState* gamestate, EPlayer* player, EPiece boardInit[4][10]); // OK
void Game_InitPlayer(EPlayer* player1, EPlayer* player2, SGameConfig* gameconfig, int nbCoups); // OK
void Game_InitGameState(SGameState* gamestate); // OK
int Game_CheckTab(EPiece boardInit[4][10]); // OK
void Game_RazSBox(SBox *box); // OK

// fonctions de verification de mouvements
int Game_CheckPosition(SPos start, EPlayer player, SGameState gamestate); // OK
int Game_CheckMove(SMove move, EPlayer *player, SGameState gamestate, int position); // OK ?  A Tester encore plus
SMove Player_NextMove(EPlayer player, SDL_Event *event, int *continuer);
SMove Game_TranslateMove(SMove move, EPlayer player, int etat);  // OK
SGameState* Game_SwitchGS(SGameState game, EPlayer player);

// fonction qui effectue le mouvement
int Game_DoMove(SGameState* game,SMove move, EPlayer *MovingPlayer, EPlayer *Other, BoardLayout *layout, SGameConfig config, StructIA IA1, StructIA IA2); // OK 
// fonction qui retourne le gagnant du combat
SBox Game_Fight(SBox player1, SBox player2); // OK

// procédure de vérification de la fin du jeu
// renvoie le gagnant
int Game_GotWinner(EPlayer player1, EPlayer player2, SGameState gamestate, int nbCoups);
int analyzeBoard(EPlayer player);
void addAnalyzedMove(unsigned int i, unsigned int j, int new_i, int new_j, int is_i, int lim, unsigned int* compteur, EColor enemyColor, EPlayer player);

// Init le nombre de victoire des joueurs pour tout un MATCH
void Game_Start(EPlayer *player1, EPlayer *player2, SGameConfig *config);
int Game_EndMatch(EPlayer player1, EPlayer player2, SGameConfig config, SGameState gamestate, int nbCoups);

// fonction de gestion des pénalités
void Game_AddPenalty(EPlayer *player, SMove nextmove);	// idée : variable statique ? allouées au début du programme et libérées à la fin

// initialisation du jeu pour le joueur humain (placement des pieces)
void Game_Begin(EPlayer *player1, EPlayer *player2, SGameState *game, SGameConfig *gameconfig, int nbCoups);


void game_PvP();	
void game_IAvsP();
void game_IAvsIA();

#endif
