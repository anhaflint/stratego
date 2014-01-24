#include "resources.h"
#include "riskProbability.h"

/*Permet d'avoir le nombre de piece ennemie cachée */
int getInfoHidedEnemyGlobal()
{
	int i, j;
	int numHidedEnemy = 0; //Nombre d'ennemis restants sur le plateau
	/* Parcours du plateau pour déterminer le nombre d'ennemis non visibles (EPnone) */
	for (i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			/* Si il y a un ennemi sur la case */
			if (m_board[i][j].box.content == m_enemyColor)
			{
				/* Si on ne connait pas la pièce */
				if(m_board[i][j].box.piece == EPnone)
					numHidedEnemy++;
			}
		}
	}
	return numHidedEnemy;
}

/* Permet d'avoir nombre de pièce ennemie cachée qui peuvent bouger */
int getInfoHidedEnemyMovable(const SGameState * const gameState)
{
	int numHidedEnemy; //Nombre d'ennemis restants sur le plateau
	int numHidedMovableEnemy; //nombre de pièce ennemie cachée qui peuvent bouger
	int numBomb; // Nombre de bombes visibles */
	int numFlag = 0; // Nombre de drapeau visible */
	
	numHidedEnemy = getInfoHidedEnemyGlobal();
	numBomb = getInfoHidedEnemyBomb(gameState);

	// on soutrait du nombre de pièce ennemie cachée, le nombre de bombe cachée et le drapeau caché */
	numHidedMovableEnemy = numHidedEnemy - numBomb - 1;

	return numHidedMovableEnemy;
}
 
/* Permet d'avoir nombre de piece ennemie de rang superieur à ma piece de plus haut rang cachée */ 
int getInfoHighEnemy (const SGameState * const gameState, EPiece myPiece)
{
	int numTotal = 0;
	int i, j;
	numTotal = calculateHighEnemy(numTotal, myPiece, (m_color == ECblue ? gameState->redOut : gameState->blueOut));

	for (i=0; i<10; i++)
		for (j=0; j<10; j++)
			/* Si la pièce est un ennemi visible et plus fort que myPiece, on décrémente numTotal */
			if ( (winnerFight(myPiece, m_board[i][j].box.piece) != myPiece) && (m_board[i][j].box.content == m_enemyColor) && (m_board[i][j].box.piece != EPnone))
				numTotal--;

	return numTotal;
}

/* calcule le nombre de piece de rang superieur à une piece */
int calculateHighEnemy(int numTotal, EPiece piece, const unsigned int pieceOut[])
{
	int numberEnemyPiece=0;
	
	if(piece == EPspy)
	{	
		numberEnemyPiece = 8 - pieceOut[piece + 1];
		return calculateHighEnemy( numTotal + numberEnemyPiece, EPscout, pieceOut);
	}
	else if(piece == EPscout)
	{
		numberEnemyPiece = 5 - pieceOut[piece + 1];
		return calculateHighEnemy( numTotal + numberEnemyPiece, EPminer, pieceOut);
	}
	else if(piece == EPminer)
	{
		numberEnemyPiece = 4 - pieceOut[piece + 1];
		return calculateHighEnemy( numTotal + numberEnemyPiece, EPsergeant, pieceOut);
	}
	else if(piece == EPsergeant)
	{
		numberEnemyPiece = 4 - pieceOut[piece + 1];
		return calculateHighEnemy( numTotal + numberEnemyPiece, EPlieutenant, pieceOut);
	}
	else if(piece == EPlieutenant)
	{
		numberEnemyPiece = 4 - pieceOut[piece + 1];
		return calculateHighEnemy( numTotal + numberEnemyPiece, EPcaptain, pieceOut);
	}
	else if(piece == EPcaptain)
	{
		numberEnemyPiece = 3 - pieceOut[piece + 1];
		return calculateHighEnemy( numTotal + numberEnemyPiece, EPmajor, pieceOut);
	}
	else if(piece == EPmajor)
	{
		numberEnemyPiece = 2 - pieceOut[piece + 1];
		return calculateHighEnemy( numTotal + numberEnemyPiece, EPcolonel, pieceOut);
	}
	else if(piece == EPcolonel)
	{
		numberEnemyPiece = 1 - pieceOut[piece + 1];
		return calculateHighEnemy( numTotal + numberEnemyPiece, EPgeneral, pieceOut);
	}
	else if(piece == EPgeneral)
	{
		 numberEnemyPiece = 1 - pieceOut[piece + 1];
		return calculateHighEnemy( numTotal + numberEnemyPiece, EPmarshal, pieceOut);
	}
	else if(piece == EPmarshal)
	{
		if (numTotal == 0)
			numberEnemyPiece = 1 - pieceOut[EPspy];
		else 
			numberEnemyPiece = 0;
	}

	return numberEnemyPiece + numTotal;
}

