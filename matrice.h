#ifndef MATRICE_H
#define MATRICE_H
#include "config.h"
#include "libISEN/BmpLib.h"

typedef struct troimat{
	int r[HAUTEUR][LARGEUR];
	int v[HAUTEUR][LARGEUR];
	int b[HAUTEUR][LARGEUR];
}troimat;

/****************************************************
 Nom : cree3matrices
 Description : Create 3 Matrice 2D with BGR color
 Valeur retournée : troimat
 Paramètre en entrée : DonneesImageRGB *img
 Paramètre en entrée / sortie :
 Paramètres en sortie : troimat
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
troimat cree3matrices(DonneesImageRGB *img);
/****************************************************
 Nom : affiche_3mat
 Description : Display the Troimat
 Valeur retournée : void
 Paramètre en entrée : troimat t
 Paramètre en entrée / sortie : 
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void affiche_3mat(troimat t);
/****************************************************
 Nom : matricesVersImage
 Description : Take the data from the troimat
 Valeur retournée : void
 Paramètre en entrée : troimat t
 Paramètre en entrée / sortie : DonneesImageRGB *imgret
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void matricesVersImage(troimat t,DonneesImageRGB *imgret);
/****************************************************
 Nom : creeImage
 Description : Create an image
 Valeur retournée : void
 Paramètre en entrée : char nomFichier[11]
 Paramètre en entrée / sortie : DonneesImageRGB *imgret
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void creeImage(DonneesImageRGB *imgret, char nomFichier[11]);
#endif
