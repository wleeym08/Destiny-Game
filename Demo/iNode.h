/**
 * File Name:    iNode.h
 * Description:  Struct INode Declaration
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
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