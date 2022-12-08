//#include "stdafx.h"
#include "FrogObjectCol.h"
#include "FrogObject.h"
#include "FrogObjNode.h"
#include <iostream>
#include <stdio.h>

using namespace std;

FrogObjectCol::FrogObjectCol()
{
	head = nullptr;

	this->colSize = 0;
}

FrogObjectCol::~FrogObjectCol()
{
	
	//printf("Destroying FrogObjectCol:STARTED \n");

	//destroy(this->head);
	FrogObjNode * itemNode = this->head, *old;

	this->head = nullptr;

	while (itemNode != nullptr)
	{
		old = itemNode;
		itemNode = itemNode->getNextFrogObjNode();
		delete old;
		old = nullptr;
	}

	
	//---------------------------
	//FrogObjNode * temp;

	//temp = head;

	//while(this->head != nullptr)
	//{
	//	temp = temp->getNextFrogObjNode();
	//	delete head;
	//	head = temp;
	//}
	//---------------------------

	//printf("Destroying FrogObjectCol:FINISHED \n");
}

void FrogObjectCol::destroy(FrogObjNode * itemNode)
{
	//printf("Destroying FrogObjectCol: STARTED \n");

	while(itemNode != nullptr)
	{
		FrogObjNode * old = itemNode;
		itemNode = itemNode->getNextFrogObjNode();
		delete old;
	}
	
	//if(itemNode != nullptr)
	//{
	//	delete itemNode;
	//}

	//printf("Destroying FrogObjectCol: FINISHED \n");
}

void FrogObjectCol::addFrogObject(FrogObject * fs)
{
	FrogObjNode * ptr;

	ptr = new FrogObjNode(fs, head);

	head = ptr;

	this->colSize++;
}

int FrogObjectCol::getFrogObjectPositionById(int id)
{
	int result = -1, i;

	bool found = false;
	
	FrogObjNode * nodePtr;
	FrogObject * solPtr;

	i = 0;

	nodePtr = this->head;

	while (found == false && i < this->getSize() && nodePtr != nullptr)
	{
		solPtr = nodePtr->getFrogItem();

		found = (solPtr->getId() == id);

		if (found == false) 
		{
			nodePtr = nodePtr->getNextFrogObjNode();
			i++;
		}
		else
		{
			result = i;
		}			
	}

	return result;
}

void FrogObjectCol::addLastFrogObject(FrogObject * fs) 
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = nullptr;
	// *nodePtrTemp; unused variable
	//bool stopLoop = false; unused variable

	if (fs != nullptr)
	{
		if (head == nullptr)
		{
			head = new FrogObjNode(fs, nullptr);
			this->colSize++;
		}
		else
		{			
			do
			{
				nodePtrPrev = nodePtr;
				nodePtr = nodePtr->getNextFrogObjNode();
			} while (nodePtr != nullptr);

			//if I am in the end of the list
			if (nodePtr == nullptr)
			{
				nodePtr = new FrogObjNode(fs, nullptr);
				nodePtrPrev->setNextFrogObjNode(nodePtr);
				this->colSize++;
			}
		}//end else (head == nullptr)
	}// end if(fs != nullptr)
}

int FrogObjectCol::addFrogObjectInPosition(FrogObject * fs, int position)
{
	// assign the first element
	FrogObjNode * prevNode = nullptr;
	FrogObjNode * currentNode = head;
	// FrogObject * result = nullptr; unused variable

	if ((this->head != nullptr) && (position <= this->getSize()) && (position >= 0))
	{
		// if i == 0 then for is not executed, otherwise we start from i = 1
		// cause result is pointing to the first Node already (first node is in position = 0)
		for (int j = 0; j < position; j++)
		{
			prevNode = currentNode;
			currentNode = currentNode->getNextFrogObjNode();
		}

		if(prevNode == nullptr) // This means that position = 0
		{
			this->addFrogObject(fs);
		}
		else
		{
			FrogObjNode * ptr;

			ptr = new FrogObjNode(fs, currentNode);

			prevNode->setNextFrogObjNode(ptr);

			this->colSize++;
		}

		return 1;
	}
	else
	{
		return 0;
	}
}

