#pragma once
class MemoryBlock
{
public:


	MemoryBlock(int totalBlockSize, int occupedSize, int position);
	
	void resetOccupedSize();

	void setNextFreeBlock(MemoryBlock* ocs);

	void removeNextFreeBlock();

	int getOccupedSize();

	int getTotalBlockSize();

	int getPosition();

	MemoryBlock* getNextFreeBlock();

private:
	int totalBlockSize;
	int occupedSize;
	int position;
	MemoryBlock* nextFreeBlock;
};

