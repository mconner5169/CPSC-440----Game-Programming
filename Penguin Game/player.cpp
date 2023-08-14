#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"

player::~player()
{
	al_destroy_bitmap(image);
}
player::player(int WIDTH, int HEIGHT)
{
	
	x = WIDTH / 2 - 65;
	y = HEIGHT / 2; 
	score = 0;
	killCount = 0;
	image = al_load_bitmap("firepenguin.png");
	al_convert_mask_to_alpha(image, al_map_rgb(163, 73, 164));
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
}
void player::DrawPlayer()
{
	al_draw_bitmap(image, x, y, 0);
}