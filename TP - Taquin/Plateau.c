#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Plateau.h"

/* -------------------------------------------------------- */

int init_plateau(Plateau *P, int nb_col, int nb_lig) {
	int i, j;

	P->nb_col = nb_col;
	P->nb_lig = nb_lig;

	/* On alloue et on crée le plateau */
	P->bloc = (Carre**) malloc(nb_lig * sizeof(Carre));
	if (P->bloc == NULL) {
		return -1;
	}

	for (i = 0 ; i < P->nb_lig ; i++) {
		P->bloc[i] = (Carre*) malloc(nb_lig * sizeof(Carre));
		if (P->bloc[i] == NULL) {
			return -1;
		}

		for (j = 0 ; j < P->nb_col ; j++) {
			((P->bloc)[i][j].lig = i);
			((P->bloc)[i][j].col = j);
		}
	}

	/* On intialise la case noire du plateau en bas à gauche, et on met le nombre de coups joués et le timer à 0 */
	P->case_vide.lig = P->nb_lig - 1;
	P->case_vide.col = P->nb_col - 1;
	P->coups_joues = 0;
	P->time = 0;

	return 1;
}

/* -------------------------------------------------------- */

void reinit_plateau(Plateau *P) {
	int i, j;

	/* On a déjà alloué le tableau de Carre, on a juste à remettre les valeurs à zéro */
	for (i = 0 ; i < P->nb_lig ; i++) {
		for (j = 0 ; j < P->nb_col ; j++) {
			((P->bloc)[i][j].lig = i);
			((P->bloc)[i][j].col = j);
		}
	}
	
	/* On réinitialise les champs de la structure */
	P->case_vide.lig = P->nb_lig - 1;
	P->case_vide.col = P->nb_col - 1;
	P->coups_joues = 0;
	P->time = 0; 
}

/* -------------------------------------------------------- */

int touche_valide(Plateau P, MLV_Keyboard_button touche) {
	/* On interdit un mouvement des touches directionnelles selon chaque bord du plateau */
	/* Bord haut */
	if (P.case_vide.lig == 0 && touche == MLV_KEYBOARD_DOWN) {
		return 0;
	}

	/* Bord Bas */
	if (P.case_vide.lig == P.nb_lig - 1 && touche == MLV_KEYBOARD_UP) {
		return 0;
	}

	/* Bord Gauche */
	if (P.case_vide.col == 0 && touche == MLV_KEYBOARD_RIGHT) {
		return 0;
	}

	/* Bord Droite */
	if (P.case_vide.col == P.nb_col - 1 && touche == MLV_KEYBOARD_LEFT) {
		return 0;
	}

	/* Si on a passé tous les tests, on peut donc faire n'importe quel mouvement */
	return 1;
}

/* -------------------------------------------------------- */

int clique_valide(Plateau P, int x, int y) {
	/* On calcule dans quelle case le clique de coordonnées (x, y) 
	   se situe par rapport à la case vide du plateau */
	x -= P.case_vide.col;
	y -= P.case_vide.lig;
	
	/* Si case en haut */
	if (x == 0 && y == -1) {
		return 1;
	}

	/* Si case en bas */
	if (x == 0 && y == 1) {
		return 2;
	}

	/* Si case à gauche */
	if (x == -1 && y == 0) {
		return 3;
	}

	/* Si case à droite */
	if (x == 1 && y == 0) {
		return 4;
	}

	return 0;
}

/* -------------------------------------------------------- */

void swap_case_plateau(Plateau *P, MLV_Keyboard_button touche) {
	Carre temp;

	/* On swap 2 cases du plateau selon le mouvement initié par le joueur 
	   On va modifier respectivement :
	   - Les coordonnées de la case à bouger pour qu'elle prenne la place de la case noire
	   - Les coordonnées de la case noire pour qu'elle prenne la place de la case à bouger
	   - Les coordonées du champ case_vide pour noircir la nouvelle case 
	*/
	if (touche == MLV_KEYBOARD_DOWN) {
		temp = P->bloc[P->case_vide.lig - 1][P->case_vide.col];

		P->bloc[P->case_vide.lig - 1][P->case_vide.col] = P->bloc[P->case_vide.lig][P->case_vide.col];
		P->bloc[P->case_vide.lig][P->case_vide.col] = temp;
		P->case_vide.lig -= 1;
	}
	
	else if (touche == MLV_KEYBOARD_UP) {
		temp = P->bloc[P->case_vide.lig + 1][P->case_vide.col];

		P->bloc[P->case_vide.lig + 1][P->case_vide.col] = P->bloc[P->case_vide.lig][P->case_vide.col];
		P->bloc[P->case_vide.lig][P->case_vide.col] = temp;
		P->case_vide.lig += 1;
	}

	else if (touche == MLV_KEYBOARD_RIGHT) {
		temp = P->bloc[P->case_vide.lig][P->case_vide.col - 1];

		P->bloc[P->case_vide.lig][P->case_vide.col - 1] = P->bloc[P->case_vide.lig][P->case_vide.col];
		P->bloc[P->case_vide.lig][P->case_vide.col] = temp;
		P->case_vide.col -= 1;
	}

	else if (touche == MLV_KEYBOARD_LEFT) {
		temp = P->bloc[P->case_vide.lig][P->case_vide.col + 1];

		P->bloc[P->case_vide.lig][P->case_vide.col + 1] = P->bloc[P->case_vide.lig][P->case_vide.col];
		P->bloc[P->case_vide.lig][P->case_vide.col] = temp;
		P->case_vide.col += 1;
	}
}

