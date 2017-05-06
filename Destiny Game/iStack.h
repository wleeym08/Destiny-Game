/**
 * File Name:    iStack.h
 * Description:  Struct IStack Declaration
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#ifndef ISTACK_H
#define ISTACK_H
#include "iNode.h"

typedef struct IntStack IStack;

struct IntStack {
	INode* peek;
};

IStack** newIStack(void);
void push_i(int, IStack**);
int pop_i(IStack**);
int peek_i(IStack**);
int getIStackSize(IStack**);
int isIStackEmpty(IStack**);
void clearIStack(IStack**);

#endif