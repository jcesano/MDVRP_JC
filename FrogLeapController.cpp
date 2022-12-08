//#include "stdafx.h"
#include "FrogLeapController.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include <time.h>
#include <string>
#include "FrogObject.h"
#include "FrogObjectCol.h"
//#include "DecodedFrogLeapSolution.h"
#include "TspLibEuc2D.h"
//#include "TestCaseObj.h"
#include "Pair.h"
#include "DistanceTable.h"
//#include "FloatDistanceTable.h"
#include "Graph.h"
//#include "FrogLeapSolution.h"
#include "Pair.h"
#include "IndexList.h"
//#include "Vehicle.h"
//#include "Cluster.h"
//#include "FeasibleSolution.h"
#include <limits>
#include <iostream>
#include <string>
#include <functional>
#include <random>
#include <utility>
#include <chrono>
#include <vector>
#include <numeric>
#include <chrono>

//using std::string;
//using std::cout;
//using std::endl;
//using std::cin;
//using std::string;
//using std::random_device;
//using std::default_random_engine;

using namespace std;

/// @brief 
// const int LINE_MAX = 256

FrogLeapController::FrogLeapController()
{	
	line_max_value = 256;

	this->distanceTypeMeasure = DistanceTypeCtrl::knapsack;
	
	this->tempCustomerCol = nullptr;

	this->failAttempts = 0;

	this->successAttempts = 0;

	this->timeSeedUsed = (unsigned)time(nullptr);
	this->timeSeedUsed = 1537280770;

	srand(this->timeSeedUsed);

	this->minCostValue = std::numeric_limits<float>::max();;

	this->totalImprovements = 0;
	this->localSearchImprovements = 0;
	this->globalImprovements = 0;

	this->tspLibEud2DPtr = nullptr;
	this->testCaseObjPtr = nullptr;

	//this->distTablePtr = nullptr;
	//this->floatDistTablePtr = nullptr;

	//this->graphPtr = nullptr;

	//this->customerList = new FrogObjectCol();
	this->depotList = new FrogObjectCol();
	//this->vehiclePairList = new FrogObjectCol();
	//this->ptrBestSolution = nullptr;

	this->globalVehicleId = 0;	

	//this->ptrBestDepotFeasibleSolution = nullptr;

//	currentDepotFeasibleSolution = nullptr;
}

FrogLeapController::~FrogLeapController()
{

	// delete this->vehiclePairList;
	// delete this->depotList;
	// delete this->customerList;
	// delete this->tempCustomerCol;

	//this->unreferenceArray(this->customerArray, this->getNumberOfCustomers());
	//delete[] this->customerArray;

	//this->unreferenceArray(this->depotArray, this->getNumberOfDepots());
	//delete[] this->depotArray;

	// if(ptrBestDepotFeasibleSolution == currentDepotFeasibleSolution)
	// {
	// 	if(ptrBestDepotFeasibleSolution != nullptr)
	// 	{
	// 		currentDepotFeasibleSolution = nullptr;
	// 		delete ptrBestDepotFeasibleSolution;
	// 	}
	// }
	// else 
	// {
	// 	if(currentDepotFeasibleSolution != nullptr)
	// 	{
	// 		delete currentDepotFeasibleSolution;
	// 	}		
	// }
}

// int FrogLeapController::getFailAttempts()
// {
// 	return this->failAttempts;
// }

// void FrogLeapController::incFailAttempts()
// {
// 	this->failAttempts++;
// }

int FrogLeapController::getTotalImprovements()
{
	//return this->localSearchImprovements + this->globalImprovements;
	return this->totalImprovements;
}

void FrogLeapController::incTotalImprovements()
{
	this->totalImprovements++;
}

// int FrogLeapController::getLocalSearchImprovements()
// {
// 	return this->localSearchImprovements;
// }

// void FrogLeapController::incLocalSearchImprovements()
// {
// 	this->localSearchImprovements;
// }

// int FrogLeapController::getGlobalSearchImprovements()
// {
// 	return this->globalImprovements;
// }

// void FrogLeapController::incGlobalSearchImprovements()
// {
// 	this->globalImprovements++;
// }

// int FrogLeapController::getLocalGeneratedSolutions()
// {
// 	return this->localGeneratedSolutions;
// }

// void FrogLeapController::incLocalGeneratedSolutions()
// {
// 	this->localGeneratedSolutions++;
// }

// void FrogLeapController::setLocaImprovement()
// {	
// 	this->incLocalSearchImprovements();	
// 	this->solutionMode = SolutionMode::LocalSearch;
// }

// void FrogLeapController::setGlobalImprovement()
// {
// 	this->incGlobalSearchImprovements();
// 	this->solutionMode = SolutionMode::Global;
// }

// long int FrogLeapController::getNumberOfIterations()
// {
// 	return 150000;
// }

// float FrogLeapController::getMinCostValue()
// {
// 	return this->minCostValue;
// }

// void FrogLeapController::setMinCostValue(float cost)
// {
// 	this->minCostValue = cost;
// }

// float FrogLeapController::getCurrentCostValue()
// {
// 	return this->currentCostValue;
// }

// void FrogLeapController::setCurrentCostValue(float cost)
// {
// 	this->currentCostValue = cost;
// }

// long long int FrogLeapController::getExecTime()
// {
// 	return this->execTime;
// }

// long long int FrogLeapController::getIterations()
// {
// 	return this->iterations;
// }

// void FrogLeapController::incIterations()
// {
// 	this->iterations++;
// }

// void FrogLeapController::resetIterations()
// {
// 	this->iterations = 0;
// }

// void FrogLeapController::setExecTime(long long int v_execTime)
// {
// 	this->execTime = v_execTime;
// }

// void FrogLeapController::setBestDecodedFrogLeapSolution(DecodedFrogLeapSolution * ptrSolution)
// {	
// 	DecodedFrogLeapSolution * oldSolution = this->ptrBestSolution;
// 	this->ptrBestSolution = ptrSolution;
// 	delete oldSolution;
// 	oldSolution = nullptr;
// }

// void FrogLeapController::setUpLocalSolution(DecodedFrogLeapSolution * dfls_1, float eval)
// {
// 	this->setLocaImprovement();

// 	this->setBestDecodedFrogLeapSolution(dfls_1);
// 	this->setMinCostValue(eval);

// 	this->take_Execution_Time();
// 	this->set_BestSolution_ExecutionTime(this->get_Execution_Time());	

// 	this->ptrBestDepotFeasibleSolution = this->currentDepotFeasibleSolution;
// }

// void FrogLeapController::setUpGlobalSolution(DecodedFrogLeapSolution * dfls_1, float evalSol)
// {	
// 	this->setGlobalImprovement();
		
// 	this->setBestDecodedFrogLeapSolution(dfls_1);
// 	this->setMinCostValue(evalSol);

// 	this->take_Execution_Time();
// 	this->set_BestSolution_ExecutionTime(this->get_Execution_Time());

// 	if(this->ptrBestDepotFeasibleSolution != this->currentDepotFeasibleSolution)
// 	{
// 		delete this->ptrBestDepotFeasibleSolution;
// 	}

// 	this->ptrBestDepotFeasibleSolution = this->currentDepotFeasibleSolution;
// }

// DecodedFrogLeapSolution * FrogLeapController::getBestDecodedFrogLeapSolution()
// {
// 	return this->ptrBestSolution;
// }

// void FrogLeapController::setRandomSeed()
// {
// 	srand(this->timeSeedUsed);
// }

// void FrogLeapController::applyLocalSearch()
// {
// 	float newCost = this->ptrBestSolution->applyLocalSearch(this);
// 	this->setMinCostValue(newCost);
// }

// void FrogLeapController::printCtrl()
// {
// 	printf("\n \n SHOWING DATA OF FROGLEAPING CONTROLLER \n");
// 	if(this->ptrBestSolution != nullptr)
// 	{
// 		this->ptrBestSolution->printFrogObj();
// 	}
// 	else
// 	{
// 		printf("\n NO FEASIBLE SOLUTION FOUND: ptrBestSolution IS nullptr \n");
// 	}
	
// 	printf("\n Summary of Best Found Solution \n");
// 	printf("	Time Seed used %lld \n", (long long)this->timeSeedUsed);
// 	printf("	Number of success attempts: %d \n", this->successAttempts);
// 	printf("	Number of fail attempts: %d \n", this->failAttempts);
// 	printf("	Number of TOTAL Improvements: %d \n", this->getTotalImprovements());
// 	printf("	Number of Global Search Improvements: %d \n", this->globalImprovements);
// 	printf("	Number of Local Search Improvements: %d \n", this->localSearchImprovements);
// 	printf("	Evaluation of best found solution is: %.3f \n \n", this->getMinCostValue());
// }

void FrogLeapController::loadTSPEUC2D_Data(char * fileName)
{
	
	FILE * filePtr;	
	
	TspLibEuc2D * tspLibEuc2DPtrAux = new TspLibEuc2D();
	
	char * sectionTag = new char[50], *separatorChar = new char[1], buf[line_max_value];

	string ctrlSectionTagStr, ctrlSeparatorCharStr, sectionTagStr, separatorCharStr;

	ctrlSeparatorCharStr = string(":");
		
	// Opening file
	if ((filePtr = fopen(fileName, "r")) != nullptr)
	{
		
		// Reading section tag NAME
		char * name = new char[50];
		if (fgets(buf, sizeof buf, filePtr) != nullptr)
		{
			sscanf(buf, "%s %s %s", sectionTag, separatorChar, name);
			printf("Section: %s %s %s \n", sectionTag, separatorChar, name);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;

			ctrlSectionTagStr = string("NAME");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setName(name);
		}
		else
		{
			printf("Error reading file \n");
			return;
		}

		// reading COMMENT
		char * comment = new char[100];
		if (fgets(buf, sizeof buf, filePtr) != nullptr)
		{
			sscanf(buf, "%s %s %s", sectionTag, separatorChar, comment);
			printf("Section: %s %s %s \n", sectionTag, separatorChar, comment);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;
			ctrlSectionTagStr = string("COMMENT");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setComment(comment);
		}
		else
		{
			printf("Error reading file \n");
			return;
		}

		
		// reading type
		char * type = new char[50];
		if (fgets(buf, sizeof buf, filePtr) != nullptr)
		{
			sscanf(buf, "%s %s %s", sectionTag, separatorChar, type);
			printf("Section: %s %s %s \n", sectionTag, separatorChar, type);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;

			ctrlSectionTagStr = string("TYPE");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setType(type);
		}
		else
		{
			printf("Error reading file \n");
			return;
		}

		// reading DIMENSION
		int dimension;
		if (fgets(buf, sizeof buf, filePtr) != nullptr)
		{
			sscanf(buf, "%s %s %d", sectionTag, separatorChar, &dimension);
			printf("Section: %s %s %d \n", sectionTag, separatorChar, dimension);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;

			ctrlSectionTagStr = string("DIMENSION");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setDimension(dimension);
		}
		else
		{
			printf("Error reading file \n");
			return;
		}
		
		// reading EDGE_WEIGHT_TYPE
		char * edge_weight_type = new char[50];;
		if (fgets(buf, sizeof buf, filePtr) != nullptr)
		{
			sscanf(buf, "%s %s %s", sectionTag, separatorChar, edge_weight_type);
			printf("Section: %s %s %s \n", sectionTag, separatorChar, edge_weight_type);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;

			ctrlSectionTagStr = string("EDGE_WEIGHT_TYPE");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setEdgeWeightType(edge_weight_type);
		}
		else
		{
			printf("Error reading file \n");
			return;
		}
		

		// reading CAPACITY
		int capacity;
		if (fgets(buf, sizeof buf, filePtr) != nullptr)
		{
			sscanf(buf, "%s %s %d", sectionTag, separatorChar, &capacity);
			printf("Section: %s %s %d \n", sectionTag, separatorChar, capacity);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;

			ctrlSectionTagStr = string("CAPACITY");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setCapacity(capacity);
		}
		else
		{
			printf("Error reading file \n");
			return;
		}

		// reading Node Coord Section
		char * nodeCoordSection = new char[50];;
		if (fgets(buf, sizeof buf, filePtr) != nullptr)
		{
			sscanf(buf, "%s ", nodeCoordSection);
			printf("Section: %s \n", nodeCoordSection);

			sectionTagStr = nodeCoordSection;
			
			ctrlSectionTagStr = string("NODE_COORD_SECTION");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			// Loading coordinates (we load the node Id, x_coord and y_coord)
			this->loadCoordinates(filePtr, tspLibEuc2DPtrAux);

			// Loading demands (we load the node Id, demand). The Id is the same as the previous one
			this->loadDemand(filePtr, tspLibEuc2DPtrAux);

			this->loadDepots(filePtr, tspLibEuc2DPtrAux);

			this->tspLibEud2DPtr = tspLibEuc2DPtrAux;
			fclose(filePtr);
		}
		else
		{
			printf("Error reading file \n");
			fclose(filePtr);
		}		
	}
	else
	{
		printf("Error found opening file");
		return;
	}
}

