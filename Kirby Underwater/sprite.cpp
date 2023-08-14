#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "sprite.h"
#include <iostream>
using namespace std;

void sprite::load_animated_sprite(int frames)
{
	int curFrame = 0;
	int maxFrame = 2;
	int frameDelay = 5;
	int frameCount = 0;
	int x = 770;
	int y = 60;
	image[0] = NULL;
	image[1] = NULL;
	
	for (int n = 0; n < frames; n++)
	{
		switch (n)
		{
		case 0:
			image[0] = al_load_bitmap("1.bmp");
			boundx = al_get_bitmap_width(image[0]);
			boundy = al_get_bitmap_height(image[0]);
			al_convert_mask_to_alpha(image[0], al_map_rgb(255, 0, 255));
			break;
		case 1:
			image[1] = al_load_bitmap("2.bmp");
			boundx = al_get_bitmap_width(image[1]);
			boundy = al_get_bitmap_height(image[1]);
			al_convert_mask_to_alpha(image[1], al_map_rgb(255, 0, 255));
			break;
		}
	}
}
sprite::~sprite()
{
	for (int i = 0; i < 2; i++)
		al_destroy_bitmap(image[i]);
}
void sprite::Drawsprite()
{
	
	al_draw_bitmap(image[getcurFrame()], getX(), getY(), 0);
}

void sprite::movesprite()
{
	if (frameCount++ > frameDelay)
	{
		frameCount = 0;
		curFrame++;
		if (curFrame >= maxFrame)
			curFrame = 0;
	}
}
