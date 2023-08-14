#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "player.h"
#include "iceberg.h"
#include "cannon.h"
#include "snowball.h"
#include "penguinDrop.h"

int main(void)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;
	const int NUM_Snowballs = 5;
	const int NUM_Penguins = 10;
	enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	bool keys[5] = { false, false, false, false, false };

	//primitive variable
	bool done = false;
	bool redraw = true;
	const int FPS = 35;


	//Allegro variables
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_BITMAP* background = NULL;

	//Initialization Functions
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)										//test display object
		return -1;


	//addons
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();

	//Loads background
	background = al_load_bitmap("icebergbackground.png");

	ALLEGRO_FONT* font10 = al_load_ttf_font("comici.ttf", 15, 0);
	ALLEGRO_FONT* font20 = al_load_ttf_font("comici.ttf", 30, 0);
	ALLEGRO_FONT* font30 = al_load_ttf_font("comici.ttf", 40, 0);

	//object variables
	iceberg myiceberg(WIDTH,HEIGHT);
	player myPlayer(WIDTH, HEIGHT);
	cannon myCannon(myiceberg);
	snowball snowball[NUM_Snowballs];
	penguinDrop penguinDrop[NUM_Penguins];

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	srand(time(NULL));

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));


	//Introduction
	al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT, al_map_rgb(155, 155, 155));
	al_draw_textf(font20, al_map_rgb(0, 0, 255), 400, 5, ALLEGRO_ALIGN_CENTER, "WELCOME TO PENGUIN DROP!");
	al_draw_textf(font20, al_map_rgb(5, 164, 10), 0, 105, 0, "Game Instructions");
	al_draw_textf(font20, al_map_rgb(255, 0, 0), 0, 200, 0, "Objective: ");
	al_draw_textf(font10, al_map_rgb(0, 0, 0), 0, 270, 0, "Shoot down as many penguins as you can before the iceberg life hits zero and you fall into the water.");
	al_draw_textf(font20, al_map_rgb(255, 165, 0), 0, 350, 0, "Controls: ");
	al_draw_textf(font10, al_map_rgb(0, 0, 0), 0, 400, 0, "Right Key turns cannon to the right");
	al_draw_textf(font10, al_map_rgb(0, 0, 0), 0, 450, 0, "Left Key turns cannon to the left");
	al_draw_textf(font10, al_map_rgb(0, 0, 0), 0, 500, 0, "Space Bar fires snowballs at penguins");
	al_flip_display();
	al_rest(5);
	
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) 
		{
			redraw = true;
			if (keys[UP])
			{
				keys[UP] = true;
			}
			if (keys[DOWN])
			{
				keys[DOWN] = true;
			}
			if (keys[LEFT])
				myCannon.rotateLeft();
			if (keys[RIGHT])
				myCannon.rotateRight();

			for (int i = 0; i < NUM_Snowballs; i++) 
				snowball[i].UpdateSnowball(WIDTH);
			for (int i = 0; i < NUM_Penguins; i++) 
				penguinDrop[i].StartPenDrop(WIDTH);
			for (int i = 0; i < NUM_Penguins; i++) 
				penguinDrop[i].UpdatePen();
			for (int i = 0; i < NUM_Snowballs; i++)
				snowball[i].CollideSnowball(penguinDrop, NUM_Penguins, myPlayer);
			for (int i = 0; i < NUM_Penguins; i++) 
				penguinDrop[i].CollidePenguin(myiceberg, HEIGHT);

		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				for (int i = 0; i < NUM_Snowballs; i++)
					snowball[i].FireSnowball(myCannon);
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			al_draw_bitmap(background, 0, 0, 0);

			//Checks if game has ended
			if (myiceberg.endGame() == true) {
				done = true;
				break;
			}
			else if (myiceberg.endGame() == false) {
				myiceberg.DrawIceberg();
				myPlayer.DrawPlayer();
				myCannon.DrawCannon();
				done = false;
			}

			for (int i = 0; i < NUM_Snowballs; i++)
				snowball[i].DrawSnowball();
			for (int i = 0; i < NUM_Penguins; i++)
				penguinDrop[i].DrawPenguinDrop();

			//In-Game Stats
			al_draw_filled_rectangle(560, 500, WIDTH, HEIGHT, al_map_rgb(155, 155, 155));
			al_draw_textf(font10, al_map_rgb(0, 0, 0), 680, 505, ALLEGRO_ALIGN_CENTER, "Game Stats:");
			al_draw_textf(font10, al_map_rgb(88, 15, 240), 560, 530, ALLEGRO_ALIGN_LEFT, "Iceberg Life: %i/5", myiceberg.getIceLife());
			al_draw_textf(font10, al_map_rgb(245, 10, 139), 560, 560, ALLEGRO_ALIGN_LEFT, "Penguins Shot Down: %i", myPlayer.getKill());

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));

		}
	}

	//Print End Game Stats here
	al_draw_filled_rectangle(100, 100, 650, 500, al_map_rgb(155, 155, 155));
	al_draw_textf(font30, al_map_rgb(255, 165, 0), 400, 105, ALLEGRO_ALIGN_CENTER, "GAME OVER!");
	al_draw_textf(font20, al_map_rgb(0, 255, 0), 120, 220, ALLEGRO_ALIGN_LEFT, "Final Score: %i", myPlayer.getScore());
	al_draw_textf(font20, al_map_rgb(255, 0, 0), 120, 320, ALLEGRO_ALIGN_LEFT, "Penguins Shot Down: %i", myPlayer.getKill());
	al_flip_display();

	al_rest(6);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object
	system("Pause");
	return 0;
}