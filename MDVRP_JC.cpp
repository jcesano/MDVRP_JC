// MDVRP_JC.cpp : Defines the entry point for the console application.
// To setup files to make this project able to debug use the following links:
// https://stackoverflow.com/questions/47872250/cant-compile-code-launch-program-program-path-does-not-exist
// https://github.com/manoharreddyporeddy/programming-language-notes/tree/master/vscode-c%2B%2B/myproj

//#include "stdafx.h"

// #include "FrogLeapSolution.h"
// #include "DecodedFrogLeapSolution.h"
//#include "FrogObjectCol.h"
//#include "IndexList.h"
// #include "FeasibleSolution.h"
//#include "DistanceTable.h"
#include "Graph.h"
#include "FrogLeapController.h"
// #include "FeasibleSolCol.h"
// #include "DistanceTable.h"

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <chrono>
#include <string>
#include <random>
#include <utility>

//using std::string;

using namespace std;

// void setDepot(FrogLeapController *controller, Graph * g, int vertIdLabel, int capacity)
// {
// 	int vertexIndex = g->getPositionVertexById(vertIdLabel);

// 	if (vertexIndex != -1)
// 	{
// 		controller->setAsDepot(vertexIndex, capacity);
// 	}
// }

// void setCustomer(FrogLeapController *controller, Graph * g, int vertIdLabel, int capacity)
// {
// 	int vertexIndex = g->getPositionVertexById(vertIdLabel);

// 	if (vertexIndex != -1)
// 	{
// 		controller->setAsCustomer(vertexIndex, capacity);
// 	}
// }


