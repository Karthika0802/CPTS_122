#pragma once
#include<iostream>
#include <string>
#include <time.h>       
#include <random>
#include <fstream>


using namespace std;

class GameWorld {
private:

	char Grid[5][5];//Creates the grid which the game will be played on
	char OG[5][5];//the original grid incase the player wants to restart
	int targeti;//this and targeti represent current location of user, updated for every finduser() call
	int targetj;
	int points;
	string PlayerName;


public:

	bool IsGameOver = false;//to check if games over

	GameWorld() {
		for (int i = 0; i < 5; i++) {//Creates empty grid. All empty spaces will contain a dash -
			for (int j = 0; j < 5; j++) {
				Grid[i][j] = '-';
			}
		}

		//Now to randomize  and place everything
		RandomPlace('w');
		RandomPlace('u');
		RandomPlace('g');
		int numpit = rand() % 10 + 5;

		//between 5 and 10 pits. seems a bit excessive but meh
		for (int i = 0; i < numpit; i++) {
			RandomPlace('p');
		}

		//store a copy of the grid in case of reset
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				OG[i][j] = Grid[i][j];
			}
		}

		SetPlayerName();
		points = 2;//set to two to account for first call of display visible world
	}

	void SetPlayerName() {
		cout << "Please enter player name" << endl;
		cin >> PlayerName;
		cout << "Welcome to the game " << PlayerName << endl;
	}

	void Restart(bool IsNewPlayer) {
		cout << "Restarting game!";
		if (IsNewPlayer == true) {
			SetPlayerName();
		}

		//Sets Grid back to the original grid
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				Grid[i][j] = OG[i][j];
			}
		}

		//to go thru restart procedures
		points = 2;
		cout << "Here's the visible world! First time free!" << endl;
		displayVisibleWorld();
	}

	void RandomPlace(char place) {
		//To randomly place stuff in the grid
		int n1;
		int n2;
		bool check = false;
		do {
			n1 = rand() % 5;
			n2 = rand() % 5;

			if (Grid[n1][n2] == '-') {
				Grid[n1][n2] = place;
				check = true;
			}
		} while (check == false);
	}

	void displayEntireWorld() {
		for (int i = 0; i < 5; i++) {//Print the entire world!
			for (int j = 0; j < 5; j++) {
				cout << Grid[i][j];
			}
			cout << endl;
		}
		cout << endl << "That'll be 5 points please" << endl;
		points = points - 5;
	}


	void displayVisibleWorld() {

		findUser();///updates current position of user

		for (int i = 0; i < 5; i++) {//Print visible entire world!
			for (int j = 0; j < 5; j++) {
				if (abs(i - targeti) <= 1 && abs(j - targetj) <= 1) {
					cout << Grid[i][j];
				}
				else {
					cout << '-';
				}
			}
			cout << endl;
		}
		cout << endl << "That'll be 2 points please" << endl;
		points = points - 2;

	}

	void moveUp() {
		findUser();
		move(targeti - 1, targetj);
	}

	void moveDown() {
		findUser();
		move(targeti + 1, targetj);
	}

	void moveLeft() {
		findUser();
		move(targeti, targetj - 1);
	}

	void moveRight() {
		findUser();
		move(targeti, targetj + 1);
	}

	void move(int newi, int newj) {
		//haha generic functions go brr
		if (newi < 0 || newj < 0 || newi>4 || newj>4) {
			cout << "Oh no! You tried to move but it was off the map!" << endl;
			return;
		}

		else {

			bool win = haveIWon(newi, newj);
			bool loss = AmIDead(newi, newj);
			if (win == true || loss == true) {
				GameOver(win);
			}
			else {
				Grid[targeti][targetj] = '-';
				Grid[newi][newj] = 'u';
				cout << "Moved! Here's 5 points for that" << endl;
				points += 5;//You survived! Have some points!
			}
		}
	}

	bool haveIWon(int newi, int newj) {
		if (Grid[newi][newj] == 'g') {
			return true;
		}
		else {
			return false;
		}
	}

	bool AmIDead(int newi, int newj) {
		//checks if player is dead, changed slightly from instructions dunno if that's ok

		if (Grid[newi][newj] == 'w' || Grid[newi][newj] == 'p') {
			return true;
		}
		else {
			return false;
		}
	}


	bool findUser() {//Updates location of the user

		for (int i = 0; i < 5; i++) {//Print the entire world!
			for (int j = 0; j < 5; j++) {
				if (Grid[i][j] == 'u') {
					targeti = i;
					targetj = j;
					return true;

				}
			}
		}
		cout << "Could not find"<<endl;
		return false;

	}

	void GameOver(bool win) {
		//games over but did you win?

		//time to write to file!
		ofstream scores;
		scores.open("GameScores.txt", ofstream::out | ofstream::app);
		if (win == true) {
			cout << "Congrats you won!";
			scores << PlayerName << " was a winner with " << points << " points" << endl;
		}
		else {
			cout << "haha you died";
			scores << PlayerName << " was a loser with " << points << " points" << endl;

		}
		IsGameOver = true;
	}

};