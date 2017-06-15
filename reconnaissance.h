#ifndef RECO_H
#define RECO_H
#include "analyse.h"

#define NBPOURCENT 7
void apprentissage(jointure j[NBIMAGE],stats s[JOINT],int id);
int reconnaissance(jointure j[NBIMAGE]);

void calcStats(jointure xy[NBIMAGE], stats s[JOINT],int jointactive);
int carre(int a);
void calcMeanValue(jointure xy[NBIMAGE],stats *s,int jointactive);
void calcDeviaValue(jointure xy[NBIMAGE], stats *s,int jointactive);
void calcLenght(jointure xy[NBIMAGE], stats *s,int jointactive);
void calcMinMax(jointure xy[NBIMAGE], stats *s,int jointactive);

float pourcentage(int ref,int test);
float pourcentagef(float ref,float test);
void calcTabPourc(stats ref[JOINT], stats test[JOINT],float T[JOINT][7]);
void identifieCourbe(float T[JOINT][NBPOURCENT],int TabCorrect[JOINT]);
#endif
