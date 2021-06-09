#include <stdio.h>
#include <stdlib.h>
#include "Liste_Chainee.h"
#include "Cellule_Valide.h"

/* --------------------------------------------------------- */

void free_listecasedetruisable(ListeCaseDetruisable *liste)
{
	CaseDetruisable *temp = *liste;

	while (temp != NULL)
	{
		*liste = (*liste)->suivant;
		free(temp);
		temp = *liste;
	}
}

/* --------------------------------------------------------- */

void free_liste_hachage(ListeCaseDetruisable hachage[], int taille)
{
	int i;

	for (i = 0 ; i < taille ; i++)
	{
		free_listecasedetruisable(&hachage[i]);
	}
}

/* --------------------------------------------------------- */

ListeCaseDetruisable alloue_case_liste(int x, int y)
{
	CaseDetruisable *nouvelle_cellule = malloc(sizeof(CaseDetruisable));

	if (nouvelle_cellule == NULL)
	{
		fprintf(stderr, "Erreur : Allocation dynamique das la fonction ajoute_cellule() a échoué\n");
		exit(EXIT_FAILURE);
	}

	nouvelle_cellule->coordonnees_case.x = x;
	nouvelle_cellule->coordonnees_case.y = y;
	nouvelle_cellule->suivant = NULL;

	return nouvelle_cellule;
}

/* --------------------------------------------------------- */

ListeCaseDetruisable ajoute_casedetruisable(ListeCaseDetruisable liste, int x, int y)
{
	CaseDetruisable *temp = alloue_case_liste(x, y);

	if (liste == NULL)
	{
		return temp;
	}

	else
	{
		temp->suivant = liste;
		return temp;
	}
}

/* --------------------------------------------------------- */

ListeCaseDetruisable init_liste_mursdetruisables(int num_ligne, int nombre_liste, int taille_liste)
{
	int i;
	ListeCaseDetruisable nouvelle_liste = NULL;

	for (i = 0 ; i < taille_liste ; i++)
	{
		if (num_ligne != nombre_liste - 1 || i != taille_liste - 1)
		{
			nouvelle_liste = ajoute_casedetruisable(nouvelle_liste, num_ligne, i);
		}
	}

	return nouvelle_liste;
}

/* --------------------------------------------------------- */

void init_hachage_mursdetruisables(ListeCaseDetruisable Hachage[], int nombre_liste, int taille_liste)
{
	int i;

	for (i = 0 ; i < nombre_liste ; i++)
	{
		Hachage[i] = init_liste_mursdetruisables(i, nombre_liste, taille_liste);
	}
}


/* --------------------------------------------------------- */

void init_tailles_listes(int tab[], int taille_tab, int taille_liste)
{	
	int i;

	for (i = 0 ; i < taille_tab ; i++)
	{
		tab[i] = taille_liste;
	}

	/* La dernière ligne ne compte pas la case de fin, donc on enlève 1 */
	tab[taille_tab - 1] = taille_liste - 1;
}

/* --------------------------------------------------------- */

int calcul_indice_hachage(int *case_a_detruire, int liste_tailles[])
{
	int indice_hachage = 0;

	while (*case_a_detruire - liste_tailles[indice_hachage] >= 0)
	{
		*case_a_detruire -= liste_tailles[indice_hachage];
		++indice_hachage;
	} 	

	return indice_hachage;
}

/* --------------------------------------------------------- */

void extrait_coordonnees_case(ListeCaseDetruisable hachage[], int case_a_detruire, int *x, int *y, int liste_tailles[])
{
	int i = 0, indice_hachage = calcul_indice_hachage(&case_a_detruire, liste_tailles);
	ListeCaseDetruisable temp = hachage[indice_hachage];

	/* Tant qu'on n'a pas atteint i-ème case qui correspond à case_a_detruire */
	while (i != case_a_detruire)
	{
		temp = temp->suivant;
		++i;
	}

	*x = temp->coordonnees_case.x;
	*y = temp->coordonnees_case.y;
}

/* --------------------------------------------------------- */

void maj_cases_accessibles(ListeCaseDetruisable hachage[], laby_t *labyrinthe)
{
	int i, indice_hachage = 0, x, y, cases_non_accessibles_debut = labyrinthe->cases_non_accessibles;
	ListeCaseDetruisable temp = hachage[indice_hachage];

	/* Tant que la liste actuelle est vide, on passe à la suivante */
	while (temp == NULL)
	{
		++indice_hachage;
		temp = hachage[indice_hachage];
	}
	/* On parcourt la table de hachage */
	for (i = 0 ; i < cases_non_accessibles_debut ; i++)
	{
		x = temp->coordonnees_case.x;
		y = temp->coordonnees_case.y;
		/* Si la case étudiée et celle de départ sont dans la même classe, on l'enlève de la liste */
		if (meme_classe(labyrinthe->cases, 0, 0, x, y))
		{
			supprime_case_quelconque(&hachage[x], x, y);
			labyrinthe->cases_non_accessibles--;
		}
		
		temp = temp->suivant;
			
		/* Tant la liste actuelle est vide, ou si on a atteint la fin, on passe à la suivante */
		while (temp == NULL)
		{
			++indice_hachage;
			temp = hachage[indice_hachage];
		}
	}
}

/* --------------------------------------------------------- */

ListeCaseDetruisable supprime_premiere_case(ListeCaseDetruisable liste) 
{
	CaseDetruisable *temp;

	if (liste == NULL)
	{
		return liste;
	}

	temp = malloc(sizeof(CaseDetruisable));

	if (temp == NULL)
	{
		fprintf(stderr, "Erreur : Allocation dynamique dans 'supprime_premiere_case_liste()'\n");
		exit(EXIT_FAILURE);
	}

	temp = liste->suivant;

	free(liste);
	liste = NULL;

	return temp;
}

/* --------------------------------------------------------- */

void supprime_case(ListeCaseDetruisable liste, int x, int y) 
{
	CaseDetruisable *temp = liste;
	CaseDetruisable *before = liste;

	while(temp->coordonnees_case.x != x || temp->coordonnees_case.y != y)
	{
		before = temp;
		temp = temp->suivant;
	}

	before->suivant = temp->suivant;
	free(temp);
}

/* --------------------------------------------------------- */

void supprime_case_quelconque(ListeCaseDetruisable *liste, int x, int y)
{
	if ((*liste)->coordonnees_case.x == x && (*liste)->coordonnees_case.y == y)
	{
		*liste = supprime_premiere_case(*liste);
	}

	else
	{
		supprime_case(*liste, x, y); /* enleve la case (x, y) dans liste_cases_detruisales */
	}
}

/* --------------------------------------------------------- */







