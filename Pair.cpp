//#include "stdafx.h"
#include "Pair.h"
#include "FrogObjectCol.h"
#include <iostream>

Pair::Pair(PairType type)
{
	this->pairtype = type;
	i_int = -1;
	j_int = -1;

	i_float = -1;
	j_float = -1;

	this->pairCol = nullptr;
	this->clusterCol = nullptr;
}

Pair::Pair(PairType type, int pairId):FrogObject(pairId)
{
	this->pairtype = type;
	i_int = -1;
	j_int = -1;

	i_float = -1;
	j_float = -1;

	this->pairCol = nullptr;
	this->clusterCol = nullptr;
}

Pair::~Pair()
{
	//printf("Destroying Pair \n");

	if(this->pairCol != nullptr)
	{
		delete this->pairCol;
		this->pairCol = nullptr;
	}

	if (this->clusterCol != nullptr)
	{
		delete this->clusterCol;
		this->clusterCol = nullptr;
	}
}

PairType Pair::getType()
{
	return this->pairtype;
}

void Pair::setType(PairType typeValue)
{
	this->pairtype = typeValue;
}

int Pair::get_i_IntValue()
{
	return this->i_int;
}

void Pair::set_i_IntValue(int intValue)
{
	this->i_int = intValue;
}

int Pair::get_j_IntValue()
{
	return this->j_int;
}

void Pair::set_j_IntValue(int intValue)
{
	this->j_int = intValue;
}

int Pair::get_k_IntValue()
{
	return this->k_int;
}

void Pair::set_k_IntValue(int intValue)
{
	this->k_int = intValue;
}

float Pair::get_i_FloatValue()
{
	return this->i_float;
}

float Pair::set_i_FloatValue(float floatValue)
{
	return this->i_float = floatValue;
}

float Pair::get_j_FloatValue()
{
	return this->j_float;
}

float Pair::set_j_FloatValue(float floatValue)
{
	return this->j_float = floatValue;
}

int Pair::getAssignedDepotIndex()
{
	return this->assignedDepotIndex;
}

void Pair::setAssignedDepotIndex(int depotIndex)
{
	this->assignedDepotIndex = depotIndex;
}

FrogObjectCol * Pair::getPairCol()
{
	return this->pairCol;
}

void Pair::setPairCol(FrogObjectCol * v_pairCol)
{
	this->pairCol = v_pairCol;
}

void Pair::addPairInPairCol(Pair * v_pair)
{
	this->pairCol->addFrogObject(v_pair);
}

void Pair::createPairCol()
{
	this->pairCol = new FrogObjectCol();
}

FrogObjectCol * Pair::getClusterCol()
{
	return this->clusterCol;
}

void Pair::setClusterCol(FrogObjectCol * v_clusterCol)
{
	this->clusterCol = v_clusterCol;
}

void Pair::upDateRemainingCapacity(Pair * customerPair)
{
	int customerDemand = customerPair->get_i_IntValue();
	int depotRemainingCap = this->get_j_IntValue();
	int newCapacity = depotRemainingCap - customerDemand;
	this->set_j_IntValue(newCapacity);
}

Pair * Pair::createCopy()
{
	Pair * copy = new Pair(this->getType(), this->getId());

	copy->set_i_IntValue(this->get_i_IntValue());
	copy->set_j_IntValue(this->get_j_IntValue());
	copy->set_i_FloatValue(this->get_i_FloatValue());
	copy->set_j_FloatValue(this->get_j_FloatValue());

	return copy;
}

void Pair::unreferenceAndDeleteClusterCol()
{
	this->clusterCol->unReferenceFrogObjectCol();
	delete this->clusterCol;
	this->clusterCol = nullptr;
}

void Pair::deleteClusterCol()
{	
	delete this->clusterCol;
	this->clusterCol = nullptr;
}

void Pair::printFrogObj()
{
	printf("Printing values of pair object: int_i = %.d, int_j = %.d, float_i = %.2f, float_j = %.2f, \n", this->i_int, this->j_int, this->i_float, this->j_float);
}

bool Pair::isTheSame(FrogObject * fs)
{
	
	return (this == fs);
	//Pair * fspair = (Pair *)fs;

	//if (fspair->getType() != this->getType())
	//{
	//	return false;
	//}

	//if (fspair->get_i_IntValue() != this->get_i_IntValue())
	//{
	//	return false;
	//}

	//if (fspair->get_j_IntValue() != this->get_j_IntValue())
	//{
	//	return false;
	//}

	//if (fspair->get_i_FloatValue() != this->get_i_FloatValue())
	//{
	//	return false;
	//}

	//if (fspair->get_j_FloatValue() != this->get_j_FloatValue())
	//{
	//	return false;
	//}

	//return true;
}