// DecodedFrogLeapSolution * FrogLeapController::loadTestCaseData(char * fileName)
// {
// 	FILE * filePtr;
// 	char * sectionTag = new char[50], *separatorChar = new char[1], buf[line_max_value];
// 	string ctrlSectionTagStr, ctrlSeparatorCharStr, sectionTagStr, separatorCharStr;

// 	TestCaseObj * testCaseObjPtr = new TestCaseObj();

// 	ctrlSeparatorCharStr = string(":");

// 	if ((filePtr = fopen(fileName, "r")) != nullptr)
// 	{
// 		// Reading section tag NAME
// 		char * name = new char[50];
// 		if (fgets(buf, sizeof buf, filePtr) != nullptr)
// 		{
// 			sscanf(buf, "%s %s %s", sectionTag, separatorChar, name);
// 			printf("Section: %s %s %s \n", sectionTag, separatorChar, name);

// 			sectionTagStr = sectionTag;
// 			separatorCharStr = separatorChar;

// 			ctrlSectionTagStr = string("NAME");
			
// 			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
// 			{
// 				printf("Error in file format \n");
// 				return nullptr;
// 			}

// 			testCaseObjPtr->setName(name);
// 		}
// 		else
// 		{
// 			printf("Error reading file \n");
// 			return nullptr;
// 		}

// 		// reading COMMENT
// 		char * comment = new char[100];
// 		if (fgets(buf, sizeof buf, filePtr) != nullptr)
// 		{
// 			sscanf(buf, "%s %s %s", sectionTag, separatorChar, comment);
// 			printf("Section: %s %s %s \n", sectionTag, separatorChar, comment);

// 			sectionTagStr = sectionTag;
// 			separatorCharStr = separatorChar;
// 			ctrlSectionTagStr = string("COMMENT");
// 			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
// 			{
// 				printf("Error in file format \n");
// 				return nullptr;
// 			}

// 			testCaseObjPtr->setComment(comment);
// 		}
// 		else
// 		{
// 			printf("Error reading file \n");
// 			return nullptr;
// 		}

// 		// reading DIMENSION
// 		int dimension;
// 		if (fgets(buf, sizeof buf, filePtr) != nullptr)
// 		{
// 			sscanf(buf, "%s %s %d", sectionTag, separatorChar, &dimension);
// 			printf("Section: %s %s %d \n", sectionTag, separatorChar, dimension);

// 			sectionTagStr = sectionTag;
// 			separatorCharStr = separatorChar;

// 			ctrlSectionTagStr = string("DIMENSION");
// 			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
// 			{
// 				printf("Error in file format \n");
// 				return nullptr;
// 			}

// 			testCaseObjPtr->setDimension(dimension);
// 		}
// 		else
// 		{
// 			printf("Error reading file \n");
// 			return nullptr;
// 		}

// 		// reading type
// 		char * type = new char[50];
// 		if (fgets(buf, sizeof buf, filePtr) != nullptr)
// 		{
// 			sscanf(buf, "%s %s %s", sectionTag, separatorChar, type);
// 			printf("Section: %s %s %s \n", sectionTag, separatorChar, type);

// 			sectionTagStr = sectionTag;
// 			separatorCharStr = separatorChar;

// 			ctrlSectionTagStr = string("TYPE");
// 			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
// 			{
// 				printf("Error in file format \n");
// 				return nullptr;
// 			}

// 			testCaseObjPtr->setType(type);
// 		}
// 		else
// 		{
// 			printf("Error reading file \n");
// 			return nullptr;
// 		}

// 		// reading CAPACITY
// 		int capacity;
// 		if (fgets(buf, sizeof buf, filePtr) != nullptr)
// 		{
// 			sscanf(buf, "%s %s %d", sectionTag, separatorChar, &capacity);
// 			printf("Section: %s %s %d \n", sectionTag, separatorChar, capacity);

// 			sectionTagStr = sectionTag;
// 			separatorCharStr = separatorChar;

// 			ctrlSectionTagStr = string("CAPACITY");
// 			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
// 			{
// 				printf("Error in file format \n");
// 				return nullptr;
// 			}

// 			testCaseObjPtr->setCapacity(capacity);
// 		}
// 		else
// 		{
// 			printf("Error reading file \n");
// 			return nullptr;
// 		}

// 		// reading Assignation Section
// 		char * assignationSection = new char[50];;
// 		if (fgets(buf, sizeof buf, filePtr) != nullptr)
// 		{
// 			sscanf(buf, "%s ", assignationSection);
// 			printf("Section: %s \n", assignationSection);

// 			sectionTagStr = assignationSection;

// 			ctrlSectionTagStr = string("ASSIGNATION");
// 			if (sectionTagStr.compare(ctrlSectionTagStr) != 0)
// 			{
// 				printf("Error in file format \n");
// 				return nullptr;
// 			}

// 			DecodedFrogLeapSolution * dfls = nullptr;
// 			FrogLeapSolution * fls = nullptr;

// 			// Loading assignations (customers to vehicles)
// 			dfls = this->loadAssignations2(filePtr, testCaseObjPtr);
// 			//fls = this->loadAssignations3(filePtr, testCaseObjPtr);
// 			//dfls = fls->decodeFrogLeapSolution(this);
// 			//dfls = fls->decodeSolutionWithAngularCriteria(this);
// 			float evaluation = dfls->evalSolution();
// 			printf("Showing test evaluation: %.3f", evaluation);
// 			fclose(filePtr);
// 			return dfls;
// 		}
// 		else
// 		{
// 			printf("Error reading file \n");
// 			fclose(filePtr);

// 			return nullptr;
// 		}
// 	}
// }

// void FrogLeapController::loadAssignations(FILE * filePtr, TestCaseObj * testCaseObjPtr)
// {
// 	bool stopLoop = false, vehicleDataLoaded = false, assignationBlockLoaded = false;
// 	int nodeLabelId = 0, depot_capacity = 0, customer_load = 0, v_dimension = testCaseObjPtr->getDimension();
// 	char buf[line_max_value];
// 	Pair * currPair;

// 	while(stopLoop == false)
// 	{
// 		if (fgets(buf, sizeof buf, filePtr) != nullptr)
// 		{
// 			if(vehicleDataLoaded == false)
// 			{
// 				sscanf(buf, "%d %d %d", &nodeLabelId, &depot_capacity, &customer_load);
// 				printf("Depot data: %d %d %d \n", nodeLabelId, depot_capacity, customer_load);

// 				currPair = new Pair(PairType::IntVsInt, nodeLabelId);
// 				currPair->set_i_IntValue(depot_capacity);
// 				currPair->set_j_IntValue(customer_load);
// 				currPair->setId(nodeLabelId);
// 				currPair->setValue(nodeLabelId);

// 				testCaseObjPtr->AddVehicleItem(currPair);
// 				vehicleDataLoaded = true;
// 				assignationBlockLoaded = false;
// 			}
// 			else
// 			{
// 				int customerLabelId;
// 				if(assignationBlockLoaded == false)
// 				{					
// 					sscanf(buf, "%d ", &customerLabelId);
// 					printf("Customer Label Id : %d \n", customerLabelId);
					
// 					if(customerLabelId == -1)
// 					{
// 						assignationBlockLoaded = true;
// 						vehicleDataLoaded = false;
// 					}
// 					else
// 					{
// 						if(customerLabelId == -2)
// 						{
// 							stopLoop = true;
// 						}
// 						else
// 						{
// 							currPair = new Pair(PairType::IntVsInt, customerLabelId);
// 							currPair->set_i_IntValue(customerLabelId);
// 							currPair->set_j_IntValue(nodeLabelId);
// 							currPair->setId(customerLabelId);
// 							currPair->setValue(customerLabelId);

// 							testCaseObjPtr->AddCustomerItem(currPair);
// 						}
// 					}
// 				}
// 			}
// 		}
// 		else
// 		{
// 			printf("Error reading file: Section Node Coordinates \n");
// 			return;
// 		}
// 	}
// }

// // This method creates an already decoded solution
// DecodedFrogLeapSolution * FrogLeapController::loadAssignations2(FILE * filePtr, TestCaseObj * testCaseObjPtr)
// {
// 	bool stopLoop = false, vehicleDataLoaded = false, assignationBlockLoaded = false;
// 	int depotLabelId = 0, vehicle_cost = 0, vehicle_load = 0, v_dimension = testCaseObjPtr->getDimension();
// 	char buf[line_max_value];
// 	Pair * currPair;
// 	float globalCounter = 0;
// 	int depotIndex;

// 	DecodedFrogLeapSolution * decodedSolution = new DecodedFrogLeapSolution(this->getNumberOfDepots(), this);
// 	Vehicle * veh = nullptr;
// 	int count;
// 	Pair * customerPair = nullptr;

// 	int prevDepotLabelId = -1;

// 	while (fgets(buf, sizeof buf, filePtr) != nullptr)
// 	{
// 		char* tok = strtok(buf, " ");
			
// 		// read data of the depot vehicle
// 		count = 0;
			
// 		// Loading the first three data of the vehicle depot
// 		while (tok != nullptr && count < 3) // Correct logic to use to stop looping.
// 		{
// 			if(count == 0)
// 			{
// 				depotLabelId = atoi(tok);
// 				cout << depotLabelId << endl;  // Print the current token before getting the next token.
// 			}				

// 			if(count == 1)
// 			{
// 				vehicle_cost = atoi(tok);
// 				cout << vehicle_cost << endl;  // Print the current token before getting the next token.
// 			}

// 			if(count == 2)
// 			{
// 				vehicle_load = atoi(tok);
// 				cout << vehicle_load << endl;  // Print the current token before getting the next token.
// 			}
								
// 			tok = strtok(nullptr, " ");
// 			count++;
// 		}

// 		veh = new Vehicle(this->getGlobalVehicleId(), this);
// 		veh->setDepotInternalId(depotLabelId);
// 		depotIndex = this->getDepotIndexByLabelId(depotLabelId);
// 		veh->setDepotIndex(depotIndex);

// 		decodedSolution->addVehicle(depotIndex, veh);

// 		count = 0;

// 		int customerLabelId, customerIndex;
// 		while (tok != nullptr) 
// 		{
// 			customerLabelId = atoi(tok);
// 			customerIndex = this->getCustomerIndexByLabelId(customerLabelId);
// 			float fvalue = depotIndex + (globalCounter / 1000);
// 			customerPair = new Pair(PairType::IntVsFloat);
// 			customerPair->set_i_IntValue(customerIndex);
// 			customerPair->set_j_FloatValue(fvalue);
// 			customerPair->setValue(fvalue);
// 			customerPair->setId(customerIndex);
				
