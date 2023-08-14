#include "logic.h"
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Constructor
logic::logic()
{
	if (!createLists())
	{
		fprintf(stderr, "Error! Couldn't read file.\n");
		exit(0);
	}
	int numCorrect = 0;
	int smallWordArrayLength = 0; //number of elements in small word array
	int mediumWordArrayLength = 0; //number of elements in medium word array
	int longWordArrayLength = 0; // number of elements in long word array
	string scrambledWord;
	string smallWords[50];
	string mediumWords[50];
	string longWords[50];
}

//Destructor
logic::~logic() 
{

}

//Prints game Instruction
void logic::introduction()
{
	cout << "Welcome to Word Unscrambler!\n";
	cout << "The objective of this game is to unscramble five words in less than 60 seconds.\n";
	cout << "At the end of the game, regardless of the outcome, your will be given a final score.\n";
	cout << "Ideally, the more words you unscramble, the more points you accumulate. So LET'S GET STARTED!\n\n";
}

//Reads file and places words in assigned arrays
//Returns: true if the file is successfully read
bool logic::createLists()
{
	ifstream newfile;
	string word = " ";
	int smallindex = 0;
	int medindex = 0;
	int longindex = 0;
	
	newfile.open("dictionary.txt");
	if (newfile.is_open()) {
		while (getline(newfile, word)) {
			if (word.length() <= 5) {
				smallWords[smallindex] = word;
				smallWordArrayLength += 1; 
				smallindex++;
			}
			else if (word.length() >= 8) {
				longWords[longindex] = word;
				longWordArrayLength += 1;
				longindex++;	
			}
			else {
				mediumWords[medindex] = word;
				mediumWordArrayLength += 1;
				medindex++;
			}
		}

		newfile.close();
		return true;
	}
	else {
		return false;
	}
}

//Conducts the actual game
//Returns: true if the user finishes the game
bool logic::playGame()
{
	int level = 1;
	while (numCorrect < 5) {
		string correctWord = getWord(numCorrect); //grabs word to be scrambled
		scrambledWord = scrambler(correctWord);
		string userWord = " ";
		cout << "\nLEVEL: " << level << endl;
		cout << "\nYour scrambled word is: " << scrambledWord << endl;

		//Loops until user gets correct answer
		while (true) {
			cout << "Your guess: ";
			cin >> userWord;
			if (userWord != correctWord) {
				cout << "\nPlease try again.\nYour scrambled word is: " << scrambledWord << endl;
			}
			else {
				break;
			}
		}
		numCorrect++;
		level++;
	}

	if (numCorrect == 5) {
		return true;
	}
	else {
		return false;
	}
}

//Gets a word from an array based on the number of correct words
//the user has already answered
//Param: number of correct answers
//Returns: the word
string logic::getWord(int numCorrect)
{
	srand((unsigned)time(NULL));
	int index = 0;
	if (numCorrect == 0) 
	{
		int index = rand() % (smallWordArrayLength);
		string smallwrd = smallWords[index];
		return smallwrd;
	}
	else if (numCorrect == 1)
	{
		int index = rand() % (smallWordArrayLength);
		string smallwrd = smallWords[index];
		return smallwrd;
	}
	else if (numCorrect == 2) 
	{
		int index = rand() % (mediumWordArrayLength);
		string medwrd = mediumWords[index];
		return medwrd;
	}
	else if (numCorrect == 3) 
	{
		int index = rand() % (longWordArrayLength);
		string longwrd = longWords[index];
		return longwrd;
	}
	else if (numCorrect == 4) 
	{
		int index = rand() % (longWordArrayLength);
		string longwrd = longWords[index];
		return longwrd;
	}
	else {
		return NULL;
	}
}

//This scrambles the words received from the getWord method
//Param: a word
//Returns: the scrambled word
string logic::scrambler(string &word)
{
	srand((unsigned)time(NULL));
	string scrambledWord = word;
	size_t length = scrambledWord.length();
	for (int i = 0; i < length; i++) 
	{
		int index1 = (rand() % length);
		int index2 = (rand() % length);

		char temp = scrambledWord[index1];
		scrambledWord[index1] = scrambledWord[index2];
		scrambledWord[index2] = temp;
	}

	return scrambledWord;
}

//The message printed if the user runs out of time
void logic::timeOut()
{
	cout << "\nGame over! Time has expired." << endl;
}

//Messages that will be printed at the end of the game
void logic::end()
{
	if (numCorrect == 2) {
		cout << "\nOh come on, it's not that hard. You only unscrambled " << numCorrect << " / 5 words" << endl;
	}
	else if (numCorrect == 3) {
		cout << "\nGreat job! You're smarter than you look. You unscrambled " << numCorrect << " / 5 words" << endl ;
	}
	else if (numCorrect == 4) {
		cout << "\nAh, you almost had it. You got to be quicker than that. You unscrambled " << numCorrect << " / 5 words" << endl;
	}
	else if (numCorrect == 5) {
		cout << "\nGame over!\nFantastic! You unscrabled all the words. Come back and play again!" << endl;
	}
	else {
		cout << "\nGame over!\nPlease just try again!" << endl;
	}
}