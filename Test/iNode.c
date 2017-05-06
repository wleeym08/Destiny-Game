/**
 * Program Name: iNode.c
 * Discussion:   Struct INode Definition
 * Written By:   Zhiying Li
 * Date:         2017/04/02
 */

#include <stdio.h>
#include "iNode.h"

INode* newINode(int value) {
	INode* iNodePtr = (INode*)malloc(sizeof(INode));
	iNodePtr->value = value;
	iNodePtr->next = NULL;

	return iNodePtr;
}