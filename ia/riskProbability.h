#ifndef RISKPROBABILITY_H
#define RISKPROBABILITY_H

/**
* Permet d'avoir le nombre de piece ennemie cachée 
*/
int getInfoHidedEnemyGlobal();

/**
* Permet d'avoir nombre de pièce ennemie cachée qui peuvent bouger
*/
int getInfoHidedEnemyMovable(const SGameState * const gameState);

/**
* Permet d'avoir nombre de piece ennemie de rang superieur à une piece de l'IA de plus haut rang cachée 
* @param myPiece est la pièce de l'IA de reference pour laquelle on determine le nombre de piece de rang superieur
*/
int getInfoHighEnemy (const SGameState * const gameState, EPiece myPiece);

/**
* calcule le nombre de piece de rang superieur à une piece
* @param piece est la pièce  de reference pour laquelle on determine le nombre de piece de rang superieur
* @param pieceOut est le tableau contenant les pieces eliminés de l'ennemi
* @param numTotal est de piece de rang superieur à une piece
*/
int calculateHighEnemy(int numTotal, EPiece piece, const unsigned int pieceOut[]);

/**
* Permet d'avoir nombre de piece ennemie de rang inférieur à ma piece de plus haut rang cachée
* @param myPiece est la pièce de l'IA de reference pour laquelle on determine le nombre de piece de rang inférieur
*/
int getInfoLowEnemy(const SGameState * const gameState, EPiece myPiece);

/**
* calcule le nombre de piece de rang inferieur à une piece
* @param piece est la pièce  de reference pour laquelle on determine le nombre de piece de rang inférieur
* @param pieceOut est le tableau contenant les pieces eliminés de l'ennemi
*/
int calculateLowEnemy(int numTotal, EPiece piece, const unsigned int pieceOut[]);

/**
* Permet d'avoir nombre de bombes ennemies cachées 
*/
int getInfoHidedEnemyBomb(const SGameState * const gameState);

/**
* Permet de savoir si le marshal ennemi est en vie et caché =1 sinon =0 
*/
int isHidedMarshal(const SGameState * const gameState);

#endif
