#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include "Texte.h"
#include "Structures.h"

/* --------------------------------------------------------- */

void ligne_colonne_max(int *hauteur_laby, int *largeur_laby)
{
	if (*hauteur_laby > (LINES - 1) / 2)
	{
		*hauteur_laby = (LINES - 1) / 2;
	}

	if (*largeur_laby > (COLS - 1) / 3)
	{
		*largeur_laby = (COLS - 1) / 3;
	}
		
}
/* --------------------------------------------------------- */

void affichage_texte(laby_t labyrinthe, int hauteur_laby, int largeur_laby, int attente)
{
	if (attente != 0)
	{
		int i, j;

		clear();

		/* Tracer du grand mur fixe supérieur */
		for (i = 0 ; i < largeur_laby ; i++)
		{
			printw("+--");
		}

		addch('+');

		/* Tracer du grand mur fixe gauche */
		for (i = 2 ; i < hauteur_laby * 2 ; i += 2)
		{
			mvaddch(i, 0, '+');
			mvaddch(i + 1, 0, '|');
		}

		mvaddch(hauteur_laby * 2, 0, '+');

		for (i = 0 ; i < hauteur_laby ; i++)
		{
			for (j = 0 ; j < largeur_laby ; j++)
			{	
				
				if (labyrinthe.cases[i][j].murSud)
				{
					mvprintw(2 * i + 2, 3 * j, "+--+");
				}

				
				if (labyrinthe.cases[i][j].murEst)
				{
					mvaddch(2 * i, 3 * (j + 1), '+');
					mvaddch(2 * i + 1, 3 * (j + 1), '|');
					mvaddch(2 * i + 2, 3 * (j + 1), '+');
				}
			}
		}
		
		refresh();
		usleep(attente);
	}
}

/* --------------------------------------------------------- */

void affichage_texte_avancee(laby_t labyrinthe, int hauteur_laby, int largeur_laby, int attente)
{
	int i, j;
	int nord, est, sud, ouest;
	
	if (attente != 0)
	{
		/* Coin haut gauche */
		printf("\n%s", intersections[0][0][0][1]);

		/* 1ère ligne, le mur en haut du labyrinthe */
		for (i = 0 ; i < largeur_laby - 1 ; i++)
		{	
			/* Si la case (0, i) a un murEst */
			if (labyrinthe.cases[0][i].murEst)
			{
				printf("%s%s", intersections[0][0][1][1], intersections[1][0][1][1]);
			}

			/* Mais s'il n'y a pas de murEst */
			else
			{
				printf("%s%s", intersections[0][0][1][1], intersections[0][0][1][1]);
			}
			
		}

		/* Le coin tout en haut à droite */
		printf("%s%s\n", intersections[0][0][1][1], intersections[1][0][1][0]);

		/* Le corps du labyrinthe, sauf le mur en bas */
		for (i = 0 ; i < hauteur_laby - 1 ; i++)
		{
			/* Mur à gauche, mais 1ère ligne exception car on laisse de la place pour l'entrée */
			if (i == 0)
			{
				/* Si la case (0, 0) a un murSud */
				if (labyrinthe.cases[0][0].murSud)
				{
					printf("%s", intersections[1][0][0][1]);
				}

				/* Si elle n'en a pas */
				else
				{
					printf("%s", intersections[1][0][0][0]);
				}
			}

			/* Le reste du mur à gauche */
			else if (i > 0)
			{
				/* Si la case (i, 0) a un mur sud */
				if (labyrinthe.cases[i][0].murSud)
				{
					printf("%s", intersections[1][1][0][1]);
				}

				/* Si elle n'en a pas */
				else
				{
					printf("%s", intersections[1][1][0][0]);
				}
			}

			for (j = 0 ; j < largeur_laby ; j++)
			{
				/* Tout le corps du labyrinthe, sauf le mur tout à droite */
				if (j != largeur_laby - 1)
				{
					/* S'il y a un murSud en (i, j) */
					if (labyrinthe.cases[i][j].murSud)
					{
						printf("%s", intersections[0][0][1][1]);
					}

					/* S'il n'y en a pas */
					else
					{
						printf("%s", intersections[0][0][0][0]);
					}

					/* L'intersection : on regarde tout autour s'il y a des murs */
					nord = labyrinthe.cases[i][j].murEst;
					est = labyrinthe.cases[i][j + 1].murSud;
					sud = labyrinthe.cases[i + 1][j].murEst;
					ouest = labyrinthe.cases[i][j].murSud;

					print_intersection(nord, est, sud, ouest);
				}

				/* Le mur tout à droite */
				else
				{
					/* L'avant dernière ligne, la dernière case */
					if (i == hauteur_laby - 2)
					{
						if (labyrinthe.cases[i][j].murSud)
						{
							printf("%s%s", intersections[0][0][1][1], intersections[0][1][1][0]);
						}

						/* Si elle n'a pas de murSud */
						else
						{
							printf("%s%s", intersections[0][0][0][0], intersections[0][1][0][0]);
						}
					}

					/* Tout le reste du mur droit */
					else
					{
						/* Si la case (i, j), j = dernière colonne, a un murSud */
						if (labyrinthe.cases[i][j].murSud)
						{
							printf("%s%s", intersections[0][0][1][1], intersections[1][1][1][0]);
						}

						/* Si elle n'a pas de murSud */
						else
						{
							printf("%s%s", intersections[0][0][0][0], intersections[1][1][0][0]);
						}
					}
				}
			}
			printf("\n");
		}

		/* Le coin en bas à gauche */
		printf("%s", intersections[0][1][0][1]);

		/* Tout le mur en bas */
		for (i = 0 ; i < largeur_laby - 1; i++)
		{
			if (labyrinthe.cases[hauteur_laby - 1][i].murEst)
			{
				printf("%s%s", intersections[0][0][1][1], intersections[0][1][1][1]);
			}

			else
			{
				printf("%s%s", intersections[0][0][1][1], intersections[0][0][1][1]);
			}
		}
		printf("%s%s", intersections[0][0][1][1], intersections[0][0][1][0]);
		printf("\n");
		usleep(attente);
	}

	
}

