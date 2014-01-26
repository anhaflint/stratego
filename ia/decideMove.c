#include <stdio.h>
#include <time.h>
#include "resources.h"
#include "decideMove.h"

// Choix d'un type
int chooseTypeOfMove(const SGameState * const gameState, int normalMoves, int priorityMoves)
{
	// Choix obligatoire si une des listes est vide
	if (normalMoves == 0)
		return 0;
	else if (priorityMoves == 0)
		return 1;

	// Valeurs des maximum de chaque ennemi
	int nbRedOnBoard[11];
	int nbBlueOnBoard[11];
	int nbMax[11];
	int nbRedPieces=0, nbBluePieces=0;

	nbMax[EPspy] = 1;
	nbMax[EPscout] = 8;
	nbMax[EPminer] = 5;
	nbMax[EPsergeant] = 4;
	nbMax[EPlieutenant] = 4;
	nbMax[EPcaptain] = 4;
	nbMax[EPmajor] = 3;
	nbMax[EPcolonel] = 2;
	nbMax[EPgeneral] = 1;
	nbMax[EPmarshal] = 1;
	
	// Calcul de l'espérance de force des pièces de chaque côté
	float esperanceBlue = 0;
	float esperanceRed = 0;
	int i;

	/* On somme les forces de toutes les pièces
	movibles restantes chez l'ennemi */
	for (i=1; i < 11; i++)
	{
		nbRedOnBoard[i] = nbMax[i] - gameState->redOut[i];
		nbRedPieces += nbRedOnBoard[i];

		nbBlueOnBoard[i] = nbMax[i] - gameState->blueOut[i];
		nbBluePieces += nbBlueOnBoard[i];		
	}

	/* On calcule l'espérance à l'aide des données */
	for (i=1; i < 11; i++)
	{
		esperanceRed += ((float)nbRedOnBoard[i]/(float)nbRedPieces)*(float)i;
		esperanceBlue += ((float)nbBlueOnBoard[i]/(float)nbBluePieces)*(float)i;
	}

	/* On ne fait un mouvement risqué que dans le cas où notre espérance est supérieure
	à celle de l'ennemi. On retourne notre choix avec la ligne suivante */
	return ((m_color == ECblue) ? (esperanceBlue < esperanceRed) : (esperanceRed < esperanceBlue));
}

// Décision du mouvement à effectuer
void decideMove(const SGameState * const gameState)
{
	SMove choosedMove;
	int choice;
	
	// Décision du mouvemennt
	/*j'ai besoin du coup precedent(m_decidedMove) pour determiner le suivant*/

	GroupMoves priorityMoves; // liste qui contient les mouvements non dupliqués et risqués évalués globalement( avec toutes les pieces énnemies voisines)
	GroupMoves normalMoves, riskedMoves;

	evaluateMoves(gameState, &normalMoves,&riskedMoves);
 	globalEvaluation(&priorityMoves,riskedMoves, gameState);
 	normalClassication(gameState, &normalMoves);

 	/* Choix du type de mouvement à faire en fonction
 	du gameState et des mouvements trouvés */
	choice = chooseTypeOfMove(gameState, normalMoves.length_list, riskedMoves.length_list);

	if(choice == 0)
		choosedMove = chooseMove(gameState, priorityMoves);
	else
		choosedMove = chooseMove(gameState, normalMoves);

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

 	/* Vérification si le mouvement est une attaque pour la valeur de m_myMove */
 	if (gameState->board[m_decidedMove.end.line][m_decidedMove.end.col].content == m_enemyColor)
 		m_myMove = true;
}

// fonction interne a decideMove
// calcule la probabilité de risque pour la force des pieces ennemies voisines ou les pieces ennemies à attaquer directement
float riskProbability( const SGameState * const gameState,SPos myPosition,SPos enemyPosition)
{
	int i;  /*compteur*/
	int numHidedEnemyGlobal; /* nombre de piece ennemie cachée */
	int numHidedEnemyMovable; /* nombre de pièce ennemie cachée qui peuvent bouger */
	int numHighEnemy; /* nombre de piece ennemie de rang superieur à ma piece de plus haut rang cachée */
	int numLowEnemy; /* nombre de piece ennemie de rang inferieur à ma piece de plus bas rang cachée */
	int numHidedEnemyBomb; /* nombre de bombes ennemies cachées*/
	int hidedMarshal; /* Permet de savoir si le marshal ennemi est en vie et caché =1 sinon =0 */
	int numFlag = 1.f; /* nombre de drapeau */
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
			winProbability = ((float)hidedMarshal / (float)numHidedEnemyMovable);
		else 
			winProbability = ((float)numLowEnemy / (float)numHidedEnemyMovable);
	}
	else
	{
		if(m_board[myPosition.line][myPosition.col].box.piece == EPminer)
			winProbability = ((float)numFlag + (float)numHidedEnemyBomb + (float)numLowEnemy) / (float)numHidedEnemyGlobal;
		else
		{
			if(m_board[myPosition.line][myPosition.col].box.piece == EPspy)
				winProbability = ((float)numFlag + (float)hidedMarshal) / (float)numHidedEnemyGlobal;
			else 
				winProbability = ((float)numLowEnemy + (float)numFlag) / (float)numHidedEnemyGlobal;
		}
	}
	return ((-20 * winProbability) + 10);
}

