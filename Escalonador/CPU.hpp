#include "Core.hpp"

#pragma once

class CPU
{
private:
	vector<Core*> cores;
	int qtd_cores;

public:
	CPU(int qtd_cores)
	{
		for (int i = 0; i < qtd_cores; i++)
			this->cores.push_back(new Core(NULL, i));

		this->qtd_cores = qtd_cores;
	}

	void printProcessos() {
		cout << "R:";
		for (Core* c : cores) {
			if (c->getProcess() != NULL) {
				cout << " [" << c->getProcess()->get_process_id() << " , " 
					<< c->getProcess()->get_remaining_time() << " , " << c->getProcess()->getStatusAsString() << "] , ";
			}
			else {
				cout << " [ 0 ,0 , 0] , ";
			}

			
		}
		cout<<endl;

	}


	vector<Core*> getCores() {
		return cores;
	}

	Core* getCore(int i) {
		return cores[i];
	}
	bool coreIsEmpty(int position) {
		return cores[position]->coreIsEmpty();
	}
};