void FrogObjectCol::addFrogObjectOrdered(FrogObject * fs)
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = nullptr, *nodePtrTemp;
	bool stopLoop = false;

	if (fs != nullptr)
	{
		if (head == nullptr)
		{
			head = new FrogObjNode(fs, nullptr);
			this->colSize++;
		}
		else
		{
			stopLoop = false;
			
			do
			{
				//if the new value is lower than current item => add new value before
				if (fs->getValue() <= nodePtr->getFrogItem()->getValue())
				{
					nodePtrTemp = new FrogObjNode(fs, nodePtr);

					// if nodePtrPrev == nullptr then i am in the begining of the list
					if(nodePtrPrev != nullptr)
					{
						nodePtrPrev->setNextFrogObjNode(nodePtrTemp);
					}
					else
					{
						head = nodePtrTemp;
					}
					
					this->colSize++;
					stopLoop = true;
				}
				else //keep looking
				{
					nodePtrPrev = nodePtr;
					nodePtr = nodePtr->getNextFrogObjNode();
				}
			} while (!stopLoop && nodePtr != nullptr);

			//if I am in the end of the list
			if (nodePtr == nullptr)
			{
				nodePtr = new FrogObjNode(fs, nullptr);
				nodePtrPrev->setNextFrogObjNode(nodePtr);
				this->colSize++;
			}
		}//end else (head == nullptr)
	}// end if(fs != nullptr)
}

void FrogObjectCol::addFrogObjectDoubleOrdered(FrogObject * fs)
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = nullptr, *nodePtrTemp;
	bool stopLoop = false;

	if (fs != nullptr)
	{
		if (head == nullptr)
		{
			head = new FrogObjNode(fs, nullptr);
			this->colSize++;
		}
		else
		{
			stopLoop = false;

			do
			{
				//if the new value is lower than current item => add new value before
				if (fs->getValue() < nodePtr->getFrogItem()->getValue())
				{
					nodePtrTemp = new FrogObjNode(fs, nodePtr);

					// if nodePtrPrev == nullptr then i am in the begining of the list
					if (nodePtrPrev != nullptr)
					{
						nodePtrPrev->setNextFrogObjNode(nodePtrTemp);
					}
					else
					{
						head = nodePtrTemp;
					}

					this->colSize++;
					stopLoop = true;
				}
				else 
				{
					// If it is equal then check second value
					if(fs->getValue() == nodePtr->getFrogItem()->getValue())
					{	// order by Value2
						if (fs->getValue2() <= nodePtr->getFrogItem()->getValue2())
						{
							nodePtrTemp = new FrogObjNode(fs, nodePtr);

							// if nodePtrPrev == nullptr then i am in the begining of the list
							if (nodePtrPrev != nullptr)
							{
								nodePtrPrev->setNextFrogObjNode(nodePtrTemp);
							}
							else
							{
								head = nodePtrTemp;
							}

							this->colSize++;
							stopLoop = true;
						}
						else // keep looking
						{
							nodePtrPrev = nodePtr;
							nodePtr = nodePtr->getNextFrogObjNode();
						}
					}
					else //keep looking
					{
						nodePtrPrev = nodePtr;
						nodePtr = nodePtr->getNextFrogObjNode();
					}
				}
			} while (!stopLoop && nodePtr != nullptr);

			//if I am in the end of the list
			if (nodePtr == nullptr)
			{
				nodePtr = new FrogObjNode(fs, nullptr);
				nodePtrPrev->setNextFrogObjNode(nodePtr);
				this->colSize++;
			}
		}//end else (head == nullptr)
	}// end if(fs != nullptr)
}

void FrogObjectCol::addFrogObjectDescOrdered(FrogObject * fs)
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = nullptr, *nodePtrTemp;
	bool stopLoop = false;

	if (fs != nullptr)
	{
		if (head == nullptr)
		{
			head = new FrogObjNode(fs, nullptr);
			this->colSize++;
		}
		else
		{
			stopLoop = false;

			do
			{
				//if the new value is lower than current item => add new value before
				if (fs->getValue() >= nodePtr->getFrogItem()->getValue())
				{
					nodePtrTemp = new FrogObjNode(fs, nodePtr);

					// if nodePtrPrev == nullptr then i am in the begining of the list
					if (nodePtrPrev != nullptr)
					{
						nodePtrPrev->setNextFrogObjNode(nodePtrTemp);
					}
					else
					{
						head = nodePtrTemp;
					}

					this->colSize++;
					stopLoop = true;
				}
				else //keep looking
				{
					nodePtrPrev = nodePtr;
					nodePtr = nodePtr->getNextFrogObjNode();
				}
			} while (!stopLoop && nodePtr != nullptr);

			//if I am in the end of the list
			if (nodePtr == nullptr)
			{
				nodePtr = new FrogObjNode(fs, nullptr);
				nodePtrPrev->setNextFrogObjNode(nodePtr);
				this->colSize++;
			}
		}//end else (head == nullptr)
	}// end if(fs != nullptr)
}

void FrogObjectCol::printFrogObjCol()
{	
	cout << "Printing frog objects " << endl;

	if (head != nullptr)
	{
		head->printNodeItems();
	}
}

int FrogObjectCol::getSize()
{
	return this->colSize;
}

