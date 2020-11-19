#include "Header.h"

int main() {
	//Tested with quickview and breakpoints instead of print statements

	Account testAcc(50,.03);
	testAcc.Deposit(5);
	testAcc.Withdraw(4);

	SavingAcc testSav(50, .03);
	testSav.Withdraw(45);
	testSav.Withdraw(5);
	testSav.Deposit(300);
	testSav.monthlyProc();

	CheckingAcc testCheck(50, .03);
	testCheck.Withdraw(40);
	testCheck.Withdraw(200);
	testCheck.Deposit(500);
	testCheck.monthlyProc();




}