
Stratego's Creed

=================

 Projet de C - Programmation d'un jeu
     Polytech Nantes 2013-2014

Groupe :


--GUI/Moteur de jeu--

- BELLIER Maxime
- REMY Claire

		--IA--


- NONO Ariel
- PORCHET Valentin

************************************************

== Compilation ==

Dans une console, saisir :
- "make"   pour compiler l'interface et l'IA
- "make game"   pour compiler l'interface
- "make lib"    pour compiler l'IA
- "make clean" pour effacer l'interface et l'IA

== Exécution ==

Dans une console, saisir :
- "./stratego nbMax 1 libIA.so" pour jouer contre l'IA contenue dans libIA.so avec nbMax coups chacun
- "./stratego nbMax 2 libIA1.so libIA2.so" pour initier un match entre deux IA (libIA1.so et libIA2.so)

-- Partie Interface --

Rq : par manque de temps, une optimisation de l'implémentation des gamestates joueurs n'a pas été faite. Nous pensions au départ 
qu'il serait plus simple d'avoir des gamestates différemment orientés en fonction du joueur, ce qui n'est pas le cas.
Si nous avions plus de temps, nous supprimerions les gamestates personnels des joueurs en ne gardant qu'un seul gamestate: le gamestate général  afin de changer son sens par recopie lors de l'appel de la fonction nextMove du joueur.

== Explications pour le code de l'interface ==

Le déroulement d'une partie est décomposé en différentes parties.
Le programme parcourt ces différentes parties via les modules suivants :

Rôle des fichiers :

- structure.h  : Définition des structures et énumérations utilisées (générales à tous les modules)
- main.c       : Entrée du programme
- initlib.c    : Gestion de l'importation des fonctions de l'IA
- display.c    : Affichage et gestion du plateau, pièces, ...
- game.c       : Fonctions liées à la vérification des mouvements et à l'arbitrage
- event.c      : Gestion des évènements du menu, du plateau de pièces.


-- Partie IA --

== Explications pour le code de l'IA ==

-= Placement des pions =-

-= Choix d'un mouvement à effectuer =-

Notre IA raisonne seulement sur le coup suivant, elle ne fait
pas de raisonnement à long terme comme le permet l'algorithme
Minimax. Nous avons choisi de différencier plusieurs étapes
dans le choix d'un mouvement à effectuer.

	Premièrement, on met à jour les données internes de l'IA avec
les données fournies par l'arbitre (le plateau, les pièces
éliminées, ...). On effectue également des déductions selon les
mouvements effectués et les pièces découvertes depuis le début
de la partie.

	Deuxièmement, on analyse le plateau, et on stocke tous les
mouvements possibles à faire dans un tableau de mouvements SMove :
on filtre tous les mouvements impossibles du genre "bouger à gauche quand
on est sur le bord gauche du plateau", "bouger sur une case où il y a un 
lac ou un allié", "passer par dessus un lac avec un scout", "faire deux 
allers-retours complets entre deux case (règle des 2 cases)", etc...

	Troisièmement, on prend une décision sur le mouvement à effectuer,
en séparant d'abord les mouvements dits "risqués" des "non risqués"
selon certains critères. Les mouvements dit "risqués" sont les mouvements
où l'on attaque un ennemi, et/ou on se déplace sur une case à côté d'un ennemi
	Tout d'abord, on classifie les mouvements risqués en fonction
de la force des pièces qui sont à côté de la position d'arrivée de chaque mouvement,
avec des calculs de probabilités dans le cas de pièces inconnues.
	Ensuite, on classifie les mouvements normaux en privilégiant les fuites
(si un ennemi est à côté d'une de nos pièces), ainsi que les pièces qui sont plus fortes
que la majorité des pièces ennemies, et celles qui ont déjà bougé pour miniser le
nombre de pièces différentes qui bougent.
	Enfin, en fonction de l'avancement du jeu, on choisit un tableau à utiliser
pour effectuer notre choix : on calcule l'espérance de la force des pièces pour
les deux camps (en omettant les bombes et les drapeaux). Si on a une espérance
inférieure à l'ennemi, on fait un mouvement pas risqué, dans le cas contraire on
prend des risques. On prend le mouvement du tableau choisi le moins risqué.

	Quatrièmement, si le mouvement qu'on a choisi est pacifique, on sauvegarde
le nouveau plateau directement en interne. Dans le cas contraire, on
sauvegardera le plateau au moment où l'arbitre nous donnera les 
détails du combat.
	Enfin, on retourne le mouvement à l'arbitre

-= Enregistrement des combats =-

	Dès qu'un combat a lieu, l'arbitre transmet à chaque joueur
les données concernant la position initiale et la force de
chaque pièce participant au combat.

	On effectue de notre côté une "simulation" afin de savoir 
qui a gagné, et on met à jour le plateau de jeu interne.
Dans le cas où on aurait déclenché l'attaque et que l'ennemi
gagne, on sauvegarde quelle pièce nous a attaqué.
