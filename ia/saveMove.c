// Enregistrement du plateau si déplacement simple
void saveMove()
{
	// On met la nouvelle pièce dans sa nouvelle case
	updateSquare(m_decidedMove.end,
		m_board[m_decidedMove.start.line][m_decidedMove.start.col].box.piece,
		m_color,
		m_board[m_decidedMove.start.line][m_decidedMove.start.col].isVisible,
		m_board[m_decidedMove.start.line][m_decidedMove.start.col].isBomb);

	// Puis on vide la case d'où vient la pièce
	updateSquare(m_decidedMove.start, EPnone, ECnone, false, false);
}

//----------- Fonctions utilisées à l'envoi d'un combat par l'arbitre -----------//

// Fonction interne à AttackResult
void analyseFight(EPiece PieceA, EPiece PieceB, SPos APos, SPos BPos)
{
	EPiece winner;

	if (PieceA != PieceB) // Si les deux pièces sont différentes, on analyse le fight
	{
		// On détermine le gagnant du combat		
		winner = winnerFight(PieceA, PieceB);

		if (winner == PieceA) // Si la pièce A a attaqué et gagné, on remplace la pièce B
		{
			printf("La pièce alliée %d gagne, la pièce ennemie %d perd\n", PieceA, PieceB);
			/* On place la pièce A sur la case où était la pièce B */
			updateSquare(BPos, PieceA, m_board[APos.line][APos.col].box.content, true, false);
		}
		else // Si la pièce A a perdu, on sauvegarde ce qu'est la pièce B
		{	
			printf("La pièce ennemie %d gagne, la pièce ennemie %d perd\n", PieceB, PieceA);
			updateSquare(BPos, PieceB, m_board[BPos.line][BPos.col].box.content, true, (PieceB == EPbomb) ? true : false);
		}		

		/* Dans tous les cas, la case d'où vient la pièce A devient vide */
		updateSquare(APos, EPnone, ECnone, false, false);
	}
	else // Si les deux pièces sont identiques, elles sont éliminées
	{
		printf("Les deux pièces sont identiques, elles sont éliminées\n");
		/* Plus rien dans la case de la pièce A */
		updateSquare(APos, EPnone, ECnone, false, false);

		/* Plus rien dans la case de la pièce B */
		updateSquare(BPos, EPnone, ECnone, false, false);
	}
}

// Fonction interne à AttackResult
EPiece winnerFight(EPiece A, EPiece B)
{	
	/* Si les pièces sont identiques, on
	renvoie EPnone */
	if (A == B)
		return EPnone;
	/* Si la pièce visée est le drapeau,
	la pièce attaquante gagne d'office */
	if (B == EPflag)
		return A;
	/* Si l'attaquant est un espion */
	else if (A == EPspy)
	{
		/* Il gagne seulement si la pièce 
		cible est le maréchal */
		if (B == EPmarshal)
			return A;
		else
			return B;
	}
	/* Sinon si l'attaquant est un démineur */
	else if (A == EPminer)
	{
		/* Il gagne si la pièce attaquée est une 
		bombe, un espion ou un éclaireur */
		if (B < EPminer)
			return A;
		else
			return B;
	}
	/* Sinon, dans tous les autres cas */
	else
	{
		/* Si la pièce attaquée est une bombe ou si sa 
		puissance est supérieure à l'attaquant, elle gagne */
		if ((B == EPbomb) || (B > A))
			return B;
		else
			return A;
	}

}
