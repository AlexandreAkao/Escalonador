#include <list> 
#include <iostream> 
#include <thread> 
#include <time.h>

#include "Process.h"
#include "Scheduler.h"


#pragma once
#ifndef Kernel_H
#define Kernel_H
class Kernel
{
	public:
		Kernel(int quantum, int processor_cores_number, Scheduler::Algorithms algorithm);
		~Kernel();
		void run();
		list<Process*> get_process_control_table();
		void create_process(int process_id, int total_time, Process::States state);
		void run_process(Process* process);
		void kill_process(Process* process);


private:
	list<Process*> process_control_table;
	Scheduler* scheduler;
};
#endif

