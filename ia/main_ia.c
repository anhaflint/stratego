#include <stdio.h>
#include <stdbool.h>

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
void drawMoves(SMove moves[170], int m_nbMove);
void analyzeBoard(InfoPiece m_board[10][10]);

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

	for (i=0; i<10; i++)
	{
		for (j=0; j<10; j++)
		{
			if (j < 4)
			{
				board[i][j].box.content = ECblue;
				board[i][j].box.piece = EPscout;
			}				
			else if (j > 5)
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
	printf("  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |\n");
	printf("-------------------------------------------\n");
	for (i=0; i<10; i++)
	{
		printf("%d |", i);
		for (j = 0; j < 10; ++j)
		{
			printf(" %d |", board[i][j].box.piece);
		}
		printf("\n-------------------------------------------\n");
	}
}

// Analyse du plateau => Mise à jour des déplacements possibles
void analyzeBoard(InfoPiece m_board[10][10])
{
	int m_nbMove;
	unsigned int i, j, temp, compteur = 0;
	SPos start, end;
	SMove m_movements[172];
	EColor m_color = ECblue;
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
			if ((m_board[i][j].box.content == m_color) && (m_board[i][j].box.piece != EPbomb) && (m_board[i][j].box.piece != EPflag))
			{				
				// Si on n'est pas sur la ligne du bas et qu'on peut bouger sur la case du dessous, rajout du mouvement
				if ((i != 0) && (m_board[i-1][j].box.content != EClake) && (m_board[i-1][j].box.content != m_color)) 
				{
					start.line = i; start.col = j;
					end.line = i-1; end.col = j;
					m_movements[compteur].start = start;
					m_movements[compteur].end = end;
					compteur++;

					/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
					if (m_board[i][j].box.piece == EPscout)
					{
						temp = i-1;
						/* On rajoute une condition supplémentaire : on s'arrête dès qu'on tombe sur une case contenant un ennemi */
						while ((temp != 0) && (m_board[temp-1][j].box.content != EClake) && (m_board[temp-1][j].box.content != m_color) && (m_board[temp][j].box.content != enemyColor))
						{
							start.line = i; start.col = j;
							end.line = temp-1; end.col = j;
							m_movements[compteur].start = start;
							m_movements[compteur].end = end;
							compteur++;
							temp--;
						}
					}							
				}
			
				// Si on n'est pas sur la ligne du dessus et qu'on peut bouger sur la case du dessus, rajout du mouvement
				if ((i != 9) && (m_board[i+1][j].box.content != EClake) && (m_board[i+1][j].box.content != m_color)) 
				{
					start.line = i; start.col = j;
					end.line = i+1; end.col = j;
					m_movements[compteur].start = start;
					m_movements[compteur].end = end;
					compteur++;

					/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
					if (m_board[i][j].box.piece == EPscout)
					{
						temp = i+1;
						/* On rajoute une condition supplémentaire : on s'arrête dès qu'on tombe sur une case contenant un ennemi */
						while ((temp != 9) && (m_board[temp+1][j].box.content != EClake) && (m_board[temp+1][j].box.content != m_color) && (m_board[temp][j].box.content != enemyColor))
						{
							start.line = i; start.col = j;
							end.line = temp+1; end.col = j;
							m_movements[compteur].start = start;
							m_movements[compteur].end = end;
							compteur++;
							temp++;
						}
					}	
				}
				
				// Si on n'est pas sur la ligne de gauche et qu'on peut bouger sur la case de gauche, rajout du mouvement
				if ((j != 0) && (m_board[i][j-1].box.content != EClake) && (m_board[i][j-1].box.content != m_color))
				{
					start.line = i; start.col = j;
					end.line = i; end.col = j-1;
					m_movements[compteur].start = start;
					m_movements[compteur].end = end;
					compteur++;

					/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
					if (m_board[i][j].box.piece == EPscout)
					{
						temp = j-1;
						/* On rajoute une condition supplémentaire : on s'arrête dès qu'on tombe sur une case contenant un ennemi */
						while ((temp != 0) && (m_board[i][temp-1].box.content != EClake) && (m_board[i][temp-1].box.content != m_color) && (m_board[i][temp].box.content != enemyColor))
						{
							start.line = i; start.col = j;
							end.line = i; end.col = temp-1;
							m_movements[compteur].start = start;
							m_movements[compteur].end = end;
							compteur++;
							temp--;
						}
					}
				} 

				// Si on n'est pas sur la ligne de droite et qu'on peut bouger sur la case de droite, rajout du mouvement
				if ((j != 9) && (m_board[i][j+1].box.content != EClake) && (m_board[i][j+1].box.content != m_color))
				{
					start.line = i; start.col = j;
					end.line = i; end.col = j+1;
					m_movements[compteur].start = start;
					m_movements[compteur].end = end;
					compteur++;

					/* Si la pièce étudiée est un éclaireur, on regarde tous les déplacements possibles en ligne */
					if (m_board[i][j].box.piece == EPscout)
					{
						temp = j+1;
						/* On rajoute une condition supplémentaire : on s'arrête dès qu'on tombe sur une case contenant un ennemi */
						while ((temp != 9) && (m_board[i][temp+1].box.content != EClake) && (m_board[i][temp+1].box.content != m_color) && (m_board[i][temp].box.content != enemyColor))
						{
							start.line = i; start.col = j;
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
	printf("Nombre de mouvements trouvés : %d\n", m_nbMove);
	drawMoves(m_movements, m_nbMove);
}

void drawMoves(SMove moves[170], int m_nbMove)
{
	int i;

	for (i = 0; i < m_nbMove; i++)
	{
		printf("( %d,%d ) -> ( %d,%d )\n", moves[i].start.line, moves[i].start.col, moves[i].end.line, moves[i].end.col);
	}
}