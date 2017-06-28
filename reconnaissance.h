#ifndef RECO_H
#define RECO_H
#include "analyse.h"

#define NBPOURCENT 7
/****************************************************
 Nom : afficheStats
 Description : Display stats from 1 person
 Valeur retournée : 
 Paramètre en entrée : stats s[JOINT]
 Paramètre en entrée / sortie :
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void afficheStats(stats s[JOINT]);
/****************************************************
 Nom : apprentissage
 Description : Save all the stats of 1 person into a file
 Valeur retournée : 
 Paramètre en entrée : jointure j[NBIMAGE],stats s[JOINT],int id
 Paramètre en entrée / sortie :
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void apprentissage(jointure j[NBIMAGE],stats s[JOINT],int id);
/****************************************************
 Nom : reconnaissance
 Description : Compare the gait of 1 person with the database
 Valeur retournée : 
 Paramètre en entrée : jointure j[NBIMAGE]
 Paramètre en entrée / sortie :
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
int reconnaissance(jointure j[NBIMAGE]);
/****************************************************
 Nom : calcStats
 Description : Calcul the stats for 1 curve( 1 joint)
 Valeur retournée : 
 Paramètre en entrée : jointure xy[NBIMAGE],int jointactive
 Paramètre en entrée / sortie : stats s[JOINT]
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void calcStats(jointure xy[NBIMAGE], stats s[JOINT],int jointactive);
/****************************************************
 Nom : carre
 Description : Calcul the square of a number
 Valeur retournée : int
 Paramètre en entrée : int a
 Paramètre en entrée / sortie :
 Paramètres en sortie : int
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
int carre(int a);
/****************************************************
 Nom : calcMeanValue
 Description : Calcul the mean value of the curve
 Valeur retournée : jointure xy[NBIMAGE],
 Paramètre en entrée : int a,int jointactive
 Paramètre en entrée / sortie : stats *s
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void calcMeanValue(jointure xy[NBIMAGE],stats *s,int jointactive);
/****************************************************
 Nom : calcDeviaValue
 Description : Calcul the deviation value of the curve
 Valeur retournée : 
 Paramètre en entrée : jointure xy[NBIMAGE],int jointactive
 Paramètre en entrée / sortie : stats *s
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void calcDeviaValue(jointure xy[NBIMAGE], stats *s,int jointactive);
/****************************************************
 Nom : calcLenght
 Description : Calcul the length of the curve
 Valeur retournée : jointure xy[NBIMAGE],
 Paramètre en entrée : jointure xy[NBIMAGE],int jointactive
 Paramètre en entrée / sortie : stats *s
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void calcLenght(jointure xy[NBIMAGE], stats *s,int jointactive);
/****************************************************
 Nom : calcMinMax
 Description : Calcul the min and the max of the curve
 Valeur retournée : jointure xy[NBIMAGE],
 Paramètre en entrée : jointure xy[NBIMAGE],int jointactive
 Paramètre en entrée / sortie : stats *s
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void calcMinMax(jointure xy[NBIMAGE], stats *s,int jointactive);
/****************************************************
 Nom : pourcentage
 Description : Calcul a pourcentage of 2 integer
 Valeur retournée : float
 Paramètre en entrée : int ref,int test
 Paramètre en entrée / sortie : 
 Paramètres en sortie : float
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
float pourcentage(int ref,int test);
/****************************************************
 Nom : pourcentagef
 Description : Calcul a pourcentage of 2 float
 Valeur retournée : float
 Paramètre en entrée : int ref,int test
 Paramètre en entrée / sortie : 
 Paramètres en sortie : float
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
float pourcentagef(float ref,float test);
/****************************************************
 Nom : calcTabPourc
 Description : Calcul all pourcentage
 Valeur retournée : 
 Paramètre en entrée : stats ref[JOINT], stats test[JOINT]
 Paramètre en entrée / sortie : float T[JOINT][7]
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void calcTabPourc(stats ref[JOINT], stats test[JOINT],float T[JOINT][7]);
/****************************************************
 Nom : moyenne
 Description : Calculate the mean value of pourcentage
 Valeur retournée : float
 Paramètre en entrée : 
 Paramètre en entrée / sortie : float T[NBPOURCENT]
 Paramètres en sortie : float
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
float moyenne(float T[NBPOURCENT]);
/****************************************************
 Nom : identifieCourbe
 Description : Identify the curve
 Valeur retournée : 
 Paramètre en entrée : float T[JOINT][NBPOURCENT]
 Paramètre en entrée / sortie : int TabCorrect[JOINT]
 Paramètres en sortie : 
 Auteur : Valentin Magnan
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void identifieCourbe(float T[JOINT][NBPOURCENT],int TabCorrect[JOINT]);
#endif
