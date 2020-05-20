#include <vector> 
#include "MemoryBlock.h"

using namespace std;
#pragma once
class MemoryManager
{
public:
	MemoryManager(int totalMemory, int minimumAmountCalls);

	MemoryBlock* malloc(int memoryNeeded);

	bool checkFreeMemory(int memoryNeeded);

	void free(MemoryBlock* position);



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
};

