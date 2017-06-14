#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "reconnaissance.h"

void calcStats(info xy, stats *s)
{
	printf("\nCalcul de la valeur moyenne :\t");
	calcMeanValue(xy,s);
	printf("FAIT\n");
	
	printf("Calcul de l'écart type :\t");
	calcDeviaValue(xy,s);
	printf("FAIT\n");
	
	printf("Calcul de la longueur :\t");
	calcLenght(xy,s);
	printf("FAIT\n");
	
	printf("Calcul du Min et du Max :\t");
	calcMinMax(xy,s);
	printf("FAIT\n");
}
void calcMeanValue(info xy,stats *s) // Somme de toutes les x et de tous les y.
{
	s->mean.x = 0;
	s->mean.y = 0;
	for(int i = 0;i< xy.nb;i++)
	{
		s->mean.x += xy.position[i].x;
		s->mean.y += xy.position[i].y;
	}
	s->mean.x = s->mean.x /	xy.nb;
	s->mean.y = s->mean.y /	xy.nb;
}

void calcDeviaValue(info xy, stats *s) // Calcul de l'écart type
{
	posf transit;
	transit.x = 0; //Initialisation des valeurs de transition pour les calculs des sommes.
	transit.y = 0;
	s->devia.x = 0;
	s->devia.y = 0;
	for(int i = 0;i< xy.nb;i++)
	{
		transit.x += (xy.position[i].x - s->mean.x) * (xy.position[i].x - s->mean.x);
		transit.y += (xy.position[i].y - s->mean.y) * (xy.position[i].y - s->mean.y);
	}
	s->devia.x = sqrtf((float)transit.x / xy.nb);
	s->devia.y = sqrtf((float)transit.y / xy.nb);	
}

int carre(int a)
{
	return a*a;
}
void calcLenght(info xy, stats *s)
{
	s->lenght += 0;
	for(int i=0;i<xy.nb-1;i++) // Le -1 sinon on va dépasser le tableau (prendre le n+1 de x et y qui n'existe pas !)
	{
			s->lenght += sqrtf(carre(xy.position[i].x-xy.position[i+1].x)
			+ carre(xy.position[i].y-xy.position[i+1].y));
	}
}

void calcMinMax(info xy, stats *s)
{
	s->h.min = xy.position[0].y;
	s->h.max = xy.position[0].y;
	for(int i=1;i<xy.nb;i++) 
	{
		if(s->h.min > xy.position[i].y)
		s->h.min = xy.position[i].y;
		if(s->h.max < xy.position[i].y)
		s->h.max = xy.position[i].y;
	}
}
