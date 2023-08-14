#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "fish.h"

fish::fish()
{
	image = al_load_bitmap("fish.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));
	live = false;
	speed = 5;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	x = 0;
	y = 0;

	sample = NULL;
	sample = al_load_sample("collision.wav");
	if (!sample) {
		exit(9);
	}

}
fish::~fish()
{
	al_destroy_bitmap(image);
}
void fish::Drawfish(int level)
{
	if(live)
	{
		al_draw_bitmap(image, x, y, 0);
	}
}
void fish::Startfish(int WIDTH, int HEIGHT )
{
	if(!live)
	{
		if(rand() % 500 == 0)
		{
			live = true;
			x = WIDTH - 60;
			y = rand() % (HEIGHT-boundy);

		}
	}
}
void fish::Updatefish(int level)
{

	if (live)
	{
		x -= speed;
	}

}
void fish::Collidefish(player &Player)
{
	if(live)
	{
		if( x - boundx < Player.getX() + Player.getBoundX() &&
			x + boundx > Player.getX() - Player.getBoundX() &&
			y - boundy < Player.getY() + Player.getBoundY() &&
			y + boundy > Player.getY() - Player.getBoundY())
		{
			Player.removeLife();
			live = false;
			al_play_sample(sample, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		else if(x < 0)
		{
			live = false;
		}
	}
}