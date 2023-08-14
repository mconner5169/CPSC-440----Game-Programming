#include <allegro5\allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Rock.h"

Rock::Rock()
{
	x = 0;
	y = 0;
	angle = 0;
	speed = 10;
	live = false;
	image = al_load_bitmap("rock.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

	sample = NULL;
	sample2 = NULL;
	sample = al_load_sample("arrowthrow.wav");
	sample2 = al_load_sample("fishdie.wav");
	if (!sample && !sample2) {
		exit(9);
	}
}
Rock::~Rock()
{
	al_destroy_bitmap(image);
}
void Rock::DrawRock()
{

	if (live)
		al_draw_rotated_bitmap(image, al_get_bitmap_width(image) / 2, al_get_bitmap_height(image) / 2, x, y, angle, 0);

}
void Rock::FireRock(player& Player)
{
	if (!live)
	{
		x = Player.getX();
		y = Player.getY();
		live = true;
		al_play_sample(sample, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}
void Rock::UpdateRock(int WIDTH)
{
	if (live)
	{
		x += speed;
		angle += 0.1;
		if (x > WIDTH)
			live = false;
	}
}
void Rock::CollideRock(fish fishss[], int cSize, player& Player)
{
	if (live)
	{
		for (int j = 0; j < cSize; j++)
		{
			if (fishss[j].getLive())
			{
				if (x > (fishss[j].getX() - fishss[j].getBoundX()) &&
					x < (fishss[j].getX() + fishss[j].getBoundX()) &&
					y >(fishss[j].getY() - fishss[j].getBoundY()) &&
					y < (fishss[j].getY() + fishss[j].getBoundY()))
				{
					live = false;
					fishss[j].setLive(false);
					Player.UpdateFishKill();
					Player.UpdateScore();
					al_play_sample(sample2, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}
		}
	}

}