/*#include "../stratego.h"*/
#include "ia.h"
#include <stdbool.h>

typedef Enum{
	defaut=0,
	offensive,
	defensive,
	malicious
}Strategy;

EColor m_color; // Couleur des pièces de l'IA
SPos m_armyPos, m_enemyPos; // Variables sauvegardant la position des pièces avant un combat
SPiece m_armyPiece, m_enemyPiece; // Variables sauvegardant le type des pièces avant un combat
SMove m_movements[172]; // Tableau contenant les mouvements possibles à chaque tour
SMove m_decidedMove; // Mouvement décidé après une réflexion par l'IA
int m_nbMove; // Nombre de mouvements enregistrés dans le tableau des mouvements
InfoPiece m_board[10][10]; // Tableau de la structure InfoPiece, qui stocke des pièces et des informations dessus
Strategy m_strategy; // Stratégie choisie
int m_caution; // Variable pour prise de risque : vaut 0 si aucun risque à prendre, 10 si faire des mouvements très risqués
bool m_myMove; // Variable pour connaître le mouvement que l'on a fait au tour précédent : false = mouvement normal et true = attaque
bool m_hisMove; // Variable pour connaître le mouvement que l'ennemi a fait au tour précédent : false = mouvement normal et true = attaque

void InitLibrary(char name[50])
{
	printf("InitLibrary\n");
	strcpy(name,"Fabien Picarougne");
}

void StartMatch()
{	
	printf("StartMatch\n");
}

void StartGame(const EColor color, EPiece boardInit[4][10]){
	/* Initialisation du tableau de l'IA avec positionement de pions*/
	printf("StartGame\n");
	m_color = color;
	m_fight = false;
	m_strategy = defaut;
	m_caution = 5;

	switch(m_strategy){

		case defensive:
			/* placement du drapeau */
			boardInit[0][0] = EPflag;
			/* placement des bombes */
			boardInit[1][0] = boardInit[0][1] = boardInit[0][4] = boardInit[1][5] = boardInit[0][6] = boardInit[2][8] = EPbomb;
			/* placement de l'espion */
			boardInit[2][3] = EPspy;
			/*placement des eclaireurs */
			boardInit[3][0] = boardInit[3][1] = boardInit[3][4] = boardInit[3][5] = boardInit[3][8] = boardInit[2][5] = boardInit[1][9] = boardInit[0][9] = EPscout;
			/* placements des démineurs */
			boardInit[1][2] = boardInit[1][3] = boardInit[1][6] = boardInit[1][7] = boardInit[0][3] = EPminer;
			/* placement des sergents */
			boardInit[2][0] = boardInit[2][6] = boardInit[0][5] = boardInit[0][7] = EPsergeant;			
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
	// Désallocation
	printf("EndMatch\n");
}

void NextMove(const SGameState * const gameState, SMove *move)
{
	printf("NextMove\n");
	updateData(gameState); // Première phase, mise à jour des données internes
	analyzeBoard(); // Analyse du plateau => Mise à jour des dplcmts possibles
	decideMove(gameState); // Décision du mouvement à faire
	checkMove(); // Vérification du mouvement avec notre propre arbitre interne à l'IA
	*move = m_decidedMove; // On retourne le mouvement à l'arbitre
}

void AttackResult(SPos armyPos,EPiece armyPiece,SPos enemyPos,EPiece enemyPiece)
{
	/* Déclaration des variables internes à la fonction */
	SPiece winner;

	/* Enregistrement des données fournies par l'arbitre */
	printf("AttackResult\n");
	m_armyPos = armyPos;
	m_armyPiece = armyPiece;
	m_enemyPos = enemyPos;
	m_enemyPiece = enemyPiece;
	
	/* On ne traite les données que dans le cas où on a attaqué */
	if (m_myMove)
	{
		if (armyPiece != enemyPiece) // Si les deux pièces sont différentes, on analyse le fight
		{
			/* Dans le cas où on a déclenché une attaque, on traite les données maintenant */
			winner = winner(armyPiece, enemyPiece);

			/* Dans tous les cas, la case d'où vient notre pièce devient vide */
			m_board[armyPos.line][armyPos.col].box.piece = EPnone;
			m_board[armyPos.line][armyPos.col].box.content = ECnone;

			if (winner == armyPiece) // Si on a attaqué et gagné, on remplace la pièce visée
			{
				/* On place notre pièce sur la case où était l'ennemi */
				m_board[enemyPos.line][enemyPos.col].box.piece = armyPiece;
				m_board[enemyPos.line][enemyPos.col].box.content = m_color;
			}
			else // Si on a perdu, on enregistre contre quelle pièce on a perdu
			{	
				m_board[enemyPos.line][enemyPos.col].box.piece = enemyPiece;
			}		
		}
		else // Si les deux pièces sont identiques, les deux pièces sont éliminées
		{
			/* Plus rien dans la case de notre pièce */
			m_board[armyPos.line][armyPos.col].box.piece = EPnone;
			m_board[armyPos.line][armyPos.col].box.content = ECnone;

			/* Plus rien dans la case où était l'ennemi */
			m_board[enemyPos.line][enemyPos.col].box.piece = armyPiece;
			m_board[enemyPos.line][enemyPos.col].box.content = m_color;
		}		
	}
	else
	{
		m_hisMove = true;
	}
}	

void void Penalty()
{
	printf("Penalty\n");
}

//--- Fonctions personnelles ---//

// Fonction interne à AttackResult
SPiece winner(SPiece A, SPiece B)
{
	/* Si la pièce visée est le drapeau,
	la pièce attaquante gagne d'office */
	if (B == EPflag)
		return A;
	/* Si l'attaquant est un espion */
	else if (A == EPspy)
	{
		/* Il gagne seulement si la pièce 
		cible est le maréchal */
		if (B == EPmarshal)
			return A;
		else
			return B;
	}
	/* Sinon si l'attaquant est un démineur */
	else if (A == EPminer)
	{
		/* Il gagne si la pièce attaquée est une 
		bombe, un espion ou un éclaireur */
		if (B < EPminer)
			return A;
		else
			return B;
	}
	/* Sinon, dans tous les autres cas */
	else
	{
		/* Si la pièce attaquée est une bombe ou si sa 
		puissance est supérieure à l'attaquant, elle gagne */
		if ((B == EPbomb) || (B > A))
			return B;
		else
			return A;
	}
}

// Première phase, mise à jour des données internes
void updateData(gameState)
{
	m_nbMove = 0;

	/* On analyse les changements qu'il y a eu depuis notre dernier tour */

	/* On regarde les actions qui se sont déroulées depuis notre dernier tour */
	
	if (m_myMove) // Si on a attaqué, on a besoin de traiter le mouvement de l'ennemi seulement
	{
		if (m_hisMove) // Si l'ennemi a attaqué aussi,
		{

		}
	}
	// Réinitialisation des valeurs

	m_myMove = false;
	m_hisMove = false;
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