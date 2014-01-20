#include <stdio.h> // A enlever à la fin
#include <string.h> // A peut-être enlever à la fin
#include <stdbool.h>
#include "../structure.h"
#include "updateData.h"
#include "analyzeBoard.h"
#include "decideMove.h"
#include "riskProbability.h"
#include "saveMove.h"
#include "api.h"

//------------------------- Données internes de l'IA ------------------------//

Strategy m_strategy; // Stratégie choisie
EColor m_color, m_enemyColor; // Couleur des pièces de l'IA
InfoPiece m_board[10][10]; // Tableau de la structure InfoPiece, qui stocke des pièces et des informations dessus
SMove m_movements[172]; // Tableau contenant les mouvements possibles à chaque tour
SMove m_decidedMove; // Mouvement décidé après une réflexion par l'IA
int m_nbMove; // Nombre de mouvements enregistrés dans le tableau des mouvements
int m_caution; // Variable pour prise de risque : vaut 0 si aucun risque à prendre, 10 si faire des mouvements très risqués
int m_nbRoundTrips; // Nombre d'allers et retours que l'on a fait (pour la règle des 2 cases)
bool m_myMove; // Variable pour connaître le mouvement que l'on a fait au tour précédent : false = mouvement normal et true = attaque
bool m_hisMove; // Variable pour connaître le mouvement que l'ennemi a fait au tour précédent : false = mouvement normal et true = attaque

//-------------------------- Fonctions de l'API IA --------------------------//

void InitLibrary(char name[50])
{
	printf("InitLibrary\n");
	strcpy(name,"Fabien Picarougne");
}

void StartMatch()
{	
	printf("StartMatch\n");
}

void StartGame(const EColor color, EPiece boardInit[4][10])
{
	/* Initialisation du tableau de l'IA avec positionement de pions*/
	printf("Démarrage de StartGame...\n");
	m_color = color;
	m_enemyColor = (m_color == ECblue) ? ECred : ECblue;
	printf("Couleur choisie : %d\n", m_color);
	m_strategy = str_default;
	printf("Stratégie choisie : %d\n", m_strategy);
	m_caution = 5;
	printf("Taux de risque initial : %d\n", m_caution);
	m_nbRoundTrips = 1;
	printf("Nombre d'allers-retours initial : %d\n", m_nbRoundTrips);

	/* Variables servant à 
	l'initialisation de m_board */
	
	int i, j;		
	SPos pos;	
	
	if (m_strategy == defensive)
	{
		EPiece initBoard[4][10] = {{11, 0, 8, 3, 0, 4, 0, 4, 5, 2},
						 		   {0, 7, 3, 3, 5, 0, 3, 3, 5, 2},
						 		   {4, 6, 6, 1, 6, 2, 4, 6, 0, 8},
						 		   {2, 2, 7, 9, 2, 2, 10, 7, 2, 5}};
		memcpy(boardInit, initBoard, sizeof(initBoard));
	}
	else if (m_strategy == str_default)
	{
		EPiece initBoard[4][10] = {{3, 2, 3, 3, 4, 0, 11, 0, 3, 2},
						 		   {6, 4, 7, 1, 7, 5, 0, 4, 0, 4},
						 		   {10, 2, 7, 8, 2, 6, 0, 5, 0, 5},
						 		   {2, 8, 5, 2, 6, 2, 9, 3, 2, 6}};
		memcpy(boardInit, initBoard, sizeof(initBoard));
	}
	else if (m_strategy == offensive)
	{
		EPiece initBoard[4][10] = {{2, 3, 4, 5, 6, 11, 6, 2, 3, 4},
						 		   {2, 3, 4, 6, 3, 7, 5, 4, 2, 3},
								   {6, 8, 2, 0, 7, 0, 1, 0, 0, 5},
								   {2, 2, 10, 5, 0, 2, 9, 7, 8, 0}};
		memcpy(boardInit, initBoard, sizeof(initBoard));
	}
	else if (m_strategy == protective)
	{
		EPiece initBoard[4][10] = {{7, 5, 3, 3, 3, 6, 0, 4, 0, 11},
								   {6, 2, 6, 4, 5, 2, 2, 0, 4, 0},
								   {2, 7, 2, 2, 10, 7, 6, 3, 0, 4},
								   {5, 2, 8, 3, 5, 2, 8, 1, 9, 0}};
		memcpy(boardInit, initBoard, sizeof(initBoard));
	}
	else if (m_strategy == agressive)
	{
		EPiece initBoard[4][10] = {{11, 0, 2, 2, 2, 2, 2, 2, 3, 4},
								   {0, 10, 5, 3, 3, 7, 6, 5, 5, 5},
								   {9, 8, 1, 3, 6, 8, 6, 6, 7, 4},
								   {2, 2, 3, 7, 0, 0, 4, 4, 0, 0}};
		memcpy(boardInit, initBoard, sizeof(initBoard));
	}
	else if (m_strategy == searchme)
	{
		EPiece initBoard[4][10] = {{4, 0, 3, 6, 3, 5, 0, 11, 0, 4},
								   {0, 4, 5, 3, 6, 3, 8, 0, 5, 0},
								   {8, 2, 6, 1, 2, 7, 4, 2, 3, 2},
								   {6, 2, 7, 9, 2, 2, 10, 7, 2, 5}};
		memcpy(boardInit, initBoard, sizeof(initBoard));
	}
	else if (m_strategy == malicious)
	{
		EPiece initBoard[4][10] = {{3, 5, 3, 5, 0, 4, 0, 11, 0, 4},
								   {6, 3, 6, 2, 4, 0, 4, 0, 6, 0},
								   {8, 5, 2, 3, 6, 7, 1, 3, 2, 8},
								   {2, 2, 7, 10, 2, 2, 9, 7, 2, 5}};
		memcpy(boardInit, initBoard, sizeof(initBoard));
	}
	else if (m_strategy == bluff)
	{
		EPiece initBoard[4][10] = {{2, 4, 3, 5, 2, 1, 4, 0, 5, 3},
								   {5, 4, 6, 6, 3, 3, 6, 2, 6, 5},
								   {7, 9, 8, 0, 10, 7, 0, 3, 8, 7},
								   {2, 2, 0, 11, 0, 0, 4, 2, 2, 2}};
		memcpy(boardInit, initBoard, sizeof(initBoard));
	}
	else if (m_strategy == risked)
	{
		//
	}

	/* Initialisation du tableau interne */

	for (i=0; i<10; i++) // Lignes
	{
		for (j=0; j<10; j++) // Colonnes
		{
			pos.line = i;
			pos.col = j;

			if (i < 4) // Si on est dans nos rangs, on sauvegarde ce qu'on a mis
			{
				updateSquare(pos, boardInit[i][j], m_color, false, true);				
			}
			else if (i > 3 && i < 6) // Sinon si on est entre les joueurs
			{
				if ((j > 1 && j < 4)||(j > 5 && j < 8)) // Si on se trouve sur un lac
				{
					updateSquare(pos, EPnone, EClake, false, false);
				}
				else // Sinon on se trouve sur une case vide
				{
					updateSquare(pos, EPnone, ECnone, false, false);
				}
			}
			else // Sinon, on est dans le camp ennemi
			{
				updateSquare(pos, EPnone, m_enemyColor, false, true);
			}
		}		
	}

	printf("Affichage du tableau interne :\n");

	printf("  |");
	for (i=0; i<10; i++)
	{
		printf(" %d  ", i);
		printf("|");
	}
	printf("\n");
	printf("-----------------------------------------------------\n");
	for (i=0; i<10; i++)
	{		
		printf("%d ", 9-i);		
		printf("|");

		for (j = 0; j < 10; ++j)
		{
			if (m_board[9-i][j].box.piece >= 10)
				printf(" %d", m_board[9-i][j].box.piece);		
			else
				printf(" %d ", m_board[9-i][j].box.piece);			
			printf(" |");				
		}
		printf("\n-----------------------------------------------------\n");
	}	
}

