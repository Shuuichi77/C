#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <MLV/MLV_all.h>
#include "Graphique.h"

/* --------------------------------------------------------- */

void calcule_taille_cellule(int hauteur_laby, int largeur_laby, int taille_max, int *taille_cellule)
{
	if (hauteur_laby > largeur_laby)
	{
		*taille_cellule = taille_max / hauteur_laby;
	} 

	else
	{
		*taille_cellule = taille_max / largeur_laby;
	}

	/* On fixe une taille de cellule minimum, pour ne pas se retrouver avec une cellule de taille 1, voir 0 */
	if (*taille_cellule < 3)
	{
		*taille_cellule = 3;
	}
}

/* --------------------------------------------------------- */

void affichage_graphique(laby_t labyrinthe, int taille_cellule, int hauteur_laby, int largeur_laby, int attente)
{
	int i, j;

	if (attente != 0)
	{
		MLV_clear_window(MLV_COLOR_WHITE);

		/* On affiche tous les murs du labyrinthe encore présent */
		for (i = 0 ; i < hauteur_laby ; i++)
		{
			for (j = 0 ; j < largeur_laby ; j++)
			{	
				/* Affiche murs SUD */
				if (labyrinthe.cases[i][j].murSud)
				{
					MLV_draw_line(j * taille_cellule, (i + 1) * taille_cellule, 
								  (j + 1) * taille_cellule, (i + 1) * taille_cellule, 
					 		      MLV_COLOR_BLACK);
				}

				/* Affiche murs EST */
				if (labyrinthe.cases[i][j].murEst)
				{
					MLV_draw_line((j + 1) * taille_cellule, i * taille_cellule, 
								  (j + 1) * taille_cellule, (i + 1) * taille_cellule, 
					 		      MLV_COLOR_BLACK);
				}
			}
		}

		MLV_actualise_window();
		usleep(attente);
	}
}

/* --------------------------------------------------------- */
