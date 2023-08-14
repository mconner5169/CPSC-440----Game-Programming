#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include<stdio.h>
#include "dino.h"

void dino::load_animated_sprite()
{
	//image[0] = NULL;
	//char s[80];
	//maxframe = size;
	//for (int n = 0; n < size; n++)
	//{
		//sprintf_s(s, "dino%d.bmp", n + 1);
		//image[n] = al_load_bitmap(s);

		//al_convert_mask_to_alpha(image[n], al_map_rgb(155, 155, 155));
	//}
	//boundx = al_get_bitmap_width(image[0]);
	//boundy = al_get_bitmap_height(image[0]);
	//curframe = 0;
	//framedelay = 5;
	//framecount = 0;
	live = false;
	speed = 5;
	x = 0;
	y = 0;
	image = al_load_bitmap("dino3.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);

}
dino::~dino()
{
	//for (int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image);
}
void dino::Drawdino()
{
	if (live)
	{
		al_draw_bitmap(image, x, y, 0);
	}
}
void dino::Startdino(int WIDTH, int HEIGHT)
{
	if (!live)
	{
		if (rand() % 500 == 0)
		{
			live = true;
			//load_animated_sprite(6);
			x = WIDTH;
			y = rand() % (HEIGHT - boundy);

		}
	}
}
void dino::Updatedino()
{

	if (live)
	{
		x -= speed;
	}
	//if (framecount++ > framedelay)
	//{
		//framecount = 0;
		//curframe++;
		//if (curframe >= maxframe)
			//curframe = 0;
	//}

}
void dino::Collidedino(player& Player)
{
	if (live)
	{
		if (x - boundx < Player.getX() + Player.getBoundX() &&
			x + boundx > Player.getX() - Player.getBoundX() &&
			y - boundy < Player.getY() + Player.getBoundY() &&
			y + boundy > Player.getY() - Player.getBoundY())
		{
			Player.removeLife();
			live = false;
		}
		else if (x < 0)
		{
			live = false;
		}
	}
}