#ifndef FROGLEAPCONTROLLER_H_   /* Include guard */
#define FROGLEAPCONTROLLER_H_

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>

class DecodedFrogLeapSolution;
class FeasibleSolution;
class FrogObject;
class FrogObjectCol;
class TspLibEuc2D;
class TestCaseObj;
class DistanceTable;
class FloatDistanceTable;
class Graph;
class FrogLeapSolution;
class Pair;
class IndexList;
class Cluster;

enum class SourceType { Graph, Tsp2DEuc};

enum class SolutionGenerationType { FrogLeaping, FixedFrogLeaping};

enum class SolutionMode {Global, LocalSearch};

enum class DistanceTypeCtrl { mean, nearest, furthest, knapsack };

const int VEHICLE_CAPACITY = 500;
const long int TOPE_ITERATIONS = 10000;


class FrogLeapController
{
	private:

		int line_max_value;

		FrogObjectCol * tempCustomerCol;

		DistanceTypeCtrl distanceTypeMeasure;

		// SolutionMode solutionMode;
		long int successAttempts;
		long int failAttempts;
		// long int localGeneratedSolutions;

		long int totalImprovements;
		long int localSearchImprovements;
		long int globalImprovements;
		long int vehicle_capacity;

		long long int globalVehicleId;

		// long long int execTime;		

		// long long int iterations;

		// long long int bestSol_ExecTime;

		std::chrono::time_point<std::chrono::system_clock> end_time; 
		std::chrono::time_point<std::chrono::system_clock> start_time;

		float minCostValue;

		// float currentCostValue;

		time_t timeSeedUsed;

		// DecodedFrogLeapSolution * ptrBestSolution;

		// FeasibleSolution * ptrBestDepotFeasibleSolution;

		// FeasibleSolution * currentDepotFeasibleSolution;

		TspLibEuc2D * tspLibEud2DPtr;

		TestCaseObj * testCaseObjPtr;

		DistanceTable * distTablePtr;
		// FloatDistanceTable * floatDistTablePtr;

		// Graph * graphPtr;

		SourceType source_t;

		// SolutionGenerationType sgt;

		FrogObjectCol * customerList;

		FrogObjectCol * depotList;

		// FrogObjectCol * vehiclePairList;		

		// Pair * * vehiclePairArray;

		Pair * * customerArray;

		Pair * * depotArray;

		// int origin;

		// int nVehiclesPerDepot;

		// FILE * pFile;
		
		// char * outPutFileName;		

	public:

		FrogLeapController();

		~FrogLeapController();

		// void unreferenceArray(Pair ** arrayPtr, int v_size);		

		// void setSuccessAttempts(int vsuccessAttempts);
		// int getSuccessAttempts();
		// void incSuccessAttempts();

		// void setFailAttempts(int vfailAttempts);
		// int getFailAttempts();
		// void incFailAttempts();

		int getTotalImprovements();
		void incTotalImprovements();

		// int getLocalSearchImprovements();
		// void incLocalSearchImprovements();

		// int getGlobalSearchImprovements();
		// void incGlobalSearchImprovements();

		// int getLocalGeneratedSolutions();
		// void incLocalGeneratedSolutions();
		
		// void setLocaImprovement();

		// void setGlobalImprovement();

		// long int getNumberOfIterations();

		// float getMinCostValue();

		// void setMinCostValue(float cost);

		// float getCurrentCostValue();

		// void setCurrentCostValue(float cost);

		// long long int getExecTime();

		// long long int getIterations();

		// void incIterations();

		// void resetIterations();

		// void setExecTime(long long int execTime);

		// void setBestDecodedFrogLeapSolution(DecodedFrogLeapSolution * ptrSolution);

		// void setUpLocalSolution(DecodedFrogLeapSolution * dfls, float eval);

		// void setUpGlobalSolution(DecodedFrogLeapSolution * dfls, float eval);

		// DecodedFrogLeapSolution * getBestDecodedFrogLeapSolution();

		// void setRandomSeed();

		// void applyLocalSearch();

		// void printCtrl();

		void loadTSPEUC2D_Data(char * fileName);

		// DecodedFrogLeapSolution * loadTestCaseData(char * fileName);

		// void readTSPSection(FILE * filePtr, char * ctrlSectionTag, char * ctrlSeparatorChar, int * off_set);

		// void loadTSPSection(char * buf, char * sectionTag);

