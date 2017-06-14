#ifndef RECO_H
#define RECO_H
#include "config.h"
#include "analyse.h"

int carre(int a);
void calcMeanValue(info xy,stats *s);
void calcDeviaValue(info xy, stats *s);
void calcLenght(info xy, stats *s);
void calcMinMax(info xy, stats *s);

#endif
