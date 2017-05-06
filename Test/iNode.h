/**
 * Program Name: iNode.h
 * Discussion:   Struct INode Declaration
 * Written By:   Zhiying Li
 * Date:         2017/04/02
 */

#ifndef INODE_H
#define INODE_H

typedef struct IntNode INode;

struct IntNode {
	int value;
	INode* next;
};

INode* newINode(int);

#endif