#ifndef PNODE_H
#define PNODE_H

typedef struct Point P;
typedef struct PointNode PNode;

struct Point {
	int x;
	int y;
};

struct PointNode {
	P* ptr;
	PNode* next;
};

P* newPoint(int, int);
P* newPointP(P*);
void displayPoint(P*);
PNode* newPNode(P*);

#endif