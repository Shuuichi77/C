#ifndef FUSION_H
#define FUSION_H

#include "Case.h"
#include "Coordonnees.h"

/* --------------------------------------------------------- */
	
	/* Cherche la classe d'une cellule (x, y) dans le tableau 'cases', 
	   tout en compressant les chemins */
	coordonnees_t Trouve(case_t **cases, int x, int y);	

	/* Fusionne 2 cellules 'cellule1' et 'cellule2' à partir de 'cases' */
	void Fusion(case_t **cases, int x1, int y1, int x2, int y2);

/* --------------------------------------------------------- */

#endif