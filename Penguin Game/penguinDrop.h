#ifndef PENGUINDROPH
#define PENGUINDROPH
#include "iceberg.h"

class penguinDrop
{
public:
	penguinDrop();
	~penguinDrop();
	void DrawPenguinDrop();
	void StartPenDrop(int HEIGHT); //drops penguins from sky
	void CollidePenguin(iceberg& Iceberg, int HEIGHT); //checks when penguin hits iceberg
	void UpdatePen(); //checks when penguin is off screen
	int getX() { return x; }
	int getY() { return y; }
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	bool getLive() { return live; }
	void setLive(bool l){ live = l; } 
private:
	int x;
	int y;
	int boundx;
	int boundy;
	bool live;
	int speed;
	ALLEGRO_BITMAP* image;
};

#endif 

