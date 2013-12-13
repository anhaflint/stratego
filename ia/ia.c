#include "../stratego.h"
#include "ia.h"
#include <stdbool.h>

typedef Enum{
	offensive=0;
	defensive;
	malicious;
}Strategy;

bool m_fight; // Booléen indiquant s'il y a eu un combat lors de la manche précédente
EColor m_color; // Couleur des pièces de l'IA
SPos m_armyPos, m_enemyPos; // Variables sauvegardant la position des pièces avant un combat
SPiece m_armyPiece, m_enemyPiece; // Variables sauvegardant le type des pièces avant un combat
SMove m_movements[172]; // Tableau contenant les mouvements possibles à chaque tour
int m_nbMove; // Nombre de mouvements enregistrés dans le tableau des mouvements
InfoPiece m_board[10][10]; // Tableau de la structure InfoPiece, qui stocke des pièces et des informations dessus
Strategy m_strategy;

void InitLibrary(char name[50])
{
	printf("InitLibrary\n");
	strcpy(name,"Fabien Picarougne");
}

void StartMatch(const EColor color)
{
	printf("StartMatch\n");
}

void StartGame(EPiece boardInit[4][10]){
	/* Initialisation du tableau de l'IA avec positionement de pions*/
	printf("StartGame\n");
	switch(m_strategy){

		case defensive:
			/* placement du drapeau */
			boardInit[0][0] = EPflag;
			/* placement des bombes */
			boardInit[1][0] = boardInit[0][1] = boardInit[0][4] = boardInit[1][5] = boardInit[0][6] =  EPbomb;
			/* placement des sergants */
			boardInit[2][0] = boardInit[2][6] = boardInit[0][5] = boardInit[0][7] = EPsergeant;
			/* placements des scouts */
			boardInit[1][2] = boardInit[1][3] = boardInit[1][6] = boardInit[1][7] = boardInit[0][3] = EPscout;
			/*placement des espions */
			boardInit[3][0] = boardInit[3][1] = boardInit[3][4] = boardInit[3][5] = boardInit[3][8] = EPspy;
			boardInit[2][5] = boardInit[1][9] = boardInit[0][9] = EPspy;
			/* placement des lieutenants */
			boardInit[3][9] = boardInit[1][4] = boardInit[1][8] = boardInit[0][8] = EPlieutenant;
			/* placement des capitaines */
			boardInit[2][1] = boardInit[2][2] = boardInit[2][4] = boardInit[2][7] = EPcaptain;
			/* placement des majors */
			boardInit[3][2] = boardInit[3][7] = boardInit[1][1] = EPmajor;
			/* placement des colonels */
			boardInit[2][9] = boardInit[0][2] = EPcolonel;
			/* placements du général */
			boardInit[3][3] = EPgeneral;
			/* placement du maréchal */
			boardInit[3][6] = EPmarshal;
		break;
	}
}

void EndGame()
{
	printf("EndGame\n");
}

void EndMatch()
{
	printf("EndMatch\n");
}

void NextMove(const SGameState * const gameState, SMove *move)
{
	printf("NextMove\n");
}

void AttackResult(SPos armyPos,EPiece armyPiece,SPos enemyPos,EPiece enemyPiece)
{
	m_armyPos = armyPos;
	printf("AttackResult\n");
}

void void Penalty()
{
	printf("Penalty\n");
}

//--- Fonctions personnelles ---//

// Première phase, mise à jour des données internes
void updateData(gameState)
{
	
}

