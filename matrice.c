#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "toolbox.h"
#include "libISEN/GfxLib.h"
#include "libISEN/BmpLib.h"
#include "matrice.h"
#include "analyse.h"

//~ int main(int argc, char **argv)
//~ {
	//~ static DonneesImageRGB *image = NULL;
	//~ static DonneesImageRGB imageret;
	//~ static char nomImage[11];
	//~ static troimat t;
	//~ strcpy(nomImage,"Pictures/Basique.bmp"); 
	//~ printf("\nChargement de l'image\n");
	//~ chargeImage(nomImage,&image); 
	//~ t=cree3matrices(*image);
	//~ affiche_3mat(t,*image);
	//~ matricesVersImage(t,&imageret);
	//~ ecrisBMPRGB_Dans(&imageret,"BasiqueTransf.bmp");
	//~ creeImage(&imageret,"BasiqueTransf.bmp");
	
	
	//~ return 0;
//~ }

troimat cree3matrices(DonneesImageRGB *img)
{
	troimat t;
	for(int i = 0; i < img->hauteurImage; i++)
	{
		for(int j = 0; j < img->largeurImage; j++)
		{
			t.b[i][j]=img->donneesRGB[3*(i*img->largeurImage+j)];
			t.v[i][j]=img->donneesRGB[3*(i*img->largeurImage+j)+1];
			t.r[i][j]=img->donneesRGB[3*(i*img->largeurImage+j)+2];
		}
		
	}
	//~ printf("%d\n",t.b[550][555]);
	//~ printf("%d\n",t.v[550][555]);
	//~ printf("%d\n",t.r[550][555]);
	return t;
}

void affiche_3mat(troimat t, DonneesImageRGB img)
{
	for(int i = 0; i < HAUTEUR; i++)
	{
		printf("\n");
		for(int j = 0; j < LARGEUR; j++)
		{
			printf("%d\n",t.b[i][j]+t.v[i][j]+t.r[i][j]);
		}
		
	}
}
 
void matricesVersImage(troimat t,DonneesImageRGB *imgret)
{
	
	imgret->hauteurImage=HAUTEUR;
	imgret->largeurImage=LARGEUR;
	imgret->donneesRGB=malloc(imgret->hauteurImage * imgret->largeurImage * sizeof(char) * 3);
	
	for(int i = 0; i < HAUTEUR; i++)
	{
		for(int j = 0; j < LARGEUR; j++)
		{
			imgret->donneesRGB[3*(i * imgret->largeurImage + j)] = t.b[i][j];
			imgret->donneesRGB[3*(i * imgret->largeurImage + j) + 1] = t.v[i][j];
			imgret->donneesRGB[3*(i * imgret->largeurImage + j) + 2] = t.r[i][j];
		}
		
	}
}

void creeImage(DonneesImageRGB *imgret, char nomFichier[11])
{
		ecrisBMPRGB_Dans(imgret,nomFichier);
}
