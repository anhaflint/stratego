#include <stdio.h>
#include "resources.h"
#include "decideMove.h"

/****** FONCTIONS DE DEBUG ******/

void drawGroupMoves(GroupMoves moves)
{
	int i;
	SMove move;
	for (i=0; i < moves.lenght_list; i++)
	{
		move = moves.listMoves[i].move;
		printf("--------------------------------\n");
		printf("| %d | (%d,%d) -> (%d,%d) | %f |\n", i, move.start.line, move.start.col, move.end.line, move.end.col, moves.listMoves[i].caution);
	}
	printf("\n");
}

// Décision du mouvement à effectuer
void decideMove(const SGameState * const gameState)
{
	printf("Démarrage de decideMove...\n");
	SMove choosedMove;
	
	// Décision du mouvemennt
	// Penser à mettre m_myMove à true lorsqu'on attaque l'ennemi
	/*j'ai besoin du coup precedent(m_decidedMove) pour determiner le suivant*/

	GroupMoves priorityMoves; // liste qui contient les mouvements non dupliqués et risqués évalués globalement( avec toutes les pieces énnemies voisines)
	GroupMoves normalMoves, riskedMoves;

	evaluateMoves(gameState, &normalMoves,&riskedMoves);
 	globalEvaluation(&priorityMoves,riskedMoves);

 	printf("[decideMove] PRINTF DES GROUPMOVES\n");

 	printf("[decideMove] ---- NORMALMOVES ----\n");
 	drawGroupMoves(normalMoves);

 	printf("[decideMove] ---- RISKEDMOVES ----\n");
 	drawGroupMoves(riskedMoves);

 	printf("[decideMove] ---- PRIORITYMOVES ----\n");
 	drawGroupMoves(priorityMoves);

 	printf("[decideMove] Stratégie choisie : %d\n", m_strategy);

 	switch(m_strategy)
 	{
	       case defensive || malicious || searchme :
				if(normalMoves.lenght_list > 0)// si il ya la possibilité de jouer sans perdre de pion
					choosedMove = chooseMove(gameState, normalMoves);
				else 
					choosedMove = chooseMove(gameState, priorityMoves);
	       break;

	       case str_default:
	       		choosedMove = chooseMove(gameState, normalMoves);
	       	break;
 	}

 	printf("[decideMove] choosedMove : (%d,%d) -> (%d,%d)\n", choosedMove.start.line, choosedMove.start.col, choosedMove.end.line, choosedMove.end.col);
 	/* A décommenter si test de lib */
 	// choosedMove = m_movements[0];

 	/* Mise à jour de la variable de nombre d'allers-retours */

 	// Si on a fait le mouvement inverse du précédent, on incrémente le nombre
 	if ((choosedMove.start.line == m_decidedMove.end.line)
 		&&(choosedMove.start.col == m_decidedMove.end.col)
 		&&(choosedMove.end.line == m_decidedMove.start.line)
 		&&(choosedMove.end.col == m_decidedMove.start.col))
 		m_nbRoundTrips++;
 	else // Sinon remise à zéro de la variable
 		m_nbRoundTrips = 1;

 	m_decidedMove = choosedMove;
}

