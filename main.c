#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int choice;
	do{
		printMenuHome();
		printf("\tEnter the choice: ");
		scanf("%d", &choice);
		printf("\n");
		fflush(stdin);
		switch(choice){
			case 1:
				system("cls");
				inputMenu();
				break;
			case 0:
				printExit();
				break;
			default:
				system("cls");
				printf("\tError: Wrong syntax!\n");
		}
	}while(choice != 0);
	return 0;
}
