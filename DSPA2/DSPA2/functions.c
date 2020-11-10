#include "Header.h"
#include "TestHeader.h"


void load(FILE* infile, node** Head) {

	node* HoldNode = *Head; // holds previous loop's node
	node* CurrNode = NULL; //hold's current loops node
	//fgets
	char read[1000];
	//fscanf(infile, "%[^\n]", read);
	fgets(read, 1000, infile);//To get rid of first line
	while (!feof(infile)) {//loops to end of file
		
		CurrNode = (node*)malloc(sizeof(node)); 
		CurrNode->next = NULL;

		
		//fscanf(infile, "%[^\n]", read);
		fgets(read, 1000, infile);

		strcpy(CurrNode->Title, strtok(read, ","));
		strcpy(CurrNode->Director, strtok(NULL, ","));
		strcpy(CurrNode->Description, strtok(NULL, ","));
		strcpy(CurrNode->Genre, strtok(NULL, ","));
		CurrNode->runtime.hours = atof(strtok(NULL, ":"));
		CurrNode->runtime.minutes = atof(strtok(NULL, ","));
		CurrNode->Year = atof(strtok(NULL, ","));
		CurrNode->TimesPlayed = atof(strtok(NULL, ","));
		CurrNode->Rating = atof(strtok(NULL, ","));



		if (HoldNode == NULL) {//means list is empty
			*Head = CurrNode;
			HoldNode = CurrNode;
		}
		else {//list not empty, operate as normal
			CurrNode->prev = HoldNode;
			HoldNode->next = CurrNode;
			HoldNode = CurrNode;
		}
	}

	
}



void store(FILE* outfile, node* Head) {
	
	outfile = freopen("moviePlayList.csv", "w+", outfile);
	//fclose(fopen(*outfile, "w"));
	fprintf(outfile, "Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating");
	node* Current = Head;
	while (Current != NULL) {
		fprintf(outfile,"\n%s,%s,%s,%s,%d:%d,%d,%d,%d", Current->Title, Current->Director, Current->Description, Current->Genre, Current->runtime.hours, Current->runtime.minutes, Current->Year, Current->TimesPlayed, Current->Rating);
		Current = Current->next;
	}

}

void display(node* Head) {
	
	node* Current = Head;
	
	int choice = 0;
	printf("Please choose which records to display.\n1. Print all movies.\n2. Print all records that match a director.\n3. Print all records that match a year.\n ");
	scanf("%d", &choice);

	char DirSearch[50];
	int YearSearch = 0;

	if (choice == 2) {
		printf("\nPlease enter a director you want to search. Caps sensetive.\n");
		scanf(" %[^\n]s", &DirSearch);//Did some googling to figure out how to accept spaces
	}

	if (choice == 3) {
		printf("\nPlease enter a year you want to search.\n");
		scanf("%d", &YearSearch);
	}
	
	printf("Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating");

	while (Current != NULL) {
		if (choice == 1) {
			printf("\n\n%s,%s,%s,%s,%d:%d,%d,%d,%d", Current->Title, Current->Director, Current->Description, Current->Genre, Current->runtime.hours, Current->runtime.minutes, Current->Year, Current->TimesPlayed, Current->Rating);
		}
		else if (choice == 2 && strcmp(DirSearch, Current->Director) == 0) {
			printf("\n\n%s,%s,%s,%s,%d:%d,%d,%d,%d", Current->Title, Current->Director, Current->Description, Current->Genre, Current->runtime.hours, Current->runtime.minutes, Current->Year, Current->TimesPlayed, Current->Rating);
		}
		else if (choice == 3 && YearSearch == Current->Year) {
			printf("\n\n%s,%s,%s,%s,%d:%d,%d,%d,%d", Current->Title, Current->Director, Current->Description, Current->Genre, Current->runtime.hours, Current->runtime.minutes, Current->Year, Current->TimesPlayed, Current->Rating);
		}
		Current = Current->next;
	}
}