// 			veh->addLastCustomerPair(customerPair);

// 			tok = strtok(nullptr, " ");

// 			globalCounter = globalCounter + 1;
// 		}

// 		globalCounter = 0;
// 		prevDepotLabelId = depotLabelId;
// 	}

// 	return decodedSolution;
// }


// FrogLeapSolution * FrogLeapController::loadAssignations3(FILE * filePtr, TestCaseObj * testCaseObjPtr)
// {
// 	bool stopLoop = false, vehicleDataLoaded = false, assignationBlockLoaded = false;
// 	int depotLabelId = 0, vehicle_cost = 0, vehicle_load = 0, v_dimension = testCaseObjPtr->getDimension();
// 	char buf[line_max_value];
// 	Pair * currPair;
// 	float globalCounter = 0, fvalue;
// 	int depotIndex, customerLabelId, customerIndex;
// 	FrogLeapSolution * frogLeapSolution = new FrogLeapSolution(SolutionGenerationType::FrogLeaping, this->getSourceType(), this->getNumberOfCustomers(), this->getNumberOfDepots(), 0);
		
// 	int count;
// 	Pair * customerPair = nullptr;
		
// 	while (fgets(buf, sizeof buf, filePtr) != nullptr)
// 	{
// 		char* tok = strtok(buf, " ");

// 		// read data of the depot vehicle
// 		count = 0;

// 		// Loading the first three data of the vehicle depot
// 		while (tok != nullptr && count < 3) // Correct logic to use to stop looping.
// 		{
// 			if (count == 0)
// 			{
// 				depotLabelId = atoi(tok);
// 				cout << depotLabelId << endl;  // Print the current token before getting the next token.
// 			}

// 			if (count == 1)
// 			{
// 				vehicle_cost = atoi(tok);
// 				cout << vehicle_cost << endl;  // Print the current token before getting the next token.
// 			}

// 			if (count == 2)
// 			{
// 				vehicle_load = atoi(tok);
// 				cout << vehicle_load << endl;  // Print the current token before getting the next token.
// 			}

// 			tok = strtok(nullptr, " ");
// 			count++;
// 		}

// 		depotIndex = this->getDepotIndexByLabelId(depotLabelId);
// 		count = 0;

// 		while (tok != nullptr)
// 		{
// 			customerLabelId = atoi(tok);
// 			customerIndex = this->getCustomerIndexByLabelId(customerLabelId);
// 			fvalue = depotIndex + (globalCounter / 1000);
// 			frogLeapSolution->setFLValue(customerIndex, fvalue);

// 			tok = strtok(nullptr, " ");

// 			globalCounter = globalCounter + 1;
// 		}		
// 	}

// 	return frogLeapSolution;
// }


void FrogLeapController::loadCoordinates(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr)
{
	//bool stopLoop = false;
	int nodeId = 0, x_coord = 0, y_coord = 0, v_dimension = tspLibEuc2DPtr->getDimension();
	char buf[line_max_value];

	for(int i=0; i < v_dimension;i++)
	{
		if (fgets(buf, sizeof buf, filePtr) != nullptr)
		{
			sscanf(buf, "%d %d %d", &nodeId, &x_coord, &y_coord);
			printf("Coordinate: %d %d %d \n", nodeId, x_coord, y_coord);

			Pair * currPair = new Pair(PairType::IntVsInt, nodeId);

			currPair->set_i_IntValue(x_coord);
			currPair->set_j_IntValue(y_coord);
			currPair->setId(nodeId);
			currPair->setValue(nodeId);

			tspLibEuc2DPtr->AddNodeCoordItem(currPair);
		}
		else
		{
			printf("Error reading file: Section Node Coordinates \n");
			return;
		}
	}
}

void FrogLeapController::loadDemand(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr)
{	
	int nodeId = -1, demand = 0;
	char * demandSection = new char[50];
	char buf [line_max_value];

	if (fgets(buf, sizeof buf, filePtr) != nullptr)
	{
		sscanf(buf, "%s ", demandSection);
		printf("Section: %s \n", demandSection);
	}

	string sectionTagStr = demandSection;

	string ctrlSectionTagStr = string("DEMAND_SECTION");

	if (sectionTagStr.compare(ctrlSectionTagStr) != 0)
	{
		printf("Error in file format \n");
		return;
	}

	int dimension = tspLibEuc2DPtr->getDimension();

	for (int i = 0; i < dimension; i++)
	{
		if (fgets(buf, sizeof buf, filePtr) != nullptr)
		{
			sscanf(buf, "%d %d", &nodeId, &demand);
			printf("Demand: %d %d \n", nodeId, demand);

	
			Pair * currPair = new Pair(PairType::IntVsInt, nodeId);

			currPair->set_i_IntValue(nodeId);
			currPair->set_j_IntValue(demand);
			currPair->setId(nodeId);
			currPair->setValue(nodeId);

			tspLibEuc2DPtr->AddDemandItem(currPair);
		}
		else
		{
			printf("Error reading file: Section Node Coordinates \n");
			return;
		}
	}
}

void FrogLeapController::loadDepots(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr)
{
	int depotId = -2;
	char * depotSection = new char[50];
	char buf[line_max_value];

	if (fgets(buf, sizeof buf, filePtr) != nullptr)
	{
		sscanf(buf, "%s ", depotSection);
		printf("Section: %s \n", depotSection);
	}

	string sectionTagStr = depotSection;

	string ctrlSectionTagStr = string("DEPOT_SECTION");

	if (sectionTagStr.compare(ctrlSectionTagStr) != 0)
	{
		printf("Error in file format \n");
		return;
	}
	
	bool stopLoop = false;

	while(!stopLoop)	
	{
		if (fgets(buf, sizeof buf, filePtr) != nullptr)
		{
			sscanf(buf, "%d ", &depotId);
			printf("%d \n", depotId);

			if(depotId != -1)
			{
				tspLibEuc2DPtr->AddDepotItem(depotId);
			}
			else
			{
				stopLoop = true;
			}
		}
		else
		{
			printf("Error reading file: Section Node Coordinates \n");
			return;
		}
	}
}

DistanceTable * FrogLeapController::loadDistanceTable()
{
	int dimension = this->tspLibEud2DPtr->getDimension();
	float floatDistance;

	DistanceTable * fdt = new DistanceTable(dimension);

	for(int i = 0; i < dimension; i++)
	{
		for(int j = i + 1; j < dimension; j++)
		{
			floatDistance = this->tspLibEud2DPtr->getEucDistance(i, j);			

			// we add two edges (a[u][v] and a[v][u])
			fdt->addEdge(i, j, floatDistance);			

			//if (i == 54 && j == 260)
			//{
			//	printf("Testing distance table: dt[%d, %d] = %f", i, j, fdt->getEdge(i,j));
			//}

		}
	}

	for (int k = 0; k < dimension; k++)
	{
		fdt->addDiagEdge(k, 0);
	}

	this->distTablePtr = fdt;

	return fdt;
}

// void FrogLeapController::setDistanceTable(DistanceTable * t)
// {
// 	this->distTablePtr = t;
// }

// DistanceTable * FrogLeapController::getDistanceTable()
// {
// 	return this->distTablePtr;
// }

// void FrogLeapController::setFloatDistanceTable(FloatDistanceTable * t)
// {
// 	this->floatDistTablePtr = t;
// }

// FloatDistanceTable * FrogLeapController::getFloatDistanceTable()
// {
// 	return this->floatDistTablePtr;
// }

int FrogLeapController::getNumberOfDepots()
{
	if(this->source_t == SourceType::Graph)
	{
		return this->depotList->getSize();
	}
	else
	{
		return this->tspLibEud2DPtr->getNumberOfDepots();
	}	
}

// Pair * FrogLeapController::getDepotPairByIndex(int position)
// {
// 	return this->depotArray[position];
// }


// Pair * FrogLeapController::getDepotPairByInternal(int customerInternalId)
// {
// 	int depotIndex = this->getDepotListIndexByInternal(customerInternalId);

// 	Pair * depotPair = this->getDepotPairByIndex(depotIndex);

// 	return depotPair;
// }

// Pair * FrogLeapController::getCustomerPairByInternal(int customerInternalId)
// {
// 	int customerIndex = this->getCustomerListIndexByInternal(customerInternalId);

// 	Pair * customerPair = this->getCustomerPairByIndex(customerIndex);

// 	return customerPair;
// }

// Pair * FrogLeapController::getCustomerPairByIndex(int position)
// {
// 	return this->customerArray[position];
// }

// Pair * FrogLeapController::getPairByInternalId(int internalId)
// {
// 	return (Pair *) this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(internalId);	
// }

// void FrogLeapController::setAngularValues(Pair * customerPair, int customerInternalId, int depotInternalId)
// {
// 	float theta = this->tspLibEud2DPtr->getAngularTheta(customerInternalId, depotInternalId);
// 	float rho = this->tspLibEud2DPtr->getAngularRho(customerInternalId, depotInternalId);

// 	customerPair->setValue(theta);
// 	customerPair->setValue2(rho);
// }

// void FrogLeapController::setUpVehiclesPerDepot()
// {
// 	int numOfDepots = this->depotList->getSize();
// 	Pair * depotPair = nullptr;
// 	int depotDemand, depotId;

// 	this->vehiclePairList = new FrogObjectCol();

// 	for (int i = 0; i < numOfDepots; i++)
// 	{
// 		depotPair = this->depotArray[i];
// 		depotId = depotPair->get_i_IntValue();
// 		depotDemand = depotPair->get_j_IntValue();

// 		assignVehiclesToDepots(depotId, depotDemand);
// 	}

// 	setUpVehiclePairList();
// }

// void FrogLeapController::assignVehiclesToDepots(int depotId, int depotDemand)
// {
// 	int remainingDemand = depotDemand;
// 	Pair * vehiclePair = nullptr;
// 	int currentId = this->vehiclePairList->getSize();
	
// 	while (remainingDemand > 0)
// 	{
// 		vehiclePair = new Pair(PairType::IntVsInt);
// 		vehiclePair->setId(currentId);		

// 		vehiclePair->set_i_IntValue(this->getVehicleCapacity());
// 		vehiclePair->set_j_IntValue(depotId);
// 		this->vehiclePairList->addFrogObjectOrdered(vehiclePair);

// 		if(remainingDemand >= this->getVehicleCapacity())
// 		{
// 			remainingDemand = remainingDemand - this->getVehicleCapacity();
// 		}
// 		else
// 		{
// 			remainingDemand = 0;
// 		}
// 	}
// }

int FrogLeapController::getNumberOfCustomers()
{
	if (this->source_t == SourceType::Graph)
	{
		return this->customerList->getSize();
	}
	else
	{
		return this->tspLibEud2DPtr->getNumberOfCustomers();
	}
}

// void FrogLeapController::setGraph(Graph * gPtr)
// {
// 	this->graphPtr = gPtr;
// }

// Graph * FrogLeapController::getGraph()
// {
// 	return this->graphPtr;
// }

void FrogLeapController::setSourceType(SourceType source)
{
	this->source_t = source;
}

SourceType FrogLeapController::getSourceType()
{
	return this->source_t;
}

// void FrogLeapController::setSolutionGenerationType(SolutionGenerationType v_sgt)
// {
// 	this->sgt = v_sgt;
// }

// SolutionGenerationType FrogLeapController::getSolutionGenerationType()
// {
// 	return this->sgt;
// }

// void FrogLeapController::readTSPSection(FILE * filePtr, char * ctrlSectionTag, char * ctrlSeparatorChar, int * off_set)
// {
// 	char * sectionTag = new char[50], *separatorChar = new char[1], buf[line_max_value];

// 	string ctrlSectionTagStr = ctrlSectionTag, ctrlSeparatorCharStr = ctrlSeparatorChar;

