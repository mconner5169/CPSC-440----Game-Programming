#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "iceberg.h"

iceberg::~iceberg()
{
	for(int i = 0; i < 5; i++)
	al_destroy_bitmap(image[i]);
}
iceberg::iceberg(int WIDTH, int HEIGHT) 
{
	x = (WIDTH / 2);
	y = (HEIGHT / 2) + 50;
	scaledx = x - 285;
	scaledy = y;
	life = 5;
	boundx = 200;
	boundy = 80;
	image[0] = NULL;
	image[1] = NULL;
	image[2] = NULL;
	image[3] = NULL;
	image[4] = NULL;

	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 4:
			image[4] = al_load_bitmap("iceburg44.png");
			al_convert_mask_to_alpha(image[4], al_map_rgb(163, 73, 164));
			boundx = al_get_bitmap_width(image[4]) * .50;
			boundy = al_get_bitmap_height(image[4]) * .05;
		case 3:
			image[3] = al_load_bitmap("iceburg33.png");
			al_convert_mask_to_alpha(image[3], al_map_rgb(163, 73, 164));
			boundx = al_get_bitmap_width(image[3]) * .50;
			boundy = al_get_bitmap_height(image[3]) * .05;
		case 2:
			image[2] = al_load_bitmap("iceburg22.png");
			al_convert_mask_to_alpha(image[2], al_map_rgb(163, 73, 164));
			boundx = al_get_bitmap_width(image[2]) * .50;
			boundy = al_get_bitmap_height(image[2]) * .05;
		case 1:
			image[1] = al_load_bitmap("iceburg11.png");
			al_convert_mask_to_alpha(image[1], al_map_rgb(163, 73, 164));
			boundx = al_get_bitmap_width(image[1]) * .50;
			boundy = al_get_bitmap_height(image[1]) * .05;
		case 0:
			image[0] = al_load_bitmap("iceburg00.png");
			al_convert_mask_to_alpha(image[0], al_map_rgb(163, 73, 164));
			boundx = al_get_bitmap_width(image[0]) *.50;
			boundy = al_get_bitmap_height(image[0]) * .05;
		}
	}
}
void iceberg::DrawIceberg()
{
	al_draw_bitmap(image[getIceLife() - 1], scaledx, scaledy, 0);
}
bool iceberg::endGame()
{
	bool done;

	if (getIceLife() <= 0)
		done = true;
	else
		done = false;

	return done;
}