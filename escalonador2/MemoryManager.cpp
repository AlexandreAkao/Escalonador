#include "MemoryManager.h"

MemoryManager::MemoryManager(MemoryManager::Algorithms alg, int totalMemory,int minimumAmountCalls)
{
	this->totalMemory = totalMemory;
	this->headFreeBlockList = nullptr;
	this->tailFreeBlockList = nullptr;
	this->minimumAmountCalls = minimumAmountCalls;
	this->memoryOverhead = 0;
	this->availableMemory = totalMemory;
	this->occupiedMemory = 0;
	this->memoryStaticOverhead = 16;
}

MemoryBlock* MemoryManager::malloc(int memoryNeeded)
{
	MemoryBlock* mbAux = this->headFreeBlockList;
	this->occupiedMemory += memoryNeeded;

	while (mbAux != nullptr) {
		if (mbAux->getTotalBlockSize() >= memoryNeeded) {
			this->calculateAvaibleMemory();
			this->removeBlock(mbAux);
			return mbAux;
		}
		mbAux = mbAux->getNextFreeBlock();

	}

	this->memoryOverhead += this->memoryStaticOverhead;

	int position = this->memory.size();
	MemoryBlock* newMb = new MemoryBlock(memoryNeeded, memoryNeeded, position);
	this->memory.push_back(newMb);
	this->calculateAvaibleMemory();

	return newMb;
}

bool MemoryManager::checkFreeMemory(int memoryNeeded)
{
	if (this->availableMemory < memoryNeeded)
		return false;
	else {
		MemoryBlock* mb_aux = this->headFreeBlockList;
		while (mb_aux != nullptr) {
			if (mb_aux->getTotalBlockSize() >= memoryNeeded) {
				return true;
			}
		}

		return false;

	}
}

void MemoryManager::free(MemoryBlock* position)
{
	int occupedSize = position->getOccupedSize();
	this->occupiedMemory -= occupedSize;
	this->calculateAvaibleMemory();

	position->resetOccupedSize();
	this->tailFreeBlockList->setNextFreeBlock(position);
	this->tailFreeBlockList = position;
}

void MemoryManager::calculateAvaibleMemory()
{
	this->availableMemory = this->totalMemory - this->memoryStaticOverhead - this->occupiedMemory;
}

void MemoryManager::removeBlock(MemoryBlock* mb)
{
	if (mb == this->headFreeBlockList) {
		//MemoryBlock* aux = mb->getNextFreeBlock();
		this->headFreeBlockList = mb->getNextFreeBlock();
	}
	else if (mb == this->tailFreeBlockList) {
		MemoryBlock* aux = this->headFreeBlockList;
		while (aux->getNextFreeBlock() != mb)
		{
			aux = aux->getNextFreeBlock();
		}
		aux->setNextFreeBlock(nullptr);
		this->tailFreeBlockList = aux;

	}
	else
	{
		MemoryBlock* aux = this->headFreeBlockList;
		while (aux->getNextFreeBlock() != mb)
		{
			aux = aux->getNextFreeBlock();
		}

		aux->setNextFreeBlock(mb->getNextFreeBlock());
	}
	mb->setNextFreeBlock(nullptr);

}
