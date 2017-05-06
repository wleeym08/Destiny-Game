/**
 * File Name:    pStack.h
 * Description:  Struct PStack Declaration
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#ifndef PSTACK_H
#define PSTACK_H
#include "pNode.h"

typedef struct PointStack PStack;

struct PointStack {
	PNode* peek;
};

PStack** newPStack(void);
void push(P*, PStack**);
void pop(PStack**);
P* peek(PStack**);
int getPStackSize(PStack**);
int isPStackEmpty(PStack**);
void clearPStack(PStack**);

#endif