// 	if (fgets(buf, sizeof buf, filePtr) != nullptr)
// 	{
// 		sscanf(buf, "%s %s", sectionTag, separatorChar);
// 		printf("Section: %s %s", sectionTag, separatorChar);

// 		string sectionTagStr = sectionTag;
// 		string separatorCharStr = separatorChar;

// 		if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
// 		{
// 			printf("Error in file format \n");
// 			return;
// 		}

// 		loadTSPSection(buf, sectionTag);
// 	}
// 	else
// 	{
// 		printf("Error buffering file content \n");
// 	}
// }

// void FrogLeapController::loadTSPSection(char * buf, char * sectionTag)
// {
// 	char * auxContentCharPtr = new char[50];
// 	string auxContentStr, sectionTagStr;
// 	int auxShortInt;

// 	sectionTagStr = sectionTag;

// 	if (sectionTagStr.compare("NAME") == 0)
// 	{
// 		sscanf(buf, "%s", auxContentCharPtr);

// 		this->tspLibEud2DPtr->setName(auxContentCharPtr);
// 		return;
// 	}

// 	if (sectionTagStr.compare("TYPE") == 0)
// 	{
// 		sscanf(buf, "%s", auxContentCharPtr);
// 		this->tspLibEud2DPtr->setType(auxContentCharPtr);
// 		return;
// 	}

// 	if (sectionTagStr.compare("DIMENSION") == 0)
// 	{
// 		sscanf(buf, "%hu", &auxShortInt);

// 		this->tspLibEud2DPtr->setDimension(auxShortInt);
// 		return;
// 	}

// 	if (sectionTagStr.compare("EDGE_WEIGHT_TYPE") == 0)
// 	{
// 		sscanf(buf, "%s", auxContentCharPtr);
// 		this->tspLibEud2DPtr->setEdgeWeightType(auxContentCharPtr);
// 		return;
// 	}

// 	if (sectionTagStr.compare("CAPACITY") == 0)
// 	{
// 		sscanf(buf, "%hu", &auxShortInt);
// 		this->tspLibEud2DPtr->setCapacity(auxShortInt);
// 		return;
// 	}

// 	printf("Error in file format: Section does not exist");

// 	return;
// }


// void FrogLeapController::setFailAttempts(int vfailAttempts)
// {
// 	this->failAttempts = vfailAttempts;
// }

// int FrogLeapController::getSuccessAttempts()
// {
// 	return this->successAttempts;
// }

// void FrogLeapController::incSuccessAttempts()
// {
// 	this->successAttempts++;
// }

// void FrogLeapController::setSuccessAttempts(int vsucessAttempts)
// {
// 	this->successAttempts = vsucessAttempts;
// }

void FrogLeapController::setAsCustomer(int customerInternalId, int demand)
{
	Pair * customerPair = new Pair(PairType::IntVsInt);
	customerPair->set_i_IntValue(demand);
	customerPair->set_j_IntValue(demand);
	customerPair->setValue(customerInternalId);
	customerPair->setId(customerInternalId);

	this->customerList->addFrogObjectOrdered(customerPair);
}

void FrogLeapController::setAsDepot(int depotInternalId, int capacity)
{

	Pair * depotPair = new Pair(PairType::IntVsInt);
	depotPair->set_i_IntValue(capacity);
	depotPair->set_j_IntValue(capacity);
	depotPair->setValue(depotInternalId);
	depotPair->setId(depotInternalId);

	this->depotList->addFrogObjectOrdered(depotPair);
}

void FrogLeapController::setUpCustomerList()
{
	int n_customers = this->getNumberOfCustomers();

	this->customerArray = new Pair *[n_customers];

	for (int i = 0; i < n_customers; i++)
	{
		this->customerArray[i] = (Pair *) this->customerList->getFrogObject(i);
	}
}

void FrogLeapController::setUpDepotList()
{
	int n_depots = this->getNumberOfDepots();

	this->depotArray = new Pair *[n_depots];

	for (int i = 0; i < n_depots; i++)
	{
		depotArray[i] = (Pair *)this->depotList->getFrogObject(i);
	}
}

void FrogLeapController::loadCustomerAndDepotList()
{
	int size = this->tspLibEud2DPtr->getDimension(), demandOrCapacity;

	IndexList * depotListSection = this->tspLibEud2DPtr->getDepotSection();

	// i is the internal id of the node in the nodeCoordSection collection
	for (int i = 0; i < size; i++)
	{			
		Pair * nodeCoord = (Pair *) this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(i);

		int nodeIdLabel = nodeCoord->getId();

		Pair * demandPair = (Pair *) this->tspLibEud2DPtr->getDemandSection()->getFrogObjectById(nodeIdLabel);

		if(demandPair != nullptr)
		{
			demandOrCapacity = demandPair->get_j_IntValue();
		}		

		//if does not exist then it is a customer
		if (depotListSection->getItemById(nodeIdLabel) == -1)
		{				
			this->setAsCustomer(i, demandOrCapacity);
		}
		else //is a depot
		{
			this->setAsDepot(i, demandOrCapacity);
		}
	}
}

// int FrogLeapController::getLabel(int internalId)
// {
// 	if(this->source_t == SourceType::Graph)
// 	{
// 		return this->graphPtr->getVertexIdByPosition(internalId);
// 	}
// 	else
// 	{
// 		return this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(internalId)->getId();
// 	}
	
// }

// int FrogLeapController::getDepotListIndexByInternal(int depotInternalId)
// {

// 	for (int i = 0; i < this->depotList->getSize(); i++)
// 	{
// 		if (this->depotArray[i]->getId() == depotInternalId)
// 		{			
// 			return i;
// 		}
// 	}

// 	return -1;
// }

// int FrogLeapController::getCustomerListIndexByInternal(int customerInternalId)
// {

// 	for (int i = 0; i < this->customerList->getSize(); i++)
// 	{
// 		if (this->customerArray[i]->getId() == customerInternalId)
// 		{
// 			return i;
// 		}
// 	}

// 	return -1;
// }

// int FrogLeapController::getDepotIndexByLabelId(int depotLabelId)
// {
	
// 	int depotInternalIndex = -1;
// 	Pair * depotPair = nullptr;
// 	Pair * nodeCoord = nullptr;

// 	for(int i = 0; i < this->getNumberOfDepots(); i++)
// 	{
// 		depotPair = (Pair *)this->depotArray[i];

// 		if(depotPair != nullptr)
// 		{
// 			depotInternalIndex = depotPair->getId();
// 			nodeCoord = (Pair *) this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(depotInternalIndex);
// 			if(nodeCoord != nullptr)
// 			{
// 				int nodeIdLabel = nodeCoord->getId();
// 				if(nodeIdLabel == depotLabelId)
// 				{
// 					return i;
// 				}
// 			}
// 		}		
// 	}

// 	return -1;
// }

// int FrogLeapController::getCustomerIndexByLabelId(int customerLabelId)
// {
// 	int customerInternalIndex = -1;
// 	Pair * customerPair = nullptr;
// 	Pair * nodeCoord = nullptr;

// 	for (int i = 0; i < this->getNumberOfCustomers(); i++)
// 	{
// 		customerPair = (Pair *)this->customerArray[i];

// 		if (customerPair != nullptr)
// 		{
// 			customerInternalIndex = customerPair->getId();
// 			nodeCoord = (Pair *) this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(customerInternalIndex);
// 			if (nodeCoord != nullptr)
// 			{
// 				int nodeIdLabel = nodeCoord->getId();
// 				if (nodeIdLabel == customerLabelId)
// 				{
// 					return i;
// 				}
// 			}
// 		}
// 	}

// 	return -1;
// }

// FrogObjectCol * FrogLeapController::getTestCustomerSectionList()
// {
// 	return this->testCaseObjPtr->getCustomerSection();
// }

void FrogLeapController::setUpCustomerAndDepotLists()
{
	if(this->getSourceType() == SourceType::Tsp2DEuc)
	{
		loadCustomerAndDepotList();		
	}

 	setUpCustomerList();
 	setUpDepotList();
 }

void FrogLeapController::setUpVehicleCapacity()
{
	this->vehicle_capacity = this->tspLibEud2DPtr->getCapacity();
}

// long int FrogLeapController::getVehicleCapacity()
// {
// 	return this->vehicle_capacity;
// }

// void FrogLeapController::setUpVehiclePairList()
// {
// 	int n_vehiclePairs = this->vehiclePairList->getSize();

// 	this->vehiclePairArray = new Pair *[n_vehiclePairs];

// 	for (int i = 0; i < n_vehiclePairs; i++)
// 	{
// 		vehiclePairArray[i] = (Pair *)this->vehiclePairList->getFrogObject(i);
// 	}
// }

// int FrogLeapController::getNumberOfVehicles()
// {
// 	return this->vehiclePairList->getSize();
// }

int FrogLeapController::getCustomerInternalId(int position)
{
	return this->customerArray[position]->getId();
}


// int FrogLeapController::getCustomerDemandByIndex(int position)
// {
// 	return this->customerArray[position]->get_j_IntValue();
// }

// int FrogLeapController::getDepotInternalId(int position)
// {
	
// 	return this->depotArray[position]->getId();
// }

// int  FrogLeapController::getDepotCapacityByIndex(int position)
// {
// 	return this->depotArray[position]->get_i_IntValue();
// }

// int  FrogLeapController::getDepotRemainingCapacityByIndex(int position)
// {
// 	return this->depotArray[position]->get_j_IntValue();
// }

// void FrogLeapController::decRemainingDepotCapacity(int position, int capacity_to_dec)
// {
// 	int oldValue = this->depotArray[position]->get_j_IntValue();
// 	this->depotArray[position]->set_j_IntValue(oldValue - capacity_to_dec);
// }

// void  FrogLeapController::setDepotRemainingCapacityByIndex(int position, int remaining_capacity)
// {
// 	this->depotArray[position]->set_j_IntValue(remaining_capacity);
// }

// FrogLeapSolution * FrogLeapController::genRandomFrogLeapSolution(FrogLeapController * controller)
// {
// 	FrogLeapSolution * result = new FrogLeapSolution(this->sgt, this->source_t, this->getNumberOfCustomers(), this->getNumberOfDepots(), 0);

// 	result->genRandomSolution(controller);
// 	return result;
// }

// long int FrogLeapController::getTope()
// {
// 	return TOPE_ITERATIONS;
// }

// FrogObjectCol * FrogLeapController::createDepotListOrderedByCapacity()
// {
// 	FrogObjectCol * localDepotCol = new FrogObjectCol();
// 	Pair * current = nullptr;

// 	for(int i = 0; i < this->getNumberOfDepots(); i++)
// 	{
// 		current = this->depotArray[i];
// 		current->setValue(current->get_i_IntValue());
// 		localDepotCol->addFrogObjectOrdered(current);
// 	}

// 	return localDepotCol;
// }

// FrogObjectCol * FrogLeapController::createDepotListDescOrderedByCapacity()
// {
// 	FrogObjectCol * localDepotCol = new FrogObjectCol();
// 	Pair * current = nullptr;

// 	for (int i = 0; i < this->getNumberOfDepots(); i++)
// 	{
// 		current = this->depotArray[i];
// 		current->setValue(current->get_i_IntValue());
// 		localDepotCol->addFrogObjectDescOrdered(current);
// 	}

// 	return localDepotCol;
// }

// FrogObjectCol * FrogLeapController::createDepotListOrderedByRemainingCapacity()
// {
// 	FrogObjectCol * localDepotCol = new FrogObjectCol();
// 	Pair * current = nullptr;

// 	for (int i = 0; i < this->getNumberOfDepots(); i++)
// 	{
// 		current = this->depotArray[i];
// 		current->setValue(current->get_j_IntValue());
// 		localDepotCol->addFrogObjectOrdered(current);
// 	}

