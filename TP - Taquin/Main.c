#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "Plateau.h"
#include "Affiche_Jeu.h"
#include "Menu.h"

int main(int argc, char const *argv[])
{
	int x, y, nb_melange, nb_lig, nb_col, previous_time = 0; /* previous_time permettra de reset le timer si on recommence */
	char *nom_image = NULL;
	Plateau plateau;
	MLV_Image *image;
	MLV_Keyboard_button touche, *ordre_melange; /* ordre_melange stock l'ordre des mélanges effectués sur le plateau lorsqu'on voudra recommencer le jeu */
	MLV_Button_state state; 
 	MLV_Event event;

 	/* Menu avant le jeu */
 	MLV_create_window("TP4 - Menu", "TP4", TAILLE_IMAGE, TAILLE_IMAGE);
 	choix_taille_plateau(&nb_col, &nb_lig);
	choix_nb_melange(&nb_melange);
	choix_image(&nom_image);
	affiche_regles();

	MLV_free_window();

 	/* Jeu principal */
	if (init_plateau(&plateau, nb_col, nb_lig) == -1) {
		fprintf(stderr, "Erreur d'allocation dynamique lors de l'initialisation du plateau\n");
		exit(EXIT_FAILURE);
	}

	/* On alloue le tableau ordre_melange puisqu'on a le nombre de mélange */
	ordre_melange = (MLV_Keyboard_button*) malloc(nb_melange * sizeof(MLV_Keyboard_button));
	if (ordre_melange == NULL) {
		fprintf(stderr, "Erreur d'allocation dynamique lors de l'initialisation du tableau melange_plateau\n");
		exit(EXIT_FAILURE);
	}

	MLV_create_window("TP4 - Taquin", "TP4", TAILLE_IMAGE * 2 + TAILLE_SEPARATEUR_IMAGE, TAILLE_IMAGE + TAILLE_INTERFACE);
	image = MLV_load_image(nom_image);
	melange_plateau(&plateau, ordre_melange, nb_melange);
	affiche_image(image, plateau);
	previous_time = MLV_get_time();

	/* Boucle du jeu */
	while (!plateau_victoire(plateau)) {
		event = MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
		plateau.time = MLV_get_time() - previous_time;
		affiche_interface_jeu(plateau);
	
		/* Si une touche a été préssée, on vérifie que le mouvement voulu est possible 
		   puis on réaffiche l'image si c'est le cas */
		if (event == MLV_KEY && state == MLV_PRESSED) {
			if (mouvement_touche(&plateau, touche)) { 
				affiche_image(image, plateau);
			}
		}

		/* Si un clique de souris gauche a été réalisé */
		if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
			MLV_get_mouse_position(&x, &y);

			/* Si on a cliqué sur le taquin, et qu'on peut bouger la case cliquée */
			if (mouvement_souris(&plateau, x, y)) { 
				affiche_image(image, plateau);
			}

			/* Si on a cliqué sur le bouton quitter */
			if (quitter(x, y)) {
				return 0;
			}

			/* Si on a cliqué sur le bouton recommencer */
			if (recommencer(x, y)) {
			 	reset_plateau(&plateau, ordre_melange, nb_melange);
			 	affiche_image(image, plateau);
			 	previous_time = MLV_get_time(); /* On met à jour previous_time pour le soustraire à plateau.time et pouvoir réinitialiser le temps */
			}
		}
	}

	/* Boucle du jeu fini, donc victoire du joueur */
	affiche_victoire(plateau);
	
	return 0;
}