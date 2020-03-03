
#include "Scheduler.h"

using namespace std;


void Scheduler::insert_process(Process* newProcess) {
		if (algorithm == Algorithms::sjf) {
			insertOnSort(newProcess);
		}
		else {
			ready_queue.push_back(newProcess);
		}
	}

void Scheduler::run()
{
}

Scheduler::Scheduler(Algorithms algotithm,int cores,list<Process*> ready_queue) {
	this->algorithm = algotithm;
	this->ready_queue = ready_queue;

	if (algotithm == Algorithms::sjf) {
		this->ready_queue.sort([](Process* lhs, Process* rhs) {return lhs->get_remaining_time() < rhs->get_remaining_time(); });
	}

	qtd_cores = cores;	
}

Scheduler::Scheduler(Algorithms algotithm, int cores, list<Process*> ready_queue,int quantum) {
	this->quantum = quantum;
	this->algorithm = algotithm;
	this->ready_queue = ready_queue;

	if (algotithm == Algorithms::sjf) {
		this->ready_queue.sort([](Process* lhs, Process* rhs) {return lhs->get_remaining_time() < rhs->get_remaining_time(); });
	}

	qtd_cores = cores;
}

void Scheduler::mostrar_queue() {
		for (Process* p : ready_queue) {
			cout << p->get_process_id() << endl;
		}
	}

void Scheduler::insertOnSort(Process* new_process) {
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

void Scheduler::fifo_scheduler()
{
}

void Scheduler::shortest_job_first()
{
}

void Scheduler::round_robin()
{
}

void Scheduler::schedule_process()
{
}

void Scheduler::deschedule_process()
{
}



