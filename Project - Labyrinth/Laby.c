#include <stdio.h>
#include <stdlib.h>
#include "Laby.h"
#include "Cellule_Valide.h"

/* --------------------------------------------------------- */

laby_t init_labyrinthe(int hauteur_laby, int largeur_laby)
{
	int i, j;

	laby_t labyrinthe;

	labyrinthe.cases_non_accessibles = hauteur_laby * largeur_laby - 1;

	/* On alloue un tableau de tableaux de case_t (hauteur_laby tableaux)*/ 
	labyrinthe.cases = malloc(hauteur_laby * sizeof(case_t*));

	if (labyrinthe.cases == NULL)
	{
		fprintf(stderr, "Erreur : Problème d'allocation dynamique lors de l'initialisation de labyrinthe.cases\n");
		exit(EXIT_FAILURE);
	}

	/* Dans chaque tableau, on alloue de la place pour largeur_laby case_t, et on les initialise */
	for (i = 0 ; i < hauteur_laby ; i++)
	{	
		labyrinthe.cases[i] = malloc(largeur_laby * sizeof(case_t));

		if (labyrinthe.cases[i] == NULL)
		{
			fprintf(stderr, "Erreur : Problème d'allocation dynamique lors de l'initialisation de labyrinthe.cases\n");
			exit(EXIT_FAILURE);
		}

		for (j = 0 ; j < largeur_laby ; j++)
		{
			labyrinthe.cases[i][j] = init_case_t(i, j, hauteur_laby, largeur_laby);
		}
	}

	return labyrinthe;
}

/* --------------------------------------------------------- */

void free_labyrinthe(laby_t *labyrinthe, int hauteur_laby)
{
	int i;

	for (i = 0 ; i < hauteur_laby ; i++)
	{
		free(labyrinthe->cases[i]);
	}

	free(labyrinthe->cases);
}

/* --------------------------------------------------------- */

int chemin_acceptant(laby_t labyrinthe, int hauteur_laby, int largeur_laby)
{
	return meme_classe(labyrinthe.cases, 0, 0, hauteur_laby - 1, largeur_laby - 1);
}
/* --------------------------------------------------------- */

int labyrinthe_fini(laby_t labyrinthe, int hauteur_laby, int largeur_laby, int unique, int acces, int nb_cellules_restantes)
{
	if (acces && unique)
	{
		return nb_cellules_restantes == 0;
	}

	else if (acces && !unique)
	{
		return labyrinthe.cases_non_accessibles == 0;
	}

	else
	{
		return chemin_acceptant(labyrinthe, hauteur_laby, largeur_laby);
	}
}

/* --------------------------------------------------------- */


