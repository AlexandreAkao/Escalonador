#include <list> 
#include <iostream> 
#include <vector>
#include <thread> 
#include "Process.h"
#include "CPU.hpp"
#pragma once
class Scheduler
{
public:
	enum class Algorithms
	{
		fifo, sjf, round_robin
	};

	Scheduler(Algorithms algotithm, int cores, int quantum, CPU* cpu) {
		this->cpu = cpu;
		this->algorithm = algotithm;
		this->quantum = quantum;
		qtd_cores = cores;
		this->someEmpty = true;
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
			if (cpu->coreIsEmpty(core_position)) {
				schedule_process(core_position);
			}
			else
			{
				Process* process = getCpuCore(core_position);
				
				int tempoParaSerProcessado = 0;
				if (this->algorithm == Algorithms::round_robin) {
					tempoParaSerProcessado = quantum;
				}
				else {
					tempoParaSerProcessado = process->get_remaining_time();
				}
				
				for (int i = 0; i < tempoParaSerProcessado; i++) {
					process->printProcess();
					this_thread::sleep_for(chrono::seconds(1));
					cout << process->get_process_id() <<" : "<<process->get_remaining_time() << endl;

					if (process->decrease_time(1) == 0)
						break;
				}
		
				deschedule_process(core_position);
			}
		}
	}

	void run()
	{
		vector<thread> cores_thread;

		for (int i = 0; i < qtd_cores; i++)
			cores_thread.push_back(thread(&Scheduler::process_core, this, i));
		for (thread& t : cores_thread)
			t.join();

	}

	void mostrar_queue() {
		for (Process* p : ready_queue) {
			cout << p->get_process_id() << endl;
		}
	}

	list<Process*> get_queue();

private:
	int quantum;
	list<Process*> ready_queue;
	Algorithms algorithm;
	CPU* cpu;
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

	void setCpuCore(int position, Process* process) {
		this->cpu->getCores()[position]->setProcess(process);
	}

	Process* getCpuCore(int position) {
		return this->cpu->getCores()[position]->getProcess();
	}
	
	void schedule_process(int position)
	{
		Process* aux = this->ready_queue.front();
		aux->set_state(Process::States::running);
		setCpuCore(position, aux);
		this->ready_queue.pop_front();
	}

	void deschedule_process(int position)
	{
		Process* process = cpu->getCore(position)->getProcess();
		cpu->getCore(position)->setProcess(NULL);
		//std::vector<Process* >::iterator it;
		
		//this->cores.erase(it + position);

		//it = cores.insert(it + position, NULL);

		//this->cores.erase;

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
