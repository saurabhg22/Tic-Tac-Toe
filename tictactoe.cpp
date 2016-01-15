#include "tictactoe.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <stdlib.h>
using namespace std;
tictactoe::tictactoe() // constructor just clear the board and start a new game
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	clearBoard();
	mode = '\0';

	outc = 114;
	inc = 115;
	aic = 124;
	pl1c = 117;
	pl2c = 121;
	brdc = 111;

	system("COLOR 70");
	startGame();

}

void tictactoe::startGame() {
	if (mode == '\0')
		mainMenu();
	clearBoard();
	playGame();
}


void tictactoe::mainMenu() {
	SetConsoleTextAttribute(hConsole, outc);
	printf("-----Welcome to the TicTacToe Game----\n\n");
	printf("Multiplayer or SinglePlayer (M/S): ");
	SetConsoleTextAttribute(hConsole, inc);
	cin >> mode;
	if (mode == 'm' || mode == 'M') {
		SetConsoleTextAttribute(hConsole, outc);
		printf("Enter name of 1st Player: ");
		cin.clear(); cin.ignore(INT_MAX, '\n');
		SetConsoleTextAttribute(hConsole, inc);
		getline(cin, name1, '\n');
		SetConsoleTextAttribute(hConsole, outc);
		cout << "Enter " << name1 << "'s Symbol: ";
		SetConsoleTextAttribute(hConsole, inc);
		cin >> sym1;
		SetConsoleTextAttribute(hConsole, outc);
		printf("Enter name of 2nd Player: ");
		SetConsoleTextAttribute(hConsole, inc);
		cin.clear(); cin.ignore(INT_MAX, '\n');
		getline(cin, name2, '\n');
		SetConsoleTextAttribute(hConsole, outc);
		cout << "Enter " << name2 << "'s Symbol: ";
		SetConsoleTextAttribute(hConsole, inc);
		cin >> sym2;
	}
	else if (mode == 's' || mode == 'S') {
		SetConsoleTextAttribute(hConsole, outc);
		printf("Enter your name: ");
		SetConsoleTextAttribute(hConsole, inc);
		cin.clear(); cin.ignore(INT_MAX, '\n');
		getline(cin, name1, '\n');
		SetConsoleTextAttribute(hConsole, outc);
		cout << "Enter your Symbol: ";
		SetConsoleTextAttribute(hConsole, inc);
		cin >> sym1;
		SetConsoleTextAttribute(hConsole, outc);
		cout << "Enter A.I.'s Symbol: ";
		SetConsoleTextAttribute(hConsole, inc);
		cin >> sym2;
	}
}

