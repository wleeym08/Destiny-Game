/**
 * File Name:    pQueue.h
 * Description:  Struct PQueue Declaration
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#ifndef PQUEUE_H
#define PQUEUE_H
#include "pNode.h"	

typedef struct PointQueue PQueue;

struct PointQueue {
	PNode* front;
	PNode* end;
};

PQueue** newPQueue(void);
void enqueue(P*, PQueue**);
void dequeue(PQueue**);
P* front(PQueue**);
int getPQueueSize(PQueue**);

#endif
