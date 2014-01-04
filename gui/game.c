#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

// Tous les tableaux sont comptés avec le 0,0 en bas à gauche
// Tous les indices donnés en commentaires sont comptés à partir de 0 (indice 3 = 4eme ligne du tableau)


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
		{  // l'affichage commence par le haut du gamestate
			printf(" [%d|%d] ", gamestate.board[9-i][j].content, gamestate.board[9-i][j].piece);
		}
		printf("\n");
	}

	for(i=0; i<11; i++)
	{
		printf("[%d]       [%d]\n", gamestate.redOut[i], gamestate.blueOut[i]);
	}
	printf("\n");
}

void DisplayPlayerGS(SBox board[10][10])
{
	int i, j; 
	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{  // l'affichage commence par le haut du gamestate
			printf(" [%d|%d] ", board[9-i][j].content, board[9-i][j].piece);
		}
		printf("\n");
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
 * initialise les couleurs des pions dans les plateaux des joueurs mais pas leur valeur
 */
void Game_InitPlayer(EPlayer* player1, EPlayer* player2, SGameConfig* gameconfig)
{
	player1->nbPenalty = 0;
	player2->nbPenalty = 0;
	int i, j;
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
	// Mise a jour de la couleur du joueur 1 dans la config du jeu
	gameconfig->ColorPlayer1 = player1->Color;
	// Remplissage des tableaux des joueurs
	for (i=0; i<10; i++)
	{
		for (j=0; j<10; j++)
		{
			if (i < 4) // Mise a jour des couleurs des pions dans le gamestate
			{
				// bas des plateaux des joueurs sont de la couleur du joeur
				player1->Pboard[i][j].content = player1->Color;
				player2->Pboard[i][j].content = player2->Color;
				// haut des plateaux des joueurs sont de la couleur de l'adversaire du joueur
				player1->Pboard[9-i][j].content = player2->Color;
				player2->Pboard[9-i][j].content = player1->Color;

			}
			else if (i>3)
			{ 
				// pieces du joueur adverse non renseignées pour ne pas tricher
				player1->Pboard[i][j].piece = EPnone;
				player2->Pboard[i][j].piece = EPnone;

				// lignes vides du milieu  (indices 4 et 5)
				if (i<=5)
				{
					// Couleur des cases vides : Rien
					player1->Pboard[i][j].content = ECnone;
					player2->Pboard[i][j].content = ECnone;
					// Pieces des cases vides : Rien pour l'instant
					player1->Pboard[i][j].piece = EPnone;
					player2->Pboard[i][j].piece = EPnone;
				

					// Lacs
					if ((j==2)||(j==3)||(j==6)||(j==7))
					{
						player1->Pboard[i][j].content = EClake;
						player2->Pboard[i][j].content = EClake;					
					}
				}
			}
		}
	}
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
			// Toutes les cases sont vides au début du jeu
			gamestate->board[i][j].piece = EPnone;
			if (i < 4)
			{
				// Bas du gamestate (lignes de 0 à 3)
				gamestate->board[i][j].content = ECred;
				// Haut du gamestate (lignes de 6 à 9)
				gamestate->board[9-i][j].content = ECblue; 
			}
			else if ((i>=4) && (i<=5))
			{
				// La case ne contient pas de pion donc la couleur est nulle et le contenu aussi
				gamestate->board[i][j].content = ECnone;
				// Placement des lacs
				if ((j==2)||(j==3)||(j==6)||(j==7))
					gamestate->board[i][j].content = EClake;
			}
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
	int RETURN = 0; // ERROR
	int i = start.line;
	int	j = start.col;
	/* En fonction de la couleur du joueur, on regarde differentes parties du tableau du gamestate
	 * On regarde si la couleur du pion selectionné par le joueur est la bonne
	 * On regarde si sa piece est un scout : si oui, on renvoie 2 car on doit savoir pour la validité du mouvement
	 * On regarde si la piece est une piece mobile qui n'est pas un scout : @return value = 1
	 * si le pion n'est pas une piece mobile, la couleur selectionnée est mauvaise ou si la case est vide : @return value = 0
	 */

	/* Pas besoin car on regarde directement le gamestate du joueur, qui est déjà dans le sens de display
	 * A  effacer plus tard ---------------------------------------------------------------------------------------
	if (player.Color == ECblue) // on regarde différentes parties du tableau du gamestate en fonction de la couleur
	{ // Bleu, indice i € [6, 9] haut du tableau

	}
	else // Rouge, indice i € [0,3], bas du tableau
	{
		i = 9 - start.line;
		j = 9 - start.col;
	}
	*/

	EColor _color = player.Pboard[i][j].content; // couleur de la piece selectionnée sur le gamestate du joueur
	EPiece _piece = player.Pboard[i][j].piece;  // piece selectionnée en vrai sur le gamestate du joueur

	if (_color == player.Color) // Le joueur cherche bien à bouger ses pions
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
 * @param SBox* board[10][10] 
 *				gamestate du joueur, avec le tableau orienté vers le bas
 */
void Game_CpyGameState(SGameState* gamestate, EPlayer* player, EPiece boardInit[4][10])
{
	int k, l; 
	// k : lignes du tableau 4*10
	// l : colonnes du tab 4*10
	if (player->Color == ECred)
	{// On remplie le bas du gamestate
		for (k=0; k<4; k++)
		{
			for (l=0; l<10; l++)
			{
				gamestate->board[k][l].piece = boardInit[k][l];
			}
		}
	}
	else if ( player->Color == ECblue)
	{// On remplie le haut du gamestate en retournant le tableau de 4*10 de 180°
		for (k=0; k<4; k++)
		{
			for (l=0; l<10; l++)
			{
				gamestate->board[9-k][9-l].piece = boardInit[k][l];
			}
		}
	}

}

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
