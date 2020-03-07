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
			this->cores.push_back(new Core(nullptr, i));

		this->qtd_cores = qtd_cores;
	}
	vector<Core*> getCores() {
		return cores;
	}
	bool coreIsEmpty(int position) {
		return cores[position]->coreIsEmpty();
	}
};

