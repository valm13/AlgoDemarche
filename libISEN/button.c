#include <stdio.h>
#include <stdlib.h>
#include "button.h"
#include "GfxLib.h"
#include "imageSF.h"

void init_button(struct button_struct *new_button, int text_size)
{
	new_button->active = true;
	new_button->state = 0;
	new_button->state_changed = false;
	new_button->clickable = true;

	new_button->text_size = text_size;

	new_button->x = 0;
	new_button->y = 0;
	new_button->height = 0;
	new_button->width = 0;

	new_button->nb_states = 0;
	new_button->states_prop = NULL;
}

void button_print_event(struct button_struct button)
{
	if(button.active == true)
	{
		epaisseurDeTrait(1);
		if(button.state >=0 && button.state < button.nb_states)
		{
			change_current_color(button.states_prop[button.state].button_color);

			if (button.states_prop[button.state].pic != NULL)
			{
				ecrisImageSansFond(button.x, button.y, button.states_prop[button.state].pic->largeurImage,  button.states_prop[button.state].pic->hauteurImage,  button.states_prop[button.state].pic->donneesRGB,(couleur){0,255,0});
			}
			else
			{
				rectangle(button.x, button.y, button.x + button.width, button.y + button.height);
			}

			change_current_color(button.states_prop[button.state].text_color);
			afficheChaine(button.states_prop[button.state].name, button.text_size, button.x + (button.width - tailleChaine(button.states_prop[button.state].name, button.text_size))/2.0, button.y + (button.height - button.text_size)/2 );
		}
		else
		{
			fprintf(stderr, "the button is not correctly initialyse\n");
		}
	}
}
void button_mouse_event(struct button_struct *button)
{
	if(button != NULL)
	{
		if(button->active == true && button->clickable == true)
		{
			if(abscisseSouris() > button->x
				&& abscisseSouris() < (button->x + button->width)
				&& ordonneeSouris() > button->y
				&& ordonneeSouris() < (button->y + button->height))
			{
				if (etatBoutonSouris() == GaucheAppuye && button->press == false)
				{
					button->state ++;
					button->state %= button->nb_states;
					button->state_changed = true;
				}
				else
				{
					button->state_changed = false;
					button->over = true;
				}
				if (etatBoutonSouris() == GaucheAppuye)
				{
					button->press = true;
				}
			}
			else
			{
				button->press = false;
				button->state_changed = false;
				button->over = false;
			}
			if (etatBoutonSouris() == GaucheRelache)
			{
				button->press = false;
			}
		}
		else
		{
			button->state_changed = false;
		}
	}
}
void button_change_coordinates(struct button_struct *button, int x, int y, int width, int height)
{
	button->x = x;
	button->y = y;
	button->height = height;
	button->width = width;
}

void button_change_name(struct button_struct *button, int state_id, char* name)
{
	if(state_id < button->nb_states)
	{
		sprintf(button->states_prop[state_id].name, "%s", name);
	}
	else
	{
		fprintf(stderr,"error : the state %d dont existe on the button %s", state_id, button->states_prop[0].name);
	}
}

int button_state(struct button_struct button)
{
	return button.state;
}

bool button_over(struct button_struct button)
{
	return button.over;
}

bool button_state_changed (struct button_struct button)
{
	return button.state_changed;
}

void button_make_active(struct button_struct *button)
{
	button->active = true;
	
}

void button_make_unactive(struct button_struct *button)
{
	button->active = false;
	button->state_changed = false;
}

void button_make_clickable(struct button_struct *button)
{
	button->clickable = true;

}

void button_make_unclickable(struct button_struct *button)
{
	button->clickable = false;
	button->state_changed = false;
}

void button_change_state(struct button_struct *button, int state)
{
	button->state = state;
}

void button_add_state(struct button_struct *button, struct state_property new_state)
{
	button->nb_states ++;
	button->states_prop = realloc(button->states_prop, sizeof(struct state_property) * button->nb_states);
	button->states_prop[button->nb_states - 1] = new_state;
}
