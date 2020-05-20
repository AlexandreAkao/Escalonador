#include "MemoryBlock.h"

MemoryBlock::MemoryBlock(int totalBlockSize, int occupedSize, int position)
{
	this->nextFreeBlock = nullptr;
	this->totalBlockSize = totalBlockSize;
	this->occupedSize = occupedSize;
	this->position = position;
}

void MemoryBlock::resetOccupedSize()
{
	this->occupedSize = 0;
}

void MemoryBlock::setNextFreeBlock(MemoryBlock* ocs)
{
	this->nextFreeBlock = ocs;
}

void MemoryBlock::removeNextFreeBlock()
{
	this->nextFreeBlock = nullptr;
}

int MemoryBlock::getOccupedSize()
{
	return this->occupedSize;
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
