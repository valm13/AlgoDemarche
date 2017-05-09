#include "color.h"
#include "GfxLib.h"

void change_current_color (color new_color)
{
	couleurCourante(new_color.r, new_color.g, new_color.b);
}

void change_current_color_to_complementary (color new_color)
{
	couleurCourante(255 - new_color.r, 255 - new_color.g, 255 - new_color.b);
}