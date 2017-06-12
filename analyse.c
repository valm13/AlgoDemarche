#include <stdio.h>
#include <stdlib.h>
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
	int offset = 10;
	int target[JOINT] = {0,50,120,180,205};
	for(int i = 0; i < HAUTEUR; i++)
		{

			for(int j = 0; j < LARGEUR; j++)
			{
				for(int u=0;u<5;u++)
				{
					color[i][j]= -1; 
					if(t.h[i][j] < target[u] + offset && t.h[i][j] > target[u] - offset)
					{
						printf("u=%d\n",u);
						color[i][j]= u; // C'est du rouge
					}
				}
				if((t.h[i][j] < target[0] + offset && t.h[i][j] > target[0] - offset)) 
				{
				color[i][j]= 0; // C'est du rouge
				}
				//~ else if((t.h[i][j] < target[1] + offset && t.h[i][j] > target[1] - offset))
				//~ {
				//~ color[i][j]= 1; // C'est du jaune
				//~ }
				//~ else if((t.h[i][j] < target[2] + offset && t.h[i][j] > target[2] - offset))
				//~ {
				//~ color[i][j]= 2; // C'est du vert
				//~ }
				//~ else if((t.h[i][j] < target[3] + offset && t.h[i][j] > target[3] - offset))
				//~ {
				//~ color[i][j]= 3; // C'est du turquoise
				//~ }
				//~ else if((t.h[i][j] < target[4] + offset && t.h[i][j] > target[4] - offset))
				//~ {
				//~ color[i][j]= 4; // C'est du bleu plus foncé
				//~ }
				//~ else 
				//~ {
				//~ color[i][j]= -1; // Autres couleurs
				//~ printf("autre\n");
				//~ }
			}
		}	
}

void identifieColor(image tp,jointure pic[NBIMAGE],int z)
{
		
		int color[HAUTEUR][LARGEUR];	// Couleur détectée
		int a=0;	// Variable d'incrémentation pour les position des points
		int b=0;
		int c=0;
		int d=0;
		int e=0;
		initialiseTabPoint(pic,z); // Initialise les cases du tableau à 0
		ChangePixCouleurImg(tp,color);
		for(int i = 0; i < HAUTEUR; i++)
		{
			for(int j = 0; j < LARGEUR; j++)
			{
				switch(color[i][j])
				{
					case 0:
					pic[z].j[0].position[a].y=i;	// Rouge
					pic[z].j[0].position[a].x=j;
					a++;
					pic[z].j[0].nb++;
					break;
					
					case 1:
					pic[z].j[1].position[a].y=i;	// Rouge
					pic[z].j[1].position[a].x=j;
					b++;
					pic[z].j[1].nb++;
					break;
					
					case 2:
					pic[z].j[2].position[a].y=i;	// Rouge
					pic[z].j[2].position[a].x=j;
					c++;
					pic[z].j[2].nb++;
					break;
					
					case 3:
					pic[z].j[3].position[a].y=i;	// Rouge
					pic[z].j[3].position[a].x=j;
					d++;
					pic[z].j[3].nb++;
					break;
					
					case 4:
					pic[z].j[4].position[a].y=i;	// Rouge
					pic[z].j[4].position[a].x=j;
					e++;
					pic[z].j[4].nb++;
					break;
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
	int i,h;
	int sommation_x=0;
	int sommation_y=0;
	
	for(h=0;h<JOINT;h++)
	{
		for(i=0;i<pic->j[h].nb;i++)
		{
			sommation_x+=pic->j[h].position[i].x;
			sommation_y+=pic->j[h].position[i].y;
		}
		if(pic->j[h].nb != 0)
		{
			pic->j[h].centre.x=sommation_x/pic->j[h].nb;
			pic->j[h].centre.y=sommation_y/pic->j[h].nb;
		}
		sommation_x=0;
		sommation_y=0;
	}

}
