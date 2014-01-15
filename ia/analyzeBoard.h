/**
* Analyse des mouvements possibles sur le plateau par l'IA, stockage en interne
*/
void analyzeBoard();

/**
* Analyse le mouvement de (i,j) à (new_i, new_j), vérifiant si c'est en ligne
* @param unsigned int i
*   Ligne sur laquelle est la pièce dont le mouvement est à analyser
* @param unsigned int j
*   Colonne sur laquelle est la pièce dont le mouvement est à analyser
* @param int new_i
*   Ligne sur laquelle est la case sur laquelle on veut tester le mouvement
* @param int new_j
*   Colonne sur laquelle est la case sur laquelle on veut tester le mouvement
* @param int is_i
*   Vaut 1 si le déplacement à analyser est vertical, 0 sinon
* @param int lim
*   Limite de déplacement sur le plateau dans la direction du mouvement (0 ou 9)
* @param unsigned int* compteur
*   Compteur du nombre de mouvements possibles au total
*/
void addAnalyzedMove(unsigned int i, unsigned int j, int new_i, int new_j, int is_i, int lim, unsigned int* compteur);
