
#include "../structure.h"
#include "display.h"
#include "game.h"

//**************************************************************************
//							Fonctions d'affichages
//**************************************************************************

//			=	INITIALISATION DU BOARDLAYOUT : STRUCTURE PRINCIPALE DU DISPLAY	=

void BoardLayout_Init(BoardLayout* layout){ 

int i,j;


//Initialisation des rectangles : "découpe" du Patron pour les Pièces Rouges
for (i=0;i<13;i++){

	if(i==0)
	{	

		layout->PiecesLayout[i].x=11*40;
		layout->PiecesLayout[i].y=0;			// Pour une bombe
		layout->PiecesLayout[i].w=40;			// Taille d'une pièce 40x40
		layout->PiecesLayout[i].h=40;
	}
	else if(i==11)
	{																// 3 CAS PARTICULERS DU A L'ORDRE DES PIECES SUR LE PATRON

		layout->PiecesLayout[i].x=12*40;
		layout->PiecesLayout[i].y=0;			// Pour un drapeau
		layout->PiecesLayout[i].w=40;			// Taille d'une pièce 40x40
		layout->PiecesLayout[i].h=40;
	}
	else if(i==12)
	{

		layout->PiecesLayout[i].x=0*40;
		layout->PiecesLayout[i].y=0;			// Pour une case retournée
		layout->PiecesLayout[i].w=40;			// Taille d'une pièce 40x40
		layout->PiecesLayout[i].h=40;
	}
	else
	{

	layout->PiecesLayout[i].x=i*40;			// On part du point (0,0) du Patron
	layout->PiecesLayout[i].y=0;			// On avance suivant x de 40 px
	layout->PiecesLayout[i].w=40;			// Taille d'une pièce 40x40
	layout->PiecesLayout[i].h=40;
	}
}

//Init Rectangle découpe Patron Pièces Bleues
for (i=13;i<26;i++){


	if(i==13)
	{
		layout->PiecesLayout[i].x=11*40;
		layout->PiecesLayout[i].y=40;
		layout->PiecesLayout[i].w=40;			// Taille d'une pièce 40x40
		layout->PiecesLayout[i].h=40;
	}
	else if(i==24)
	{																// 3 CAS PARTICULERS DU A L'ORDRE DES PIECES SUR LE PATRON
		layout->PiecesLayout[i].x=12*40;
		layout->PiecesLayout[i].y=40;
		layout->PiecesLayout[i].w=40;			// Taille d'une pièce 40x40
		layout->PiecesLayout[i].h=40;
	}
	else if(i==25)
	{
		layout->PiecesLayout[i].x=0*40;
		layout->PiecesLayout[i].y=40;
		layout->PiecesLayout[i].w=40;			// Taille d'une pièce 40x40
		layout->PiecesLayout[i].h=40;
	}
	else
	{
	layout->PiecesLayout[i].x=(i-13)*40;	// On part du point (0,40) du Patron
	layout->PiecesLayout[i].y=40;			// On avance tj suivant x de 40 px
	layout->PiecesLayout[i].w=40;		
	layout->PiecesLayout[i].h=40;
	}
}
// Initialisation des tableaux de rect. (écran de jeu) pour affichage 
// du nombre de pièces éliminées
	for (i=0;i<11;i++){
		layout->RECTredOut[i].x=55;
		layout->RECTredOut[i].y=33+45*i;	

		layout->RECTblueOut[i].x=755;			//(indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10)
		layout->RECTblueOut[i].y=33+45*i;
		layout->RECTblueOut[i].w=30;
		layout->RECTredOut[i].w=30;
		layout->RECTblueOut[i].h=40;
		layout->RECTredOut[i].h=40;

	}

// Initialisation et Chargement des images
		//	-Patron des pièces-	
			layout->Patron=SDL_LoadBMP("gui/images/pieces.bmp");

		//	-Jeton Joueur-		
			layout->J1=SDL_LoadBMP("gui/images/j1.bmp");   // Charge image J1
			SDL_SetColorKey(layout->J1, SDL_SRCCOLORKEY, SDL_MapRGB(layout->J1->format, 0, 0, 0));

			layout->J2=SDL_LoadBMP("gui/images/j2.bmp");   // Charge image J2
			SDL_SetColorKey(layout->J2, SDL_SRCCOLORKEY, SDL_MapRGB(layout->J2->format, 0, 0, 0));

		//	-Fond/Backgound du jeu-	
			layout->Background=SDL_LoadBMP("gui/images/venice.bmp");

		// 	-Image grisée- (pour phases de placement)
			layout->Placement=SDL_LoadBMP("gui/images/endTuile.bmp");
			SDL_SetAlpha(layout->Placement, SDL_SRCALPHA, 192);

		//	-Patron des nombres- (pour pieces éliminées)	
			layout->Killed=SDL_LoadBMP("gui/images/piecekill.bmp");
			SDL_SetColorKey(layout->Killed, SDL_SRCCOLORKEY, SDL_MapRGB(layout->Killed->format, 0, 0, 0));

		//	-Image de pénalité-	
			layout->Penalty=SDL_LoadBMP("gui/images/penality.bmp");
			SDL_SetColorKey(layout->Penalty, SDL_SRCCOLORKEY, SDL_MapRGB(layout->Penalty->format, 0, 0, 255));

			layout->Fight=NULL; 		// Stocke image affichée lors d'un combat (inutilisé pour le moment)

// Initialisation de la fenêtre d'affichage
	 	layout->Screen=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Setup de la surface de l'ecran : 800x600

	 	SDL_WM_SetCaption("Stratego's Creed", "SC"); //Affichage des infos de la fenêtre notamment son nom

	 	SDL_BlitSurface(layout->Background, NULL, layout->Screen, NULL); //Affichage du Background en 0,0 sur l'écran 
	 	
	 	// Rafraichissement
	 	SDL_Flip(layout->Screen);


//Init DisplayTab	: Tableau des cellules du plateau (Représentation spaticiale et graphique du plateau)

	for (i=0;i<10;i++){
		for (j=0;j<10;j++){

			layout->DisplayTab[i][j].position.h=40;
			layout->DisplayTab[i][j].position.w=40;
			layout->DisplayTab[i][j].position.x=156+50*j; //Position relative d'une case 
			layout->DisplayTab[i][j].position.y=506-50*i;

			// On part du point (156,56) on parcout les colonnes, puis les lignes en ajoutant 50 px à chaque fois.


			layout->DisplayTab[i][j].cellaff=12;		//Rien n'est encore afficher sur le plateau.
														//Piece Affichée : NONE 						
			layout->DisplayTab[i][j].cellcol=ECnone;	//Couleur de la pièce : NONE				=> Background
		}

	}

}

