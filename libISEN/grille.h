#ifndef GRILLE_H
#define GRILLE_H
enum type
{
	none_use,
	button,
	text_area,
	grille_type
};
struct grille_struct
{
	int x, y;
	int width, height;
	int line, column;
	void **pt_table; // this table will contain the poiter how point to the differents object in the table
	enum type *type_table; // this table will contain the type of the objects point by pt table 
};



int init_grille (struct grille_struct *new_grille, int nb_line, int nb_column);
void grille_change_coordinates (struct grille_struct * grille, int x, int y, int width, int height);
int grille_remplace_object (struct grille_struct *grille, int line, int column, void *object, int type);
void free_table (struct grille_struct *grille);
void* grille_select_object (struct grille_struct grille, int line, int column, int type);

#endif
