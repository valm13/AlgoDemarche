#ifndef MATRICE_H
#define MATRICE_H
#include "config.h"

typedef struct troimat{
	int r[HAUTEUR][LARGEUR];
	int v[HAUTEUR][LARGEUR];
	int b[HAUTEUR][LARGEUR];
}troimat;

troimat cree3matrices(DonneesImageRGB *img);
void affiche_3mat(troimat t, DonneesImageRGB img);
void matricesVersImage(troimat t,DonneesImageRGB *imgret);
void creeImage(DonneesImageRGB *imgret, char nomFichier[11]);
#endif
