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




