
#pragma once
#include "Scheduler.hpp"
#include "Core.hpp"

#ifndef CentralPu_H
#define CentralPu_H

class CentralPu
{
public:
	CentralPu(Scheduler* scheduler, int qtd_cores)
	{
		for (int i = 0; i < qtd_cores; i++)
			this->cores.push_back(new Core(NULL, i, scheduler));

		this->qtd_cores = qtd_cores;
	}
	vector<Core*> getCores() {
		return cores;
	}
	bool coreIsEmpty(int position) {
	return cores[position]->coreIsEmpty();
}

private:
	vector<Core*> cores;
	int qtd_cores;
};
#endif