		// void loadAssignations(FILE * filePtr, TestCaseObj * testCaseObjPtr);

		// DecodedFrogLeapSolution * loadAssignations2(FILE * filePtr, TestCaseObj * testCaseObjPtr);

		// FrogLeapSolution * loadAssignations3(FILE * filePtr, TestCaseObj * testCaseObjPtr);

		void loadCoordinates(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr);
		
		void loadDemand(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr);

		void loadDepots(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr);

		DistanceTable * loadDistanceTable();

		// void setDistanceTable(DistanceTable * t);

		// DistanceTable * getDistanceTable();

		// void setFloatDistanceTable(FloatDistanceTable * t);

		// FloatDistanceTable * getFloatDistanceTable();

		int getNumberOfDepots();

		int getNumberOfCustomers();

		// Pair * getDepotPairByIndex(int position);

		// Pair * getDepotPairByInternal(int position);

		// Pair * getCustomerPairByInternal(int position);

		// Pair * getCustomerPairByIndex(int position);

		// Pair * getPairByInternalId(int position);

		// void setAngularValues(Pair * veh_customerPair, int customerInternalId, int depotInternalId);		

		// void setGraph(Graph * gPtr);

		// Graph * getGraph();

		void setSourceType(SourceType sourc);

		SourceType getSourceType();

		// void setSolutionGenerationType(SolutionGenerationType v_sgt);

		// SolutionGenerationType getSolutionGenerationType();

		void setAsCustomer(int customerId, int demand);

		void setAsDepot(int depotId, int capacity);
				
		void setUpCustomerList();

		void setUpDepotList();

		void setUpCustomerAndDepotLists();

		void setUpVehicleCapacity();

		// long int getVehicleCapacity();

		// void setUpVehiclesPerDepot();

		// void assignVehiclesToDepots(int depotId, int depotDemand);

		// void setUpVehiclePairList();

		// int getNumberOfVehicles();

		int getCustomerInternalId(int position);
		
		// int getCustomerDemandByIndex(int position);

		// int getDepotInternalId(int position);

		// int getDepotCapacityByIndex(int position);

		// int getDepotRemainingCapacityByIndex(int position);

		// void decRemainingDepotCapacity(int position, int capacity_to_dec);

		// void setDepotRemainingCapacityByIndex(int position, int remaining_capacity);

		// FrogLeapSolution * genRandomFrogLeapSolution(FrogLeapController * controller);

		// void resetCapacityOrDemand(Pair * depotPair);

		// long int getTope();

		// FrogObjectCol * createDepotListOrderedByCapacity();

		// FrogObjectCol * createDepotListDescOrderedByCapacity();

		// FrogObjectCol * createDepotListOrderedByRemainingCapacity();

		// FrogObjectCol * createCustomerListOrderedByDemandDesc();

		// FrogObjectCol * createCustomerListOrderedByDemand();

		// void resetDepotRemainingCapacities();

		// void resetCustomerRemainingDemands();

		void loadCustomerAndDepotList();

		// int getLabel(int internalId);

		// int getDepotListIndexByInternal(int depotInternalId);

		// int getCustomerListIndexByInternal(int customerInternalId);

		// int getDepotIndexByLabelId(int depotLabelId);

		// int getCustomerIndexByLabelId(int depotLabelId);

		// FrogObjectCol * getTestCustomerSectionList();

		// long long int getGlobalVehicleId();		

		// int getCloserIndexToDepot(int depotIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localDepotCol);

		// int getClosestLocalDepotIndexToCustomer(int customerIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localDepotCol, float & distance);

		// int getClosestCustomerLocalIndexToDepot(int depotIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localNodeCol);

		// int getClosestCustomerLocalIndexToCustomer(int customerIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localCustomerIndexesCol);

		// bool existInLocalDepotList(int assignedDepotIndex, FrogObjectCol * localDepotCol, int low, int top);

		// int getDepotIndexOfClosestAssignedCustomer(int customerIndex, FrogObjectCol * localDepotCol, int low, int top, float & distanceToCustomer);

		// void setCustomerPairAsAssigned(int customerIndex, int depotIndex);

		// void resetCustomersAsNotAssigned();

		// float genRandomFloatingNumber(float a, float b);

		// int genRandomIntNumber(int a, int b);

		// int getX_Coord(int nodeInternalId);

