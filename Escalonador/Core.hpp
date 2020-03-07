
#pragma once
#include "Scheduler.hpp"

#ifndef Core_H
#define Core_H
class Core
{
public:
	Core(Process* process,int position, Scheduler* scheduler) {
		this->process = process;
		this->position = position;
		this->scheduler = scheduler;
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
		return (process == NULL)? true: false;
	}

private:
	Process* process;
	int position;
	Scheduler* scheduler;
};
#endif
