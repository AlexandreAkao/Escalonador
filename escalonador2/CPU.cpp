#include "CPU.h"

CPU::CPU(int qtd_cores, int quantum)
{
	for (int i = 0; i < qtd_cores; i++)
		this->cores.push_back(new Core(NULL, i, quantum));

	this->qtd_cores = qtd_cores;
}

void CPU::printProcessos()
{
	cout << "R:";
	for (Core* c : cores) {
		if (c->getProcess() != NULL) {
			cout << " [" << c->getProcess()->get_process_id() << " , "
				<< c->getProcess()->get_remaining_time() << " , M: " << c->getProcess()->getTotalMemory() << "] , ";
		}
		else {
			cout << " [ -1 ,-1 , -1] , ";
		}
	}
	cout << endl;
}

vector<Core*> CPU::getCores()
{
	return cores;
}

Core* CPU::getCore(int i)
{
	return cores[i];
}

bool CPU::coreIsEmpty(int position)
{
	return cores[position]->coreIsEmpty();
}
