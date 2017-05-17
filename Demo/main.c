/**
 * File Name:    main.c
 * Description:  Desitiny Game Driver
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#include <stdio.h>
#include "boardInfo.h"

int main(int argc, char** argv) {
	int option;

	printf("+---------------------------+\n"
		"|    CIS 27 Final Project   |\n"
		"|       Destiny Game        |\n"
		"|         ver 0.0.1         |\n"
		"|    Author: Zhiying Li     |\n"
		"|    GitHub: winghearn      |\n"
		"+---------------------------+\n"
		"Welcome to Destiny Game!\n"
		"You have to WALK through a mine field to win.\n"
		"You have 3 lives.\n\n"
		"In-game Control:\n"
		"O -- Play BGM\n"
		"P -- Pause BGM\n"
		"Q -- Hint\n"
		"R -- Undo\n"
		"H -- Help\n"
		"ESC -- Close window"
	);

	// Select Mode 
	do {
		printf("\n\nSelect a mode:\n"
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
				printf("\nHave fun!!\n");
				break;
			default:
				printf("\nWrong option!!\n");
				while (getchar() != '\n');
				option = 0;
				break;
		}
	} while (option != 5);
}
