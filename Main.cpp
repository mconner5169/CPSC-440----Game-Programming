#include <allegro5/allegro.h>
#include <cstdlib>
#include <iostream>
#include "logic.h"
using namespace std;

logic game_logic;
bool finished = false;
bool out_of_time = false;

void* input(ALLEGRO_THREAD* ptr, void* arg);
void* timer(ALLEGRO_THREAD* ptr, void* arg);

int main(int argc, char* argv[])
{
	//Creates threads
	ALLEGRO_THREAD* gamePlay = NULL, * gameTimer = NULL;
	gamePlay = al_create_thread(input, NULL);
	gameTimer = al_create_thread(timer, NULL);

	//Introduces the game
	game_logic.introduction();
	system("pause");

	//Runs game until time runs out or user finishes game
	while (!finished && !out_of_time)
	{
		if (!finished && !out_of_time)
		{
			al_start_thread(gamePlay);
			al_start_thread(gameTimer);
		}
		else
		{
			al_destroy_thread(gamePlay);
			al_destroy_thread(gameTimer);
		}

	}
	
	if (out_of_time) 
	{
		game_logic.timeOut();
	}	
	
	//Prints game results regardless of outcome
	game_logic.end();

	game_logic.~logic();
	return 0;
}

// A pointer to a function that starts the game
// Param: the thread and any return argument type
// Return: Null
void* input(ALLEGRO_THREAD* ptr, void* arg)
{
	finished = game_logic.playGame();
	return NULL;
}
// A pointer to a function that starts the timer and checks the change in
// finished, to see which thread finishes first
// Param: the thread and any return argument type
// Return: Null
void* timer(ALLEGRO_THREAD* ptr, void* arg)
{
	time_t startTime, currentTime; //times used to measure elapsed time
	startTime = time(NULL);
	currentTime = time(NULL);
	while (currentTime - startTime < 60 && !finished)
	{
		currentTime = time(NULL);
	}
	out_of_time = true;
	return NULL;
}