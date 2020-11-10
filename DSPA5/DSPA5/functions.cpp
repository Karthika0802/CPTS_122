#include "Header.h"

void Game(Player PlayerA, Player PlayerB, string NameA, string NameB) {

	bool GameOver = false;

	do {
		//Queuing
		cout << NameA << "'s turn: " << endl;
		PlayerA.turn();
		cout << "Turn over, please click enter to clear screen and give the computer to the other player" << endl;
		cin.ignore();
		system("CLS");
		cout << NameB << "'s turn: " << endl;
		PlayerB.turn();
		cout << "Turn over, please click enter to clear screen and give the computer to the other player" << endl;
		cin.ignore();
		system("CLS");

		Card CardA;
		Card CardB;



		//Life points calculation

		//Both players play defense
		if (PlayerA.GetMode() == 2 && PlayerB.GetMode() == 2) {
			cout << "Both players activated defense queue!" << endl;

			CardA = PlayerA.PlayDefense();
			CardB = PlayerB.PlayDefense();

			cout << NameA << " played " << CardA.Name << endl;
			cout << NameB << " played " << CardB.Name << endl;
			cout << "Nothing happened!" << endl;

		}

		//Both players play attack
		else if (PlayerA.GetMode() == 1 && PlayerB.GetMode() == 1) {
			cout << "Both players activated attack queue!" << endl;

			CardA = PlayerA.PlayAttack();
			CardB = PlayerB.PlayAttack();

			cout << NameA << " played " << CardA.Name << endl;
			cout << NameB << " played " << CardB.Name << endl;

			if (CardA.Atk > CardB.Atk) {
				cout << NameB << "received " << CardA.Atk - CardB.Atk << " damage!" << endl;
				PlayerB.Damage(CardA.Atk - CardB.Atk);
			}
			else if (CardA.Atk < CardB.Atk) {
				cout << NameA << "received " << CardB.Atk - CardA.Atk << " damage!" << endl;
				PlayerB.Damage(CardB.Atk - CardA.Atk);
			}
			else
			{
				cout << "Both cards had the same attack! No damage dealt!" << endl;
			}
		}

		//Player A attacks but Player B defends

		else if (PlayerA.GetMode() == 1 && PlayerB.GetMode() == 2) {
			cout << NameA << " activated the attack queue but " << NameB << " activated the defense queue" << endl;

			CardA = PlayerA.PlayAttack();
			CardB = PlayerB.PlayDefense();

			cout << NameA << " played " << CardA.Name << endl;
			cout << NameB << " played " << CardB.Name << endl;

			cout << "If negative damage has been assigned, then " << NameB << " has been healed by that amount" << endl;
			cout << NameB << "received " << CardA.Atk - CardB.Atk << " damage!" << endl;
			PlayerB.Damage(CardA.Atk - CardB.Def);

		}

		//Player A defends but Player B attacks

		else if (PlayerB.GetMode() == 2 && PlayerA.GetMode() == 1) {
			cout << NameB << " activated the attack queue but " << NameA << " activated the defense queue" << endl;

			CardB = PlayerB.PlayAttack();
			CardA = PlayerA.PlayDefense();

			cout << NameB << " played " << CardB.Name << endl;
			cout << NameA << " played " << CardA.Name << endl;

			cout << "If negative damage has been assigned, then " << NameA << " has been healed by that amount" << endl;
			cout << NameA << "received " << CardB.Atk - CardA.Atk << " damage!" << endl;
			PlayerA.Damage(CardB.Atk - CardA.Def);

		}

		//Checks if game is over
		if (PlayerA.GetLifePoints() <= 0) {
			cout << NameA << " has died! " << NameB << "wins! " << endl;
			GameOver == true;
		}

		if (PlayerB.GetLifePoints() <= 0) {
			cout << NameB << " has died! " << NameA << "wins! " << endl;
			GameOver == true;
		}


	} while (GameOver == false);

}


void Trade(Player Player1, Player Player2) {
	string input;
	
	cout << "Player 1, here are your cards. " << endl;
	Player1.printStack();
	cout << "Player 1, please enter the name of the card you would like to trade. " << endl;
	cin >> input;
	Player1.getForTrade(input);
	Card CardA = Player1.getTrade();
	if (CardA.Name == "Empty Man") {
		cout << "Invalid card" << endl;
		return;
	}


	cout << "Player 2, here are your cards. " << endl;
	Player2.printStack();
	cout << "Player 2, please enter the name of the card you would like to trade. " << endl;
	cin >> input;
	Player2.getForTrade(input);
	Card CardB = Player2.getTrade();
	if (CardA.Name == "Empty Man") {
		cout << "Invalid card" << endl;
		return;
	}

	cout << "Cards traded!";

	Player1.receiveTrade(CardB);
	Player2.receiveTrade(CardA);


}