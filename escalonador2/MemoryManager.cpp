#include "MemoryManager.h"
#include <limits>

MemoryManager::MemoryManager(MemoryManager::Algorithms alg, int totalMemory,int minimumAmountCalls) {
	this->totalMemory = totalMemory;
	this->headFreeBlockList = nullptr;
	this->tailFreeBlockList = nullptr;
	this->minimumAmountCalls = minimumAmountCalls;
	this->minimumAmountCallsCounter = 0;
	this->memoryOverhead = 0;
	this->freeMemoryLen = 0;
	this->availableMemory = totalMemory;
	this->occupiedMemory = 0;
	this->memoryStaticOverhead = 16;
	this->alg = alg;
}

MemoryBlock* MemoryManager::malloc(int memoryNeeded, QuickfeetFreeBlocksItem item) {
	MemoryBlock* mbAux = nullptr;
	if (item.value != QuickfeetFreeBlocksItem().value) {
		mbAux = item.head;
	}
	else
	{
		mbAux = this->headFreeBlockList;
	}
	this->occupiedMemory += memoryNeeded;

	MemoryBlock* bestBlock = nullptr;
	int bestBlockValue = numeric_limits<int>::max();

	if (this->alg == MemoryManager::Algorithms::quick_fit) {
		this->minimumAmountCallsCounter ++;
	}

	while (mbAux != nullptr) {
		if (mbAux->getTotalBlockSize() >= memoryNeeded) {
			if (this->alg == MemoryManager::Algorithms::first_fit || this->alg == MemoryManager::Algorithms::quick_fit) {
				this->calculateAvaibleMemory();
				this->removeBlock(mbAux, item);
				if (item.value != QuickfeetFreeBlocksItem().value) {
					item.len--;
				}
				else
				{
					this->freeMemoryLen--;
				}

				mbAux->setOccupedSize(memoryNeeded);
				return mbAux;
				
			}
			else if (this->alg == MemoryManager::Algorithms::best_fit) {
				int difference = mbAux->getTotalBlockSize() - memoryNeeded;
				if(difference <= bestBlockValue) {
					bestBlock = mbAux;
					bestBlockValue = difference;
				}
			}
		}
		
		mbAux = mbAux->getNextFreeBlock();

	}

	if (this->alg == MemoryManager::Algorithms::best_fit && bestBlock != nullptr) {
		this->calculateAvaibleMemory();
		this->removeBlock(bestBlock, item);
		this->freeMemoryLen--;
		bestBlock->setOccupedSize(memoryNeeded);
		return bestBlock;
	}

	this->memoryOverhead += this->memoryStaticOverhead;

	int position = this->memory.size();
	MemoryBlock* newMb = new MemoryBlock(memoryNeeded, memoryNeeded, position);
	this->memory.push_back(newMb);
	this->calculateAvaibleMemory();

	return newMb;
}


MemoryBlock* MemoryManager::malloc(int memoryNeeded)
{
	if (this->alg == MemoryManager::Algorithms::first_fit || this->alg == MemoryManager::Algorithms::best_fit) {
		return this->malloc(memoryNeeded, QuickfeetFreeBlocksItem());
	}
	else {
		return nullptr;

	}
}

bool MemoryManager::checkFreeMemory(int memoryNeeded)
{
	if (this->availableMemory < memoryNeeded)
		return false;
	else {
		MemoryBlock* mb_aux = this->headFreeBlockList;
		int avaibleInMemoryBlock = 0;
		while (mb_aux != nullptr) {
			if (mb_aux->getTotalBlockSize() >= memoryNeeded) {
				return true;
			}

			avaibleInMemoryBlock += mb_aux->getTotalBlockSize();
			mb_aux = mb_aux->getNextFreeBlock();
		}

		if (this->availableMemory - avaibleInMemoryBlock >= memoryNeeded)
			return true;
		else
			return false;


	}
}

void MemoryManager::free(MemoryBlock* block) {
 	int occupedSize = block->getOccupedSize();
	this->occupiedMemory -= occupedSize;
	block->resetOccupedSize();

	this->calculateAvaibleMemory();
	//block->resetOccupedSize();

	if (headFreeBlockList == nullptr) {
		headFreeBlockList = block;
		tailFreeBlockList = block;
	} else {
		this->tailFreeBlockList->setNextFreeBlock(block);
		this->tailFreeBlockList = block;
	}

	this->freeMemoryLen++;
}

void MemoryManager::calculateAvaibleMemory() {
	this->availableMemory = this->totalMemory - this->memoryOverhead - this->occupiedMemory;
}


void MemoryManager::removeBlock(MemoryBlock* mb, QuickfeetFreeBlocksItem item) {
	MemoryBlock* head = nullptr;
	MemoryBlock* tail = nullptr;
	bool mainList = true;
	if (item.value != QuickfeetFreeBlocksItem().value) {
		head = item.head;
		tail = item.tail;
		mainList = false;
	}
	else
	{
		head = this->headFreeBlockList;
		tail = this->tailFreeBlockList;
	}

	if (mb == head) {
		//MemoryBlock* aux = mb->getNextFreeBlock();
		if (mainList) {
			this->headFreeBlockList = mb->getNextFreeBlock();
		}
		else {
			item.head = mb->getNextFreeBlock();
		}
	} else if (mb == tail) {
		MemoryBlock* aux = head;
		while (aux->getNextFreeBlock() != mb) {
			aux = aux->getNextFreeBlock();
		}
		aux->setNextFreeBlock(nullptr);
		if (mainList) {
			this->headFreeBlockList = aux;
		}
		else {
			item.head = aux;
		}
	} else {
		MemoryBlock* aux = head;
		while (aux->getNextFreeBlock() != mb) {
			aux = aux->getNextFreeBlock();
		}

		aux->setNextFreeBlock(mb->getNextFreeBlock());
	}
	mb->setNextFreeBlock(nullptr);

}

bool MemoryManager::compareByLength(const MemoryBlockFrequency& a, const MemoryBlockFrequency& b)

{
	return a.qtd > b.qtd;
}

void MemoryManager::checkStatisticsTable(int value)
{
	bool key = true;
	for (MemoryBlockFrequency mbf : this->statisticsTable) {
		if (value == mbf.value) {
			mbf.qtd++;
			key = false;
			break;
		}
	}

	if (key) {
		MemoryBlockFrequency newMbf;
		newMbf.qtd = 1;
		newMbf.value = value;
		this->statisticsTable.push_back(newMbf);
	}

}

void MemoryManager::showStatus() {
	cout << "T: " << this->totalMemory << " ,A: " << this->availableMemory << " ,O: " << this->occupiedMemory << " ,Ov " << this->memoryOverhead << " ,QtdB " << this->memoryOverhead / this->memoryStaticOverhead << " ,FLen " << this->freeMemoryLen<< endl;
}