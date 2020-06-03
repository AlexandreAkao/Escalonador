#include "Core.h"

Core::Core(Process* process, int position, int quantum) {
	this->process = process;
	this->position = position;
	this->quantum = quantum;
	this->quantumTimer = quantum;
}

int Core::decreaseQuantumTime(int time) {
	quantumTimer--;
	return quantumTimer;
}

void Core::reset_quantum() {
	quantumTimer = quantum;
}

Process* Core::getProcess() {
	return process;
}

int Core::getPosicao() {
	return position;
}

void Core::setProcess(Process* process) {
	this->process = process;
}

bool Core::coreIsEmpty() {
	return (process == NULL);
}

bool Core::genarateDynamicMemory() {
	return this->process->generateRandomMemory(false);
}
