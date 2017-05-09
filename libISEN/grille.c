#include <stdlib.h>
#include <stdio.h>
#include "toolbox.h"
#include "grille.h"
#include "button.h"
#include "text_area.h"

int init_grille (struct grille_struct *new_grille, int nb_line, int nb_column)
{
	new_grille->pt_table = calloc(nb_line * nb_column, sizeof(void*));
	new_grille->type_table = calloc(nb_line * nb_column, sizeof(enum type));
	new_grille->column = nb_column;
	new_grille->line = nb_line;

	if (new_grille->pt_table == NULL || new_grille->type_table == NULL)
	{
		fprintf(stderr, "error, memory is full\n");
		return -1;
	}

	for (int y = 0; y < nb_line; ++y)
	{
		for (int x = 0; x < nb_column; ++x)
		{
			new_grille->type_table[y * nb_column + x] = none_use;
//			printf(" case %d\n", y * nb_column + x);
		}
	}

	return 0;
}

void grille_change_coordinates (struct grille_struct * grille, int x, int y, int width, int height)
{
	int cell_width;
	int cell_height;
	grille->x = x;
	grille->y = y;
	grille->width = width;
	grille->height = height;
	cell_width = grille->width / grille->column - 2;
	cell_height = grille->height / grille->line - 2;
	if(grille->column != 0 && grille->line != 0)
	{
		for (int i = 0; i < grille->line; ++i)
		{
			for(int u = 0; u < grille->column; ++u)
			{
				switch(grille->type_table[i * grille->column + u])
				{
					case none_use:
						break;
					case button:
//						printf("change coordinate for case : %4d \t", i * grille->column + u);
						button_change_coordinates((struct button_struct*)grille->pt_table[i * grille->column + u], (width * u) / grille->column + x + 1, y - (height * i) / grille->line - 1, cell_width, cell_height);
						break;
					case text_area:
						text_area_change_coordinates((text_area_struct*)grille->pt_table[i * grille->column + u], width * u / grille->column  + x + 1, y - height * i / grille->line - 1, cell_width, cell_height);
						break;
					case grille_type:
						grille_change_coordinates((struct grille_struct*)grille->pt_table[i * grille->column + u], width * u / grille->line + x + 1 , y - height * i / grille->column - 1, cell_width, cell_height);
						break;
				}
			}
		}
	}
}

int grille_remplace_object (struct grille_struct *grille, int line, int column, void *object, int type)
{
	if (line >= grille->line || column >= grille->column)
	{
		return -1;
	}
	if (type > grille_type)
	{
		return -2;
	}
	grille->pt_table[line * grille->column + column] = object;
	grille->type_table[line * grille->column + column] = type;
	return 0;
}

void* grille_select_object (struct grille_struct grille, int column, int line, int type)
{
	if (line >= grille.line || column >= grille.column)
	{
		return NULL;
	}
	if (grille.type_table[line * grille.column + column] == type)
		return grille.pt_table[line * grille.column + column];
	return NULL;
}
