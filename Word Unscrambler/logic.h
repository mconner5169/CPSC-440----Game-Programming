#include <string>
using namespace std;
class logic
{
public:
	logic(); //constructor
	~logic(); //destructor
	void introduction(); //provides a game introduction message to the user
	bool createLists(); //Opens a file and reads in the list of words that can be scrambled
	bool playGame(); //starts the game
	string getWord(int numCorrect); //retrives word from correct array
	string scrambler(string &word); //scrambles the words
	void timeOut(); //displays message if timer runs out
	void end(); //displays end of game message and results
private:
	int numCorrect;
	int smallWordArrayLength;
	int mediumWordArrayLength;
	int longWordArrayLength;
	string scrambledWord;
	string smallWords[50];
	string mediumWords[50];
	string longWords[50];
};