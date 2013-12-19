#ifndef _STRATEGO_H
	#define _STRATEGO_H

/////////// Strutures à utiliser
// cf structures.h

/////////// Fonctions à utiliser
// Les prototypes en commentaires sont à implémenter dans la librairie
// Les types pointeur de fonction dans l'application

/**
 * Initialiser la librairie
 * @param char name[50]
 *	nom associé à la librairie
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
 * Prise de décision de la part de l'IA
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @return SMove
 *	mouvement à effectuer par l'IA
 */
//SMove NextMove(const SGameState * const gameState);
typedef SMove (*pfNextMove)(const SGameState * const);

/**
 * Indication du résultat d'une attaque (résultat envoyé à tous les joueurs)
 * @param SPos armyPos
 *	position de l'élément de l'armée du joueur (attaquant ou attaquée)
 * @param EPiece armyPiece
 *	type de de l'élément de l'armée du joueur (attaquant ou attaquée)
 * @param SPos enemyPos
 *	position de l'élément de l'ennemi (attaquant ou attaquée)
 * @param EPiece enemyPiece
 *	type de de l'élément de l'ennemi (attaquant ou attaquée)
 */
//void AttackResult(SPos armyPos,EPiece armyPiece,SPos enemyPos,EPiece enemyPiece);
typedef void (*pfAttackResult)(SPos,EPiece,SPos,EPiece);

/**
 * Indication d'une pénalitée pour règle non respectée -> coup précédent annulé
 */
//void Penalty();
typedef void (*pfPenalty)();

#endif
