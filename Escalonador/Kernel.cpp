#include "Kernel.h"

Kernel::Kernel(int quantum, int processor_cores_number, Scheduler::Algorithms algorithm)
{
	this->cpu = new CPU(processor_cores_number);
	this->scheduler = new Scheduler(algorithm,processor_cores_number,quantum, cpu);
	
}

Kernel::~Kernel()
{
}

void Kernel::run()
{
	thread scheduler_thread(&Scheduler::run,scheduler);
	scheduler_thread.join();
}

list<Process*> Kernel::get_process_control_table()
{
	return this->process_control_table;
}

void Kernel::create_process(int process_id, int total_time, Process::States state)
{
	this->process_control_table.push_back(new Process(process_id,total_time,state));
}

void Kernel::kill_process(Process* process){
	this->process_control_table.remove(process);
	delete(process);
}

void Kernel::run_process(Process* process)
{
	scheduler->insert_process(process);
}
