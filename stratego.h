#ifndef _STRATEGO_H
	#define _STRATEGO_H

/////////// Strutures � utiliser
// cf structures.h

/////////// Fonctions � utiliser
// Les prototypes en commentaires sont � impl�menter dans la librairie
// Les types pointeur de fonction dans l'application

/**
 * Initialiser la librairie
 * @param char name[50]
 *	nom associ� � la librairie
 */
//void InitLibrary(char name[50]);
typedef void (*pfInitLibrary)(char[50]);

/**
 * Initialiser l'IA pour un match
 */
//void StartMatch();
typedef void (*pfStartMatch)();

/**
 * Initialiser l'IA pour une manche (d'un match)
 * @param const EColor color
 *	couleur du joueur
 * @param EPiece boardInit[4][10]
 *	variable en sortie : initialisation du jeu pour un joueur (ligne 0 = ligne la plus proche du joueur)
 */
//void StartGame(const EColor color,EPiece boardInit[4][10]);
typedef void (*pfStartGame)(const EColor,EPiece[4][10]);

/**
 * Fin d'une manche (d'un match)
 */
//void EndGame();
typedef void (*pfEndGame)();

/**
 * Fin d'un match
 */
//void EndMatch();
typedef void (*pfEndMatch)();

/**
 * Prise de d�cision de la part de l'IA
 * @param const SGameState * const gameState
 *	l'�tat du jeu courant
 * @return SMove
 *	mouvement � effectuer par l'IA
 */
//SMove NextMove(const SGameState * const gameState);
typedef SMove (*pfNextMove)(const SGameState * const);

/**
 * Indication du r�sultat d'une attaque (r�sultat envoy� � tous les joueurs)
 * @param SPos armyPos
 *	position de l'�l�ment de l'arm�e du joueur (attaquant ou attaqu�e)
 * @param EPiece armyPiece
 *	type de de l'�l�ment de l'arm�e du joueur (attaquant ou attaqu�e)
 * @param SPos enemyPos
 *	position de l'�l�ment de l'ennemi (attaquant ou attaqu�e)
 * @param EPiece enemyPiece
 *	type de de l'�l�ment de l'ennemi (attaquant ou attaqu�e)
 */
//void AttackResult(SPos armyPos,EPiece armyPiece,SPos enemyPos,EPiece enemyPiece);
typedef void (*pfAttackResult)(SPos,EPiece,SPos,EPiece);

/**
 * Indication d'une p�nalit�e pour r�gle non respect�e -> coup pr�c�dent annul�
 */
//void Penalty();
typedef void (*pfPenalty)();

#endif
