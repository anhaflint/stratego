#include "event.h"
 
void Event_InitGameState(SDL_Event *event, int *continuer,EColor color,BoardLayout* layout, EPiece Pieces[4][10]){
 
EPiece PieceSelectionnee;
SPos PosSelectionnee;
SPos* PosPrecedente=malloc(sizeof(SPos));
PosPrecedente->line =-1;
PosPrecedente->col=-1;    // Mem Vide = Case Invalide
int pieceOK=0;
int posOK=0;
int remise=0;
int i,j;
int nbPiecesRestantes[13];
int echange;
int endPlacement=0;;
int attente=0;
 
// INIT Tableau des Pieces Restant à Placer
nbPiecesRestantes[EPbomb]      =6;
nbPiecesRestantes[EPspy]       =1;
nbPiecesRestantes[EPscout]     =8;
nbPiecesRestantes[EPminer]     =5;
nbPiecesRestantes[EPsergeant]  =4;
nbPiecesRestantes[EPlieutenant]=4;
nbPiecesRestantes[EPcaptain]   =4;
nbPiecesRestantes[EPmajor]     =3;
nbPiecesRestantes[EPcolonel]   =2;
nbPiecesRestantes[EPgeneral]   =1;
nbPiecesRestantes[EPmarshal]   =1;
nbPiecesRestantes[EPflag]      =1;
nbPiecesRestantes[EPnone]      =40;

 
 
// INIT TAB PIECES
 
for (i=0;i<4;i++)
  {
    for (j=0;j<10;j++)
    {
     Pieces[i][j]=EPnone;  
    }
  }
 
 Display_EPieceTest(Pieces);

// Affichage des pièces
 
if(color==ECred){
  Display_Init(*layout,ECred,nbPiecesRestantes); // On affiche les pieces rouges latéralement à gauche
  printf("Début de la phase de placement Rouge \n");
}
if(color==ECblue){
Display_Init(*layout,ECblue,nbPiecesRestantes); // On affiche les pieces bleue latéralement à doite
  printf("Début de la phase de placement Bleu \n");
  }
 
// ------------Debut phase de placement---------------------------------------
 
int placement=40;           // nombre de pièces à placer

 
 
while (endPlacement!=1)
{       // Tant que le placement n'est pas fini
 

  Display_Init(*layout,color,nbPiecesRestantes); // On affiche les pieces rouges latéralement à gauche

  SDL_WaitEvent(event);      // Capture d'un évent(clic)
 
 
  // On analyse le type d'event reçu
  switch(event->type)
   {
        case SDL_QUIT:          // Si l'on quitte la fenêtre, on quitte la boucle, donc le jeu.
            printf("Vous quittez le jeu...\n");
            *continuer=0;
            endPlacement=1;         // Placement fini prématurément
           
            break;
 
        case SDL_MOUSEBUTTONUP: // Si il y a un clic, on récupère les positions x y du pointeur de la souris
           

              Display_Init(*layout,color,nbPiecesRestantes); // On affiche les pieces rouges latéralement à gauche

            //--------------------------------------------------------------------------------------------------
            // ANALYSE PIECES
            //--------------------------------------------------------------------------------------------------
      if(pieceOK==0)   // Si on a pas pris de piece OU que l'on est pas en remise de pièce
       {
//---- ROUGE------
            if(color==ECred){
 
              PieceSelectionnee=Event_IdPiece_Init(event->button.x,event->button.y,ECred);
             
              if ( PieceSelectionnee!=EPnone ){
                    if (nbPiecesRestantes[PieceSelectionnee]!=0)
                    {
                      pieceOK = 1;
               
                      printf("Choisissez une case pour la pièce de valeur [%d] \n",PieceSelectionnee );
                    }
                    else if(remise!=1)// si remise, on ne vérifie pas le choix.
                    {
                      printf("INVALIDE : Ttes les pièces de valeur [%d] sont placées\n",PieceSelectionnee );
                      posOK =0; // Dans le cas où la case est choisie en premier on recommance le mouvement
                      pieceOK =0;
                    }
               
               
              }          
 
            }
 
//---- BLEU------
            if(color==ECblue){
 
             PieceSelectionnee=Event_IdPiece_Init(event->button.x,event->button.y,ECblue);
 
              if (PieceSelectionnee!=EPnone){
                    if (nbPiecesRestantes[PieceSelectionnee]!=0)
                    {
                      pieceOK = 1;
               
                      printf("Choisissez une case pour la pièce de valeur [%d] \n",PieceSelectionnee );
                    }
                    else if(remise!=1) // si remise, on ne vérifie pas le choix.
                    {
                      printf("INVALIDE : Ttes les pièces de valeur [%d] sont placées\n",PieceSelectionnee );
                      posOK =0; // Dans le cas où la case est choisie en premier on recommance le mouvement
                      pieceOK=0;
                    }            
 
              }
 
            }
 
            /* SI LA CASE SELECTIONNEE EST DANS LE BANDEAU ET QU'ON A SELECTIONNE UNE CASE SUR LE PLATEAU AVEC UNE
            PIECE, ON REMET CETTE PIECE DANS LE BANDEAU */
            if ((posOK == 1)&&(((color == ECred)&&(event->button.x < 100))||((color == ECblue)&&(event->button.x > 700))))
            {
              //printf("");
              printf("Remise de la pièce [%d;%d]\n",PosPrecedente->line,PosPrecedente->col);
              nbPiecesRestantes[Pieces[PosPrecedente->line][PosPrecedente->col]]++;
              Pieces[PosPrecedente->line][PosPrecedente->col] = EPnone;
              Display_EPieceTest(Pieces);
              Display_PieceInit(EPnone, *PosPrecedente, layout, ECnone); // argument 3 pour lancer un bkg
 
              pieceOK = 0;
              posOK = 0;
              remise =0;
              placement++;
              PosPrecedente->line = -1;
              PosPrecedente->col = -1;
            }
       }
 
            //-------------------------------------------------------------------------------------------------------
            // ANALYSE POS
            //-------------------------------------------------------------------------------------------------------
 
      PosSelectionnee=Event_IdBoard(event->button.x,event->button.y); // Recupération position sur le plateau
     
      // SI ON A PAS CHOISI DE CASE AU PREALABLE
      if (pieceOK==0)
      {    
            // SI LA CASE EST BIEN DANS LA ZONE DE PLACEMENT DU PLATEAU
            if( ( (PosSelectionnee.line != -1)&&(PosSelectionnee.col != -1) ) && (PosSelectionnee.line < 4) )
            {
                // Si ON A UNE MEMOIRE VIDE
                if (posOK==0)
                {
                     //printf("");
                     // SI LA CASE CLIQUEE EST NON VIDE
                      if (Pieces[PosSelectionnee.line][PosSelectionnee.col]!=EPnone)
                      {
                      posOK=1;
                      remise=1;   // dans le cas d'une remise
                      printf("Choisissez une autre case, ou replacer la pièce [%d,%d] dans le volet\n",PosSelectionnee.line,PosSelectionnee.col );
                      PosPrecedente->line= PosSelectionnee.line;
                      PosPrecedente->col = PosSelectionnee.col;

                    }
                }
 
                // SI ON A UNE MEMOIRE CASE PLEINE - ECHANGE
                else if( (PosPrecedente->line!=-1) && (PosPrecedente->col!=-1) )
                {
                    //printf("");
                    printf("Echange de pièces en [%d,%d] / [%d,%d] \n",PosPrecedente->line,PosPrecedente->col,PosSelectionnee.line,PosSelectionnee.col);
                   
                    // Affichage
                    if (Pieces[PosPrecedente->line][PosPrecedente->col] == EPnone)
                    {
                      Display_PieceInit(EPnone,PosSelectionnee, layout, ECnone); // argument 3 pour lancer un bkg
                    }
                    else
                    {
                      Display_PieceInit(Pieces[PosPrecedente->line][PosPrecedente->col], PosSelectionnee, layout, color);
                    }
                     if (Pieces[PosSelectionnee.line][PosSelectionnee.col] == EPnone)
                    {
                      Display_PieceInit(EPnone, *PosPrecedente, layout, ECnone); // argument 3 pour lancer un bkg
                    }
                  else
                    {
                      Display_PieceInit(Pieces[PosSelectionnee.line][PosSelectionnee.col], *PosPrecedente, layout, color);
                    }

 
                    // Echange
                    echange = Pieces[PosSelectionnee.line][PosSelectionnee.col];
                    Pieces[PosSelectionnee.line][PosSelectionnee.col]=Pieces[PosPrecedente->line][PosPrecedente->col];
                    Pieces[PosPrecedente->line][PosPrecedente->col]=echange;
                    Display_EPieceTest(Pieces);
 
                    PosPrecedente->line=-1 ; // réinit mémoire
                    PosPrecedente->col=-1;
 
                    posOK=0; // Réinit Choix de case
 
                   
                }
            }            
        }
       
      // SI ON A CHOISI UNE CASE AU PREALABLE
     if ( (pieceOK==1) && ( (PosSelectionnee.line != -1)&&(PosSelectionnee.col != -1) && (PosSelectionnee.line < 4) ) )
        {
          // SI LA MEMOIRE CASE EST VIDE
          if (posOK==0)
          {      //printf("");          
                // SI LA CASE CLIQUEE EST VIDE
              if (Pieces[PosSelectionnee.line][PosSelectionnee.col]==EPnone)
              {
                //printf("");
              posOK=1;  
              }
                // ECHANGE CASE MEMOIRE AVEC PIECE PLUS REMISE !
              else
              {
                    printf("Modif. pièce en [%d,%d] \n",PosSelectionnee.line,PosSelectionnee.col);
                   
                    nbPiecesRestantes[Pieces[PosSelectionnee.line][PosSelectionnee.col]]++;
                    Pieces[PosSelectionnee.line][PosSelectionnee.col]=PieceSelectionnee;
 
                    nbPiecesRestantes[Pieces[PosSelectionnee.line][PosSelectionnee.col]]--;
 
                    // Affichage
                    Display_PieceInit(Pieces[PosSelectionnee.line][PosSelectionnee.col], PosSelectionnee, layout, color);
                    Display_EPieceTest(Pieces);
                    PosPrecedente->line=-1;
                    PosPrecedente->col=-1;
                    pieceOK=0;
                    posOK=0; // Réinit Choix de case
 
              }
          }
        }    
 
            //----------------
            // AJOUT DANS TABLEAU EPiece Pieces
            //----------------
 
       if ((posOK==1) && (pieceOK==1))
      {
            Pieces[PosSelectionnee.line][PosSelectionnee.col]=PieceSelectionnee;
            Display_EPieceTest(Pieces);
 
            nbPiecesRestantes[PieceSelectionnee]--;
           
            posOK=0;
            pieceOK=0;
            PosPrecedente->line =-1;
            PosPrecedente->col=-1;
           
            placement--;
           
            printf("Ajout de la pièce %d en [%d][%d] | Nb de placement : %d \n\n\n", PieceSelectionnee,PosSelectionnee.line,PosSelectionnee.col,placement);
            Display_PieceInit(PieceSelectionnee, PosSelectionnee, layout, color);
      }
 
  //printf("pieceOK : %d , posOK : %d \n",pieceOK,posOK );
           break; // Fin de l'analyse du clic
      

      case SDL_KEYDOWN:
          if (placement==0)           // Condition d'arrêt du placement
          {
            endPlacement=1;
          }
          break;

   }
  if ( (placement==0)&&(attente==0) )
  {
  printf("Votre placement est terminé, appuyer sur une touche pour continuer.\n");
  attente=1;
  }

}// fin while

Display_Init(*layout,ECnone,nbPiecesRestantes); // On efface l'affichage des tuiles car Placement terminé
Display_ReinitDisplayBoard(*layout);
free(PosPrecedente);
 
}//fin fonction
 
 
 
 
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 
 
 
 
 
 
 
EPiece Event_IdPiece_Init(int x,int y,EColor color){
 
int noPiece;
 
// TRAITEMENT SUR X
 
  if (color==ECred){                 // Si c'est un placement rouge
 
    if ( (x<10)||(x>50)) {          // Le clic n'est pas centrée sur les pièces en X C [10:50]
 
      return EPnone;  
      }       // La coordonnée X ne correspont à aucune pièce.
  }
 
  if (color==ECblue){               // Si c'est un placement bleu
   
    if ( (x<710)||(x>750)) {        // Le clic est centrée sur les pièces en X C [710:750]
 
      return EPnone;          // La coordonnée X ne correspont à aucune pièce.
 
    }
  }
 
// TRAITEMENT SUR Y
 
  for (noPiece=0;noPiece<12;noPiece++){
     
    if (   ( y>=33+noPiece*(5+40) )    &&   ( y<=73+noPiece*(5+40) )     ) {
                                          // La première case est en y C [33:73] auquel on ajoute 60 pour passer
                                          // d'une pièce à l'autre, 5 pour l'écart entre les pièces et 40 pour
                                          // la taille de la pièce
 
    break;
    }
 
  }
    return noPiece;
}
 
 
 
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 
 
 
 