// 	return localDepotCol;
// }

// // create a list ordered by demand in descendant order
// FrogObjectCol * FrogLeapController::createCustomerListOrderedByDemandDesc()
// {
// 	FrogObjectCol * localCustomerCol = new FrogObjectCol();
// 	Pair * current = nullptr;

// 	for (int i = 0; i < this->getNumberOfCustomers(); i++)
// 	{
// 		current = this->customerArray[i];
// 		current->setValue(current->get_i_IntValue());
// 		localCustomerCol->addFrogObjectDescOrdered(current);
// 	}

// 	return localCustomerCol;
// }

// // create a list ordered by demand in descendant order
// FrogObjectCol * FrogLeapController::createCustomerListOrderedByDemand()
// {
// 	FrogObjectCol * localCustomerCol = new FrogObjectCol();
// 	Pair * current = nullptr;

// 	for (int i = 0; i < this->getNumberOfCustomers(); i++)
// 	{
// 		current = this->customerArray[i];
// 		localCustomerCol->addFrogObjectOrdered(current);
// 	}

// 	return localCustomerCol;
// }

// void FrogLeapController::resetDepotRemainingCapacities()
// {
// 	for (int i = 0; i < this->getNumberOfDepots(); i++)
// 	{		
// 		resetCapacityOrDemand(this->depotArray[i]);
// 	}
// }

// void FrogLeapController::resetCustomerRemainingDemands()
// {
// 	for (int i = 0; i < this->getNumberOfCustomers(); i++)
// 	{
// 		resetCapacityOrDemand(this->customerArray[i]);
// 	}
// }

// void FrogLeapController::resetCapacityOrDemand(Pair * nodePair)
// {
	
// 	int demandOrCap = nodePair->get_i_IntValue();
// 	nodePair->set_j_IntValue(demandOrCap);	
// }

// void FrogLeapController::unreferenceArray(Pair ** arrayPtr, int v_size) {
// 	int size = v_size;

// 	for (int i = 0; i < size; i++)
// 	{
// 		//delete arrayPtr[i];
// 		arrayPtr[i] = nullptr;
// 	}	
// }

// long long int FrogLeapController::getGlobalVehicleId()
// {
// 	long long int result = this->globalVehicleId;

// 	this->globalVehicleId++;

// 	return result;
// }

// int FrogLeapController::getCloserIndexToDepot(int depotIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localNodeCol)
// {
// 	float closerDistance = FLT_MAX;
// 	int closerNodeIndex = INT_MAX;

// 	for (int i = lowBoundIndex; i < topBoundIndex; i++)
// 	{
// 		Pair * currentPair = (Pair *)localNodeCol->getFrogObject(i);
// 		Pair * depotPair = (Pair *) this->depotArray[depotIndex];
// 		int nodeInternalId = currentPair->getId();
// 		int depotInternalId = depotPair->getId();
// 		DistanceTable * dt = this->getDistanceTable();
// 		float currentDistance = dt->getEdge(nodeInternalId, depotInternalId);
// 		if (currentDistance < closerDistance)
// 		{
// 			closerDistance = currentDistance;
// 			closerNodeIndex = i;
// 		}
// 	}

// 	return closerNodeIndex;
// }

// // returns the index in the local collection passed as parameter
// int FrogLeapController::getClosestCustomerLocalIndexToDepot(int depotIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localCustomerIndexesCol)
// {
// 	float closerDistance = FLT_MAX;
// 	int closerNodeIndex = INT_MAX;

// 	for (int i = lowBoundIndex; i < topBoundIndex; i++)
// 	{
// 		Pair * customerPair = (Pair *)localCustomerIndexesCol->getFrogObject(i);
// 		Pair * depotPair = (Pair *) this->depotArray[depotIndex];
// 		int customerInternalId = customerPair->getId();
// 		int depotInternalId = depotPair->getId();
// 		DistanceTable * dt = this->getDistanceTable();

// 		float currentDistance = dt->getEdge(customerInternalId, depotInternalId);
// 		if (currentDistance < closerDistance)
// 		{
// 			closerDistance = currentDistance;
// 			closerNodeIndex = i;
// 		}
// 	}

// 	return closerNodeIndex;
// }

// // returns the index in the local collection passed as parameter
// int FrogLeapController::getClosestCustomerLocalIndexToCustomer(int targetCustomerInternalId, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localCustomerIndexesCol)
// {
// 	float closerDistance = FLT_MAX;
// 	int closerNodeIndex = INT_MAX;

// 	for (int i = lowBoundIndex; i < topBoundIndex; i++)
// 	{
// 		Pair * customerPair = (Pair *)localCustomerIndexesCol->getFrogObject(i);
		
// 		int customerInternalId = customerPair->getId();		
// 		DistanceTable * dt = this->getDistanceTable();
// 		float currentDistance = dt->getEdge(customerInternalId, targetCustomerInternalId);

// 		if (currentDistance < closerDistance)
// 		{
// 			closerDistance = currentDistance;
// 			closerNodeIndex = i;
// 		}
// 	}

// 	return closerNodeIndex;
// }

// bool FrogLeapController::existInLocalDepotList(int assignedDepotIndex, FrogObjectCol * localDepotCol, int low, int top)
// {
// 	for(int i = low; i < top; i++)
// 	{
// 		Pair * currentPair = (Pair *)localDepotCol->getFrogObject(i);
// 		int depotInternalId = currentPair->getId();
// 		int depotIndex = this->getDepotListIndexByInternal(depotInternalId);
		
// 		if(assignedDepotIndex == depotIndex)
// 		{
// 			return true;
// 		}		
// 	}

// 	return false;	
// }

// int FrogLeapController::getDepotIndexOfClosestAssignedCustomer (int targetCustomerIndex, FrogObjectCol * localDepotCol, int low, int top, float & distanceToCustomer)
// {
// 	float closestDistance = FLT_MAX, currentDistance;
// 	int result = -1;
// 	Pair * customerPair = nullptr;
// 	int assignedDepotIndex;
// 	int customerInternalId;
// 	Pair * targetCustomerPair;
// 	int targetCustomerInternalId;
// 	DistanceTable * dt = nullptr;

// 	for(int i = 0; i < this->getNumberOfCustomers(); i++)
// 	{
// 		customerPair = this->customerArray[i];

// 		assignedDepotIndex = customerPair->getAssignedDepotIndex();

// 		if(assignedDepotIndex != -1)
// 		{
// 			if(existInLocalDepotList(assignedDepotIndex, localDepotCol, low, top) == true)
// 			{
// 				customerInternalId = customerPair->getId();
// 				targetCustomerPair = (Pair *)this->customerArray[targetCustomerIndex];
// 				targetCustomerInternalId = targetCustomerPair->getId();
// 				dt = this->getDistanceTable();

// 				currentDistance = dt->getEdge(targetCustomerInternalId, customerInternalId);

// 				if(this->distanceTypeMeasure == DistanceTypeCtrl::knapsack)
// 				{
// 					currentDistance = currentDistance / targetCustomerPair->get_i_IntValue();
// 				}

// 				if(currentDistance < closestDistance)
// 				{
// 					closestDistance = currentDistance;
// 					result = customerPair->getAssignedDepotIndex();
// 					distanceToCustomer = closestDistance;
// 				}
// 			}
// 		}
// 	} //end for

// 	return result;
// }

// void FrogLeapController::setCustomerPairAsAssigned(int customerIndex, int depotIndex)
// {
// 	Pair * customerPair = this->customerArray[customerIndex];

// 	customerPair->setAssignedDepotIndex(depotIndex);
// }

// // Set every pair in customerArray as not assigned
// void FrogLeapController::resetCustomersAsNotAssigned()
// {
// 	for(int i = 0; i < this->getNumberOfCustomers(); i++)
// 	{
// 		Pair * customerPair = this->customerArray[i];
// 		customerPair->setAssignedDepotIndex(-1);
// 	}
// }

// int FrogLeapController::getClosestLocalDepotIndexToCustomer(int customerIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localDepotCol, float & distance)
// {
// 	float closestDistance = FLT_MAX;
// 	int closestNodeIndex = INT_MAX;

// 	for(int i = lowBoundIndex; i < topBoundIndex; i++ )
// 	{
// 		Pair * currentDepotPair = (Pair *)localDepotCol->getFrogObject(i);
// 		Pair * customerPair = (Pair *) this->customerArray[customerIndex];
// 		int depotInternalId = currentDepotPair->getId();
// 		int customerInternalId = customerPair->getId();
// 		DistanceTable * dt = this->getDistanceTable();
// 		float currentDistance = dt->getEdge(depotInternalId, customerInternalId);

// 		if(this->distanceTypeMeasure == DistanceTypeCtrl::knapsack)
// 		{
// 			currentDistance = currentDistance / customerPair->get_i_IntValue();
// 		}
		
// 		if(currentDistance < closestDistance)
// 		{
// 			closestDistance = currentDistance;
// 			closestNodeIndex = i;
// 		}
// 	}

// 	distance = closestDistance;

// 	return closestNodeIndex;	
// }

// float FrogLeapController::genRandomFloatingNumber(float a, float b)
// {
// 	float randNumber = ((float)rand()) / (float)RAND_MAX;
// 	float diff = b - a;
	
// 	float result = a + diff*randNumber;
		 
// 	//this->writeRandomInfo(a, b, result);
		
// 	return result;
// }

// int FrogLeapController::genRandomIntNumber(int a, int b)
// {
// 	float randNumber = ((float)rand()) / (float)RAND_MAX;
// 	float diff = b - a;

// 	float result = a + diff*randNumber;

// 	//this->writeRandomInfo(a, b, result);

// 	int finalResult = floor(result);

// 	if (finalResult == b)
// 		finalResult--;

// 	return finalResult;
// }

// int FrogLeapController::getX_Coord(int nodeInternalId)
// {
// 	Pair * nodePair = (Pair *)this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(nodeInternalId);
	
// 	return nodePair->get_i_IntValue();
// }

// int FrogLeapController::getY_Coord(int nodeInternalId)
// {
// 	Pair * nodePair = (Pair *)this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(nodeInternalId);

// 	return nodePair->get_j_IntValue();
// }

// // create a list of customers that satisfies for each customer of the list that 
// // 1) the depotPair is the closest one of all.
// // The returned list is ordered by distance from the depotpair to all customers that satisfy condition 1)
// FrogObjectCol * FrogLeapController::createMatchCustomerList(Pair * currentDepotPair)
// {
// 	FrogObjectCol * matchCol = new FrogObjectCol();

// 	FrogObjectCol * distanceCustList = createCustomerListOrderedByDistanceFromDepot(currentDepotPair);

// 	int size = distanceCustList->getSize();

// 	for(int i = 0; i < size; i++)
// 	{
// 		Pair * currentCustomerPair = (Pair *)distanceCustList->getFrogObject(i);

// 		bool itIsAMatch = isAMatch(currentCustomerPair, currentDepotPair);

// 		if(itIsAMatch)
// 		{
// 			matchCol->addLastFrogObject(currentCustomerPair);
// 		}
// 	}

// 	distanceCustList->unReferenceFrogObjectCol();
// 	delete distanceCustList;

// 	return matchCol;
// }

// // create a list of customers that satisfies for each customer of the list that 
// // 1) the depotPair is the closest one of all.
// // The returned list is ordered by distance from the depotpair to all customers that satisfy condition 1)
// FrogObjectCol * FrogLeapController::createMatchCustomerList_Cluster(Cluster * currentCluster, FrogLeapSolution * fls)
// {
// 	FrogObjectCol * matchCol = new FrogObjectCol();

// 	Pair * currentDepotPair = currentCluster->getDepotPair();

// 	FrogObjectCol * distanceCustList = createCustomerListOrderedByDistanceFromCluster(currentCluster);

