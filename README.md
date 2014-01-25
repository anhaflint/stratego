
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

-- Partie Interface --
Des bugs d'interface restent présents.

== Explications pour le code de l'interface ==

Le déroulement d'une partie est décomposé en différentes parties.
Le programme parcourt ces différentes parties via les modules suivants :

Rôle des fichiers :

- structure.h  : Définition des structures et énumérations utilisées (générales à tous les modules)
- main.c       : Entrée du programme
- initlib.c    : Gestion de l'importation des fonctions de l'IA
- display.c    : Affichage et gestion du plateau, pièces, ...
- game.c       : Fonctions liées à la vérification des mouvements et à l'arbitrage + IA
- event.c      : Gestion des évènements du menu, du plateau de pièces.


--Partie IA--