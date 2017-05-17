/**
 * File Name:    iStack.c
 * Description:  Struct IStack Definition
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#include <stdio.h>
#include <stdlib.h>
#include "iStack.h"

IStack** newIStack() {
	IStack** iStackPtr = (IStack**)malloc(sizeof(IStack*));
	*iStackPtr = NULL;

	return iStackPtr;
}

void push_i(int value, IStack** iStackPtr) {
	INode* iNodePtr = newINode(value);

	if (*iStackPtr != NULL) {
		iNodePtr->next = (*iStackPtr)->peek;
		(*iStackPtr)->peek = iNodePtr;
	}
	else {
		*iStackPtr = (IStack*)malloc(sizeof(IStack));
		(*iStackPtr)->peek = iNodePtr;
	}
}

int pop_i(IStack** iStackPtr) {
	INode* tmpNodePtr = NULL;
	int returnValue = -891230142;  // Some weird numbers...

	if (*iStackPtr != NULL) {
		if ((*iStackPtr)->peek->next != NULL) {
			tmpNodePtr = (*iStackPtr)->peek;
			(*iStackPtr)->peek = tmpNodePtr->next;
			returnValue = tmpNodePtr->value;
			free(tmpNodePtr);
			tmpNodePtr = NULL;
		}
		else {
			returnValue = (*iStackPtr)->peek->value;
			free((*iStackPtr)->peek);
			(*iStackPtr)->peek = NULL;
			free(*iStackPtr);
			*iStackPtr = NULL;
		}
	}

	return returnValue;
}

int peek_i(IStack** iStackPtr) {
	if (*iStackPtr != NULL)
		return (*iStackPtr)->peek->value;
	else
		return -891230142;  // Some weird numbers...
}

int getIStackSize(IStack** iStackPtr) {
	INode* tmpNodePtr = NULL;
	int size = 0;

	if (*iStackPtr != NULL) {
		tmpNodePtr = (*iStackPtr)->peek;
		size = 1;
		while (tmpNodePtr->next != NULL) {
			tmpNodePtr = tmpNodePtr->next;
			size++;
		}
	}

	return size;
}

int isIStackEmpty(IStack** iStackPtr) {
	if (*iStackPtr)
		return 0;
	else
		return 1;
}

void clearIStack(IStack** iStackPtr) {
	while (*iStackPtr)
		pop_i(iStackPtr);
}