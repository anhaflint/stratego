#include "../stratego.h"
#include "ia.h"

typedef Enum{
	offensive=0;
	defensive=0;
	malisious;
}Strategy;

SPos m_ArmyPos;
Strategy m_strategy;

void InitLibrary(char name[50])
{
	printf("InitLibrary\n");
	strcpy(name,"Fabien Picarougne");
}

void StartMatch(const EColor color)
{
	printf("StartMatch\n");
}

void StartGame(EPiece boardInit[4][10]){
	/* Initialisation du tableau de l'IA avec positionement de pions*/
	printf("StartGame\n");
	swich(m_strategy){
		case defensive:{
			/* placement du drapeau */
			boardInit[0][0]=EPflag;
			/* placement des bombes */
			boardInit[1][0]=boardInit[0][1]=boardInit[0][4]=boardInit[1][5]=boardInit[0][6]= EPbomb;
			/* placement des sergants */
			boardInit[2][0]=boardInit[2][6]=boardInit[0][5]=boardInit[0][7]=EPsergeant;
			/* placements des scouts */
			boardInit[1][2]=boardInit[1][3]=boardInit[1][6]=boardInit[1][7]=boardInit[0][3]=EPscout;
			/*placement des espions */
			boardInit[3][0]=boardInit[3][1]=boardInit[3][4]=boardInit[3][5]=boardInit[3][8]=EPspy;
			boardInit[2][5]=boardInit[1][9]=boardInit[0][9]=EPspy;
			/* placement des lieutenants */
			boardInit[3][9]=boardInit[1][4]=boardInit[1][8]=boardInit[0][8]=EPlieutenant;
			/* placement des capitaines */
			boardInit[2][1]=boardInit[2][2]=boardInit[2][4]=boardInit[2][7]=EPcaptain;
			/* placement des majors */
			boardInit[3][2]=boardInit[3][7]=boardInit[1][1]=EPmajor;
			/* placement des colonels */
			boardInit[2][9]=boardInit[0][2]=EPcolonel;
			/* placements du général */
			boardInit[3][3]=EPgeneral;
			/* placement du maréchal */
			boardInit[3][6]=EPmarshal;
		}
	}
}

void EndGame()
{
	printf("EndGame\n");
}

void EndMatch()
{
	printf("EndMatch\n");
}

void NextMove(const SGameState * const gameState, SMove *move)
{
	printf("NextMove\n");
}

void AttackResult(SPos armyPos,EPiece armyPiece,SPos enemyPos,EPiece enemyPiece)
{
	m_armyPos = armyPos;
	printf("AttackResult\n");
}

void void Penalty()
{
	printf("Penalty\n");
}