/* Permet d'avoir nombre de piece ennemie de rang inferieur à ma piece de plus haut rang cachée */ 
int getInfoLowEnemy(const SGameState * const gameState, EPiece myPiece)
{
	int numTotal = 0;
	int i, j;
	numTotal = calculateLowEnemy(numTotal, myPiece, (m_color == ECblue ? gameState->redOut : gameState->blueOut));

	for (i=0; i<10; i++)
		for (j=0; j<10; j++)
			/* Si la pièce est un ennemi visible et plus fort que myPiece, on décrémente numTotal */
			if ( (winnerFight(myPiece, m_board[i][j].box.piece) == myPiece) && (m_board[i][j].box.content ==m_enemyColor) && (m_board[i][j].box.piece != EPnone))
				numTotal--;
}

/* calcule le nombre de piece de rang inferieur à une piece */
int calculateLowEnemy(int numTotal, EPiece piece, const unsigned int pieceOut[])
{
	int numberEnemyPiece=0;
	
	if(piece == EPmarshal)
	{	
		numberEnemyPiece = 1 - pieceOut[piece - 1];
		return calculateLowEnemy( numTotal + numberEnemyPiece, EPgeneral, pieceOut);
	}
	else if(piece == EPgeneral)
	{
		numberEnemyPiece = 2 - pieceOut[piece - 1];
		return calculateLowEnemy( numTotal + numberEnemyPiece, EPcolonel, pieceOut);
	}
	else if(piece == EPcolonel)
	{
		numberEnemyPiece = 3 - pieceOut[piece - 1];
		return calculateLowEnemy( numTotal + numberEnemyPiece, EPmajor, pieceOut);
	}
	else if(piece == EPmajor)
	{
		numberEnemyPiece = 4 - pieceOut[piece - 1];
		return calculateLowEnemy( numTotal + numberEnemyPiece, EPcaptain, pieceOut);
	}
	else if(piece == EPcaptain)
	{
		numberEnemyPiece = 4 - pieceOut[piece - 1];
		return calculateLowEnemy( numTotal + numberEnemyPiece, EPlieutenant, pieceOut);
	}
	else if(piece == EPlieutenant)
	{
		numberEnemyPiece = 4 - pieceOut[piece - 1];
		return calculateLowEnemy( numTotal + numberEnemyPiece, EPsergeant, pieceOut);
	}
	else if(piece == EPsergeant)
	{
		numberEnemyPiece = 5 - pieceOut[piece - 1];
		return calculateLowEnemy( numTotal + numberEnemyPiece, EPminer, pieceOut);
	}
	else if(piece == EPminer)
	{
		numberEnemyPiece = 8 - pieceOut[piece - 1];
		return calculateLowEnemy( numTotal + numberEnemyPiece, EPscout, pieceOut);
	}
	else if(piece == EPscout)
	{
		 numberEnemyPiece = 1 - pieceOut[piece - 1];
		return calculateLowEnemy( numTotal + numberEnemyPiece, EPspy, pieceOut);
	}
	else if(piece == EPspy)
	{
		if (numTotal == 0)
			numberEnemyPiece = 1 - pieceOut[EPmarshal];
	}		

	return numberEnemyPiece + numTotal;
}

/* Permet d'avoir nombre de bombes ennemies cachées */
int getInfoHidedEnemyBomb(const SGameState * const gameState)
{
	int i, j;
	int numShownBomb = 0; // nombre de bombe ennemie découverte
	int numHidedBomb; // nombre de bombe ennemie cachée

	for (i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			/* Si il y a un ennemi sur la case */
			if (m_board[i][j].box.content ==m_enemyColor)
			{
				/* on calcule le nombre de bombes visibles */
				if(m_board[i][j].box.piece == EPbomb)
					numShownBomb++;
			}
		}
	}
	/*Dans chaque cas le nombre de bombes caché est equivalent au nombre maximal de bombe moins le nombre
	de bombes visibles moins le nombre de bombes éliminées */

	if (m_color == ECblue)
		numHidedBomb = 6 - numShownBomb - gameState->redOut[EPbomb];
	else
		numHidedBomb = 6 - numShownBomb - gameState->blueOut[EPbomb];

	return numHidedBomb;
}

/* Permet de savoir si le marshal ennemi est en vie et caché =1 sinon =0 */
int isHidedMarshal(const SGameState * const gameState)
{
	int i, j;
	bool marshalIsVisible = false; // variable permettant de savoir si le maréchal énnemi est visible

	for (i=0; (i<10 && !marshalIsVisible); i++)
	{
		for(j=0; (j<10 && !marshalIsVisible) ; j++)
		{
			/* Si il y a un ennemi sur la case */
			if (m_board[i][j].box.content ==m_enemyColor)
			{
				/* Si le marechal ennemi est visible */
				if(m_board[i][j].box.piece == EPmarshal)
					marshalIsVisible = true;
			}
		}
	}
	if (m_color == ECblue)
	{
		/* si le maréchal ennemie est visible ou mort */
		if(gameState->redOut[EPmarshal] == 1 || marshalIsVisible)
			return 0;
		else
			return 1;
	}
	else
	{
		/* si le maréchal ennemie est visible ou mort */
		if(gameState->blueOut[EPmarshal] == 1 || marshalIsVisible)
			return 0;
		else
			return 1;
	}	
}
