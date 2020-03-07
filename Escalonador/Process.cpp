#include "Process.h"

using namespace std;

Process::Process(int process_id, int total_time, States state) {
	this->process_id = process_id;
	this->total_time = total_time;
	this->remaining_time = total_time;
	this->state = state;
}

Process::~Process() {}

int Process::get_remaining_time() {
	return remaining_time;
}

int Process::get_total_time() {
	return remaining_time;
}

int Process::get_process_id() {
	return process_id;
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




