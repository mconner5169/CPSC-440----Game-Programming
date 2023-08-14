#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "cannon.h"

cannon::~cannon()
{
	al_destroy_bitmap(image);
}
cannon::cannon(iceberg &Iceberg)
{
	
	x = Iceberg.getX();
	y = Iceberg.getY() - 15;
	angle = 0;
	image = al_load_bitmap("cannon.png");
	al_convert_mask_to_alpha(image, al_map_rgb(163, 73, 164));
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
}
void cannon::DrawCannon()
{
	al_draw_rotated_bitmap(image, 32, 32, x, y, getAngle() * 3.14159 / 180.0, 0);
}
void cannon::rotateRight()
{
	angle += 4.5;
	if (angle > 80)
		angle = 80;
}
void cannon::rotateLeft()
{
	angle -= 4.5;
	if (angle < -80)
		angle = -80;	
}