void tictactoe::playGame() {
	curerntPlayerName = name1;
	curerntPlayerSym = sym1;
	bool isDone = false;
	int x, y;
	turns = 0;
	if (mode == 's' || mode == 'S') {
		SetConsoleTextAttribute(hConsole, outc);
		cout << "Want to play first? (y/n): ";
		SetConsoleTextAttribute(hConsole, inc);
		cin >> playFirst;
	}
	while (!isDone) {
		if (playFirst == 'n' || playFirst == 'N') {
			changeplayer(&isDone);
			playFirst = 'y';
		}
		displayBoard();
		if (curerntPlayerSym == sym1)
			SetConsoleTextAttribute(hConsole, pl1c);
		else
			SetConsoleTextAttribute(hConsole, pl2c);
		cout << "\n\n" << curerntPlayerName << "'s Move:\n";

		// input coordinates of player's move and varify them
	here:
		x = getXcord();
		y = getYcord();
		if (board[y][x] != ' ') {
			SetConsoleTextAttribute(hConsole, outc);
			cout << "That Spot is occupied!!..\n";
			goto here;
		}
		//now the user has entered the right coordinates so we just set the board's value at that coordinates
		board[y][x] = curerntPlayerSym;
		turns++;
		if (checkForVictory()) {
			displayBoard();
			SetConsoleTextAttribute(hConsole, outc);
			cout << "\nThe Game is Over!!!...\n\n...Winner...\n\n";
			if(curerntPlayerSym == sym1)
				SetConsoleTextAttribute(hConsole, pl1c);
			else
				SetConsoleTextAttribute(hConsole, pl2c);
			cout << "...!!!!---" << curerntPlayerName << "---!!!!...";
			SetConsoleTextAttribute(hConsole, outc);
			cout << "\n\nWant to play more.(y/n): ";
			SetConsoleTextAttribute(hConsole, inc);
			cin >> choice;
			isDone = true;
		}
		// if no one wins and 9 turns are passed , then it's a tie
		else if (turns == 9) {
			displayBoard();
			SetConsoleTextAttribute(hConsole, outc);
			cout << "\nThe Game is Over!!!...\n\n...!!!!---It's a TIE---!!!!...\n\nWant to play more.(y/n): ";
			SetConsoleTextAttribute(hConsole, inc);
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
	int diff = (brdc / 16 - outc / 16)*16;

	printf("\n\n");
	for (int y = 0; y < 3; y++) {
		SetConsoleTextAttribute(hConsole, inc);
		cout << "\t";
		SetConsoleTextAttribute(hConsole, brdc);
		for (int x = 0; x < 3; x++) {
			cout << " ";
			if(board[y][x] == sym1)
				SetConsoleTextAttribute(hConsole, pl1c + diff);
			else if (board[y][x] == sym2) {
				if(mode == 'm' || mode == 'M')
					SetConsoleTextAttribute(hConsole, pl2c + diff);
				else
					SetConsoleTextAttribute(hConsole, aic + diff);
			}
			else
				SetConsoleTextAttribute(hConsole, brdc);
			cout << board[y][x];
			SetConsoleTextAttribute(hConsole, brdc);
			cout << " ";
			if (x != 2)
				cout << "|";
		}
		if (y != 2) {
			SetConsoleTextAttribute(hConsole, inc);
			printf("\n\t");
			SetConsoleTextAttribute(hConsole, brdc);
			printf("---|---|---");
			SetConsoleTextAttribute(hConsole, inc);
			printf("\n");
		}
	}
	SetConsoleTextAttribute(hConsole, inc);
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
		displayBoard();
		SetConsoleTextAttribute(hConsole, aic);
		cout << "\n Thinking......\n";
		turns++;
		performMove(sym2, board);
		if (checkForVictory()) {
			displayBoard();
			SetConsoleTextAttribute(hConsole, outc);
			cout << "\nGame is Over!!!...\n\n";
			SetConsoleTextAttribute(hConsole, aic);
			cout << "...!!!!---I WON---!!!!...";
			SetConsoleTextAttribute(hConsole, outc);
			cout << "\n\nWant to play more.(y / n) : ";
			SetConsoleTextAttribute(hConsole, inc);cin >> choice;
			*isDone = true;//to exit from the game loop in playGame()
		}
		else if (turns == 9) {
			displayBoard();
			SetConsoleTextAttribute(hConsole, outc);
			cout << "\nThe Game is Over!!!...\n\n...!!!!---It's a TIE---!!!!...\n\nWant to play more.(y/n): ";
			SetConsoleTextAttribute(hConsole, inc);cin >> choice;
			*isDone = true;
		}
	}
}




void tictactoe::performMove(char sym, char board[][3]) {
	move bestMove = getBestMove(sym, board); // get the best move for A.I.
	board[bestMove.y][bestMove.x] = sym; // play the bestMove on board
}

int tictactoe::getXcord() {
	int x;
	SetConsoleTextAttribute(hConsole, outc);
	cout << "Enter X co-ordinate: ";
	SetConsoleTextAttribute(hConsole, inc);
	cin >> x;
	if (x < 1 || x>3) {
		SetConsoleTextAttribute(hConsole, outc);
		cout << "Invalid Co-ordinate!!\n";
		x = getXcord() + 1;
	}
	return x - 1;
}


int tictactoe::getYcord() {
	int y;
	SetConsoleTextAttribute(hConsole, outc);
	cout << "Enter Y co-ordinate: ";
	SetConsoleTextAttribute(hConsole, inc);
	cin >> y;
	if (y < 1 || y>3) {
		SetConsoleTextAttribute(hConsole, outc);
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
	if (turns == 10)
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