/* -------------------------------------------------------- */

void melange_plateau(Plateau *P, MLV_Keyboard_button ordre_melange[], int nb_melange) {
	int compteur, ajoute_time = 0; /* ajoute_time permet de modifier la graine de srand() au cas où on refait une boucle dans le do while */
	MLV_Keyboard_button touche;

	/* On fait un do while au cas où lorsqu'on mélange le plateau, il est déjà gagné : 
	   ça peut arriver dans la difficulté facile où on mélange seulement 10 fois, 
	   ou bien si on fait un petit plateau de 2x2 */
	do {
		/* On remet toujours compteur à 0 au cas où on refait une boucle */
		compteur = 0;

		srand(time(NULL) + ajoute_time);

		while (compteur < nb_melange) {
			do {
				switch(rand() % 4) {
					case 0: touche = MLV_KEYBOARD_DOWN; break;
					case 1: touche = MLV_KEYBOARD_UP; break;
					case 2: touche = MLV_KEYBOARD_LEFT; break;
					case 3: touche = MLV_KEYBOARD_RIGHT; break;
				}
			} while (!touche_valide(*P, touche));

			ordre_melange[compteur] = touche;
			swap_case_plateau(P, touche);
			compteur++;
		}

		/* On incrémente ajoute_time pour changer la graine de srand() au cas où on refait une boucle */
		ajoute_time++;
	} while (plateau_victoire(*P));
}

/* -------------------------------------------------------- */

void reset_plateau(Plateau *P, MLV_Keyboard_button ordre_melange[], int nb_melange) { 
	int i;

	/* On réinitialise le plateau à son état d'origine avant de le remélanger */
	reinit_plateau(P);

	/* On mélange tout le plateau à partir du tableau "ordre_melange" qu'on a crée lors
	   du 1er mélange du plateau */
	for (i = 0 ; i < nb_melange ; i++) {
		swap_case_plateau(P, ordre_melange[i]);
	}
}

/* -------------------------------------------------------- */

int mouvement_touche(Plateau *P, MLV_Keyboard_button touche) {
	/* Si la touche est une des flèches directionnelles, 
	   on vérifie qu'on peut bouger la case adjacente associé à la touche en question */
	if (touche == MLV_KEYBOARD_LEFT || touche == MLV_KEYBOARD_RIGHT || touche == MLV_KEYBOARD_UP ||touche == MLV_KEYBOARD_DOWN) {
		if (touche_valide(*P, touche)) {
			P->coups_joues++;
			swap_case_plateau(P, touche);
		}

		return 1;
	}

	return 0;
}


/* -------------------------------------------------------- */

int mouvement_souris(Plateau *P, int x, int y) {
	/* On vérifie que le clique a été fait sur une des cases adjacentes de la case vide, 
	   tout en vérifiant si le mouvement est faisable */
	switch (clique_valide(*P, x / (TAILLE_IMAGE / P->nb_col), y / (TAILLE_IMAGE / P->nb_lig))) {
		case 1: swap_case_plateau(P, MLV_KEYBOARD_DOWN); P->coups_joues++; return 1;
		case 2: swap_case_plateau(P, MLV_KEYBOARD_UP); P->coups_joues++; return 1;
		case 3: swap_case_plateau(P, MLV_KEYBOARD_RIGHT); P->coups_joues++; return 1;
		case 4: swap_case_plateau(P, MLV_KEYBOARD_LEFT); P->coups_joues++; return 1;
	}

	return 0;
}

/* -------------------------------------------------------- */

int plateau_victoire(Plateau P) {
	int i, j;

	/* On vérifie si chaque case du plateau est bien positionnée, 1 par 1
	   On renvoie 0 dès qu'on rencontre une case mal placée */
	for (i = 0 ; i < P.nb_lig ; i++) {
		for (j = 0 ; j < P.nb_col ; j++) {
			if (P.bloc[i][j].lig != i || P.bloc[i][j].col != j) {
				return 0;
			}
		}
	}

	return 1;
}

/* -------------------------------------------------------- */