// procedure interne a decideMoves
// Classement des mouvements en fonction du risque encouru
void evaluateMoves(const SGameState * const gameState,GroupMoves *normalMoves,GroupMoves *riskedMoves)
{
	/* Declaration des variables internes à la procédure*/
	int i = 0;
	bool neighbour=1;
	EPiece enemyPiece;
	EPiece myPiece;
	SPos myPosition;
	SPos enemyPosition;

	/* initialisation des longueurs de tableau des mouvements*/
	normalMoves->length_list= 0;
	riskedMoves->length_list= 0;
	
	/* classification des mouvements */
	while(i<m_nbMove)
	{
		/* information sur ma piece */
		myPiece = m_board[m_movements[i].start.line][m_movements[i].start.col].box.piece;
		myPosition = m_movements[i].start;
		bool flag = false; /* pour les risqués */
		
		if (!flag)
		{			
			/* si en effectuant le mouvement dans une case vide, je peux directement  être attaqué en haut  au prochain tour */
			if( m_movements[i].end.line < 9 
				&&  m_board[m_movements[i].end.line + 1][m_movements[i].end.col].box.content == m_enemyColor 
				&& (m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone 
					|| m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == m_enemyColor))
			{
				flag = true;
				/* informations sur l'ennemi */
				enemyPiece = m_board[m_movements[i].end.line + 1][m_movements[i].end.col].box.piece;
				enemyPosition.line = m_movements[i].end.line + 1;
				enemyPosition.col = m_movements[i].end.col;

				/* enregistrement d'informations sur le mouvement risqué */
				riskedMoves->listMoves[riskedMoves->length_list].move = m_movements[i];
							
				if( m_board[enemyPosition.line][enemyPosition.col].box.piece == EPnone)
					riskedMoves->listMoves[riskedMoves->length_list].caution = riskProbability(gameState,myPosition,enemyPosition);
				else
					riskedMoves->listMoves[riskedMoves->length_list].caution = attributionRank(myPiece,enemyPiece,neighbour);

				riskedMoves->length_list++;			
			}

			/* si en effectuant le mouvement dans une case vide je peux directement  être attaqué en bas */
			if (m_movements[i].end.line > 0  
				&&  m_board[ m_movements[i].end.line - 1 ][m_movements[i].end.col].box.content  == m_enemyColor 
				&& (m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone
					|| m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == m_enemyColor))
			{
				flag = true;
				/* informations sur l'ennemi */
				enemyPiece = m_board[m_movements[i].end.line - 1][m_movements[i].end.col].box.piece;
				enemyPosition.line = m_movements[i].end.line - 1;
				enemyPosition.col = m_movements[i].end.col;

				/* enregistrement d'informations sur le mouvement risqué */
				riskedMoves->listMoves[riskedMoves->length_list].move = m_movements[i];
				if( m_board[enemyPosition.line][enemyPosition.col].box.piece == EPnone)
					riskedMoves->listMoves[riskedMoves->length_list].caution = riskProbability(gameState,myPosition,enemyPosition);
				else
					riskedMoves->listMoves[riskedMoves->length_list].caution = attributionRank(myPiece,enemyPiece,neighbour);
				riskedMoves->length_list++;
			}

			/* si en effectuant le mouvement dans une case videje peux directement  être attaqué à droite*/
			if (m_movements[i].end.col < 9 
				&&  m_board[ m_movements[i].end.line][m_movements[i].end.col + 1 ].box.content == m_enemyColor 
				&& (m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone
					|| m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == m_enemyColor))
			{
				flag = true;
				/* informations sur l'ennemi */
				enemyPiece = m_board[m_movements[i].end.line][m_movements[i].end.col + 1].box.piece;
				enemyPosition.line = m_movements[i].end.line;
				enemyPosition.col = m_movements[i].end.col + 1;

				/* enregistrement d'informations sur le mouvement risqué */
				riskedMoves->listMoves[riskedMoves->length_list].move = m_movements[i];
				if( m_board[enemyPosition.line][enemyPosition.col].box.piece == EPnone)
					riskedMoves->listMoves[riskedMoves->length_list].caution = riskProbability(gameState,myPosition,enemyPosition);
				else
					riskedMoves->listMoves[riskedMoves->length_list].caution = attributionRank(myPiece,enemyPiece,neighbour);
				riskedMoves->length_list++;
			}

			/* si en effectuant le mouvement dans une case vide je peux directement  être attaqué par le bas */
			if (m_movements[i].end.col > 0 
				&&  m_board[ m_movements[i].end.line][m_movements[i].end.col - 1 ].box.content  == m_enemyColor 
				&& (m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == ECnone
					|| m_board[m_movements[i].end.line][m_movements[i].end.col].box.content == m_enemyColor))
			{
				flag = true;
				/* informations sur l'ennemi */
				enemyPiece = m_board[m_movements[i].end.line][m_movements[i].end.col - 1 ].box.piece;
				enemyPosition.line = m_movements[i].end.line;
				enemyPosition.col = m_movements[i].end.col - 1;

				/* enregistrement d'informations sur le mouvement risqué */
				riskedMoves->listMoves[riskedMoves->length_list].move = m_movements[i];
				if( m_board[enemyPosition.line][enemyPosition.col].box.piece == EPnone)
					riskedMoves->listMoves[riskedMoves->length_list].caution = riskProbability(gameState,myPosition,enemyPosition);
				else
					riskedMoves->listMoves[riskedMoves->length_list].caution = attributionRank(myPiece,enemyPiece,neighbour);
				riskedMoves->length_list++;
			}

			/* si 0n effectuant le mouvement dans une case contenant une piece ennemie */
			if ( m_board[m_movements[i].end.line][m_movements[i].end.col].box.content  == m_enemyColor )
			{
				flag = true;
				neighbour=0;/*il s'agit d'une attaque*/

				/* informations sur l'ennemi */
				enemyPiece = m_board[m_movements[i].end.line][m_movements[i].end.col].box.piece;
				enemyPosition.line = m_movements[i].end.line;
				enemyPosition.col = m_movements[i].end.col;

				/* enregistrement d'informations sur le mouvement risqué */
				riskedMoves->listMoves[riskedMoves->length_list].move = m_movements[i];

				if(m_board[enemyPosition.line][enemyPosition.col].box.piece == EPnone)
					riskedMoves->listMoves[riskedMoves->length_list].caution = riskProbability(gameState,myPosition,enemyPosition);				
				else
					riskedMoves->listMoves[riskedMoves->length_list].caution = attributionRank(myPiece,enemyPiece,neighbour);				
				riskedMoves->length_list++;
			}
		}		

		if(!flag)/* si en effectuant le mouvement je ne risque rien */
		{
			normalMoves->listMoves[normalMoves->length_list].move = m_movements[i];
			normalMoves->length_list++;
		}
		i++;
	}
}

