from upemtk import *
from copy import deepcopy
taille_case = 60 # Modifier pour agrandir la taille des cases de la grille

## Projet Hitori
### Tâche 1 : Représentation et chargement des niveaux
def lire_grille(nom_fichier):
    """
    Renvoie une liste de listes décrivant les valeurs des cellules de la grille à partir d'un fichier.
    
    :param nom_fichier: fichier texte représentant une grille de hitori.
    :return: liste de listes décrivant les valeurs des cellules de la grille.

    >>> grille_hitori = lire_grille(hitori1.txt) ## hitori1 est un fichier .txt contenant les chiffres
    >>> print(grille_hitori)
    [[2, 2, 1, 5, 3],
     [2, 3, 1, 4, 5],
     [1, 1, 1, 3, 5],
     [1, 3, 5, 4, 2],
     [5, 4, 3, 2, 1]]
    """
    grille = []
    fichier = open(nom_fichier)
    
    for ligne in fichier:
        ligne_grille = []
        
        for chiffre in ligne.strip().split():
            ligne_grille.append(int(chiffre))
        grille.append(ligne_grille)
    
    # Vérifie si on a des lignes de longueurs différentes
    len_ref = len(grille[0])
    for liste in grille: 
        if len(liste) != len_ref:
            return None
    
    return grille


def afficher_nombre(nb_ligne, nb_colonne, grille):
    """
    Affiche graphiquement les chiffres d'une grille d'Hitori
    à l'aide d'une liste de listes.
    
    :param nb_ligne: nombre de ligne de la grille d'Hitori.
    :param nb_colonne: nombre de colonne de la grille d'Hitori.
    :param grille: liste de listes décrivant les valeurs des cellules d'une grille d'Hitori.
    """
    efface("nombres")
    for i in range(nb_ligne):
        for j in range(nb_colonne):
            texte(j*taille_case + taille_case//2,
                  i*taille_case + taille_case//2,
                  chaine = grille[i][j], ancrage = "center", couleur = "white", tag = "nombres")


