#ifndef SPRITEH
#define SPRITEH

class sprite
{
public:
	void load_animated_sprite(int size);
	~sprite();
	void Drawsprite();
	void movesprite();
	//void Collidesprite(player& Player);
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	int getX() { return x; }
	int getY() { return y; }
	int getcurFrame() { return curFrame; }
private:
	int x;
	int y;
	int curFrame;
	int maxFrame;
	int frameDelay;
	int frameCount;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP* image[2];
};
#endif
