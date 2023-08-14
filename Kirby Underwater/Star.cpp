#include <allegro5\allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Star.h"

Star::Star()
{
	x = 0;
	y = 0;
	angle = 0;
	speed = 10;
	live = false;
	image = al_load_bitmap("star.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

	sample = NULL;
	sample2 = NULL;
	sample = al_load_sample("arrowthrow.wav");
	sample2 = al_load_sample("fishdie.wav");
	if (!sample && !sample2) {
		exit(9);
	}
}
Star::~Star()
{
	al_destroy_bitmap(image);
}
void Star::DrawStar()
{
	r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (live)
		al_draw_tinted_rotated_bitmap(image, al_map_rgba_f(r, g, b, 1), al_get_bitmap_width(image) / 2, al_get_bitmap_height(image) / 2, x, y, angle, 0);

}
void Star::FireStar(player& Player)
{
	if (!live)
	{
		x = Player.getX();
		y = Player.getY();
		live = true;
		al_play_sample(sample, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}
void Star::UpdateStar(int WIDTH)
{
	if (live)
	{
		x += speed;
		angle += .1;
		if (x > WIDTH)
			live = false;
	}
}
void Star::CollideStar(fish fishsss[], int cSize, player& Player)
{
	if (live)
	{
		for (int j = 0; j < cSize; j++)
		{
			if (fishsss[j].getLive())
			{
				if (x > (fishsss[j].getX() - fishsss[j].getBoundX()) &&
					x < (fishsss[j].getX() + fishsss[j].getBoundX()) &&
					y >(fishsss[j].getY() - fishsss[j].getBoundY()) &&
					y < (fishsss[j].getY() + fishsss[j].getBoundY()))
				{
					live = false;
					fishsss[j].setLive(false);
					Player.UpdateFishKill();
					Player.UpdateScore();
					al_play_sample(sample2, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}
		}
	}

}