// fonction interne a decideMove
// calcule la probabilité de risque pour la force des pieces ennemies voisines ou les pieces ennemies à attaquer directement
float riskProbability( const SGameState * const gameState,SPos myPosition,SPos enemyPosition)
{
	printf("Démarrage de riskProbability...\n");
	int i;  /*compteur*/
	int numHidedEnemyGlobal; /* nombre de piece ennemie cachée */
	int numHidedEnemyMovable; /* nombre de pièce ennemie cachée qui peuvent bouger */
	int numHighEnemy; /* nombre de piece ennemie de rang superieur à ma piece de plus haut rang cachée */
	int numLowEnemy; /* nombre de piece ennemie de rang inferieur à ma piece de plus bas rang cachée */
	int numHidedEnemyBomb; /* nombre de bombes ennemies cachées*/
	int hidedMarshal; /* Permet de savoir si le marshal ennemi est en vie et caché =1 sinon =0 */
	int numFlag = 1; /* nombre de drapeau */
	float winProbability; /* Probabilité de gagner l'adversaire */
	EPiece myPiece = gameState->board[myPosition.line][myPosition.col].piece; /* Notre pièce */
	/* recuperation des informations */

	numHidedEnemyGlobal = getInfoHidedEnemyGlobal();
	numHidedEnemyMovable = getInfoHidedEnemyMovable(gameState);
	numHighEnemy = getInfoHighEnemy(gameState, myPiece);
	numLowEnemy = getInfoLowEnemy(gameState, myPiece);
	numHidedEnemyBomb = getInfoHidedEnemyBomb(gameState);
	hidedMarshal = isHidedMarshal(gameState);

	/* calcul effectif des probabilités */

	/* Si l'ennemi a déjà bougé, donc ni bombe ni flag */
	if(m_board[enemyPosition.line][enemyPosition.col].isBomb == false)
	{
		if(m_board[myPosition.line][myPosition.col].box.piece == EPspy)
			winProbability = (hidedMarshal / numHidedEnemyMovable);
		else winProbability = (numLowEnemy / numHidedEnemyMovable);
	}
	else
	{
		if(m_board[myPosition.line][myPosition.col].box.piece == EPminer)
			winProbability = (numFlag + numHidedEnemyBomb + numLowEnemy) / numHidedEnemyGlobal;
		else
			{
				if(m_board[myPosition.line][myPosition.col].box.piece == EPspy)
					winProbability = (numFlag + hidedMarshal) / numHidedEnemyGlobal;
				else winProbability = (numLowEnemy + numFlag) / numHidedEnemyGlobal;
			}
	}
	return ((-20 * winProbability) + 10 );
}

