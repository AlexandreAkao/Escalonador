#include "Process.h"
#pragma once


class Core
{
private:
	Process* process;
	int position;
public:
	Core(Process* process,int position) {
		this->process = process;
		this->position = position;
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
