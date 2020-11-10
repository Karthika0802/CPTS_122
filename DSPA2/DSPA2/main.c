/*******************************************************************************************
* Programmer: Karthik Ayyalasomayajula *
* Class: CptS 122, Fall, 2020; Lab Section 4 *
* Programming Assignment: PA2 *
* Date: 9/16/20 *
* Description: Video Manager *
*******************************************************************************************/

#include "Header.h"
#include "TestHeader.h"
int main()
{
	srand(time(0));
	FILE* infile = fopen("moviePlayList.csv", "r");
	//FILE* outfile = fopen("output.dat", "w");
	node* head = NULL;
	int x = 0;
	
	load(infile, &head);
	testinsert(&head);
	testdelete(&head);
	testshuffle(head);

	while (x != 11) {
		printf("\n(1) load\n(2) store\n(3) display\n(4) insert\n(5) delete\n(6) edit\n(7) shuffle\n(8) rate\n(9) play\n(11) exit\n");
		scanf(" %d", &x);
		
		if (x == 1) {
			load(infile, &head);
		}
		if (x == 2) {
			store(infile, head);
		}
		if (x == 3) {
			display(head);
		}
		if (x == 4) {
			insert(&head);
		}
		if (x == 5) {
			delete(&head);
		}
		if (x == 6) {
			edit(&head);
		}
		if (x == 7) {
			shuffle(head);
		}
		if (x == 8) {
			rate(&head);
		}
		if (x == 9) {
			play(head);
		}
		if (x == 10) {
			//sorttitle(&head);
		}
		if (x == 11) {
			Exit(infile, head);//dont really get the diff btwn this and store
		}
		
	}
	return 0;

}

