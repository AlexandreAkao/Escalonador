#include <list> 
#include <iostream> 
#include <time.h>
#include <thread> 

#include "Process.h"
#include "Scheduler.h"
#include "Kernel.h"

using namespace std;

class Simulador {
private:
	int quantum, processor_cores_number, nmbProcess;
	Scheduler::Algorithms alg;
public:
	int idTraker = 0;
	Kernel* kernel = NULL;

	Simulador(int quantum, int processor_cores_number, int nmbProcess, Scheduler::Algorithms alg) {
		this->quantum = quantum;
		this->processor_cores_number = processor_cores_number;
		this->nmbProcess = nmbProcess;
		this->alg = alg;
	}

	struct processAux {
		int id;
		int lifeTime;
		Process::States state;
	};

	void start() {

		list<processAux> lista_process = batch_process_init(nmbProcess);
		thread kernelThread(&Simulador::run, this, lista_process);
		thread addingProcessThread(&Simulador::addNewProcess, this);

		kernelThread.join();
		addingProcessThread.join();
	}

	void run(list<processAux> lista_process) {
		kernel = new Kernel(quantum, processor_cores_number, alg);

		for (processAux aux : lista_process)
			kernel->create_process(aux.id, aux.lifeTime, aux.state);
		kernel->run();
	}

	processAux create_random_process() {
		processAux newProcess;
		newProcess.id = idTraker;
		idTraker++;
		newProcess.lifeTime = rand() % 20 + 1;
		newProcess.state = Process::States::ready;

		return newProcess;
	}

	void addNewProcess() {
		while (true)
		{
			if (kernel != NULL) {
				this_thread::sleep_for(chrono::seconds(4));
				processAux newProcess = create_random_process();

				//form.changeLabels(new Process(newProcess.id, newProcess.lifeTime, newProcess.state));
				kernel->create_process(newProcess.id, newProcess.lifeTime, newProcess.state);
			}
		}
	}

	list<processAux> batch_process_init(int nmbProcess) {
		list<processAux> processInitList;

		for (int i = 0; i < nmbProcess; i++)
			processInitList.push_back(create_random_process());

		return processInitList;
	}
};


//[STAThread]

int main() {
	srand(time(NULL));
 	Scheduler::Algorithms alg = Scheduler::Algorithms::round_robin;

	int quantum = 3;
	int processor_cores_number = 1;
	int nmbProcess = 20;

	Simulador* simulador = new Simulador(quantum, processor_cores_number, nmbProcess, alg);

	simulador->start();




	return 0;
}