SPos Event_IdBoard(int x,int y){
 
  int i,j;
  SPos posBoard;
 
  // TRAITEMENT SUR Y - lignes
 
  for (i=0;i<10;i++){
       
      if (   ( y>=501-50*i )    &&   ( y<=549-50*i )     ) {
                                          // La première case est en y C [156:196] auquel on ajoute 50px pour passer
                                          // d'une pièce à l'autre
 
       break;
      }
     
    }
 
      // CAS Y correspont à aucune lignes
      if (i==10){
 
        posBoard.line=-1;
        posBoard.col=-1;
        return posBoard;
      }
 
  // TRAITEMENT SUR X - colonnes
 
    for (j=0;j<10;j++){
     
      if (   ( x>=151+50*j )    &&   ( x<=199+50*j )     ) {
                                          // La première case est en y C [156:196] auquel on ajoute 50px pour passer
                                          // d'une pièce à l'autre
 
        break;
      }
    }
 
          // CAS Y correspont à aucune lignes
      if (j==10){
 
        posBoard.line=-1;
        posBoard.col=-1;
        return posBoard;
      }
 
  // INSERTION ET RENVOI DU SPOS VALIDE
 
    posBoard.line=i;
    posBoard.col=j;
    return posBoard;
 
}
 



SMove Event_IdMove(SDL_Event *event, EPlayer player,int *continuer)
{
  SMove Move;
  int moveStart;
  int moveOK;
  moveStart=0;
  moveOK=0;
 while(moveStart!=1) 
{
    SDL_WaitEvent(event);      // Capture d'un évent(clic)
      switch(event->type)
   {
        case SDL_QUIT:          // Si l'on quitte la fenêtre, on quitte la boucle, donc le jeu.
            printf("Vous quittez le jeu...\n");
            *continuer=0;
            Move.start.line=-1;
            Move.start.col=-1;
            break;
 
        case SDL_MOUSEBUTTONUP:

            Move.start=Event_IdBoard(event->button.x,event->button.y);
            if (player.Pboard[Move.start.line][Move.start.col].content==player.Color) moveStart=1;

        break;
    }
    
}
while(moveOK!=1)
{
  SDL_WaitEvent(event);      // Capture d'un évent(clic)
      switch(event->type)
   {
        case SDL_QUIT:          // Si l'on quitte la fenêtre, on quitte la boucle, donc le jeu.
            printf("Vous quittez le jeu...\n");
            *continuer=0;
            Move.end.line=-1;
            Move.end.col=-1;
            break;
 
        case SDL_MOUSEBUTTONUP:
            Move.end=Event_IdBoard(event->button.x,event->button.y);
            moveOK=1;
        break;
    }
}

    return Move;
}

 
 
