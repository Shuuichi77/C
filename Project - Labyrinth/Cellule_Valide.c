#include <stdio.h>
#include <stdlib.h>
#include "Cellule_Valide.h"
#include "Fusion.h"

/* --------------------------------------------------------- */

int meme_classe(case_t **cases, int x1, int y1, int x2, int y2)
{
	coordonnees_t cellule_depart = Trouve(cases, x1, y1), cellule_fin = Trouve(cases, x2, y2);
	
	return (cellule_depart.x == cellule_fin.x && cellule_depart.y == cellule_fin.y);
}

/* --------------------------------------------------------- */

void verif_voisins_classe(case_t **cases, int x, int y)
{
	/* Si on peut détruire n'importe quel mur */
	if (cases[x][y].mur_a_detruire == 1)
	{
		/* Si cependant la cellule est dans la même classe que sa cellule Est et Sud, 
		   on ne pourra plus jamais détruire de mur, on change mur_a_detruire */
		if (meme_classe(cases, x, y, x + 1, y) && meme_classe(cases, x, y, x, y + 1))
		{
			cases[x][y].mur_a_detruire = 0;
		}

		/* S'il est seulement dans la même classe que sa cellule au Sud, mur_a_detruire = 2 
		   car on peut détruire que le murEst */
		else if (meme_classe(cases, x, y, x + 1, y))
		{
			cases[x][y].mur_a_detruire = 2;
		}

		/* Et s'il est seulement dans la même classe que sa cellule à l'Est, on peut détruire
	       que murSud */
		else if (meme_classe(cases, x, y, x, y + 1))
		{
			cases[x][y].mur_a_detruire = 3;
		}
	}

	/* Si on peut détruire que murEst */
	if (cases[x][y].mur_a_detruire == 2)
	{
		/* Mais si il est dans la même classe que la cellule à l'est,
		   on ne peut plus détruire de mur */
		if (meme_classe(cases, x, y, x, y + 1))
		{
			cases[x][y].mur_a_detruire = 0;
		}
	}

	/* Et si on peut détruire que murSud */
	if (cases[x][y].mur_a_detruire == 3)
	{
		/* Et s'il a la même classe que sa cellule au sud,
		   on ne peut plus détuire aucun mur */
		if (meme_classe(cases, x, y, x + 1, y))
		{
			cases[x][y].mur_a_detruire = 0;
		}
	}
}

/* --------------------------------------------------------- */