void EndGame()
{
	printf("EndGame\n");
}

void EndMatch()
{
	// Désallocation
	printf("EndMatch\n");
}

SMove NextMove(const SGameState * const gameState)
{
	printf("NextMove\n");
	updateData(gameState); // Première phase, mise à jour des données internes
	analyzeBoard(gameState); // Analyse du plateau => Mise à jour des dplcmts possibles
	decideMove(gameState); // Décision du mouvement à faire
	if (!m_myMove) // Si on a fait un déplacement normal, on le sauvegarde 
		saveMove(); // On sauvegarde le plateau interne avec le mouvement que l'on va faire
	return m_decidedMove;
}

void AttackResult(SPos armyPos,EPiece armyPiece,SPos enemyPos,EPiece enemyPiece)
{	
	int i, j;
	printf("Démarrage de AttackResult\n");	
	printf("Tableau avant fin de l'attaque\n");
	printf("  |");
	for (i=0; i<10; i++)
	{
		printf(" %d  ", i);
		printf("|");
	}
	printf("\n");
	printf("-----------------------------------------------------\n");
	for (i=0; i<10; i++)
	{		
		printf("%d ", 9-i);		
		printf("|");

		for (j = 0; j < 10; ++j)
		{
			if (m_board[9-i][j].box.piece >= 10)
				printf(" %d|%d", m_board[9-i][j].box.piece, m_board[9-i][j].box.content);		
			else
				printf(" %d|%d ", m_board[9-i][j].box.piece, m_board[9-i][j].box.content);			
			printf(" |");				
		}
		printf("\n-----------------------------------------------------\n");
	}
	printf("(%d,%d) à (%d,%d) : %d versus %d\n", armyPos.line, armyPos.col, enemyPos.line, enemyPos.col, armyPiece, enemyPiece);
	
	/* Si c'est nous qui avons engagé l'attaque */
	if (m_myMove)
	{
		analyseFight(armyPiece, enemyPiece, armyPos, enemyPos);
		m_myMove = false;
	}
	else
	{
		m_hisMove = true;
		analyseFight(enemyPiece, armyPiece, enemyPos, armyPos);
	}
	printf("Tableau après l'attaque\n");
	printf("  |");
	for (i=0; i<10; i++)
	{
		printf(" %d  ", i);
		printf("|");
	}
	printf("\n");
	printf("-----------------------------------------------------\n");
	for (i=0; i<10; i++)
	{		
		printf("%d ", 9-i);		
		printf("|");

		for (j = 0; j < 10; ++j)
		{
			if (m_board[9-i][j].box.piece >= 10)
				printf(" %d", m_board[9-i][j].box.piece);		
			else
				printf(" %d ", m_board[9-i][j].box.piece);			
			printf(" |");				
		}
		printf("\n-----------------------------------------------------\n");
	}
}

void Penalty()
{
	printf("Penalty\n");
}
