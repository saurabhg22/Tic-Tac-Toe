#include "tictactoe.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
using namespace std;
tictactoe::tictactoe() // constructor just clear the board and start a new game
{
	clearBoard();
	startGame();
}

void tictactoe::startGame() {
	if (mode == '\0')
		mainMenu();
	clearBoard();
	playGame();
}


void tictactoe::mainMenu() {
	printf("-----Welcome to the TicTacToe Game----\n\n");
	printf("Multiplayer or SinglePlayer (M/S): ");
	cin >> mode;
	if (mode == 'm' || mode == 'M') {
		printf("Enter name of 1st Player: ");
		cin.clear(); cin.ignore(INT_MAX, '\n');
		getline(cin, name1, '\n');
		cout << "Enter " << name1 << "'s Symbol: ";
		cin >> sym1;
		printf("Enter name of 2nd Player: ");
		cin.clear(); cin.ignore(INT_MAX, '\n');
		getline(cin, name2, '\n');
		cout << "Enter " << name2 << "'s Symbol: ";
		cin >> sym2;
	}
	else if (mode == 's' || mode == 'S') {
		printf("Enter your name: ");
		cin.clear(); cin.ignore(INT_MAX, '\n');
		getline(cin, name1, '\n');
		cout << "Enter your Symbol: ";
		cin >> sym1;
		cout << "Enter A.I.'s Symbol: ";
		cin >> sym2;
	}
}

void tictactoe::playGame() {
	curerntPlayerName = name1;
	curerntPlayerSym = sym1;
	bool isDone = false;
	int x, y;
	turns = 0;
	while (!isDone) {
		displayBoard();
		cout << "\n\n" << curerntPlayerName << "'s Move:\n";

		// input coordinates of player's move and varify them
	here:
		x = getXcord();
		y = getYcord();
		if (board[y][x] != ' ') {
			cout << "That Spot is occupied!!..\n";
			goto here;
		}
		//now the user has entered the right coordinates so we just set the board's value at that coordinates
		board[y][x] = curerntPlayerSym;
		turns++;
		if (checkForVictory()) {
			displayBoard();
			cout << "\nThe Game is Over!!!...\n\n" << curerntPlayerName << " has won!.\n\nWant to play more.(y/n): ";
			cin >> choice;
			isDone = true;
		}
		// if no one wins and 9 turns are passed , then it's a tie
		else if (turns == 9) {
			displayBoard();
			cout << "\nThe Game is Over!!!...\n\n" << "It's a Tie.\n\nWant to play more.(y/n): ";
			cin >> choice;
			isDone = true;
		}
		if (!isDone)
			changeplayer(&isDone);
	}
	if (choice == 'y' || choice == 'Y')
		startGame();
	else
		exit(0);
}



void tictactoe::clearBoard() {
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			board[y][x] = ' ';
		}
	}
}

void tictactoe::displayBoard() {
	printf("\n\n");
	for (int y = 0; y < 3; y++) {
		cout << "\t ";
		for (int x = 0; x < 3; x++) {
			cout << " " << board[y][x] << " ";
			if (x != 2)
				cout << "|";
			else
				cout << " ";
		}
		if (y != 2)
			printf("\n\t ---|---|---\n");
	}
	printf("\n");
}

void tictactoe::changeplayer(bool* isDone) {
	//for multiplayer mode it detects the currentplayer & changes the currentplayer to the another one
	if (mode == 'm' || mode == 'M') {
		if (curerntPlayerSym == sym1) {
			curerntPlayerName = name2;
			curerntPlayerSym = sym2;
		}
		else {
			curerntPlayerName = name1;
			curerntPlayerSym = sym1;
		}
	}
	//In singleplayer mode it playes A.I.'s turn
	else {
		turns++;
		performMove(sym2, board);
		if (checkForVictory()) {
			displayBoard();
			cout << "\nThe Game is Over!!!...\n\nA.I. has won!.\n\nWant to play more.(y/n): ";
			cin >> choice;
			*isDone = true;//to exit from the game loop in playGame()
		}
	}
}




void tictactoe::performMove(char sym, char board[][3]) {
	move bestMove = getBestMove(sym, board); // get the best move for A.I.
	board[bestMove.y][bestMove.x] = sym; // play the bestMove on board
}

int tictactoe::getXcord() {
	int x;
	cout << "Enter X co-ordinate: ";
	cin >> x;
	if (x < 1 || x>3) {
		cout << "Invalid Co-ordinate!!\n";
		x = getXcord() + 1;
	}
	return x - 1;
}


int tictactoe::getYcord() {
	int y;
	cout << "Enter Y co-ordinate: ";
	cin >> y;
	if (y < 1 || y>3) {
		cout << "Invalid Co-ordinate!!\n";
		y = getYcord() + 1;
	}
	return y - 1;
}


bool tictactoe::checkForVictory() {
	// checking in rows
	for (int i = 0; i < 3; i++) {
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
			return true;
	}
	// checking in coloumns
	for (int i = 0; i < 3; i++) {
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
			return true;
	}
	// checking in 1st diagonal
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
		return true;
	// checking in 2nd diagonal
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
		return true;
	return false;
}


//MinMax Algorithm using recursion
tictactoe::move tictactoe::getBestMove(char sym, char board[][3]) {

	//Base Case
	bool cv = checkForVictory();
	if (cv) {
		if (sym == sym2) {
			return move(10);
		}
		else {
			return move(-10);
		}
	}
	if (turns == 9)
		return move(0);

	std::vector<move> moves; // stores all possible moves
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			// can play only at empty position
			if (board[y][x] == ' ') {
				move newmove;
				newmove.x = x;
				newmove.y = y;
				board[y][x] = sym;
				turns++;
				if (sym == sym2) {
					newmove.score = getBestMove(sym1, board).score;
				}
				else {
					newmove.score = getBestMove(sym2, board).score;
				}
				moves.push_back(newmove);
				board[y][x] = ' ';
				turns--;
			}
		}
	}
	int bestMove = 0;
	//best move for player1 is with highest score
	if (sym == sym1) {
		int bestScore = -10000;
		for (unsigned int i = 0; i < moves.size(); i++) {
			if (moves[i].score > bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	//best move for A.I. or player2 is with lowest score
	else {
		int bestScore = 10000;
		for (unsigned int i = 0; i < moves.size(); i++) {
			if (moves[i].score < bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	return moves[bestMove];
}