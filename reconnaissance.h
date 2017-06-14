#ifndef RECO_H
#define RECO_H
#include "analyse.h"

typedef struct hull{
	int min,max;
}hull;

typedef struct stats{
	int lenght;
	posf mean;
	posf devia;
	hull h;
}stats;
int carre(int a);
void calcMeanValue(info xy,stats *s);
void calcDeviaValue(info xy, stats *s);
void calcLenght(info xy, stats *s);
void calcMinMax(info xy, stats *s);

#endif
