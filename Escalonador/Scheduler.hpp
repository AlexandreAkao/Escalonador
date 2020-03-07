#include <list> 
#include <iostream> 
#include <vector>
#include <thread> 

#include "Process.h"
#include "CentralPu.hpp"

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

	Scheduler(Algorithms algotithm, int cores, int quantum) {
		this->algorithm = algotithm;
		this->quantum = quantum;
		qtd_cores = cores;
		this->someEmpty = true;
		for (int i = 0; i < cores; i++)
			this->cores.push_back(NULL);
	}


	~Scheduler();
	
	void insert_process(Process* newProcess) {
		if (algorithm == Algorithms::sjf) {
			insertOnSort(newProcess);
		}
		else {
			ready_queue.push_back(newProcess);
		}
	}
	void process_core(int core_position)
	{
		while (true)
		{
			if (this->cores[core_position] == NULL) {
				this->someEmpty = true;
			}
			else
			{
				Process* process = this->cores[core_position];

				if (this->algorithm == Scheduler::Algorithms::round_robin) {
					this_thread::sleep_for(chrono::seconds(this->quantum));
					process->set_remaining_time(process->get_remaining_time() - quantum);
				}
				else {
					this_thread::sleep_for(chrono::seconds(process->get_remaining_time()));
					process->set_remaining_time(0);
				}

				deschedule_process(core_position);
			}
		}
	}

	void run()
	{
		thread algorithm_thread;
		vector<thread> cores_thread;
		if (this->algorithm == Scheduler::Algorithms::fifo) {
			algorithm_thread = thread(&Scheduler::fifo_scheduler, this);

		}
		else if (this->algorithm == Scheduler::Algorithms::sjf) {
		}
		else {

		}
		for (int i = 0; i < qtd_cores; i++)
			cores_thread.push_back(thread(&Scheduler::process_core, this, i));
		for (thread& t : cores_thread)
			t.join();

		algorithm_thread.join();


	}



	void mostrar_queue() {
		for (Process* p : ready_queue) {
			cout << p->get_process_id() << endl;
		}
	}
	list<Process*> get_queue();


private:
	int quantum;
	vector<Process*> cores;
	list<Process*> ready_queue;
	Algorithms algorithm;
	//CentralPu* cpu;
	int qtd_cores;
	bool someEmpty;

	void insertOnSort(Process* new_process) {
		int key = 0;
		list<Process*>::iterator it = ready_queue.begin();

		for (Process* process : ready_queue)
		{
			if (process->get_total_time() > new_process->get_total_time())
				break;
			else
				key++;
		}

		advance(it, key);
		ready_queue.insert(it, new_process);


	}
	void fifo_scheduler()
	{
		while (true)
		{
			if (someEmpty) {
				if (ready_queue.size() > 0) {
					schedule_process(ready_queue.front());
					ready_queue.pop_front();
				}

			}
		}

	}
	void shortest_job_first()
	{
		while (true)
		{
			if (someEmpty) {
				if (ready_queue.size() > 0) {
					schedule_process(ready_queue.front());
					ready_queue.pop_front();
				}

			}
		}
	}
	void round_robin();
	
	void schedule_process(Process* process)
	{
		for (Process* proc : this->cores) {
			if (proc == NULL) {
				proc = process;
				proc->set_state(Process::States::running);
				break;
			}
		}
	}
	void deschedule_process(int position)
	{
		Process* process = this->cores[position];
		this->cores[position] = NULL;

		if (process->get_remaining_time() > 0) {
			process->set_state(Process::States::ready);
			insert_process(process);
		}
		else {
			process->set_state(Process::States::terminated);
		}

		someEmpty = true;


	}
};
#endif
