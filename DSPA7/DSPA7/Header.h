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

class Account {
	protected:
		double Balance = 0;
		int NumDeposits = 0;
		int NumWithdrawals = 0;
		double AnnIntrstRate = 0;// Annual interest rate
		double MonSrvChrgs = 0;//Monthly Service Charges

	public:
		Account(double inpBal, double inpAnnIntrst) {
			Balance = inpBal;
			AnnIntrstRate = inpAnnIntrst;
		}

		void Deposit(double AmtDpst) {
			Balance = Balance + AmtDpst;
			NumDeposits++;
		}

		void Withdraw(double AmtWtdraw) {
			Balance = Balance - AmtWtdraw;
			NumWithdrawals++;
		}

		void calcIntrst() {
			double MonIntrstRate = AnnIntrstRate / 12; //Calculates monthly interest rate
			Balance = (Balance * MonIntrstRate) + Balance;//Adds monthly intrest
		}

		void monthlyProc() {
			//Fees and interest
			Balance = Balance - MonSrvChrgs;
			calcIntrst();
			
			//reset to zero 
			NumDeposits = 0;
			NumWithdrawals = 0;
			MonSrvChrgs = 0;
			
		}
};

class SavingAcc : public Account {
	private:
		bool Status = false;
	public:

		SavingAcc(double inpBal, double inpAnnIntrst) : Account(inpBal, inpAnnIntrst) {
			CheckStatus();
		}

		void CheckStatus() {
			if (Balance >= 25) {
				Status = true;
			}
			else {
				Status = false;
			}
		}

		void Deposit(double AmtDpst) {
			Account::Deposit(AmtDpst);
			CheckStatus();
		}

		void Withdraw(double AmtWtdraw) {
			if (Status == true) {
				Account::Withdraw(AmtWtdraw);
				CheckStatus();
			}
			else{
				cout << "Error: Savings account inactive! Balance too low!" << endl;
			}
		}

		void monthlyProc() {
			if (NumWithdrawals > 4) {
				MonSrvChrgs = MonSrvChrgs + ((double)NumWithdrawals - 4);//Adds a dollar charge for every deposit over 4
			}
			Account::monthlyProc();
		}


};

class CheckingAcc : public Account {
	public:

		CheckingAcc(double inpBal, double inpAnnIntrst) : Account(inpBal, inpAnnIntrst) {
		}

		void Withdraw(double AmtWtdraw) {
			double ChkBal = Balance - AmtWtdraw;//Checks what new balance *would* be prior to actually transacting

			if (ChkBal >= 0) {//If balance would stay over 0
				Account::Withdraw(AmtWtdraw);
			}
			else {//Means balance would fall under 0! Withdrawal not made
				Balance = Balance - 15;
			}
		}

		void monthlyProc() {
			MonSrvChrgs = 5 + ((double)NumWithdrawals * .1);
			Account::monthlyProc();

		}
};