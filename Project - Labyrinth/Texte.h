#ifndef TEXTE_H
#define TEXTE_H

#include "Laby.h"

/* --------------------------------------------------------- */
	/* Calcule le nombre de ligne et colonne maximum qu'un écran peut afficher.
	   Si les valeurs d'"hauteur_laby" et "largeur_laby" sont trop grandes pour l'écran,
	   on les réajuste */
	void ligne_colonne_max(int *hauteur_laby, int *largeur_laby);

	/* Affiche le labyrinthe en mode texte selon une taille selon ses dimensions.
	   Actualise l'affichage selon la valeur de "attente" */
	void affichage_texte(laby_t labyrinthe, int hauteur_laby, int largeur_laby, int attente);

	/* Version avancée de la fonction "affichage_texte()" */
	void affichage_texte_avancee(laby_t labyrinthe, int hauteur_laby, int largeur_laby, int attente);

	/* Affiche l'intersection de 4 cases du labyrinthe, selon l'existence des murs autour
	   (aux 4 points cardinaux) */
	void print_intersection(int nord, int est, int sud, int ouest);

/* --------------------------------------------------------- */

#endif