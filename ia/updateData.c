#include <stdio.h>
#include "resources.h"
#include "updateData.h"

/* Mise à jour d'une case de notre structure InfoPiece m_board */
void updateSquare(SPos position, EPiece piece, EColor color, bool isVisible, bool isBomb)
{
	m_board[position.line][position.col].box.piece = piece;
	m_board[position.line][position.col].box.content = color;
	m_board[position.line][position.col].isVisible = isVisible;
	m_board[position.line][position.col].isBomb = isBomb;
}

/* Déductions et spéculations sur les pièces ennemies */
void updateBoard(const SGameState * const gameState, SMove enemyMovement)
{
	int nbEnemies = 40; // Nombre d'ennemis restants sur le plateau
	int nbHiddenEnemies = 0; // Nombre d'ennemis non visibles restant sur le plateau
	int nbMovableEnemies = 33; // Nombre d'ennemis qui peuvent bouger restant sur le plateau
	int nbMovablesHiddenEnemies; // Nombre d'ennemis qui peuvent bouger non visibles restant sur le plateau
	int nbNotMovablesHiddenEnemies; // Nombre d'ennemis qui ne peuvent pas bouger et non visibles restants sur le plateau
	int nbPossibilities; // Nombre de possibilités pour les cas traités
	SPos posPiece; // Position de la pièce identifiée et à remplacer
	EPiece piecePossible; // Type de la pièce identifiée
	int i, j; // Compteurs

	/* On parcourt les tableaux de pièces éliminées
	afin de déterminer le nombre d'ennemis restants
	sur le plateau */
	if (m_color == ECblue)
	{
		for(i=0; i<12; i++)
		{
			nbEnemies -= gameState->redOut[i];
			if ((i != 0)&&(i != 11))
				nbMovableEnemies -= gameState->redOut[i];
		}
	}
	else
	{
		for(i=0; i<12; i++)
		{
			nbEnemies -= gameState->blueOut[i];
			if ((i != 0)&&(i != 11))
				nbMovableEnemies -= gameState->blueOut[i];
		}
	}

	/* On initialise les compteurs d'ennemis qui peuvent
	bouger et non visibles, c'est à dire dont la valeur 
	est EPnone pour nous */
	nbMovablesHiddenEnemies = nbMovableEnemies;

	/* Parcours du plateau pour déterminer le nombre 
	d'ennemis non visibles (EPnone) */
	for (i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			/* Si il y a un ennemi sur la case */
			if (m_board[i][j].box.content == m_enemyColor)
			{
				/* Si on ne connait pas la pièce */
				if(m_board[i][j].box.piece == EPnone)
					nbHiddenEnemies++;

				/* Sinon, si on la voit et qu'elle peut bouger, on décrémente nbMovablesHiddenEnemies */
				else if ((m_board[i][j].box.piece != EPbomb) && (m_board[i][j].box.piece != EPflag))
					nbMovablesHiddenEnemies--;
			}
		}
	}

	nbNotMovablesHiddenEnemies = nbHiddenEnemies - nbMovablesHiddenEnemies;

	/* Traitement de chaque cas de déduction */

	/* Cas 1 : Si il y a n pièces ennemies cachées, et qu'il y en a n-1 qui peuvent bouger,
	alors la dernière ne peut pas bouger et on peut déterminer laquelle c'est */
	if (nbNotMovablesHiddenEnemies == 1)
	{
		/* On regarde les positions possibles pour cette pièce */
		for (i=0; i<11; i++)
		{
			for (j=0; j<11; j++)
			{
				/* Si la pièce est un ennemi qu'on ne connaît pas, et qui est une bombe potentielle */
				if ((m_board[i][j].box.content ==m_enemyColor)&&(m_board[i][j].box.piece == EPnone)&&(m_board[i][j].isBomb))
				{
					nbPossibilities++;
					posPiece.line = i;
					posPiece.col = j;
					piecePossible = m_board[i][j].box.piece;
				}			
				/* Si on a trouvé plus d'une possibilité, on arrête */
				else if (nbPossibilities > 1)
					break;
			}
		}

		/* Si le nombre de positions possibles pour la pièce
		recherchée est 1, alors on a trouvé la pos de la pièce
		et le type, on met à jour le board interne */
		if (nbPossibilities == 1)
			updateSquare(posPiece, piecePossible, m_enemyColor, true, (piecePossible == EPbomb ? true : false));

		/* Réinitialisation du nombre de possibilités */
		nbPossibilities = 0;
	}

	/* Cas 2 : Si il y a n pièces ennemies cachées, et qu'il y en a n-1 qui ne peuvent pas bouger,
	alors la dernière peut bouger et on peut déterminer laquelle c'est */
	if (nbMovablesHiddenEnemies == 1)
	{
		/* On regarde les positions possibles pour cette pièce */
		for (i=0; i<11; i++)
		{
			for (j=0; j<11; j++)
			{
				/* Si la pièce est un ennemi qu'on ne connaît pas, et qui n'est pas une bombe potentielle */
				if ((m_board[i][j].box.content ==m_enemyColor)&&(m_board[i][j].box.piece == EPnone)&&(!(m_board[i][j].isBomb)))
				{
					nbPossibilities++;
					posPiece.line = i;
					posPiece.col = j;
					piecePossible = m_board[i][j].box.piece;
				}			
				/* Si on a trouvé plus d'une possibilité, on arrête */
				else if (nbPossibilities > 1) 
					break;
			}
		}

		/* Si le nombre de positions possibles pour la pièce
		recherchée est 1, alors on a trouvé la pos de la pièce
		et le type, on met à jour le board interne */
		if (nbPossibilities == 1)
			updateSquare(posPiece, piecePossible, m_enemyColor, true, false);

		/* Réinitialisation du nombre de possibilités */
		nbPossibilities = 0;
	}

	/* Cas 3 : Si l'ennemi a bougé de plus d'une case et qu'il était inconnu, alors
	on peut aisément conclure que c'est un scout */
	if (((enemyMovement.start.line - enemyMovement.end.line)/2 != 0)
		||((enemyMovement.start.col - enemyMovement.end.col)/2 != 0))
	{
		updateSquare(enemyMovement.end, EPscout, m_enemyColor, true, false);
	}
	
	/* D'autres cas à venir sûrement... */
}

