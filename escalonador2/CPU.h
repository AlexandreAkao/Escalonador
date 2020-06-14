#include <vector>
#include "Core.h"

#pragma once

class CPU {
private:
	vector<Core*> cores;
	int qtd_cores;
public:
	CPU(int qtd_cores, int quantum);
	void printProcessos();
	vector<Core*> getCores();
	Core* getCore(int i);
	bool coreIsEmpty(int position);
};

