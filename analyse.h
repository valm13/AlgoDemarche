#ifndef ANALYSE_H
#define ANALYSE_H
#include "matrice.h"
#include "config.h"

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

/****************************************************
 Nom : rgbToHsv
 Description : Turn RGB to HSV
 Valeur retournée : image
 Paramètre en entrée :troimat t
 Paramètre en entrée / sortie : 
 Paramètres en sortie : image
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
image rgbToHsv(troimat t);
/****************************************************
 Nom : chargeImage
 Description : Load a picture
 Valeur retournée : 
 Paramètre en entrée :char nomFichier[11]
 Paramètre en entrée / sortie : DonneesImageRGB **img
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void chargeImage(char nomFichier[11],DonneesImageRGB **img);
/****************************************************
 Nom : determineMaxColor
 Description : Determine which is the max value between RGB and save the correspondent color
 Valeur retournée : 
 Paramètre en entrée :int bleu,int vert,int rouge
 Paramètre en entrée / sortie : determ *det
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void determineMaxColor(int bleu,int vert,int rouge,determ *det);
/****************************************************
 Nom : determineMinColor
 Description : Determine which is the min value between R,G,B and save the correspondent color
 Valeur retournée : 
 Paramètre en entrée :int bleu,int vert,int rouge
 Paramètre en entrée / sortie : determ *det
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void determineMinColor(int bleu,int vert,int rouge,determ *det);
/****************************************************
 Nom : calculS
 Description : Calculate the saturation
 Valeur retournée : int
 Paramètre en entrée :determ det
 Paramètre en entrée / sortie :
 Paramètres en sortie : int
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
int calculS(determ det);
/****************************************************
 Nom : calculH
 Description : Calculate the hue
 Valeur retournée : int
 Paramètre en entrée :determ det,int r,int g,int b
 Paramètre en entrée / sortie :
 Paramètres en sortie : int
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
int calculH(determ det,int r,int g,int b);
/****************************************************
 Nom : ChangePixCouleurImg
 Description : Get info of the color joint on a picture
 Valeur retournée : 
 Paramètre en entrée :image p
 Paramètre en entrée / sortie : int color[HAUTEUR][LARGEUR]
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void ChangePixCouleurImg(image p,int color[HAUTEUR][LARGEUR]);
/****************************************************
 Nom : identifieColor
 Description : Identify the position of the pixel of coloured joints
 Valeur retournée : 
 Paramètre en entrée :image tp,int z
 Paramètre en entrée / sortie : jointure pic[NBIMAGE
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void identifieColor(image tp,jointure pic[NBIMAGE],int z);
/****************************************************
 Nom : initialiseTabPoint
 Description : Set the jointure to 0
 Valeur retournée : 
 Paramètre en entrée :int z
 Paramètre en entrée / sortie : jointure pic[NBIMAGE]
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void initialiseTabPoint(jointure pic[NBIMAGE],int z);
/****************************************************
 Nom : sommePointJoint
 Description : Identify the center of a joint for  each joint
 Valeur retournée : 
 Paramètre en entrée :
 Paramètre en entrée / sortie : jointure *pic
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void sommePointJoint(jointure *pic);

#endif
