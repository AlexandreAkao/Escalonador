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
	void calculateAvaibleMemory();

	void removeBlock(MemoryBlock* mb);


	vector<MemoryBlock*> memory;
	MemoryBlock* headFreeBlockList;
	MemoryBlock* tailFreeBlockList;

	int totalMemory;
	int memoryOverhead;
	int availableMemory;
	int occupiedMemory;
	int memoryStaticOverhead;
	int minimumAmountCalls;
	int freeMemoryLen = 0;
};

