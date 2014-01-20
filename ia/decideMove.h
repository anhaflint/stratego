#ifndef DECIDEMOVE_H
#define DECIDEMOVE_H

/**
* Renvoie le mouvement à faire qui a été décidé par l'IA
* @param SGameState gameState
* 	l'état du jeu courant
* @return SMove
* 	mouvement à faire, décidé par l'IA
*/
void decideMove(const SGameState * const  gameState);

/**
* calcule la probabilité de risque de la force des pieces ennemies voisines inconnues 
* ou les pieces ennemies inconnues à attaquer directement
* @param riskedMoves est le tableau qui contient tous les movements courants risqués
*/
float riskProbability( const SGameState * const gameState,SPos myPosition,SPos enemyPosition);

/**
* Classe les mouvements possibles en fonction du risque encouru
* @param riskedMoves est le tableau qui contient tous les movements courants risqués
* @param normalMoves est le tableau qui contient tous les movements courants  qui ne sont pas risqués
*/
void evaluateMoves(const SGameState * const gameState,GroupMoves *normalMoves,GroupMoves *riskedMoves);

/**
* Donne l'information sur la pièce ennemie voisine pour évaluer le risque encouru si on effectue le mouvement
* @param myPiece est la pièce qui effectue le mouvement 
* @param enemyPiece est la pièce ennemie voisine à analyser pour donne un grade de risque au mouvement effectuer par myPiece
* @param evaluationType permet de savoir si on evalue la piece ennemie voisine ou si on attaque l'ennemi
*/
float attributionRank(EPiece myPiece,EPiece enemyPiece,bool evaluationType);


/**
* Donne une priorité au mouvements normaux qui echappent à l'attaque de l'ennemi 
* en attribuant un nombre au parametre interne caution de nomalMoves 
* @param normalMoves est le tableau qui contient tous les movements courants  qui ne sont pas risqués
*/
void normalClassication(GroupMoves *normalMoves);

/**
* Donne la priorité au mouvements normaux (sans risque d'être attaqué) en fonction du nombre de pièce énnemie environante 
* @param numEnemy est le nombre de pièces ennemies environantes à echapper
*/
float giveNormalRank(int numEnemy);

/**
* A commenter
*
*/
void globalEvaluation(GroupMoves *priorityMoves, GroupMoves riskedMoves);

/**
* A commenter
*
*/
void findOccurences(SMove movement,GroupMoves riskedMoves,GroupMoves *buffer);

/**
* A commenter
*
*/
float globalProbability(GroupMoves buffer);

/**
* A commenter
*
*/
bool isMovePresent(SMove mouvement, GroupMoves buffer);

/**
* A commenter
*
*/
void emptyList(GroupMoves *buffer);

/**
* A commenter
*
*/
SMove chooseMove(const SGameState * const gameState, GroupMoves moves);

#endif