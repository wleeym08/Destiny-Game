#include <stdio.h>
#include <stdlib.h>
#include "pStack.h"

PStack** newPStack() {
	PStack** pStackPtr = (PStack**)malloc(sizeof(PStack*));
	*pStackPtr = NULL;

	return pStackPtr;
}

void push(P* p, PStack** pStackPtr) {
	PNode* pNode = newPNode(p);

	if (*pStackPtr != NULL) {
		pNode->next = (*pStackPtr)->peek;
		(*pStackPtr)->peek = pNode;
	}
	else {
		*pStackPtr = (PStack*)malloc(sizeof(PStack));
		(*pStackPtr)->peek = pNode;
	}
}

void pop(PStack** pStackPtr) {
	PNode* tmpNode = NULL;

	if (*pStackPtr != NULL) {
		if ((*pStackPtr)->peek->next != NULL) {
			tmpNode = (*pStackPtr)->peek;
			(*pStackPtr)->peek = tmpNode->next;
			free(tmpNode->ptr);
			tmpNode->ptr = NULL;
			free(tmpNode);
			tmpNode = NULL;
		}
		else {
			free((*pStackPtr)->peek->ptr);
			(*pStackPtr)->peek->ptr = NULL;
			free((*pStackPtr)->peek);
			(*pStackPtr)->peek = NULL;
			free(*pStackPtr);
			*pStackPtr = NULL;
		}
	}
}

P* peek(PStack** pStackPtr) {
	if (*pStackPtr != NULL)
		return (*pStackPtr)->peek->ptr;
	else
		return NULL;
}

int getPStackSize(PStack** pStackPtr) {
	PNode* tmpNode = NULL;
	int size = 0;

	if (*pStackPtr != NULL) {
		tmpNode = (*pStackPtr)->peek;
		size = 1;
		while (tmpNode->next != NULL) {
			tmpNode = tmpNode->next;
			size++;
		}
	}

	return size;
}

int isPStackEmpty(PStack** pStackPtr) {
	if (*pStackPtr)
		return 0;
	else
		return 1;
}

void clearPStack(PStack** pStackPtr) {
	while (*pStackPtr)
		pop(pStackPtr);
}