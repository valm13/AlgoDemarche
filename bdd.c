/*
 * bdd.c
 *
 *  Created on: Jun 12, 2017
 *      Author: colin
 */

#include <stdio.h>
#include <stdlib.h>

#include "bdd.h"

int store_values(char *file_name, jointure donne, stats statistique)
{
	int rv = 0;
	FILE *fp;
	fp = fopen(file_name, "wb");
	if (fp == NULL)
	{
		rv = -1;
	}
	else
	{
		fwrite(&donne, sizeof(jointure), 1, fp);
		fwrite(&statistique, sizeof(stats), 1, fp);
		fclose(fp);
	}
	return rv;
}
int restore_values(char *file_name, jointure *donne, stats *statistique)
{
	int rv = 0;
	FILE *fp;
	fp = fopen(file_name, "wb");
	if (fp == NULL)
	{
		rv = -1;
	}
	else
	{
		fread(donne, sizeof(jointure), 1, fp);
		fread(statistique, sizeof(stats), 1, fp);
	}
	return rv;
}

int flush_person(char *file_name)
{
	char command[500];
	sprintf(command, "rm -f %s", file_name);
	system(command);
	return 1;
}
