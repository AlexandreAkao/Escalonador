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

	void showEmptyListsStatus();


private:
	struct QuickfeetFreeBlocksItem {
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

	void printEmptyList(QuickfeetFreeBlocksItem& list);

	void calculateAvaibleMemory(QuickfeetFreeBlocksItem& list);

	bool checkFreeMemory(int memoryNeeded, QuickfeetFreeBlocksItem& list);
	void free(MemoryBlock* position, QuickfeetFreeBlocksItem& list);

	QuickfeetFreeBlocksItem& findFreeBlock(int qtdNeedes);
	MemoryBlock* malloc(int memoryNeeded, QuickfeetFreeBlocksItem &list);

	void removeBlock(MemoryBlock* mb, QuickfeetFreeBlocksItem& list);



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

	QuickfeetFreeBlocksItem freeList;
	MemoryManager::Algorithms alg;
};

