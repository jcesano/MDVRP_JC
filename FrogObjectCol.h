#ifndef FROGOBJECTCOL_H_   /* Include guard */
#define FROGOBJECTCOL_H_

//=================================
// included dependencies
#include "FrogObject.h"

// forward declared dependencies
class FrogObjNode;


class FrogObjectCol : public FrogObject
{
	FrogObjNode * head;

	int colSize;

public:

	FrogObjectCol();

	~FrogObjectCol();

	void destroy(FrogObjNode * itemNode);

	int getFrogObjectPositionById(int id);

	void addFrogObject(FrogObject * fs);

	void addLastFrogObject(FrogObject * fs);

	int addFrogObjectInPosition(FrogObject * fs, int position);

	void addFrogObjectOrdered(FrogObject * fs);

	void addFrogObjectDescOrdered(FrogObject * fs);

	void addFrogObjectDoubleOrdered(FrogObject * fs);
	
	void printFrogObjCol();

	int getSize();

	FrogObject * getFrogObject(int i);

	FrogObject * getFrogObjectById(int objid);

	FrogObject * getMaxValueFrogObject();

	void removeFrogObjects(FrogObjectCol * sourceSolutionCol);

	void removeFrogObject(FrogObject * fs);

	FrogObjectCol * removeRepetedItems();

	int areThereRepetedItems();

	int frogObjectExists(FrogObject * fs);

	int frogObjectExists(int id);

	void ConcatCol(FrogObjectCol * fs);

	void reverse();	

	FrogObject * getFirstUpperValueFrogObject(float searchedValue);

	FrogObject * getFirstHigherValueFrogObjectIndex(float searchedValue, int &frogObjectValue);

	FrogObject * getFirstLowerValueFrogObjectIndex(float searchedValue, int &frogObjectValue);

	void reorderFrogObject(FrogObject * fs);

	void removeAllLowerValueFrogObject(int value, FrogObjectCol * deletedFrogObjects);

	void addAllFrogObjects(FrogObjectCol * elementsToAdd);

	void unReferenceFrogObjectCol();

	// abstract methods
	void printFrogObj();

	bool isTheSame(FrogObject * fs);

};


#endif