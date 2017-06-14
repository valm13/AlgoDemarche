/*
 * bdd.h
 *
 *  Created on: Jun 12, 2017
 *      Author: colin
 */

#ifndef BDD_H_
#define BDD_H_
#include "config.h"
int store_values(char *file_name, jointure donne, stats statistique[JOINT]);
int restore_values(char *file_name, stats *statistique);

#endif /* BDD_H_ */
