#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "player.h"
#include "fish.h"

class Star
{
public:
	Star();
	~Star();
	void DrawStar();
	void FireStar(player& Player);
	void UpdateStar(int WIDTH);
	void CollideStar(fish fishsss[], int cSize, player& Player);
private:
	int x;
	int y;
	float angle;
	float r, g, b;
	bool live;
	int speed;
	ALLEGRO_BITMAP* image;
	ALLEGRO_SAMPLE* sample;
	ALLEGRO_SAMPLE* sample2;
};


