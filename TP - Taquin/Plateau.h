#ifndef PLATEAU_H
#define PLATEAU_H

/* -------------------------------------------------------- */

	#include <MLV/MLV_all.h>

	#define TAILLE_IMAGE 512
	#define TAILLE_INTERFACE 100
	#define COULEUR_MENU MLV_COLOR_WHITE
	#define COULEUR_SOUS_MENU MLV_COLOR_BROWN
	#define TAILLE_SEPARATEUR_IMAGE 8

	typedef struct carre {
		int lig;
		int col;
	} Carre;

	typedef struct plateau {
		int nb_col;					/* On met un champ nb_col et nb_lig dans la structure plutôt qu'en #define, pour ainsi modifier les dimensions du plateau à notre guise */
		int nb_lig;		
		Carre **bloc;				/* Puisqu'on a un nb_col et nb_lig modulable, il faut que le tableau de Carre, qui représente le plateau, ait une taille modulable */
		Carre case_vide;			/* Les coordonnées de la case noire du plateau */
		int coups_joues;			/* Nombre de coups joués par le joueur */
		int time;					/* Temps de la partie du joueur */
	} Plateau;

/* -------------------------------------------------------- */

	/* Fonction initialisant les champs d'une structure Plateau */
	int init_plateau(Plateau *P, int nb_col, int nb_lig);

	/* Réinitialise le plateau à zéro, sans le mélanger 
	   Fonction qui nous sera utile pour recommencer le jeu,
	   pour nous repermettre de mélanger tout le plateau en partant de la base */
	void reinit_plateau(Plateau *P);

	/* Vérifie que la touche directionnelle effectuée est possible 
	   (pour empêcher de sortir du plateau) */
	int touche_valide(Plateau P, MLV_Keyboard_button touche);
 
	/* Renvoie un chiffr entre 1 et 4 selon sur quelle case adjacente à la case vide on a cliqué :
		1 case en haut
		2 case du bas
		3 case à gauche
		4 case à droite
		0 si aucune des cases adjacentes 
	*/
	int clique_valide(Plateau P, int x, int y);

	/* Echange l'emplacement de 2 carrés sur le plateau (un carré rempli et la case vide) 
	   selon la touche directionnelle (variable touche) */
	void swap_case_plateau(Plateau *P, MLV_Keyboard_button touche);

	/* Mélange tout le plateau et stocke l'ordre des mélanges dans le tableau "ordre_melange" */
	void melange_plateau(Plateau *P, MLV_Keyboard_button ordre_melange[], int nb_melange);

	/* Réinitialise le plateau avec le mélange d'origine à l'aide du tableau "ordre_melange" */
	void reset_plateau(Plateau *P, MLV_Keyboard_button ordre_melange[], int nb_melange);

	/* Renvoie 1 si on a bougé une case, 0 sinon */
	int mouvement_touche(Plateau *P, MLV_Keyboard_button touche);

	/* Renvoie 1 si on a bougé une case, 0 sinon */
	int mouvement_souris(Plateau *P, int x, int y);

	/* Renvoie 1 si toutes les cases du plateau sont bien positionnées, 0 sinon */
	int plateau_victoire(Plateau P);

/* -------------------------------------------------------- */


#endif