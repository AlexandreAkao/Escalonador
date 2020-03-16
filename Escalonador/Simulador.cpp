#include <list> 
#include <iostream> 
#include <time.h>
#include <thread> 
//#include "MainScreen.h"
//#include "MainScreen.h"
#include "Process.h"
#include "Scheduler.hpp"
#include "Kernel.h"



using namespace std;
class Simulador{
private:
	int quantum, processor_cores_number, nmbProcess;
	Scheduler::Algorithms alg;

public:
	int idTraker = 0;
	Kernel* kernel = NULL;

	Simulador(int quantum, int processor_cores_number,int nmbProcess, Scheduler::Algorithms alg) {
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
		/*Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);*/

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
				this_thread::sleep_for(chrono::seconds(3));
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

int main(){
	srand(time(NULL));

	Scheduler::Algorithms alg = Scheduler::Algorithms::round_robin;


	int quantum = 4;
	int processor_cores_number = 3;
	int nmbProcess = 1;
	Simulador* simulador = new Simulador(quantum,processor_cores_number,nmbProcess,alg);
	simulador->start();
	//thread simuladorThread(&Simulador::start,simulador);

	//cout << "fasdfasfas" << endl;

	//Escalonador::MainScreen form;
	//Application::Run(% form);

	//simuladorThread.join();

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