#include "MemoryBlock.h"

MemoryBlock::MemoryBlock(int totalBlockSize, int occupiedSize, int position)
{
	this->nextFreeBlock = nullptr;
	this->totalBlockSize = totalBlockSize;
	this->occupiedSize = occupiedSize;
	this->position = position;
}

void MemoryBlock::setOccupiedSize(int ocs)
{
	this->occupiedSize = ocs;
}

void MemoryBlock::setNextFreeBlock(MemoryBlock* ocs)
{
	this->nextFreeBlock = ocs;
}

void MemoryBlock::removeNextFreeBlock()
{
	this->nextFreeBlock = nullptr;
}

int MemoryBlock::getOccupiedSize()
{
	return this->occupiedSize;
}

int MemoryBlock::getTotalBlockSize()
{
	return this->totalBlockSize;
}

int MemoryBlock::getPosition()
{
	return this->position;
}

MemoryBlock* MemoryBlock::getNextFreeBlock()
{
	return this->nextFreeBlock;
}
