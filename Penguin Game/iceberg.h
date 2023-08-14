#ifndef ICEBERGH
#define ICEBERGH
class iceberg
{
public:
	iceberg(int WIDTH, int HEIGHT);
	~iceberg();
	void DrawIceberg();
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	int getX() { return x; }
	int getY() { return y; }
	int removeIceLife() { life -= 1; return life; }
	int getIceLife() { return life; }
	bool endGame(); //checks if game ends when iceberg is broken
private:
	int x;
	int y;
	int scaledx;
	int scaledy;
	int life;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP* image[5];
};
#endif
