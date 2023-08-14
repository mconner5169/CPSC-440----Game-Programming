#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#include "player.h"


player::~player()
{
	for(int i = 0; i < 5; i++)
	al_destroy_bitmap(image[i]);
}
player::player(int HEIGHT)
{
	x = 20;
	y = HEIGHT / 2;
	lives = 5;
	speed = 7;
	score = 0;
	fishKillCount = 0;
	killCount = 0;
	boundx = 50;
	boundy = 50;
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
			image[4] = al_load_bitmap("kirby5.png");
			boundx = al_get_bitmap_width(image[4]);
			boundy = al_get_bitmap_height(image[4]);
			al_convert_mask_to_alpha(image[4], al_map_rgb(0, 0, 0));
			break;
		case 3:
			image[3] = al_load_bitmap("kirby4.png");
			boundx = al_get_bitmap_width(image[3]);
			boundy = al_get_bitmap_height(image[3]);
			break;
		case 2:
			image[2] = al_load_bitmap("kirby3.png");
			boundx = al_get_bitmap_width(image[2]);
			boundy = al_get_bitmap_height(image[2]);
			break;
		case 1:
			image[1] = al_load_bitmap("kirby2.png");
			boundx = al_get_bitmap_width(image[1]);
			boundy = al_get_bitmap_height(image[1]);
			break;
		case 0:
			image[0] = al_load_bitmap("kirby1.png");
			boundx = al_get_bitmap_width(image[0]);
			boundy = al_get_bitmap_height(image[0]);
			break;

		}
	}
	
}
int player::getTotalKill()
{
	killCount = fishKillCount;
	return killCount;
}
void player::DrawPlayer()
{
	
	al_draw_bitmap(image[getLife() - 1], x,y, 0);
}
void player::MoveUp()
{
	y -= speed;
	if(y < 0)
		y = 0;
}
void player::MoveDown(int HEIGHT)
{
	y += speed;
	if(y > HEIGHT - 50)
		y = HEIGHT - 50;
}
void player::MoveLeft()
{
	x -= speed;
	if(x < 0)
		x = 0;
}
void player::MoveRight()
{
	x += speed;
	if(x > 200)
		x = 200;
}
bool player::endGame()
{
	bool done;
	if (getLife() <= 0)
	{
		done = true;
	}
	else
	{
		done = false;
	}
	return done;
}
