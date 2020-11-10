#include "Header.h"
#include "Declarations.h"

int main() {
	srand(time(NULL));

	CardList TheList;
	cout << "Creating profiles for players" << endl;
	cout << "Creating profile for player 1!" << endl;
	Player Player1(TheList);
	cout << "Creating profile for player 2!" << endl;
	Player Player2(TheList);

	int choice = 0;



	//Menu
	do {
		cout << "Menu\n1. Recreate player profiles\n2.Battle\n3.Trade cards\n4. Quit game" << endl;
		cin >> choice;

		if (choice == 1) {
			cout << "Creating profiles for players" << endl;
			cout << "Creating profile for player 1!" << endl;
			Player Player1(TheList);
			cout << "Creating profile for player 2!" << endl;
			Player Player2(TheList);
			choice == 0;
		}

		else if (choice == 2) {
			cout << "Flipping a coin to see who goes first" << endl;
			int coin = rand() % 1; //0 means player 1 goes first, 1 means player 2 does
			if (coin == 0) {
				cout << "Player 1 goes first" << endl;
				Game(Player1, Player2, "Player 1", "Player 2");
				
			}
			else if (coin == 1) {
				cout << "Player 2 goes first" << endl;
				Game(Player2, Player1, "Player 2", "Player 1");

			}
		}

		else if (choice == 3) {
			Trade(Player1, Player2);
			choice = 0;
		}

		else if (choice == 4) {
			cout << "Quitting game" << endl;
		}

		else {
			cout << "Invalid input" << endl;
			choice = 0;
		}


	} while (choice == 0);

}