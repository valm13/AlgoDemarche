#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "libISEN/BmpLib.h"
#include "matrice.h"
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

image rgbToHsv(troimat t) //Pour 1 photo
{
	image tp; //tableau de h s v
	determ det;

	for(int i = 0; i < HAUTEUR; i++)
	{
		
		for(int j = 0; j < LARGEUR; j++)
		{
			determineMinColor(t.b[i][j],t.v[i][j],t.r[i][j],&det);	// Determine le max et le min pour effectuer les calculs de H S et V
			determineMaxColor(t.b[i][j],t.v[i][j],t.r[i][j],&det);

			tp.h[i][j]=calculH(det,t.r[i][j],t.v[i][j],t.b[i][j]); // Rentre les valeurs de H S et V dans un tableau de pixel(une image)
			tp.s[i][j]=calculS(det);
			tp.v[i][j]=(det.max.v*100)/255;		
		}
	}
	return tp;
}

void determineMinColor(int bleu,int vert,int rouge,determ *det)
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

void determineMaxColor(int bleu,int vert,int rouge,determ *det)
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

int calculS(determ det)
{
	if(det.max.v==0)
	return 0;
	else
	return 1-(det.min.v/det.max.v);

}

int calculH(determ det,int r,int g,int b)
{
	int offset=10;
	if(abs(r-g)<=offset && abs(r-b)<=offset &&  abs(g-b)<=offset)
	{
		return -100;
	}
	if(det.max.v==det.min.v)
	{
		return 0;
	}
	else if(det.max.c==3) // r
	{
		return (int)(60*((float)(g-b)/(det.max.v-det.min.v))+360)%360;
	}
	else if(det.max.c==2) // v
	{
		return 60*((float)(b-r)/(det.max.v-det.min.v))+120;
	}
	else if(det.max.c==1) // b
	{
		return 60*((float)(r-g)/(det.max.v-det.min.v))+240;
	}
	else
	return -1;
}




void ChangePixCouleurImg(image t,int color[HAUTEUR][LARGEUR])
{
	int offset = 4;
	int target[JOINT] = { 82, 330, 207 ,35, 273 };
	for(int i = 0; i < HAUTEUR; i++)
		{

			for(int j = 0; j < LARGEUR; j++)
			{
				color[i][j]= -1; 
				for(int u=0;u<JOINT;u++)
				{
					if(t.h[i][j] < target[u] + offset && t.h[i][j] > target[u] - offset)
					{
						color[i][j]= u;
					}
				}
			}
		}	
}

void identifieColor(image tp,jointure pic[NBIMAGE],int z)
{
		
		int color[HAUTEUR][LARGEUR];	// Couleur détectée
		int casetab[JOINT]={0}; //	Case du tableau de la position de x et y | il s'incremente donc !
		initialiseTabPoint(pic,z); // Initialise les cases du tableau à 0
		ChangePixCouleurImg(tp,color);
		for(int i = 0; i < HAUTEUR; i++)
		{
			for(int j = 0; j < LARGEUR; j++)
			{
				for(int k = 0;k<JOINT;k++)
				{
					if(color[i][j]==k)
					{
						pic[z].j[k].position[casetab[k]].y=i;	
						pic[z].j[k].position[casetab[k]].x=j;
						casetab[k]++;
						pic[z].j[k].nb++;
					}
				}
			}	
		}
}

void initialiseTabPoint(jointure pic[NBIMAGE],int z)
{
	for(int i=0;i<JOINT;i++)
	{	
		pic[z].j[i].nb=0;
		for(int j=0;j<MAXPIXJOINT;j++)
		{
			pic[z].j[i].position[j].x=0;
			pic[z].j[i].position[j].y=0;
		}
	}
}

void sommePointJoint(jointure *pic) // Trouve les coordonnées du centre des cercle (jointure)
{
	int i,h,j;
	int som_x;
	int som_y;
	int tmp_lenght;
	
	for(h=0;h<JOINT;h++)
	{
		som_x=0;
		som_y=0;
		for(i=0;i<pic->j[h].nb;i++)
		{
			som_x += pic->j[h].position[i].x;
			som_y += pic->j[h].position[i].y;
		}
		if(pic->j[h].nb > 500)
		{
			pic->j[h].centre.x=som_x/pic->j[h].nb;
			pic->j[h].centre.y=som_y/pic->j[h].nb;som_x=0;
			som_y=0;
			tmp_lenght = 0;
			for(j=0;j<pic->j[h].nb;j++)
			{
				if (BETWEEN(pic->j[h].position[j].x, pic->j[h].centre.x - CIRCLE_RADIUS, pic->j[h].centre.x + CIRCLE_RADIUS))
				{
					som_x += pic->j[h].position[j].x;
					som_y += pic->j[h].position[j].y;
					tmp_lenght ++;
				}
			}
//			printf("lenght %d \n", tmp_lenght);
			if(tmp_lenght > 500)
			{
				pic->j[h].centre.x=som_x/tmp_lenght;
				pic->j[h].centre.y=som_y/tmp_lenght;
			}
			else
			{
				pic->j[h].centre.x=0;
				pic->j[h].centre.y=0;
			}
		}
		
	}
	
}
