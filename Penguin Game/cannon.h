#ifndef CANNONH
#define CANNONH
#include "iceberg.h"

class cannon
{
public:
	cannon(iceberg &Iceberg);
	~cannon();
	void DrawCannon();
	int getX() { return x; }
	int getY() { return y; }
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	void rotateLeft(); //rotates left when key is pressed
	void rotateRight(); //rotates right when key is pressed
	float getAngle() { return angle; }
private:
	int x;
	int y;
	int boundx;
	int boundy;
	float angle;
	ALLEGRO_BITMAP* image;
};
#endif 

