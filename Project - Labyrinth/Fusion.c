#include <stdlib.h>
#include <stdio.h>
#include "Fusion.h"

/* --------------------------------------------------------- */

coordonnees_t Trouve(case_t **cases, int x, int y)
{	
	if (x != cases[x][y].pere.x || y != cases[x][y].pere.y)
	{
		cases[x][y].pere = Trouve(cases, cases[x][y].pere.x, cases[x][y].pere.y);
	}

	return cases[x][y].pere;
}

/* --------------------------------------------------------- */

void Fusion(case_t **cases, int x1, int y1, int x2, int y2)
{
	coordonnees_t representant_cellule1 = Trouve(cases, x1, y1), representant_cellule2 = Trouve(cases, x2, y2);

	int x3 = representant_cellule1.x, y3 = representant_cellule1.y, x4 = representant_cellule2.x, y4 = representant_cellule2.y;
	/* (x3, y3) = représentant de cases[x1][y1] 
	 * (x4, y4) = représentant de cases[x2][y2] */

	/* Si la cellule1 et la cellule2 n'appartiennent pas à la même classe, on les fusionne */
	if (x3 != x4 || y3 != y4)
	{
		/* Si les 2 cellules sont de même rang, la classe de cellule1 devient le nouveau père de cellule2, et on incrémente le rang de cellule 1 */			
		if (cases[x3][y3].rang == cases[x4][y4].rang)
		{
			cases[x3][y3].rang++;
			cases[x4][y4].pere.x = x3;
			cases[x4][y4].pere.y = y3;
		}

		else if (cases[x3][y3].rang > cases[x4][y4].rang)
		{
			cases[x4][y4].pere.x = x3;
			cases[x4][y4].pere.y = y3;
		}

		else
		{
			cases[x3][y3].pere.x = x4;
			cases[x3][y3].pere.y = y4;
		}
	}
}

/* --------------------------------------------------------- */
