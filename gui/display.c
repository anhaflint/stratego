#include "../structure.h"
#include "display.h"

//**************************************************************************
//							Fonctions d'affichages
//**************************************************************************


void BoardLayout_Init(BoardLayout* layout){ 

int i,j;


//Init Rectangle découpe Patron Pièces Rouges
for (i=0;i<13;i++){

	if(i==0)
	{	

		layout->PiecesLayout[i].x=11*40;
		layout->PiecesLayout[i].y=0;
		layout->PiecesLayout[i].w=40;			// Taille d'une pièce 40x40
		layout->PiecesLayout[i].h=40;
	}
	else if(i==11)
	{

		layout->PiecesLayout[i].x=12*40;
		layout->PiecesLayout[i].y=0;
		layout->PiecesLayout[i].w=40;			// Taille d'une pièce 40x40
		layout->PiecesLayout[i].h=40;
	}
	else if(i==12)
	{

		layout->PiecesLayout[i].x=0*40;
		layout->PiecesLayout[i].y=0;
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
	{
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

	layout->Patron=SDL_LoadBMP("images/piecestest.bmp");   // Charge image Patron Pièces
	
	layout->J1=SDL_LoadBMP("images/j1.bmp");   // Charge image J1
	layout->J2=SDL_LoadBMP("images/j2.bmp");   // Charge image J2
	
	layout->Background=SDL_LoadBMP("images/venicetest.bmp");   // Charge image de fond

	layout->Placement=SDL_LoadBMP("images/endTuile.bmp");   // Charge image grisée
	SDL_SetAlpha(layout->Placement, SDL_SRCALPHA, 192);

	layout->Penalty=SDL_LoadBMP("images/penality.bmp");


 	layout->Screen=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Setup de la surface de l'ecran : 800x600

 	SDL_WM_SetCaption("Stratego's Creed", "SC"); //Affichage des infos de la fenêtre notamment son nom

 	SDL_BlitSurface(layout->Background, NULL, layout->Screen, NULL); //Affichage du Background en 0,0 sur l'écran 
 	
 	// Rafraichissement
 	SDL_Flip(layout->Screen);


	layout->Fight=NULL; 		// Stocke image affichée lors d'un combat si jamais on en met une

//Init Display TAB	: Tab des cellules du plateau

	for (i=0;i<10;i++){
		for (j=0;j<10;j++){

			layout->DisplayTab[i][j].position.h=40;
			layout->DisplayTab[i][j].position.w=40;
			layout->DisplayTab[i][j].position.x=156+50*j; //Position relative d'une case 
			layout->DisplayTab[i][j].position.y=506-50*i;

			// On part du point (156,56) on parcout les colonnes, puis les lignes en ajoutant 50 px à chaque fois.


			layout->DisplayTab[i][j].cellaff=12;	//Rien n'est encore afficher sur le plateau.
													//toute cellule ne possède aucun remplissage => Background
		}

	}

}

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
			SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[i]), layout.Screen, &rectTuilesAPlacer[i]); //Affichage de chacune des tuiles
				if (nbPiecesRestantes[i]==0)
				{
					SDL_BlitSurface(layout.Placement, NULL, layout.Screen, &rectTuilesAPlacer[i]);
				}
		}

		else if (color==ECblue)
		{
			rectTuilesAPlacer[i].x=710;
			rectTuilesAPlacer[i].y=33+45*i;
			SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[i+13]), layout.Screen, &rectTuilesAPlacer[i]); //Affichage de chacune des tuiles
			if (nbPiecesRestantes[i]==0)
				{
					SDL_BlitSurface(layout.Placement, NULL, layout.Screen, &rectTuilesAPlacer[i]);
				}

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



