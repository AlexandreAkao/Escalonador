#include <iostream> 
#include <vector> 
#include "MemoryBlock.h"
//#include "Kernel.h"
#pragma once

using namespace std;
class Process
{
public:
	enum class States
	{
		ready, running, terminated, aborted
	};

	Process(int process_id, int total_time, States state);

	void printProcess();
	string getStatusAsString();
	int get_remaining_time();
	int get_total_time();
	int get_process_id();
	States getState();
	void set_state(States state);
	void set_remaining_time(int time);
	int decrease_time(int time);
	void setMemoryPointers(MemoryBlock* mb);
	void generateRandomMemory(bool isStatic);
	vector<MemoryBlock*> abortProcess();

	void removeMemoryPointers();

private:
	int dinamicProb;
	int process_id;
	int total_time;
	int remaining_time;
	States state;
	//Kernel* kernel;
	vector< MemoryBlock*> memoryPointers; 

};
