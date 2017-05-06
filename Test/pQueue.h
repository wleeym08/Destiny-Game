/**
 * Program Name: pQueue.h
 * Discussion:   Struct PQueue Declaration
 * Written By:   Zhiying Li
 * Date:         2017/04/02
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
