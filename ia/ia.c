/*#include "../stratego.h"*/
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
SMove m_decidedMove; // Mouvement décidé après une réflexion par l'IA
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
	unsigned int i, j, compteur = 0;
	for (i=0; i<10; i++)
	{
		for (j=0; j<10; j++)
		{
			/* Si la pièce est une pièce appartenant à l'IA et qu'elle est
			déplaçable, on regarde les cases aux alentours */
			if ((m_board[i][j].box.content == m_color) && (m_board[i][j].box.piece != EPbomb) && (m_board[i][j].box.piece != EPflag))
			{				
				// Analyse du mouvement vers le bas
				addAnalyzedMove(i, j, i-1, j, 1, 0, &compteur);

				// Analyse du mouvement vers le haut
				addAnalyzedMove(i, j, i+1, j, 1, 9, &compteur);

				// Analyse du mouvement vers la gauche
				addAnalyzedMove(i, j, i, j-1, 0, 0, &compteur);

				// Analyse du mouvement vers la droite
				addAnalyzedMove(i, j, i, j+1, 0, 9, &compteur);
			}
		}
	}

	m_nbMove = compteur;
}

// Sous-fonction de l'analyse du plateau
void addAnalyzedMove(int i, int j, int new_i, int new_j, int is_i, int lim, unsigned int* compteur)
{	
	/* Déclaration des variables internes */
	int temp, val, newVal, dirLine, dirCol;
	SPos start, end;
	EColor enemyColor;

	/* Initialisation des variables contenant les positions
	initiales et finales du mouvement à analyser */
	if (is_i == 1)
	{
		val = i;
		newVal = new_i;
	}		
	else
	{
		val = j;
		newVal = new_j;
	}

	/* Initialisation des variables permettant de 
	sauvegarder la direction du mouvement à analyser */
	dirLine = new_i - i;
	dirCol = new_j - j;
	
	/* Initialisation de la couleur ennemie */
	if (m_color == ECred)
		enemyColor = ECblue;
	else
		enemyColor = ECred;

	/* Condition principale : si la case sur laquelle on veut se déplacer n'est pas hors des limites du plateau,
	et si elle ne contient ni un lac ni un allié, alors on peut s'y déplacer */
	if ((val != lim) && (m_board[new_i][new_j].box.content != EClake) && (m_board[new_i][new_j].box.content != m_color)) 
	{
		/* Affectation des positions */
		start.line = i; start.col = j;
		end.line = new_i; end.col = new_j;

		/* Ajout du mouvement dans le tableau des mouvements */
		m_movements[*compteur].start = start;
		m_movements[*compteur].end = end;
		*compteur++;

		/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
		if (m_board[i][j].box.piece == EPscout)
		{
			/* On utilise une variable temp pour parcourir toute la ligne */
			temp = newVal;	

			/* Tant qu'on n'a pas atteint la limite du plateau et que la case cible ne contient ni un lac, 
			ni un allié, et que la case actuelle ne contient pas un ennemi, le mouvement est possible */		
			while ((temp != lim) && (m_board[new_i+dirLine][new_j+dirCol].box.content != EClake) && (m_board[new_i+dirLine][new_j+dirCol].box.content != m_color) && (m_board[new_i][new_j].box.content != enemyColor))
			{
				/* Rajout du mouvement dans le tableau des mouvements */
				start.line = i; start.col = j;
				end.line = new_i+dirLine; end.col = new_j+dirCol;
				m_movements[*compteur].start = start;
				m_movements[*compteur].end = end;
				*compteur++;

				/* Parcours de la ligne selon la direction (vers les i ou j négatifs, ou positifs) */
				if ((dirLine < 0)||(dirCol < 0))
					temp--;
				else
					temp++;

				/* Utilisation de temp selon la direction du déplacement
				(en ligne ou en colonne) */
				if (is_i == 1)
					new_i = temp;
				else
					new_j = temp;				
			}
		}						
	}
}