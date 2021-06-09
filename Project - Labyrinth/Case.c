#include <stdio.h>
#include <stdlib.h>
#include "Case.h"

/* --------------------------------------------------------- */

case_t init_case_t(int x, int y, int hauteur_laby, int largeur_laby)
{
	case_t nouvelle_cellule;

	/* mur_a_detruire :
	   0 -> aucun mur à détruire
	   1 -> les 2 murs
	   2 -> murEst
	   3 -> murSud 
    */

	/* La cellule de sortie n'a aucun mur détruisable */
	if (x == hauteur_laby - 1 && y == largeur_laby - 1)
	{
		nouvelle_cellule.mur_a_detruire = 0;
	}

	/* Si on est sur le bord droit du labyrinthe, on ne peut détruire que murSud */
	else if (y == largeur_laby - 1)
	{
		nouvelle_cellule.mur_a_detruire = 3;
	}

	/* Si on est sur le bord en bas du labyrinthe, on ne peut détruire que le murSud */
	else if (x == hauteur_laby - 1)
	{
		nouvelle_cellule.mur_a_detruire = 2;
	}

	/* Sinon, on peut détruire les 2 murs */
	else
	{
		nouvelle_cellule.mur_a_detruire = 1;
	}

	nouvelle_cellule.murEst = 1;
	nouvelle_cellule.murSud = 1;
	nouvelle_cellule.pere.x = x;
	nouvelle_cellule.pere.y = y;
	nouvelle_cellule.rang = 1;

	return nouvelle_cellule;
}

/* --------------------------------------------------------- */
