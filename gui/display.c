#include "../structure.h"
#include "display.h"

//**************************************************************************
//							Fonctions d'affichages
//**************************************************************************


void BoardLayout_Init(BoardLayout* layout){ 

int i,j;


//Init Rectangle découpe Patron Pièces Bleu
for (i=0;i<13;i++){
	layout->PiecesLayout[i].x=i*40;			// On part du point (0,0) du Patron
	layout->PiecesLayout[i].y=0;			// On avance suivant x de 40 px
	layout->PiecesLayout[i].w=40;			// Taille d'une pièce 40x40
	layout->PiecesLayout[i].h=40;
}

//Init Rectangle découpe Patron Pièces Rouges
for (i=13;i<26;i++){
	layout->PiecesLayout[i].x=(i-13)*40;	// On part du point (0,40) du Patron
	layout->PiecesLayout[i].y=40;			// On avance tj suivant x de 40 px
	layout->PiecesLayout[i].w=40;		
	layout->PiecesLayout[i].h=40;
}

	layout->Patron=SDL_LoadBMP("images/piecestest.bmp");   // Charge image Patron Pièces
	
	layout->Background=SDL_LoadBMP("images/venicetest.bmp");   // Charge image de fond


 	layout->Screen=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Setup de la surface de l'ecran : 800x600

 	SDL_WM_SetCaption("Stratego's Creed", "SC"); //Affichage des infos de la fenêtre notamment son nom

 	SDL_BlitSurface(layout->Background, NULL, layout->Screen, NULL); //Affichage du Background en 0,0 sur l'écran
 	
 	// Rafraichissement
 	SDL_Flip(layout->Screen);


	layout->Fight=NULL; 		// Stocke image affichée lors d'un combat si jamais on en met une

//Init Display TAB	: Tab des cellules du plateau

	for (i=0;i<10;i++){
		for (j=0;j<10;j++){

		
			layout->DisplayTab[i][j].position.x=156+50*j; //Position relative d'une case 
			layout->DisplayTab[i][j].position.y=506-50*i;

			// On part du point (156,56) on parcout les colonnes, puis les lignes en ajoutant 50 px à chaque fois.


			layout->DisplayTab[i][j].cellaff=NULL;	//Rien n'est encore afficher sur le plateau.
													//toute cellule ne possède aucun remplissage => Background
		}

	}

}

void Display_Init(BoardLayout layout,int color){

SDL_Rect rectTuilesAPlacer[12];
SDL_Rect rectImageTuilesAPlacer[12];
int i;

	for (i=0;i<12;i++){
		rectTuilesAPlacer[i].h=40;
		rectTuilesAPlacer[i].w=40;
		
		if (color==1)
		{
			rectTuilesAPlacer[i].x=10;
			rectTuilesAPlacer[i].y=33+45*i;
			rectImageTuilesAPlacer[i]=layout.PiecesLayout[1+i];
			SDL_BlitSurface(layout.Patron, &rectImageTuilesAPlacer[i], layout.Screen, &rectTuilesAPlacer[i]); //Affichage de chacune des tuiles
		}
		if (color==2)
		{
			rectTuilesAPlacer[i].x=710;
			rectTuilesAPlacer[i].y=33+45*i;
			rectImageTuilesAPlacer[i]=layout.PiecesLayout[14+i];
			SDL_BlitSurface(layout.Patron, &rectImageTuilesAPlacer[i], layout.Screen, &rectTuilesAPlacer[i]); //Affichage de chacune des tuiles
		}
		if (color==3){  // remise à vide
			rectTuilesAPlacer[i].x=10;
			rectTuilesAPlacer[i].y=33+45*i;
			SDL_BlitSurface(layout.Background, &rectTuilesAPlacer[i], layout.Screen, &rectTuilesAPlacer[i]);
			rectTuilesAPlacer[i].x=710;
			SDL_BlitSurface(layout.Background, &rectTuilesAPlacer[i], layout.Screen, &rectTuilesAPlacer[i]);

		}	
	}
 	SDL_Flip(layout.Screen); // Rafraichissement

}



void Display_PieceInit(EPiece Piece, SPos posPiece, BoardLayout layout,int color){

	switch (Piece)
	{
		case 0: //BOMBE
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[11]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[24]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			break;

		case 11: // FLAG
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[12]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[25]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			break;


		case 1: //SPY
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[1]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[14]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			break;


		case 2: //SCOUT
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[2]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[15]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			break;

		case 3: //...
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[3]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[16]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			break;

		case 4: //...
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[4]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[17]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			break;

		case 5: //...
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[5]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[18]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			break;

		case 6: //...
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[6]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[19]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			break;

		case 7: //...
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[7]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[20]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			break;

		case 8: //...
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[8]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[21]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			break;

		case 9: //...
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[9]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[22]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			break;

		case 10: //...
		
			if(color==1)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[10]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}

			if(color==2)
			{
				SDL_BlitSurface(layout.Patron, &(layout.PiecesLayout[23]), layout.Screen,  &(layout.DisplayTab[ posPiece.line ][ posPiece.col ].position));
			}
			break;

	}	
SDL_Flip(layout.Screen); // Rafraichissement
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

/*
void Display_Board(BoardLayout layout, SGameState gamestate){





}
void Display_Fight(SDL_Surface* piece){




}


void Display_Piece(SGameState gamestate, SPos posPiece, BoardLayout layout){





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