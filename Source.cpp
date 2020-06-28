#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>				//Our primitive header file
#include <allegro5\allegro_native_dialog.h> 

//Draws a green circle to represent a lollipop
//Param: the location of circle, circle's radius, circle's color
//Return: drawn circle
void draw_filled_circle(int pos_x, int pos_y, ALLEGRO_COLOR color);

//Draws a white line to represent the stick of the lollipop
//Param: first point of line, second point of line, color, thickness of line
//Return: drawn line
void draw_line(int pos_x, int pos_y, ALLEGRO_COLOR color);

int main(void)
{
	ALLEGRO_DISPLAY *Screen = NULL;

	if(!al_init())
	{
		al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	int width=800, height=600;
	Screen = al_create_display(width, height);
	if(Screen == NULL)
	{
		al_show_native_message_box(Screen, "Error!", "Failed to create the display.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
		
	bool done = false;
	int pos_x = width / 2;
	int pos_y = height / 2;

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_EVENT ev;

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();
	
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	while(!done)
	{

		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					pos_y -= 20;
					break;
				case ALLEGRO_KEY_DOWN:
					pos_y += 20;
					break;
				case ALLEGRO_KEY_RIGHT:
					pos_x += 20;
					break;
				case ALLEGRO_KEY_LEFT:
					pos_x -= 20;
					break;
				case ALLEGRO_KEY_U:
					pos_x += -20;
					pos_y -= 20;
					break;
				case ALLEGRO_KEY_D:
					pos_x -= -20;
					pos_y -= -20;
					break;
				case ALLEGRO_KEY_R:
					pos_x += 20;
					pos_y -= 20;
					break;
				case ALLEGRO_KEY_L:
					pos_x -= 20;
					pos_y += 20;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;
		}

		draw_filled_circle(pos_x, pos_y, al_map_rgb(5, 200, 50));
		draw_line(pos_x, pos_y, al_map_rgb(255, 255, 255));

		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(Screen);						//destroy our display object
	system("pause");
	return 0;
}

void draw_filled_circle(int pos_x, int pos_y, ALLEGRO_COLOR color)
{
	int x = pos_x - 25;
	int y = pos_y - 25;
	int r = 30;
	al_draw_filled_circle(x, y, r, color);
}

void draw_line(int pos_x, int pos_y, ALLEGRO_COLOR color)
{
	int px = pos_x - 10;
	int py = pos_y - 10;
	int px2 = pos_x + 75;
	int py2 = pos_y + 75;
	int thickness = 5;
	al_draw_line(px, py, px2, py2, color, thickness);
}
