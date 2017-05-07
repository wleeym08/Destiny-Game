/**
 * File Name:    pNode.c
 * Description:  Struct PNode Definition
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#include <stdio.h>
#include <stdlib.h>
#include "pNode.h"

P* newPoint(int x, int y) {
	P* p = (P*)malloc(sizeof(P));

	p->x = x;
	p->y = y;

	return p;
}

P* newPointP(P* p) {
	P* myP = (P*)malloc(sizeof(P));

	myP->x = p->x;
	myP->y = p->y;

	return myP;
};

void displayPoint(P* p) {
	if (p != NULL)
		printf("(%d, %d)", p->x, p->y);
}

PNode* newPNode(P* p) {
	PNode* pNodePtr = (PNode*)malloc(sizeof(PNode));
	pNodePtr->ptr = newPointP(p);
	pNodePtr->next = NULL;

	return pNodePtr;
}