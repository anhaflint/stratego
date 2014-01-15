#ifndef RISKPROBABILITY_H
#define RISKPROBABILITY_H

/**
* 
*/
float getInfoHidedEnemyGlobal();

/**
* 
*/
float getInfoHidedEnemyMovable(const SGameState * const gameState);

/**
* 
*/
float getInfoHighEnemy (const SGameState * const gameState, EPiece myPiece);

/**
* 
*/
float calculateHighEnemy(float numTotal, EPiece piece, const unsigned int pieceOut[]);

/**
* 
*/
float getInfoLowEnemy(const SGameState * const gameState, EPiece myPiece);

/**
* 
*/
float calculateLowEnemy(float numTotal, EPiece piece, const unsigned int pieceOut[]);

/**
* 
*/
float getInfoHidedEnemyBomb(const SGameState * const gameState);

/**
* 
*/
float isHidedMarshal(const SGameState * const gameState);

#endif