void edit(node** Head) {

	node* Current = *Head;
	int choice = 0;

	

	char DirSearch[50];


	printf("\nPlease enter a director you want to search by. Caps sensetive.\n");
	scanf(" %[^\n]s", &DirSearch);
	
	while (Current != NULL) {
		printf("boop");
		if (strcmp(DirSearch, Current->Director) == 0) {
			printf("MATCH FOUND: ");
			printf("\n\n%s,%s,%s,%s,%d:%d,%d,%d,%d", Current->Title, Current->Director, Current->Description, Current->Genre, Current->runtime.hours, Current->runtime.minutes, Current->Year, Current->TimesPlayed, Current->Rating);
			printf("\n\nWould you like to edit this entry or keep going? 1 to edit, any other key to continue\n");
			scanf("%d", &choice);
			while (choice == 1) {
				printf("\nPlease enter what you would like to edit next in this entry.\n 1. Title\n2.Director\n3.Description\n4.Genre\n5.Runtime\n6.Year\n7.Times Played\n8.Rating\nEnter any other number to exit\n");
				scanf("%d", &choice);
				if (choice == 1) {
					printf("\nPlease enter new title\n");
					scanf(" %[^\n]s", Current->Title);
				}
				if (choice == 2) {
					printf("\nPlease enter new director\n");
					scanf(" %[^\n]s", Current->Director);
					choice = 1;
				}
				
				if (choice == 3) {
					printf("\nPlease enter new Description\n");
					scanf(" %[^\n]s", Current->Description);
					choice = 1;
				}
				if (choice == 4) {
					printf("\nPlease enter new genre\n");
					scanf(" %[^\n]s", Current->Genre);
					choice = 1;
				}
				if (choice == 5) {
					printf("\nPlease enter new hours runtime\n");
					scanf("%d", &Current->runtime.hours);
					printf("\nPlease enter new minutes runtime\n");
					scanf("%d", &Current->runtime.minutes);

					choice = 1;
				}
				if (choice == 6) {
					printf("\nPlease enter new year\n");
					scanf("%d", &Current->Year);

					choice = 1;
				}
				if (choice == 7) {
					printf("\nPlease enter new Time Played\n");
					scanf("%d", &Current->TimesPlayed);

					choice = 1;
				}
				if (choice == 8) {
					printf("\nPlease enter new rating\n");
					scanf("%d", &Current->Rating);

					choice = 1;
				}

			}


		}
		Current = Current->next;

	}
}

void rate(node** Head) {

	char ourtitle[50];
	printf("\nPlease enter the name of the movie you want to change (caps sensetive)\n");
	scanf(" %[^\n]s", &ourtitle);
	node* Current = *Head;
	int newrating = 0;
	while (Current != NULL) {
		
		if (strcmp(ourtitle, Current->Title) == 0) {
			printf("Movie found! Please enter new rating!");
			scanf("%d", &newrating);
			Current->Rating = newrating;
		}
		
		Current = Current->next;
	}
	

}

void play(node* Head) {
	printf("Please enter the name of the movie you would like to start with (caps sensetive)");
	char ourtitle[50];
	node* Current = Head;
	node* Match = NULL;

	while (Current != NULL) {

		if (strcmp(ourtitle, Current->Title) == 0) {
			Match = Current;
		}

		Current = Current->next;
	}

	Current = Match;

	while (Current != NULL) {
		system("cls");

		printf("Will play for 10 seconds");
		
		printf("\n\n%s,%s,%s,%s,%d:%d,%d,%d,%d", Current->Title, Current->Director, Current->Description, Current->Genre, Current->runtime.hours, Current->runtime.minutes, Current->Year, Current->TimesPlayed, Current->Rating);

		Sleep(10000);

		Current = Current->next;
	}

	Current = Head;//To play everything before the match

	while (Current != Match) {
		system("cls");
		printf("Will play for 10 seconds");

		printf("\n\n%s,%s,%s,%s,%d:%d,%d,%d,%d", Current->Title, Current->Director, Current->Description, Current->Genre, Current->runtime.hours, Current->runtime.minutes, Current->Year, Current->TimesPlayed, Current->Rating);

		Sleep(10000);

		Current = Current->next;
	}

}

void Exit(FILE* outfile, node* Head) {

	outfile = freopen("moviePlayList.csv", "w+", outfile);
	fprintf(outfile, "Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating");
	node* Current = Head;
	while (Current != NULL) {
		fprintf(outfile, "\n%s,%s,%s,%s,%d:%d,%d,%d,%d", Current->Title, Current->Director, Current->Description, Current->Genre, Current->runtime.hours, Current->runtime.minutes, Current->Year, Current->TimesPlayed, Current->Rating);
		Current = Current->next;
	}
	fclose(outfile);
	exit(0);


}

void insert(node** Head) {

	node* Current = (node*)malloc(sizeof(node));
	node* Hold = *Head;
	
	printf("\nPlease enter title\n");
	scanf(" %[^\n]s", Current->Title);
		
	printf("\nPlease enter director\n");
	scanf(" %[^\n]s", Current->Director);
		

	printf("\nPlease enter Description\n");
	scanf(" %[^\n]s", Current->Description);
			
	printf("\nPlease enter new genre\n");
	scanf(" %[^\n]s", Current->Genre);

	printf("\nPlease enter new hours runtime\n");
	scanf("%d", &Current->runtime.hours);
		
	printf("\nPlease enter new minutes runtime\n");
	scanf("%d", &Current->runtime.minutes);

	printf("\nPlease enter new year\n");
	scanf("%d", &Current->Year);

	printf("\nPlease enter new Time Played\n");
	scanf("%d", &Current->TimesPlayed);

	printf("\nPlease enter new rating\n");
	scanf("%d", &Current->Rating);

	Current->next = *Head;
	Hold->prev = Current;
	*Head = Current;
	Current->prev = NULL;

}

void delete(node** Head) {

	char ourtitle[50];
	printf("\nPlease enter the name of the movie you want to change (caps sensetive)\n");
	scanf(" %[^\n]s", &ourtitle);
	node* Current = *Head;
	int newrating = 0;
	while (Current != NULL) {

		if (strcmp(ourtitle, Current->Title) == 0) {
			printf("Movie found and has been deleted!");

			if (Current->prev == NULL) {
				Current->next->prev = Current->prev;
				*Head = Current->next;
			}
			else {
				Current->prev->next = Current->next;
				Current->next->prev = Current->prev;
			}

		}

		Current = Current->next;

	}
}

