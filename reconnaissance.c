#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "reconnaissance.h"
#include "bdd.h"

void apprentissage(jointure j,stats s[JOINT],int id)
{
	char fileName[10];
	calcStats(j.j,s);
	sprintf(fileName,"%d",id);
	store_values(fileName,j,s);
}

int reconnaissance(info xy[JOINT])
{
	stats test[JOINT];
	stats col[JOINT];
	stats dam[JOINT];
	stats val[JOINT];
	float T1[JOINT][NBPOURCENT];
	float T2[JOINT][NBPOURCENT];
	float T3[JOINT][NBPOURCENT];
	int Correct1[JOINT];
	int Correct2[JOINT];
	int Correct3[JOINT];
	int a = 0;
	int b = 0;
	int c = 0;
	
	calcStats(xy,test);
	calcTabPourc(col,test,T1);
	calcTabPourc(dam,test,T2);
	calcTabPourc(val,test,T3);
	identifieCourbe(T1,Correct1);
	identifieCourbe(T2,Correct2);
	identifieCourbe(T3,Correct3);
	for(int i = 0;i<NBPOURCENT;i++)
	{
		a += Correct1[i];
		b += Correct2[i];
		c += Correct3[i];
	}
	if(a > b && a > c)
	return 1;
	else if(b > a && b > c)
	return 2;
	else if(c > a && c > b)
	return 3;
	else return 0;
}

void calcStats(info xy[JOINT], stats s[JOINT]) // Calcule les statistiques d'une courbe, le faire directement sur JOINT courbe ? dans ce cas il faudrait un tableau de stats.
{
	for(int i = 0;i < JOINT;i++)
	{
		printf("Courbe n°%d\n",i);
		printf("\nCalcul de la valeur moyenne :\t");
		calcMeanValue(xy[i],&(s[i]));
		printf("FAIT\n");
		
		printf("Calcul de l'écart type :\t");
		calcDeviaValue(xy[i],&(s[i]));
		printf("FAIT\n");
		
		printf("Calcul de la longueur :\t");
		calcLenght(xy[i],&(s[i]));
		printf("FAIT\n");
		
		printf("Calcul du Min et du Max :\t");
		calcMinMax(xy[i],&(s[i]));
		printf("FAIT\n");
	}
}

void calcMeanValue(info xy,stats *s) // Somme de toutes les x et de tous les y.
{
	s->mean.x = 0;
	s->mean.y = 0;
	for(int i = 0;i < xy.nb;i++)
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
	for(int i = 0;i < xy.nb;i++)
	{
		transit.x += (xy.position[i].x - s->mean.x) * (xy.position[i].x - s->mean.x);
		transit.y += (xy.position[i].y - s->mean.y) * (xy.position[i].y - s->mean.y);
	}
	s->devia.x = sqrtf((float)transit.x / xy.nb);
	s->devia.y = sqrtf((float)transit.y / xy.nb);	
}

int carre(int a)
{
	return a * a;
}
void calcLenght(info xy, stats *s)
{
	s->lenght += 0;
	for(int i = 0;i < xy.nb-1;i++) // Le -1 sinon on va dépasser le tableau (prendre le n+1 de x et y qui n'existe pas !)
	{
			s->lenght += sqrtf(carre(xy.position[i].x - xy.position[i+1].x)
			+ carre(xy.position[i].y - xy.position[i+1].y));
	}
}

void calcMinMax(info xy, stats *s)
{
	s->h.min = xy.position[0].y;
	s->h.max = xy.position[0].y;
	for(int i = 1;i < xy.nb;i++) 
	{
		if(s->h.min > xy.position[i].y)
		s->h.min = xy.position[i].y;
		if(s->h.max < xy.position[i].y)
		s->h.max = xy.position[i].y;
	}
}

float pourcentage(int ref,int test)
{
	return ((ref - test) / ref) * 100;
}

float pourcentagef(float ref,float test)
{
	return ((ref - test) / ref) * 100;
}

void calcTabPourc(stats ref[JOINT], stats test[JOINT],float T[JOINT][NBPOURCENT])
{
	for(int i = 0;i < JOINT;i++)
	{
		T[i][0] = pourcentagef(ref[i].mean.x,test[i].mean.x);
		T[i][1] = pourcentagef(ref[i].mean.y,test[i].mean.y);
		
		T[i][2] = pourcentagef(ref[i].devia.x,test[i].devia.x);
		T[i][3] = pourcentagef(ref[i].devia.y,test[i].devia.y);
		
		T[i][4] = pourcentage(ref[i].lenght,test[i].lenght);
		
		T[i][5] = pourcentage(ref[i].h.min,test[i].h.min);
		T[i][6] = pourcentage(ref[i].h.max,test[i].h.max);
	}
}

float moyenne(float T[NBPOURCENT])
{
	float f = 0;
	for(int i = 0; i < NBPOURCENT; i++)
	f += T[i];
	return f / NBPOURCENT;
}

void identifieCourbe(float T[JOINT][NBPOURCENT],int TabCorrect[JOINT]) // Return tableau d'entier 0 ou 1
{
	float TabMoy[JOINT];
	float Acceptation[JOINT] = {10,12,10,14,10}; // Pied, Genoux, Main, Coude, Epaule
	
	for(int i = 0;i < JOINT;i++) // Initialise les cases à 0.
	TabCorrect[i] = 0;
	
	for(int i = 0;i < JOINT;i++) // On récupere les moyenne de chaques courbes
	TabMoy[i] = moyenne(T[i]);
	
	for(int i = 0;i < JOINT;i++)
	{
		if(TabMoy[i] < Acceptation[i]) // Si on est sous un certain seuil pour la courbe i, on observe la bonne personne, on met 1.
		TabCorrect[i] = 1;
		else
		TabCorrect[i] = 0;
	}
}
