#ifndef AFFICHE_JEU_H
#define AFFICHE_JEU_H 

	#include <MLV/MLV_all.h>
	#include "Plateau.h"

/* -------------------------------------------------------- */
	
	/* Affiche le quadrillage du taquin */
	void affiche_quadrillage(Plateau P);

	/* Affiche l'interface en bas du jeu (le nombre de coups joués, le temps, le bouton recommencer et quitter */
	void affiche_interface_jeu(Plateau P);

	/* Affiche l'état actuel du plateau et son interface */
	void affiche_image(const MLV_Image *image, Plateau plateau);

	/* Affiche un message de victoire si le plateau est bien complété
	   Ce message s'efface au bout d'un certain temps */
	void affiche_victoire(Plateau P);

	/* Renvoie 1 si les coordonnées (x, y) sont sur le bouton "Recommencer" */
	int recommencer(int x, int y);

	/* Renvoie 1 si les coordonnées (x, y) sont sur le bouton "Quitter" */
	int quitter(int x, int y);
	
/* -------------------------------------------------------- */

#endif