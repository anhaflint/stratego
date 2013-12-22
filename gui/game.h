#ifndef _GAME_H
#define _GAME_H

#include "../structure.h"

//--------------------------------------------fonctions de gestion de jeu et arbitrage------------------------------------------------
// valables pour un joueur humain ou inhumain (pica)
/*
 * un match est composé de plusieurs jeux
 */

// procédure d'affichage 
void DisplayGS(SGameState gamestate);

// fonction de detection du mode de jeu
SGameMode DetectGameMode(int argc, char *argv[]);


// procédures d'initialisation
void Game_InitPlayer(EPlayer* player1, EPlayer* player2, SGameConfig* gameconfig);	
void Game_InitGameState(SGameState* gamestate);


// fonctions de verification de mouvements
int Game_CheckMove(SMove move);
int Game_CheckPosition(SPos start);
SMove Player_NextMove(const SGameState * const gamestate);

// fonction qui effectue le mouvement
void Game_DoMove(SGameState* game,SMove move); 


// procédure de vérification de la fin du jeu
void Game_End(SGameState gamestate, const EColor color); 
void Game_EndMatch();

// fonction de gestion des pénalités
void Game_AddPenalty();	// idée : variable statique ? allouées au début du programme et libérées à la fin

// procédure de recopie des tableaux des joueurs dans le tableau de l'arbitre à l'initialisation	
void Game_CpyGameState(SGameState* gamestate, const EColor color, EPiece boardInit[4][10]);

// initialisation du jeu pour le joueur humain (placement des pieces)
void Game_Begin(const EColor color, EPiece boardInit[4][10]);




void game_PvP();	
void game_IAvsP();
void game_IAvsIA();

#endif

//-------------------------------------------------fonctions à utiliser pour gèrer l'IA ---------------------------------------------
typedef void (*pfInitLibrary)(char[50]);					// initialisation de la librairie de l'IA
typedef SMove (*pfNextMove)(const SGameState * const); 		// demande du prochain mouvement à l'IA
typedef void (*pfStartMatch)();								// Initialise l'IA pour tout un match
typedef void (*pfStartGame)(const EColor,EPiece[4][10]);	// L'IA place ses pions
typedef void (*pfEndGame)();								// Remise à Zero de l'IA entre deux jeux (plateaux, variables etc)
typedef void (*pfEndMatch)();								// Remise à Zero de l'IA entre deux matchs
typedef void (*pfAttackResult)(SPos,EPiece,SPos,EPiece);	// Indication du résultat d'une attaque (résultat envoyé à tous les joueurs)
typedef void (*pfPenalty)();								// Indication d'une pénalitée pour règle non respectée -> coup précédent annulé
