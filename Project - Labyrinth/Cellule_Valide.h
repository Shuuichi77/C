#ifndef CELLULE_VALIDE_H
#define CELLULE_VALIDE_H

#include "Case.h"

/* --------------------------------------------------------- */

	/* Renvoie 1 si les cellules (x1, y1) et (x2, y2) appartiennent à la même classe, 0 sinon */
	int meme_classe(case_t **cases, int x1, int y1, int x2, int y2);

	/* Verifie qu'une cellule pour laquelle on veut détruire des murs n'a pas la même classe que 
	   ses cellules voisines (sud et est). Dans le cas échéant, met à jour quels murs on pourra encore détruire 
	   pour la cellule "cases[x][y]" */
	void verif_voisins_classe(case_t **cases, int x, int y);

/* --------------------------------------------------------- */

#endif