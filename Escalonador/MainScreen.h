#pragma once
#include "Process.h"

namespace Escalonador {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainScreen
	/// </summary>
	public ref class MainScreen : public System::Windows::Forms::Form
	{
	public:
		MainScreen(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void changeLabels(Process* process);
		//Simulador* sim = new Simulador(1,3,4,Scheduler::Algorithms::fifo);
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainScreen()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ idProcessoLabel;
	protected:

	private: System::Windows::Forms::Label^ statusProcessoLabel;
	private: System::Windows::Forms::Label^ tempoProcessoLabel;
	private: System::Windows::Forms::Button^ testButton;
	protected:





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->idProcessoLabel = (gcnew System::Windows::Forms::Label());
			this->statusProcessoLabel = (gcnew System::Windows::Forms::Label());
			this->tempoProcessoLabel = (gcnew System::Windows::Forms::Label());
			this->testButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// idProcessoLabel
			// 
			this->idProcessoLabel->AccessibleDescription = L"";
			this->idProcessoLabel->AutoSize = true;
			this->idProcessoLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->idProcessoLabel->Location = System::Drawing::Point(54, 36);
			this->idProcessoLabel->Name = L"idProcessoLabel";
			this->idProcessoLabel->Size = System::Drawing::Size(93, 32);
			this->idProcessoLabel->TabIndex = 0;
			this->idProcessoLabel->Text = L"label1";
			// 
			// statusProcessoLabel
			// 
			this->statusProcessoLabel->AutoSize = true;
			this->statusProcessoLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->statusProcessoLabel->Location = System::Drawing::Point(54, 191);
			this->statusProcessoLabel->Name = L"statusProcessoLabel";
			this->statusProcessoLabel->Size = System::Drawing::Size(93, 32);
			this->statusProcessoLabel->TabIndex = 3;
			this->statusProcessoLabel->Text = L"label4";
			// 
			// tempoProcessoLabel
			// 
			this->tempoProcessoLabel->AutoSize = true;
			this->tempoProcessoLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tempoProcessoLabel->Location = System::Drawing::Point(54, 117);
			this->tempoProcessoLabel->Name = L"tempoProcessoLabel";
			this->tempoProcessoLabel->Size = System::Drawing::Size(93, 32);
			this->tempoProcessoLabel->TabIndex = 4;
			this->tempoProcessoLabel->Text = L"label5";
			// 
			// testButton
			// 
			this->testButton->Location = System::Drawing::Point(78, 345);
			this->testButton->Name = L"testButton";
			this->testButton->Size = System::Drawing::Size(75, 23);
			this->testButton->TabIndex = 5;
			this->testButton->Text = L"button1";
			this->testButton->UseVisualStyleBackColor = true;
			this->testButton->Click += gcnew System::EventHandler(this, &MainScreen::testButton_Click);
			// 
			// MainScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(551, 426);
			this->Controls->Add(this->testButton);
			this->Controls->Add(this->tempoProcessoLabel);
			this->Controls->Add(this->statusProcessoLabel);
			this->Controls->Add(this->idProcessoLabel);
			this->Name = L"MainScreen";
			this->Text = L"Escalonador";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void testButton_Click(System::Object^ sender, System::EventArgs^ e) {
	this->idProcessoLabel->Text = "asasds";
}
};
}