FrogObject * FrogObjectCol::getFrogObject(int position)
{
	// assign the first element
	FrogObjNode * currentNode = head;
	FrogObject * result = nullptr;

	if ((this->head != nullptr) && (position < this->getSize()) && (position >= 0))
	{
		// if i == 0 then for is not executed, otherwise we start from i = 1
		// cause result is pointing to the first Node already (first node is in position = 0)
		for (int j = 0; j < position; j++)
		{			
			currentNode = currentNode->getNextFrogObjNode();
		}

		result = currentNode->getFrogItem();

		return result;
	}
	else
	{
		return nullptr;
	}
}

void FrogObjectCol::removeFrogObjects(FrogObjectCol * sourceSolutionCol)
{
	if (sourceSolutionCol != nullptr)
	{
		for (int i = 1; i <= sourceSolutionCol->colSize; i++)
		{
			FrogObject * fs = sourceSolutionCol->getFrogObject(i);
			if (this->frogObjectExists(fs) != -1)
			{
				this->removeFrogObject(fs);
			}
		}
	}
}

void FrogObjectCol::removeFrogObject(FrogObject * fs)
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = nullptr, *nodePtrTemp;

	if (fs != nullptr)
	{
		while (nodePtr != nullptr)
		{
			if (nodePtr->getFrogItem() != nullptr)
			{
				if (nodePtr->getFrogItem()->isTheSame(fs))
				{

					// if the element is located at the begining of the list
					if (head == nodePtr)
					{
						nodePtrTemp = head;						
						head = head->getNextFrogObjNode();
						nodePtr = head;

						nodePtrTemp->setFrogItem(nullptr);
						delete nodePtrTemp;
						nodePtrTemp = nullptr;
						
						this->colSize--;
					}
					else 
					{
						nodePtrTemp = nodePtr;
						nodePtrPrev->setNextFrogObjNode(nodePtr->getNextFrogObjNode());
						nodePtr = nodePtrTemp->getNextFrogObjNode();						

						nodePtrTemp->setFrogItem(nullptr);
						delete nodePtrTemp;
						nodePtrTemp = nullptr;

						this->colSize--;
					}
				}
				else 
				{
					nodePtrPrev = nodePtr;
					nodePtr = nodePtr->getNextFrogObjNode();
				}
			} // end if (nodePtr->getFrogItem() != nullptr)
		} // end while (nodePtr != nullptr)

		nodePtrPrev = nullptr;

	} // end if(fs != nullptr)
}

void FrogObjectCol::reorderFrogObject(FrogObject * fs)
{
	this->removeFrogObject(fs);
	this->addFrogObjectOrdered(fs);
}

void FrogObjectCol::removeAllLowerValueFrogObject(int value, FrogObjectCol * deletedFrogObjects)
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = nullptr, *nodePtrTemp;

	while (nodePtr != nullptr)
	{
		if (nodePtr->getFrogItem() != nullptr)
		{
			//float currValue = nodePtr->getFrogItem()->getValue(); unused variable

			if (nodePtr->getFrogItem()->getValue() < value)
			{

				// if the element is located at the begining of the list
				if (head == nodePtr)
				{
					nodePtrTemp = head;
					deletedFrogObjects->addLastFrogObject(nodePtrTemp->getFrogItem());

					head = head->getNextFrogObjNode();
					nodePtr = head;

					nodePtrTemp->setFrogItem(nullptr);
					delete nodePtrTemp;
					nodePtrTemp = nullptr;

					this->colSize--;
				}
				else
				{
					nodePtrTemp = nodePtr;
					deletedFrogObjects->addLastFrogObject(nodePtrTemp->getFrogItem());
					nodePtrPrev->setNextFrogObjNode(nodePtr->getNextFrogObjNode());
					nodePtr = nodePtrTemp->getNextFrogObjNode();

					nodePtrTemp->setFrogItem(nullptr);
					delete nodePtrTemp;
					nodePtrTemp = nullptr;

					this->colSize--;
				}
			}
			else {
				nodePtrPrev = nodePtr;
				nodePtr = nodePtr->getNextFrogObjNode();
			}
		} // end if (nodePtr->getFrogItem() != nullptr)
	} // end while (nodePtr != nullptr)

	nodePtrPrev = nullptr;
}

void FrogObjectCol ::addAllFrogObjects(FrogObjectCol * elementsToAdd)
{
	int size = elementsToAdd->getSize();

	for(int i = 0; i < size; i++)
	{
		this->addFrogObject(elementsToAdd->getFrogObject(i));
	}
}

