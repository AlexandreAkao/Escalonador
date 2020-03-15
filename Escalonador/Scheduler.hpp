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
				if (ready_queue.size() > 0) {

					schedule_process(core_position);

				}
			}
			else
			{
				cout << "------------------------------" << endl;
				cpu->printProcessos();
				printReadQueue();

				Process* process = getCpuCore(core_position);
				
				int tempoParaSerProcessado = 0;
				if (this->algorithm == Algorithms::round_robin) {
					tempoParaSerProcessado = quantum;
				}
				else {
					tempoParaSerProcessado = process->get_remaining_time();
				}
				
				for (int i = 0; i < tempoParaSerProcessado; i++) {

					this_thread::sleep_for(chrono::seconds(1));

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

	void printReadQueue() {
		if (printing == false) {
			printing = true;
			cout << "A: ";
			if (ready_queue.size() > 0 ){
				for (Process* p : ready_queue) {
					cout << "[ " << p->get_remaining_time() << " , " << p->get_total_time() << "] , ";
				}
			}
			cout << endl;
			printing = false;

		}

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
	bool printing = false;

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
		if (ready_queue.size() > 0) {

			Process* aux = this->ready_queue.front();
			this->ready_queue.pop_front();

			aux->set_state(Process::States::running);
			setCpuCore(position, aux);
		}
	
	}

	void deschedule_process(int position)
	{
		Process* process = getCpuCore(position);
		cpu->getCore(position)->setProcess(NULL);


		if (process->get_remaining_time() > 0) {
			process->set_state(Process::States::ready);
			insert_process(process);
		}
		else {
			process->set_state(Process::States::terminated);
		}

	}
};
