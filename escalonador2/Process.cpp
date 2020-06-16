#include "Process.h"

using namespace std;

Process::Process(int process_id, int total_time, States state, MemoryManager* memoryManager) {
	this->process_id = process_id;
	this->total_time = total_time;
	this->remaining_time = total_time;
	this->state = state;
	this->dinamicProb = 80;
	this->memoryManager = memoryManager;
}

void Process::printProcess() {
	cout << "id: " << this->process_id << endl;
	cout << "tempo inicial: " << this->total_time << endl;
	cout << "tempo remanecente: " << this->remaining_time << endl;

	if (this->state == Process::States::running)
		cout << "Status : running" << endl;
	else if (this->state == Process::States::terminated)
		cout << "Status : terminitated" << endl;
	else
		cout << "Status : ready" << endl;
}

string Process::getStatusAsString() {
	if (this->state == Process::States::running)
		return "running";
	else if (this->state == Process::States::terminated)
		return "terminatated";
	else
		return "ready";
}

int Process::get_remaining_time() {
	return this->remaining_time;
}

int Process::get_total_time() {
	return total_time;
}

int Process::get_process_id() {
	return process_id;
}

Process::States Process::getState() {
	return this->state;
}

void Process::set_state(States state) {
	this->state = state;
}

void Process::set_remaining_time(int time) {
	this->remaining_time = time;
}

int Process::decrease_time(int time) {
	this->remaining_time -= time;
	return remaining_time;
}

void Process::setMemoryPointers(MemoryBlock* mb) {
	this->memoryPointers.push_back(mb);
}

int Process::getTotalMemory() {
	return this->totalMemory;
}

bool Process::generateRandomMemory(bool isStatic) {
	int memoryValue = rand() % 4096 + 1;
	
	if (!isStatic && rand() % 100 < this->dinamicProb) {
		//cout << "*******************" << memoryValue << "*******************" << endl;
		return true;
	}
	
	if (this->memoryManager->checkFreeMemory(memoryValue)) {
		MemoryBlock* newBlock = this->memoryManager->malloc(memoryValue);
		this->setMemoryPointers(newBlock);
		this->totalMemory += memoryValue;
		//cout << "*******************" << memoryValue << "*******************" << endl;

		return true;
	} else {
		return false;
	}
}

void Process::abortProcess() {
	this->state = Process::States::aborted;
	this->freeMemoryPointers();
}

void Process::freeMemoryPointers() {
	for (MemoryBlock* mb: this->memoryPointers) {
		this->memoryManager->free(mb);
	}
	this->memoryPointers.clear();
}