// 	int size = distanceCustList->getSize();

// 	for (int i = 0; i < size; i++)
// 	{
// 		Pair * currentCustomerPair = (Pair *)distanceCustList->getFrogObject(i);

// 		bool itIsAMatch = fls->isAMatch_Cluster(currentCustomerPair, currentCluster, this);

// 		if (itIsAMatch)
// 		{
// 			if (this->getCustomerListIndexByInternal(currentCustomerPair->getId()) == 19)
// 			{
// 				//printf("Stop in createMatchCustomerList: customer 19 found \n");
// 			}

// 			matchCol->addLastFrogObject(currentCustomerPair);
// 		}
// 	}

// 	distanceCustList->unReferenceFrogObjectCol();
// 	delete distanceCustList;

// 	return matchCol;
// }

// FrogObjectCol * FrogLeapController::createCustomerListOrderedByDistanceFromDepot(Pair * currentDepotPair)
// {
// 	FrogObjectCol * distanceCustomerList = new FrogObjectCol();

// 	int customerSetSize = this->getNumberOfCustomers();

// 	for(int i = 0; i < customerSetSize; i++)
// 	{
// 		Pair * customerPair = this->customerArray[i];

// 		int assignedDepotIndex = customerPair->getAssignedDepotIndex();

// 		if (assignedDepotIndex == -1)
// 		{
// 			int customerInternalId = customerPair->getId();			
// 			int currentDepotInternalId = currentDepotPair->getId();
// 			DistanceTable * dt = this->getDistanceTable();

// 			float currentDistance = dt->getEdge(currentDepotInternalId, customerInternalId);

// 			customerPair->setValue(currentDistance);

// 			distanceCustomerList->addFrogObjectOrdered(customerPair);
// 		}
// 	}

// 	return distanceCustomerList;
// }

// FrogObjectCol * FrogLeapController::createCustomerListOrderedByDistanceFromCluster(Cluster * currentCluster)
// {
// 	FrogObjectCol * distanceCustomerList = new FrogObjectCol();

// 	int customerSetSize = this->getNumberOfCustomers();

// 	for (int i = 0; i < customerSetSize; i++)
// 	{
// 		Pair * customerPair = this->getCustomerPairByIndex(i);
		
// 		if (customerPair->getAssignedDepotIndex() == -1)
// 		{
// 			float currentDistance = currentCluster->getDistanceToCustomer(i, this);

// 			customerPair->setValue(currentDistance);

// 			distanceCustomerList->addFrogObjectOrdered(customerPair);
// 		}
// 	}

// 	return distanceCustomerList;
// }

// FrogObjectCol * FrogLeapController::createDepotListOrderedByDistanceFromCustomer(Pair * currentCustomerPair)
// {
// 	FrogObjectCol * distanceDepotList = new FrogObjectCol();

// 	int depotSetSize = this->getNumberOfDepots();

// 	for (int i = 0; i < depotSetSize; i++)
// 	{
// 		Pair * depotPair = this->depotArray[i];

// 		int depotInternalId = depotPair->getId();
// 		int currentCustomerInternalId = currentCustomerPair->getId();

// 		DistanceTable * dt = this->getDistanceTable();

// 		float currentDistance = dt->getEdge(currentCustomerInternalId, depotInternalId);

// 		Pair * depotPairCopy = depotPair->createCopy();

// 		depotPairCopy->setValue(currentDistance);

// 		distanceDepotList->addFrogObjectOrdered(depotPairCopy);
// 	};

// 	return distanceDepotList;
// }

// bool FrogLeapController::isAMatch(Pair * currentCustomerPair, Pair * currentDepotPair)
// {
// 	bool result = false;
// 	FrogObjectCol * depotListOrdered = currentCustomerPair->getPairCol();

// 	if(depotListOrdered == nullptr)
// 	{
// 		depotListOrdered = this->createDepotListOrderedByDistanceFromCustomer(currentCustomerPair);
// 		currentCustomerPair->setPairCol(depotListOrdered);
// 	}
	
// 	Pair * closestDepotPair = (Pair *) depotListOrdered->getFrogObject(0);
		
// 	result = (currentDepotPair->getId() == closestDepotPair->getId());
// 	return result;
// }


// int FrogLeapController::getTotalDemandOrCapacity(FrogObjectCol * pairCol)
// {
// 	float result = 0;

// 	int size = pairCol->getSize();

// 	for (int i = 0; i < size; i++)
// 	{
// 		Pair * currentPair = (Pair *)pairCol->getFrogObject(i);
// 		result = result + currentPair->get_i_IntValue();
// 	}

// 	return result;
// }

// void FrogLeapController::assignDepotToCustomerPairs(Pair * depotPair, FrogObjectCol * customerCol)
// {
// 	int size = customerCol->getSize();
	
// 	for(int i = 0; i < size; i++)
// 	{
// 		Pair * customerPair = (Pair *) customerCol->getFrogObject(i);

// 		this->assignDepotToCustomer(depotPair, customerPair);

// 		depotPair->upDateRemainingCapacity(customerPair);		
// 	}
// }

// FrogObjectCol * FrogLeapController::assignDepotToCustomerPairsUntilDemandComplete(Pair * depotPair, FrogObjectCol * customerCol)
// {
// 	int size = customerCol->getSize();

// 	bool demandCompleted = false;
// 	int i = 0;
// 	FrogObjectCol * newCol = new FrogObjectCol();

// 	while (i < size && demandCompleted == false)
// 	{
		
// 		Pair * customerPair = (Pair *)customerCol->getFrogObject(0);

// 		int customerDemand = customerPair->get_i_IntValue();
// 		int currentDepotRemainingCapacity = depotPair->get_j_IntValue();

// 		if (currentDepotRemainingCapacity == 0)
// 		{
// 			demandCompleted = true;
// 		}
// 		else
// 		{
// 			if (customerDemand <= currentDepotRemainingCapacity)
// 			{
// 				depotPair->upDateRemainingCapacity(customerPair);
// 				this->assignDepotToCustomer(depotPair, customerPair);
// 				newCol->addLastFrogObject(customerPair);
// 			}
	
// 			customerCol->removeFrogObject(customerPair);
// 			i++;
// 		}		
// 	}

// 	customerCol->unReferenceFrogObjectCol();
// 	delete customerCol;

// 	return newCol;
// }

// FrogObjectCol * FrogLeapController::selectCustomerPairsUntilDemandComplete(Pair * depotPair, FrogObjectCol * customerCol)
// {
// 	int size = customerCol->getSize();

// 	bool demandCompleted = false;
// 	int i = 0;
// 	FrogObjectCol * newCol = new FrogObjectCol();

// 	//save depot remaining capacity
// 	int currentCapacity = depotPair->get_j_IntValue();

// 	while (i < size && demandCompleted == false)
// 	{

// 		Pair * customerPair = (Pair *)customerCol->getFrogObject(0);

// 		int customerDemand = customerPair->get_i_IntValue();
// 		int currentDepotRemainingCapacity = depotPair->get_j_IntValue();

// 		if (currentDepotRemainingCapacity == 0)
// 		{
// 			demandCompleted = true;
// 		}
// 		else
// 		{
// 			if (customerDemand <= currentDepotRemainingCapacity)
// 			{
// 				depotPair->upDateRemainingCapacity(customerPair);
// 				//this->assignDepotToCustomer(depotPair, customerPair);
// 				newCol->addLastFrogObject(customerPair);
// 			}

// 			customerCol->removeFrogObject(customerPair);
// 			i++;
// 		}
// 	}

// 	// restore capacity of depot
// 	depotPair->set_j_IntValue(currentCapacity);

// 	//this->resetCapacityOrDemand(depotPair);

// 	customerCol->unReferenceFrogObjectCol();
// 	delete customerCol;

// 	return newCol;
// }

// FrogObjectCol * FrogLeapController::selectCustomerPairsUntilDemandComplete_Cluster(Cluster * cluster, FrogObjectCol * customerCol)
// {
// 	int size = customerCol->getSize();

// 	bool demandCompleted = false;
// 	int i = 0;
// 	FrogObjectCol * newCol = new FrogObjectCol();
// 	Pair * depotPair = nullptr;

// 	while (i < size && demandCompleted == false)
// 	{

// 		Pair * customerPair = (Pair *)customerCol->getFrogObject(0);

// 		int customerDemand = customerPair->get_i_IntValue();
		
// 		depotPair = cluster->getDepotPair();

// 		int currentDepotRemainingCapacity = depotPair->get_j_IntValue();

// 		if (currentDepotRemainingCapacity == 0)
// 		{
// 			demandCompleted = true;
// 		}
// 		else
// 		{
// 			if (customerDemand <= currentDepotRemainingCapacity)
// 			{
// 				depotPair->upDateRemainingCapacity(customerPair);
// 				//this->assignDepotToCustomer(depotPair, customerPair);
// 				newCol->addLastFrogObject(customerPair);
// 			}

// 			customerCol->removeFrogObject(customerPair);
// 			i++;
// 		}
// 	}

// 	// reset capacity of depot
// 	this->resetCapacityOrDemand(depotPair);

// 	customerCol->unReferenceFrogObjectCol();
// 	delete customerCol;

// 	return newCol;
// }

// void FrogLeapController::assignCustomersToDepotOrNearCustomerDepot(FrogObjectCol * & customerCol, FrogObjectCol * depotListOrderedByCapacity, FrogLeapSolution * fs)
// {
// 	int size = customerCol->getSize();

// 	if(this->distanceTypeMeasure != DistanceTypeCtrl::knapsack)
// 	{
// 		for (int i = 0; i < size; i++)
// 		{
// 			int rand_int = this->genRandomIntNumber(0, customerCol->getSize());
// 			Pair * customerPair = (Pair *)customerCol->getFrogObject(rand_int);

// 			int customerIndex = this->getCustomerListIndexByInternal(customerPair->getId());

// 			if(customerIndex == 8)
// 			{
// 				printf("ojo...customerIndex 8 found \n");
// 			}

// 			//float u = fs->assignRandomFeasibleDepot4(this, depotListOrderedByCapacity, customerIndex);
// 			float u = this->assignRandomFeasibleDepot4(depotListOrderedByCapacity, customerIndex);
// 			fs->setFLValue(customerIndex, u);

// 			customerCol->removeFrogObject(customerPair);
// 		}
// 	}
// 	else
// 	{
// 		this->saveRemainingCapacityOfDepots();

// 		for (int i = 0; i < size; i++)
// 		{
// 			int rand_int = this->genRandomIntNumber(0, customerCol->getSize());
// 			Pair * customerPair = (Pair *)customerCol->getFrogObject(rand_int);

// 			int customerIndex = this->getCustomerListIndexByInternal(customerPair->getId());

// 			float u = this->colectRandomFeasibleDepot4(depotListOrderedByCapacity, customerIndex);

// 			customerCol->removeFrogObject(customerPair);
// 		}

// 		this->restoreRemainingCapacityOfDepots();

// 		for (int k = 0; k < size; k++)
// 		{
// 			Pair * customerPair = (Pair *)this->tempCustomerCol->getFrogObject(k);

// 			int customerIndex = this->getCustomerListIndexByInternal(customerPair->getId());

// 			//float u = fs->assignRandomFeasibleDepot4(this, depotListOrderedByCapacity, customerIndex);
// 			float u = this->assignRandomFeasibleDepot4(depotListOrderedByCapacity, customerIndex);
// 			fs->setFLValue(customerIndex, u);			
// 		}

// 		this->tempCustomerCol->unReferenceFrogObjectCol();
// 		delete this->tempCustomerCol;
// 		this->tempCustomerCol = nullptr;
// 	}
// }

// void FrogLeapController::assignCustomersToCluster(Cluster * cluster, FrogObjectCol * & customerCol, FrogLeapSolution * fls)
// {
// 	int size = customerCol->getSize();

