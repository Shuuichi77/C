CC = gcc
CFLAGS = -Wall -pedantic -ansi
LDFLAGS = -lMLV -lncurses
OBJ = Main.o Murs.o Graphique.o Texte.o Arguments.o Case.o Laby.o Fusion.o Cellule_Valide.o Liste_Chainee.o

##########################################################

Labyrinthe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 

####################

Main.o: Main.c Murs.h Laby.h Cellule_Valide.h Liste_Chainee.h Fusion.h

Murs.o: Murs.c Murs.h Laby.h Fusion.h Cellule_Valide.h

Graphique.o: Graphique.c Graphique.h Laby.h

Texte.o: Texte.c Texte.h Laby.h Structures.h

Arguments.o: Arguments.c Arguments.h 

Case.o: Case.c Case.h Coordonnees.h

Laby.o: Laby.c Laby.h Case.h Coordonnees.h Cellule_Valide.h

Fusion.o: Fusion.c Fusion.h Case.h Coordonnees.h

Cellule_Valide.o: Cellule_Valide.c Cellule_Valide.h Fusion.h Case.h

Liste_Chainee.o: Liste_Chainee.c Liste_Chainee.h Coordonnees.h Laby.h Cellule_Valide.h

%.o: %.c
	$(CC) -c $^ $(CFLAGS) $(LDFLAGS) 

##########################################################

install: Labyrinthe
	mkdir Projet
	mv Labyrinthe Projet/Labyrinthe
	make mrproper

uninstall: mrproper
	rm -f Projet/Labyrinthe
	rm -rf Projet

clean:
	rm -f *.o
	rm -f *.gch

mrproper: clean
	rm -f Labyrinthe
