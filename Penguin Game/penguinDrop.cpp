#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "penguinDrop.h"


penguinDrop::~penguinDrop()
{
	al_destroy_bitmap(image);
}
penguinDrop::penguinDrop()
{
	
	int x = 0; 
	int y = 0; 
	live = false;
	speed = 3;
	image = al_load_bitmap("fallingpenguin.png");
	al_convert_mask_to_alpha(image, al_map_rgb(163, 73, 164));
	boundx = 32;
	boundy = 32;

}
void penguinDrop::DrawPenguinDrop()
{
	if (live)
		al_draw_bitmap(image, x, y, 0);

}
void penguinDrop::StartPenDrop(int WIDTH)
{
	if (!live)
	{
		if (rand() % 400 == 0)
		{
			live = true;
			x = rand() % (WIDTH - boundx);
			y = 0;
		}
	}
}
void penguinDrop::UpdatePen()
{
	if (live)
	{
		y += rand() % 2;
		y += speed;
	}
}
void penguinDrop::CollidePenguin(iceberg& Iceberg, int HEIGHT)
{
	if (live)
	{
		if (x - boundx < Iceberg.getX() + Iceberg.getBoundX() &&
			x + boundx > Iceberg.getX() - Iceberg.getBoundX() &&
			y - boundy < Iceberg.getY() + Iceberg.getBoundY() &&
			y + boundy > Iceberg.getY() - Iceberg.getBoundY())
		{
			Iceberg.removeIceLife();
			live = false;

		}
		else if (y > HEIGHT)
			live = false;
	}
}