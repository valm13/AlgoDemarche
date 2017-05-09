#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include "BmpLib.h"
#include "color.h"

struct state_property
{
	color text_color;
	color button_color;
	DonneesImageRGB *pic;
	char name[10];
};

struct button_struct
{
	int x;
	int y;
	int height;
	int width;

	int state;
	bool state_changed;
	bool over;
	bool press;

	bool active;
	bool clickable;
	int nb_states;

	int text_size;

	struct state_property *states_prop;
};


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : init_button                                                   */
/* Description : initialyse structure                                      */
/* Input :                                                                 */
/*             * text_size : the size in px of the text                    */
/* Input/ouput :                                                           */
/*             * new_button : pointer to the button struct to initialyse   */
/* Output : no                                                             */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void init_button(struct button_struct *new_button, int text_size);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_print_event                                            */
/* Description : display the button on screen                              */
/* Input :                                                                 */
/*             * new_button : the size in px of the text                   */
/* Input/ouput : no                                                        */
/* Output : no                                                             */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void button_print_event(struct button_struct button);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_mouse_event                                            */
/* Description : take mouse event and save new button state                */
/* Input : no                                                              */
/* Input/ouput :                                                           */
/*             * button : the button for whitch one test the mouse event   */
/* Output : no                                                             */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void button_mouse_event(struct button_struct *button);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_change_coordinates                                     */
/* Description : change coordinate of the button to the wanted coordinate  */
/* Input :                                                                 */
/*             * x : the new position of the button in x in px             */
/*             * y : the new position of the button in y in px             */
/*             * height : the new height of the button in px               */
/*             * width : the new width of the button in px                 */
/* Input/ouput :  no                                                       */
/* Output :                                                                */
/*             * button : the button for whitch one we change coordinate   */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void button_change_coordinates(struct button_struct *button, int x, int y, int height, int width);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_change_name                                            */
/* Description : change name of the button                                 */
/* Input :                                                                 */
/*             * name : the new name of the button                         */
/* Input/ouput :  no                                                       */
/* Output :                                                                */
/*             * button : the button for whitch one we change name         */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void button_change_name(struct button_struct *button, int state_id, char* name);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_state                                                  */
/* Description : return the current state of the button                    */
/* Input :                                                                 */
/*             * button : the button to check                              */
/* Input/ouput :  no                                                       */
/* Output :                                                                */
/*             * return value : the state of the button                    */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int button_state(struct button_struct button);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_state                                                  */
/* Description : return the current state of the button                    */
/* Input :                                                                 */
/*             * button : the button to check                              */
/* Input/ouput :  no                                                       */
/* Output :                                                                */
/*             * return value : if the cursor is over the button           */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 march 2017 17:20                                          */
/* Update : 22 march 2017 17:20                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool button_over(struct button_struct button);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_state                                                  */
/* Description : change name of the button                                 */
/* Input :                                                                 */
/*             * button : the button for which one we want know state      */
/* Input/ouput :  no                                                       */
/* Output :                                                                */
/*             * return value : the state of the button                    */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool button_state_changed(struct button_struct button);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_make_active                                            */
/* Description : make the button active                                    */
/* Input : no                                                              */
/* Input/ouput :                                                           */
/*             * button : the button to active                             */
/* Output : no                                                             */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void button_make_active(struct button_struct *button);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_make_unactive                                          */
/* Description : make the button unactive                                  */
/* Input : no                                                              */
/* Input/ouput :                                                           */
/*             * button : the button to unactive                           */
/* Output : no                                                             */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void button_make_unactive(struct button_struct *button);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_make_clickable                                            */
/* Description : make the button clickable                                    */
/* Input : no                                                              */
/* Input/ouput :                                                           */
/*             * button : the button to active                             */
/* Output : no                                                             */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void button_make_clickable(struct button_struct *button);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_make_unclickable                                          */
/* Description : make the button unclickable                                  */
/* Input : no                                                              */
/* Input/ouput :                                                           */
/*             * button : the button to unactive                           */
/* Output : no                                                             */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void button_make_unclickable(struct button_struct *button);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_change_state                                           */
/* Description : force the state of one button                             */
/* Input :                                                                 */
/*             * state : the new state of the button                       */
/* Input/ouput :                                                           */
/*             * button : the button to change state                       */
/* Output : no                                                             */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void button_change_state(struct button_struct *button, int state);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Funtion : button_change_state                                           */
/* Description : force the state of one button                             */
/* Input :                                                                 */
/*             * state : the new state of the button                       */
/* Input/ouput :                                                           */
/*             * button : the button to change state                       */
/* Output : no                                                             */
/* Autor : Colin ROUBAUD                                                   */
/* Creation : 22 November 2017 17:20                                       */
/* Update : 01 March 2017 21:00                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void button_add_state(struct button_struct *button, struct state_property new_state);



#endif // BUTTON_H
