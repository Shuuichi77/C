#include <stdlib.h>
#include <stdio.h>
#include "Menu.h"

/* -------------------------------------------------------- */

void choix_taille_plateau(int *nb_col, int *nb_lig) {
	int taille;
	char *chaine, *endPtr;

	/* Affiche un menu et attend que l'utilsateur entre 1, 2 ou 3 pour choisir sa taille de plateau */
	do {
		MLV_draw_text_box(TAILLE_MENU / 4, TAILLE_MENU / 3, TAILLE_MENU * 2 / 4, 100, "(1) Facile (2x2)\n(2) Normal (4x4)\n(3) Difficile (8x8)", 10, MLV_COLOR_GREEN, MLV_COLOR_GREEN, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
		MLV_wait_input_box(50, 50, TAILLE_MENU - 100, (TAILLE_MENU / 4) - 50, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "Choisir la taille du plateau (1, 2 ou 3): ", &chaine);
		
		taille = strtol(chaine, &endPtr, 10);
	} while (strcmp(endPtr, "") != 0 || taille < 1 || taille > 3);
	/* strcmp permet d'empêcher les entrées comme "1a" */

	/* Selon la difficulté choisi, on modifie les paramètres de la fonction pour créer la taille du plateau par la suite */
	switch (taille) {
    	case 1: *nb_col = 2; *nb_lig = 2; break;
    	case 2: *nb_col = 4; *nb_lig = 4; break;
    	case 3: *nb_col = 8; *nb_lig = 8; break;
    }

    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_actualise_window();
}

/* -------------------------------------------------------- */

void choix_nb_melange(int *nb_melange) {
	int nv_difficulte;
	char *chaine, *endPtr;

	/* Affiche un menu et attend que l'utilisateur entre un chiffre valide, 1, 2 ou 3, pour choisir un nombre de mélange pour le jeu */
	do {
		MLV_draw_text_box(TAILLE_MENU / 4, TAILLE_MENU / 3, TAILLE_MENU * 2 / 4, 100, "(1) Facile (20 mélanges)\n(2) Normal (60 mélanges)\n(3) Difficile (120 mélanges)", 10, MLV_COLOR_GREEN, MLV_COLOR_GREEN, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
		MLV_wait_input_box(50, 50, TAILLE_MENU - 100, (TAILLE_MENU / 4) - 50, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "Choisir la difficulté (1, 2 ou 3) : ", &chaine);
		
		nv_difficulte = strtol(chaine, &endPtr, 10);
	} while (strcmp(endPtr, "") != 0 || nv_difficulte < 1 || nv_difficulte > 3);

    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_actualise_window();

    /* Selon la difficulté, on associe un nombre de mélange à nb_melange */
    switch (nv_difficulte) {
    	case 1: *nb_melange = 10; break;
    	case 2: *nb_melange = 60; break;
    	case 3: *nb_melange = 120; break;
    }
}

/* -------------------------------------------------------- */

void choix_image(char **nom_image) {
	char *chaine, *endPtr;
	int num_image;
	MLV_Image *panda = MLV_load_image("./panda.png"),
			  *paysage = MLV_load_image("./paysage.png"),
			  *whatsapp = MLV_load_image("./paysage2.png"),
			  *panthere = MLV_load_image("./panthere_rose.jpeg");

	MLV_resize_image(panda, 102, 102);
	MLV_resize_image(paysage, 102, 102);
	MLV_resize_image(whatsapp, 102, 102); 
	MLV_resize_image(panthere, 102, 102); 

	/* Affiche un menu et les images disponibles, puis attend que l'utilisateur 
	   entre un chiffre entre 1, 2, 3 ou 4 pour choisir l'image avec laquelle il va jouer */
	do {
		MLV_draw_image(panda, 20.8, 325);
		MLV_draw_image(paysage, 20.8 * 2 + 102, 325);
		MLV_draw_image(whatsapp, 20.8 * 3 + 102 * 2, 325);
		MLV_draw_image(panthere, 20.8 * 4 + 102 * 3, 325);

		MLV_draw_text_box(TAILLE_MENU / 4, TAILLE_MENU / 3, TAILLE_MENU * 2 / 4, 100, "(1) Panda\n(2) Paysage\n(3) Paysage 2\n(4) Panthere Rose", 10, MLV_COLOR_GREEN, MLV_COLOR_GREEN, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
		MLV_wait_input_box(50, 50, TAILLE_MENU - 100, (TAILLE_MENU / 4) - 50, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "Choisir l'image (1, 2, 3 ou 4) : ", &chaine);
		

		num_image = strtol(chaine, &endPtr, 10);
	} while (strcmp(endPtr, "") != 0 || num_image < 1 || num_image > 4);

    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_actualise_window();

    switch (num_image) {
    	case 1: *nom_image = "./panda.png"; break;
    	case 2: *nom_image = "./paysage.png"; break;
    	case 3: *nom_image = "./paysage2.png"; break;
    	case 4: *nom_image = "./panthere_rose.jpeg"; break;
    }  
}

/* -------------------------------------------------------- */

void affiche_regles(void) {
	int x, y;

	MLV_draw_text_box(TAILLE_MENU / 8, TAILLE_MENU / 8, TAILLE_MENU * 3 / 4, TAILLE_MENU * 11 / 16, "Règles du jeu\n\n- Reformer l'image à gauche par rapport\nà l'image d'origine à droite\n\n- Déplacer les cases adjacentes à la case noire\nà l'aide des flèches directionnelles\n\n- Ou bien cliquer sur une des cases\nadjacentes à la case noire pour la déplacer", 10, MLV_COLOR_GREEN, MLV_COLOR_GREEN, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_TOP);
	MLV_draw_text_box(TAILLE_MENU * 3 / 8, TAILLE_MENU * 11 / 16, TAILLE_MENU * 2 / 8, TAILLE_MENU / 16, "Lancer", 10, MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_TOP);
	MLV_actualise_window();

	while (1) {
		if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
			MLV_get_mouse_position(&x, &y);

			if (x > TAILLE_MENU * 3 / 8 && x < TAILLE_MENU * 5 / 8 &&
				y > TAILLE_MENU * 11 / 16 && y < TAILLE_MENU * 12 / 16) {
				break;
			}
		}
	}
}

/* -------------------------------------------------------- */