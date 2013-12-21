#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"


/* fonction de detection du mode de jeu
 * @param char *argv[]
 *			nombre de joueurs humains detectés via argv[1]=j j={0,1,2}
 *			si argv[1]==0 : IA vs IA
 *			si argv[1]==1 : P vs IA
 *			si argv[1]==2 : PVP
 * @param int argc : nombre d'arguments.  par défaut le jeu se lance en humain vs humain
 * @return value : retourne un gamemode (entier)
 */
SGameMode DetectGameMode(int argc, char* argv[])
{
	SGameMode gamemode = ERROR;
	if (argc == 1 || argc >4)
		printf("le nombre d'arguments est incorrect\n");
	if (*argv[1] == '1')
		gamemode = IA_HUMAN;
	else if (*argv[1] == '2')
		gamemode = HUMAN_HUMAN;
	else if (*argv[1] == '0')
		gamemode = IA_IA;
	return gamemode;

}


/* procédure d'initialisation des variables de la structure joueur 
 * au début de chaque jeu
 * initialise les deux joueurs en même temps 
 */
void Game_InitPlayer(EPlayer player1, EPlayer player2, SGameConfig gameconfig)
{
	if (random)

}
/* procédure d'initialisation de l'etat du jeu
 * @param SGameState* gamestate
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

void game_PvP();	
void game_IAvsP();
void game_IAvsIA();
