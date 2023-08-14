#include "sprite.h"

Sprite::Sprite()
{
	image=NULL;
}
Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}
void Sprite::InitSprites(int width, int height)
{
	x = 10;
	y = (height /2) + 60;


	maxFrame = 6;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 5;
	frameWidth = 38;
	frameHeight = 40;
	animationColumns = 6;
	animationDirection = 1;

	image = al_load_bitmap("greenguy.bmp");
	al_convert_mask_to_alpha(image, al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(image, al_map_rgb(0,0,0));

}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	if(dir == 1){ //right key
		animationDirection = 1; 
		x+=2; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > maxFrame)
				curFrame=1;
		}
	} else if (dir == 0){ //left key
		animationDirection = 0; 
		x-=2; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > maxFrame)
				curFrame=1;
		}
	}
	else if (dir == 2) { //up key
		animationDirection = 2;
		y -= 2;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
	}
	else if (dir == 3) { //down key
		animationDirection = 3;
		y += 2;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
	}
	else //represent that they hit the space bar and that mean direction = 0
		animationDirection = dir;

	//check for collided with foreground tiles
	if (animationDirection==0)
	{ 
		if (collided(x, y + frameHeight)) { //collision detection to the left
			x = oldx; 
			y= oldy;
		}

	}
	else if (animationDirection == 1)
	{ 
		if (collided(x + frameWidth, y + frameHeight)) { //collision detection to the right
			x = oldx; 
			y= oldy;
		}
	}
	else if (animationDirection == 2) //collision detection up
	{
		if (collided(x + frameWidth, y)) {
			x = oldx;
			y = oldy;
		}
	}
	else if (animationDirection == 3) { //collisioin detection down
		if (collided(x + frameWidth, y + frameHeight)) {
			x = oldx;
			y = oldy;
		}
	}
}

bool Sprite::CollisionEndBlock()
{
	if (endValue(x + frameWidth/2, y + frameHeight + 5))
		return true;
	else
		return false;
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	if (animationDirection==1){ //right
		al_draw_bitmap_region(image, fx, fy, frameWidth,frameHeight, x-xoffset, y-yoffset, 0);
	}else if (animationDirection == 0 ){ //left
		al_draw_bitmap_region(image, fx, fy, frameWidth,frameHeight, x-xoffset, y-yoffset, ALLEGRO_FLIP_HORIZONTAL);
	}
	else if (animationDirection == 2) { //up
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, ALLEGRO_FLIP_VERTICAL);
	}
	else if (animationDirection == 3) { //down
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	else if (animationDirection == 4 ){ //standing
		al_draw_bitmap_region(image,0,0,frameWidth,frameHeight,  x-xoffset, y-yoffset, 0);

	}
}
