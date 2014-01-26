#include "game.h"

// Analyze des déplacements possibles
int analyzeBoard(EPlayer player)
{
	unsigned int i, j, compteur = 0;
	EColor enemyColor = (player.Color == ECblue ? ECred : ECblue); 
	for (i=0; i<10; i++)
	{
		for (j=0; j<10; j++)
		{
		/* Si la pièce est une pièce appartenant à l'IA et qu'elle est
			déplaçable, on regarde les cases aux alentours */
			if ((player.Pboard[i][j].content == player.Color) && (player.Pboard[i][j].piece != EPbomb) && (player.Pboard[i][j].piece != EPflag))
			{
				// Analyse du mouvement vers le bas
				addAnalyzedMove(i, j, i-1, j, 1, 0, &compteur, enemyColor, player);

				// Analyse du mouvement vers le haut
				addAnalyzedMove(i, j, i+1, j, 1, 9, &compteur, enemyColor, player);

				// Analyse du mouvement vers la gauche
				addAnalyzedMove(i, j, i, j-1, 0, 0, &compteur, enemyColor, player);

				// Analyse du mouvement vers la droite
				addAnalyzedMove(i, j, i, j+1, 0, 9, &compteur, enemyColor, player);
			}
			if (compteur != 0)
				break;
		}
	}

	return compteur;
}


// Sous-fonction de l'analyse du plateau
void addAnalyzedMove(unsigned int i, unsigned int j, int new_i, int new_j, int is_i, int lim, unsigned int* compteur, EColor enemyColor, EPlayer player)
{	
	/* Si on a bien trouvé aucun mouvement précédemment, on regarde 
	si le mouvement à analyser est possible */
	if ((*compteur) == 0)
	{
		// Déclaration des variables internes 
		int val;

		// Initialisation des variables contenant les positions
		// initiales et finales du mouvement à analyser 
		if (is_i == 1)
			val = i;	
		else
			val = j;

		// Condition principale : si la case sur laquelle on veut se déplacer n'est pas hors des limites du plateau, si elle ne contient ni un lac ni un allié, et si ce n'est pas un 4e aller-retour, alors on peut s'y déplacer 
		if ((val != lim) 
			&& (player.Pboard[new_i][new_j].content != EClake) 
			&& (player.Pboard[new_i][new_j].content != player.Color)
			&& (!((player.previousMove.start.line == new_i)
				&&(player.previousMove.start.col == new_j)
				&&(player.previousMove.end.line == i)
				&&(player.previousMove.end.col == j)
				&&(player.nbMove == 3)
				)))
		{
			//Ajout du mouvement dans le tableau des mouvements 
			(*compteur)++;	
		}
	}	
}
