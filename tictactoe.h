#pragma once
#include <string>
using std::string;
class tictactoe
{
public:
	tictactoe();
	void startGame(); // to initialize the game
	void mainMenu();
private:
	struct move // this is an A.I.'s move
	{
		move() {};
		move(int s) { score = s; }
		int x;
		int y;
		int score;
	};
	int turns; // store no. of turns for both A.I and Players
	char  board[3][3];
	char sym1, sym2, curerntPlayerSym, choice;//symbol of player1 and player2
	char  mode = '\0',playFirst;
	string name1, name2, curerntPlayerName;
	void playGame(); // main game loop
	void clearBoard();
	void displayBoard();
	void changeplayer(bool*); // In multiplayer mode it just changes the player but in single player mode it playes the A.I. move through perfomMove()
	void performMove(char, char[][3]); //To perform AI move
	int getXcord(); // to input x co-ordinate of player's move
	int getYcord(); // to input y co-ordinate of player's move
	bool checkForVictory();
	move getBestMove(char, char[][3]); // It get the best move for A.I.
};