void shuffle(node* Head) {
	//Getting length of LL
	int counter = 0;
	node* Current = Head;
	while (Current != NULL) {
		counter++;
		Current = Current->next;
	}

	//int arr[length];

	int* arr = (int*)malloc(counter * sizeof(int));
	
	//setting values

	for (int i = 0; i < counter; i++) {
		*(arr+i) = i + 1;
	}
	printf("%d", *(arr+counter-1));
	
	int random = 0;
	int temp = 0;
	
	for (int i = 0; i < counter; i++) {
		random = (rand() % (counter-1 - 0 + 1)) + 0;
		temp = *(arr + i);
		*(arr + i) = *(arr + random);
		*(arr + random) = temp;
	}

	Current = Head;
	int pos = 1;
	for (int i = 0; i < counter; i++) {
		//printf("\n%d", *(arr + pos));
		int val = *(arr + i);
		while (pos != val) {
			if (pos > val) {
				Current = Current->prev;
				pos--;
			}
			if (pos < val) {
				Current = Current->next;
				pos++;
			}
		}
		printf("\n Playing record number %d :", val);
		printf("\n%s,%s,%s,%s,%d:%d,%d,%d,%d", Current->Title, Current->Director, Current->Description, Current->Genre, Current->runtime.hours, Current->runtime.minutes, Current->Year, Current->TimesPlayed, Current->Rating);


	}


}


//EXTRA CREDIT

int sortq() {
	int choice;
	scanf("%d", &choice);
	return choice;

}



//void sorttitle(node** Head) {
//	node* Node1 = *Head;
//	node* Node2 = NULL;
//	char* next;
//	char* prev;
//	int i = 0;
//	int j = 0;
//	while (Node1 != NULL) {
//		Node2 = Node1->next;
//		while (Node2 != NULL) {
//			if (strcmp(Node1->Title, Node2->Title) > 0) {
//				next = Node1->next;
//				prev = Node1->prev;
//				Node1->next = Node2->next;
//				Node1->prev = Node2->prev;
//				Node2->next = next;
//				Node2->prev = prev;
//			}
//			Node2 = Node2->next;
//		}
//		Node1 = Node1->next;
//	}
//}


//TEST FUNCTIONS START HERE


void testinsert(node** Head) {

	node* Current = (node*)malloc(sizeof(node));
	node* Hold = *Head;

	printf("\nPlease enter title\n");
	strcpy(Current->Title, "Bohemian Rhapsody");
	

	printf("\nPlease enter director\n");
	strcpy(Current->Director, "Bryan Singer");


	printf("\nPlease enter Description\n");
	strcpy(Current->Description, "Freddie Mercury the lead singer of Queen defies stereotypes and convention to become one of history's most beloved entertainers.");

	printf("\nPlease enter new genre\n");
	strcpy(Current->Genre, "Drama");

	printf("\nPlease enter new hours runtime\n");
	Current->runtime.hours = 2;

	printf("\nPlease enter new minutes runtime\n");
	Current->runtime.minutes = 13;

	printf("\nPlease enter new year\n");
	Current->Year = 2018;

	printf("\nPlease enter new Time Played\n");
	Current->TimesPlayed = -1;

	printf("\nPlease enter new rating\n");
	Current->Rating = 6;

	Current->next = *Head;
	Hold->prev = Current;
	*Head = Current;
	Current->prev = NULL;

}

void testdelete(node** Head) {

	char ourtitle[50] = "Bohemian Rhapsody";
	printf("\nPlease enter the name of the movie you want to change (caps sensetive)\n");
	node* Current = *Head;
	node* trash = NULL;
	int newrating = 0;
	while (Current != NULL) {

		if (strcmp(ourtitle, Current->Title) == 0) {
			printf("Movie found and has been deleted!");
			
			if(Current->prev == NULL) {
				Current->next->prev = Current->prev;
				*Head = Current->next;				
			}
			else {
				Current->prev->next = Current->next;
				Current->next->prev = Current->prev;
			}

		}

		Current = Current->next;
		
	}


}

void testshuffle(node* Head) {
	//Getting length of LL
	int counter = 3;
	node* Current = Head;
	

	//int arr[length];

	int arr[3] = { 3,1,2 };

	//setting values

	Current = Head;
	int pos = 1;
	for (int i = 0; i < counter; i++) {
		//printf("\n%d", *(arr + pos));
		int val = arr[i];
		while (pos != val) {
			if (pos > val) {
				Current = Current->prev;
				pos--;
			}
			if (pos < val) {
				Current = Current->next;
				pos++;
			}
		}
		printf("\n Playing record number %d :", val);
		printf("\n%s,%s,%s,%s,%d:%d,%d,%d,%d", Current->Title, Current->Director, Current->Description, Current->Genre, Current->runtime.hours, Current->runtime.minutes, Current->Year, Current->TimesPlayed, Current->Rating);


	}


}

