#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h> 
#include <time.h> 

typedef struct Duration {
	int hours;
	int minutes;
}Duration;

typedef struct node
{
	char Title[200];
	char Director[200];
	char Description[200];
	char Genre[200];
	Duration runtime;
	int Year;
	int TimesPlayed;
	int Rating;

	struct node* next;
	struct node* prev;
}node;

void load(FILE* infile, node** Head);
void store(FILE* outfile, node* Head);
void display(node* Head);
void edit(node** Head);
void rate(node** Head);
void play(node* Head);
void Exit(FILE* outfile, node* Head);
void insert(node** Head);
void delete(node** Head);
void shuffle(node* Head);
//void sorttitle(node** Head);