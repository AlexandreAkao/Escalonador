#include <list> 
#include <iostream> 
#include "Process.h"
#include "Scheduler.h"
using namespace std;
int main(){

	list<Process*> a;

	a.push_back(new Process(1,3, Process::States::ready));
	a.push_back(new Process(2, 2, Process::States::ready));
	Process* c = new Process(3, 1, Process::States::ready);
	Process* d = new Process(4, 4, Process::States::ready);

	Scheduler* b = new 	Scheduler(Scheduler::Algorithms::sjf, 1, a);
	b->insert_process(c);
	b->insert_process(d);

	b->mostrar_queue();
		
	return 0;
}