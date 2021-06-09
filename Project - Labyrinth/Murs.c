#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Murs.h"
#include "Fusion.h"
#include "Cellule_Valide.h"

/* --------------------------------------------------------- */

void enleve_mur(laby_t *labyrinthe, int x, int y)
{	
	int mur = labyrinthe->cases[x][y].mur_a_detruire;

	/* Si on peut détruire les 2 murs, on rand() pour choisir lequel on va détruire */
	if (mur == 1)
	{
		mur += rand() % 2 + 1; /* On veut rajouter "+ 1" ou "+ 2" pour que mur == 2 ou mur == 3 */
	}

	/* On détruit murEst */
	if (mur == 2)
	{
		labyrinthe->cases[x][y].murEst = 0;
		Fusion(labyrinthe->cases, x, y, x, y + 1);
	}

	/* On détruit murSud */
	else if (mur == 3)
	{	
		labyrinthe->cases[x][y].murSud = 0;
		Fusion(labyrinthe->cases, x, y, x + 1, y);
	}

	maj_mur_a_detruire(&(labyrinthe->cases[x][y]), mur);
}

/* --------------------------------------------------------- */

void maj_mur_a_detruire(case_t *cellule_detruit, int mur_detruit)
{	
	/* S'il ne leur restait plus qu'1 mur à détruire, donc mur_a_detruire != 1,
	   on vient de détruire leur dernier mur restant, donc mur_a_detruire devient 0 */
	if (cellule_detruit->mur_a_detruire != 1)
	{
		cellule_detruit->mur_a_detruire = 0;
	}

	/* Sinon, on regarde on vient de détruire quel mur, et on met à jour
	   mur_a_detruire en fonction de celui qu'on vient de détruire */
	else
	{
		if (mur_detruit == 2)
		{
			cellule_detruit->mur_a_detruire = 3;
		}

		else
		{
			cellule_detruit->mur_a_detruire = 2;
		}
	}
}