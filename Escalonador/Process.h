#pragma once
#ifndef Process_H
#define Process_H
using namespace std;
class Process
{
public:
	enum class States
	{
		ready, running, terminated
	};

	Process(int process_id, int total_time, States state);
	~Process();

	int get_remaining_time();

	int get_total_time();

	int get_process_id();

	States getState();

	void set_state(States state);
	void set_remaining_time(int time);

	int decrease_time(int time);

private:
	int process_id;
	int total_time;
	int remaining_time;
	States state;


};

#endif



