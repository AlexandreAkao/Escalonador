#include "Process.h"

using namespace std;

Process::Process(int process_id, int total_time, States state) {
	this->process_id = process_id;
	this->total_time = total_time;
	this->remaining_time = total_time;
	this->state = state;
	this->dinamicProb = 80;
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

Process::States Process::getState()
{
	return this->state;
}

void Process::set_state(States state)
{
	this->state = state;
}

void Process::set_remaining_time(int time)
{
	this->remaining_time = time;
}

int Process::decrease_time(int time) {
	this->remaining_time -= time;
	return remaining_time;
}

void Process::setMemoryPointers(MemoryBlock* mb)
{
	this->memoryPointers.push_back(mb);
}

bool Process::generateRandomMemory(bool isStatic, MemoryManager* memManager)
{
	int memoryValue =  rand() % 4096 + 1;
 
	if (! isStatic)
	{
		if (rand() % 100 > this->dinamicProb) {
			memoryValue=  memoryValue;
		}
		else {
			memoryValue = 0;
		}
	}
	
	if (memoryValue != 0) {
		if (memManager->checkFreeMemory(memoryValue)) {
			MemoryBlock* a = memManager->malloc(memoryValue);
			this->setMemoryPointers(a);
			return true;
		}
		else {
			return false;
		}
	}

	return true;

}

vector<MemoryBlock*> Process::abortProcess()
{
	this->state = Process::States::aborted;
	return this->memoryPointers;
}

void Process::removeMemoryPointers() {
	this->memoryPointers.clear();
}
