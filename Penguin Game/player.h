#ifndef PLAYERH
#define PLAYERH
#include "iceberg.h"
class player
{
public:
	player(int WIDTH, int HEIGHT);
	~player();
	void DrawPlayer();
	int getX() { return x; }
	int getY() { return y; }
	int getScore() { return score; } 
	void UpdateScore() { score += 5; } //keeps track of score
	int getKill() { return killCount; }
	void UpdateKill() { killCount++; } //keeps track of hit penguins
private:
	int x;
	int y;
	int boundx;
	int boundy;
	int score;
	int killCount;
	ALLEGRO_BITMAP* image;
};
#endif
