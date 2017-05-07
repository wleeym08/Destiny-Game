/**
 * File Name:    path.c
 * Description:  Find Path
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#include <stdio.h>
#include <stdlib.h>
#include "boardInfo.h"
#include "pQueue.h"
#include "path.h"

void displayMap(int** gameMap, int row, int column) {
	printf("   |  ");
	for (int i = 0; i < column; i++)
		printf("%d   ", i);
	printf("\n---+");
	for (int i = 0; i < column; i++)
		printf("----");
	printf("\n");
	for (int i = 0; i < row; i++) {
		printf("%d  |  ", i);
		for (int j = 0; j < column; j++)
			printf("%d   ", *(*(gameMap + i) + j));
		printf("\n");
	}
}

int** findWay(int startX, int startY, char** mapAry, int mode) {  // Use a queue to do a breadth-first-search (maybe?)
	P* tmpP = NULL;
	int row;
	int column;
	int currentX;
	int currentY;
	int endX;
	int endY;
	int step = 0;
	PQueue** pQueuePtr = newPQueue();
	int** pathAry = NULL;

	switch (mode) {
	case EASY:
		row = ROW_NUMBER_EASY;
		column = COLUMN_NUMBER_EASY;
		break;
	case NORMAL:
		row = ROW_NUMBER_NORMAL;
		column = COLUMN_NUMBER_NORMAL;
		break;
	case HARD:
		row = ROW_NUMBER_HARD;
		column = COLUMN_NUMBER_HARD;
		break;
	case LUNATIC:
		row = ROW_NUMBER_LUNATIC;
		column = COLUMN_NUMBER_LUNATIC;
		break;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (*(*(mapAry + i) + j) == 'G') {
				endX = j;
				endY = i;
				j = column;
				i = row;
			}
		}
	}

	pathAry = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++) {
		*(pathAry + i) = (int*)malloc(column * sizeof(int));
		for (int j = 0; j < column; j++) {
			*(*(pathAry + i) + j) = -1;
		}
	}



	enqueue(newPoint(startX, startY), pQueuePtr);
	*(*(pathAry + startY) + startX) = 0;

	tmpP = newPoint(-1, -1);

	do {
		tmpP->x = (*pQueuePtr)->front->ptr->x;
		tmpP->y = (*pQueuePtr)->front->ptr->y;
		dequeue(pQueuePtr);

		for (int i = 0; i < 4; i++) {
			currentX = tmpP->x + directionX[i];
			currentY = tmpP->y + directionY[i];

			if (currentX >= 0 && currentX < column && currentY >= 0 && currentY < row &&
				*(*(mapAry + currentY) + currentX) != '#' &&
				*(*(pathAry + currentY) + currentX) == -1) {
				enqueue(newPoint(currentX, currentY), pQueuePtr);
				*(*(pathAry + currentY) + currentX) = *(*(pathAry + tmpP->y) + tmpP->x) + 1;
			}
		}
		step++;
	} while (getPQueueSize(pQueuePtr) && !(tmpP->x == endX && tmpP->y == endY));

	while ((*pQueuePtr) != NULL)
		dequeue(pQueuePtr);

	free(pQueuePtr);
	pQueuePtr = NULL;

	return pathAry;
}

PStack** findShortestPath(int startX, int startY, int endX, int endY, int** pathAry, int mode) {  // Call findNext()
	int row;
	int column;
	int move;
	int** solutionMap = NULL;
	PStack** pathStack = NULL;

	switch (mode) {
		case EASY:
			row = ROW_NUMBER_EASY;
			column = COLUMN_NUMBER_EASY;
			break;
		case NORMAL:
			row = ROW_NUMBER_NORMAL;
			column = COLUMN_NUMBER_NORMAL;
			break;
		case HARD:
			row = ROW_NUMBER_HARD;
			column = COLUMN_NUMBER_HARD;
			break;
		case LUNATIC:
			row = ROW_NUMBER_LUNATIC;
			column = COLUMN_NUMBER_LUNATIC;
			break;
	}

	pathStack = newPStack();
	move = *(*(pathAry + endY) + endX);

	solutionMap = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++) {
		*(solutionMap + i) = (int*)malloc(column * sizeof(int));
		for (int j = 0; j < column; j++)
			*(*(solutionMap + i) + j) = 0;
	}

	*(*(solutionMap + startY) + startX) = 1;
	push(newPoint(startX, startY), pathStack);
	if (move != -1)
		findNext(endX, endY, row, column, pathStack, pathAry, solutionMap);

	return pathStack;
}

void findNext(int endX, int endY, int row, int column, 
	PStack** pStackPtr, int** pathAry, int** solutionMap) {  // Use a stack to do a depth-first-search (maybe?)
	int x = (*pStackPtr)->peek->ptr->x;
	int y = (*pStackPtr)->peek->ptr->y;
	int presentX;
	int presentY;
	int flag = 1;

	if (!(x == endX && y == endY)) {
		for (int i = 0; i < 4; i++) {
			presentX = x + directionX[i];
			presentY = y + directionY[i];

			if (presentX >= 0 && presentX < column && presentY >= 0 && presentY < row && *(*(pathAry + presentY) + presentX) == *(*(pathAry + y) + x) + 1 &&
				*(*(solutionMap + presentY) + presentX) != 1) {

				flag = 0;
				push(newPoint(presentX, presentY), pStackPtr);
				*(*(solutionMap + presentY) + presentX) = 1;
				findNext(endX, endY, row, column, pStackPtr, pathAry, solutionMap);
			}
		}

		if (flag) {
			pop(pStackPtr);
			findNext(endX, endY, row, column, pStackPtr, pathAry, solutionMap);
		}
	}
}