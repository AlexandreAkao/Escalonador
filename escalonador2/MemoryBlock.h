#pragma once
class MemoryBlock
{
public:
	MemoryBlock(int totalBlockSize, int occupiedSize, int position);
	
	void setOccupiedSize(int ocs);

	void setNextFreeBlock(MemoryBlock* ocs);

	void removeNextFreeBlock();

	int getOccupiedSize();

	int getTotalBlockSize();

	int getPosition();

	MemoryBlock* getNextFreeBlock();

private:
	int totalBlockSize;
	int occupiedSize;
	int position;
	MemoryBlock* nextFreeBlock;
};

