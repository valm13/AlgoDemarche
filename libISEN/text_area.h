#ifndef TEXT_AREA
#define TEXT_AREA
#include "color.h"
typedef struct 
{
	int x;
	int y;
	int height;
	int width;

	char name[100];

	int text_size;

	color background_color;
	color active_color;
	color text_color;
}text_area_struct;

void init_text_area(text_area_struct *new_text_area, int text_size, int background_r, int background_g, int background_b);
void text_area_change_coordinates(text_area_struct *text_area, int x, int y, int width, int height);
void text_area_change_name(text_area_struct *text_area, char* name);
void text_area_print_event(text_area_struct text_area);

#endif //TEXT_AREA