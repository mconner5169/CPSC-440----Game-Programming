#ifndef SNOWBALLH
#define SNOWBALLH
#include "player.h"
#include "cannon.h"
#include "penguinDrop.h"


class snowball
{
public:
	snowball();
	~snowball();
	void DrawSnowball();
	void UpdateSnowball(int WIDTH); //checks when snowball is off screen
	void FireSnowball(cannon &Cannon); //fires snowball from cannon
	void CollideSnowball(penguinDrop penguinDrop[], int NUM_Penguins, player &Player); //checks if snowball and penguin collide
	float getRadAngle() { return radian_angle; }
	int getX() { return x; }
	int getY() { return y; }
private:
	int x;
	int y;
	bool live;
	int speed;
	float radian_angle;
	float anglex;
	float angley;
	ALLEGRO_BITMAP* image;
};
#endif 