		// int getY_Coord(int nodeInternalId);
		
		// FrogObjectCol * createMatchCustomerList(Pair * currentDepotPair);

		// FrogObjectCol * createMatchCustomerList_Cluster(Cluster * currentCluster, FrogLeapSolution * fls);

		// FrogObjectCol * createCustomerListOrderedByDistanceFromDepot(Pair * currentDepotPair);

		// FrogObjectCol * createCustomerListOrderedByDistanceFromCluster(Cluster * currentDepotPair);

		// FrogObjectCol * createDepotListOrderedByDistanceFromCustomer(Pair * currentCustomerPair);

		// FrogObjectCol * createClusterIdListOrderedByDistanceFromCustomer(Pair * currentCustomerPair);

		// bool isAMatch(Pair * currentCustomerPair, Pair * currentDepotPair);

		// int getTotalDemandOrCapacity(FrogObjectCol * pairCol);

		// void assignDepotToCustomerPairs(Pair * depotPair, FrogObjectCol * customerCol);

		// void assignCustomersToCluster(Cluster * cluster, FrogObjectCol * & customerCol, FrogLeapSolution * fls);

		// float assignRandomToDepotSelected(int depotIndex);

		// FrogObjectCol * assignDepotToCustomerPairsUntilDemandComplete(Pair * depotPair, FrogObjectCol * customerCol);

		// FrogObjectCol * selectCustomerPairsUntilDemandComplete(Pair * depotPair, FrogObjectCol * customerCol);

		// FrogObjectCol * selectCustomerPairsUntilDemandComplete_Cluster(Cluster * cluster, FrogObjectCol * customerCol);

		// void assignCustomersToDepotOrNearCustomerDepot(FrogObjectCol * & customerCol, FrogObjectCol * depotListOrderedByCapacity, FrogLeapSolution * fs);
		
		// FrogObjectCol * orderCustomerPairListByNthClosestDepotDesc(int n, FrogObjectCol * customerPairCol);

		// FrogObjectCol * orderCustomerPairListByNthClosestClusterDesc(int n, FrogObjectCol * customerPairCol);

		// void assignDepotToCustomer(Pair * depotPair, Pair * customerPair);

		// float addRandomNumberToInt(int index);

		// bool isCustomerPairAssigned(Pair * customerPair);

		// bool allCustomerPairAssigned();

		// float assignRandomFeasibleDepot4(FrogObjectCol * & localDepotCol, int customerIndex);

		// int colectRandomFeasibleDepot4(FrogObjectCol * & localDepotCol, int customerIndex);

		// int getNumberOfUnassignedCustomers();

		// void initCheckFLS_for_depots();

		// bool checkFLS(FrogLeapSolution * fls, int & v_customerIndex, int & depotIndex, float & capacity, float & cumDemand);

		// bool checkFLS_i(FrogLeapSolution * fls, int customerIndex, int & depotIndex, float & capacity, float & cumDemand);

		// void applyLocalDepotOrderSearch();

		// void deleteDepotFeasibleSolution();

		// void setDepotFeasibleSolution(FeasibleSolution * v_fs);
		
		// bool generateLocalDepotSolutionsAndEvaluate();

		// time_t getSeedUsed();

		// void start_Timer();

		// void take_Execution_Time();

		// long long int get_Execution_Time();

		// void set_BestSolution_ExecutionTime(long long int bestSolutionExecutionTime);

		// DistanceTypeCtrl getDistanceTypeCtrl();

		// Pair * getTempCustomerItem(int position);

		// void saveRemainingCapacityOfDepot(int depotIndex);

		// void saveRemainingCapacityOfDepots();

		// void restoreRemainingCapacityOfDepot(int depotIndex);
		
		// void restoreRemainingCapacityOfDepots();

		// // functions for writing information in an output file
		// void openOutPutFile();

		// void closeOutPutFile();

		// FILE * getPFile();

		// char * getTestCaseName();

		// char * getTestCaseComment();

		// int getTestCaseDimension();

		// char * getTestCaseType();

		// int getTestCaseCapacity();

		// void writeBestAndCurrentSolutionsAndTime();

		// void writeSeed();
		// void writeFrogLeapSolution(FrogLeapSolution * fls);		
		// void writeIterationInfo(long long int i, float currentValue);
		// void writeRandomInfo(float a, float b, float finalRandom);
		// void writeExecutionInfo();
};
#endif
