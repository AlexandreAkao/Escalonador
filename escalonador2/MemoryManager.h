#include <vector> 
#include "MemoryBlock.h"

using namespace std;
#pragma once
class MemoryManager
{
public:
	MemoryManager(int totalMemory) {
		this->totalMemory = totalMemory;
		this->freeBlockList = nullptr;
		this->memoryOverhead = 0;
		this->availableMemory = totalMemory;
		this->occupiedMemory = 0;
	}
	MemoryBlock* malloc(int memory);

	bool checkFreeMemory() {
		
	}

private:
	vector<MemoryBlock*> memory;
	MemoryBlock* freeBlockList;
	int totalMemory;
	int memoryOverhead;
	int availableMemory;
	int occupiedMemory;
};