// procedure interne a evaluateMoves
// Donne l'information sur la piece ennemie voisine pour evaluer le risque encouru
float attributionRank(EPiece myPiece,EPiece enemyPiece,bool evaluationType)
{
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
			return -12.f;
		/* cas ou la piece ennemie est la bombe et que la notre est un demineur */
		else if (enemyPiece == EPbomb && myPiece == EPminer)
			return -11.f;
		/* cas ou la piece ennemie est une bombe ou l'espion */
		else if( enemyPiece == EPbomb || (enemyPiece == EPspy && myPiece != EPmarshal))
			return 0.f;
		/* cas ou la piece ennemie est un espion et la mienne un marechal */
		else if((enemyPiece == EPspy && myPiece == EPmarshal) || (enemyPiece == EPmarshal && myPiece == EPspy))
			return 12.f;// le maximum warning 
		/* cas où la piece de l'ennemi et la mienne est egale */
		else if (enemyPiece == myPiece)
			return 10.f;
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
			return -12.f;
		/* cas ou la piece ennemie est la bombe et que la notre est un demineur */
		else if (enemyPiece == EPbomb && myPiece == EPminer)
			return -11.f;
		/* cas ou la piece ennemie est une bombe */
		else if( enemyPiece == EPbomb )
			return 10.f;
		/* cas ou la piece ennemie est un marechal et la mienne un espion*/
		else if (enemyPiece == EPmarshal && myPiece == EPspy)
			return 12.f;// le maximun warning 
		/* cas où la piece de l'ennemi et la mienne est egale */
		else if (enemyPiece == myPiece)
			return 10.f;
		else
		{
			forceDifference = enemyPiece - myPiece;
		return (forceDifference);
		} 
	}
}