/* --------------------------------------------------------- */

void print_intersection(int nord, int est, int sud, int ouest)
{
	if (!nord && !est && !sud && !ouest)
	{
		printf("%s", intersections[0][0][0][0]);
	}

	/* 2ème : OUEST */
	else if (!nord && !est && !sud && ouest)
	{
		printf("%s", intersections[0][0][1][0]);
	}

	/* 3ème : SUD */
	else if (!nord && !est && sud && !ouest)
	{
		printf("%s", intersections[1][0][0][0]);
	}

	/* 4ème : SUD - OUEST */
	else if (!nord && !est && sud && ouest)
	{
		printf("%s", intersections[1][0][1][0]);
	}

	/* 5ème : EST */
	else if (!nord && est && !sud && !ouest)
	{
		printf("%s", intersections[0][0][0][1]);
	}

	/* 6ème : EST - OUEST */
	else if (!nord && est && !sud && ouest)
	{
		printf("%s", intersections[0][0][1][1]);
	}

	/* 7ème : EST - SUD*/
	else if (!nord && est && sud && !ouest)
	{
		printf("%s", intersections[1][0][0][1]);
	}

	/* 8ème : EST - SUD - OUEST*/
	else if (!nord && est && sud && ouest)
	{
		printf("%s", intersections[1][0][1][1]);
	}

	/* 9ème : NORD */
	else if (nord && !est && !sud && !ouest)
	{
		printf("%s", intersections[0][1][0][0]);
	}

	/* 10ème : NORD - OUEST*/
	else if (nord && !est && !sud && ouest)
	{
		printf("%s", intersections[0][1][1][0]);
	}

	/* 11ème : NORD - SUD*/
	else if (nord && !est && sud && !ouest)
	{	
		printf("%s", intersections[1][1][0][0]);
	}

	/* 12ème : NORD - SUD - OUEST*/
	else if (nord && !est && sud && ouest)
	{
		printf("%s", intersections[1][1][1][0]);
	}

	/* 13ème : NORD - EST */
	else if (nord && est && !sud && !ouest)
	{
		printf("%s", intersections[0][1][0][1]);
	}	

	/* 14ème : NORD - EST - OUEST */
	else if (nord && est && !sud && ouest)
	{
		printf("%s", intersections[0][1][1][1]);
	}

	/* 15ème : NORD - EST - SUD*/
	else if (nord && est && sud && !ouest)
	{
		printf("%s", intersections[1][1][0][1]);
	}

	/* 16ème : NORD - EST - SUD - OUEST */
	else if (nord && est && sud && ouest)
	{
		printf("%s", intersections[1][1][1][1]);
	}
}