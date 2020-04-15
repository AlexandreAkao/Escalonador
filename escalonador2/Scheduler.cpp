#include "Scheduler.h"

Scheduler::Scheduler(Algorithms algotithm, int cores, int quantum, CPU* cpu)
{
	this->cpu = cpu;
	this->algorithm = algotithm;
	this->quantum = quantum;
	qtd_cores = cores;
}

void Scheduler::insert_process(Process* newProcess)
{
	if (algorithm == Algorithms::sjf) {
		insertOnSort(newProcess);
	}
	else {
		ready_queue.push_back(newProcess);
	}
}

void Scheduler::process_core_multithread(int core_position)
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
			printReadyQueue();

			Process* process = getCpuCoreProcess(core_position);

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

void Scheduler::process_core_singlethread()
{
	while (true)
	{
		cout << "---------------------------------------------------------------------------------" << endl;

		cpu->printProcessos();
		printReadyQueue();

		this_thread::sleep_for(chrono::seconds(1));

		for (int core_position = 0; core_position < qtd_cores; core_position++) {
			if (cpu->coreIsEmpty(core_position)) {
				if (ready_queue.size() > 0)
					schedule_process(core_position);
			}
			else {
				if (this->algorithm == Algorithms::round_robin) {
					Core* core = getCpuCore(core_position);

					if (core->decreaseQuantumTime(1) < 0 || getCpuCoreProcess(core_position)->decrease_time(1) == 0) {
						deschedule_process(core_position);
						core->reset_quantum();
					}
				}
				else {
					Process* process = getCpuCoreProcess(core_position);
					if (process->decrease_time(1) == 0)
						deschedule_process(core_position);
				}
			}
		}
	}
}

void Scheduler::run()
{
	/*vector<thread> cores_thread;

	for (int i = 0; i < qtd_cores; i++)
		cores_thread.push_back(thread(&Scheduler::process_core_multithread, this, i));
	for (thread& t : cores_thread)
		t.join();*/

	thread singlethread(&Scheduler::process_core_singlethread, this);
	singlethread.join();
}

void Scheduler::printReadyQueue()
{
	if (printing == false) {
		printing = true;
		cout << "A: ";
		if (ready_queue.size() > 0) {
			for (Process* p : ready_queue) {
				cout << "[ " << p->get_total_time() << " , " << p->get_remaining_time() << "] , ";
			}
		}
		cout << endl;
		printing = false;
	}
}

void Scheduler::mostrar_queue()
{
	for (Process* p : ready_queue) {
		cout << p->get_process_id() << endl;
	}
}

list<Process*> Scheduler::get_queue()
{
	return list<Process*>();
}

void Scheduler::insertOnSort(Process* new_process)
{
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

void Scheduler::setCpuCore(int position, Process* process)
{
	this->cpu->getCores()[position]->setProcess(process);
}

Process* Scheduler::getCpuCoreProcess(int position)
{
	return this->cpu->getCores()[position]->getProcess();
}

Core* Scheduler::getCpuCore(int position)
{
	return this->cpu->getCores()[position];
}

void Scheduler::schedule_process(int position)
{
	if (ready_queue.size() > 0) {

		Process* aux = this->ready_queue.front();
		this->ready_queue.pop_front();

		aux->set_state(Process::States::running);
		setCpuCore(position, aux);
	}
}

void Scheduler::deschedule_process(int position)
{
	Process* process = getCpuCoreProcess(position);
	cpu->getCore(position)->setProcess(NULL);

	if (process->get_remaining_time() > 0) {
		process->set_state(Process::States::ready);
		insert_process(process);
	}
	else {
		process->set_state(Process::States::terminated);
	}
}