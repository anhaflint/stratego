\\\\\\\\\\\\\\\\ EXPLICATIONS DU FONCTION DE L'INTELLIGENCE ARTIFICIELLE ////////////////

\\\\\\\\ I - PLACEMENT DES PIONS ////////

\\\\\\\\ II - CHOIX D'UN MOUVEMENT A EFFECTUER ////////

Notre IA raisonne seulement sur le coup suivant, elle ne fait
pas de raisonnement à long terme comme le permet l'algorithme
Minimax. Nous avons choisi de différencier plusieurs étapes
dans le choix d'un mouvement à effectuer :

- Premièrement, on met à jour les données internes de l'IA avec
les données fournies par l'arbitre (le plateau, les pièces
éliminées, ...). On effectue également des déductions selon les
mouvements effectués et les pièces découvertes depuis le début
de la partie.

- Deuxièmement, on analyse le plateau, et on stocke tous les
mouvements possibles à faire dans un tableau de mouvements SMove :
on filtre tous les mouvements impossibles du genre "bouger à gauche quand
on est sur le bord gauche du plateau", "bouger sur une case où il y a un 
lac ou un allié", "passer par dessus un lac avec un scout", "faire deux 
allers-retours complets entre deux case (règle des 2 cases)", etc...

- Troisièmement, on prend une décision sur le mouvement à effectuer,
en séparant d'abord les mouvements dits "risqués" des "non risqués"
selon certains critères. Les mouvements dit "risqués" sont les mouvements
où l'on attaque un ennemi, et/ou on se déplace sur une case à côté d'un ennemi

Ensuite, en fonction de l'IA choisie et de l'état du jeu, 
la prise de risque est plus ou moins élevée : c'est
ce qui nous permet de savoir quel tableau nous devons utiliser pour
effectuer notre choix. On sélectionne ensuite un mouvement en fonction
de sa chance de réussite dans le cas d'une attaque, d'une nécessité
d'un mouvement de défense ou d'attaque massif, etc...

- Quatrièmement, si le mouvement qu'on a choisi est pacifique, on sauvegarde
le nouveau plateau directement en interne. Dans le cas contraire, on
sauvegardera le plateau au moment où l'arbitre nous donnera les 
détails du combat.

- Enfin, on retourne le mouvement à l'arbitre

\\\\\\\\ III - ENREGISTREMENT DES COMBATS ////////

Dès qu'un combat a lieu, l'arbitre transmet à chaque joueur
les données concernant la position initiale et la force de
chaque pièce participant au combat.

On effectue de notre côté une "simulation" afin de savoir 
qui a gagné, et on met à jour le plateau de jeu interne.
Dans le cas où on aurait déclenché l'attaque et que l'ennemi
gagne, on sauvegarde quelle pièce nous a attaqué.