#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "../structure.h"
#include "couleurs.h"

void initGameState(SGameState * const gameState);
void initBoard(InfoPiece m_board[10][10]);
void initBoxBoard(SBox m_board[10][10]);
void drawGameState(SGameState * const gameState);
void drawBoard(InfoPiece board[10][10]);
void drawBoxBoard(SBox board[10][10]);

int main(int argc, char* argv[])
{
	/* Initialisation du gameState */
	SGameState etatJeu;
	initGameState(&etatJeu);
	drawGameState(&etatJeu);

	/* Initialisation du tableau interne */
	InfoPiece m_board[10][10];	// Tableau du jeu de 10 cases par 10. dim1=ligne dim2=colonne
	initBoard(m_board);
	drawBoard(m_board);

	/* Tests */

	return 0;
}

void initGameState(SGameState * const gameState)
{
	initBoxBoard(gameState->board);
	int i;

	for (i=0; i<12; i++)
	{
		gameState->redOut[i] = 0;
		gameState->blueOut[i] = 0;
	}
}

void initBoard(InfoPiece board[10][10])
{
	int i,j;
	srand(time(NULL)); // Réinitialisation de l'aléatoire

	for (i=0; i<10; i++) // Lignes
	{
		for (j=0; j<10; j++) // Colonnes
		{
			if (i > 3 && i < 6 && ((j > 1 && j < 4)||(j > 5 && j < 8)))
			{
				board[i][j].box.content = EClake;
				board[i][j].box.piece = EPnone;
			}
			else
			{
				board[i][j].box.content = (i > 5) ? ECblue : ECnone;
				board[i][j].box.piece = EPnone;
			}
		}
	}

	EPiece initBoard[4][10] = {{11, 0, 8, 3, 0, 4, 0, 4, 5, 2},
						 		{0, 7, 3, 3, 5, 0, 3, 3, 5, 2},
						 		{4, 6, 6, 1, 6, 2, 4, 6, 0, 8},
						 		{2, 2, 7, 9, 2, 2, 10, 7, 2, 5}};

	for (i=0; i<4; i++)
	{
		for (j=0; j<10; j++)
		{
			board[i][j].box.piece = initBoard[i][j];
			board[i][j].box.content = ECred;
		}
	}
}

void initBoxBoard(SBox board[10][10])
{
	int i,j;
	srand(time(NULL)); // Réinitialisation de l'aléatoire

	for (i=0; i<10; i++) // Lignes
	{
		for (j=0; j<10; j++) // Colonnes
		{
			if (i > 3 && i < 6 && ((j > 1 && j < 4)||(j > 5 && j < 8)))
			{
				board[i][j].content = EClake;
				board[i][j].piece = EPnone;
			}
			else
			{
				board[i][j].content = (i > 5) ? ECblue : ECnone;
				board[i][j].piece = EPnone;
			}
		}
	}

	EPiece initBoard[4][10] = {{11, 0, 8, 3, 0, 4, 0, 4, 5, 2},
						 		{0, 7, 3, 3, 5, 0, 3, 3, 5, 2},
						 		{4, 6, 6, 1, 6, 2, 4, 6, 0, 8},
						 		{2, 2, 7, 9, 2, 2, 10, 7, 2, 5}};

	for (i=0; i<4; i++)
	{
		for (j=0; j<10; j++)
		{
			board[i][j].piece = initBoard[i][j];
			board[i][j].content = ECred;
		}		
	}	
}

void drawGameState(SGameState * const gameState)
{
	printf("\n-------------------------------------\n");
	drawBoxBoard(gameState->board);
	int i;

	for (i=0; i<12; i++)
	{
		printf("RED[%d] : [%d] | BLUE[%d] : [%d]\n", i, gameState->redOut[i], i, gameState->blueOut[i]);
	}
	printf("\n-------------------------------------\n");
}

void drawBoard(InfoPiece board[10][10])
{
	int i, j;
	printf("  |");
	for (i=0; i<10; i++)
	{
		couleur("33");
		printf(" %d  ", i);
		couleur("0");
		printf("|");
	}
	printf("\n");
	printf("-----------------------------------------------------\n");
	for (i=0; i<10; i++)
	{
		couleur("33");
		printf("%d ", 9-i);
		couleur("0");
		printf("|");

		for (j = 0; j < 10; ++j)
		{
			if (board[9-i][j].box.content == ECred)
				couleur("31");			
			if (board[9-i][j].box.content == ECblue)
				couleur("36");
			if (board[9-i][j].box.content == EClake)
				couleur("30");

			if (board[9-i][j].box.piece >= 10)
				printf(" %d", board[9-i][j].box.piece);		
			else
				printf(" %d ", board[9-i][j].box.piece);

			couleur("0");
			printf(" |");
				
		}
		printf("\n-----------------------------------------------------\n");
	}
	couleur("0");
}

void drawBoxBoard(SBox board[10][10])
{
	int i, j;
	printf("  |");
	for (i=0; i<10; i++)
	{
		couleur("33");
		printf(" %d  ", i);
		couleur("0");
		printf("|");
	}
	printf("\n");
	printf("-----------------------------------------------------\n");
	for (i=0; i<10; i++)
	{
		couleur("33");
		printf("%d ", 9-i);
		couleur("0");
		printf("|");

		for (j = 0; j < 10; ++j)
		{
			if (board[9-i][j].content == ECred)
				couleur("31");			
			if (board[9-i][j].content == ECblue)
				couleur("36");
			if (board[9-i][j].content == EClake)
				couleur("30");

			if (board[9-i][j].piece >= 10)
				printf(" %d", board[9-i][j].piece);		
			else
				printf(" %d ", board[9-i][j].piece);

			couleur("0");
			printf(" |");
				
		}
		printf("\n-----------------------------------------------------\n");
	}
	couleur("0");
}