// Analyse du plateau => Mise à jour des déplacements possibles
void analyzeBoard()
{
	unsigned int i, j, temp, compteur = 0;
	SPos start, end;
	EColor enemyColor;

	if (m_color == ECred)
		enemyColor = ECblue;
	else
		enemyColor = ECred;

	for (i=0; i<10; i++)
	{
		for (j=0; j<10; j++)
		{
			/* Si la pièce est une pièce appartenant à l'IA et qu'elle est
			déplaçable, on regarde les cases aux alentours */
			if ((m_board[i][j].box.color == m_color) && (m_board[i][j].box.piece != EPbomb) && (m_board[i][j].box.piece != EPflag))
			{				
				// Si on n'est pas sur la ligne du bas et qu'on peut bouger sur la case du dessous, rajout du mouvement
				if ((i != 0) && (m_board[i-1][j].box.color != EClake) && (m_board[i-1][j].box.color != m_color)) 
				{
					start.line = i; start.col = j;
					end.line = i-1; end.col = j;
					m_movements[compteur].start = start;
					m_movements[compteur].end = end;
					compteur++;

					/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
					if (m_board[i][j].box.piece == EPscout)
					{
						temp = i;
						/* On rajoute une condition supplémentaire : on s'arrête dès qu'on tombe sur une case contenant un ennemi */
						while ((temp != 0) && (m_board[temp-1][j].box.color != EClake) && (m_board[temp-1][j].box.color != m_color) && (m_board[temp][j].box.color != enemyColor))
						{
							start.line = temp; start.col = j;
							end.line = temp-1; end.col = j;
							m_movements[compteur].start = start;
							m_movements[compteur].end = end;
							compteur++;
							temp++;
						}
					}							
				}
			
				// Si on n'est pas sur la ligne du dessus et qu'on peut bouger sur la case du dessus, rajout du mouvement
				if ((i != 9) && (m_board[i+1][j].box.color != EClake) && (m_board[i+1][j].box.color != m_color)) 
				{
					start.line = i; start.col = j;
					end.line = i+1; end.col = j;
					m_movements[compteur].start = start;
					m_movements[compteur].end = end;
					compteur++;

					/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
					if (m_board[i][j].box.piece == EPscout)
					{
						temp = i;
						/* On rajoute une condition supplémentaire : on s'arrête dès qu'on tombe sur une case contenant un ennemi */
						while ((temp != 0) && (m_board[temp+1][j].box.color != EClake) && (m_board[temp+1][j].box.color != m_color) && (m_board[temp][j].box.color != enemyColor))
						{
							start.line = temp; start.col = j;
							end.line = temp+1; end.col = j;
							m_movements[compteur].start = start;
							m_movements[compteur].end = end;
							compteur++;
							temp++;
						}
					}	
				}
				
				// Si on n'est pas sur la ligne de gauche et qu'on peut bouger sur la case de gauche, rajout du mouvement
				if ((j != 0) && (m_board[i][j-1].box.color != EClake) && (m_board[i][j-1].box.color != m_color))
				{
					start.line = i; start.col = j;
					end.line = i; end.col = j-1;
					m_movements[compteur].start = start;
					m_movements[compteur].end = end;
					compteur++;

					/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
					if (m_board[i][j].box.piece == EPscout)
					{
						temp = j;
						/* On rajoute une condition supplémentaire : on s'arrête dès qu'on tombe sur une case contenant un ennemi */
						while ((temp != 0) && (m_board[i][temp-1].box.color != EClake) && (m_board[i][temp-1].box.color != m_color) && (m_board[i][temp].box.color != enemyColor))
						{
							start.line = temp; start.col = j;
							end.line = i; end.col = temp-1;
							m_movements[compteur].start = start;
							m_movements[compteur].end = end;
							compteur++;
							temp++;
						}
					}
				} 

				// Si on n'est pas sur la ligne de droite et qu'on peut bouger sur la case de droite, rajout du mouvement
				if ((j != 9) && (m_board[i][j+1].box.color != EClake) && (m_board[i][j+1].box.color != m_color))
				{
					start.line = i; start.col = j;
					end.line = i; end.col = j+1;
					m_movements[compteur].start = start;
					m_movements[compteur].end = end;
					compteur++;

					/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
					if (m_board[i][j].box.piece == EPscout)
					{
						temp = j;
						/* On rajoute une condition supplémentaire : on s'arrête dès qu'on tombe sur une case contenant un ennemi */
						while ((temp != 0) && (m_board[i][temp+1].box.color != EClake) && (m_board[i][temp+1].box.color != m_color) && (m_board[i][temp].box.color != enemyColor))
						{
							start.line = temp; start.col = j;
							end.line = i; end.col = temp+1;
							m_movements[compteur].start = start;
							m_movements[compteur].end = end;
							compteur++;
							temp++;
						}
					}
				}
			}
		}
	}

	m_nbMove = compteur;
}