// Première phase, mise à jour des données internes
void updateData(const SGameState * const gameState)
{
	/************************
	* Il y a 4 cas possibles de mouvements 
	* qui se sont passés depuis le dernier tour :
	* - On a attaqué une pièce, et l'ennemi a également attaqué une pièce
	* - On a attaqué une pièce, et l'ennemi a effectué un déplacement simple
	* - On a effectué un déplacement simple, et l'ennemi a également effectué un déplacement simple
	* - On a effectué un déplacement simple, et l'ennemi a attaqué une pièce
	* Tous les cas d'attaque (dans un sens ou dans un autre) sont gérés par la fonction AttackResult().
	* Tous les cas où l'on fait un déplacement simple sont gérés par la fonction saveMove().
	* Il ne reste donc qu'à gérer les deux cas dans lesquels l'ennemi effectue 
	* un déplacement simple : ce cas est géré dans cette fonction updateData()
	*************************/

	/* Variables internes à la fonction */
	int i, j; // Variables pour les boucles	
	int diff; // Différence entre les gameState à chaque passage de boucle
	SMove enemyMovement; // Tableaux contenant les positions qui ont changé depuis le dernier mouvement
	m_nbMove = 0; // A déplacer dans la fonction précédant l'envoi de mouvement
	bool enemyHasMoved = false; // Permet de savoir si l'ennemi a fait un déplacement simple

	/* Initialisation de la variable de mouvement, pour le cas où l'on jouerait
	en premier et enemyMovement serait analysé */
	enemyMovement.start.line = 0;
	enemyMovement.start.col = 0;
	enemyMovement.end.line = 0;
	enemyMovement.end.col = 0;

	/* On analyse les changements qu'il y a eu depuis notre dernier tour, 
	on stocke ça dans le tableau de positions adéquat */
	for (i=0; i < 10; i++)
	{
		for (j=0; j < 10; j++)
		{
			diff = m_board[i][j].box.content - gameState->board[i][j].content;
			
			/* Si une pièce n'est plus dans la case en (i,j), on stocke */
			if (diff > 0)
			{
				enemyHasMoved = true;
				enemyMovement.start.line = i;
				enemyMovement.start.col = j;
			}
			/* Sinon si une pièce est arrivée en (i,j), on stocke */
			else if (diff < 0)
			{
				enemyMovement.end.line = i; 
				enemyMovement.end.col = j;				
			}
		}
	}

	if (enemyHasMoved)
	{		
		/* On met à jour la case d'arrivée de l'ennemi */		
		updateSquare(enemyMovement.end,
			m_board[enemyMovement.start.line][enemyMovement.start.col].box.piece, 
			m_board[enemyMovement.start.line][enemyMovement.start.col].box.content, 
			m_board[enemyMovement.start.line][enemyMovement.start.col].isVisible, 
			false);
		
		/* On vide la case d'où provient l'ennemi */
		updateSquare(enemyMovement.start, EPnone, ECnone, false, false);
	}

	/* Déductions et spéculations sur les pièces ennemies */
	updateBoard(gameState, enemyMovement);

	/* Réinitialisation des valeurs */
	m_myMove = false;
}
