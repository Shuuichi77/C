#ifndef CASE_H
#define CASE_H

#include "Coordonnees.h"

/* --------------------------------------------------------- */

	typedef struct 
	{
		int mur_a_detruire; /* 0 -> aucun mur à détruire // 1 -> les 2 murs // 2 -> murEst // 3 -> murSud */
		int murEst;				
		int murSud;
		coordonnees_t pere;	
		int rang;
	} case_t;

/* --------------------------------------------------------- */

	/* Initialise les variables d'une structure 'case_t', 
	   avec des coordonnées (x, y) */
	case_t init_case_t(int x, int y, int hauteur_laby, int largeur_laby);

/* --------------------------------------------------------- */

#endif