#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <MLV/MLV_all.h> 
#include <ncurses.h>	 
#include <unistd.h>		 
#include "Murs.h"
#include "Graphique.h"
#include "Texte.h"
#include "Arguments.h"
#include "Laby.h"
#include "Cellule_Valide.h"
#include "Liste_Chainee.h"
#include "Coordonnees.h"
#include "Fusion.h"
#include <sys/ioctl.h>


int main(int argc, char const *argv[])
{
	int hauteur_laby = 6, largeur_laby = 8, options[NOMBRE_OPTIONS] = {0}, nb_case_detruisable, x, y, case_a_detruire, *tailles_listes;
	int taille_cellule, taille_fenetre_max = 650;
	char texte_options[NOMBRE_OPTIONS][20] = { "--taille=", "--graine=", "--attente=", "--mode=texte", "--unique", "--acces", "--victor"};
	laby_t labyrinthe;
	ListeCaseDetruisable *liste_hachage_detruisables, *liste_hachage_accessible;
	coordonnees_t classe_actuelle = {-1, -1}, cellule_depart;

	/* On met une valeur random pour graine, et si elle reste inchangée 
       (donc si l'utilisateur ne fournit pas de graine), on génère un labyrinthe
       totalement random avec srand(time(NULL)) */
	options[1] = 1455646486; 

	teste_arguments(argc, &(*argv), texte_options, options, &hauteur_laby, &largeur_laby);

	/* Pour fixer la graine si l'utilisateur en a fourni */
	if (options[1] == 1455646486)
	{
		srand(time(NULL));
	}

	else
	{
		srand(options[1]);
	}


	/* Affichage graphique, on ouvre une fenêtre */
	if (!options[3])
	{
		calcule_taille_cellule(hauteur_laby, largeur_laby, taille_fenetre_max, &taille_cellule);
		MLV_create_window("Labyrinthe", "Labyrinthe", largeur_laby * taille_cellule , hauteur_laby * taille_cellule);	
	}

	/* Affichage texte, on se renseigne sur la taille de la fenêtre afin de  limiter la largeur du labyrinthe s'il est trop grand,
	   sinon l'affichage ne se ferait pas correctement (on ne limite pas la hauteur, on peut scroll pour voir tout le labyrinthe verticalement) */
	else
	{
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);

		if (largeur_laby > (w.ws_col - 1) / 2)
		{
			largeur_laby = (w.ws_col - 1) / 2;
		}
	}

	/* Initialisation de toutes les variables pour construire le labyrinthe */
	liste_hachage_detruisables = malloc(hauteur_laby * sizeof(ListeCaseDetruisable));
	tailles_listes = malloc(hauteur_laby * sizeof(int));
	labyrinthe = init_labyrinthe(hauteur_laby, largeur_laby);
	init_tailles_listes(tailles_listes, hauteur_laby, largeur_laby);
	init_hachage_mursdetruisables(liste_hachage_detruisables, hauteur_laby, largeur_laby);
	nb_case_detruisable = hauteur_laby * largeur_laby - 1;
	
	/* Si on a "--acces" mais pas "--unique" */
	if (!options[4] && options[5])
	{
		liste_hachage_accessible = malloc(hauteur_laby * sizeof(ListeCaseDetruisable));
		init_hachage_mursdetruisables(liste_hachage_accessible, hauteur_laby, largeur_laby);
	}

/* -------------------------------------- Boucle principale -------------------------------------- */

	while (!labyrinthe_fini(labyrinthe, hauteur_laby, largeur_laby, options[4], options[5], nb_case_detruisable))
	{
		/* Le "do while" ne sert que pour l'option "unique" : on break en plein milieu si l'option n'est pas acivitée.
		 * Dans ce "do while", on vérifie que la case qu'on va selectionner n'est pas devenue une case
		   sans mur détruisable suite au dernier mur détruit, au cas où ses voisins sont maintenant dans la même classe  */
		do
		{
			case_a_detruire = rand() % nb_case_detruisable;
			extrait_coordonnees_case(liste_hachage_detruisables, case_a_detruire, &x, &y, tailles_listes);

			/* Si on a pas l'option "unique", on sort du "do while" */
			if (!options[4])
			{
				break;
			}

			verif_voisins_classe(labyrinthe.cases, x, y);

			/* Si la case est devenue une case sans mur destruisable, on doit l'enlever de la liste chainee */
			if (labyrinthe.cases[x][y].mur_a_detruire == 0)
			{	
				supprime_case_quelconque(&liste_hachage_detruisables[x], x, y);
				--tailles_listes[x];
				--nb_case_detruisable;
			}

		} while (labyrinthe.cases[x][y].mur_a_detruire == 0 && nb_case_detruisable > 0);

		/* Si on sort du 'do while' avec la condition "nb_case_detruisable > 0",
		   alors il n'y a plus de case détruisable, le labyrinthe est complet */
		if (nb_case_detruisable == 0)
		{
			break;
		}
		
	 	enleve_mur(&labyrinthe, x, y);

	 	/* Si "--acces" mais pas "--unique" 
	 	 * Dès qu'on a un chemin acceptant, on regarde toutes les cellules qui n'ont pas la même classe
	 	   que la première case, qui a la classe d'un chemin acceptant */
	 	if (options[5] && !options[4] && chemin_acceptant(labyrinthe, hauteur_laby, largeur_laby))
	 	{	
		 	/* Permet de voir si la classe de la case de départ a changé (peu probable mais possible)
		 	   Si c'est le cas, on réinitiale "liste_hachage_accessible" */
	 		cellule_depart = Trouve(labyrinthe.cases, 0, 0);
		 	if (cellule_depart.x != classe_actuelle.x || cellule_depart.y != classe_actuelle.y)
		 	{
		 		classe_actuelle = Trouve(labyrinthe.cases, 0, 0);
		 		free_liste_hachage(liste_hachage_accessible, hauteur_laby);
		 		liste_hachage_accessible = malloc(hauteur_laby * sizeof(ListeCaseDetruisable));
				init_hachage_mursdetruisables(liste_hachage_accessible, hauteur_laby, largeur_laby);
		 	}

		 	maj_cases_accessibles(liste_hachage_accessible, &labyrinthe);
	 	}

		/* On vérifie que la case qu'on vient de détruire possède encore des murs détruisable,
		   dans le cas échéant on l'enlève dans la table de hachage */
		if (labyrinthe.cases[x][y].mur_a_detruire == 0)
		{
			supprime_case_quelconque(&liste_hachage_detruisables[x], x, y);
			--tailles_listes[x];
			--nb_case_detruisable;
		}

		options[3] ? affichage_texte_avancee(labyrinthe, hauteur_laby, largeur_laby, options[2]) :
					 affichage_graphique(labyrinthe, taille_cellule, hauteur_laby, largeur_laby, options[2]);
	}

	/* On reaffiche la fenêtre pour le cas où attente = 0 */
	options[3] ? affichage_texte_avancee(labyrinthe, hauteur_laby, largeur_laby, 1) :
				 affichage_graphique(labyrinthe, taille_cellule, hauteur_laby, largeur_laby, 1);

	MLV_wait_seconds(120);

/* --------------------------------------- FIN DU PROGRAMME -------------------------------------- */

	if (!options[3])
	{
		MLV_free_window();
	}

	if (!options[4] && options[5])
	{
		free_liste_hachage(liste_hachage_accessible, hauteur_laby);
	}

	free_liste_hachage(liste_hachage_detruisables, hauteur_laby);
	free_labyrinthe(&labyrinthe, hauteur_laby);
 
	return 0;
}