// 	for (int i = 0; i < size; i++)
// 	{
// 		Pair * customerPair = (Pair *)customerCol->getFrogObject(0);
// 		Pair * depotPair = cluster->getDepotPair();

// 		if(this->getDepotListIndexByInternal(depotPair->getId()) == 8)
// 		{
// 			//printf("Stop: depot 8 found in assignCustomersToCluster \n");
// 		}

// 		int customerIndex = this->getCustomerListIndexByInternal(customerPair->getId());

// 		if(customerIndex == 8)
// 		{
// 			printf("Stop: customer 8 found in assignCustomersToCluster \n");
// 		}

// 		cluster->addCustomer(customerIndex, this);
				
// 		this->assignDepotToCustomer(depotPair, customerPair);

// 		depotPair->upDateRemainingCapacity(customerPair);

// 		int depotIndex = this->getDepotListIndexByInternal(depotPair->getId());

// 		float u = this->assignRandomToDepotSelected(depotIndex);
		
// 		fls->setFLValue(customerIndex, u);

// 		customerCol->removeFrogObject(customerPair);
// 	}
// }

// FrogObjectCol * FrogLeapController::orderCustomerPairListByNthClosestDepotDesc(int n, FrogObjectCol * customerPairCol)
// {
// 	int size = customerPairCol->getSize();
// 	Pair * customerPair = nullptr;
// 	FrogObjectCol * customerPairFrogObjectCol = nullptr;
// 	FrogObjectCol * newCol = new FrogObjectCol();
	
// 	for (int i = 0; i < size; i++)
// 	{
// 		customerPair = (Pair *)customerPairCol->getFrogObject(0);
// 		customerPairFrogObjectCol = customerPair->getPairCol();
// 		if(customerPairFrogObjectCol != nullptr)
// 		{
// 			Pair * localPair = (Pair *)customerPairFrogObjectCol->getFrogObject(n - 1);
// 			float nthFurthestDistance = localPair->getValue();
// 			customerPair->setValue(nthFurthestDistance);

// 			customerPairCol->removeFrogObject(customerPair);
// 			newCol->addFrogObjectDescOrdered(customerPair);
// 		}
// 		else {
// 			int result = -1;
// 		}
// 	}

// 	customerPairCol->unReferenceFrogObjectCol();
// 	delete customerPairCol;

// 	return newCol;
// }

// FrogObjectCol * FrogLeapController::orderCustomerPairListByNthClosestClusterDesc(int n, FrogObjectCol * customerPairCol)
// {
// 	int size = customerPairCol->getSize();
// 	Pair * customerPair = nullptr;
// 	FrogObjectCol * customerPairFrogObjectCol = nullptr;
// 	FrogObjectCol * newCol = new FrogObjectCol();

// 	for (int i = 0; i < size; i++)
// 	{
// 		customerPair = (Pair *)customerPairCol->getFrogObject(0);
// 		customerPairFrogObjectCol = customerPair->getClusterCol();
// 		if (customerPairFrogObjectCol != nullptr)
// 		{
// 			FrogObject * secondNearestCluster = customerPairFrogObjectCol->getFrogObject(n - 1);
// 			float nthFurthestDistance = secondNearestCluster->getValue();
// 			customerPair->setValue(nthFurthestDistance);

// 			customerPairCol->removeFrogObject(customerPair);
// 			newCol->addFrogObjectDescOrdered(customerPair);
// 		}
// 		else {
// 			int result = -1;
// 		}
// 	}

// 	customerPairCol->unReferenceFrogObjectCol();
// 	delete customerPairCol;

// 	return newCol;
// }

// void FrogLeapController::assignDepotToCustomer(Pair * depotPair, Pair * customerPair)
// {
// 	int depotIndex = this->getDepotListIndexByInternal(depotPair->getId());
// 	customerPair->setAssignedDepotIndex(depotIndex);
// }

// float FrogLeapController::addRandomNumberToInt(int index)
// {
// 	float result = 0;
// 	float randnum;

// 	do
// 	{
// 		randnum = this->genRandomFloatingNumber(0, 1);
// 	} while (randnum >= 1);

// 	result = index + randnum;

// 	return  result;	
// }

// bool FrogLeapController::isCustomerPairAssigned(Pair * customerPair)
// {
// 	if (customerPair->getAssignedDepotIndex() == -1)
// 		return false;
// 	else
// 		return true;
// }

// bool FrogLeapController::allCustomerPairAssigned()
// {
// 	for(int i = 0; i < this->getNumberOfCustomers(); i++)
// 	{
// 		Pair * customerPair = this->getCustomerPairByIndex(i);

// 		if (customerPair->getAssignedDepotIndex() == -1)
// 			return false;
// 	}

// 	return true;	
// }

// //void FrogLeapController::setEngine(std::default_random_engine * generator)
// //{
// //	this->engine = generator;
// //}

// //std::default_random_engine * FrogLeapController::getEngine()
// //{
// //	return this->engine;
// //}

// void FrogLeapController::openOutPutFile()
// {
// 	outPutFileName = "outPutFL.txt";
// 	pFile = fopen(outPutFileName, "w");

// 	if(pFile != nullptr)
// 	{
// 		fputs("MDVRP ALGORITHM OUTPUT \n", pFile);
// 	}
// }

// void FrogLeapController::closeOutPutFile()
// {
// 	fclose(this->pFile);
// }

// FILE * FrogLeapController::getPFile()
// {
// 	return this->pFile;
// }

// char * FrogLeapController::getTestCaseName()
// {
// 	return this->tspLibEud2DPtr->getName();	
// }

// char * FrogLeapController::getTestCaseComment()
// {
// 	return this->tspLibEud2DPtr->getComment();
// }

// int FrogLeapController::getTestCaseDimension()
// {
// 	return this->tspLibEud2DPtr->getDimension();
// }

// char * FrogLeapController::getTestCaseType()
// {
// 	return this->tspLibEud2DPtr->getType();
// }

// int FrogLeapController::getTestCaseCapacity()
// {
// 	return this->tspLibEud2DPtr->getCapacity();
// }

// void FrogLeapController::writeBestAndCurrentSolutionsAndTime()
// {
// 	if(this->solutionMode == SolutionMode::Global)
// 	{
// 		printf("\n Global Sol - ");
// 	}
// 	else
// 	{
// 		printf("\n Local Sol - ");
// 	}
// 	printf("Iteration Number i = %lld MinCostValue = %.3f solExecTime = %.3lld CurrentValue = %.3f CurrentTime = %.3lld \n", this->getIterations(), this->getMinCostValue(), this->getExecTime(), this->getCurrentCostValue(), this->getExecTime());

// }

// void FrogLeapController::writeSeed()
// {
// 	char buffer[256] = { 0 };

// 	sprintf(buffer, "SEED USED: ; %lld \n", this->timeSeedUsed);

// 	fputs(buffer, this->pFile);
// }

// void FrogLeapController::writeFrogLeapSolution(FrogLeapSolution * fls)
// { 
// 	//fputs("FrogLeapSolution \n", this->pFile);
	
// 	fputs("FLS Customer Index: ;", this->pFile);

// 	for(int i = 0; i < fls->getSize(); i++)
// 	{
// 		fprintf(this->pFile, "%d ; ", i);
// 	}

// 	fprintf(this->pFile, "\n");

// 	fputs("FLS Depot Index: ;", this->pFile);

// 	for (int i = 0; i < fls->getSize(); i++)
// 	{
// 		fprintf(this->pFile, "%.3f ;", fls->getFLValue(i));
// 	}

// 	fprintf(this->pFile, "\n");
// }



// void FrogLeapController::writeIterationInfo(long long int i, float currentValue)
// {
// 	char buffer[300] = { 0 };

// 	printf("\n\n\n Iteration Number i = %lld ; MinCostValue = %.3f ; CurrentCostValue = %.3f \n\n\n", i, this->getMinCostValue(), currentValue);
// 	sprintf(buffer, "Iteration Number i = ; %lld ; MinCostValue = ; %.3f ; CurrentCostValue = ; %.3f \n", i, this->getMinCostValue(), currentValue);
// 	fputs(buffer, this->pFile);	
// }

// void FrogLeapController::writeRandomInfo(float a, float b, float finalRandom)
// {
// 	char buffer[300] = { 0 };

// 	printf("Random Info a = %.3f b = %.3f finalRandom = %.3f \n", a, b, finalRandom);
// 	sprintf(buffer, "Random Info a = ; %.3f ; b = ; %.3f m = ; %.3f finalRandom = ; %.3f \n", a, b, finalRandom);
// 	fputs(buffer, this->pFile);
// }

// void FrogLeapController::writeExecutionInfo()
// {
// 	char buffer[300] = { 0 };

// 	sprintf(buffer, "\n \n SHOWING DATA OF FROGLEAPING CONTROLLER \n");
// 	buffer[300] = { 0 };
// 	fputs(buffer, this->pFile);

// 	if (this->ptrBestSolution != nullptr)
// 	{
// 		this->ptrBestSolution->printFrogObj();
// 	}
// 	else
// 	{
// 		sprintf(buffer,"\n NO FEASIBLE SOLUTION FOUND: ptrBestSolution IS nullptr \n");
// 		buffer[300] = { 0 };
// 	}

// 	sprintf(buffer, "\n Summary of Best Found Solution \n");
// 	buffer[300] = { 0 };
// 	fputs(buffer, this->pFile);
// 	sprintf(buffer, "	Time Seed used %lld \n", (long long)this->timeSeedUsed);
// 	buffer[300] = { 0 };
// 	fputs(buffer, this->pFile);
// 	sprintf(buffer, "	Number of success attempts: %d \n", this->successAttempts);
// 	buffer[300] = { 0 };
// 	fputs(buffer, this->pFile);
// 	sprintf(buffer, "	Number of fail attempts: %d \n", this->failAttempts);
// 	buffer[300] = { 0 };
// 	fputs(buffer, this->pFile);
// 	sprintf(buffer, "	Number of TOTAL Improvements: %d \n", this->getTotalImprovements());
// 	buffer[300] = { 0 };
// 	fputs(buffer, this->pFile);
// 	sprintf(buffer, "	Number of Global Search Improvements: %d \n", this->globalImprovements);
// 	buffer[300] = { 0 };
// 	fputs(buffer, this->pFile);
// 	sprintf(buffer, "	Number of Local Search Improvements: %d \n", this->localSearchImprovements);
// 	buffer[300] = { 0 };
// 	fputs(buffer, this->pFile);
// 	sprintf(buffer, "	Evaluation of best found solution is: %.3f \n \n", this->getMinCostValue());
// 	buffer[300] = { 0 };
// 	fputs(buffer, this->pFile);
// }

// //choose the closest item: available depot or the depot of the closest assigned customer
// float FrogLeapController::assignRandomFeasibleDepot4(FrogObjectCol * & localDepotCol, int customerIndex)
// {
// 	float u = -1, result = -1;
// 	Pair * depotPairSelected = nullptr, * customerPair = nullptr;
// 	int lowBoundIndex = -1;

// 	// get the customer demand
// 	int customerDemand = this->getCustomerDemandByIndex(customerIndex);

// 	if (this->distanceTypeMeasure == DistanceTypeCtrl::knapsack)
// 	{
// 		customerPair = this->getCustomerPairByIndex(customerIndex);
// 	}

// 	// get the index of the first depot with capacity enough to attend customer demand
// 	localDepotCol->getFirstHigherValueFrogObjectIndex(customerDemand, lowBoundIndex);

// 	// if there is not any depot then return -1
// 	if (lowBoundIndex == -1)
// 	{
// 		return result;
// 	}

// 	// choose between the available depots with suffiecient capacity to attend the customer demand
// 	int numberOfDepots = this->getNumberOfDepots();

