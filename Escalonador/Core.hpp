#include "Process.h"
#pragma once


class Core
{
private:
	Process* process;
	int position;
	int quantum;
	int quantumTimer;
public:
	Core(Process* process,int position, int quantum) {
		this->process = process;
		this->position = position;
		this->quantum = quantum;
		this->quantumTimer = quantum;
	}


	int decreaseQuantumTime(int time) {
		quantumTimer--;
		return quantumTimer;
	}

	void reset_quantum() {
		quantumTimer = quantum;
	}

	Process* getProcess() {
		return process;
	}

	int getPosicao() {
		return position;
	}

	void setProcess(Process* process) {
		this->process = process;
	}

	bool coreIsEmpty() {
		return (process == NULL);
	}
};
