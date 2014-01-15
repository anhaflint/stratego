/**
* Enregistre le plateau si on a fait un déplacement simple
* @param SGameState gameState
* 	l'état du jeu courant
*/
void saveMove();

//----------- Fonctions utilisées à l'envoi d'un combat par l'arbitre -----------//

/**
* Calcule et fais les remplacements sur le plateau selon le 
* résultat de Piece A qui attaque Piece B
* @param EPiece PieceA
*	Pièce attaquante
* @param EPiece Piece B
*   Pièce attaquée
* @param SPos APos
*	Position de la pièce qui attaque
* @param Spos BPos
* 	Position de la pièce attaquée
*/
void analyseFight(EPiece PieceA, EPiece PieceB, SPos APos, SPos BPos);

/**
*  Renvoie le gagnant du combat dans lequel la pièce A attaque la pièce B (A != B)
* @param EPiece A
*  Pièce attaquante
* @param EPiece B
*  Pièce attaquée
* @return EPiece
*  Pièce gagnante du combat
*/
EPiece winnerFight(EPiece A, EPiece B);