//----------------------------------------------------------------------------------------------------------------------

//			=	PHASE DE PLACEMENT : AFFICHACHE LATERAL DES PIECES	=

void Display_Init(BoardLayout layout,EColor color, int nbPiecesRestantes[13]){

SDL_Rect rectTuilesAPlacer[12];
int i;

	for (i=0;i<12;i++){
		rectTuilesAPlacer[i].h=40;
		rectTuilesAPlacer[i].w=40;
		
		if (color==ECred)
		{
			rectTuilesAPlacer[i].x=10;
			rectTuilesAPlacer[i].y=33+45*i;
			SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[i]), layout.Screen, &rectTuilesAPlacer[i]); // Affichage de chacune des tuiles rouges
				if (nbPiecesRestantes[i]==0)
				{
					SDL_BlitSurface(layout.Placement, NULL, layout.Screen, &rectTuilesAPlacer[i]);
				}
		}

		else if (color==ECblue)
		{
			rectTuilesAPlacer[i].x=710;
			rectTuilesAPlacer[i].y=33+45*i;
			SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[i+13]), layout.Screen, &rectTuilesAPlacer[i]); //Affichage de chacune des tuiles bleues
			if (nbPiecesRestantes[i]==0)
				{
					SDL_BlitSurface(layout.Placement, NULL, layout.Screen, &rectTuilesAPlacer[i]);
				}

		}
		else if (color==ECnone){  																				// Remise à vide ( recopie de Background )
			rectTuilesAPlacer[i].x=10;
			rectTuilesAPlacer[i].y=33+45*i;
			SDL_BlitSurface(layout.Background, &rectTuilesAPlacer[i], layout.Screen, &rectTuilesAPlacer[i]);
			rectTuilesAPlacer[i].x=710;
			SDL_BlitSurface(layout.Background, &rectTuilesAPlacer[i], layout.Screen, &rectTuilesAPlacer[i]);

		}
		
	}
 	SDL_Flip(layout.Screen); // Rafraichissement

}