void FrogObjectCol::unReferenceFrogObjectCol()
{
	//printf("Unreferencing FrogObjectCol: STARTED \n");

	FrogObjNode * itemNode = this->head;

	while (itemNode != nullptr)
	{
		FrogObjNode * old = itemNode;
		old->setFrogItem(nullptr);
		itemNode = itemNode->getNextFrogObjNode();		
	}

	//printf("Unreferencing FrogObjectCol: FINISHED \n");
}

void FrogObjectCol::printFrogObj()
{
}

bool FrogObjectCol::isTheSame(FrogObject * fs)
{
	return false;
}

FrogObjectCol * FrogObjectCol::removeRepetedItems()
{
	return nullptr;
}

int FrogObjectCol::areThereRepetedItems()
{
	return 0;
}

int FrogObjectCol::frogObjectExists(FrogObject * fs)
{
	bool found = false;
	int i;
	
	FrogObjNode * nodePtr;
	FrogObject * solPtr;

	i = 0;

	nodePtr = this->head;

	while (found == false && i < this->getSize() && nodePtr != nullptr)
	{
		solPtr = nodePtr->getFrogItem();

		found = (solPtr == fs);

		if(found == true)
		{
			return i;
		}
		else
		{
			nodePtr = nodePtr->getNextFrogObjNode();
			i = i + 1;
		}
	}
	
	return -1;
}

int FrogObjectCol::frogObjectExists(int objid)
{
	bool found = false;
	int i;

	FrogObjNode * nodePtr;
	FrogObject * solPtr;

	i = 0;

	nodePtr = this->head;

	while (found == false && i < this->getSize() && nodePtr != nullptr)
	{
		solPtr = nodePtr->getFrogItem();

		found = solPtr->isTheSame(objid);

		if(found == true)
		{
			return i;
		}
		else
		{
			nodePtr = nodePtr->getNextFrogObjNode();
			i = i + 1;
		}
	}
	

	return -1;
}

FrogObject * FrogObjectCol::getFrogObjectById(int objid)
{
	bool found = false;
	int i;
	FrogObject * result = nullptr;

	FrogObjNode * nodePtr;
	FrogObject * solPtr;

	i = 1;

	nodePtr = this->head;

	while (found == false && i <= this->getSize() && nodePtr != nullptr)
	{
		solPtr = nodePtr->getFrogItem();

		found = solPtr->isTheSame(objid);

		if(found == true)
		{
			result = solPtr;
		}
		else
		{
			nodePtr = nodePtr->getNextFrogObjNode();
			i = i + 1;					
		}
	}

	return result;
}

FrogObject * FrogObjectCol::getMaxValueFrogObject()
{
	FrogObject * result = nullptr, * currentFrogObject = nullptr;

	result = this->getFrogObject(0);
	
	for (int i = 1; i < this->getSize(); i++)
	{
		currentFrogObject = this->getFrogObject(i);
		if (currentFrogObject->getValue() > result->getValue())
		{
			result = currentFrogObject;
		}
	}

	return result;
}

FrogObject * FrogObjectCol::getFirstUpperValueFrogObject(float searchedValue)
{
	FrogObject * result = nullptr, *currentFrogObject = nullptr;

	for (int i = 0; i < this->getSize(); i++)
	{
		currentFrogObject = this->getFrogObject(i);
		if (currentFrogObject->getValue() >= searchedValue)
		{
			result = currentFrogObject;
			return result;
		}
	}

	return result;
}

FrogObject * FrogObjectCol::getFirstHigherValueFrogObjectIndex(float searchedValue, int & frogObjectIndex)
{	
	FrogObject * currentFrogObject = nullptr, * result = nullptr;

	for (int i = 0; i < this->getSize(); i++)
	{
		currentFrogObject = this->getFrogObject(i);
		if (currentFrogObject->getValue() >= searchedValue)
		{
			result = currentFrogObject;
			frogObjectIndex = i;  
			return result;
		}
	}

	frogObjectIndex = -1;
	return result;
}

FrogObject * FrogObjectCol::getFirstLowerValueFrogObjectIndex(float searchedValue, int & frogObjectIndex)
{
	FrogObject * currentFrogObject = nullptr, *result = nullptr;

	for (int i = 0; i < this->getSize(); i++)
	{
		currentFrogObject = this->getFrogObject(i);
		if (currentFrogObject->getValue() <= searchedValue)
		{
			result = currentFrogObject;
			frogObjectIndex = i;
			return result;
		}
	}

	frogObjectIndex = -1;
	return result;
}

void FrogObjectCol::ConcatCol(FrogObjectCol * fs)
{
}

void FrogObjectCol::reverse()
{
	for (int i = 0; i < this->getSize(); i++)
	{
		FrogObject * object = this->getFrogObject(i);
		this->removeFrogObject(object);
		this->addLastFrogObject(object);
	}
}







