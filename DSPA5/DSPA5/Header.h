#pragma once
#include<iostream>
#include <string>
#include <time.h>       
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

struct Card {
	//Basic card structure
	string Name;
	int Atk;
	int Def;
	string Type;
	bool Played = false;//For use in hand, will be set to true once played
};

class CardList {
	//Gets cards from the csv and stores them in a deck
	public:
		Card TheList[150];

		CardList() {
			ifstream CList;
			CList.open("Yu_Gi_Oh_card_list.csv");
			string line;
			string tok;
			getline(CList, line);
			int Index = 0;
			while (getline(CList, line))
			{
				istringstream ss(line);
				
				int CommaCount = std::count(line.begin(), line.end(), ',');//Counts number of commas
				
				if (CommaCount == 7) {//If there are 7 commas instead of 6, that means there is a comma in the name
					getline(ss, tok, ',');//Name part A
					string PartA = tok;
					getline(ss, tok, ',');
					TheList[Index].Name = PartA +","+tok;
				}
				else {//If there are the standard 6 commas instead
					getline(ss, tok, ',');//Name
					TheList[Index].Name = tok;
				}
				getline(ss, tok, ',');//Type
				TheList[Index].Type = tok;

				//The uneeded variables, to be read and discarded
				getline(ss, tok, ',');//Level
				getline(ss, tok, ',');//Race
				getline(ss, tok, ',');//Attribute

				getline(ss, tok, ',');//Atk
				TheList[Index].Atk = stoi(tok);


				getline(ss, tok, ',');//Defense
				TheList[Index].Def = stoi(tok);



				Index++;
				
			}

		}


};

typedef struct Deck {
	//old, no longer used
	Card data;
	struct Deck* next;
}Deck;

class Player {
	
	private:

		int LifePoints;

		Card Hand[5];

		int DeckSize = 0;
		//Set up for the deck

		stack<Card> mystack;//the deck
		queue<Card> AtkQueue;
		queue<Card> DefQueue;
		
		int Mode = 0; //1 for atk mode 2 for def mode
		
		Card Trade;


	public:
		Player(CardList List) {
			//Constructor

			//Initialize 
			LifePoints = 8000;
			Trade.Name == "Empty Man"; //Signal that is empty
			
			//Intialize deck
			int choice;
			do {
				choice = 0;
				cout << "Deck Builder: Press 1 to manually add card to deck, press 2 to autobuild the rest "<<endl;
				cin >> choice;
				if(choice == 1){
					AddToDeck(List);
				}
				else if (choice == 2)
				{
					cout << "Autobuilding rest of your deck" << endl;
					while(DeckSize<30){
						//Will add random cards to deck until full
						Card d;
						int myrand = rand() % 149;

						d.Name = List.TheList[myrand].Name;
						d.Atk = List.TheList[myrand].Atk;
						d.Def = List.TheList[myrand].Def;
						d.Type = List.TheList[myrand].Type;

						cout << "Adding:" << d.Name << endl;
						if (!d.Name.empty())
						{
							mystack.push(d);
							DeckSize++;
							cout << DeckSize << endl;
						}
					}
					cout << "out" << endl;
				}
				else {
					cout << "Invalid input"<<endl;
				}
				cin.ignore();
			} while (DeckSize<30);

			cout << endl;

			//Initialize hand
			for (int i = 0; i < 5; i++) {
				Hand[i].Played = true;
			}
			//refillhand();
			
		}

		//Deck building!

		void AddToDeck(CardList List) {
			//To manually add cards to the list
			cin.ignore();
			cout << "Please enter the card you would like to add to your deck"<<endl;
			string Name;
			cin >> Name;
			for (int i = 0; i < 150; i++) {
				if (Name == List.TheList[i].Name) {
					cout << "Card Found!"<<endl;
					Card d;
					int myrand = i;

					d.Name = List.TheList[myrand].Name;
					d.Atk = List.TheList[myrand].Atk;
					d.Def = List.TheList[myrand].Def;
					d.Type = List.TheList[myrand].Type;

					cout << "Adding:" << d.Name << endl;
					if (!d.Name.empty())
					{
						mystack.push(d);
						DeckSize++;
					}
					return;
				}
			}
			cout << "Card not found." << endl;
		}

