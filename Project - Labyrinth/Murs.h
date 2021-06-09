#ifndef MURS_H
#define MURS_H

#include "Laby.h"	

/* --------------------------------------------------------- */
	
	/* Supprime un mur dans le labyrinthe, et fusionne les cellules en conséquence */
	void enleve_mur(laby_t *labyrinthe, int x, int y);

	/* Met à jour la variable "mur_a_detruire" de la cellule de "labyrinthe" pour laquelle
	   on vient de détruire le mur "mur_detruit" */
	void maj_mur_a_detruire(case_t *cellule_detruit, int mur_detruit);

/* --------------------------------------------------------- */

#endif

