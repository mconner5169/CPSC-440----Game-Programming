#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <math.h>
#include "snowball.h"

snowball::~snowball()
{
	al_destroy_bitmap(image);
}
snowball::snowball()
{
	x = 400;
	y = 335;
	speed = 7;
	radian_angle = 0;
	live = false;
	image = al_load_bitmap("snowball.png");
	al_convert_mask_to_alpha(image, al_map_rgb(163, 73, 164));
}
void snowball::DrawSnowball()
{
	if (live)
		al_draw_rotated_bitmap(image, al_get_bitmap_width(image) / 2, al_get_bitmap_height(image) / 2, x, y, radian_angle, 0);
}
void snowball::FireSnowball(cannon& Cannon)
{
	if (!live)
	{
		x = 400;
		y = 335;
		radian_angle = ((Cannon.getAngle() * 3.14159 / 180.0));
		live = true;
	}
}
void snowball::UpdateSnowball(int WIDTH)
{
	if (live)
	{ 
		x -= speed * sin(radian_angle);
		y -= speed * cos(radian_angle);
		if (y <= 0 || x <=0 || x >= WIDTH)
			live = false;
	}
}
void snowball::CollideSnowball(penguinDrop penguinDrop[], int NUM_Penguins, player& Player)
{
	if (live)
	{
		for (int i = 0; i < NUM_Penguins; i++)
		{
			if (penguinDrop[i].getLive())
			{
				if (x > (penguinDrop[i].getX() - penguinDrop[i].getBoundX()) &&
					x < (penguinDrop[i].getX() + penguinDrop[i].getBoundX()) &&
					y >(penguinDrop[i].getY() - penguinDrop[i].getBoundY()) &&
					y < (penguinDrop[i].getY() + penguinDrop[i].getBoundY()))
				{
					live = false;
					penguinDrop[i].setLive(false);
					Player.UpdateKill();
					Player.UpdateScore();
				}
			}
		}
	}
}