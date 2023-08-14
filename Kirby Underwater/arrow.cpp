#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5\allegro_image.h>
#include "Arrow.h"

Arrow::Arrow()
{
	x = 0;
	y = 0;
	speed = 10;
	live = false;
	image = al_load_bitmap("arrow.png");

	sample = NULL;
	sample2 = NULL;
	sample = al_load_sample("arrowthrow.wav");
	sample2 = al_load_sample("fishdie.wav");
	if (!sample && !sample2) {
		exit(9);
	}
}
Arrow::~Arrow()
{
	al_destroy_bitmap(image);
}
void Arrow::DrawArrow()
{

	if(live)
		al_draw_rotated_bitmap(image,al_get_bitmap_width(image)/2,al_get_bitmap_height(image)/2,x,y,90,0);

}
void Arrow::FireArrow(player &Player)
{
	if(!live)
	{
		x = Player.getX();
		y = Player.getY();
		live = true;
		al_play_sample(sample, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}
void Arrow::UpdateArrow(int WIDTH)
{
	if(live)
	{
		x += speed;
		if(x > WIDTH)
			live = false;
	}
}
void Arrow::CollideArrow(fish fishs[], int cSize, player &Player)
{
	if(live)
	{
		for(int j =0; j < cSize; j++)
		{
			if(fishs[j].getLive())
			{
				if(x > (fishs[j].getX() - fishs[j].getBoundX()) &&
					x < (fishs[j].getX() + fishs[j].getBoundX()) &&
					y > (fishs[j].getY() - fishs[j].getBoundY()) &&
					y < (fishs[j].getY() + fishs[j].getBoundY()))
				{
					live = false;
					fishs[j].setLive(false);
					Player.UpdateFishKill();
					Player.UpdateScore();
					al_play_sample(sample2, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}
		}
	}

}