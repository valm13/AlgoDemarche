#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "reconnaissance.h"
#include "bdd.h"

void apprentissage(jointure j[NBIMAGE],stats s[JOINT],int id)
{
	char fileName[10];
	for(int i=0;i<JOINT;i++)
	{
		calcStats(j,s,i);
	}
	sprintf(fileName,"%d",id);
	store_values(fileName,s);
}

int reconnaissance(jointure j[NBIMAGE])
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
	for(int jointactive=0;jointactive<JOINT;jointactive++)
	calcStats(j,test,jointactive);
	
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

void calcStats(jointure xy[NBIMAGE], stats s[JOINT],int jointactive) // Calcule les statistiques d'une courbe, le faire directement sur JOINT courbe ? dans ce cas il faudrait un tableau de stats.
{
		printf("Courbe n°%d\n",jointactive+1);
		printf("\nCalcul de la valeur moyenne :\t");
		calcMeanValue(xy,&(s[jointactive]),jointactive);
		printf("FAIT\n");
		
		printf("Calcul de l'écart type :\t");
		calcDeviaValue(xy,&(s[jointactive]),jointactive);
		printf("FAIT\n");
		
		printf("Calcul de la longueur :\t");
		calcLenght(xy,&(s[jointactive]),jointactive);
		printf("FAIT\n");
		
		printf("Calcul du Min et du Max :\t");
		calcMinMax(xy,&(s[jointactive]),jointactive);
		printf("FAIT\n");
}

void calcMeanValue(jointure xy[NBIMAGE],stats *s,int jointactive) // Somme de toutes les x et de tous les y.
{
	s->mean.x = 0;
	s->mean.y = 0;
	for(int i = 0;i < NBIMAGE;i++)
	{
		s->mean.x += xy[i].j[jointactive].centre.x;
		s->mean.y += xy[i].j[jointactive].centre.y;
	}
	s->mean.x = s->mean.x /	NBIMAGE;
	s->mean.y = s->mean.y /	NBIMAGE;
}

void calcDeviaValue(jointure xy[NBIMAGE], stats *s,int jointactive) // Calcul de l'écart type
{
	posf transit;
	transit.x = 0; //Initialisation des valeurs de transition pour les calculs des sommes.
	transit.y = 0;
	s->devia.x = 0;
	s->devia.y = 0;
	for(int i = 0;i < NBIMAGE;i++)
	{
		transit.x += (xy[i].j[jointactive].centre.x - s->mean.x) * (xy[i].j[jointactive].centre.x - s->mean.x);
		transit.y += (xy[i].j[jointactive].centre.y - s->mean.y) * (xy[i].j[jointactive].centre.y - s->mean.y);
	}
	s->devia.x = sqrtf((float)transit.x / NBIMAGE);
	s->devia.y = sqrtf((float)transit.y / NBIMAGE);	
}

int carre(int a)
{
	return a * a;
}
void calcLenght(jointure xy[NBIMAGE], stats *s,int jointactive)
{
	s->lenght += 0;
	for(int i = 0;i < NBIMAGE-1;i++) // Le -1 sinon on va dépasser le tableau (prendre le n+1 de x et y qui n'existe pas !)
	{
			s->lenght += sqrtf(carre(xy[i].j[jointactive].centre.x - xy[i+1].j[jointactive].centre.x)
			+ carre(xy[i].j[jointactive].centre.y - xy[i+1].j[jointactive].centre.y));
	}
}

void calcMinMax(jointure xy[NBIMAGE], stats *s,int jointactive)
{
	s->h.min = xy[4].j[jointactive].centre.y;
	s->h.max = xy[4].j[jointactive].centre.y;
	for(int i = 1;i < NBIMAGE;i++) 
	{
		if(s->h.min > xy[i].j[jointactive].centre.y)
		s->h.min = xy[i].j[jointactive].centre.y;
		if(s->h.max < xy[i].j[jointactive].centre.y)
		s->h.max = xy[i].j[jointactive].centre.y;
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
