/**
 * File Name:    iNode.c
 * Description:  Struct INode Definition
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#include <stdio.h>
#include "iNode.h"

INode* newINode(int value) {
	INode* iNodePtr = (INode*)malloc(sizeof(INode));
	iNodePtr->value = value;
	iNodePtr->next = NULL;

	return iNodePtr;
}