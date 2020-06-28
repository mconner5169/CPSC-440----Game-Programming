#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>	
#include <stdio.h>

//Creating the color white
//Param: none
//Return: white color
ALLEGRO_COLOR makeColorWhite();

//Creating the color red
//Param: none
//Return: red color
ALLEGRO_COLOR makeColorRed();

//Draws a circle to represent a peppermint
//Param: the location of circle, circle's color
//Return: drawn circle
void draw_filled_circle(int pos_x, int pos_y, ALLEGRO_COLOR color);

//Draws triangles to represent the wrapper
//Param: triangle location and color
//Return: drawn triangle
void draw_filled_triangle(int pos_x, int pos_y, ALLEGRO_COLOR color);

//Draws the outline of the peppermint wrapper specifically for the upper left quadrent
//Param: triangle location and color
//Return: outline of peppermint wrapper
void draw_triangle(int pos_x, int pos_y, ALLEGRO_COLOR color);
int main(void)
{

	ALLEGRO_DISPLAY* Screen = NULL;

	if (!al_init())
	{
		fprintf(stderr, "Error! Allegro has failed to initialize.\n");
		return -1;
	}

	int width = 840, height = 600;
	Screen = al_create_display(width, height);
	if (Screen == NULL)
	{
		fprintf(stderr, "Error! Failed to create the display.\n");
		return -1;
	}

	bool draw = false, done = false;;
	int pos_x = width / 2;
	int pos_y = height / 2;


	ALLEGRO_EVENT_QUEUE* event_queue = NULL;


	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* font20 = al_load_font("segoeprb.ttf", 20, 0);
	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_display_event_source(Screen));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	if (!al_install_mouse()) {
		fprintf(stderr, "Error! Failed to initialize the mouse!\n.");
		return -1;
	}

	al_register_event_source(event_queue, al_get_mouse_event_source());

	//al_hide_mouse_cursor(display);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				draw = true;
				pos_x = ev.mouse.x;
				pos_y = ev.mouse.y;
			}
		}


		if (draw)
		{
			//upper left
			if (pos_x <= 250 && pos_x >= 0 && pos_y >= 0 && pos_y <= 250) {
				//Change backgroud to white and text to black
				al_draw_filled_rectangle(0, 0, 250, 250, al_map_rgb(255, 255, 255)); 
				draw_filled_circle(pos_x, pos_y, makeColorRed());
				draw_triangle(pos_x, pos_y, al_map_rgb(0, 0, 0));
				al_draw_textf(font20, al_map_rgb(0, 0, 0), pos_x, pos_y, ALLEGRO_ALIGN_LEFT, "X: %i Y: %i", pos_x, pos_y);
				al_flip_display();
			}
			//upper right
			else if (pos_x >= 500 && pos_x <= width && pos_y >= 0 && pos_y <= 250) {
				//Change backgound to black and text to white
				al_draw_filled_rectangle(width, 0, 500, 250, al_map_rgb(0, 0, 0));
				draw_filled_circle(pos_x, pos_y, makeColorRed());
				draw_filled_triangle(pos_x, pos_y, makeColorWhite());
				al_draw_textf(font20, al_map_rgb(255, 255, 255), pos_x, pos_y, ALLEGRO_ALIGN_LEFT, "X: %i Y: %i", pos_x, pos_y);
				al_flip_display();
			}
			//lower left
			else if (pos_x <= 250 && pos_x >= 0 && pos_y >= 400 && pos_y <= height) {
				//Change background to blue and text to yellow
				al_draw_filled_rectangle(250, 400, 0, height, al_map_rgb(0, 0, 255));
				draw_filled_circle(pos_x, pos_y, makeColorRed());
				draw_filled_triangle(pos_x, pos_y, makeColorWhite());
				al_draw_textf(font20, al_map_rgb(255, 255, 0), pos_x, pos_y, ALLEGRO_ALIGN_LEFT, "X: %i Y: %i", pos_x, pos_y);
				al_flip_display();
			}
			//lower right
			else if (pos_x >= 500 && pos_x <= width && pos_y >= 400 && pos_y <= height) {
				//Change background to yellow and text to blue
				al_draw_filled_rectangle(500, 400, width, height, al_map_rgb(255, 255, 0));
				draw_filled_circle(pos_x, pos_y, makeColorRed());
				draw_filled_triangle(pos_x, pos_y, makeColorWhite());
				al_draw_textf(font20, al_map_rgb(0,0, 255), pos_x, pos_y, ALLEGRO_ALIGN_LEFT, "X: %i Y: %i", pos_x, pos_y);
				al_flip_display();
			}
			else {
				//place object
				draw_filled_circle(pos_x, pos_y, makeColorRed());
				draw_filled_triangle(pos_x, pos_y, makeColorWhite());
				al_draw_textf(font20, al_map_rgb(255, 0, 0), 250, 300, ALLEGRO_ALIGN_LEFT, "X: %i Y: %i", pos_x, pos_y);
				al_flip_display();
			}

			draw = false;
		}


		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(Screen);						//destroy our display object
	system("pause");
	return 0;
}

ALLEGRO_COLOR makeColorWhite()
{
	int red = 255;
	int green = 255;
	int blue = 255;
	return (al_map_rgb(red, green, blue));
}

ALLEGRO_COLOR makeColorRed()
{
	int red = 255;
	int green = 0;
	int blue = 0;

	return (al_map_rgb(red, green, blue));
}

void draw_filled_circle(int pos_x, int pos_y, ALLEGRO_COLOR color)
{
	int cx = (pos_x);
	int cy = (pos_y);
	int r = 20;
	al_draw_filled_circle(cx, cy, r, color);
}

void draw_filled_triangle(int pos_x, int pos_y, ALLEGRO_COLOR color)
{
	int x = (pos_x + 20);
	int y = pos_y;
	int x2 = (pos_x + 50);
	int y2 = (pos_y - 20);
	int x3 = (pos_x + 50);
	int y3 = (pos_y + 20);
	al_draw_filled_triangle(x, y, x2, y2, x3, y3, color);

	int x4 = (pos_x - 20);
	int y4 = pos_y;
	int x5 = (pos_x - 50);
	int y5 = (pos_y + 20);
	int x6 = (pos_x - 50);
	int y6 = (pos_y - 20);
	al_draw_filled_triangle(x4, y4, x5, y5, x6, y6, color);
}

void draw_triangle(int pos_x, int pos_y, ALLEGRO_COLOR color)
{
	int x = (pos_x + 20);
	int y = pos_y;
	int x2 = (pos_x + 50);
	int y2 = (pos_y - 20);
	int x3 = (pos_x + 50);
	int y3 = (pos_y + 20);
	int thickness = 3;
	al_draw_triangle(x, y, x2, y2, x3, y3, color, thickness);

	int x4 = (pos_x - 20);
	int y4 = pos_y;
	int x5 = (pos_x - 50);
	int y5 = (pos_y + 20);
	int x6 = (pos_x - 50);
	int y6 = (pos_y - 20);
	al_draw_triangle(x4, y4, x5, y5, x6, y6, color, thickness);
}
