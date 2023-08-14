#ifndef PLAYERH
#define PLAYERH
class player
{
public:
	player(int HEIGHT);
	~player();
	void DrawPlayer();
	void MoveUp();
	void MoveDown(int HEIGHT);
	void MoveLeft();
	void MoveRight();
	int getBoundX(){return boundx;}
	int getBoundY(){return boundy;}
	int getX(){return x;}
	int getY(){return y;}
	int getScore(){ return score; }
	void UpdateScore(){score += 10; }
	int getFishKill() { return fishKillCount; }
	void UpdateFishKill() { fishKillCount++; }
	int getTotalKill();
	void UpdateTotalKill() { killCount++; }
	int removeLife() { lives -= 1; return lives; }
	int getLife() { return lives; }
	bool endGame();
private:
	int x;
	int y;
	int lives;
	int speed;
	int boundx;
	int boundy;
	int score;
	int fishKillCount;
	int killCount;
	ALLEGRO_BITMAP *image[5];
};
#endif
