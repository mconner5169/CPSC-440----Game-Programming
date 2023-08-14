#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include "player.h"
#include "fish.h"
#include "Arrow.h"
#include "Rock.h"
#include "Star.h"
using namespace std;

void load_animated_sprite(ALLEGRO_BITMAP* image[], int size);
void move_sprite(ALLEGRO_BITMAP* image[], int& x, int& framecount, int& curframe, int y, int framedelay, int maxFrame);

int main(int argc, char** argv)
{

	const int WIDTH = 800;
	const int HEIGHT = 600;
	const int NUM_ArrowS = 5;
	const int NUM_Rocks = 5;
	const int NUM_Stars = 5;
	const int NUM_fishS = 5; //level 1
	const int NUM_fishSS = 15; //level 2
	const int NUM_fishSSS = 20; //level 3
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
	bool keys[5] = {false, false, false, false, false};


	//primitive variable
	bool done = false;
	bool redraw = true;
	int level = 1;
	bool levelOver = false;
	const int FPS = 60;
	int curFrame = 0;
	const int maxFrame = 2;
	int frameDelay = 5;
	int frameCount = 0;
	int x = 750;
	int y = 60;


	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP* background = NULL;
	ALLEGRO_BITMAP* mySprite[maxFrame];
	ALLEGRO_SAMPLE* sample = NULL;

	//Initialization Functions
	if(!al_init())										//initialize Allegro
		return -1;

	//Initializing sound
	if (!al_install_audio()) {
		return -1;
	}
	if (!al_init_acodec_addon()) {
		return -1;
	}
	if (!al_reserve_samples(4)) {
		return -1;
	}
	sample = al_load_sample("underwatersound.wav");

	if (!sample) {
		exit(9);
	}

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_init_image_addon();
	background = al_load_bitmap("water.png");
	al_init_primitives_addon();

	//Sets fonts
	ALLEGRO_FONT* font10 = al_load_ttf_font("corbel.ttf", 20, 0);
	ALLEGRO_FONT* font20 = al_load_ttf_font("corbel.ttf", 30, 0);
	ALLEGRO_FONT* font30 = al_load_ttf_font("calibrib.ttf", 40, 0);

	//object variables
	player myPlayer(HEIGHT);
	//sprite mySprite[2];
	Arrow Arrows[NUM_ArrowS];
	Rock Rocks[NUM_Rocks];
	Star Stars[NUM_Stars];
	fish fishs[NUM_fishS];
	fish fishss[NUM_fishSS];
	fish fishsss[NUM_fishSSS];
	load_animated_sprite(mySprite, 2);

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	srand(time(NULL));

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	//Intro
	al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT, al_map_rgb(255, 255, 255));
	al_draw_textf(font30, al_map_rgb(0, 255, 0), WIDTH / 2, 20, ALLEGRO_ALIGN_CENTER, "WELCOME TO GURDIANS OF THE WORLD!");
	al_draw_textf(font20, al_map_rgb(255, 165, 0), 0, 150, 0, "INSTRUCTIONS:");
	al_draw_textf(font10, al_map_rgb(0, 0, 0), 0, 200, 0, "Your job is to rescue your friend from drowing, but there are lots of fish blocking the path.");
	al_draw_textf(font10, al_map_rgb(0,0,0), 0, 220, 0, "Be careful because you'll only have five lives total.");
	al_draw_textf(font10, al_map_rgb(0, 0, 0), 0, 240, 0, "Beware, the levels get harder as you complete each one. Use your keyboard to kill the enemies.");
	al_draw_textf(font20, al_map_rgb(255, 166, 0), 0, 380, 0, "GAME CONTROLS:");
	al_draw_textf(font10, al_map_rgb(0, 0, 0), 0, 420, 0, "Right Key - moves player right");
	al_draw_textf(font10, al_map_rgb(0, 0, 0), 0, 450, 0, "Left Key - moves player left");
	al_draw_textf(font10, al_map_rgb(0, 0, 0), 0, 480, 0, "Up Key - moves player up");
	al_draw_textf(font10, al_map_rgb(0, 0, 0), 0, 510, 0, "Donw Key - moves player down");
	al_draw_textf(font10, al_map_rgb(0, 0, 0), 0, 540, 0, "Space Bar - fires arrows");
	al_flip_display();
	al_rest(10);

	
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);
	al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		al_draw_bitmap(background, 0, 0, 0);
		
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if(keys[UP])
				myPlayer.MoveUp();
			if(keys[DOWN])
				myPlayer.MoveDown(HEIGHT);
			if(keys[LEFT])
				myPlayer.MoveLeft();
			if(keys[RIGHT])
				myPlayer.MoveRight();

			if (level == 1)
			{
				for (int i = 0; i < NUM_ArrowS; i++)
					Arrows[i].UpdateArrow(WIDTH);
				for (int i = 0; i < NUM_fishS; i++)
					fishs[i].Startfish(WIDTH, HEIGHT);
				for (int i = 0; i < NUM_fishS; i++)
					fishs[i].Updatefish(level);
				for (int i = 0; i < NUM_ArrowS; i++)
					Arrows[i].CollideArrow(fishs, NUM_fishS, myPlayer);
				for (int i = 0; i < NUM_fishS; i++)
					fishs[i].Collidefish(myPlayer);
				if (myPlayer.getFishKill() == 10)
				{
					levelOver = true;
				}

			}
			else if (level == 2)
			{
				for (int i = 0; i < NUM_Rocks; i++)
					Rocks[i].UpdateRock(WIDTH);
				for (int i = 0; i < NUM_fishSS; i++)
					fishss[i].Startfish(WIDTH, HEIGHT);
				for (int i = 0; i < NUM_fishSS; i++)
					fishss[i].Updatefish(level);
				for (int i = 0; i < NUM_Rocks; i++)
					Rocks[i].CollideRock(fishss, NUM_fishSS, myPlayer);
				for (int i = 0; i < NUM_fishSS; i++)
					fishss[i].Collidefish(myPlayer);
				if (myPlayer.getFishKill() == 20)
				{
					levelOver = true;
				}

			}
			else if (level == 3)
			{
				for (int i = 0; i < NUM_Stars; i++)
					Stars[i].UpdateStar(WIDTH);
				for (int i = 0; i < NUM_fishSSS; i++)
					fishsss[i].Startfish(WIDTH, HEIGHT);
				for (int i = 0; i < NUM_fishSSS; i++)
					fishsss[i].Updatefish(level);
				for (int i = 0; i < NUM_Stars; i++)
					Stars[i].CollideStar(fishsss, NUM_fishSSS, myPlayer);
				for (int i = 0; i < NUM_fishSSS; i++)
					fishsss[i].Collidefish(myPlayer);
				if (myPlayer.getFishKill() == 40)
				{
					levelOver = true;
				}
				
			}
			else if (level >= 4)
			{
				done = true;
				break;
			}
			
			//Checks if level is over
			if (levelOver == true)
			{
				levelOver = false;

				al_draw_filled_rectangle(50, 100, WIDTH - 50, HEIGHT - 100, al_map_rgb(255, 255, 255));
				al_draw_textf(font20, al_map_rgb(0, 0, 0), 50, HEIGHT / 2, 0, "You beat level %i! Get ready for the next one.", level);
				level++;
				al_flip_display();
				_sleep(2000);
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}

			//Game Status
			al_draw_filled_rectangle(600, 500, WIDTH, HEIGHT, al_map_rgb(255, 255, 255));
			al_draw_textf(font10, al_map_rgb(0, 0, 0), 600, 510, ALLEGRO_ALIGN_LEFT, "Kirby's Lives: %i/5", myPlayer.getLife());
			al_draw_textf(font10, al_map_rgb(0, 0, 0), 600, 580, ALLEGRO_ALIGN_LEFT, "Total Kills: %i", myPlayer.getTotalKill());
			if (myPlayer.getLife() < 3)
				al_draw_textf(font10, al_map_rgb(255, 0, 0), 600, 535, ALLEGRO_ALIGN_LEFT, "You're running low on lives!");
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
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
				if (level == 1)
				{
					for (int i = 0; i < NUM_ArrowS; i++)
						Arrows[i].FireArrow(myPlayer);
					break;
				}
				if (level == 2)
				{
					for (int i = 0; i < NUM_Rocks; i++)
						Rocks[i].FireRock(myPlayer);
				}
				if (level == 3)
				{
					for (int i = 0; i < NUM_Stars; i++)
						Stars[i].FireStar(myPlayer);
				}
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
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

		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false; 
			move_sprite(mySprite, x, frameCount, curFrame, y, frameDelay, maxFrame);

			if (myPlayer.endGame() == true) {
				done = true;
				break;
			}
			else if (myPlayer.endGame() == false)
			{
				myPlayer.DrawPlayer();
				done = false;
			}
			
			if (level == 1)
			{
				for (int i = 0; i < NUM_ArrowS; i++)
					Arrows[i].DrawArrow();
				for (int i = 0; i < NUM_fishS; i++)
					fishs[i].Drawfish(level);				
			}
			if (level == 2)
			{
				for (int i = 0; i < NUM_Rocks; i++)
					Rocks[i].DrawRock();
				for (int i = 0; i < NUM_fishSS; i++)
					fishss[i].Drawfish(level);
			}
			if (level == 3)
			{
				for (int i = 0; i < NUM_Stars; i++)
					Stars[i].DrawStar();
				for (int i = 0; i < NUM_fishSSS; i++)
					fishsss[i].Drawfish(level);				
			}
			
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	
	//End Game Stats
	al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT, al_map_rgb(255, 255, 255));
	if (level == 4)
	{
		al_draw_textf(font30, al_map_rgb(0, 255, 0), WIDTH / 2, 10, ALLEGRO_ALIGN_CENTER, "CONGRATS! You rescued your friend!");
	}
	else 
	{
		al_draw_textf(font30, al_map_rgb(0, 255, 0), WIDTH / 2, 10, ALLEGRO_ALIGN_CENTER, "GAME OVER! Your friend drowned.");
	}
	al_draw_textf(font20, al_map_rgb(0, 0, 255), 0, 200, 0, "Fishes Killed: %i", myPlayer.getFishKill());
	al_draw_textf(font20, al_map_rgb(162, 155, 40), 0, 400, ALLEGRO_ALIGN_LEFT, "Final Score: %i", myPlayer.getScore());
	al_flip_display();


	al_rest(5);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_sample(sample);
	al_destroy_display(display);						//destroy our display object
	system("Pause");
	return 0;
}

void load_animated_sprite(ALLEGRO_BITMAP* image[], int size)
{
	char s[80];
	for (int n = 0; n < size; n++)
	{
		sprintf_s(s, "%d.bmp", n + 1);
		cout << s << endl;
		image[n] = al_load_bitmap(s);

		al_convert_mask_to_alpha(image[n], al_map_rgb(255, 0, 255));
	}
}

void move_sprite(ALLEGRO_BITMAP* image[], int& x, int& framecount, int& curframe, int y, int framedelay, int maxFrame)
{
	if (framecount++ > framedelay)
	{
		framecount = 0;
		curframe++;
		if (curframe >= maxFrame)
			curframe = 0;
	}

	//draw the sprite
	al_draw_bitmap(image[curframe], x, y, 0);
}
