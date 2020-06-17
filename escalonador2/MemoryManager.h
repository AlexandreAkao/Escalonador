#include <vector> 
#include <iostream> 

#include "MemoryBlock.h"

using namespace std;
#pragma once
class MemoryManager {
public:
	enum class Algorithms {
		first_fit, best_fit, quick_fit
	};
	
	MemoryManager(MemoryManager::Algorithms alg ,int totalMemory, int minimumAmountCalls, int totalAuxListQuickFeet);
	MemoryBlock* malloc(int memoryNeeded);
	bool checkFreeMemory(int memoryNeeded);
	void free(MemoryBlock* position);
	void showStatus();
	void showEmptyListsStatus();
	MemoryManager::Algorithms getAlg();
	void verifyAndCreateAuxLists();
	void run();

private:
	struct QuickFitFreeBlocksItem {
		int value;
		int len;
		int available;
		int total;
		int occupiedMemory;
		MemoryBlock* head;
		MemoryBlock* tail;
	};

	struct MemoryBlockFrequency {
		int value;
		int qtd;
	};

	void printEmptyList(QuickFitFreeBlocksItem& list);
	void calculateAvaibleMemory(QuickFitFreeBlocksItem& list);
	bool checkFreeMemory(int memoryNeeded, QuickFitFreeBlocksItem& list);
	void free(MemoryBlock* position, QuickFitFreeBlocksItem& list);
	QuickFitFreeBlocksItem* findFreeBlock(int qtdNeedes);
	int metodoDaFe(int qtdNeedes);
	MemoryBlock* malloc(int memoryNeeded, QuickFitFreeBlocksItem &list);
	void removeBlock(MemoryBlock* mb, QuickFitFreeBlocksItem& list);
	void checkStatisticsTable(int value);
	void createQuickfeetBlock();
	void resetQuickfeetBlock();


	vector<MemoryBlockFrequency> statisticsTable;
	vector<QuickFitFreeBlocksItem> quickfeetFitBlocksList;
	vector<MemoryBlock*> memory;
	MemoryBlock* headFreeBlockList;
	MemoryBlock* tailFreeBlockList;

	int totalMemory;
	int memoryOverhead;
	int availableMemory;
	int occupiedMemory;
	int memoryStaticOverhead;
	int minimumAmountCalls;
	int minimumAmountCallsCounter;
	int freeMemoryLen = 0;
	int totalAuxListQuickFeet;

	QuickFitFreeBlocksItem freeList;
	MemoryManager::Algorithms alg;
};

