#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#define NOMBRE_OPTIONS 7

/* --------------------------------------------------------- */

	/* Permet de vérifier si 'mot' commence par tous les caractères du mot 'chaine' */
	int mot_contient_chaine(char *mot, char *chaine);

	/* Teste tous les arguments qui ont été fourni à l'exécution du programme, 
	   et valide les variables dans 'options_valides', ou les modifie selon la valeur fournie
	   (par exemple pour la hauteur, la largeur, ou bien la graine ou l'attente).

	 * tab_options = le texte de toutes les options valides pour les strcmp avec les arguments
	 				 fournis par l'utilisateur (par ex. '--graine=X', '--victor', ...)
	 * options_valides = variables qui sont égales à 0 à la base, pour dire qu'une option ne sera pas activée,
	 					 qui devient 1 si l'option a été fourni par l'utilisateur en argument 
	 */
	void teste_arguments(int nombre_arguments, char const *tab_arguments[], char tab_options[][20], int options_valides[7], int *hauteur_laby, int *largeur_laby);

/* --------------------------------------------------------- */

#endif