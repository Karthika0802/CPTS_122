#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <math.h>

typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

typedef struct fitbit
{
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;

double GetNum(char String[], int c, int PrevNum);
int DoesTimeExist(char Time[], FitbitData fitbit[], int c);
