#include <stdlib.h>
#include <stdio.h>
#include "Affiche_Jeu.h"

/* -------------------------------------------------------- */

void affiche_quadrillage(Plateau P) {
	int i;

	/* NB : En soi on pourrait combiner les deux vu qu'on a forcément ligne = colonne, mais au cas où on change les options */
	/* Lignes verticales */
	for (i = 1 ; i < P.nb_col ; i++) {
		MLV_draw_filled_rectangle(i * TAILLE_IMAGE / P.nb_col, 0, 5, TAILLE_IMAGE, MLV_COLOR_BLACK);
	}

	/* Lignes horizontales */
	for (i = 1 ; i < P.nb_lig ; i++) {
		MLV_draw_filled_rectangle(0, i * TAILLE_IMAGE / P.nb_lig, TAILLE_IMAGE, 5, MLV_COLOR_BLACK);
	}
}

/* -------------------------------------------------------- */

void affiche_interface_jeu(Plateau P) {
	int longueur_plateau = TAILLE_IMAGE * 2 + TAILLE_SEPARATEUR_IMAGE;

	/* Ligne séparateur entre les 2 images, et entre les images et l'interface en as */
	MLV_draw_filled_rectangle(TAILLE_IMAGE, 0, TAILLE_SEPARATEUR_IMAGE, TAILLE_IMAGE, COULEUR_SOUS_MENU);
	MLV_draw_filled_rectangle(0, TAILLE_IMAGE, longueur_plateau, TAILLE_SEPARATEUR_IMAGE, COULEUR_SOUS_MENU);

	/* 1ère case : Nombre de coups joués */
	MLV_draw_text_box(0, TAILLE_IMAGE + TAILLE_SEPARATEUR_IMAGE, longueur_plateau / 4, TAILLE_INTERFACE - TAILLE_SEPARATEUR_IMAGE, "Coups joues : %d", 10, COULEUR_SOUS_MENU, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, P.coups_joues);

	/* 2ème case : Temps écoulé */
	MLV_draw_text_box(longueur_plateau / 4, TAILLE_IMAGE + TAILLE_SEPARATEUR_IMAGE, longueur_plateau / 4, TAILLE_INTERFACE - TAILLE_SEPARATEUR_IMAGE, "Temps écoulé : %d", 10, COULEUR_SOUS_MENU, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, P.time / 1000);

	/* 3ème case : Retry */
	MLV_draw_text_box(longueur_plateau * 2 / 4, TAILLE_IMAGE + TAILLE_SEPARATEUR_IMAGE, longueur_plateau / 4, TAILLE_INTERFACE - TAILLE_SEPARATEUR_IMAGE, "Recommencer", 10, COULEUR_SOUS_MENU, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

	/* 4ème case : Quitter */
	MLV_draw_text_box(longueur_plateau * 3 / 4, TAILLE_IMAGE + TAILLE_SEPARATEUR_IMAGE, longueur_plateau / 4, TAILLE_INTERFACE - TAILLE_SEPARATEUR_IMAGE, "Quitter", 10, COULEUR_SOUS_MENU, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

	MLV_actualise_window();
}

/* -------------------------------------------------------- */

void affiche_image(const MLV_Image *image, Plateau P) {
	int i, j;
	double taille_case_col = TAILLE_IMAGE / P.nb_col, taille_case_lig = TAILLE_IMAGE / P.nb_lig;

	/* Blocs du taquin */
	for (i = 0 ; i < P.nb_lig ; i++) {
		for (j = 0 ; j < P.nb_col ; j++) {
			MLV_draw_partial_image(image, P.bloc[i][j].col * taille_case_col, P.bloc[i][j].lig * taille_case_lig, taille_case_col, taille_case_lig, j * taille_case_col, i * taille_case_lig);
		}
	}
 	
	/* Case noire du taquin */
	MLV_draw_filled_rectangle(P.case_vide.col * taille_case_col, P.case_vide.lig * taille_case_lig, taille_case_col, taille_case_lig, MLV_COLOR_BLACK);
	
	/* Image originale à droite */
	MLV_draw_partial_image(image, 0, 0, TAILLE_IMAGE, TAILLE_IMAGE, TAILLE_IMAGE + TAILLE_SEPARATEUR_IMAGE, 0);
	MLV_draw_filled_rectangle(TAILLE_IMAGE * 2 + TAILLE_SEPARATEUR_IMAGE - taille_case_col, TAILLE_IMAGE - taille_case_lig, taille_case_col, taille_case_lig, MLV_COLOR_BLACK);

	/* On affiche le quadrillage et l'interface du jeu (les boutons en bas des images) */
	affiche_quadrillage(P);
	affiche_interface_jeu(P);
}

/* -------------------------------------------------------- */

void affiche_victoire(Plateau P) {
	int longueur_plateau = (TAILLE_IMAGE * 2 + TAILLE_SEPARATEUR_IMAGE), temps = 20;

	/* Le while qui fait un timer = temps (en seconde) */
	while (temps-- > 1) {	
		MLV_draw_text_box(longueur_plateau * 5 / 12, TAILLE_IMAGE * 5 / 12, longueur_plateau * 2 / 12, TAILLE_IMAGE * 2 / 12, "VICTOIRE !\nFermeture automatique\nde la fenêtre dans %d sec", 10, MLV_COLOR_RED, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, temps);
		MLV_actualise_window();
		MLV_wait_seconds(1);
	}
	
	MLV_free_window();
}

/* -------------------------------------------------------- */

int recommencer(int x, int y) {
	/* On vérifie que les coordonnées (x, y) sont sur le bouton "Recommencer" */
	return x > (TAILLE_IMAGE * 2 + TAILLE_SEPARATEUR_IMAGE) / 2 && x < (TAILLE_IMAGE * 2 + TAILLE_SEPARATEUR_IMAGE) * 3 / 4 &&
	       y > TAILLE_IMAGE + TAILLE_SEPARATEUR_IMAGE;
}

/* -------------------------------------------------------- */

int quitter(int x, int y) {
	/* On vérifie que les coordonnées (x, y) sont sur le bouton "Quitter" */
	return x > (TAILLE_IMAGE * 2 + TAILLE_SEPARATEUR_IMAGE) * 3 / 4 && y > TAILLE_IMAGE + TAILLE_SEPARATEUR_IMAGE;
}

/* -------------------------------------------------------- */
