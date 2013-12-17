#include <stdio.h>
#include <stdbool.h>
#include "couleurs.h"

typedef enum
{
	ECnone,
	EClake,
	ECred,
	ECblue
} EColor;

typedef enum
{
	EPbomb=0,
	EPspy,
	EPscout,
	EPminer,
	EPsergeant,
	EPlieutenant,
	EPcaptain,
	EPmajor,
	EPcolonel,
	EPgeneral,
	EPmarshal,
	EPflag,
	EPnone,
} EPiece;

typedef struct
{
	EColor content;
	EPiece piece;
} SBox;

// Structure de représentation d'une position
typedef struct
{
	int line;
	int col;
} SPos;

// Structure de représentation d'un mouvement
typedef struct
{
	SPos start;
	SPos end;
} SMove;

// Structure qui sera interne à l'ia
typedef struct{
	SBox box;
	bool isVisible;
	bool isBomb;
}InfoPiece;

void initBoard(InfoPiece m_board[10][10]);
void drawBoard(InfoPiece board[10][10]);
void analyzeBoard(InfoPiece m_board[10][10]);
void addAnalyzedMove(InfoPiece m_board[10][10], EColor m_color, SMove m_movements[172], int i, int j, int new_i, int new_j, int is_i, int lim, unsigned int* compteur);
void drawMoves(SMove moves[170], int m_nbMove);

int main(int argc, char* argv[])
{
	InfoPiece m_board[10][10];	// Tableau du jeu de 10 cases par 10. dim1=ligne dim2=colonne
	initBoard(m_board);
	drawBoard(m_board);
	analyzeBoard(m_board);
	return 0;
}

void initBoard(InfoPiece board[10][10])
{
	int i,j;

	for (i=0; i<10; i++) // Lignes
	{
		for (j=0; j<10; j++) // Colonnes
		{
			if (i > 3 && i < 6 && ((j > 1 && j < 4)||(j > 5 && j < 8)))
			{
				board[i][j].box.content = EClake;
				board[i][j].box.piece = EPnone;
			}
			else if (i < 4)
			{
				board[i][j].box.content = ECblue;
				board[i][j].box.piece = EPspy;
			}				
			else if (i > 5)
			{
				board[i][j].box.content = ECred;
				board[i][j].box.piece = EPscout;				
			}
			else
			{
				board[i][j].box.content = ECnone;
				board[i][j].box.piece = EPnone;
			}				
		}
	}	
}

void drawBoard(InfoPiece board[10][10])
{
	int i, j;
	printf("  | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  |\n");
	printf("-----------------------------------------------------\n");
	for (i=0; i<10; i++)
	{
		printf("%d |", 9-i);
		for (j = 0; j < 10; ++j)
		{

			if (board[i][j].box.content == ECred)
				couleur("31");			
			if (board[i][j].box.content == ECblue)
				couleur("36");
			if (board[i][j].box.content == EClake)
				couleur("30");

			if (board[i][j].box.piece > 10)
				printf(" %d", board[i][j].box.piece);		
			else
				printf(" %d ", board[i][j].box.piece);

			couleur("0");
			printf(" |");
				
		}
		printf("\n-----------------------------------------------------\n");
	}
	couleur("0");
}

// Analyse du plateau => Mise à jour des déplacements possibles
void analyzeBoard(InfoPiece m_board[10][10])
{
	int m_nbMove;
	unsigned int i, j, compteur = 0;
	SMove m_movements[172];
	EColor m_color = ECblue;

	for (i=0; i<10; i++)
	{
		for (j=0; j<10; j++)
		{
			/* Si la pièce est une pièce appartenant à l'IA et qu'elle est
			déplaçable, on regarde les cases aux alentours */
			if ((m_board[i][j].box.content == m_color) && (m_board[i][j].box.piece != EPbomb) && (m_board[i][j].box.piece != EPflag))
			{				
				// Si on n'est pas sur la ligne du bas et qu'on peut bouger sur la case du dessous, rajout du mouvement
				addAnalyzedMove(m_board, m_color, m_movements, i, j, i-1, j, 1, 0, &compteur);

				// Si on n'est pas sur la ligne du dessus et qu'on peut bouger sur la case du dessus, rajout du mouvement
				addAnalyzedMove(m_board, m_color, m_movements, i, j, i+1, j, 1, 9, &compteur);

				// Si on n'est pas sur la ligne de gauche et qu'on peut bouger sur la case de gauche, rajout du mouvement
				addAnalyzedMove(m_board, m_color, m_movements, i, j, i, j-1, 0, 0, &compteur);

				// Si on n'est pas sur la ligne de droite et qu'on peut bouger sur la case de droite, rajout du mouvement
				addAnalyzedMove(m_board, m_color, m_movements, i, j, i, j+1, 0, 9, &compteur);
			}
		}
	}

	m_nbMove = compteur;
	printf("Nombre de mouvements trouvés : %d\n", m_nbMove);
	drawMoves(m_movements, m_nbMove);
}

// Sous-fonction de l'analyse du plateau
void addAnalyzedMove(InfoPiece m_board[10][10], EColor m_color, SMove m_movements[172], int i, int j, int new_i, int new_j, int is_i, int lim, unsigned int* compteur)
{	
	int temp;	
	SPos start, end;
	EColor enemyColor;
	if (m_color == ECred)
		enemyColor = ECblue;
	else
		enemyColor = ECred;

	int val, newVal;
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

	int dirLine, dirCol;
	dirLine = new_i - i;
	dirCol = new_j - j;

	if ((val != lim) && (m_board[new_i][new_j].box.content != EClake) && (m_board[new_i][new_j].box.content != m_color)) 
	{
		start.line = 9-i; start.col = j;
		end.line = 9-new_i; end.col = new_j;
		m_movements[*compteur].start = start;
		m_movements[*compteur].end = end;
		(*compteur)++;

		/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
		if (m_board[i][j].box.piece == EPscout)
		{
			temp = newVal;
			
			while ((temp != lim) && (m_board[new_i+dirLine][new_j+dirCol].box.content != EClake) && (m_board[new_i+dirLine][new_j+dirCol].box.content != m_color) && (m_board[new_i][new_j].box.content != enemyColor))
			{
				start.line = 9-i; start.col = j;
				end.line = 9-(new_i+dirLine); end.col = new_j+dirCol;
				m_movements[*compteur].start = start;
				m_movements[*compteur].end = end;
				(*compteur)++;

				if ((dirLine < 0)||(dirCol < 0))
					temp--;
				else
					temp++;

				if (is_i == 1)
					new_i = temp;
				else
					new_j = temp;				
			}
		}						
	}
}

// Afficher les mouvements analysés
void drawMoves(SMove moves[170], int m_nbMove)
{
	int i;

	for (i = 0; i < m_nbMove; i++)
	{
		printf("( %d,%d ) -> ( %d,%d )\n", moves[i].start.line, moves[i].start.col, moves[i].end.line, moves[i].end.col);
	}
}