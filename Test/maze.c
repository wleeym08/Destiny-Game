/**
 * Program Name: maze.c
 * Discussion:   Find Path
 * Written By:   Zhiying Li
 * Date:         2017/04/02
 */

#include <stdio.h>
#include "pQueue.h"
#include "pStack.h"
#include "boardInfo.h"

static int column = 10;
static int row = 10;
int startX = 1;
int startY = 0;
int endX = 8;
int endY = 9;
const char maze[10][10] = {
	".S....#...",				// This is a 10x10 board
	"........#.",               // # : cannot go through
	"#.....##..",				// . : empty space
	"#...###...",				// S : START
	"...#..#.##",				// G : GOAL
	"...#..#...",				// The START and GOAL are fixed positions
	"...#..###.",				// You can change the value of startX and startY
	"...#.##...",				// If you want to change the position of the blocks
	"...#.....#",				// Just change # to . to see what will happen
	"....#.##G."
};

/*
int main() {  // For the output map, -1 means it doesn't go through. Number other than -1 means possible moves are made to specific location
	P* tmpP = NULL;
	int presentX = -1;
	int presentY = -1;
	int** map;
	PNode* tmpNode = NULL;
	PStack** path = NULL;

	map = findWay(startX, startY, maze, NORMAL);
	displayMap(map, row, column);
	path = findShortestPath(map);
	printf("\n\nShortest path requires moves: %d\n\n", getPStackSize(path) - 1);

	tmpNode = (*path)->peek;
	printf("Path:\n");
	while (tmpNode != NULL) {
		displayPoint(tmpNode->ptr);
		printf("\n");
		tmpNode = tmpNode->next;
	}

	return 0;
}
*/

/*
int main2() {
	P* tmpP = newPoint(10, 100);
	P* anotherP = newPointP(tmpP);
	PNode* tmpNode = NULL;
	PQueue** pQueuePtr = newPQueue();
	enqueue(newPoint(1, 2), pQueuePtr);
	enqueue(newPoint(3, 4), pQueuePtr);
	enqueue(newPoint(5, 4), pQueuePtr);
	enqueue(newPoint(3, 12), pQueuePtr);
	enqueue(newPoint(9, 4), pQueuePtr);
	enqueue(newPoint(-1, 4), pQueuePtr);
	enqueue(tmpP, pQueuePtr);
	enqueue(anotherP, pQueuePtr);
	dequeue(pQueuePtr);
	dequeue(pQueuePtr);
	dequeue(pQueuePtr);
	dequeue(pQueuePtr);
	while ((*pQueuePtr) != NULL) {
		dequeue(pQueuePtr);
	}
	//dequeue(pQueuePtr);
	//dequeue(pQueuePtr);
	//dequeue(pQueuePtr);

	if (*pQueuePtr != NULL) {
		tmpNode = (*pQueuePtr)->front;
	}

	while (tmpNode != NULL) {
		displayPoint(tmpNode->ptr);
		tmpNode = tmpNode->next;
	}

	printf("%d", getPQueueSize(pQueuePtr));
	if (getPQueueSize(pQueuePtr))
		printf("Not empty");
	else
		printf("Empty");

	free(tmpP);
	tmpP = NULL;
	free(anotherP);
	anotherP = NULL;
	free(tmpNode);
	tmpNode = NULL;
	free(pQueuePtr);
	pQueuePtr = NULL;

	return 0;
}
*/