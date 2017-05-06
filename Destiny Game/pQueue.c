/**
 * File Name:    pQueue.c
 * Description:  Struct PQueue Definition
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#include <stdio.h>
#include "pQueue.h"

PQueue** newPQueue() {
	PQueue** pQueuePtr = (PQueue**)malloc(sizeof(PQueue*));
	*pQueuePtr = NULL;

	return pQueuePtr;
}

void enqueue(P* p, PQueue** pQueuePtr) {
	PNode* pNode = newPNode(p);

	if (*pQueuePtr != NULL) {
		(*pQueuePtr)->end->next = pNode;
		(*pQueuePtr)->end = pNode;
	}
	else {
		*pQueuePtr = (PQueue*)malloc(sizeof(PQueue));
		(*pQueuePtr)->end = pNode;
		(*pQueuePtr)->front = pNode;
	}

}

void dequeue(PQueue** pQueuePtr) {
	PNode* tmpNode = NULL;

	if (*pQueuePtr != NULL) {
		if ((*pQueuePtr)->front != (*pQueuePtr)->end) {
			tmpNode = (*pQueuePtr)->front;
			(*pQueuePtr)->front = tmpNode->next;
			free(tmpNode->ptr);
			tmpNode->ptr = NULL;
			free(tmpNode);
			tmpNode = NULL;
		}
		else {
			free((*pQueuePtr)->front->ptr);
			(*pQueuePtr)->front->ptr = NULL;
			free((*pQueuePtr)->front);
			(*pQueuePtr)->front = NULL;
			free(*pQueuePtr);
			*pQueuePtr = NULL;

		}
	}

}

P* front(PQueue** pQueuePtr) {
	if (*pQueuePtr != NULL)
		return (*pQueuePtr)->front->ptr;
	else 
		return NULL;
}

int getPQueueSize(PQueue** pQueuePtr) {
	PNode* tmpNode = NULL;
	int size = 0;

	if (*pQueuePtr != NULL) {
		tmpNode = (*pQueuePtr)->front;
		size = 1;
		while (tmpNode->next != NULL) {
			tmpNode = tmpNode->next;
			size++;
		}
	}
	
	return size;
}