//----------------------------------------------------------------------------------------------------------------------

//			=	AFFICHAGE D'UNE PIECE : AFFICHAGE LOCALISE PAR SPOS & ECOLOR	=

void Display_PieceInit(EPiece Piece, SPos posPiece, BoardLayout *layout,EColor color){

			if(color==ECred) // Rouge
			{
				SDL_BlitSurface(layout->Patron, &(layout->PiecesLayout[Piece]), layout->Screen,  &(layout->DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==ECblue) // Bleu
			{
				SDL_BlitSurface(layout->Patron, &(layout->PiecesLayout[Piece+13]), layout->Screen,  &(layout->DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}
			if(color==ECnone) // Effacement de piece
			{
			SDL_BlitSurface(layout->Background, &(layout->DisplayTab[ posPiece.line ][ posPiece.col ].position), layout->Screen,  &(layout->DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}
			//layout->DisplayTab[posPiece.line][posPiece.col].cellaff=Piece;

SDL_Flip(layout->Screen); // Rafraichissement
}

//----------------------------------------------------------------------------------------------------------------------

//			=	REINITIALISATION DU PLATEAU: EFFACE LES PIECES DU PLATEAU	=

void Display_ReinitDisplayBoard(BoardLayout layout)
{
	int i,j;
	SDL_Rect rectCut;
	rectCut.w=40;
	rectCut.h=40;

	for (i=0;i<10;i++)
	{
		for (j=0;j<10;j++)
		{
				rectCut.x=156+50*j;
				rectCut.y=506-50*i;
				SDL_BlitSurface(layout.Background, &rectCut, layout.Screen, &(layout.DisplayTab[i][j].position));
				
		}
	}
SDL_Flip(layout.Screen); // Rafraichissement
}



//----------------------------------------------------------------------------------------------------------------------

//			=	AFFICHAGE PLATEAU JOUEUR	=


void Display_BoardPlayer(BoardLayout *layout, EPlayer player)

{

	int i,j;
	SPos posPiece;

	for (i=0;i<10;i++)
	{
		for (j=0;j<10;j++)
		{		
				// Cas d'une pièce vide
			if( (player.Pboard[i][j].content==ECnone)&&(player.Pboard[i][j].piece==EPnone) )
			{	
				// Si la case ne comprend déjà le fond

				
					SDL_BlitSurface(layout->Background, &(layout->DisplayTab[i][j].position), layout->Screen, &(layout->DisplayTab[i][j].position));
					layout->DisplayTab[i][j].cellaff=12;
					layout->DisplayTab[i][j].cellcol=ECnone;						
			}
			else
			{	
				// Si la case ne comprend déjà la bonne pièce
				if  ((player.Pboard[i][j].content!=player.Color)||(layout->DisplayTab[i][j].cellaff!=player.Pboard[i][j].piece)||(layout->DisplayTab[i][j].cellcol!=player.Pboard[i][j].content))
				{
				posPiece.line=i;
				posPiece.col=j;
				Display_PieceInit(player.Pboard[i][j].piece, posPiece, layout ,player.Pboard[i][j].content);
				layout->DisplayTab[i][j].cellaff=player.Pboard[i][j].piece;
				layout->DisplayTab[i][j].cellcol=player.Pboard[i][j].content;
				}

			}
		
		}		
	}

	SDL_Flip(layout->Screen); // Rafraichissement
}

//----------------------------------------------------------------------------------------------------------------------

//			=	AFFICHAGE PENALITE	=

void Display_Penalty(BoardLayout *layout,EPlayer player)
{
	
	SDL_Rect rectPenalty;
	rectPenalty.w=40;
	rectPenalty.h=40;

	if ((player.nbPenalty>0)&&(player.nbPenalty<=3))
	{
		if(player.Color==2)
		{
			rectPenalty.x=150+(30*player.nbPenalty);
			rectPenalty.y=554;
		}

		if(player.Color==3)
		{
			rectPenalty.x=800-(190+30*player.nbPenalty);
			rectPenalty.y=554;
		}
		
		SDL_BlitSurface(layout->Penalty, NULL, layout->Screen, &(rectPenalty));
		SDL_Flip(layout->Screen);
	}
	else
	{
		int i;
		for (i = 1; i < 4; i++)
		{
		if(player.Color==2)
		{
			rectPenalty.x=150+30*i;
			rectPenalty.y=554;
		}

		if(player.Color==3)
		{
			rectPenalty.x=800-(190+30*i);
			rectPenalty.y=554;
		}

		SDL_BlitSurface(layout->Background, &(rectPenalty) , layout->Screen, &(rectPenalty));
		SDL_Flip(layout->Screen);
		}

	}

}

//----------------------------------------------------------------------------------------------------------------------

//			=	AFFICHAGE DES JETONS JOUEUR : AFFICHAGE DU TOUR DE CHAQUE JOUEUR	=

void Display_affPlayer(BoardLayout *layout,int joueur)
{
	SDL_Rect rectJ;
	rectJ.w=80;
	rectJ.h=40;


	rectJ.x=260;
	rectJ.y=280;
	SDL_BlitSurface(layout->Background, &rectJ , layout->Screen, &rectJ);

	rectJ.x=800-340; // 120-80
	rectJ.y=280;
	SDL_BlitSurface(layout->Background, &rectJ , layout->Screen, &rectJ);
	
	SDL_Flip(layout->Screen);

			switch(joueur)
			{
				case 1: // joueur 1
						rectJ.x=260;
						rectJ.y=280;
						SDL_BlitSurface(layout->J1, NULL, layout->Screen, &rectJ);
						break;

				case 2: // joueur 2
						rectJ.x=800-340; //120-80
						rectJ.y=280;
						SDL_BlitSurface(layout->J2, NULL, layout->Screen, &rectJ);
						break;

			}
		
		SDL_Flip(layout->Screen);
}


//----------------------------------------------------------------------------------------------------------------------

//			=	AFFICHAGE LATERAL DES PIECES POUR ELIMINATION	=

void Display_lateralPieces(BoardLayout layout,EColor color)
{
	SDL_Rect rectTuilesAPlacer[12];
int i;

	for (i=0;i<12;i++){
		rectTuilesAPlacer[i].h=40;
		rectTuilesAPlacer[i].w=40;
		
		if (color==ECred)
		{
			rectTuilesAPlacer[i].x=10;
			rectTuilesAPlacer[i].y=33+45*i;
			SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[i]), layout.Screen, &rectTuilesAPlacer[i]); //Affichage de chacune des tuiles

		}

		else if (color==ECblue)
		{
			rectTuilesAPlacer[i].x=710;
			rectTuilesAPlacer[i].y=33+45*i;
			SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[i+13]), layout.Screen, &rectTuilesAPlacer[i]); //Affichage de chacune des tuiles


		}
		else if (color==ECnone){  // remise à vide
			rectTuilesAPlacer[i].x=10;
			rectTuilesAPlacer[i].y=33+45*i;
			SDL_BlitSurface(layout.Background, &rectTuilesAPlacer[i], layout.Screen, &rectTuilesAPlacer[i]);
			rectTuilesAPlacer[i].x=710;
			SDL_BlitSurface(layout.Background, &rectTuilesAPlacer[i], layout.Screen, &rectTuilesAPlacer[i]);

		}
		
	}
 	SDL_Flip(layout.Screen); // Rafraichissement
}


//----------------------------------------------------------------------------------------------------------------------

//			=	AFFICHAGE PIECES ELIMINEES	=

void Display_killedPieces(BoardLayout *layout,EPlayer player,SGameState gamestate)
{

SDL_Rect rectKilled;
//RECTredOut[11];	// Tableau rectangle de comptage des pièces rouges éliminées (indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10
//RECTblueOut[11];	// Tableau rectangle de comptage des pièces bleues éliminées (indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10

int i;

	for (i=0;i<11;i++){
		rectKilled.h=40;
		rectKilled.w=30;

		rectKilled.y=0;

		
		if (player.Color==ECred)
		{

		rectKilled.x=0+(gamestate.redOut[i]*30);
		SDL_BlitSurface(layout->Background, &(layout->RECTredOut[i]), layout->Screen, &(layout->RECTredOut[i]));		
		SDL_BlitSurface(layout->Killed, &(rectKilled), layout->Screen, &(layout->RECTredOut[i])); //Affichage 

		}

		else if (player.Color==ECblue)
		{
		rectKilled.x=0+(gamestate.blueOut[i]*30);
		SDL_BlitSurface(layout->Background, &(layout->RECTblueOut[i]), layout->Screen, &(layout->RECTblueOut[i]));	
		SDL_BlitSurface(layout->Killed, &(rectKilled), layout->Screen, &(layout->RECTblueOut[i])); //Affichage
		}
		/*
		else if (color==ECnone){  // remise à vide
			rectTuilesAPlacer[i].x=10;
			rectTuilesAPlacer[i].y=33+45*i;
			SDL_BlitSurface(layout.Background, &rectTuilesAPlacer[i], layout.Screen, &rectTuilesAPlacer[i]);
			rectTuilesAPlacer[i].x=710;
			SDL_BlitSurface(layout.Background, &rectTuilesAPlacer[i], layout.Screen, &rectTuilesAPlacer[i]);


		}
		*/
		
	}
 	SDL_Flip(layout->Screen); // Rafraichissement
}


//----------------------------------------------------------------------------------------------------------------------

//			=	AFFICHAGE D'UN COMBAT : AFFICHAGE DE DEUX TUILES	=

void Display_fight(SMove moveaff,SGameState game, EPlayer *player, BoardLayout *layout)
{
SMove move;
move= Game_TranslateMove(moveaff,*player,1);
	Display_PieceInit(game.board[move.start.line][move.start.col].piece, moveaff.start,layout,game.board[move.start.line][move.start.col].content);
	Display_PieceInit(game.board[move.end.line][move.end.col].piece, moveaff.end,layout,game.board[move.end.line][move.end.col].content);
	SDL_Delay(1500);

}


//----------------------------------------------------------------------------------------------------------------------


//			=	AFFICHAGE D'UN COMBAT : AFFICHAGE DEBUT DE JEU	=
/*
void Display_NewGame(BoardLayout *layout, int ok)
{
	SDL_Rect rectNew;
	rectNew.h=40;
	rectNew.w=300;
	rectNew.x=
	rectNew.y=
	Display_PieceInit(layout->New, NULL ,layout->Screen,&rectNew);
	SDL_Delay(1000);

}
*/
