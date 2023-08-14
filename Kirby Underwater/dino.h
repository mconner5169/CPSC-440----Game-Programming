#ifndef DINOH
#define DINOH
#include "player.h"
class dino
{
public:
	~dino();
	void load_animated_sprite();
	void Drawdino();
	void Startdino(int WIDTH, int HEIGHT);
	void Updatedino();
	void Collidedino(player& Player);
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	int getX() { return x; }
	int getY() { return y; }
	bool getLive() { return live; }
	void setLive(bool l) { live = l; }
private:
	int x, y;
	int boundx, boundy;
	bool live;
	int speed;
	int xdelay, ydelay;
	int xcount, ycount;
	int curframe, maxframe;
	int framecount, framedelay;
	ALLEGRO_BITMAP* image;
};
#endif
#pragma once
