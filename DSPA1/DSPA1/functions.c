#include "Header.h"

double GetNum(char String[], int c, int PrevNum) {
	//if (strcmp(String, "\0")) {//data cleaning if null
	//	return PrevNum;
	//}
	//else {//if string is normal just give a number
	//	return atof(String);
	//}

	if (String && String[0]) {//make sure its valid
		return atof(String);
	}
	else {//clean by setting equal to most recent valid value
		return PrevNum;
	}
}

int DoesTimeExist(char Time[],FitbitData fitbit[],int c) {
	if (c == 0) {
		return 0;
	}
	for (int i = 0; i < c; i++) {
		if (strcmp(Time, fitbit[i].minute) == 0) {
			return 1;
		}
	}
	return 0;
}