// procedure interne a decideMoves
// Classement des mouvements en fonction du risque encouru
void evaluateMoves(const SGameState * const gameState,GroupMoves *normalMoves,GroupMoves *riskedMoves)
{
	printf("Démarrage de evaluateMoves...\n");
	/* Declaration des variables internes à la procédure*/
	int i = 0;
	bool neighbour=1;
	EPiece enemyPiece;
	EPiece myPiece;
	SPos myPosition;
	SPos enemyPosition;

	/* initialisation des longueurs de tableau des mouvements*/
	normalMoves->lenght_list= 0;
	riskedMoves->lenght_list= 0;


	printf("[evaluateMoves] Démarrage de la boucle principale..\n");
	/* classification des mouvements */
	while(i<m_nbMove)
	{
		/* information sur ma piece */
		myPiece = m_board[m_movements[i].start.line][m_movements[i].start.col].box.piece;
		myPosition = m_movements[i].start;
		bool flag = false; /* pour les risqués */

		printf("[evaluateMoves] Condition si non flag\n");
		if (!flag)
		{
			
			printf("[evaluateMoves] Evaluation en haut\n");
			/* si en effectuant le mouvement dans une case vide, je peux directement  être attaqué en haut  au prochain tour */
			if( m_movements[i].end.line < 9 &&  m_board[m_movements[i].end.line + 1][m_movements[i].end.col].box.content == m_enemyColor && m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone)
			{
				flag = true;
				/* informations sur l'ennemi */
				enemyPiece = m_board[m_movements[i].end.line + 1][m_movements[i].end.col].box.piece;
				enemyPosition.line = m_movements[i].end.line + 1;
				enemyPosition.col = m_movements[i].end.col;

				/* enregistrement d'informations sur le mouvement risqué */
				riskedMoves->listMoves[riskedMoves->lenght_list].move = m_movements[i];
							
				if( m_board[enemyPosition.line][enemyPosition.col].box.piece == EPnone)
					riskedMoves->listMoves[riskedMoves->lenght_list].caution = riskProbability(gameState,myPosition,enemyPosition);
				else
					riskedMoves->listMoves[riskedMoves->lenght_list].caution = attributionRank(myPiece,enemyPiece,neighbour);

				riskedMoves->lenght_list++;			
			}

			printf("[evaluateMoves] Evaluation en bas\n");
			/* si en effectuant le mouvement dans une case vide je peux directement  être attaqué en bas */
			if (m_movements[i].end.line > 0  &&  m_board[ m_movements[i].end.line - 1 ][m_movements[i].end.col].box.content  == m_enemyColor && m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone)
			{
				flag = true;
				/* informations sur l'ennemi */
				enemyPiece = m_board[m_movements[i].end.line - 1][m_movements[i].end.col].box.piece;
				enemyPosition.line = m_movements[i].end.line - 1;
				enemyPosition.col = m_movements[i].end.col;

				/* enregistrement d'informations sur le mouvement risqué */
				riskedMoves->listMoves[riskedMoves->lenght_list].move = m_movements[i];
				if( m_board[enemyPosition.line][enemyPosition.col].box.piece == EPnone)
					riskedMoves->listMoves[riskedMoves->lenght_list].caution = riskProbability(gameState,myPosition,enemyPosition);
				else
					riskedMoves->listMoves[riskedMoves->lenght_list].caution = attributionRank(myPiece,enemyPiece,neighbour);
				riskedMoves->lenght_list++;
			}

			printf("[evaluateMoves] Evaluation à droite\n");
			/* si en effectuant le mouvement dans une case videje peux directement  être attaqué à droite*/
			if (m_movements[i].end.col < 9 &&  m_board[ m_movements[i].end.line][m_movements[i].end.col + 1 ].box.content == m_enemyColor && m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone)
			{
				flag = true;
				/* informations sur l'ennemi */
				enemyPiece = m_board[m_movements[i].end.line][m_movements[i].end.col + 1].box.piece;
				enemyPosition.line = m_movements[i].end.line;
				enemyPosition.col = m_movements[i].end.col + 1;

				/* enregistrement d'informations sur le mouvement risqué */
				riskedMoves->listMoves[riskedMoves->lenght_list].move = m_movements[i];
				if( m_board[enemyPosition.line][enemyPosition.col].box.piece == EPnone)
					riskedMoves->listMoves[riskedMoves->lenght_list].caution = riskProbability(gameState,myPosition,enemyPosition);
				else
					riskedMoves->listMoves[riskedMoves->lenght_list].caution = attributionRank(myPiece,enemyPiece,neighbour);
				riskedMoves->lenght_list++;
			}

			printf("[evaluateMoves] Evaluation à gauche\n");
			/* si en effectuant le mouvement dans une case vide je peux directement  être attaqué par le bas */
			if (m_movements[i].end.col > 0 &&  m_board[ m_movements[i].end.line][m_movements[i].end.col - 1 ].box.content  == m_enemyColor && m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone)
			{
				flag = true;
				/* informations sur l'ennemi */
				enemyPiece = m_board[m_movements[i].end.line][m_movements[i].end.col - 1 ].box.piece;
				enemyPosition.line = m_movements[i].end.line;
				enemyPosition.col = m_movements[i].end.col - 1;

				/* enregistrement d'informations sur le mouvement risqué */
				riskedMoves->listMoves[riskedMoves->lenght_list].move = m_movements[i];
				if( m_board[enemyPosition.line][enemyPosition.col].box.piece == EPnone)
					riskedMoves->listMoves[riskedMoves->lenght_list].caution = riskProbability(gameState,myPosition,enemyPosition);
				else
					riskedMoves->listMoves[riskedMoves->lenght_list].caution = attributionRank(myPiece,enemyPiece,neighbour);
				riskedMoves->lenght_list++;
			}

			printf("[evaluateMoves] Evaluation sur case ennemie\n");
			/* si 0n effectuant le mouvement dans une case contenant une piece ennemie */
			if ( m_board[ m_movements[i].end.line][m_movements[i].end.col].box.content  == m_enemyColor )
			{
				flag = true;
				neighbour=0;/*il s'agit d'une attaque*/

				/* informations sur l'ennemi */
				enemyPiece = m_board[m_movements[i].end.line][m_movements[i].end.col].box.piece;
				enemyPosition.line = m_movements[i].end.line;
			
				/* enregistrement d'informations sur le mouvement risqué */
				riskedMoves->listMoves[riskedMoves->lenght_list].move = m_movements[i];
				if( m_board[enemyPosition.line][enemyPosition.col].box.piece == EPnone)
					riskedMoves->listMoves[riskedMoves->lenght_list].caution = riskProbability(gameState,myPosition,enemyPosition);
				else
					riskedMoves->listMoves[riskedMoves->lenght_list].caution = attributionRank(myPiece,enemyPiece,neighbour);
				riskedMoves->lenght_list++;

			}
		}		

		printf("[evaluateMoves] Evaluation si je ne risque rien\n");
		if(!flag)/* si en effectuant le mouvement je ne risque rien */
		{
			normalMoves->listMoves[normalMoves->lenght_list].move = m_movements[i];
			normalMoves->lenght_list++;
		}
		i++;
	}
}

