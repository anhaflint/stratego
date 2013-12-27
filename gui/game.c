#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"



/* procédure qui affiche la totalité du gamestate 
 * sous la forme tableau de 10*10 : [couleur | piece]
 * 2 tableaux de 11 cases comptant le nombre de pieces élimninées
 */
void DisplayGS(SGameState gamestate)
{
	int i, j; 
	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			printf(" [%d|%d] ", gamestate.board[i][j].content, gamestate.board[i][j].piece);
		}
		printf("\n");
	}

	for(i=0; i<11; i++)
	{
		printf("[%d]       [%d]\n", gamestate.redOut[i], gamestate.blueOut[i]);
	}
	printf("\n");
}


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
	if(argc >4 || argc == 1)
		printf("le nombre d'arguments est incorrect\n");
	if(argc > 1)
	{
		if (*argv[1] == '0')
			gamemode = IA_IA;
		else if (*argv[1] == '1')
			gamemode = IA_HUMAN;
		else if (*argv[1] == '2')
			gamemode = HUMAN_HUMAN;
	}
	return gamemode;

}


/* procédure d'initialisation des variables de la structure joueur 
 * au début de chaque jeu
 * initialise les deux joueurs en même temps 
 */
void Game_InitPlayer(EPlayer* player1, EPlayer* player2, SGameConfig* gameconfig)
{
	player1->nbPenalty = 0;
	player2->nbPenalty = 0;
	srand(time(NULL)); // initialisation de rand
	if(rand()%2== 0)
	{
		player1->Color = ECred;
		player2->Color = ECblue;
	}
	else
	{
		player1->Color = ECblue;
		player2->Color = ECred;
	}
	gameconfig->ColorPlayer1 = player1->Color;
}


/* procédure d'initialisation de l'etat du jeu
 * @param SGameState* gamestate
 *			pointeur vers l'etat du jeu
 */
void Game_InitGameState(SGameState* gamestate)
{
	int i, j; 
	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			gamestate->board[i][j].content = ECnone;
			gamestate->board[i][j].piece = EPnone;
		}
	}
	for(i=0; i<11; i++)
	{
		gamestate->redOut[i] = 0; // il y a 0 eclaireurs éliminés etc
		gamestate->blueOut[i] = 0;
	}
	
}

/* fonction pour vérifier si la pièce de départ est bien placée 
 * @param : SPos start
 * 			position de départ du mouvement
 * @return value : entier pour connaitre la validité de la position
 */
int Game_CheckPosition(SPos start, EPlayer player, SGameState gamestate)
{
	int i, j;
	int RETURN = 0; // ERROR
	/* En fonction de la couleur du joueur, on regarde differentes parties du tableau du gamestate
	 * On regarde si la couleur du pion selectionné par le joueur est la bonne
	 * On regarde si sa piece est un scout : si oui, on renvoie 2 car on doit savoir pour la validité du mouvement
	 * On regarde si la piece est une piece mobile qui n'est pas un scout : @return value = 1
	 * si le pion n'est pas une piece mobile, la couleur selectionnée est mauvaise ou si la case est vide : @return value = 0
	 */

	if (player.Color == ECred) // on regarde différentes parties du tableau du gamestate en fonction de la couleur
	{ // Rouge, indice i € [6, 9] bas du tableau
		i = start.line;
		j = start.col;
	}
	else // Bleu, indice i € [0,3], haut du tableau
	{
		i = 9 - start.line;
		j = 9 - start.col;
	}

	EColor _color = gamestate.board[i][j].content; // couleur de la piece selectionnée sur le gamestate
	EPiece _piece = gamestate.board[i][j].piece;  // piece selectionnée en vrai sur le gamestate

	if (player.Color == _color) // Le joueur cherche bien à bouger ses pions
	{
		if (_piece == EPscout) 
			RETURN = 2;  // Le scout se deplace différemment
		else if ((_piece > EPbomb)&&(_piece < EPflag)&&(_piece != EPscout)) // piece != bomb, flag ou none 
				RETURN = 1; // piece valide et n'est pas le scout
	}

	return RETURN;
}


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
