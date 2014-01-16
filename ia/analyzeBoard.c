#include "resources.h"
#include "analyzeBoard.h"

// Analyse du plateau => Mise à jour des déplacements possibles
void analyzeBoard(const SGameState * const gameState)
{
	unsigned int i, j, compteur = 0;
	for (i=0; i<10; i++)
	{
		for (j=0; j<10; j++)
		{
			/* Si la pièce est une pièce appartenant à l'IA et qu'elle est
			déplaçable, on regarde les cases aux alentours */
			if ((gameState->board[i][j].content == m_color) && (gameState->board[i][j].piece != EPbomb) && (gameState->board[i][j].piece != EPflag))
			{				
				// Analyse du mouvement vers le bas
				addAnalyzedMove(gameState, i, j, i-1, j, 1, 0, &compteur);

				// Analyse du mouvement vers le haut
				addAnalyzedMove(gameState, i, j, i+1, j, 1, 9, &compteur);

				// Analyse du mouvement vers la gauche
				addAnalyzedMove(gameState, i, j, i, j-1, 0, 0, &compteur);

				// Analyse du mouvement vers la droite
				addAnalyzedMove(gameState, i, j, i, j+1, 0, 9, &compteur);
			}
		}
	}

	m_nbMove = compteur;
}

// Sous-fonction de l'analyse du plateau
void addAnalyzedMove(const SGameState * const gameState, unsigned int i, unsigned int j, int new_i, int new_j, int is_i, int lim, unsigned int* compteur)
{	
	/* Déclaration des variables internes */
	int temp, val, newVal, dirLine, dirCol;
	SPos start, end;

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
	

	/* Condition principale : si la case sur laquelle on veut se déplacer n'est pas hors des limites du plateau, si elle ne contient ni un lac ni un allié, et si ce n'est pas un 4e aller-retour, alors on peut s'y déplacer */
	if ((val != lim) 
		&& (gameState->board[new_i][new_j].content != EClake) 
		&& (gameState->board[new_i][new_j].content != m_color)
		&& (!((m_decidedMove.start.line == new_i)
			&&(m_decidedMove.start.col == new_j)
			&&(m_decidedMove.end.line == i)
			&&(m_decidedMove.end.col == j)
			&&(m_nbRoundTrips == 3)
			)))
	{
		/* Affectation des positions */
		start.line = i; start.col = j;
		end.line = new_i; end.col = new_j;

		/* Ajout du mouvement dans le tableau des mouvements */
		m_movements[*compteur].start = start;
		m_movements[*compteur].end = end;
		(*compteur)++;

		/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
		if (gameState->board[i][j].piece == EPscout)
		{
			/* On utilise une variable temp pour parcourir toute la ligne */
			temp = newVal;	

			/* Tant qu'on n'a pas atteint la limite du plateau et que la case cible ne contient ni un lac, 
			ni un allié, et que la case actuelle ne contient pas un ennemi, le mouvement est possible */		
			while ((temp != lim) && (gameState->board[new_i+dirLine][new_j+dirCol].content != EClake) && (gameState->board[new_i+dirLine][new_j+dirCol].content != m_color) && (gameState->board[new_i][new_j].content != m_enemyColor))
			{
				/* Rajout du mouvement dans le tableau des mouvements */
				start.line = i; start.col = j;
				end.line = new_i+dirLine; end.col = new_j+dirCol;
				m_movements[*compteur].start = start;
				m_movements[*compteur].end = end;
				(*compteur)++;

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