// procedure interne a evaluateMoves
// Donne l'information sur la piece ennemie voisine pour evaluer le risque encouru
float attributionRank(EPiece myPiece,EPiece enemyPiece,bool evaluationType)
{	
	printf("Démarrage de attributionRank...\n");
	float forceDifference;// ecart de force entre la piece enemie et la mienne;
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
		else if((enemyPiece == EPspy && myPiece == EPmarshal) || (enemyPiece == EPmarshal && myPiece == EPspy))
			return 12;// le maximum warning 
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
			return (-12 * 2);
		/* cas ou la piece ennemie est la bombe et que la notre est un demineur */
		else if (enemyPiece == EPbomb && myPiece == EPminer)
			return (-11 * 2);
		/* cas ou la piece ennemie est une bombe */
		else if( enemyPiece == EPbomb )
			return (10 * 2);
		/* cas ou la piece ennemie est un marechal et la mienne un espion*/
		else if (enemyPiece == EPmarshal && myPiece == EPspy)
			return (12 * 2);// le maximun warning 
		/* cas où la piece de l'ennemi et la mienne est egale */
		else if (enemyPiece == myPiece)
			return (10 * 2);
		else
		{
			forceDifference = enemyPiece - myPiece;
		return (forceDifference * 2);
		} 
	}
}

// procedure interne a decideMove
// donne une priorité au mouvements normaux qui echappent à l'attaque de l'ennemi
void normalClassication(GroupMoves *normalMoves)
{
	printf("Démarrage de normalClassication...\n");
	int i; /* compteur */
	int numEnemy; /* nombres d'ennemi */
	while(i < normalMoves->lenght_list)
	{
		numEnemy=0;
		if( normalMoves->listMoves[i].move.start.line < 9 && m_board[normalMoves->listMoves[i].move.start.line + 1 ][normalMoves->listMoves[i].move.start.col].box.content == m_enemyColor)
			numEnemy++;
		if( normalMoves->listMoves[i].move.start.col < 9 && m_board[normalMoves->listMoves[i].move.start.line][normalMoves->listMoves[i].move.start.col + 1 ].box.content == m_enemyColor)
			numEnemy++;
		if( normalMoves->listMoves[i].move.start.line > 0 && m_board[normalMoves->listMoves[i].move.start.line -1 ][normalMoves->listMoves[i].move.start.col].box.content == m_enemyColor)
			numEnemy++;
		if( normalMoves->listMoves[i].move.start.col > 0 && m_board[normalMoves->listMoves[i].move.start.line][normalMoves->listMoves[i].move.start.col -1 ].box.content == m_enemyColor)
			numEnemy++;
		normalMoves->listMoves[i].caution=giveNormalRank(numEnemy);
	}
}

// fonction interne a normalClassication
// classifie les mouvements normaux en fonction du nombre de pièce énnemie environante 
float giveNormalRank(int numEnemy){
	printf("Démarrage de giveNormalRank...\n");
	if(numEnemy == 0)
		return 0 ;
	else if (numEnemy == 1)
		return 3;
	else if (numEnemy == 2)
		return 6;
	else if (numEnemy == 3)
		return 8;
	else if (numEnemy == 4)
		return 10;
}

// procedure interne a decideMoves
// evaluation globale des mouvements dupliqués et risqués 
void globalEvaluation(GroupMoves *priorityMoves, GroupMoves riskedMoves)
{
	printf("Démarrage de globalEvaluation...\n");
	// movement copie dans priorityMoves une seule fois avec son taux de risque non plus local mais global plus besoin d'avoir 2 taux
	// a faire
	int i, j; /* compteurs */
	GroupMoves buffer; /* tableau temporel utile pour le classement des mouvements */

	priorityMoves->lenght_list=0;

	for(i = 0; i < riskedMoves.lenght_list; i++)
	{	
		/* si on s'occupe du tyableau de mouvement pour la première fois */
		if(i == 0)
		{
			findOccurences(riskedMoves.listMoves[i].move, riskedMoves, &buffer);
			priorityMoves->listMoves[j].caution = globalProbability(buffer);
			priorityMoves->listMoves[j].move = riskedMoves.listMoves[i].move;
			priorityMoves->lenght_list++;
		}
		/* si le mouvement actuel n'a pas été pris en compte par le traitement précédent */
		else if (!isMovePresent(riskedMoves.listMoves[i].move,buffer))
		{
			emptyList(&buffer);
			findOccurences(riskedMoves.listMoves[i].move, riskedMoves, &buffer);
			priorityMoves->listMoves[j].caution = globalProbability(buffer);
			priorityMoves->listMoves[j].move = riskedMoves.listMoves[i].move;
			priorityMoves->lenght_list++;
		}
	}
}

