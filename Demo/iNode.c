#include <stdio.h>
#include <stdlib.h>
#include "iNode.h"

INode* newINode(int value) {
	INode* iNodePtr = (INode*)malloc(sizeof(INode));
	iNodePtr->value = value;
	iNodePtr->next = NULL;

	return iNodePtr;
}