#include "Process.h"

using namespace std;

Process::Process(int process_id, int total_time, States state) {
	this->process_id = process_id;
	this->total_time = total_time;
	this->remaining_time = total_time;
	this->state = state;
}

Process::~Process() {}

void Process::printProcess() {
	cout << "id: " << this->process_id << endl;
	cout << "tempo remanecente: " << this->remaining_time << endl;
	if (this->state == Process::States::running)
		cout << "Status : running" << endl;
	else if (this->state == Process::States::terminated) 
		cout << "Status : terminitated" << endl;
	else
		cout << "Status : ready" << endl;

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
	return time;
}




