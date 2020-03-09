#include "MainScreen.h"

void Escalonador::MainScreen::changeLabels(Process* process) {
	this->idProcessoLabel->Text = System::Convert::ToString(process->get_process_id());
	this->tempoProcessoLabel->Text = System::Convert::ToString(process->get_remaining_time());
	this->statusProcessoLabel->Text = (process->getState() == Process::States::ready) ? "ready": (process->getState() == Process::States::terminated)? "terminated" : "processing";
}