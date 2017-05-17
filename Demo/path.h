/**
 * File Name:    path.h
 * Description:  Find Path
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#ifndef PATH_H
#define PATH_H
#include "pStack.h"

void displayMap(int**, int, int);
int** findWay(int, int, char**, int);
PStack** findShortestPath(int startX, int startY, int endX, int endY, int** pathAry, int mode);
void findNext(int endX, int endY, int row, int column,
	PStack** pStackPtr, int** pathAry, int** solutionMap);

#endif