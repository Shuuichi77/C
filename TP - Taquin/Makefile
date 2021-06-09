CC = gcc
CFLAGS = -Wall -ansi
LDFLAGS = -lMLV
OBJ = Main.o Plateau.o Affiche_Jeu.o Menu.o

##########################################################

Taquin: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

####################

Main.o: Main.c Plateau.h Affiche_Jeu.h Menu.h
Affiche_Jeu.o: Affiche_Jeu.c Affiche_Jeu.h Plateau.h
Plateau.o: Plateau.c Plateau.h
Menu.o: Menu.c Menu.h

%.o: %.c
	$(CC) -c $^ $(CFLAGS) $(LDFLAGS) 

##########################################################

clean:
	rm -f *.o
	rm -f *.gch

mrproper: clean
	rm -f Taquin	
