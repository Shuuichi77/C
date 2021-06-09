#ifndef LABY_H
#define LABY_H

#include "Case.h"
#include "Coordonnees.h"

/* --------------------------------------------------------- */

	typedef struct laby 
	{
		int cases_non_accessibles;
		case_t **cases; 
	} laby_t ;

/* --------------------------------------------------------- */

	/* Initialise les variables d'une structure 'laby_t' */
	laby_t init_labyrinthe(int hauteur_laby, int largeur_laby);

	/* Libère la place allouée à chaque tableau de case_t dans labyrinthe->cases */
	void free_labyrinthe(laby_t *labyrinthe, int hauteur_laby);

	/* Vérifie la cellule de départ et de fin du labyrinthe "labyrinthe" de dimension "hauter_laby" et "largeur_laby" 
	   ont la même classe, donc qu'il y a un chemin valide dans le labyrinthe */
	int chemin_acceptant(laby_t labyrinthe, int hauteur_laby, int largeur_laby);

	/* Vérifie si le labyrinthe a un chemin acceptant et qu'il est donc fini.
	   Si l'option "--acces" est activée, on continue tant qu'on a encore 1 
	   cellule qui a au moins 1 mur destruisable : ce nombre est régit par "nb_cellules_restantes" */
	int labyrinthe_fini(laby_t labyrinthe, int hauteur_laby, int largeur_laby, int unique, int acces, int nb_cellules_restantes);

/* --------------------------------------------------------- */

#endif