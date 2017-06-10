#ifndef ANALYSE_H
#define ANALYSE_H
#include "matrice.h"
#define JOINT 5	// Jointures des articulation Main Coude Pied Epaule Genoux
#define MAXPIXJOINT 480000	// Jointures des articulation

typedef struct image{
	int h[HAUTEUR][LARGEUR],s[HAUTEUR][LARGEUR],v[HAUTEUR][LARGEUR]; // Repere HSV	H: Hue	S: Saturation	V: Value
}image;

typedef struct infocoul{
	int c; // 1=Bleu	2=Vert	3=Rouge
	int v; // Valeur
}infocoul;

typedef struct determ{
	infocoul min,max; // Valeur Min et Max + Info sur la couleur correspondante
}determ;

typedef struct pos{
	int x,y;
}pos;
typedef struct info{
	pos position[MAXPIXJOINT]; // y puis x
	int nb;
	pos centre;
}info;

typedef struct jointure{
	info j[JOINT];
	
}jointure;


image rgbToHsv(troimat t);

void chargeImage(char nomFichier[11],DonneesImageRGB **img);

void determineMaxColor(int bleu,int vert,int rouge,determ *det);
void determineMinColor(int bleu,int vert,int rouge,determ *det);

int calculS(determ det);
int calculH(determ det,int r,int g,int b);


void ChangePixCouleurImg(image p,int color[HAUTEUR][LARGEUR]);
jointure identifieColor(image tp,DonneesImageRGB *img);
void initialiseTabPoint(jointure *t);
void sommePointJoint(jointure *t);

#endif
