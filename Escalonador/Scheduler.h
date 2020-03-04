#include <list> 
#include <iostream> 
#include <vector>
#include <thread> 

#include "Process.h"

#pragma once
#ifndef Scheduler_H
#define Scheduler_H
class Scheduler
{
public:
	enum class Algorithms
	{
		fifo, sjf, round_robin
	};

	Scheduler(Algorithms algotithm, int cores, int quantum);

	~Scheduler();
	
	void insert_process(Process* newProcess);
	void process_core(int core_position);

	void run();



	void mostrar_queue();
	list<Process*> get_queue();


private:
	int quantum;
	vector<Process*> cores;
	list<Process*> ready_queue;
	Algorithms algorithm;
	int qtd_cores;
	bool someEmpty;

	void insertOnSort(Process* new_process);
	void fifo_scheduler();
	void shortest_job_first();
	void round_robin();

	void schedule_process(Process* process);
	void deschedule_process(int position);
};
#endif
