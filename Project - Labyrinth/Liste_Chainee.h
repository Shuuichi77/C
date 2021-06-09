#ifndef LISTE_CHAINEE_H
#define LISTE_CHAINEE_H

#include "Coordonnees.h"
#include "Laby.h"


/* --------------------------------------------------------- */

	/* Liste chaînée dans laquelle on stocke les coordonnées 
       de cases, par exemple si on veut stocker les cases
       qui ont encore au moins 1 mur */
	typedef struct casesdetruisables
	{
		coordonnees_t coordonnees_case;
		struct casesdetruisables *suivant;
	} CaseDetruisable, *ListeCaseDetruisable;

/* --------------------------------------------------------- */

	/* Initialise un tableau de int "tab" de taille "taille_tab", dont toutes
	   les valeurs seront "taille_liste" */
	void init_tailles_listes(int tab[], int taille_tab, int taille_liste);

	/* Libère tout l'espace alloué d'une liste chaînée de type "ListeCaseDetruisable" */
	void free_listecasedetruisable(ListeCaseDetruisable *liste);	

	/* Libère tout l'espace alloué d'une table de hachage "hachage", de taille "taille" */
	void free_liste_hachage(ListeCaseDetruisable hachage[], int taille);

	/* Alloue de l'espace pour une nouvelle valeur dans une liste chainée de type "ListeCaseDetruisable" */
	ListeCaseDetruisable alloue_case_liste(int x, int y);

	/* Ajoute en tete de liste, plus rapide pour rajouter de cette façon */
	ListeCaseDetruisable ajoute_casedetruisable(ListeCaseDetruisable liste, int x, int y);

	/* Initialise une liste chainée de type "ListeCaseDetruisable", de taille "taille_liste".
	   Les coordonnées dans la liste auront pour 1ère coordonnée "num_liste" */
	ListeCaseDetruisable init_liste_mursdetruisables(int num_ligne, int nombre_liste, int taille_liste);

	/* Initialise une table de hachage de type "ListeCaseDetruisable", avec "hauteur_laby" listes,
	   qui sont de taille "largeur_laby" */
	void init_hachage_mursdetruisables(ListeCaseDetruisable Hachage[], int nombre_liste, int taille_liste);

	/* Permet de calculer à quelle i-ème liste va-t-on s'intéresser dans la table de hachage : on se
	   sert de liste_tailles pour cela */
	int calcul_indice_hachage(int *case_a_detruire, int liste_tailles[]);

	/* Récupère les coordonnées (x, y) qui correspondent à la valeur numero "case_a_detruire" dans une des listes
	   de la table de hachage. On se sert pour ça de listes_tailles */
	void extrait_coordonnees_case(ListeCaseDetruisable hachage[], int case_a_detruire, int *x, int *y, int listes_tailles[]);

	/* Permet de mettre à jour la table de hachage afin de voir quelles cases sont encore 
	   accessibles dans le labyrinthe, et de se débarasser de celles qui le sont déjà (sert 
	   uniquement pour "--acces" seul, avec "--unique" on utilise la structure autrement */
	void maj_cases_accessibles(ListeCaseDetruisable hachage[], laby_t *labyrinthe);

	/* Permet de supprimer la 1ère valeur de la liste chaînée "liste" de type ListeCaseDetruisable */
	ListeCaseDetruisable supprime_premiere_case(ListeCaseDetruisable liste);

	/* Permet de supprimer une valeur de la liste chaînée "liste" de type ListeCaseDetruisable, sauf la 1ère */
	void supprime_case(ListeCaseDetruisable liste, int x, int y);

	/* Permet de supprimer n'importe quelle valeur de la liste chaînée "liste" de type ListeCaseDetruisable */
	void supprime_case_quelconque(ListeCaseDetruisable *liste, int x, int y);

/* --------------------------------------------------------- */

#endif