/*
SMove Event_Boardclick(SGameState gamestate){
 
  SDL_Event event;
  int continuer=0;
 
while(continuer=0)) {
{
     SDL_WaitEvent(&test_event);
 
     switch(event.type)
   {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONUP:
            printfpositionZozor.x = event.button.x;
            positionZozor.y = event.button.y;
           break;
   }
 
}
 
 
 
 
 
 
if (posOK==0)
      {
            PosSelectionnee=Event_IdBoard(event->button.x,event->button.y); // Recupération position sur le plateau
 
           
            // SI LA CASE EST BIEN DANS LA ZONE DE PLACEMENR DU PLATEAU
            if( ( (PosSelectionnee.line != -1)&&(PosSelectionnee.col != -1) ) && (PosSelectionnee.line < 4) )
            {
 
              // SI LA CASE CLIQUEE EST VIDE
              if (Pieces[PosSelectionnee.line][PosSelectionnee.col]==EPnone)
              {
                posOK=1;
                printf("Choisissez une autre case, ou une pièce pour la case [%d,%d] \n\n",PosSelectionnee.line,PosSelectionnee.col );
                PosPrecedente=PosSelectionnee;
              }
              // SI LA CASE CLIQUEE EST PLEINE
              else
              {  
                  // SI ON A PAS CHOISI DE PIECE ET QUE L'ON A PRIS UNE DEUXIEME AUTRE CASE : Inversion de cases
                  if ( (posOK ==1) && (pieceOK==0) && (PosSelectionnee!=PosPrecedente))
                  {
                    printf("Echange de pièces en [%d,%d] / [%d,%d] \n",PosPrecedente.line,PosPrecedente.col,PosSelectionnee.line,PosSelectionnee.col);
                   
                    // Affichage
 
                    Display_PieceInit(Pieces[PosSelectionnee.line][PosSelectionnee.col], PosPrecedente, layout, color);
                    Display_PieceInit(Pieces[PosPrecedente.line][PosPrecedente.col], PosSelectionnee, layout, color);
 
                    // Echange
                    echange = Pieces[PosSelectionnee.line][PosSelectionnee.col];
                    Pieces[PosSelectionnee.line][PosSelectionnee.col]=Pieces[PosPrecedente.line][PosPrecedente.col];
                    Pieces[PosPrecedente.line][PosPrecedente.col]=echange;
 
                    posOK=0; // Réinit Choix de case
                  }
                 
                  // SI ON A CHOISI UNE CASE ET QUE ON AVAIT DEJA UNE PIECE : On replace la case du plateau pour celle choisie
                  if ( (pieceOK==1) && (PosSelectionnee!=PosPrecedente))
                  {
                    Pieces[PosSelectionnee.line][PosSelectionnee.col]
                    pieceOK=0;
                    printf("Case déjà attribuée\n");
                  }
               
              }
 
            }
      }
*/