#include <stdio.h>

#include "GfxLib.h"
#include "text_area.h"

void init_text_area(text_area_struct *new_text_area, int text_size, int background_r, int background_g, int background_b)
{
	text_area_change_name(new_text_area, "");

	new_text_area->text_size = text_size;

	new_text_area->x = 0;
	new_text_area->y = 0;
	new_text_area->height = 0;
	new_text_area->width = 0;

	new_text_area->background_color.r = background_r;
	new_text_area->background_color.g = background_g;
	new_text_area->background_color.b = background_b;
}

void text_area_print_event(text_area_struct text_area)
{
	epaisseurDeTrait(1);
	change_current_color(text_area.background_color);

	rectangle(text_area.x, text_area.y, text_area.x + text_area.width, text_area.y + text_area.height);

	change_current_color_to_complementary(text_area.background_color);
	afficheChaine(text_area.name, text_area.text_size, text_area.x + (text_area.width - tailleChaine(text_area.name, text_area.text_size))/2.0, text_area.y + (text_area.height - 20)/2 );
}

void text_area_change_coordinates(text_area_struct *text_area, int x, int y, int width, int height)
{
	text_area->x = x;
	text_area->y = y;
	text_area->height = height;
	text_area->width = width;
}

void text_area_change_name(text_area_struct *text_area, char* name)
{
	sprintf(text_area->name, "%s", name);
}