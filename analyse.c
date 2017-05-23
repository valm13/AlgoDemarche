#include <stdio.h>
#include "BmpLib.h"
#include "analyse.h"
#include "toolbox.h"

void chargeImage(char nomFichier[11],DonneesImageRGB **img)	// Charge une image grâce au nom de celle-ci
{
	*img = lisBMPRGB(nomFichier);
	if((*img == NULL))
	{
		fprintf(stderr, "erreur l'image %s n'a pas pu être charger", nomFichier);
	}
}

void rgbToHsv(DonneesImageRGB *img) //Pour 1 photo
{
	char bleu,vert,rouge;
	int h,s,v;
	tabpixel tp; // Adapter la taille du tableau en dynamique
//	int nbpixel = img->largeurImage*img->hauteurImage;
	determ det;
	for(int i = 0; i < MIN( img->hauteurImage, HAUTEUR); i++)
	{
		for(int j = 0; j < MIN(img->largeurImage, LARGEUR); j++)
		{
			bleu=img->donneesRGB[i * img->largeurImage * 3 + j * 3];
			vert=img->donneesRGB[i * img->largeurImage * 3 + j * 3 + 1];
			rouge=img->donneesRGB[i * img->largeurImage * 3 + j * 3 + 2];
			
			determineMinColor(bleu,vert,rouge,&det);	// Determine le max et le min pour effectuer les calculs de H S et V
			determineMaxColor(bleu,vert,rouge,&det);
			// printf("det.min.c = %d\n",det.min.c);
			// printf("det.max.c = %d\n",det.max.c);
			h=calculH(det,rouge,vert,bleu);
			s=calculS(det);
			v=det.max.v;
			
			tp.p[i][j].h=h;	// Rentre les valeurs de H S et V dans un tableau de pixel(une image)
			tp.p[i][j].s=s;
			tp.p[i][j].v=v;
		}
	}
}

void determineMaxColor(char bleu,char vert,char rouge,determ *det)
{

	if(bleu>=vert && bleu >=rouge)
	{
		det->max.c=1;
		det->max.v=bleu;
	}
	else if(vert>=bleu && vert>=rouge)
	{
		det->max.c=2;
		det->max.v=vert;
	}
	else if(rouge>=vert && rouge >=bleu)
	{
		det->max.c=3;
		det->max.v=rouge;
	}
}

void determineMinColor(char bleu,char vert,char rouge,determ *det)
{

	if(bleu<=vert && bleu <=rouge)
	{
		det->min.c=1;
		det->min.v=bleu;
	}
	else if(vert<=bleu && vert<=rouge)
	{
		det->min.c=2;
		det->min.v=vert;
	}
	else if(rouge<=vert && rouge <=bleu)
	{
		det->min.c=3;
		det->min.v=rouge;
	}
}


//~ void test(DonneesImageRGB *img) // Affichage de toutes les données de l'image
//~ {
	//~ for(int i=0;i<421500;i++) //421500 = NbPixel * 3 (RVB)
	//~ {
		//~ printf("%d\n",img->donneesRGB[i]);
	//~ }
//~ }
//~ void test2(DonneesImageRGB *img) // Filtre Rouge, Vert ou Bleu #PourleFun
//~ {
	//~ for(int i=2;i<421500;i=i+3) //421500 = NbPixel * 3 (RVB)
	//~ {
		//~ img->donneesRGB[i]=255;
	//~ }
//~ }

int calculS(determ det)
{
	if(det.max.v==0)
	return 0;
	else
	return 1-(det.min.v/det.max.v);

}

int calculH(determ det,char r,char g,char b)
{
	if(det.max.v==det.min.v)
	return 0;
	else if(det.max.c==3) // r
	{
		return (60*((g-b)/(det.max.v-det.min.v))+360)%360;
	}
	else if(det.max.c==2) // v
	{
		return 60*((b-r)/(det.max.v-det.min.v))+120;
	}
	else if(det.max.c==1) // b
	{
		return 60*((r-g)/(det.max.v-det.min.v))+240;
	}
	else
	return -1;
}
