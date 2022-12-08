#ifndef PAIR_H_   /* Include guard */
#define PAIR_H_

//=================================
// included dependencies
#include "FrogObject.h"

class FrogObjectCol;

enum class PairType{IntVsInt, IntVsFloat, FloatVsInt, FloatVsFloat};

class Pair : public FrogObject
{
	PairType pairtype;
	int i_int;
	int j_int;
	int k_int;
	float i_float;
	float j_float;

	int assignedDepotIndex;

	FrogObjectCol * pairCol;

	FrogObjectCol * clusterCol;

	
public:
	Pair(PairType type);

	Pair(PairType type, int pairId);

	virtual ~Pair();

	PairType getType();

	void setType(PairType typeValue);

	int get_i_IntValue();
	void set_i_IntValue(int intValue);
	
	int get_j_IntValue();
	void set_j_IntValue(int intValue);
	
	int get_k_IntValue();
	void set_k_IntValue(int intValue);

	float get_i_FloatValue();
	float set_i_FloatValue(float floatValue);

	float get_j_FloatValue();
	float set_j_FloatValue(float floatValue);

	int getAssignedDepotIndex();

	void setAssignedDepotIndex(int depotIndex);

	FrogObjectCol * getPairCol();

	void setPairCol(FrogObjectCol * v_pairCol);

	void addPairInPairCol(Pair * v_pair);

	void createPairCol();

	FrogObjectCol * getClusterCol();

	void setClusterCol(FrogObjectCol * v_clusterCol);
	
	void upDateRemainingCapacity(Pair * customerPair);

	Pair * createCopy();

	void unreferenceAndDeleteClusterCol();

	void deleteClusterCol();

	// abstract methods
	void printFrogObj();

	bool isTheSame(FrogObject * fs);
};
#endif