// 	float distanceToDepot;
// 	int positionSelected = this->getClosestLocalDepotIndexToCustomer(customerIndex, lowBoundIndex, localDepotCol->getSize(), localDepotCol, distanceToDepot);

// 	float distanceToDepotCustomer;

// 	// get the depot index of the closest already assigned customer. Capacity of depot is checked
// 	int closestCustomerDepotIndex = this->getDepotIndexOfClosestAssignedCustomer(customerIndex, localDepotCol, lowBoundIndex, localDepotCol->getSize(), distanceToDepotCustomer);

// 	if (closestCustomerDepotIndex != -1)
// 	{
// 		if (distanceToDepotCustomer < distanceToDepot)
// 		{
// 			depotPairSelected = this->getDepotPairByIndex(closestCustomerDepotIndex);
// 		}
// 		else
// 		{
// 			// get the depotPair selected in the list of available depots
// 			depotPairSelected = (Pair *)localDepotCol->getFrogObject(positionSelected);
// 		}
// 	}
// 	else
// 	{
// 		// get the depotPair selected in the list of available depots
// 		depotPairSelected = (Pair *)localDepotCol->getFrogObject(positionSelected);
// 	}

// 	//update remaining capacity of depot pair
// 	int depotRemainingCap = depotPairSelected->get_j_IntValue();
// 	int newCapacity = depotRemainingCap - customerDemand;
// 	depotPairSelected->set_j_IntValue(newCapacity);
// 	depotPairSelected->setValue(newCapacity);

// 	localDepotCol->reorderFrogObject(depotPairSelected);

// 	// get the depot index in the controller of the selected depot
// 	int depotId = depotPairSelected->getId();
// 	int depotIndex = this->getDepotListIndexByInternal(depotId);

// 	this->setCustomerPairAsAssigned(customerIndex, depotIndex);

// 	// assign a random number to the depot selected
// 	result = this->assignRandomToDepotSelected(depotIndex);

// 	return  result;
// }

// int FrogLeapController::colectRandomFeasibleDepot4(FrogObjectCol *& localDepotCol, int customerIndex)
// {
// 	float u = -1, result = -1;
// 	Pair * depotPairSelected = nullptr, *customerPair = nullptr;
// 	int lowBoundIndex = -1;

// 	// get the customer demand
// 	int customerDemand = this->getCustomerDemandByIndex(customerIndex);

// 	customerPair = this->getCustomerPairByIndex(customerIndex);

// 	// get the index of the first depot with capacity enough to attend customer demand
// 	localDepotCol->getFirstHigherValueFrogObjectIndex(customerDemand, lowBoundIndex);

// 	// if there is not any depot then return -1
// 	if (lowBoundIndex == -1)
// 	{
// 		return result;
// 	}

// 	// choose between the available depots with suffiecient capacity to attend the customer demand
// 	int numberOfDepots = this->getNumberOfDepots();

// 	float distanceToDepot;
// 	int positionSelected = this->getClosestLocalDepotIndexToCustomer(customerIndex, lowBoundIndex, localDepotCol->getSize(), localDepotCol, distanceToDepot);

// 	float distanceToDepotCustomer;

// 	// get the depot index of the closest already assigned customer. Capacity of depot is checked
// 	int closestCustomerDepotIndex = this->getDepotIndexOfClosestAssignedCustomer(customerIndex, localDepotCol, lowBoundIndex, localDepotCol->getSize(), distanceToDepotCustomer);

// 	if (closestCustomerDepotIndex != -1)
// 	{
// 		if (distanceToDepotCustomer < distanceToDepot)
// 		{
// 			depotPairSelected = this->getDepotPairByIndex(closestCustomerDepotIndex);
// 			customerPair->setValue(distanceToDepotCustomer);			
// 		}
// 		else
// 		{
// 			// get the depotPair selected in the list of available depots
// 			depotPairSelected = (Pair *)localDepotCol->getFrogObject(positionSelected);

// 			customerPair->setValue(distanceToDepot);
// 		}
// 	}
// 	else
// 	{
// 		// get the depotPair selected in the list of available depots
// 		depotPairSelected = (Pair *)localDepotCol->getFrogObject(positionSelected);

// 		customerPair->setValue(distanceToDepot / customerDemand);		
// 	}

// 	//update remaining capacity of depot pair
// 	int depotRemainingCap = depotPairSelected->get_j_IntValue();
// 	int newCapacity = depotRemainingCap - customerDemand;
// 	depotPairSelected->set_j_IntValue(newCapacity);
// 	depotPairSelected->setValue(newCapacity);

// 	localDepotCol->reorderFrogObject(depotPairSelected);

// 	// get the depot index in the controller of the selected depot
// 	int depotId = depotPairSelected->getId();
// 	int depotIndex = this->getDepotListIndexByInternal(depotId);

// 	this->setCustomerPairAsAssigned(customerIndex, depotIndex);

// 	// assign a random number to the depot selected
// 	result = this->assignRandomToDepotSelected(depotIndex);

// 	if (this->tempCustomerCol == nullptr)
// 	{
// 		this->tempCustomerCol = new FrogObjectCol();
// 	}

// 	this->tempCustomerCol->addFrogObjectOrdered(customerPair);	

// 	return  result;
// }

// int FrogLeapController::getNumberOfUnassignedCustomers()
// {
// 	int unassignedCustomerCount = 0;

// 	for (int i = 0; i < this->getNumberOfCustomers(); i++)
// 	{
// 		Pair * currCustomerPair = this->getCustomerPairByIndex(i);
// 		if(currCustomerPair->getAssignedDepotIndex() == -1)		
// 		{
// 			unassignedCustomerCount++;
// 		}
// 	}

// 	return unassignedCustomerCount;
// }

// void FrogLeapController::initCheckFLS_for_depots()
// {
// 	for(int i = 0; i < this->getNumberOfDepots(); i++)
// 	{
// 		Pair * depotPair = this->getDepotPairByIndex(i);
// 		depotPair->set_j_FloatValue(0);
// 	}
// }

// bool FrogLeapController::checkFLS(FrogLeapSolution * fls, int & v_customerIndex, int & v_depotIndex, float & capacity, float & cumDemand)
// {	
// 	int size = fls->getSize();

// 	this->initCheckFLS_for_depots();

// 	for (int i = 0; i < size; i++) 
// 	{
// 		if (this->checkFLS_i(fls, i, v_depotIndex, capacity, cumDemand) == false)
// 		{
// 			v_customerIndex = i;
// 			return false;
// 		}
// 	}

// 	return true;
// }

// bool FrogLeapController::checkFLS_i(FrogLeapSolution * fls, int customerIndex, int & v_depotIndex, float & capacity, float & cumDemand)
// {
	
// 	int customerDemand = this->getCustomerDemandByIndex(customerIndex);
// 	int depotIndex = floor(fls->getFLValue(customerIndex));
// 	Pair * depotPair = this->getDepotPairByIndex(depotIndex);
// 	float currentCumulativeDemand = depotPair->get_j_FloatValue();
// 	currentCumulativeDemand += customerDemand;
// 	depotPair->set_j_FloatValue(currentCumulativeDemand);

// 	v_depotIndex = depotIndex;
// 	capacity = depotPair->get_i_IntValue();
// 	cumDemand = currentCumulativeDemand;

// 	if (currentCumulativeDemand > depotPair->get_i_IntValue())
// 	{
// 		return false;
// 	}

// 	return true;
// }

// void FrogLeapController::applyLocalDepotOrderSearch()
// {
// 	bool exitLocalSearch = false;
// 	bool improvementFound = false;

// 	// until we do not find any better solution we continue applying local search to each improvement solution found.
// 	while (!exitLocalSearch)
// 	{
// 		// we look for 100 local solutions. If we find an improvement then generateLocalSolutionsAndEvaluate = true to keep in the loop
// 		// and execute a new local search for new solutions from the last solution found
// 		improvementFound = generateLocalDepotSolutionsAndEvaluate();
// 		//improvementFound = generateLocalSolutionsAndEvaluate(controller);
// 		if (improvementFound == false)
// 		{
// 			exitLocalSearch = true;
// 		}
// 	}
// }

// void FrogLeapController::deleteDepotFeasibleSolution()
// {
// 	if (this->currentDepotFeasibleSolution != nullptr && this->currentDepotFeasibleSolution != this->ptrBestDepotFeasibleSolution)
// 	{
// 		delete this->currentDepotFeasibleSolution;
// 		this->currentDepotFeasibleSolution = nullptr;
// 	}
// }

// void FrogLeapController::setDepotFeasibleSolution(FeasibleSolution * v_fs)
// {
// 	if(this->ptrBestDepotFeasibleSolution != this->currentDepotFeasibleSolution)
// 	{
// 		delete this->currentDepotFeasibleSolution;
// 	}

// 	this->currentDepotFeasibleSolution = v_fs;
// }

// bool FrogLeapController::generateLocalDepotSolutionsAndEvaluate()
// {
// 	FeasibleSolution * fs = new FeasibleSolution(this->ptrBestDepotFeasibleSolution);

// 	// generate a one distance permutation solutions, evaluate each one and stop when there is an improvement 
// 	// and update the best solution in the vehicle or stop when 100 different solutions where evaluated without any udpate.
// 	bool improvement = fs->searchOneSwapDepotFeasibleSolutionsAndEval(this);

// 	delete fs;

// 	return improvement;
// }

// // assign a random number to the depot selected
// float FrogLeapController::assignRandomToDepotSelected(int depotIndex)
// {
// 	float randnum, result;

// 	do
// 	{
// 		randnum = this->genRandomFloatingNumber(0, 1);
// 	} while (randnum >= 1);

// 	result = depotIndex + randnum;

// 	return  result;
// }

// time_t FrogLeapController::getSeedUsed()
// {
// 	return this->timeSeedUsed;
// }

// void FrogLeapController::start_Timer()
// {
// 	start_time = std::chrono::system_clock::now();
// 	end_time = std::chrono::system_clock::now();
// 	auto time = end_time - start_time;
// 	execTime = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
// }

// void FrogLeapController::take_Execution_Time()
// {
// 	end_time = std::chrono::system_clock::now();
// 	auto time = end_time - start_time;
// 	execTime = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
// }

// long long int FrogLeapController::get_Execution_Time()
// {
// 	return this->execTime;
// }

// void FrogLeapController::set_BestSolution_ExecutionTime(long long int bestSolutionExecutionTime)
// {
// 	this->bestSol_ExecTime = bestSolutionExecutionTime;
// }

// DistanceTypeCtrl FrogLeapController::getDistanceTypeCtrl()
// {
// 	return this->distanceTypeMeasure;
// }

// Pair * FrogLeapController::getTempCustomerItem(int position)
// {
// 	return (Pair *)this->tempCustomerCol->getFrogObject(position);
// }

// void FrogLeapController::saveRemainingCapacityOfDepot(int depotIndex)
// {
// 	Pair * depotPair = this->getDepotPairByIndex(depotIndex);

// 	depotPair->set_k_IntValue(depotPair->get_j_IntValue());
// }

// void FrogLeapController::saveRemainingCapacityOfDepots()
// {
// 	for(int i = 0; i < this->getNumberOfDepots(); i++)
// 	{
// 		this->saveRemainingCapacityOfDepot(i);
// 	}
// }

// void FrogLeapController::restoreRemainingCapacityOfDepot(int depotIndex)
// {
// 	Pair * depotPair = this->getDepotPairByIndex(depotIndex);

// 	depotPair->set_j_IntValue(depotPair->get_k_IntValue());
// }

// void FrogLeapController::restoreRemainingCapacityOfDepots()
// {
// 	for (int i = 0; i < this->getNumberOfDepots(); i++)
// 	{
// 		this->restoreRemainingCapacityOfDepot(i);
// 	}
//}


