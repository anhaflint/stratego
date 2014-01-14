#ifndef _GAME_H
#define _GAME_H

#include "../structure.h"

//--------------------------------------------fonctions de gestion de jeu et arbitrage------------------------------------------------
// valables pour un joueur humain ou inhumain (pica)
/*
 * un match est composé de plusieurs jeux
 */

// procédure d'affichage 
void DisplayGS(SGameState gamestate); // OK, peut etre donner la couleur en parametre pour voir comment c'est affiché pour le joueur
void DisplayPlayerGS(SBox board[10][10]);

// fonction de detection du mode de jeu
SGameMode DetectGameMode(int argc, char *argv[]); // OK


// procédures d'initialisation
// procédure de recopie des tableaux des joueurs dans le tableau de l'arbitre à l'initialisation et le gamestate des joueurs (dans le bon sens)	
void Game_CpyInitGameState(SGameState* gamestate, EPlayer* player, EPiece boardInit[4][10]);
void Game_InitPlayer(EPlayer* player1, EPlayer* player2, SGameConfig* gameconfig, int nbCoups);
void Game_InitGameState(SGameState* gamestate); // voir si on init direct toutes les lignes de couleur
void Game_RazSBox(SBox *box);


// fonctions de verification de mouvements
int Game_CheckPosition(SPos start, EPlayer player, SGameState gamestate); // OK, a verifier pour l'inversion du gamestate
int Game_CheckMove(SMove move, EPlayer player, SGameState gamestate, int position);
SMove Player_NextMove(const SGameState * const gamestate);
SMove Game_TranslateMove(SMove move, EPlayer player, int etat); 

// fonction qui effectue le mouvement
void Game_DoMove(SGameState* game,SMove move, EPlayer *MovingPlayer, EPlayer *Other); 
// fonction qui retourne le gagnant du combat
SBox Game_Fight(SBox player1, SBox player2);


// procédure de vérification de la fin du jeu
void Game_End(SGameState gamestate, const EColor color); 
void Game_EndMatch();

// fonction de gestion des pénalités
void Game_AddPenalty();	// idée : variable statique ? allouées au début du programme et libérées à la fin



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
