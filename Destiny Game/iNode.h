#ifndef INODE_H
#define INODE_H

typedef struct IntNode INode;

struct IntNode {
	int value;
	INode* next;
};

INode* newINode(int);

#endif