#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "player.h"
#include "fish.h"
//#include "dino.h"

class Rock
{
public:
	Rock();
	~Rock();
	void DrawRock();
	void FireRock(player& Player);
	void UpdateRock(int WIDTH);
	void CollideRock(fish dinos[], int cSize, player& Player);
private:
	int x;
	int y;
	float angle;
	bool live;
	int speed;
	ALLEGRO_BITMAP* image;
	ALLEGRO_SAMPLE* sample;
	ALLEGRO_SAMPLE* sample2;
};