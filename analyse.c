#include <stdio.h>
#include "BmpLib.h"
#include "analyse.h"

void chargeImage(char nomFichier[11],DonneesImageRGB **img)
{
	*img = lisBMPRGB(nomFichier);
}

void rgbToHsv(DonneesImageRGB *img) //Pour 1 photo
{
	char bleu,vert,rouge;
	int h,s,v;
	tabpixel tp; // Cause un core-dumped lors de la déclaration du tableau de pixels...
	int nbpixel = img->largeurImage*img->hauteurImage;
	determ det;
	for(int i=0;i<nbpixel;i=i+3)
	{
		printf("pixel numéro %d\n",i/3);
		bleu=img->donneesRGB[i];
		vert=img->donneesRGB[i+1];
		rouge=img->donneesRGB[i+2];
		
		determineMinColor(bleu,vert,rouge,&det);
		determineMaxColor(bleu,vert,rouge,&det);
		printf("det.min.c = %d\n",det.min.c);
		printf("det.max.c = %d\n",det.max.c);
		h=calculH(det,rouge,vert,bleu);
		s=calculS(det);
		v=det.max.v;
		tp.p[i].h=h;
		tp.p[i].s=s;
		tp.p[i].v=v;
		printf("\nPixel numero %d :\nh = %d\ns = %d\nv = %d\n",i,tp.p[i].h,tp.p[i].s,tp.p[i].v);
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