// procedure interne à globalEvaluation
// cherche toutes les occurences d'un mouvement dans la liste de mouvements risqués et remplit le buffer 
void findOccurences(SMove movement,GroupMoves riskedMoves,GroupMoves *buffer)
{
	printf("Démarrage de findOccurences..\n");
 	int i = 0; /* compteurs */

 	buffer->lenght_list=0;
 	for(i=0;i < riskedMoves.lenght_list; i++)
 	{
 		if((riskedMoves.listMoves[i].move.start.line == movement.start.line)
 			&&(riskedMoves.listMoves[i].move.start.col == movement.start.col)
 			&&(riskedMoves.listMoves[i].move.end.line == movement.end.line)
 			&&(riskedMoves.listMoves[i].move.end.col == movement.end.col))
 		{
 			buffer->listMoves[buffer->lenght_list]=riskedMoves.listMoves[i];
 			buffer->lenght_list++;
		}
 	}
}

 // procedure interne à globalEvaluation
 // permet de donner le taux de risque global pour un mouvement
float globalProbability(GroupMoves buffer){
	printf("Démarrage de globalProbability...\n");
	int i=0; /* compteurs */
	float sumCautionNeighbour=0; /* somme des risques pour les mouvements risqué lies au ennemis environants */
	float cautionAttack; /* rique éventuel du mouvement d'attaque */

	for(i=0;i<buffer.lenght_list;i++)
	{
		/* mouvement d'attaque */
		if(buffer.listMoves[i].caution > 12 || buffer.listMoves[i].caution < -12)
			cautionAttack = buffer.listMoves[i].caution;
		else 
			sumCautionNeighbour += buffer.listMoves[i].caution;
	}

	float finalCaution = (sumCautionNeighbour / (buffer.lenght_list - 1) + (cautionAttack / 2) / 2 );

	return finalCaution;
}

// procedure interne a globalEvaluation
// permet de savoir si un mouvement est présent dans une liste de mouvement 
bool isMovePresent(SMove mouvement, GroupMoves buffer)
{
	printf("Démarrage de isMovePresent...\n");
	int i; /* compteur */

	for(i=0;i<buffer.lenght_list;i++)
	{
		if((buffer.listMoves[i].move.start.line == mouvement.start.line)
			&&(buffer.listMoves[i].move.start.col == mouvement.start.col)
			&&(buffer.listMoves[i].move.end.line == mouvement.end.line)
			&&(buffer.listMoves[i].move.end.col == mouvement.end.col))
			return true;
	}
	return false;
}

// procedure interne a globalEvaluation
// permet d'initialiser un tableau de mouvement
void emptyList(GroupMoves *buffer)
{
	printf("Démarrage de emptyList...\n");
	int i=0; /* compteur*/
	while(i<buffer->lenght_list)
	{
		buffer->listMoves[i].move.start.line=0;
		buffer->listMoves[i].move.end.line=0;
		buffer->listMoves[i].move.start.col=0;
		buffer->listMoves[i].move.end.col=0;
		buffer->listMoves[i].caution=0;
		i++;
	}
	buffer->lenght_list = 0;
}

SMove chooseMove(const SGameState * const gameState, GroupMoves moves)
{
	printf("Démarrage de chooseMove...\n");
	/* Declaration des variables internes à la procédure*/
	// int i = r = n = 0;
	
	// on suppose que lorsque m_caution>5 les movements passer sont ceux des mouvements risqués
 	//if(m_caution>5)
 	//{
 	
	// Valeur pour test de l'IA
 	return moves.listMoves[0].move;
}