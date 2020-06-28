#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Creates a gray color for the shapes
//Param: none
//Return: gray color
ALLEGRO_COLOR makeColorGray();

//Creates a random color for shapes
//Param: none
//Return: color
ALLEGRO_COLOR makeColor();

//Draws Robot's shoulders are triangles that are attached to the body
//Param: color, screen width, screen height
//Return: gray triangles
void draw_triangle(ALLEGRO_COLOR color, const int SCREEN_W, const int SCREEN_H);	

//Draws Robot's eyes and hands
//Param: color, screen width, screen height
//Return: the filled in circle
void draw_filled_circle(ALLEGRO_COLOR color, const int SCREEN_W, const int SCREEN_H);

//Draws Robot's body, neck, head, arms, and legs
//Param: the color, screen width, screen height
//Return: the complete rectangle
void draw_rectangle(ALLEGRO_COLOR color, const int SCREEN_W, const int SCREEN_H);

//Draws Robot's mouth that's filled in with gray
//Param: color, screen width, screen height
//Return: filled in rectangle
void draw_filled_rectangle(ALLEGRO_COLOR color, const int SCREEN_W, const int SCREEN_H);

//Draws Robot's feet that are filled in ellipse
//Param: color, screen width, screen height
//Return: filled in ellipse
void draw_filled_ellipse(ALLEGRO_COLOR color, const int SCREEN_W, const int SCREEN_H);

int main(int argc, char** argv) {
	ALLEGRO_DISPLAY *display = NULL;
	int width = 800;
	int height = 600;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(width, height);
	if (!display) {
		fprintf(stderr, "failed to initialize display!\n");
		return -1;
	}

	al_init_primitives_addon();
	bool clear = false;
	bool done = false;
	srand(time(NULL));

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	al_install_keyboard();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		draw_rectangle(makeColor(), width, height);
		draw_filled_rectangle(makeColorGray(), width, height);
		draw_triangle(makeColor(), width, height);
		draw_filled_circle(makeColorGray(), width, height);
		draw_filled_ellipse(makeColorGray(), width, height);

		if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_SPACE:
				clear = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}

		al_flip_display();
		if (clear == true) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			clear = false;
		}
	}
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}


ALLEGRO_COLOR makeColor() {
	int red = rand() % 255;
	int green = rand() % 255;
	int blue = rand() % 255;

	return (al_map_rgb(red, green, blue));
}

ALLEGRO_COLOR makeColorGray() {
	int red = 155;
	int green = 155;
	int blue = 155;

	return (al_map_rgb(red, green, blue));
}

void draw_rectangle(ALLEGRO_COLOR color, const int SCREEN_W, const int SCREEN_H) {
	
	//Body
	int x = (SCREEN_W - 500);
	int y = (SCREEN_H - 400);
	int x2 = (SCREEN_W - 300);
	int y2 = (SCREEN_H - 200);
	float thickness = 10;
	al_draw_rectangle(x, y, x2, y2, color, thickness);
	
	//Neck
	int x3 = (SCREEN_W - 425);
	int y3 = (SCREEN_H - 450);
	int x4 = (SCREEN_W - 375);
	int y4 = (SCREEN_H - 410);
	float thickness2 = 6;
	al_draw_rectangle(x3, y3, x4, y4, color, thickness2);

	//Head
	int x5 = (SCREEN_W - 460);
	int y5 = (SCREEN_H - 525);
	int x6 = (SCREEN_W - 340);
	int y6 = (SCREEN_H - 457);
	al_draw_rectangle(x5, y5, x6, y6, color, thickness2);

	//Left arm
	int x7 = (SCREEN_W - 520);
	int y7 = (SCREEN_H - 340);
	int x8 = (SCREEN_W - 565);
	int y8 = (SCREEN_H - 250);
	al_draw_rectangle(x7, y7, x8, y8, color, thickness2);

	//Right arm
	int x9 = (SCREEN_W - 283);
	int y9 = (SCREEN_H - 340);
	int x10 = (SCREEN_W - 237);
	int y10 = (SCREEN_H - 250);
	al_draw_rectangle(x9, y9, x10, y10, color, thickness2);
	
	//Left leg
	int x11 = (SCREEN_W - 320);
	int y11 = 220 + (SCREEN_H - 408);
	int x12 = (SCREEN_W - 300);
	int y12 = 410 + (SCREEN_H - 515);
	al_draw_rectangle(x11, y11, x12, y12, color, thickness2);

	//Right leg
	int x13 = (SCREEN_W - 500);
	int y13 = 220 + (SCREEN_H - 408);
	int x14 = (SCREEN_W - 480);
	int y14 = 410 + (SCREEN_H - 515);
	al_draw_rectangle(x13, y13, x14, y14, color, thickness2);
}

void draw_filled_rectangle(ALLEGRO_COLOR color, const int SCREEN_W, const int SCREEN_H) {
	int xx = (SCREEN_W - 425);
	int yy = (SCREEN_H - 480);
	int xx2 = (SCREEN_W - 375);
	int yy2 = (SCREEN_H - 470);
	al_draw_filled_rectangle(xx, yy, xx2, yy2, color);
}

void draw_filled_circle(ALLEGRO_COLOR color, const int SCREEN_W, const int SCREEN_H) {
	int cx = (SCREEN_W - 430);
	int cy = (SCREEN_H - 500);
	int cr = 15;
	al_draw_filled_circle(cx, cy, cr, color);

	int cx2 = (SCREEN_W - 370);
	int cy2 = (SCREEN_H - 500);
	al_draw_filled_circle(cx2, cy2, cr, color);

	int cx3 = (SCREEN_W - 543);
	int cy3 = (SCREEN_H - 224);
	int cr3 = 30;
	al_draw_filled_circle(cx3, cy3, cr3, color);

	int cx4 = (SCREEN_W - 259);
	int cy4 = (SCREEN_H - 224);
	int cr4 = 30;
	al_draw_filled_circle(cx4, cy4, cr4, color);
}

void draw_filled_ellipse(ALLEGRO_COLOR color, const int SCREEN_W, const int SCREEN_H) {
	int ex = (SCREEN_W - 505);
	int ey = 427 + (SCREEN_H - 515);
	int rx = 40;
	int ry = 17;
	al_draw_filled_ellipse(ex, ey, rx, ry, color);

	int ex2 = (SCREEN_W - 295);
	int ey2 = 427 + (SCREEN_H - 515);
	int rx2 = 40;
	int ry2 = 17;
	al_draw_filled_ellipse(ex2, ey2, rx2, ry2, color);
}

void draw_triangle(ALLEGRO_COLOR color, const int SCREEN_W, const int SCREEN_H) {
	int x1 = (SCREEN_W - 505);
	int y1 = (SCREEN_H - 398);
	int x2 = (SCREEN_W - 517);
	int y2 = (SCREEN_W - 550);
	int x3 = (SCREEN_W - 560);
	int y3 = (SCREEN_W - 550);
	int thickness = 6;
	al_draw_triangle(x1, y1, x2, y2, x3, y3, color, thickness);

	int x4 = (SCREEN_W - 300);
	int y4 = (SCREEN_H - 398);
	int x5 = (SCREEN_W - 283);
	int y5 = (SCREEN_W - 550);
	int x6 = (SCREEN_W - 237);
	int y6 = (SCREEN_W - 550);
	al_draw_triangle(x4, y4, x5, y5, x6, y6, color, thickness);
}