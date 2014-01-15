#ifndef UPDATEDATA_H
#define UPDATEDATA_H

/**
* Mise à jour d'une case dans notre InfoPiece m_board, utilisé dans plusieurs fonctions
* @param SPos position
*   Position de la case à mettre à jour
* @param EPiece piece
*   Piece à placer dans la case à mettre à jour
* @param EColor color
*   Couleur à placer dans la case à mettre à jour
* @param bool isVisible
*   Visibilité de la pièce dans la case à mettre à jour
* @param bool isBomb
*   Permet de savoir si la pièce 'piece' est potentiellement une bombe
*/
void updateSquare(SPos position, EPiece piece, EColor color, bool isVisible, bool isBomb);

/**
* Déductions et spéculations grâce au board interne, puis mise à jour de celui-ci
* @param const SGameState * const gameState
* 	l'état du jeu courant
* @param SMove enemyMovement
* 	Mouvement effectué par l'ennemi ce tour-ci
*/ 
void updateBoard(const SGameState * const gameState, SMove enemyMovement);

/**
* Met à jour les données internes avec les nouvelles données fournies par l'arbitre
* @param const SGameState * const gameState
*        l'état du jeu courant
*/
void updateData(const SGameState * const gameState);

#endif