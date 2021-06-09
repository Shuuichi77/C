#ifndef MENU_H
#define MENU_H
 
	#include <MLV/MLV_all.h>
	#define TAILLE_MENU 512

/* -------------------------------------------------------- */
	
	/* Affiche un menu pour entrer et choisir la taille du plateau parmi 3 possibilités :
		1 : Plateau 2x2
		2 : Plateau 4x4
		3 : Plateau 8x8
	   Modifie ensuite les paramètres nb_col et nb_lig.

	   NB : On ne laisse pas la possibilité de rentrer 2 entiers car si par exemple on entre 5x5,
	   on a des cases de 102,4 x 102,4. Sauf que libMLV ne prend que des int et non pas des doubles/float
	   pour ses fonctions, donc par exemple pour la fonction MLV_draw_partial_image, on aurait donc des décalages.
	*/
	void choix_taille_plateau(int *nb_col, int *nb_lig);

	/* Affiche un menu qui demande au joueur à choisir combien de mélange il veut pour son jeu, et
	   associe la valeur à nb_melange selon le choix de l'utilisateur :
		1 : 20 mélanges
		2 : 60 mélanges
		3 : 120 mélanges
	*/
	void choix_nb_melange(int *nb_melange);

	/* Affiche un menu avec les images disponibles, et demande au joueur de choisir une d'entre elles.
	   On met ensuite le nom de l'image dans le paramètre "nom_image" selon le choix de l'utilisateur */
	void choix_image(char **nom_image);

	/* Affiche les règles du jeu et un bouton "Lancer" sur lequel on doit cliquer pour lancer le jeu */
	void affiche_regles(void);
	
/* -------------------------------------------------------- */


#endif