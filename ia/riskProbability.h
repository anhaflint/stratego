#ifndef RISKPROBABILITY_H
#define RISKPROBABILITY_H

/**
* 
*/
int getInfoHidedEnemyGlobal();

/**
* 
*/
int getInfoHidedEnemyMovable(const SGameState * const gameState);

/**
* 
*/
int getInfoHighEnemy (const SGameState * const gameState, EPiece myPiece);

/**
* 
*/
int calculateHighEnemy(int numTotal, EPiece piece, const unsigned int pieceOut[]);

/**
* 
*/
int getInfoLowEnemy(const SGameState * const gameState, EPiece myPiece);

/**
* 
*/
int calculateLowEnemy(int numTotal, EPiece piece, const unsigned int pieceOut[]);

/**
* 
*/
int getInfoHidedEnemyBomb(const SGameState * const gameState);

/**
* 
*/
int isHidedMarshal(const SGameState * const gameState);

#endif
