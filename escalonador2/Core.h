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
	Core(Process* process, int position, int quantum);
	int decreaseQuantumTime(int time);
	void reset_quantum();
	Process* getProcess();
	int getPosicao();
	void setProcess(Process* process);
	bool coreIsEmpty();
	bool genarateDynamicMemory();
};