def fleche_historique(lst_historique_prec, lst_historique_suiv):
    """
    Ajuste la couleur des flèches des boutons "Précédent" et "Suivant"
    selon si c'est possible.
    
    :param lst_historique_prec: liste de l'historique des actions précédentes du joueur.
    :param lst_historique_suiv: liste de l'historique des actions suivantes du joueur.
    """
    efface("fleche")
    if len(lst_historique_prec) > 0:
        texte(5*largeur//8,
              hauteur + 3*taille_case//2,
              chaine = "←", ancrage = "center", couleur = "white", taille = largeur//20, tag = "fleche")
    else:
        texte(5*largeur//8,
              hauteur + 3*taille_case//2,
              chaine = "←", ancrage = "center", couleur = "black", taille = largeur//20, tag = "fleche")

    if len(lst_historique_suiv) > 0:
        texte(7*largeur//8,
              hauteur + 3*taille_case//2,
              chaine = "→", ancrage = "center", couleur = "white", taille = largeur//20, tag = "fleche")
    else:
        texte(7*largeur//8,
              hauteur + 3*taille_case//2,
              chaine = "→", ancrage = "center", couleur = "black", taille = largeur//20, tag = "fleche")
          
          
def texte_regle(largeur_grille, hauteur_grille):
    """
    Affiche graphiquement le texte des boutons des conditions.
    
    :param largeur_grille: largeur de la grille d'Hitori.
    :param hauteur_grille: hauteur de la grille d'Hitori
    """
    texte(largeur_grille//6,
          hauteur_grille + taille_case//2,
          chaine = "Conflit\nligne ou colonne", ancrage = "center", couleur = "white", taille = largeur_grille//35, tag = "condition")
    
    texte(largeur_grille//2,
          hauteur_grille + taille_case//2,
          chaine = "Cases noires\nadjacentes", ancrage = "center", couleur = "white", taille = largeur_grille//35, tag = "condition")
    
    texte(largeur_grille*5//6,
          hauteur_grille + taille_case//2,
          chaine = "Connexe", ancrage = "center", couleur = "white", taille = largeur_grille//35, tag = "condition")
        
    for i in range(0, largeur_grille, largeur_grille//3):
        ligne(i,
              hauteur_grille,
              i,
              hauteur_grille + taille_case,
              epaisseur = 3, couleur = "grey")


def afficher_grille(grille):
    """
    Affiche graphiquement une grille à l'aide d'une liste de listes.
    
    :param grille: liste de listes décrivant les valeurs des cellules d'une grille d'Hitori.
    """
    nombre_ligne, nombre_colonne = len(grille), len(grille[0])
    largeur, hauteur = nombre_colonne*taille_case, nombre_ligne*taille_case
    cree_fenetre(largeur, hauteur + taille_case*3)
    rectangle(0,
              0,
              largeur,
              hauteur,
              remplissage = "darkgrey")
    
    # Trace les lignes et colonnes en fonction du nombre d'éléments dans la grille d'Hitori
    for i in range(0, hauteur, int(hauteur/nombre_ligne)):
        ligne(0,
              i,
              largeur,
              i,
              epaisseur = 2)
              
    for i in range(0, largeur, int(largeur/nombre_colonne)):
        ligne(i,
              0,
              i,
              hauteur,
              epaisseur = 2)
    
    # Affiche les chiffres de grille
    afficher_nombre(nombre_ligne, nombre_colonne, grille)
    
    # Trace les lignes des boutons en bas
    rectangle(0,
              hauteur + taille_case,
              largeur,
              hauteur + 3*taille_case,
              remplissage = "black")
              
    rectangle(0,
              hauteur,
              largeur,
              hauteur + 3*taille_case,
              epaisseur = 3, couleur = "grey")
    
    ligne(0,
          hauteur + taille_case,
          largeur,
          hauteur + taille_case,
          epaisseur = 3, couleur = "grey")  
          
    ligne(0,
          hauteur + 2*taille_case,
          largeur,
          hauteur + 2*taille_case,
          epaisseur = 3, couleur = "grey")
          
    ligne(largeur//2,
          hauteur + taille_case,
          largeur//2,
          hauteur + 3*taille_case,
          epaisseur = 3, couleur = "grey")      
    
    ligne(3*largeur//4,
          hauteur + taille_case,
          3*largeur//4,
          hauteur + 2*taille_case,
          epaisseur = 3, couleur = "grey")
          
    # Affiche le texte des boutons en bas de la grille
    rectangle(0,
              hauteur,
              largeur,
              hauteur + taille_case,
              remplissage = "black", tag = "condition")
    
    texte_regle(largeur, hauteur)
    
    texte(largeur//4,
          hauteur + 3*taille_case//2,
          chaine = "Résoudre", ancrage = "center", couleur = "white", taille = largeur//20)
          
    texte(largeur//4,
          hauteur + 5*taille_case//2,
          chaine = "Recommencer", ancrage = "center", couleur = "white", taille = largeur//20)
          
    texte(3*largeur//4,
          hauteur + 5*taille_case//2,
          chaine = "Quitter", ancrage = "center", couleur = "white", taille = largeur//20)
    
    mise_a_jour()


def ecrire_grille(grille, nom_fichier):
    """
    Prend une grille d'Hitori sous forme de liste de listes, et la sauvegarde dans le fichier fournit en argument.
    
    :param grille: liste de listes décrivant les valeurs des cellules d'une grille d'Hitori.
    :param nom_fichier: fichier dans lequel sera sauvegarder la grille d'Hitori.
    """
    fichier = open(nom_fichier, 'w')
    for ligne in grille:
        for mot in ligne:
            fichier.write(str(mot) + " ")
        fichier.write("\n")



### Tâche 2 : Réalisation du moteur de jeu
## 1/ Sans Conflit
def sans_conflit(grille, noircies):
    """
    Vérifie si aucune des cellules visibles de la grille ne contient pas le même nombre
    qu'une autre cellule sur la même ligne ou la même colonne.
    
    :param grille: liste de listes décrivant les valeurs des cellules d'une grille d'Hitori.
    :param noircies: liste décrivant l'ensemble des cellules noircies sur la grille.
    :return: True si la condition est vérifiée, False si elle ne l'est pas.
    """
    # Pour la récursivité
    if noircies == None:
        return False
    

    # Faire une liste de listes de toutes les colonnes de la grille
    grille_colonne = []
    for j in range(len(grille[0])):
        sous_liste = []
        for i in range(len(grille)):
            sous_liste.append(grille[i][j])
        grille_colonne.append(sous_liste)
    
    # A partir d'une copie de la grille, on va changer les cases noircies en None
    # de la liste des listes de lignes (donc grille), et également pour la liste
    # des colonnes (grille_colonne qu'on vient de faire), tout ça à l'aide 
    # de la liste noircies
    grille_copy = deepcopy(grille)
    for case in noircies:
        grille_copy[case[0]][case[1]] = None
        grille_colonne[case[1]][case[0]] = None
    
    # Puis on efface les None dans chaque liste
    def efface_element(liste, e):
        """
        Prend une liste composée elle-même de listes, et 
        efface toutes les ocurrences de l'élément e dans ces "sous-listes".
        
        :param liste: liste composée de plusieurs listes qu'on va traiter.
        :param e: l'élément e qu'on va effacer de la liste.
        
        >>> exemple_liste = [[1, 3, 5, 1, 3, 1], [5, 8, 1, 3, 1], [1, 1]]
        >>> efface_element(exemple_liste, 1)
        >>> print(exemple_liste)
        [[3, 5, 3], [5, 8, 3], []]
        """
        for sous_liste in liste:
            for i in range(len(sous_liste) - 1, -1, -1):
                if sous_liste[i] == e:
                    sous_liste.pop(i)
    
    efface_element(grille_copy, None)
    efface_element(grille_colonne, None)
    
    # On compare ensuite la taille de chaque sous-liste (chaque sous-liste
    # correspondant à une ligne ou colonne) avec son homologue set(sous-liste) :
    # si elles sont de taille différentes, alors au moins 1 élément est identique, 
    # et donc la condition n'est pas respectée.
    for ligne in grille_copy:
        if len(ligne) != len(set(ligne)):
            return False
    for colonne in grille_colonne:
        if len(colonne) != len(set(colonne)):
            return False
            
    return True


## 2/ Sans voisines noircies
def sans_voisines_noircies(grille, noircies):
    """
    Vérifie si aucune celulle noircie ne sont voisines.
    
    :param grille: liste de listes décrivant les valeurs des cellules d'une grille d'Hitori.
    :param noircies: liste décrivant l'ensemble des cellules noircies sur la grille.
    :return: True si la condition est vérifiée, False si elle ne l'est pas.
    """
    # Pour la récursivité
    if noircies == None:
        return False
        
    # On construit une liste composé des voisins de chaque case noire.
    # On vérifie ensuite si chaque élément de cette liste se trouve dans la
    # liste des cases noircies, ce qui permet de voir si 2 cases noircies sont
    # voisines.
    for case_noire in noircies:
        cases_voisines = [(case_noire[0]+1, case_noire[1]),
                         (case_noire[0], case_noire[1]+1),
                         (case_noire[0]-1, case_noire[1]),
                         (case_noire[0], case_noire[1]-1)]
        
        for case in cases_voisines:
            if case in noircies:
                return False
                
    return True
    
    # Remarque : On n'utilise pas l'argument grille dans cette fonction, 
    # mais pour le bien des consignes de l'exercice, on le laisse
    # dans les arguments de la fonction.


## 3/ Connexe
def dans_grille(grille, i, j):
    """
    Renvoie True si la case (i, j) est une case de la grille, False sinon.
    
    :param i: numero de ligne de la case.
    :param j: numero de colonne de la case.
    
    >>> grille_test = [[0, 1, 2, 3, 4],
                       [7, 2, 4, 2, 4],
                       [4, 8, 9, 0, 3],
                       [1, 7, 6, 4, 5]]
    >>> dans_grille(grille_test, 4, 0)
    False
    """
    return (0 <= i < len(grille) and 
            0 <= j < len(grille[0]))


def voisins(i, j):
    """
    Renvoie la liste des voisins de la case (i, j).
    
    :param i: numero de ligne de la case.
    :param j: numero de colonne de la case.
    
    >>> voisins(2,3)
    [(3, 3), (2, 4), (1, 3), (2, 2)]
    """
    return [(i+1, j),
            (i, j+1),
            (i-1, j),
            (i, j-1)]


def colorie_int(grille, i, j):
    """
    Change toutes les valeurs de type "int" en chaine de caractère "OK" dans
    la zone de la case (i, j).

    :param grille: liste de listes décrivant les valeurs des cellules d'une grille d'Hitori, 
    avec la valeur None représentant une case noire
    :param i: numero de ligne de la case.
    :param j: numero de colonne de la case.
    
    >>> grille_test = [[0, 3, 6, 5, 8],
                       [1, 5, 8, 2, None],
                       [9, 7, 2, None, 5],
                       [2, 6, 1, None, 6]]
    >>> colorie_int(grille_test, 0, 0)
    >>> print(grille_test)
    [['OK', 'OK', 'OK', 'OK', 'OK'],
     ['OK', 'OK', 'OK', 'OK', None],
     ['OK', 'OK', 'OK', None, 5],
     ['OK', 'OK', 'OK', None, 6]]
    """
    if type(grille[i][j]) != int: # Dès qu'on rencontre un autre type que "int"
        return
    
    grille[i][j] = "OK"
    for vi, vj in voisins(i, j):
        if dans_grille(grille, vi, vj) and type(grille[vi][vj]) == int:
            colorie_int(grille, vi, vj)

    

def connexe(grille, noircies):
    """
    Vérifie si l'ensemble des cellules visibles de la grille forment une seule zone.
    
    :param grille: liste de listes décrivant les valeurs des cellules d'une grille d'Hitori.
    :param noircies: liste décrivant l'ensemble des cellules noircies sur la grille.
    :return: True si la condition est vérifiée, False si elle ne l'est pas.
    """ 
    # Pour la récursivité
    if noircies == None:
        return False
        
    # On change les cases noircies en None à partir d'une copie de grille.
    grille_copy = deepcopy(grille)
    for case in noircies:
        grille_copy[case[0]][case[1]] = None
    
    # On distingue quelle est la 1ère case non noircie
    i, j = 0, 0
    while grille_copy[i][j] == None:
        if j == (len(grille[0]) - 1):
            i += 1
            j = 0
        else:
            j += 1
    
    # On change toutes les valeurs de type "int" en chaine de caractère "OK".
    colorie_int(grille_copy, i, j)
    
    # On compte le nombre de "OK" dans grille_copy : cela correspond au
    # nombre de cellule connexe
    nb_cellules_connexe = 0
    for ligne in grille_copy:
        for elem in ligne:
            if elem == "OK":
                nb_cellules_connexe += 1
    
    # On compte le nombre de case dans grille
    nb_case_grille = 0
    for ligne in grille:
        nb_case_grille += len(ligne)
    
    # On compte le nombre de cellule noircie (obselète mais mieux pour visualiser)
    nb_cellule_noircies = len(noircies)
    
    # On regarde si : 
    # - nb_cellules_connexe + nb_cellule_noircies = nb_case_grille.
    # Si ce n'est pas le cas, certaines cellules sont isolées, 
    # et donc la condition n'est pas vérifiée
    if nb_cellules_connexe + len(noircies) != nb_case_grille:
        return False
    return True



## Fonctions pour jouer
def clic_case(i, j, noircies, lst_historique): 
    """
    Permet de distinguer si on doit noircir une case, ou si on doit la
    remettre dans son état d'origine. 
    Ajoute également chaque action effectuée à la liste de l'historique.
    
    :param i: numero de ligne de la case sur laquelle a cliqué le joueur.
    :param j: numero de colonne de la case sur laquelle a cliqué le joueur.
    :param noircies: liste décrivant l'ensemble des cellules noircies sur la grille.
    :param lst_historique: liste de l'historique des actions effectuées au cours de la partie.
    :return: action à faire sur la case, ainsi que la liste historique modifiée
             avec l'action qu'on va effectuer sur la case (i, j)
    """
    if (i, j) not in noircies:
        lst_historique.append([1, [i, j]])
        return 1, lst_historique
    lst_historique.append([0, [i, j]])
    return 0, lst_historique


def noircir_case(i, j, action_case, noircies):
    """
    Noircie ou remet une case dans son état d'origine selon la valeur de
    action_case.
    
    :param i: numero de ligne de la case sur laquelle a cliqué le joueur.
    :param j: numero de colonne de la case sur laquelle a cliqué le joueur.
    :param action_case: action à faire sur la case :
                        0 = noircir la case
                        1 = remettre la case à son état d'origine
    :param noircies: liste décrivant l'ensemble des cellules noircies sur la grille.
    :return: retourne la liste noircies modifiée selon l'action effectuée.
    """
    if action_case == 1: # Si action_case = 1, on doit colorier la case en noire
        rectangle(j*taille_case, 
                  i*taille_case,
                  (j+1)*taille_case,
                  (i+1)*taille_case,
                  remplissage = "black", tag = "cases_noires")
        noircies |= {(i, j)}
        
    else: # Si action_case = 0, on doit rendre la case noire blanche
        efface("cases_noires")
        noircies -= {(i, j)}
        for case in noircies:
            rectangle(case[1]*taille_case,
                      case[0]*taille_case,
                      (case[1]+1)*taille_case,
                      (case[0]+1)*taille_case,
                      remplissage = "black", tag = "cases_noires")
    
    return noircies
    

def cercle_case(i, j, rond): 
    """
    Dessine un cercle rouge autour du chiffre sur lequel le joueur a cliqué.
    
    :param i: numero de ligne de la case sur laquelle a cliqué le joueur.
    :param j: numero de colonne de la case sur laquelle a cliqué le joueur.
    :return: retourne la liste rond modifiée selon l'action effectuée.
    """
    if (i, j) not in rond: # Si on n'a pas encore encerclé la case
        cercle((2*j + 1)*taille_case//2,
               (2*i + 1)*taille_case//2,
                taille_case//2, 
                couleur = "red", epaisseur = 2, tag = "cercles")
        rond |= {(i, j)}
        
    else: # Si on veut enlever le cercle
        efface("cercles")
        rond -= {(i, j)}
        for case in rond:
            cercle(((2*case[1] + 1))*taille_case//2,
                   ((2*case[0] + 1))*taille_case//2,
                   taille_case//2, 
                   couleur = "red", epaisseur = 2, tag = "cercles")
        
    return rond



### Tâche 3 : interface graphique
def menu_niveaux():
    """
    Affiche le menu qui permet au joueur de choisir le 
    niveau de difficulté de la grille d'Hitori.
    
    :return: Liste du niveau de la grille d'Hitori choisi.
    """
    taille_case = 100
    nombre_niveau = 5
    couleur_niveau = ["white", "lightgreen", "green", "yellow", "orange", "red", "black"] # Il faut avoir un nombre de couleur >= nombre_niveau
    largeur, hauteur = nombre_niveau*taille_case, nombre_niveau*taille_case + 2*taille_case
    cree_fenetre(largeur, hauteur)
    
    # Pour afficher les couleurs des niveaux
    for i in range (taille_case, hauteur, taille_case):
        ligne(0,
              i,
              largeur,
              i,
              epaisseur = 3)
              
        rectangle(0,
                  i,
                  largeur,
                  i + taille_case, 
                  remplissage = str(couleur_niveau[i//100]))
    
    ligne(0,
          hauteur - taille_case,
          largeur,
          hauteur - taille_case,
          couleur = "grey", epaisseur = 2)
    
    # Pour écrire les niveaux
    for i in range (taille_case, hauteur + taille_case, taille_case):
        texte(largeur//2,
              i - taille_case//2,
              chaine = "Niveau " + str(i//taille_case - 1), ancrage = "center")
    
    texte(largeur//2,
          hauteur - taille_case//2,
          chaine = "Règles du jeu", ancrage = "center", couleur = "white")
    
    while True:
        ev = donne_ev()
        tev = type_ev(ev)
        
        if tev == "ClicGauche":
            # Pour afficher les règles
            if ordonnee(ev) > (hauteur - taille_case):
                page_regle(largeur, hauteur, taille_case//2)
                continue
            
            # Si on a choisi un niveau
            ferme_fenetre()
            return lire_grille("niveau" + str(int(ordonnee(ev)//taille_case)) + ".txt")
    
        # On quitte la fenêtre
        if tev == "Quitte" or tev == "Touche":
            quitter_jeu(largeur, hauteur)
    
        mise_a_jour()


def afficher_regle(largeur_grille, hauteur_grille, taille_des_cases):
    """
    Trace les lignes en bas du menu des règles,
    et affiche le texte "Commencer".
    
    :param largeur_grille: largeur de la grille d'Hitori.
    :param hauteur_grille: hauteur de la grille d'Hitori.
    """
    rectangle(0,
              0,
              largeur_grille,
              hauteur_grille - 3*taille_des_cases,
              remplissage = "white", epaisseur = 3, tag = "regles")
    
    rectangle(0,
              hauteur_grille - 3*taille_des_cases,
              largeur_grille,
              hauteur_grille - 2*taille_des_cases,
              remplissage = "darkgrey", epaisseur = 3, tag = "regles")
    
    rectangle(0,
              hauteur_grille - 2*taille_des_cases,
              largeur_grille,
              hauteur_grille,
              remplissage = "grey", epaisseur = 3, tag = "regles")
    
    ligne(largeur_grille//2,
          hauteur_grille - 3*taille_des_cases,
          largeur_grille//2,
          hauteur_grille - 2*taille_des_cases,
          epaisseur = 3, tag = "regles")
    
    texte(largeur_grille//2,
          hauteur_grille - taille_des_cases,
          chaine = "Revenir à la sélection des niveaux", ancrage = "center", couleur = "white", taille = largeur_grille//20, tag = "regles")


def regles_page1(largeur_grille, hauteur_grille, taille_des_cases):
    """
    Affiche la page 1 des règles.
    """
    efface("regles_page2")
    texte(largeur_grille//4,
          hauteur_grille - taille_des_cases*5//2,
          chaine = "←", ancrage = "center", couleur = "grey", taille = taille_des_cases*2//3, tag = "regles_page1")
        
    texte(largeur_grille*3//4,
          hauteur_grille - taille_des_cases*5//2,
          chaine = "→", ancrage = "center", taille = taille_des_cases*2//3, tag = "regles_page1")
    
    texte(largeur_grille//2,
          taille_des_cases//2,
          chaine = "Règles du jeu", ancrage = "center", couleur = "red", taille = taille_des_cases//2, tag = "regles_page1")
    
    texte(largeur_grille - taille_des_cases//2,
          hauteur_grille - taille_des_cases*16//5,
          chaine = "Page 1/2", ancrage = "center", taille = taille_des_cases//6, tag = "regles_page1")
          
    texte(10,
          taille_des_cases*3//2,
          chaine = 
          "1/ CONFLIT LIGNE OU COLONNE :\n" +
          "Parmi les cellules visibles (non noircies),\n" +
          "chaque nombre ne peut apparaître qu’une seule\n" +
          "fois au plus sur chaque ligne et chaque colonne.\n\n\n" +
          "2/ CASES NOIRES ADJACENTES :\n" +
          "Deux cellules noircies ne peuvent se toucher\n" +
          "par un côté (mais leurs coins peuvent se toucher).\n\n\n" +
          "3/ CONNEXE\n" +
          "L’ensemble des cellules visibles doit être\n" +
          "d’un seul tenant (il ne peut pas y avoir 2 zones\n" +
          "visibles distinctes non reliées entre elles).",
          taille = taille_des_cases//3, tag = "regles_page1")


def regles_page2(largeur_grille, hauteur_grille, taille_des_cases):
    """
    Affiche la page 2 des règles.
    """
    efface("regles_page1")
    texte(largeur_grille//4,
          hauteur_grille - taille_des_cases*5//2,
          chaine = "←", ancrage = "center", taille = taille_des_cases*2//3, tag = "regles_page2")
          
    texte(largeur_grille*3//4,
          hauteur_grille - taille_des_cases*5//2,
          chaine = "→", ancrage = "center", couleur = "grey", taille = taille_des_cases*2//3, tag = "regles_page2")  
            
    texte(largeur_grille//2,
          taille_des_cases//2,
          chaine = "Comment jouer ?", ancrage = "center", couleur = "red", taille = taille_des_cases//2, tag = "regles_page2")
    
    texte(largeur_grille - taille_des_cases//2,
          hauteur_grille - taille_des_cases*16//5,
          chaine = "Page 2/2", ancrage = "center", taille = taille_des_cases//6, tag = "regles_page2")
          
    texte(10,
          taille_des_cases*3//2,
          chaine = 
          "CLIC GAUCHE :\n" +
          "Permet de noircir une case. \n" +
          "Un second clique remet la case à son état d'origine.\n\n" +
          "CLIC DROIT : \n" +
          "Permet d'entourer une case d'un cercle rouge,\n" +
          "afin d'aider le joueur à marquer une case.\n\n" +
          "<- ou -> :\n" +
          "Permet d'annuler une action, ou de revenir à\n" +
          "l'action suivante.\n\n" +
          "RÉSOUDRE :\n" +
          "Montre une solution à la grille d'Hitori.\n",
          taille = taille_des_cases//3, tag = "regles_page2")


def page_regle(largeur_grille, hauteur_grille, taille_des_cases):
    afficher_regle(largeur_grille, hauteur_grille, taille_des_cases)
    regles_page1(largeur_grille, hauteur_grille, taille_des_cases)
    page = 1
    
    while True:
        ev = donne_ev()
        tev = type_ev(ev)
        
        if tev == "ClicGauche":
            x, y = abscisse(ev), ordonnee(ev)
            if (x < largeur_grille//2) and (hauteur_grille - 3*taille_des_cases < y < hauteur_grille - 2*taille_des_cases) and page == 2:
                regles_page1(largeur_grille, hauteur_grille, taille_des_cases)
                page = 1
                
            if (x > largeur_grille//2) and (hauteur_grille - 3*taille_des_cases < y < hauteur_grille - 2*taille_des_cases) and page == 1:
                regles_page2(largeur_grille, hauteur_grille, taille_des_cases)
                page = 2
                
            if y > hauteur_grille - 2*taille_des_cases:
                break
        
        # On quitte la fenêtre
        if tev == "Quitte" or tev == "Touche":
            if tev == "Quitte" or touche(ev) == "Escape":
                quitter_jeu(largeur_grille, hauteur_grille)
        
        mise_a_jour()
    
    efface("regles")
    efface("regles_page1")
    efface("regles_page2")
    
    
def action_precedente(lst_historique_prec, lst_historique_suiv, noircies): 
    """
    Annule l'action précédente du joueur.
    
    :param lst_historique_prec: liste de l'historique des actions précédentes du joueur.
    :param lst_historique_suiv: liste de l'historique des actions suivantes du joueur.
    :param noircies: liste décrivant l'ensemble des cellules noircies sur la grille.
    
    >>> historique_prec = [[1, [3, 1]], [1, [2, 4]], [1, [1, 4]], [1, [3, 3]]]
    >>> historique_suiv = []
    >>> noircies = {(3, 1), (2, 4), (1, 4), (3, 3)}
    >>> action_precedente(historique_prec, historique_suiv, noircies)
    >>> print(historique_prec, historique_suiv, noircies)
    [[1, [3, 1]], [1, [2, 4]], [1, [1, 4]]]     # historique_prec
    [[1, [3, 3]]]                               # historique_suiv
    {(3, 1), (2, 4), (1, 4)}                    # noircies
    """    
    dernier_indice = len(lst_historique_prec) - 1
    derniere_action = lst_historique_prec[dernier_indice]
    
    lst_historique_suiv.append(lst_historique_prec[dernier_indice])
    lst_historique_prec.pop(len(lst_historique_prec) - 1)
    
    if derniere_action[0] == 0:
        action_a_faire = 1
    else:
        action_a_faire = 0
    
    noircies = noircir_case(derniere_action[1][0], derniere_action[1][1], action_a_faire, noircies)


def action_suivante(lst_historique_prec, lst_historique_suiv, noircies):
    """
    Revient à l'action suivante du joueur s'il avait cliqué sur précédent.
    
    :param lst_historique_prec: liste de l'historique des actions précédentes du joueur.
    :param lst_historique_suiv: liste de l'historique des actions suivantes du joueur.
    :param noircies: liste décrivant l'ensemble des cellules noircies sur la grille.
    
    >>> historique_prec = [[1, [4, 5]], [1, [1, 2]]]
    >>> historique_suiv = [[1, [1, 5]]]
    >>> noircies = {(4, 5), (1, 2)}
    >>> action_precedente(historique_prec, historique_suiv, noircies)
    >>> print(historique_prec, historique_suiv, noircies)
    [[1, [4, 5]], [1, [1, 2]], [1, [1, 5]]]     # historique_prec
    []                                          # historique_suiv
    {(4, 5), (1, 5), (1, 2)}                    # noircies
    """    
    dernier_indice = len(lst_historique_suiv) - 1
    derniere_action = lst_historique_suiv[dernier_indice]
    
    lst_historique_prec.append(lst_historique_suiv[dernier_indice])
    lst_historique_suiv.pop(len(lst_historique_suiv) - 1)

    noircies = noircir_case(derniere_action[1][0], derniere_action[1][1], derniere_action[0], noircies)


def quitter_jeu(largeur_grille, hauteur_grille):
    """
    Affiche un message annonçant que la fenêtre va être fermée.
    
    :param largeur_grille: largeur de la grille d'Hitori.
    :param hauteur_grille: hauteur de la grille d'Hitori.
    """
    rectangle(0,
              hauteur_grille//2 - taille_case,
              largeur_grille,
              hauteur_grille//2 + taille_case,
              remplissage = "black", tag = "quitter")
    
    for i in range(hauteur_grille//2 - taille_case,
                    hauteur_grille//2 + taille_case + 1,
                    taille_case):
        ligne(0,
              i,
              largeur_grille,
              i,
              couleur = "red", epaisseur = 2, tag = "quitter")
    
    ligne(largeur_grille//2,
          hauteur_grille//2,
          largeur_grille//2,
          hauteur_grille//2 + taille_case,
          couleur = "red", epaisseur = 2, tag = "quitter")
    
    texte(largeur_grille//2,
          hauteur_grille//2 - taille_case//2,
          chaine = "Voulez-vous fermer la fenêtre ?", couleur = "red", ancrage = "center", taille = largeur_grille//20, tag = "quitter")
    
    texte(largeur_grille//4,
          hauteur_grille//2 + taille_case//2,
          chaine = "Oui", couleur = "white", ancrage = "center", taille = largeur_grille//20, tag = "quitter")
    
    texte(largeur_grille*3//4,
          hauteur_grille//2 + taille_case//2,
          chaine = "Non", couleur = "white", ancrage = "center", taille = largeur_grille//20, tag = "quitter")
    
    while True:
        ev = donne_ev()
        tev = type_ev(ev)
        
        if tev == "ClicGauche":
            x, y = abscisse(ev), ordonnee(ev)
            if (x < largeur_grille//2) and (hauteur_grille//2 < y < hauteur_grille//2 + taille_case) or (largeur//2 < x < largeur) and (hauteur + 2*taille_case < y < hauteur + 3*taille_case):
                ferme_fenetre()
            elif (x > largeur_grille//2) and (hauteur_grille//2 < y < hauteur_grille//2 + taille_case):
                efface("quitter")
                break
        
        if tev == "Quitte":
            ferme_fenetre()
    
    
        mise_a_jour()
    

def etat_partie(grille, noircies):
    """
    Vérifie l'état de la partie en vérifiant si l'ensemble des règles du jeu sont respectées.
    
    :param grille: liste de listes décrivant les valeurs des cellules d'une grille d'Hitori.
    :param noircies: liste décrivant l'ensemble des cellules noircies sur la grille.
    :return: True si toutes les conditions sont vérifiées, False si elles ne le sont pas
    
    >>> etat_partie(grille, noircies)
    False ## Au moins 1 des 3 conditions n'est pas respectée
    """
    condition_sans_conflit = sans_conflit(grille, noircies)
    condition_sans_voisines_noircies = sans_voisines_noircies(grille, noircies)
    condition_connexe = connexe(grille, noircies)
    def couleur_condition(condition, largeur_grille_1, largeur_grille_2):
        """
        Colore la case de la condition selon si elle est respectée ou non,
        en vert si elle est respectée, en rouge sinon.
        
        :param condition: la condition qu'on va vérifier.
        :param largeur_grille_1: la coordonnée en abscisse du côté gauche du rectangle qu'on va colorier.
        :param largeur_grille_2: la coordonnée en abscisse du côté droit du rectangle qu'on va colorier.
        """
        if condition == True:
            rectangle(largeur_grille_1,
                      hauteur,
                      largeur_grille_2,
                      hauteur + taille_case, 
                      remplissage = "green")
        else:
            rectangle(largeur_grille_1,
                      hauteur,
                      largeur_grille_2,
                      hauteur + taille_case,
                      remplissage = "red")
    
    couleur_condition(condition_sans_conflit, 0, largeur//3)
    couleur_condition(condition_sans_voisines_noircies, largeur//3, largeur*2//3)
    couleur_condition(condition_connexe, largeur*2//3, largeur)
    
    efface("condition")
    texte_regle(largeur, hauteur)
    
    if condition_sans_conflit and condition_sans_voisines_noircies and condition_connexe:
        texte(largeur//2,
              hauteur//2,
              chaine = "Victoire !", couleur = "red", ancrage = "center", taille = largeur//6)
        return True
    return False


def affichage_recommencer(largeur_grille, hauteur_grille):
    """
    Affichage pour recommencer une partie.
    
    :param largeur_grille: largeur de la grille d'Hitori.
    :param hauteur_grille: hauteur de la grille d'Hitori.
    """
    rectangle(0,
            hauteur_grille + taille_case,
            largeur_grille,
            hauteur_grille + 3*taille_case,
            remplissage = "black")
            
    for i in range(hauteur_grille + taille_case, hauteur_grille + 2*taille_case + 1, taille_case):
        ligne(0,
            i,
            largeur_grille,
            i,
            epaisseur = 3, couleur = "grey")
    
    texte(largeur_grille//2,
        hauteur_grille + taille_case*3//2,
        chaine = "Recommencer", couleur = "yellow", ancrage = "center", taille = largeur_grille//12)
        
    texte(largeur_grille//2,
        hauteur_grille + taille_case*5//2,
        chaine = "Quitter", couleur = "yellow", ancrage = "center", taille = largeur_grille//12)



### Tâche 4 : Recherche de solutions
def conflit_case(grille, i, j):
    """
    Vérifie pour une case de coordonnées (i, j) si elle est en conflit
    avec une autre cellule de la grille.
    
    :param grille: liste de listes décrivant les valeurs des cellules d'une grille d'Hitori.
    :param i: numero de ligne de la case
    :param j: numero de colonne de la case
    :return: True si elle n'est pas en conflit ;
             False si elle l'est.
    """
    # Faire une liste qui correspond à la colonne de la case (i, j)
    colonne_case = []
    for ligne in grille:
        colonne_case.append(ligne[j])
    
    # On regarde le nombre de fois où apparaît le chiffre de la case (i, j)
    # sur sa ligne et colonne : si plus d'1 fois, il y a conflit, donc False
    if (colonne_case.count(grille[i][j]) > 1) or (grille[i].count(grille[i][j]) > 1):
        return False
    return True


def solveur(grille, noircies, i, j, affiche_solveur):
    """
    Recherche une solution pour la grille de façon récursive à partir d'un état de grille donné.
    
    :param grille: liste de listes décrivant les valeurs des cellules d'une grille d'Hitori.
    :param noircies: liste décrivant l'ensemble des cellules noircies sur la grille.
    :param i: numero de ligne de la case.
    :param j: numero de colonne de la case.
    :param affiche_solveur: permet de décider si oui ou non on affiche graphiquement l'avancé du solveur.
    """
    # Met en surbrillance la case que le solveur étudie
    if affiche_solveur == "Oui":
        efface("surbrillance")
        rectangle(j*taille_case,
                  i*taille_case,
                  (j+1)*taille_case,
                  (i+1)*taille_case,
                  couleur = "lightgreen", epaisseur = 9, tag = "surbrillance")
    
    # Règle 2 ou 3 enfreinte :
    if (not sans_voisines_noircies(grille, noircies)) or (not connexe(grille, noircies)):
        return None
    
    
    # Règles 1, 2 et 3 vérifiées :
    if sans_conflit(grille, noircies) and sans_voisines_noircies(grille, noircies) and connexe(grille, noircies):
        return noircies
    
    # Règles 2 et 3 respectées, mais pas la 1 :
    # Celulle n'est pas en conflit :
    if conflit_case(grille, i, j):
        if j == (len(grille[i]) - 1):
            if i == (len(grille) - 1):
                return None
            return solveur(grille, noircies, i+1, 0, affiche_solveur)
        else:
            return solveur(grille, noircies, i, j+1, affiche_solveur)
        

    # Si par contre, la celulle est en conflit avec une autre cellule :
    else:
        noircies |= {(i, j)} # On noircit la cellule (i, j)
        if affiche_solveur == "Oui":
            rectangle(j*taille_case, 
                    i*taille_case,
                    (j+1)*taille_case,
                    (i+1)*taille_case,
                    remplissage = "black", tag = "cases_noires")
            mise_a_jour()

        
        if j == (len(grille[i]) - 1): # Et on cherche une solution à partir de la cellule suivante
            if i == (len(grille) - 1):
                return None
            potentielle_solution = solveur(grille, noircies, i+1, 0, affiche_solveur)
        else:
            potentielle_solution = solveur(grille, noircies, i, j+1, affiche_solveur)
        

        if sans_conflit(grille, potentielle_solution) and sans_voisines_noircies(grille, potentielle_solution) and connexe(grille, potentielle_solution): # Si la solution est trouvée, on la retourne
            return potentielle_solution
        
        else: # Sinon...
            noircies -= {(i, j)}
            if affiche_solveur == "Oui":
                efface("cases_noires")
                noircies -= {(i, j)} # On rend à nouveau visible la cellule
                for case in noircies:
                    rectangle(case[1]*taille_case,
                            case[0]*taille_case,
                            (case[1]+1)*taille_case,
                            (case[0]+1)*taille_case,
                            remplissage = "black", tag = "cases_noires")
                mise_a_jour()
            
            if j == (len(grille[i]) - 1): # Et on cherche une solution à partir de la cellule suivante
                if i == (len(grille) - 1):
                    return None
                potentielle_solution = solveur(grille, noircies, i+1, 0, affiche_solveur)
            else:
                potentielle_solution = solveur(grille, noircies, i, j+1, affiche_solveur)
            
            if sans_conflit(grille, potentielle_solution) and sans_voisines_noircies(grille, potentielle_solution) and connexe(grille, potentielle_solution):
                return potentielle_solution
            else:
                return None


def solveur_graphique(largeur_grille, hauteur_grille):
    """
    Affiche un message demandant si on veut avoir un mode graphique
    au solveur ou non.
    
    :param largeur_grille: largeur de la grille d'Hitori.
    :param hauteur_grille: hauteur de la grille d'Hitori.
    """
    rectangle(0,
              hauteur_grille//2 - taille_case,
              largeur_grille,
              hauteur_grille//2 + taille_case,
              remplissage = "black", tag = "solveurgraphique")
    
    for i in range(hauteur_grille//2 - taille_case,
                    hauteur_grille//2 + taille_case + 1,
                    taille_case):
        ligne(0,
              i,
              largeur_grille,
              i,
              couleur = "yellow", epaisseur = 2, tag = "solveurgraphique")
    
    ligne(largeur_grille//2,
          hauteur_grille//2,
          largeur_grille//2,
          hauteur_grille//2 + taille_case,
          couleur = "yellow", epaisseur = 2, tag = "solveurgraphique")
    
    texte(largeur_grille//2,
          hauteur_grille//2 - taille_case//2,
          chaine = "Activer le mode graphique ?", couleur = "white", ancrage = "center", taille = largeur_grille//20, tag = "solveurgraphique")
    
    texte(largeur_grille//4,
          hauteur_grille//2 + taille_case//2,
          chaine = "Oui", couleur = "white", ancrage = "center", taille = largeur_grille//20, tag = "solveurgraphique")
    
    texte(largeur_grille*3//4,
          hauteur_grille//2 + taille_case//2,
          chaine = "Non", couleur = "white", ancrage = "center", taille = largeur_grille//20, tag = "solveurgraphique")
    
    while True:
        ev = donne_ev()
        tev = type_ev(ev)
        
        if tev == "ClicGauche":
            x, y = abscisse(ev), ordonnee(ev)
            if (x < largeur_grille//2) and (hauteur_grille//2 < y < hauteur_grille//2 + taille_case):
                efface("solveurgraphique")
                return "Oui"
            elif (x > largeur_grille//2) and (hauteur_grille//2 < y < hauteur_grille//2 + taille_case):
                efface("solveurgraphique")
                return None
        
        if tev == "Quitte":
            ferme_fenetre()
    
    
        mise_a_jour()



## Début du jeu
# Variables de base nécessaires au fonctionnement du jeu
grille_hitori = menu_niveaux()
afficher_grille(grille_hitori)
hauteur, largeur, = len(grille_hitori)*taille_case, len(grille_hitori[0])*taille_case
cases_noircies, cases_cercles = set(), set()
historique_precedent = []
historique_suivant = []
fleche_historique(historique_precedent, historique_suivant)


while True:
    ev = donne_ev()
    tev = type_ev(ev)

    if tev == "ClicDroit": # Si on veut faire un cercle
        if ordonnee(ev) <= hauteur:
            x, y = int(abscisse(ev)/taille_case), int(ordonnee(ev)/taille_case)
            cases_cercles = cercle_case(y, x, cases_cercles)
    
    if tev == "ClicGauche":
        # On vérifie qu'on clique sur la grille
        if ordonnee(ev) <= hauteur:
            x, y = int(abscisse(ev)/taille_case), int(ordonnee(ev)/taille_case)
            etat_case, historique_precedent = clic_case(y, x, cases_noircies, historique_precedent)
            cases_noircies = noircir_case(y, x, etat_case, cases_noircies)
            afficher_nombre(len(grille_hitori), len(grille_hitori[0]), grille_hitori)
            
            # On efface l'historique suivant dès lors qu'on a refait une autre action
            if len(historique_suivant) > 0:
                historique_suivant = []
            fleche_historique(historique_precedent, historique_suivant)
            
            # On vérifie si le joueur a gagné
            if etat_partie(grille_hitori, cases_noircies):
                affichage_recommencer(largeur, hauteur)
                
                # Rentre dans la boucle pour nous permettre de faire rejouer une partie ou quitter
                while True:
                    ev = donne_ev()
                    tev = type_ev(ev)
                    
                    if tev == "ClicGauche":
                        if hauteur + taille_case < ordonnee(ev) < hauteur + 2*taille_case:
                            ferme_fenetre()
                            # On relance la fenêtre du menu, puis on réinitialise les variables de base
                            grille_hitori = menu_niveaux()
                            afficher_grille(grille_hitori)
                            hauteur, largeur, = len(grille_hitori)*taille_case, len(grille_hitori[0])*taille_case
                            cases_noircies, cases_cercles = set(), set()
                            historique_precedent = []
                            historique_suivant = []
                            break
                              
                        elif ordonnee(ev) > hauteur + 2*taille_case:
                            ferme_fenetre()
                        
                    if tev == "Quitte":
                        ferme_fenetre()
                        
                    mise_a_jour()
        
        # Si on a cliqué sur un des boutons en bas de la grille   
        else: 
            x, y = abscisse(ev), ordonnee(ev)
            if (0 < x < largeur//2) and (hauteur + taille_case < y < hauteur + 2*taille_case): # Bouton Résoudre
                affiche_solveur = solveur_graphique(largeur, hauteur)
                mise_a_jour()
                solution = set()
                solution = solveur(grille_hitori, solution, 0, 0, affiche_solveur)
                if solution == None:
                    texte(largeur//2,
                          hauteur//2,
                          chaine = "Pas de solution", couleur = "red", ancrage = "center", taille = largeur//12)
                
                else:
                    efface("cases_noires")
                    for case in solution:
                        rectangle(case[1]*taille_case,
                                  case[0]*taille_case,
                                  (case[1]+1)*taille_case,
                                  (case[0]+1)*taille_case,
                                  remplissage = "black", tag = "cases_noires")
                    afficher_nombre(len(grille_hitori), len(grille_hitori[0]), grille_hitori)
                    texte(largeur//2,
                          hauteur//2,
                          chaine = "Victoire !", couleur = "red", ancrage = "center", taille = largeur//6)
                affichage_recommencer(largeur, hauteur)
                    
                # Rentre dans la boucle pour nous permettre de faire rejouer une partie ou quitter
                while True:
                    ev = donne_ev()
                    tev = type_ev(ev)
                    
                    if tev == "ClicGauche":
                        if hauteur + taille_case < ordonnee(ev) < hauteur + 2*taille_case:
                            ferme_fenetre()
                            # On relance la fenêtre du menu, puis on réinitialise les variables de base
                            grille_hitori = menu_niveaux()
                            afficher_grille(grille_hitori)
                            hauteur, largeur, = len(grille_hitori)*taille_case, len(grille_hitori[0])*taille_case
                            cases_noircies, cases_cercles = set(), set()
                            historique_precedent = []
                            historique_suivant = []
                            break
                            
                        elif ordonnee(ev) > hauteur + 2*taille_case:
                            ferme_fenetre()
                        
                    if tev == "Quitte":
                        ferme_fenetre()
                        
                    mise_a_jour()
                
            elif (largeur//2 < x < 3*largeur//4) and (hauteur + taille_case < y < hauteur + 2*taille_case) and len(historique_precedent) > 0: # Bouton Précédent (<-)
                action_precedente(historique_precedent, historique_suivant, cases_noircies)
                afficher_nombre(len(grille_hitori), len(grille_hitori[0]), grille_hitori)
                etat_partie(grille_hitori, cases_noircies)
                fleche_historique(historique_precedent, historique_suivant)
                
            elif (3*largeur//4 < x < largeur) and (hauteur + taille_case < y < hauteur + 2*taille_case) and len(historique_suivant) > 0: # Bouton Suivant (->)
                action_suivante(historique_precedent, historique_suivant, cases_noircies)
                afficher_nombre(len(grille_hitori), len(grille_hitori[0]), grille_hitori)
                etat_partie(grille_hitori, cases_noircies)
                fleche_historique(historique_precedent, historique_suivant)
                
            elif (0 < x < largeur//2) and (hauteur + 2*taille_case < y < hauteur + 3*taille_case): # Bouton Recommencer
                ferme_fenetre()
                # On relance la fenêtre du menu, puis on réinitialise les variables de base
                grille_hitori = menu_niveaux()
                afficher_grille(grille_hitori)
                hauteur, largeur, = len(grille_hitori)*taille_case, len(grille_hitori[0])*taille_case
                cases_noircies, cases_cercles = set(), set()
                historique_precedent = []
                historique_suivant = []
                fleche_historique(historique_precedent, historique_suivant)
                
            elif (largeur//2 < x < largeur) and (hauteur + 2*taille_case < y < hauteur + 3*taille_case): # Bouton Quitter
                quitter_jeu(largeur, hauteur)    
    
    
    # On quitte la fenêtre
    if tev == "Quitte":
        quitter_jeu(largeur, hauteur)              

    mise_a_jour()