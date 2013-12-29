#include "display.h"

//**************************************************************************
//							Fonctions d'affichages
//**************************************************************************


void BoardLayout_Init(BoardLayout* layout){ 

for (i=0;i<13;i++){
	layout->PiecesLayout[i].x=i*50;
	layout->PiecesLayout[i].y=0;
	layout->PiecesLayout[i].w=50;		//Init Rectangle découpe Patron Pièces Bleu
	layout->PiecesLayout[i].h=50;
}

for (i=13;i<26;i++){
	layout->PiecesLayout[i].x=i*50;
	layout->PiecesLayout[i].y=50;
	layout->PiecesLayout[i].w=50;		//Init Rectangle découpe Patron Pièces Rouges
	layout->PiecesLayout[i].h=50;
}

	layout->Patron=SDL_LoadBMP("tuiles.bmp");   // Charge image Patron Pièces
	
	layout->Background=SDL_LoadBMP("venice2.bmp");   // Charge image de fond
 	layout->posBackground.x=0;
 	layout->posBackground.y=0;

 	layout->Screen=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Setup de la surface de l'ecran

	layout->Fight=NULL; 		// Stocke image affichée lors d'un combat si jamais on en met une

//Init Display TAB	

	for (i=0;i<13;i++){
		for (j=0;j<13;j++){

		
			layout->DisplayTab[i][j]->position.x=155+50*j; //Position relative d'une case
			layout->DisplayTab[i][j]->position.y=55+50*i;

			layout->DisplayTab[i][j]->cellaff=NULL; // Rien n'est encore afficher sur le plateau
		}

	}

}



void Display_Init(BoardLayout layout){



}
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