/*
 * bdd.h
 *
 *  Created on: Jun 12, 2017
 *      Author: colin
 */

#ifndef BDD_H_
#define BDD_H_
#include "config.h"
/****************************************************
 Nom : store_values
 Description : Save stats into a file
 Valeur retournée : 
 Paramètre en entrée : char *file_name, stats statistique[JOINT]
 Paramètre en entrée / sortie :
 Paramètres en sortie : 
 Auteur : Colin Roubaud
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
int store_values(char *file_name,stats statistique[JOINT]);
/****************************************************
 Nom : restore_values
 Description : Take stats value from a file
 Valeur retournée : 
 Paramètre en entrée : char *file_name
 Paramètre en entrée / sortie : stats *statistique
 Paramètres en sortie : 
 Auteur : Colin Roubaud
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
int restore_values(char *file_name, stats *statistique);

#endif /* BDD_H_ */
