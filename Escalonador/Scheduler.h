#include <list> 
#include <iostream> 
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
	Scheduler(Algorithms algorithm, int cores, list<Process*> ready_queue);
	Scheduler(Algorithms algorithm, int cores, list<Process*> ready_queue, int quantum);

	~Scheduler();
	
	void insert_process(Process* newProcess);

	void run();


	void mostrar_queue();
	list<Process*> get_queue();


private:
	int quantum;
	list<Process*> cores;
	list<Process*> ready_queue;
	Algorithms algorithm;
	int qtd_cores;

	void insertOnSort(Process* new_process);
	void fifo_scheduler();
	void shortest_job_first();
	void round_robin();

	void schedule_process();
	void deschedule_process();
};
#endif