		//Hand building!

		void refillhand()//sDeck** top_ref) 
		{
			//refills all played cards
			for (int i = 0; i < 5; i++) {
				if (Hand[i].Played == true) {
					//memcpy((void*)&Hand[i], (void*)&pop(top_ref), sizeof(Card));
					Card d = mystack.top();
					Hand[i] = d;
					
					mystack.pop();
				}
			}
		}

		void printhand() {
			//print the current hand
			for (int i = 0; i < 5; i++) {
				if (Hand[i].Played == false) {
					cout << i << ". "<< Hand[i].Name << endl;
				}
			}
		}

		//Gameplay!

		void turn() {
			refillhand();//Let's fill up the player's hand!
			Mode = 0;//resetting the mode
			bool valid = false;

			cout << "You currently have " << LifePoints << " lifepoints" << endl;
			do {
				cout << "Please pick a card for your atk queue " << endl;
				printhand();
				int choice;
				cin >> choice;
				if (0 <= choice <= 4) {
					if (Hand[choice].Played == false) {
						cout << "Card added to attack queue!" << endl;
						AtkQueue.push(Hand[choice]);
						Hand[choice].Played = true;
						valid = true;
					}
					else {
						cout << "Please enter a valid choice" << endl;
					}
				}
				else {
					cout << "Please enter a valid choice" << endl;
				}
			} while (valid == false);

			valid = false;
			do {
				cout << "Please pick a card for your def queue " << endl;
				printhand();
				int choice;
				cin >> choice;
				if (0 <= choice <= 4) {
					if (Hand[choice].Played == false) {
						cout << "Card added to defense queue!" << endl;
						DefQueue.push(Hand[choice]);
						Hand[choice].Played = true;
						valid = true;
					}
					else {
						cout << "Please enter a valid choice" << endl;
					}
				}
				else {
					cout << "Please enter a valid choice" << endl;
				}
			} while (valid == false);
			
			
			do {
				cout << "Would you like to go on attack mode or defense mode? Press 1 for Attack and 2 for Defense" << endl;
				cin >> Mode;
				if (Mode != 1 && Mode != 2) {
					cout << "Invalid input." << endl;
				}
			} while (Mode != 1 && Mode != 2);



		
		}

		Card PlayDefense() {
			Card play = DefQueue.front();
			DefQueue.pop();
			return play;
		}

		Card PlayAttack() {
			Card play = AtkQueue.front();
			AtkQueue.pop();
			return play;
		}

		void Damage(int dmg) {
			LifePoints = LifePoints - dmg;
		}

		//Getters!
		int GetMode() {
			return Mode;
		}

		int GetLifePoints() {
			return LifePoints;
		}


		//Get element for trade

		void getForTrade(string Find, int curr = 0)
		{
			if (mystack.empty()) {
				return;
			}

			Card x = mystack.top();
			mystack.pop();

			// Remove other items 
			getForTrade(Find, curr + 1);

			// Return the card to be traded, otherwise put items back into the stack if they don't have the correct name 
			if (x.Name == Find) {
				Trade = x;
			}
			else {
				mystack.push(x);
			}
			

		}

		Card getTrade() {
			return Trade;
		}

		void receiveTrade(Card receive) {
			mystack.push(receive);
			Trade.Name = "Empty Man";
		}


		void printStack(int curr = 0)
		{

			if (mystack.empty()) {
				return;
			}

			Card x = mystack.top();
			mystack.pop();
			cout << curr << "." << x.Name << endl;
			printStack(curr + 1);
			mystack.push(x);


			

			}

	

		};


