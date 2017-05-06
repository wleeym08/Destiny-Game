/**
 * Program Name: main.c
 * Discussion:   Destiny Game Driver
 * Written By:   Zhiying Li
 * Date:         2017/05/02
 */

#include <stdio.h>
#include "boardInfo.h"

int main(int argc, char** argv) {
	int option;

	// Select Mode 
	do {
		printf("Select a mode:\n"
			"1. Easy\n"
			"2. Normal\n"
			"3. Hard\n"
			"4. Lunatic\n"
			"5. Exit\n"
			"Enter your option (1 - 5): "
		);

		scanf("%d", &option);

		switch (option) {
			case 1:
				runGame(EASY);
				option = 0;
				break;
			case 2:
				runGame(NORMAL);
				option = 0;
				break;
			case 3:
				runGame(HARD);
				option = 0;
				break;
			case 4:
				runGame(LUNATIC);
				option = 0;
				break;
			case 5:
				printf("\n\nHave fun!!\n\n");
				break;
			default:
				printf("\n\nWrong option!!\n\n");
				while (getchar() != '\n');
				option = 0;
				break;
		}
	} while (option != 5);
}
