



typedef struct
{
SDL_Rect     position;
SDL_Surface     cellaff;  		//Position relative d'une case ainsi que sa surface "image" associé NULL => Backgroung
								//																	tuileA ou tuileT
								// Cette stucture est utile pour connaître la position de chaque des cases ainsi que l'image qui la remplit
}Cell;


typedef struct _BoardLayout
{
	SDL_Rect PiecesLayout[26];
	SDL_Surface *Background;    //image de fond
	SDL_Surface *Screen;		//surface de l'ecran
	SDL_Surface *Fight; 		//image affichee lors d'un combat si jamais on en met une
	Cell DisplayTab[10][10];//tableau contenant les positions des pions à afficher
}BoardLayout;


/* fonction d'initialisation de la structure contenant toutes les images à utiliser
 * @param BoardLayout layout
 * 			images du jeu
 * 			à passer par adresse &layout
 *			fonction dans laquelle on loadera tous les BMP dans la structure
 */
void BoardLayout_Init(BoardLayout layout);

/*
 * @param SDL_Surface* window 
 *		surface sur laquelle on va blitter les éléments dans la fonction
 */
void Display_Init(BoardLayout layout); 	
										// Affichage du départ : image de fond, tuiles sur les cotes
									 	// Il y aura un affichage de tableaux de pieces du jeu à gauche pour permettre au joueur de placer 
										// ses pieces : il n'y a pas besoin de creer de tableaux en mémoire je crois.
										// on ne peut pas utiliser les tab redOut et blueOut pour le début car il faudrait pouvoir tester
										// a quel stade du jeu on est (init ou pas) sinon le joueur peut reprendre ses pions après qu'ils
										// aient été éliminés ! il faut donc deux fonctions
/* fonction d'affichage du plateau pendant le jeu
 * @param SDL_Surface* window 
 *		surface sur laquelle on va blitter les éléments dans la fonction
 * @param SGameState gamestate
 * 		état du jeu à afficher
 */
void Display_Board(BoardLayout layout, SGameState gamestate);

void Display_Fight(SDL_Surface* piece);
/**
 * @param EPiece pice 
 *		piece à afficher
 */
void Display_Piece(EPiece piece); // affichage d'une piece
void Display_CpyBg(); // affichage du background sur une petite partie du plateau
