#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arguments.h"

/* --------------------------------------------------------- */

int mot_contient_chaine(char *mot, char *chaine)
{
	/* On compare 'mot' et 'chaine', selon le nombre de lettre de 'chaine',
	   et on return 1 si la comparaison a donné 0, donc le début de mot est
	   identique à chaine */	
	if (strncmp(mot, chaine, strlen(chaine)) == 0)
	{
		return 1;
	}

	return 0;
}

/* --------------------------------------------------------- */

void teste_arguments(int nombre_arguments, char const *tab_arguments[], char tab_options[][20], int options_valides[7], int *hauteur_laby, int *largeur_laby)
{
	int i, j;
	char argument[256];

	/* On étudie tous les mots entrés en argument à l'exécution du programme */
	for (i = 1 ; i < nombre_arguments ; i++)
	{
		strcpy(argument, tab_arguments[i]);
	
		/* On compare l'argument actuel à toutes les options valides */
		for (j = 0 ; j < NOMBRE_OPTIONS ; j++)
		{
			/* Les 3 premieres valeur de tab_options sont des valeurs à récupérer,
	 		   par exemple la graine, l'attente, ou la hauteur/largeur du labyrinthe,
	 		   donc on va comparer que le mot jusqu'au '=' */
			if (j < 3)
			{
				if (mot_contient_chaine(argument, tab_options[j]))
				{
					if (j == 0)
					{
						char *temp_taille_laby;

						temp_taille_laby = strchr(argument, '=');
						sscanf(temp_taille_laby, "=%dx%d", &(*hauteur_laby), &(*largeur_laby));
					}

					else if (j == 1)
					{
						char *temp_graine;

						temp_graine = strchr(argument, '=');
						sscanf(temp_graine, "=%d", &(options_valides[j]));
					}

					else if (j == 2)
					{
						char *temp_attente;

						temp_attente = strchr(argument, '=');
						sscanf(temp_attente, "=%d", &(options_valides[j]));
					}

					break;
				}
			}

			/* Les 4 valeurs suivantes sont des options à valider ou non, par exemple
			   '--unique', '--acces', ..., donc on compare tout le mot */
			else
			{
				if (strcmp(argument, tab_options[j]) == 0)
				{
					options_valides[j] = 1;
					break;
				}
			}
		}
	}
}

/* --------------------------------------------------------- */