// Procédure interne à normalClassification
// Permet de connaître le nombre d'ennemis encore présents sur le plateau
int nbAliveEnemies(const SGameState * const gameState)
{
	int nbDeadEnemies = 0;
	int i;

	if (m_color == ECred)
	{
		for (i=0; i < 12; i++)
			nbDeadEnemies += gameState->blueOut[i];
	}
	else
	{
		for (i=0; i < 12; i++)
			nbDeadEnemies += gameState->redOut[i];
	}

	return 40 - nbDeadEnemies;
}

// procedure interne a decideMove
// donne une priorité aux mouvements normaux remplissant certains critères
void normalClassication(const SGameState * const gameState, GroupMoves *normalMoves)
{
	int i = 0; /* compteur */
	int numEnemy; /* nombres d'ennemi */

	while(i < normalMoves->length_list)
	{
		// Donne une priorité aux fuites si un allié est proche d'un ou plusieurs ennemis
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

		// Donner priorité à une pièce qui a déjà bougé
		if (!(m_board[normalMoves->listMoves[i].move.start.line][normalMoves->listMoves[i].move.start.col].isBomb))
			normalMoves->listMoves[i].caution -= 5.f;

		// Donne une priorité si pièce plus forte que plus des 3/4 des pièces du plateau
		if ((float) getInfoLowEnemy(gameState, gameState->board[normalMoves->listMoves[i].move.start.line][normalMoves->listMoves[i].move.start.col].piece)
			> (3.f/4.f)*nbAliveEnemies(gameState))
			normalMoves->listMoves[i].caution -= 5.f;

		// Réglage de priorité en fonction de la hauteur sur le plateau et la force de la pièce pour mouvement vers le haut
		if ((normalMoves->listMoves[i].move.end.line - normalMoves->listMoves[i].move.start.line) > 0)
			normalMoves->listMoves[i].caution -= 0.1*(float)(gameState->board[normalMoves->listMoves[i].move.start.line][normalMoves->listMoves[i].move.start.col].piece)*(float)(normalMoves->listMoves[i].move.start.line);

		i++;
	}
}

// fonction interne a normalClassication
// classifie les mouvements normaux en fonction du nombre de pièce énnemie environante 
float giveNormalRank(int numEnemy)
{
	if(numEnemy == 0)
		return 0.f ;
	else if (numEnemy == 1)
		return 3.f;
	else if (numEnemy == 2)
		return 6.f;
	else if (numEnemy == 3)
		return 8.f;
	else if (numEnemy == 4)
		return 10.f;
}

