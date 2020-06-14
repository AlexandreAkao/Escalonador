#include <list> 
#include <iostream> 
#include <vector>
#include <thread> 
//#include "Process.h"
#include "CPU.h"
#include "MemoryBlock.h"
#include "MemoryManager.h" 

#pragma once
class Scheduler {
public:
	enum class Algorithms {
		fifo, sjf, round_robin
	};

	Scheduler(Algorithms algotithm, int cores, int quantum, CPU* cpu, MemoryManager* memoryManager);
	void insert_process(Process* newProcess, bool isNew);
 	void process_core_singlethread();
	void run();
	void printReadyQueue();
	list<Process*> get_queue();
private:
	int quantum;
	list<Process*> ready_queue;
	Algorithms algorithm;
	CPU* cpu;
	int qtd_cores;
	bool printing = false;
	MemoryManager* memoryManager;
	void insertOnSort(Process* new_process);
	void setCpuCore(int position, Process* process);
	Process* getCpuCoreProcess(int position);
	Core* getCpuCore(int position);
	void schedule_process(int position);
	void deschedule_process(int position, bool wasAborted);
 };
