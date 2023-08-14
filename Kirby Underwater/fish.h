#ifndef FISHH
#define FISHH
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "player.h"
class fish
{
public:
	fish();
	~fish();
	void Drawfish(int level);
	void Startfish(int WIDTH, int HEIGHT );
	void Updatefish(int level);
	void Collidefish(player &Player);
	int getBoundX(){return boundx;}
	int getBoundY(){return boundy;}
	int getX(){return x;}
	int getY(){return y;}
	bool getLive() {return live;}
	void setLive(bool l){live=l;}
private:
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE* sample;
};
#endif