void Display_PieceInit(EPiece Piece, SPos posPiece, BoardLayout *layout,EColor color){

			if(color==ECred)
			{
				SDL_BlitSurface(layout->Patron, &(layout->PiecesLayout[Piece]), layout->Screen,  &(layout->DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==ECblue)
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




 //fonction de test de retour EPiece
void Display_EPieceTest(EPiece Pieces[4][10]){

	int i,j;

	for (i=0;i<4;i++)
	{
		for (j=0;j<10;j++)
		{
				printf("[%d] ",Pieces[3-i][j] );
				
		}
		printf("\n");
	}

}

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
			{	printf("C 0 P 12 Case [%d|%d] en [%d][%d] \n", player.Pboard[i][j].content,player.Pboard[i][j].piece,i,j);
				// Si la case ne comprend déjà le fond

					printf("ON EFFACE \n" );
					SDL_BlitSurface(layout->Background, &(layout->DisplayTab[i][j].position), layout->Screen, &(layout->DisplayTab[i][j].position));
					layout->DisplayTab[i][j].cellaff=12;
				
				
			}
			else
			{	printf("A Case [%d|%d] en [%d][%d] et cellaff = %d  et color = %d \n", player.Pboard[i][j].content,player.Pboard[i][j].piece,i,j,layout->DisplayTab[i][j].cellaff,player.Color);
				// Si la case ne comprend déjà la bonne pièce
				if  ((player.Pboard[i][j].content!=player.Color)||(layout->DisplayTab[i][j].cellaff!=player.Pboard[i][j].piece))
				{ printf("B \n");
				posPiece.line=i;
				posPiece.col=j;
				Display_PieceInit(player.Pboard[i][j].piece, posPiece, layout ,player.Pboard[i][j].content);
				layout->DisplayTab[i][j].cellaff=player.Pboard[i][j].piece;
				}

			}
		
		}		
	}

	SDL_Flip(layout->Screen); // Rafraichissement
}

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
		SDL_SetColorKey(layout->Penalty, SDL_SRCCOLORKEY, SDL_MapRGB(layout->Penalty->format, 0, 0, 255));
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
void Display_affPlayer(BoardLayout *layout,EPlayer player,int aff)

{
	SDL_Rect rectJ;
	rectJ.w=80;
	rectJ.h=40;

	if (aff==1)
	{
		if(player.Color==2)
		{
			rectJ.x=120;
			rectJ.y=556;
			SDL_SetColorKey(layout->J1, SDL_SRCCOLORKEY, SDL_MapRGB(layout->J1->format, 0, 0, 0));
			SDL_BlitSurface(layout->J1, NULL, layout->Screen, &rectJ);
		}

		if(player.Color==3)
		{
			rectJ.x=800-200; //120-80
			rectJ.y=556;
			SDL_SetColorKey(layout->J2, SDL_SRCCOLORKEY, SDL_MapRGB(layout->J2->format, 0, 0, 0));
			SDL_BlitSurface(layout->J2, NULL, layout->Screen, &rectJ);
		}
		
		SDL_Flip(layout->Screen);
	}
	else
	{

			rectJ.x=120;
			rectJ.y=556;
		SDL_BlitSurface(layout->Background, &rectJ , layout->Screen, &rectJ);

			rectJ.x=800-200; // 120-80
			rectJ.y=556;
		SDL_BlitSurface(layout->Background, &rectJ , layout->Screen, &rectJ);
		SDL_Flip(layout->Screen);
		}
}

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



/*
void Display_killedPieces(BoardLayout *layout,SGameState gamestate)
{

}

	unsigned int redOut[11];	// Tableau de comptage des pièces rouges éliminées (indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10
	unsigned int blueOut[11];	// Tableau de comptage des pièces bleues éliminées (indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10
} SGameState;



void Display_Board(BoardLayout layout, SGameState gamestate){





}
void Display_Fight(SDL_Surface* piece){




}



void Display_CpyBg(BoardLayout *layout, SPos posPiece){
// affichage du background sur une petite partie du plateau

// On récupère les indices de la tuille à changer
int i,j;
i=SPos.line;
j=SPos.col;

// On défini le rectangle de découpe

SDL_Rect rectCut;
rectCut.w=50;
rectCut.h=50;
rectCut.x=layout->DisplayTab[i][j].position.x;
rectCut.y=layout->DisplayTab[i][j].position.y;

// On réinitialise l'affichage de cette tuile

layout->DisplayTab[i][j].cellaff=NULL;

// On affiche la découpe
SDL_BlitSurface(layout->Background, rectCut, layout->Screen, layout->DisplayTab[i][j].position);


}
*/