//#include "stdafx.h"
#include "FrogObjNode.h"
#include "FrogObject.h"
#include <stdio.h>
#include <iostream>


using namespace std;

FrogObjNode::FrogObjNode(FrogObject * fs, FrogObjNode * fsnodeptr)
{
	frogItem = fs;
	next = fsnodeptr;
}

FrogObjNode::~FrogObjNode()
{
	//printf("Destroying FrogObjNode: STARTED \n");

	if(this->frogItem != nullptr)
	{
		delete this->frogItem;
		this->frogItem = nullptr;
	}	

	next = nullptr;

	//if(this->next != NULL)
	//{
	//	delete next;
	//}

	//printf("Destroying FrogObjNode: FINISHED \n");
}

void FrogObjNode::printNodeItems()
{
	if (this->frogItem != nullptr)
	{
		this->frogItem->printFrogObj();
	}

	FrogObjNode * tempNodePtr = next;
	while (tempNodePtr != nullptr)
	{
		tempNodePtr->frogItem->printFrogObj();
		tempNodePtr = tempNodePtr->next;
	};
}

FrogObject * FrogObjNode::getFrogItem()
{
	return this->frogItem;
}

void FrogObjNode::setFrogItem(FrogObject * item)
{
	this->frogItem = item;
}

FrogObjNode * FrogObjNode::getNextFrogObjNode()
{
	return this->next;
}

void FrogObjNode::setNextFrogObjNode(FrogObjNode * node)
{
	this->next = node;
}
