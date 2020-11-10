#include "Header.h"

int main() {
	srand(time(NULL));
	GameWorld TheGame;
	cout << "Here's the visible world! First time free!"<<endl;
	TheGame.displayVisibleWorld();
	char choice = '-';

	do {

		cout << "Menu:\ni or I will move the player up\nk or K will move the player down\nj or J will move the player to the left\nl or L will move the player to the right\nv or V will use the display VisibleWorld show what is in the caves adjacent to the player\nc or C will cheat and show the entire state of the game using displayEntireWorld function\nr or R will restart the game with the same player\nn or N will restart the game with a new player\nq or Q will end the game" << endl;


		cin >> choice;
		choice = tolower(choice);
		
		if(choice=='i') {
			TheGame.moveUp();
		}
		else if (choice == 'j') {
			TheGame.moveLeft();
		}
		else if (choice == 'k') {
			TheGame.moveDown();
		}
		else if (choice == 'l') {
			TheGame.moveRight();
		}
		else if (choice == 'v') {
			TheGame.displayVisibleWorld();
		}
		else if (choice == 'c') {
			TheGame.displayEntireWorld();
		}
		else if (choice == 'r') {
			TheGame.Restart(false);//restart with same player;
		}
		else if (choice == 'n') {
			TheGame.Restart(true);
		}
		else if (choice == 'q') {
			cout << "Ending game!" << endl;
			TheGame.GameOver(false);//Forcefully ends game, considered a loss
		}
		else {
			cout << "invalid input, please enter something valid" << endl;
		}
		
	} while (TheGame.IsGameOver == false);



}