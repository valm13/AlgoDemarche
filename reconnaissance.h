#ifndef RECO_H
#define RECO_H
#include "analyse.h"

#define NBPOURCENT 7
void apprentissage(jointure j,stats s[JOINT],int id);
int reconnaissance(info xy[JOINT]);

void calcStats(info xy[JOINT], stats s[JOINT]);
int carre(int a);
void calcMeanValue(info xy,stats *s);
void calcDeviaValue(info xy, stats *s);
void calcLenght(info xy, stats *s);
void calcMinMax(info xy, stats *s);

float pourcentage(int ref,int test);
float pourcentagef(float ref,float test);
void calcTabPourc(stats ref[JOINT], stats test[JOINT],float T[JOINT][7]);
void identifieCourbe(float T[JOINT][NBPOURCENT],int TabCorrect[JOINT]);
#endif