int main()
{
	// create the graph given in above figure 

	int V = 9;

	FrogLeapController * controller = new FrogLeapController();

	int totalImps = controller->getTotalImprovements();

	cout << "Showing total improvements: " << totalImps << endl;

	char * fileName = (char *)"casog01.vrp";

	cout << "Showing fileName: " << fileName << endl; 

	char *testCaseFileName = (char *)"TestCase01Casog01 - copia.txt";

	cout << "Showing testCaseFileName: " << testCaseFileName << endl; 

	controller->setSourceType(SourceType::Tsp2DEuc);

	// DecodedFrogLeapSolution * dfls_1 = NULL;

	Graph * g = new Graph(V);

	if (controller->getSourceType() == SourceType::Graph)
	{
		g->addEdge(0, 1, 4);
		g->addEdge(0, 7, 8);
		g->addEdge(1, 2, 8);
		g->addEdge(1, 7, 11);
		g->addEdge(2, 3, 7);
		g->addEdge(2, 8, 2);
		g->addEdge(2, 5, 4);
		g->addEdge(3, 4, 9);
		g->addEdge(3, 5, 14);
		g->addEdge(4, 5, 10);
		g->addEdge(5, 6, 2);
		g->addEdge(6, 7, 1);
		g->addEdge(6, 8, 6);
		g->addEdge(7, 8, 7);

		int vertexIndex = g->getPositionVertexById(0);

		cout << "Showing vertexIndex: " << vertexIndex << endl;

		// DistVect * dv = NULL;

		// 	if (vertexIndex != -1)
		// 	{
		// 		dv = g->dijkstra(vertexIndex);
		// 	}

		// 	/* main to test Dijkstra algorithm */

		// 	setDepot(controller, g, 0, 12);
		// 	setDepot(controller, g, 6, 14);

		// 	setCustomer(controller, g, 1, 3);
		// 	setCustomer(controller, g, 2, 3);
		// 	setCustomer(controller, g, 3, 3);
		// 	setCustomer(controller, g, 4, 3);
		// 	setCustomer(controller, g, 7, 3);
		// 	setCustomer(controller, g, 8, 3);

		// 	/* main to fill the Distance Table */
		// 	DistanceTable * dt = new DistanceTable(V);

		// 	dt->fillDistanceTable(dv, g);

		// 	dt->printDistanceTable();

		// 	g->setDistanceTable(dt);

		// 	controller->setGraph(g);

		// 	controller->setDistanceTable(dt);

		// 	dt = NULL;

		// 	controller->setUpCustomerAndDepotLists();
	}
	else
	{
		controller->loadTSPEUC2D_Data(fileName);
		controller->setUpCustomerAndDepotLists();
		controller->setUpVehicleCapacity();
		controller->loadDistanceTable();		
	}

		//controller->setUpVehiclesPerDepot();	

		/* Main to test all permutations of distance = 1 and distance = 2

		FeasibleSolution * fs;
		FeasibleSolCol * fscol;

		fs = new FeasibleSolution(V);
		*/

		/* setting indexes as values in the FeasibleSolution
		for(int i = 0; i<V;i++)
		{
		fs->setSolFactValue(i, i);
		}

		int distance;
		distance = 1;
		fscol = fs->genPermutations(distance,NULL, controller);
		fscol->printFeasSolCol();
		*/

		/* main to test random vector (FeasibleSolution)
		fs = new FeasibleSolution(V);

		fs->setRandomSolution();

		fs->printFeasibleSolution();
		*/

		/* main to test the random solution generator
		//FeasibleSolution * fs = new FeasibleSolution(V);
		fs->setRandomSolution();
		fscol = fs->genRandomFeasibleSolCol();

		fscol->printFeasSolCol();
		*/


		/* main test frogSolution */

		// DistanceTable * dt = controller->getDistanceTable();

		// //printf("Testing distance table: dt[%d, %d] = %f", 260, 54, dt[260, 54]);

		// int nDepots = controller->getNumberOfDepots();
		// int nCustomers = controller->getNumberOfCustomers();

	// 	FrogLeapSolution * fls = new FrogLeapSolution(SolutionGenerationType::FrogLeaping, controller->getSourceType(), nCustomers, nDepots, 0);

	// 	dfls_1 = NULL;
	// 	float evalSol;
	// 	const long long int itNumber = controller->getNumberOfIterations();
	// 	long long int i = 0;
	// 	long long int timeBound, execTime;
	// 	timeBound = 10800000;

	// 	//std::chrono::high_resolution_clock::now();
	// 	bool isFeasibleFLS = false;

	// 	printf("Program execution started ... \n");
	// 	controller->start_Timer();
	// 	controller->openOutPutFile();
	// 	//controller->writeSeed();
	// 	int counterAux = 0;
	// 	bool testMode = false;
		
	// 	int v_depotIndex, v_customerIndex;
	// 	float capacity = -1, cumDemand = -1;

	// 	controller->resetIterations();

	// 	//while(execTime <= timeBound)
	// 	while (counterAux < 10000000)	//while(true)
	// 	{		
	// 		//controller->writeFrogLeapSolution(fls);

	// 		//fls->printFrogObj();

	// 		if (testMode == false)
	// 		{
	// 			isFeasibleFLS = fls->genRandomSolution8(controller);  
	// 			bool isFeasibleFLS2 = controller->checkFLS(fls,v_customerIndex, v_depotIndex, capacity, cumDemand);
				
	// 			if(isFeasibleFLS2 == false)
	// 			{
	// 				printf("stop");
	// 			}

	// //			fls->writeFrogLeapSolution(controller);
	// //			controller->closeOutPutFile();

	// 			if (isFeasibleFLS == true)
	// 			{				
	// 				dfls_1 = fls->decodeFrogLeapSolutionWithAngularSplitAndClosestNextCriteria(controller);

	// 				//dfls_1 = fls->decodeFrogLeapWholeSolutionWithAngularCriteria(controller);

	// 				if (dfls_1->getIsFeasibleSolution() == true)
	// 				{
	// 					controller->incSuccessAttempts();
	// 					evalSol = dfls_1->evalSolution();
	// 					controller->setCurrentCostValue(evalSol);					

	// 					if (evalSol < controller->getMinCostValue())
	// 					{
	// 						printf("NEW SOLUTION FOUND \n");
							
	// 						controller->setUpGlobalSolution(dfls_1, evalSol);

	// 						controller->openOutPutFile();
	// 						fls->writeFrogLeapSolution(controller);
	// 						//dfls_1->writeDecodedFrogLeapSolution(controller);					
	// 						//dfls_1->writeDecodedFrogLeapSolutionWithCoordinates(controller);
	// 						controller->closeOutPutFile();

	// 						//apply local search
	// 						//controller->applyLocalDepotOrderSearch();
	// 						//controller->applyLocalSearch();					
	// 						controller->printCtrl();
	// 					}
	// 					else
	// 					{
	// 						controller->applyLocalSearch();					
	// 						//dfls_1->printFrogObj();
	// 						controller->deleteDepotFeasibleSolution();
	// 						delete dfls_1;
	// 					}
	// 				}
	// 				else
	// 				{
	// 					evalSol = -1;
	// 					//dfls_1->printFrogObj();
	// 					controller->incFailAttempts();
	// 					controller->deleteDepotFeasibleSolution();
	// 					delete dfls_1;
	// 				}

	// 				controller->writeBestAndCurrentSolutionsAndTime();			
	// 			}			
	// 		}
	// 		else
	// 		{
	// 			dfls_1 = controller->loadTestCaseData(testCaseFileName);

	// 			if (dfls_1->getIsFeasibleSolution() == true)
	// 			{
	// 				evalSol = dfls_1->evalSolution();
	// 				//dfls_1->writeDecodedFrogLeapSolution(controller);
	// 				//dfls_1->writeDecodedFrogLeapSolutionWithCoordinates(controller);
	// 				if (evalSol < controller->getMinCostValue())
	// 				{
	// 					//printf("New solution found \n");
	// 					controller->setUpGlobalSolution(dfls_1, evalSol);

	// 					controller->writeBestAndCurrentSolutionsAndTime();
						
	// 					//apply local search
	// 					//controller->applyLocalSearch();					
	// 					controller->printCtrl();
	// 				}
	// 					//dfls_1->printFrogObj();
	// 					delete dfls_1;
	// 			}
	// 		}

	// 		controller->take_Execution_Time();
	// 		controller->incIterations();
	// 		controller->deleteDepotFeasibleSolution();
	// 		//controller->writeIterationInfo(i, evalSol);		
	// 		i++;

	// 		counterAux++;
	// 	}

	// 	printf("TOTAL ITERATION NUMBER %lld", i);

	// 	DecodedFrogLeapSolution * bestSolution = controller->getBestDecodedFrogLeapSolution();
	// 	//bestSolution->writeDecodedFrogLeapSolution(controller);
	// 	//bestSolution->writeDecodedFrogLeapSolutionWithCoordinates(controller);

	// 	//controller->printCtrl();
	// 	controller->closeOutPutFile();

	// 	//delete g;
	// 	delete fls;
	// 	delete controller;

	// 	controller->take_Execution_Time();	

	// 	std::cout << "FrogLeaping took " <<
 // 		controller->get_Execution_Time() << " to run.\n";

	cout << "Muestro Graph: " << g->getVertexCount() << endl;
	cout << "7: A este proyecto le voy a romper el orto vamo y vamo " << "SHOWING V: " << V << endl;

	return 0;
}


