// structures


// Etat d'une case du jeu
typedef enum
{
	ECnone,
	EClake,
	ECred,
	ECblue
} EColor;

typedef enum
{
	EPbomb=0,
	EPspy,
	EPscout,
	EPminer,
	EPsergeant,
	EPlieutenant,
	EPcaptain,
	EPmajor,
	EPcolonel,
	EPgeneral,
	EPmarshal,
	EPflag,
	EPnone,
} EPiece;

typedef struct
{
	EColor content;
	EPiece piece;
} SBox;


// Structure de représentation du jeu avec son plateau
typedef struct
{
	SBox board[10][10];	// Tableau du jeu de 10 cases par 10. dim1=ligne dim2=colonne
	unsigned int redOut[11];	// Tableau de comptage des pièces rouges éliminées (indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10
	unsigned int blueOut[11];	// Tableau de comptage des pièces bleues éliminées (indexées par la valeur de EPiece : EPbomb=0, ..., EPmarshal=10
} SGameState;

// Structure de représentation d'un mouvement
typedef struct
{
	int line;
	int col;
} SPos;

// Structure de représentation d'un mouvement
typedef struct
{
	SPos start;
	SPos end;
} SMove;


typedef struct {
	unsigned int NbPenalty;	// nombre de pénalités du joueur
	const EColor Color;		// couleur du joueur (const pour éviter la triche)
}Player;

typedef enum
{
	IA_IA=0,
	IA_HUMAN,
	HUMAN_HUMAN,
	ERROR,
}SGameMode;

typedef struct 
{
	char Player1Name[16];
	char Player2Name[16];
	SGameMode Mode; 
	const EColor ColorPlayer1;
}SGameConfig;



