#include <stdbool.h>
#include <stdio.h> // A enlever à la fin
#include <string.h> // A peut-être enlever à la fin
#include "../structure.h"
#include "ia.h"

//------------------------- Données internes de l'IA ------------------------//

Strategy m_strategy; // Stratégie choisie
EColor m_color, m_enemyColor; // Couleur des pièces de l'IA
InfoPiece m_board[10][10]; // Tableau de la structure InfoPiece, qui stocke des pièces et des informations dessus
SMove m_movements[172]; // Tableau contenant les mouvements possibles à chaque tour
SMove m_decidedMove; // Mouvement décidé après une réflexion par l'IA
int m_nbMove; // Nombre de mouvements enregistrés dans le tableau des mouvements
int m_caution; // Variable pour prise de risque : vaut 0 si aucun risque à prendre, 10 si faire des mouvements très risqués
SPos m_armyPos, m_enemyPos; // Variables sauvegardant la position des pièces avant un combat
EPiece m_armyPiece, m_enemyPiece; // Variables sauvegardant le type des pièces avant un combat
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
	analyzeBoard(); // Analyse du plateau => Mise à jour des dplcmts possibles
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
				printf(" %d", m_board[9-i][j].box.piece);		
			else
				printf(" %d ", m_board[9-i][j].box.piece);			
			printf(" |");				
		}
		printf("\n-----------------------------------------------------\n");
	}
	printf("(%d,%d) à (%d,%d) : %d versus %d\n", armyPos.line, armyPos.col, enemyPos.line, enemyPos.col, armyPiece, enemyPiece);
	
	/* Si c'est nous qui avons engagé l'attaque */
	if (m_myMove)
	{
		analyseFight(armyPiece, enemyPiece, armyPos, enemyPos);
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

//------------------------ Fonctions internes à l'IA -------------------------//

//----------- Fonctions utilisées à chaque tour de jeu -----------//

//----- updateData() -----//

/* Mise à jour d'une case de notre structure InfoPiece m_board */
void updateSquare(SPos position, EPiece piece, EColor color, bool isVisible, bool isBomb)
{
	m_board[position.line][position.col].box.piece = piece;
	m_board[position.line][position.col].box.content = color;
	m_board[position.line][position.col].isVisible = isVisible;
	m_board[position.line][position.col].isBomb = isBomb;
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
	SMove enemyMovement; // Tableaux contenant les positions qui ont changé depuis le dernier mouvement
	m_nbMove = 0; // A déplacer dans la fonction précédant l'envoi de mouvement
	bool enemyHasMoved = false; // Permet de savoir si l'ennemi a fait un déplacement simple

	/* On analyse les changements qu'il y a eu depuis notre dernier tour, 
	on stocke ça dans le tableau de positions adéquat */
	for (i=0; i < 10; i++)
	{
		for (j=0; j < 10; j++)
		{
			/* Si une pièce n'est plus dans la case en (i,j), on stocke */
			if ((m_board[i][j].box.piece - gameState->board[i][j].piece) < 0)
			{
				enemyHasMoved = true;
				enemyMovement.start.line = i;
				enemyMovement.start.col = j;
			}
			/* Sinon si une pièce est arrivée en (i,j), on stocke */
			else if ((m_board[i][j].box.piece - gameState->board[i][j].piece) > 0)
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

	/* Réinitialisation des valeurs */
	m_myMove = false;
	m_hisMove = false;
}

//----- analyzeBoard() -----//

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
void addAnalyzedMove(unsigned int i, unsigned int j, int new_i, int new_j, int is_i, int lim, unsigned int* compteur)
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
		(*compteur)++;

		/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
		if (m_board[i][j].box.piece == EPscout)
		{
			/* On utilise une variable temp pour parcourir toute la ligne */
			temp = newVal;	

			/* Tant qu'on n'a pas atteint la limite du plateau et que la case cible ne contient ni un lac, 
			ni un allié, et que la case actuelle ne contient pas un ennemi, le mouvement est possible */		
			while ((temp != lim) && (m_board[new_i+dirLine][new_j+dirCol].box.content != EClake) && (m_board[new_i+dirLine][new_j+dirCol].box.content != m_color) && (m_board[new_i][new_j].box.content != m_enemyColor))
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

//----- decideMove() -----//

// Décision du mouvement à effectuer
void decideMove(const SGameState * const gameState)
{
	// Décision du mouvemennt
	// Penser à mettre m_myMove à true lorsqu'on attaque l'ennemi
	/*j'ai besoin du coup precedent(m_decidedMove) pour determiner le suivant*/

	GroupMoves priorityMoves; /* liste qui contient les mouvements non dupliqués et risqués évalués globalement( avec toutes les pieces énnemies voisines)*/
	GroupMoves normalMoves, riskedMoves;

	evaluateMoves(&normalMoves,&riskedMoves);
 	globalEvaluation(&priorityMoves,riskedMoves);

 	switch(m_strategy)
 	{
	       case defensive || malicious || searchme :
	               if(normalMoves.lenght_list > 0)/* si il ya la possibilité de jouer sans perdre de pion*/
	                   chooseMove(gameState, normalMoves);
	               else chooseMove(gameState, riskedMoves);
	       break;
 	}

     // A décommenter si test de lib 
     m_decidedMove = m_movements[0];
}

// procedure interne a evaluateMoves
// Donne l'information sur la piece ennemie voisine pour evaluer le risque encouru
int attributionRank(EPiece myPiece,EPiece enemyPiece,bool evaluationType)
{	
	int forceDifference;// ecart de force entre la piece enemie et la mienne;
	/*legende: 
			0  ==> pas de risque pour ce mouvement meme si on ne sait pas si il ya l'enemi present à cote 
			(forceDifference < 0) ==> mouvement avantageux
			(forceDifference > 0) ==> mouvement desavantageux
			5  ==> on perds tous deux nos piece si il ya attaque
			11 ==> on a un risque eleve mais avec un bon calcul de proba on reussit a avoir estimation de la piece
			12 ==> warning max à surtout eviter
	*/
	if(evaluationType) /* il s'agit d'une evaluation sur le voisinage */
	{	
		/* cas ou la piece ennemie est le drapeau  */
		if (enemyPiece == EPflag)
			return -12;
		/* cas ou la piece ennemie est la bombe et que la notre est un demineur */
		else if (enemyPiece == EPbomb && myPiece == EPminer)
			return -11;
		/* cas ou la piece ennemie est une bombe ou l'espion */
		else if( enemyPiece == EPbomb || (enemyPiece == EPspy && myPiece != EPmarshal))
			return 0;
		/* cas ou la piece ennemie est un espion et la mienne un marechal */
		else if (enemyPiece == EPspy && myPiece == EPmarshal)
			return 12;// le maximun warning 
		/* cas où on n'a pas d'information sur la piece */
		else if ( enemyPiece == EPnone)
			return 11;
		/* cas où la piece de l'ennemi et la mienne est egale */
		else if (enemyPiece == myPiece)
			return 10;
		else
		{
			forceDifference = enemyPiece - myPiece;
		return forceDifference;
		} 
	}
	else /* il s'agit d'une evalution d'attaque */
	{
		/* cas ou la piece ennemie est le drapeau ou l'espion */
		if (enemyPiece == EPflag || (enemyPiece == EPspy && myPiece != EPspy))
			return -12;
		/* cas ou la piece ennemie est la bombe et que la notre est un demineur */
		else if (enemyPiece == EPbomb && myPiece == EPminer)
			return -11;
		/* cas ou la piece ennemie est une bombe */
		else if( enemyPiece == EPbomb )
			return 10;
		/* cas ou la piece ennemie est un marechal et la mienne un espion*/
		else if (enemyPiece == EPmarshal && myPiece == EPspy)
			return 12;// le maximun warning 
		/* cas où on n'a pas d'information sur la piece */
		else if ( enemyPiece == EPnone)
			return 11;
		/* cas où la piece de l'ennemi et la mienne est egale */
		else if (enemyPiece == myPiece)
			return 10;
		else
		{
			forceDifference = enemyPiece - myPiece;
		return forceDifference;
		} 
	}
}

// procedure interne a decideMoves
// Classement des mouvements en fonction du risque encouru
void evaluateMoves(GroupMoves *normalMoves,GroupMoves *riskedMoves)
{
	/* Declaration des variables internes à la procédure*/
	int i = 0;
	bool neighbour=1;
	EPiece enemyPiece;
	EPiece myPiece;

	/* initialisation des longueurs de tableau des mouvements*/
	normalMoves->lenght_list= 0;
	riskedMoves->lenght_list= 0;

	myPiece = m_board[m_movements[i].start.line][m_movements[i].start.col].box.piece;

	/* classification des mouvements */
	while(i<m_nbMove)
	{
		/* si en effectuant le mouvement dans une case vide, je peux directement  être attaqué en haut  au prochain tour */
		if( m_movements[i].end.line < 9 &&  m_board[m_movements[i].end.line + 1][m_movements[i].end.col].box.content == m_enemyColor && m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone)
		{
			enemyPiece = m_board[m_movements[i].end.line + 1][m_movements[i].end.col].box.piece;

			riskedMoves->listMoves[r].move = m_movements[i];
			riskedMoves->listMoves[r].caution=attributionRank(myPiece,enemyPiece,neighbour);
			riskedMoves->lenght_list++;
		}
		/* si en effectuant le mouvement dans une case vide je peux directement  être attaqué en bas */
		else if (m_movements[i].end.line > 0  &&  m_board[ m_movements[i].end.line - 1 ][m_movements[i].end.col].box.content  == m_enemyColor && m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone)
		{
			enemyPiece = m_board[m_movements[i].end.line - 1][m_movements[i].end.col].box.piece;

			riskedMoves->listMoves[r].move = m_movements[i];
			riskedMoves->listMoves[r].caution=attributionRank(myPiece,enemyPiece,neighbour);
			riskedMoves->lenght_list++;
		}
		/* si en effectuant le mouvement dans une case videje peux directement  être attaqué à droite*/
		else if (m_movements[i].end.col < 9 &&  m_board[ m_movements[i].end.line][m_movements[i].end.col + 1 ].box.content == m_enemyColor && m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone)
		{
			enemyPiece = m_board[m_movements[i].end.line][m_movements[i].end.col + 1].box.piece;

			riskedMoves->listMoves[r].move = m_movements[i];
			riskedMoves->listMoves[r].caution=attributionRank(myPiece,enemyPiece,neighbour);
			riskedMoves->lenght_list++;
		}
		/* si en effectuant le mouvement dans une case vide je peux directement  être attaqué par le bas */
		else if (m_movements[i].end.col > 0 &&  m_board[ m_movements[i].end.line][m_movements[i].end.col - 1 ].box.content  == m_enemyColor && m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone)
		{
			enemyPiece = m_board[m_movements[i].end.line][m_movements[i].end.col - 1 ].box.piece;
			
			riskedMoves->listMoves[r].move = m_movements[i];
			riskedMoves->listMoves[r].caution=attributionRank(myPiece,enemyPiece,neighbour);
			riskedMoves->lenght_list++;
		}
		/* si 0n effectuant le mouvement dans une case contenant une piece ennemie */
		else if ( m_board[ m_movements[i].end.line][m_movements[i].end.col].box.content  == m_enemyColor )
		{
			enemyPiece = m_board[m_movements[i].end.line][m_movements[i].end.col].box.piece;
			neighbour=0;/*il s'agit d'une attaque*/

			riskedMoves->listMoves[r].move = m_movements[i];
			riskedMoves->listMoves[r].caution=attributionRank(myPiece,enemyPiece,neighbour);
			riskedMoves->lenght_list++;

		}
		else /* si en effectuant le mouvement je ne risque rien */
		{
			normalMoves->listMoves[r].move = m_movements[i];
			normalMoves->lenght_list++;
		}
	}	
}

// procedure interne a decideMoves
// evaluation globale des mouvements dupliqués et risqués 
void globalEvaluation(GroupMoves *priorityMoves, GroupMoves riskedMoves)
{
	// movement copie dans priorityMoves une seule fois avec son taux de risque non plus local mais global plus besoin d'avoir 2 taux
	// a faire
}

SMove chooseMove(const SGameState * const gameState, GroupMoves moves)
{
	/* Declaration des variables internes à la procédure*/
	int i = r = n = 0;
	
	/* on suppose que lorsque m_caution>5 les movements passer sont ceux des mouvements risqués*/
	if(m_caution>5)
	
}

//----- saveMove() -----//

// Enregistrement du plateau si déplacement simple
void saveMove()
{
	// On met la nouvelle pièce dans sa nouvelle case
	updateSquare(m_decidedMove.end,
		m_board[m_decidedMove.start.line][m_decidedMove.start.col].box.piece,
		m_color,
		m_board[m_decidedMove.start.line][m_decidedMove.start.col].isVisible,
		m_board[m_decidedMove.start.line][m_decidedMove.start.col].isBomb);

	// Puis on vide la case d'où vient la pièce
	updateSquare(m_decidedMove.start, EPnone, ECnone, false, false);
}

//----------- Fonctions utilisées à l'envoi d'un combat par l'arbitre -----------//

// Fonction interne à AttackResult
void analyseFight(EPiece PieceA, EPiece PieceB, SPos APos, SPos BPos)
{
	EPiece winner;

	if (PieceA != PieceB) // Si les deux pièces sont différentes, on analyse le fight
	{
		// On détermine le gagnant du combat		
		winner = winnerFight(PieceA, PieceB);

		if (winner == PieceA) // Si la pièce A a attaqué et gagné, on remplace la pièce B
		{
			printf("La pièce alliée %d gagne, la pièce ennemie %d perd\n", PieceA, PieceB);
			/* On place la pièce A sur la case où était la pièce B */
			updateSquare(BPos, PieceA, m_board[APos.line][APos.col].box.content, true, false);
		}
		else // Si la pièce A a perdu, on sauvegarde ce qu'est la pièce B
		{	
			printf("La pièce ennemie %d gagne, la pièce ennemie %d perd\n", PieceB, PieceA);
			updateSquare(BPos, PieceB, m_board[BPos.line][BPos.col].box.content, true, (PieceB == EPbomb) ? true : false);
		}		

		/* Dans tous les cas, la case d'où vient la pièce A devient vide */
		updateSquare(APos, EPnone, ECnone, false, false);
	}
	else // Si les deux pièces sont identiques, elles sont éliminées
	{
		printf("Les deux pièces sont identiques, elles sont éliminées\n");
		/* Plus rien dans la case de la pièce A */
		updateSquare(APos, EPnone, ECnone, false, false);

		/* Plus rien dans la case de la pièce B */
		updateSquare(BPos, EPnone, ECnone, false, false);
	}
}

// Fonction interne à AttackResult
EPiece winnerFight(EPiece A, EPiece B)
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

//----------- Fonctions à supprimer si inutilisées à la fin -----------//

// permet de savoir si pour une pièce à une position donnée,si on la deplace dans une direction donnée on est hors du tableau de jeu ou pas
bool limiteUnachieved(SPos position, Direction piecedirection)
{
	switch(piecedirection){
		case left: 
			if(position.col - 1 < 0)
				return false;
			else return true;
			break;
		case right:
			if(position.col + 1 > 9) 
				return false;
			else return true;
			break;
		case top:
			if(position.line + 1 > 9) 
				return false;
			else return true;
			break;
		case bottom:
			if(position.line - 1 < 0) 
				return false;
			else return true;
			break;
	}
	return true;
}

