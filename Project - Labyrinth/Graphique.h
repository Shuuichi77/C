#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include "Laby.h"

/* --------------------------------------------------------- */
	
	/* Calcule la taille d'une celulle "taille_cellule" selon la taille du labyrinthe hauteur_laby x largeur_laby, 
	   et de la taille de la fenêtre maximale fixée "taille_max" */
	void calcule_taille_cellule(int hauteur_laby, int largeur_laby, int taille_max, int *taille_cellule);

	/* Affiche graphuiquement le labyrinthe selon une taille "taille_cellule".
	   Actualise l'affichage selon la valeur de "attente" */
	void affichage_graphique(laby_t labyrinthe, int taille_cellule, int hauteur_laby, int largeur_laby, int attente);

/* --------------------------------------------------------- */


#endif