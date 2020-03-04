#include <list> 
#include <iostream> 
#include <time.h>
#include <thread> 

#include "Process.h"
#include "Scheduler.h"
#include "Kernel.h"

using namespace std;

struct processAux {
	int id;
	int lifeTime;
	Process::States state;
};

int idTraker = 0;
Kernel* kernel = NULL;


void run(int quantum, int processor_cores_number,Scheduler::Algorithms alg,list<processAux> lista_process) {
	kernel = new Kernel(quantum,processor_cores_number,alg);
	for (processAux aux : lista_process)
		kernel->create_process(aux.id, aux.lifeTime, aux.state);

	kernel->run();

}

processAux create_random_process() {

	processAux newProcess;
	newProcess.id = idTraker;
	idTraker++;
	newProcess.lifeTime = rand() % 20 + 1;
	int key = rand() % 3;
	newProcess.state = (key == 0) ? Process::States::ready : (key == 1) ? Process::States::running : Process::States::terminated;

	return newProcess;

}

void addNewProcess() {
	while (true)
	{	
		if (kernel != NULL) {
			this_thread::sleep_for(chrono::seconds(2));

			processAux newProcess = create_random_process();
			kernel->create_process(newProcess.id, newProcess.lifeTime, newProcess.state);

			/*for (Process* proc : kernel->get_process_control_table())
				cout << proc->get_process_id() << " " << proc->get_remaining_time() << endl;*/
		}
	}
}

list<processAux> batch_process_init(int nmbProcess) {
	list<processAux> processInitList;
	for (int i = 0; i < nmbProcess; i++)
		processInitList.push_back(create_random_process());
	return processInitList;
}


int main(){

	srand(time(NULL));

	Scheduler::Algorithms alg = Scheduler::Algorithms::fifo;
	int quantum = 3;
	int processor_cores_number = 2;
	int nmbProcess = 3;
	list<processAux> lista_process = batch_process_init(nmbProcess);
	thread kernel_thread(run,quantum, processor_cores_number, alg, lista_process);
	thread addingProcess_thread(addNewProcess);

	kernel_thread.join();
	addingProcess_thread.join();
	//list<Process*> a;
	//a.push_back(new Process(1,3, Process::States::ready));
	//a.push_back(new Process(2, 2, Process::States::ready));
	//Process* c = new Process(3, 1, Process::States::ready);
	//Process* d = new Process(4, 4, Process::States::ready);
	//Scheduler* b = new 	Scheduler(Scheduler::Algorithms::sjf, 1, a);
	//b->insert_process(c);
	//b->insert_process(d);
	//b->mostrar_queue();
		
	return 0;
}