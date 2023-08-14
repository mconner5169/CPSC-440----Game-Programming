#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "player.h"
#include "fish.h"

class Arrow
{
public:
	Arrow();
	~Arrow();
	void DrawArrow();
	void FireArrow(player &Player);
	void UpdateArrow(int WIDTH);
	void CollideArrow(fish fishs[], int cSize, player &Player);
private:
	int x;
	int y;
	bool live;
	int speed;
	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE* sample;
	ALLEGRO_SAMPLE* sample2;
};

