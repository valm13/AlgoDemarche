#ifndef COLOR_H
#define COLOR_H

typedef struct
{
	int r;
	int g;
	int b;
}color;

void change_current_color (color new_color);
void change_current_color_to_complementary (color new_color);

#endif