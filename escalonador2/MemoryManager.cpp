#include "MemoryManager.h"
#include <algorithm>
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
	this->totalAuxListQuickFeet = 4;

	this->alg = alg;

	this->freeList.head = nullptr;
	this->freeList.tail = nullptr;
	this->freeList.value = -1;
	this->freeList.available = totalMemory;
	this->freeList.total = totalMemory;
	this->freeList.len = 0;
	this->freeList.occupiedMemory = 0;

	if (alg == MemoryManager::Algorithms::quick_fit) {
		for (int i = 0; i < this->totalAuxListQuickFeet; i++) {
			QuickfeetFreeBlocksItem nb;
			nb.value = -1;
			nb.len = 0;
			this->quickfeetFreeBlocksList.push_back(nb);
		}
	}
}

MemoryManager::QuickfeetFreeBlocksItem& MemoryManager::findFreeBlock(int qtdNeeded) {
	for (QuickfeetFreeBlocksItem qfb : this->quickfeetFreeBlocksList) {
		if (qtdNeeded == qfb.value) {
			return qfb;
		}
	}

	return this->freeList;
}

MemoryBlock* MemoryManager::malloc(int memoryNeeded, QuickfeetFreeBlocksItem &lista) {
	this->checkStatisticsTable(memoryNeeded); //Fase de teste
	MemoryBlock* mbAux = lista.head;
	//if (item.value != QuickfeetFreeBlocksItem().value) {
	//	mbAux = item.head;
	//}
	//else
	//{
	//	mbAux = this->headFreeBlockList;
	//}
	//this->occupiedMemory += memoryNeeded;

	lista.occupiedMemory +=  memoryNeeded;
	MemoryBlock* bestBlock = nullptr;
	int bestBlockValue = numeric_limits<int>::max();

	if (this->alg == MemoryManager::Algorithms::quick_fit) {
		this->minimumAmountCallsCounter ++;
	}

	while (mbAux != nullptr) {
		if (mbAux->getTotalBlockSize() >= memoryNeeded) {
			if (this->alg == MemoryManager::Algorithms::first_fit || this->alg == MemoryManager::Algorithms::quick_fit) {
				this->calculateAvaibleMemory(lista);
				this->removeBlock(mbAux, lista);
			/*	if (lista.value != QuickfeetFreeBlocksItem().value) {
					lista.len--;
				}
				else
				{
					this->freeMemoryLen--;
				}*/
				lista.len--;
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
		this->calculateAvaibleMemory(lista);
		this->removeBlock(bestBlock, lista);
		//this->freeMemoryLen--;
		lista.len--;

		bestBlock->setOccupedSize(memoryNeeded);
		return bestBlock;
	}

	this->memoryOverhead += this->memoryStaticOverhead;

	int position = this->memory.size();
	MemoryBlock* newMb = new MemoryBlock(memoryNeeded, memoryNeeded, position);
	this->memory.push_back(newMb);
	this->calculateAvaibleMemory(lista);

	return newMb;
}

MemoryBlock* MemoryManager::malloc(int memoryNeeded) {
	if (this->alg == MemoryManager::Algorithms::first_fit || this->alg == MemoryManager::Algorithms::best_fit) {
		return this->malloc(memoryNeeded, this->freeList);
	}
	else {

		QuickfeetFreeBlocksItem& list = this->findFreeBlock(memoryNeeded);
		if (list.len > 0) {
			return this->malloc(memoryNeeded, list);
		}
		else {
			return this->malloc(memoryNeeded, this->freeList);
		}
	}
}

bool MemoryManager::checkFreeMemory(int memoryNeeded, QuickfeetFreeBlocksItem &list) {
	if (list.available < memoryNeeded)
		return false;
	else {
		MemoryBlock* mb_aux = list.head;
			//this->headFreeBlockList;
		int avaibleInMemoryBlock = 0;
		while (mb_aux != nullptr) {
			if (mb_aux->getTotalBlockSize() >= memoryNeeded) {
				return true;
			}

			avaibleInMemoryBlock += mb_aux->getTotalBlockSize();
			mb_aux = mb_aux->getNextFreeBlock();
		}

		if (list.available - avaibleInMemoryBlock >= memoryNeeded)
			return true;
		else
			return false;
	}
}

bool MemoryManager::checkFreeMemory(int memoryNeeded) {
	if (this->alg == MemoryManager::Algorithms::first_fit || this->alg == MemoryManager::Algorithms::best_fit) {
		return this->checkFreeMemory(memoryNeeded, this->freeList);
	}
	else {
		QuickfeetFreeBlocksItem& list = this->findFreeBlock(memoryNeeded);
		if (list.value == -1) {
			return this->checkFreeMemory(memoryNeeded, list);
		}
		else {
			bool result = this->checkFreeMemory(memoryNeeded, list);
			if (!result) {
				return this->checkFreeMemory(memoryNeeded, this->freeList);
			}
			else {
				return result;
			}
		}

	}
 }

void MemoryManager::free(MemoryBlock* block, QuickfeetFreeBlocksItem &list) {
 	int occupedSize = block->getOccupedSize();
	//this->occupiedMemory -= occupedSize;
	list.occupiedMemory -= occupedSize;
	block->resetOccupedSize();

	this->calculateAvaibleMemory(list);
	//block->resetOccupedSize();

	if (list.head == nullptr) {
		list.head = block;
		list.tail = block;
	} else {
		list.tail->setNextFreeBlock(block);
		list.tail = block;
	}

	list.len++;
	//this->freeMemoryLen++;
}

void MemoryManager::free(MemoryBlock* block) {
	if (this->alg == MemoryManager::Algorithms::first_fit || this->alg == MemoryManager::Algorithms::best_fit) {
		this->free(block, this->freeList);
	} else {
		QuickfeetFreeBlocksItem& list = this->findFreeBlock(block->getTotalBlockSize());

		this->free(block, list);
	}
}

void MemoryManager::calculateAvaibleMemory(QuickfeetFreeBlocksItem &list) {
	list.available = this->totalMemory - this->memoryOverhead - list.occupiedMemory;
	//this->availableMemory = this->totalMemory - this->memoryOverhead - this->occupiedMemory;
}

void MemoryManager::removeBlock(MemoryBlock* mb, QuickfeetFreeBlocksItem &item) {
	MemoryBlock* head = nullptr;
	MemoryBlock* tail = nullptr;
	/*if (item.value != QuickfeetFreeBlocksItem().value) {
		head = item.head;
		tail = item.tail;
		mainList = false;
	}
	else
	{
		head = this->headFreeBlockList;
		tail = this->tailFreeBlockList;
	}*/

	head = item.head;
	tail = item.tail;


	if (mb == head) {
		//MemoryBlock* aux = mb->getNextFreeBlock();
	/*	if (mainList) {
			this->headFreeBlockList = mb->getNextFreeBlock();
		}
		else {
			item.head = mb->getNextFreeBlock();
		}*/

		item.head = mb->getNextFreeBlock();

	} else if (mb == tail) {
		MemoryBlock* aux = head;
		while (aux->getNextFreeBlock() != mb) {
			aux = aux->getNextFreeBlock();
		}
		aux->setNextFreeBlock(nullptr);

		/*if (mainList) {
			this->headFreeBlockList = aux;
		}
		else {
			item.head = aux;
		}*/

		item.tail = aux;

	} else {
		MemoryBlock* aux = head;
		while (aux->getNextFreeBlock() != mb) {
			aux = aux->getNextFreeBlock();
		}

		aux->setNextFreeBlock(mb->getNextFreeBlock());
	}
	mb->setNextFreeBlock(nullptr);
}

void MemoryManager::checkStatisticsTable(int value) {
	bool key = true;
	for (MemoryBlockFrequency &mbf : this->statisticsTable) {
		if (value == mbf.value) {
			mbf.qtd++;
			key = false;
			sort(this->statisticsTable.begin(), this->statisticsTable.end(), [](const MemoryBlockFrequency& a, const MemoryBlockFrequency& b) {
				return a.qtd > b.qtd;
			});
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

void MemoryManager::createQuickfeetBlock() {

	MemoryBlock* auxMb = this->freeList.head;

	for (int i = 0; i < this->totalAuxListQuickFeet; i++) {
		this->quickfeetFreeBlocksList.at(i).value = this->statisticsTable.at(i).value;
	}

	while (auxMb != nullptr) {
		MemoryBlock* nextAuxMb = auxMb->getNextFreeBlock();

		for (int i = 0; i < this->totalAuxListQuickFeet; i++) {
			if (auxMb->getTotalBlockSize() == this->statisticsTable.at(i).value) {
				this->removeBlock(auxMb, this->freeList);

				this->quickfeetFreeBlocksList.at(i).available += auxMb->getTotalBlockSize();
				this->freeList.available -= auxMb->getTotalBlockSize();
				this->quickfeetFreeBlocksList.at(i).len++;
				this->freeList.len --;

				if (this->quickfeetFreeBlocksList.at(i).head == nullptr) {

					this->quickfeetFreeBlocksList.at(i).head = auxMb;
					this->quickfeetFreeBlocksList.at(i).tail = auxMb;
				}
				else {
					this->quickfeetFreeBlocksList.at(i).tail->setNextFreeBlock(auxMb);
					this->quickfeetFreeBlocksList.at(i).tail = auxMb;
				}
				break;
			}
		}
		auxMb = nextAuxMb;
	}
}

void MemoryManager::resetQuickfeetBlock() {
	if (this->quickfeetFreeBlocksList.at(0).value == -1) {
		return;
	}

	for (int i = 0; i < this->totalAuxListQuickFeet; i++) {
		MemoryBlock* aux = this->quickfeetFreeBlocksList.at(i).head;

		while (aux != nullptr) {
			MemoryBlock* nextAuxMb = aux->getNextFreeBlock();

			this->freeList.available += aux->getTotalBlockSize();
			this->freeList.len++;

			this->removeBlock(aux, this->quickfeetFreeBlocksList.at(i));

			if (this->freeList.head == nullptr) {
				this->freeList.head = aux;
				this->freeList.tail = aux;
			}
			else {
				this->freeList.tail->setNextFreeBlock(aux);
				this->freeList.tail = aux;
			}

			aux = nextAuxMb;
		}



		QuickfeetFreeBlocksItem nb;
		nb.value = -1;
		nb.len = 0;

		this->quickfeetFreeBlocksList.at(i) = nb;

		//this->freeList.occupiedMemory += this->quickfeetFreeBlocksList.at(i).occupiedMemory;
	}
}

void MemoryManager::showStatus() {
	
	this->showEmptyListsStatus();

	cout << "Sort: [";
	for (unsigned i = 0; i < statisticsTable.size(); i++)
		cout << "{" << statisticsTable.at(i).qtd << "|" << statisticsTable.at(i).value << "}, ";
	cout << "]" << endl;

	cout << "T: " << this->totalMemory << " ,A: " << this->freeList.available << " ,O: " << this->freeList.occupiedMemory << " ,Ov " << this->memoryOverhead << " ,QtdB " << this->memoryOverhead / this->memoryStaticOverhead << " ,FLen " << this->freeMemoryLen<< endl;

	//cout << "T: " << this->freeList.total << " ,A: " << this->freeList.available << " ,O: " << this->freeList.occupiedMemory << " ,Ov " << this->memoryOverhead << " ,QtdB " << this->memoryOverhead / this->memoryStaticOverhead << " ,FLen " << this->freeList.len << endl;
}

void MemoryManager::showEmptyListsStatus() {
	cout << "bbbbbbb " << freeList.value << endl;

	this->printEmptyList(this->freeList);
	cout << "aaaaa " << freeList.value << endl;
	if (this->quickfeetFreeBlocksList.size() > 0) {
		for (QuickfeetFreeBlocksItem list : this->quickfeetFreeBlocksList) {
			this->printEmptyList(list);

		}
	}
}

MemoryManager::Algorithms MemoryManager::getAlg()
{
	return this->alg;
}

void MemoryManager::verifyAndCreateAuxLists()
{
	if (this->minimumAmountCallsCounter != this->minimumAmountCalls) {
		return;
	}
	else {
		this->resetQuickfeetBlock();
		this->minimumAmountCallsCounter = 0;
		this->createQuickfeetBlock();

	}
}

void MemoryManager::printEmptyList(QuickfeetFreeBlocksItem& list) {
	MemoryBlock* aux = list.head;
	cout << "Lv: " << list.value << " , Sz: " << list.len <<" [ ";
	while (aux != nullptr) {
		cout << aux->getTotalBlockSize() << " ,";
		aux = aux->getNextFreeBlock();
	}

	cout << " ]" << endl;
}