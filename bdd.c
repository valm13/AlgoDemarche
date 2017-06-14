/*
 * bdd.c
 *
 *  Created on: Jun 12, 2017
 *      Author: colin
 */

#include <stdio.h>
#include <stdlib.h>

#include "bdd.h"

int store_values(char *file_name,stats statistique[JOINT])
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
		fwrite(statistique, sizeof(stats), JOINT, fp);
		fclose(fp);
	}
	return rv;
}
int restore_values(char *file_name,stats statistique[JOINT])
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
		fread(statistique, sizeof(stats), JOINT, fp);
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
