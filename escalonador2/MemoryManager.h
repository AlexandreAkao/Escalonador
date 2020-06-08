#include <vector> 
#include <iostream> 

#include "MemoryBlock.h"

using namespace std;
#pragma once
class MemoryManager
{
public:
	enum class Algorithms
	{
		first_fit, best_fit, quick_fit
	};

	MemoryManager(MemoryManager::Algorithms alg ,int totalMemory, int minimumAmountCalls);

	MemoryBlock* malloc(int memoryNeeded);

	bool checkFreeMemory(int memoryNeeded);

	void free(MemoryBlock* position);
	void showStatus();




private:
	struct QuickfeetFreeBlocksItem {
		int value;
		int len;
		MemoryBlock* head;
		MemoryBlock* tail;
	};

	void calculateAvaibleMemory();

	MemoryBlock* malloc(int memoryNeeded, QuickfeetFreeBlocksItem item);

	void removeBlock(MemoryBlock* mb, QuickfeetFreeBlocksItem item);

	struct MemoryBlockFrequency {
		int value;
		int qtd;
	};





	bool compareByLength(const MemoryBlockFrequency& a, const MemoryBlockFrequency& b);

	void checkStatisticsTable(int value);

	vector<MemoryBlockFrequency> statisticsTable;
	vector<QuickfeetFreeBlocksItem> quickfeetFreeBlocksList;
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
	MemoryManager::Algorithms alg;
};