// procedure interne a decideMoves
// evaluation globale des mouvements dupliqués et risqués 
void globalEvaluation(GroupMoves *priorityMoves, GroupMoves riskedMoves, const SGameState * const gameState)
{
	// movement copie dans priorityMoves une seule fois avec son taux de risque non plus local mais global plus besoin d'avoir 2 taux
	// a faire
	int i, j = 0; /* compteurs */
	GroupMoves buffer; /* tableau temporel utile pour le classement des mouvements */

	priorityMoves->length_list=0;

	for(i = 0; i < riskedMoves.length_list; i++)
	{	
		/* si on s'occupe du tableau de mouvement pour la première fois */
		if(i == 0)
		{
			findOccurences(riskedMoves.listMoves[i].move, riskedMoves,&buffer);
			if (buffer.length_list == 1)
				priorityMoves->listMoves[j].caution = buffer.listMoves[0].caution;
			else
				priorityMoves->listMoves[j].caution = globalProbability(buffer);

			/* Rajout de probabilité si on est un scout et qu'on peut bouger en haut */
			
			if ((gameState->board[riskedMoves.listMoves[i].move.end.line][riskedMoves.listMoves[i].move.end.col].content == m_enemyColor)
			&&(gameState->board[riskedMoves.listMoves[i].move.start.line][riskedMoves.listMoves[i].move.start.col].piece == EPscout)
			&&((riskedMoves.listMoves[i].move.end.line - riskedMoves.listMoves[i].move.start.line) > 0))
				priorityMoves->listMoves[j].caution -= 10.f;

			priorityMoves->listMoves[j].move = riskedMoves.listMoves[i].move;
			priorityMoves->length_list++;
			j++;
		}
		/* si le mouvement actuel n'a pas été pris en compte par le traitement précédent */
		else if (!isMovePresent(riskedMoves.listMoves[i].move,buffer))
		{
			emptyList(&buffer);
			findOccurences(riskedMoves.listMoves[i].move, riskedMoves, &buffer);
			if (buffer.length_list == 1)
				priorityMoves->listMoves[j].caution = buffer.listMoves[0].caution;
			else
				priorityMoves->listMoves[j].caution = globalProbability(buffer);

			/* Rajout de probabilité si on est un scout et qu'on peut bouger en haut */
			
			if ((gameState->board[riskedMoves.listMoves[i].move.end.line][riskedMoves.listMoves[i].move.end.col].content == m_enemyColor)
			&&(gameState->board[riskedMoves.listMoves[i].move.start.line][riskedMoves.listMoves[i].move.start.col].piece == EPscout)
			&&((riskedMoves.listMoves[i].move.end.line - riskedMoves.listMoves[i].move.start.line) > 0))
				priorityMoves->listMoves[j].caution -= 10.f;

			priorityMoves->listMoves[j].move = riskedMoves.listMoves[i].move;
			priorityMoves->length_list++;
			j++;
		}
	}
}

// procedure interne à globalEvaluation
// cherche toutes les occurences d'un mouvement dans la liste de mouvements risqués et remplit le buffer 
void findOccurences(SMove movement,GroupMoves riskedMoves,GroupMoves *buffer)
{
 	int i = 0; /* compteurs */

 	buffer->length_list=0;
 	for(i=0;i < riskedMoves.length_list; i++)
 	{
 		if((riskedMoves.listMoves[i].move.start.line == movement.start.line)
 			&&(riskedMoves.listMoves[i].move.start.col == movement.start.col)
 			&&(riskedMoves.listMoves[i].move.end.line == movement.end.line)
 			&&(riskedMoves.listMoves[i].move.end.col == movement.end.col))
 		{
 			buffer->listMoves[buffer->length_list]=riskedMoves.listMoves[i];
 			buffer->length_list++;
		}
 	}
}

 // procedure interne à globalEvaluation
 // permet de donner le taux de risque global pour un mouvement
float globalProbability(GroupMoves buffer)
{
	int i=0; /* compteurs */
	float sum=1; /* somme des risques pour les mouvements risqué lies au ennemis environants */
	float probability;
	float finalCaution;

	for(i=0;i<buffer.length_list;i++)
	{
		// Probabilité pour la valeur de caution
		probability = (buffer.listMoves[i].caution - 10.f)/(-20.f);
		sum *= probability;
	}

	finalCaution = sum * (-20.f) + 10.f;
	return finalCaution;
}

// procedure interne a globalEvaluation
// permet de savoir si un mouvement est présent dans une liste de mouvement 
bool isMovePresent(SMove mouvement, GroupMoves buffer)
{
	int i; /* compteur */

	for(i=0;i<buffer.length_list;i++)
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
	int i=0; /* compteur*/
	while(i<buffer->length_list)
	{
		buffer->listMoves[i].move.start.line=0;
		buffer->listMoves[i].move.end.line=0;
		buffer->listMoves[i].move.start.col=0;
		buffer->listMoves[i].move.end.col=0;
		buffer->listMoves[i].caution=0;
		i++;
	}
	buffer->length_list = 0;
}

SMove takeBestMove(GroupMoves moves)
{
	SMove bestMove;
	int bestCaution;
	int i;

	// On initialise le meilleur mouvement au tout premier
	bestMove = moves.listMoves[0].move;
	bestCaution = moves.listMoves[0].caution;

	for (i=1; i < moves.length_list; i++)
		if (moves.listMoves[i].caution < bestCaution) // Si on trouve un meilleur mouvement
		{
			bestMove = moves.listMoves[i].move;
			bestCaution = moves.listMoves[i].caution;
		}			

	return bestMove;
}

SMove chooseMove(const SGameState * const gameState, GroupMoves moves)
{	
	// On ressort le meilleur mouvement, celui qui a le score le plus faible
 	return takeBestMove(moves);
}
