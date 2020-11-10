/*******************************************************************************************
* Programmer: Karthik Ayyalasomayajula *
* Class: CptS 122, Fall, 2020; Lab Section 4 *
* Programming Assignment: PA1 *
* Date: 9/4/20 *
* Description: Reads fitbit data from csv and outputs certain values back. *
*******************************************************************************************/

#include "Header.h"


int main()
{

	//Getting the Data
	FILE* infile = fopen("FitbitData.csv", "r");
	FILE* outfile = fopen("output.csv", "w");
	char read[500];
	fscanf(infile, "%s", &read);//to get rid of the first row
	FitbitData fitbit[1440];
	int c = 0; //counts all valid loops
	while(!feof(infile)){//loops to end of file
		fscanf(infile, "%s", &read);
		char Patient[50];
		char Minute[50];
		strcpy(Patient, strtok(read, ","));
		strcpy(Minute, strtok(NULL, ","));
		int IsTimeClean = DoesTimeExist(Minute, fitbit, c); // 0 if clean, 1 if time already exists
		if (strcmp(Patient, "12cx7") == 0 && IsTimeClean == 0 && c < 1440) {//checks to make sure patient is right and no non duplicate times
			//The Strings
			strcpy(fitbit[c].patient, Patient);
			strcpy(fitbit[c].minute, Minute);
			
			if (c == 0) {//for first run only
				fitbit[c].calories = atof(strtok(NULL, ","));
				fitbit[c].distance = atof(strtok(NULL, ","));
				fitbit[c].floors = atof(strtok(NULL, ","));
				fitbit[c].heartRate = atof(strtok(NULL, ","));
				fitbit[c].steps = atof(strtok(NULL, ","));
				fitbit[c].sleepLevel = atof(strtok(NULL, ","));
			}
			else {
				fitbit[c].calories = GetNum(strtok(NULL, ","), c, fitbit[c - 1].calories);
				fitbit[c].distance = GetNum(strtok(NULL, ","), c, fitbit[c - 1].distance);
				fitbit[c].floors = GetNum(strtok(NULL, ","), c, fitbit[c - 1].floors);
				fitbit[c].heartRate = GetNum(strtok(NULL, ","), c, fitbit[c - 1].heartRate);
				fitbit[c].steps = GetNum(strtok(NULL, ","), c, fitbit[c - 1].steps);
				fitbit[c].sleepLevel = GetNum(strtok(NULL, ","), c, fitbit[c - 1].sleepLevel);
			}

			/*printf("\n%s", fitbit[c].patient);
			printf("\n%s", fitbit[c].minute);
			printf("\n%lf", fitbit[c].calories);
			printf("\n%lf", fitbit[c].distance);
			printf("\n%d", fitbit[c].floors);
			printf("\n%d", fitbit[c].heartRate);
			printf("\n%d", fitbit[c].steps);
			printf("\n%d", fitbit[c].sleepLevel);*/

			c++;//haha
		}
		

	}
	
	//Using the data

	//The variables that need to be calculated
	double TotCal = 0;
	double TotWalk = 0;
	int TotFloors = 0;
	int TotSteps = 0;
	int InterHeart = 0;
	double AvgHeart = 0;
	int MaxSteps = 0;
	//Variables for poor sleep
	int IsPoorSleep = 0;//Checks if poor sleep is already started
	int CurrSleepScore = 0;//Sleep score for current bad sleep
	int MaxSleepScore = 0;//Current highest sleep score
	char CurrStart[50];
	char CurrEnd[50];
	char MaxStart[50];
	char MaxEnd[50];
	
	for (int i = 0; i < 1440; i++){
		TotCal += fitbit[i].calories;
		TotWalk += fitbit[i].distance;
		TotFloors += fitbit[i].floors;
		TotSteps += fitbit[i].steps;
		InterHeart += fitbit[i].heartRate;
		
		if (fitbit[i].steps >= MaxSteps) {//Max Steps
			MaxSteps = fitbit[i].steps;
		}

		//Sleep status stuff
		
		if (IsPoorSleep == 0 && fitbit[i].sleepLevel > 1) {
			IsPoorSleep = 1;
			strcpy(CurrStart,fitbit[i].minute);
			strcpy(CurrEnd,fitbit[i].minute);
			CurrSleepScore += fitbit[i].sleepLevel;
		}

		else if (IsPoorSleep == 1 && fitbit[i].sleepLevel > 1) {
			strcpy(CurrEnd, fitbit[i].minute);
			CurrSleepScore += fitbit[i].sleepLevel;
		}
		
		else if (IsPoorSleep == 1 && fitbit[i].sleepLevel <= 1) {//When current bout of poor sleep stops being counted
			IsPoorSleep = 0;
			if (CurrSleepScore >= MaxSleepScore) {
				strcpy(MaxStart,CurrStart);
				strcpy(MaxEnd, CurrEnd);
				MaxSleepScore = CurrSleepScore;
			}
			CurrSleepScore = 0;
		}
	}
	AvgHeart = InterHeart / 1440;

	//Now we just have to print
	fprintf(outfile, "Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Worst Sleep Range");
	fprintf(outfile, "\n%lf, %lf, %d, %d, %lf, %d, %s:%s",TotCal,TotWalk,TotFloors,TotSteps,AvgHeart,MaxSteps,MaxStart,MaxEnd);

	//Closing the files
	fclose(infile);
	fclose(outfile);

	return 0;
}