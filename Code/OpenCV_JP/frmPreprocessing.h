#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <filesystem>
#include "Extent.h"
#include "Preprocess.h"

namespace OpenCV_JP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for frmPreprocessing
	/// </summary>
	public ref class frmPreprocessing : public System::Windows::Forms::Form
	{
	public:
		frmPreprocessing(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmPreprocessing()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  pnMain;
	private: System::Windows::Forms::TrackBar^  trbOpening;

	private: System::Windows::Forms::TrackBar^  trbThresholding;
	private: System::Windows::Forms::TrackBar^  trbLaplacian;



	private: System::Windows::Forms::TrackBar^  trbMedian;
	private: System::Windows::Forms::CheckBox^  cbOpening;



	private: System::Windows::Forms::CheckBox^  cbThresholding;

	private: System::Windows::Forms::CheckBox^  cbLaplacian;

	private: System::Windows::Forms::CheckBox^  cbMedian;
	private: System::Windows::Forms::Label^  lbOrder4;


	private: System::Windows::Forms::Label^  lbOrder3;

	private: System::Windows::Forms::Label^  lbOrder2;

	private: System::Windows::Forms::Label^  lbOrder1;

	private: System::Windows::Forms::Button^  btnStart;

	private: System::Windows::Forms::Button^  btnOpenOutput;

	private: System::Windows::Forms::Button^  btnOpenInput;
	private: System::Windows::Forms::Label^  lbOutput;


	private: System::Windows::Forms::Label^  lbInput;
	private: System::Windows::Forms::Label^  lbTittleOutput;


	private: System::Windows::Forms::Label^  lbInputTittle;
	private: System::Windows::Forms::Label^  lbKernelMedian;



	private: System::Windows::Forms::Label^  lbKernelOpening;

	private: System::Windows::Forms::Label^  lbValThresholding;

	private: System::Windows::Forms::Label^  lbKernelLaplacian;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker;

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
			this->pnMain = (gcnew System::Windows::Forms::Panel());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->lbKernelOpening = (gcnew System::Windows::Forms::Label());
			this->lbValThresholding = (gcnew System::Windows::Forms::Label());
			this->lbKernelLaplacian = (gcnew System::Windows::Forms::Label());
			this->lbKernelMedian = (gcnew System::Windows::Forms::Label());
			this->trbOpening = (gcnew System::Windows::Forms::TrackBar());
			this->trbThresholding = (gcnew System::Windows::Forms::TrackBar());
			this->trbLaplacian = (gcnew System::Windows::Forms::TrackBar());
			this->trbMedian = (gcnew System::Windows::Forms::TrackBar());
			this->cbOpening = (gcnew System::Windows::Forms::CheckBox());
			this->cbThresholding = (gcnew System::Windows::Forms::CheckBox());
			this->cbLaplacian = (gcnew System::Windows::Forms::CheckBox());
			this->cbMedian = (gcnew System::Windows::Forms::CheckBox());
			this->lbOrder4 = (gcnew System::Windows::Forms::Label());
			this->lbOrder3 = (gcnew System::Windows::Forms::Label());
			this->lbOrder2 = (gcnew System::Windows::Forms::Label());
			this->lbOrder1 = (gcnew System::Windows::Forms::Label());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->btnOpenOutput = (gcnew System::Windows::Forms::Button());
			this->btnOpenInput = (gcnew System::Windows::Forms::Button());
			this->lbOutput = (gcnew System::Windows::Forms::Label());
			this->lbInput = (gcnew System::Windows::Forms::Label());
			this->lbTittleOutput = (gcnew System::Windows::Forms::Label());
			this->lbInputTittle = (gcnew System::Windows::Forms::Label());
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->pnMain->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbOpening))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbThresholding))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbLaplacian))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbMedian))->BeginInit();
			this->SuspendLayout();
			// 
			// pnMain
			// 
			this->pnMain->Controls->Add(this->btnCancel);
			this->pnMain->Controls->Add(this->lbKernelOpening);
			this->pnMain->Controls->Add(this->lbValThresholding);
			this->pnMain->Controls->Add(this->lbKernelLaplacian);
			this->pnMain->Controls->Add(this->lbKernelMedian);
			this->pnMain->Controls->Add(this->trbOpening);
			this->pnMain->Controls->Add(this->trbThresholding);
			this->pnMain->Controls->Add(this->trbLaplacian);
			this->pnMain->Controls->Add(this->trbMedian);
			this->pnMain->Controls->Add(this->cbOpening);
			this->pnMain->Controls->Add(this->cbThresholding);
			this->pnMain->Controls->Add(this->cbLaplacian);
			this->pnMain->Controls->Add(this->cbMedian);
			this->pnMain->Controls->Add(this->lbOrder4);
			this->pnMain->Controls->Add(this->lbOrder3);
			this->pnMain->Controls->Add(this->lbOrder2);
			this->pnMain->Controls->Add(this->lbOrder1);
			this->pnMain->Controls->Add(this->btnStart);
			this->pnMain->Controls->Add(this->btnOpenOutput);
			this->pnMain->Controls->Add(this->btnOpenInput);
			this->pnMain->Controls->Add(this->lbOutput);
			this->pnMain->Controls->Add(this->lbInput);
			this->pnMain->Controls->Add(this->lbTittleOutput);
			this->pnMain->Controls->Add(this->lbInputTittle);
			this->pnMain->Location = System::Drawing::Point(12, 12);
			this->pnMain->Name = L"pnMain";
			this->pnMain->Size = System::Drawing::Size(598, 411);
			this->pnMain->TabIndex = 0;
			// 
			// btnCancel
			// 
			this->btnCancel->Location = System::Drawing::Point(376, 378);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(105, 30);
			this->btnCancel->TabIndex = 23;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			this->btnCancel->Click += gcnew System::EventHandler(this, &frmPreprocessing::btnCancel_Click);
			// 
			// lbKernelOpening
			// 
			this->lbKernelOpening->AutoSize = true;
			this->lbKernelOpening->Location = System::Drawing::Point(214, 321);
			this->lbKernelOpening->Name = L"lbKernelOpening";
			this->lbKernelOpening->Size = System::Drawing::Size(15, 15);
			this->lbKernelOpening->TabIndex = 22;
			this->lbKernelOpening->Text = L"3";
			// 
			// lbValThresholding
			// 
			this->lbValThresholding->AutoSize = true;
			this->lbValThresholding->Location = System::Drawing::Point(198, 250);
			this->lbValThresholding->Name = L"lbValThresholding";
			this->lbValThresholding->Size = System::Drawing::Size(31, 15);
			this->lbValThresholding->TabIndex = 21;
			this->lbValThresholding->Text = L"200";
			// 
			// lbKernelLaplacian
			// 
			this->lbKernelLaplacian->AutoSize = true;
			this->lbKernelLaplacian->Location = System::Drawing::Point(214, 175);
			this->lbKernelLaplacian->Name = L"lbKernelLaplacian";
			this->lbKernelLaplacian->Size = System::Drawing::Size(15, 15);
			this->lbKernelLaplacian->TabIndex = 20;
			this->lbKernelLaplacian->Text = L"3";
			// 
			// lbKernelMedian
			// 
			this->lbKernelMedian->AutoSize = true;
			this->lbKernelMedian->Location = System::Drawing::Point(214, 98);
			this->lbKernelMedian->Name = L"lbKernelMedian";
			this->lbKernelMedian->Size = System::Drawing::Size(15, 15);
			this->lbKernelMedian->TabIndex = 19;
			this->lbKernelMedian->Text = L"3";
			// 
			// trbOpening
			// 
			this->trbOpening->LargeChange = 1;
			this->trbOpening->Location = System::Drawing::Point(73, 339);
			this->trbOpening->Maximum = 3;
			this->trbOpening->Minimum = 1;
			this->trbOpening->Name = L"trbOpening";
			this->trbOpening->Size = System::Drawing::Size(252, 56);
			this->trbOpening->TabIndex = 18;
			this->trbOpening->Value = 1;
			this->trbOpening->Scroll += gcnew System::EventHandler(this, &frmPreprocessing::trbOpening_Scroll);
			// 
			// trbThresholding
			// 
			this->trbThresholding->LargeChange = 1;
			this->trbThresholding->Location = System::Drawing::Point(73, 262);
			this->trbThresholding->Maximum = 200;
			this->trbThresholding->Minimum = 128;
			this->trbThresholding->Name = L"trbThresholding";
			this->trbThresholding->Size = System::Drawing::Size(252, 56);
			this->trbThresholding->TabIndex = 17;
			this->trbThresholding->Value = 200;
			this->trbThresholding->Scroll += gcnew System::EventHandler(this, &frmPreprocessing::trbThresholding_Scroll);
			// 
			// trbLaplacian
			// 
			this->trbLaplacian->LargeChange = 1;
			this->trbLaplacian->Location = System::Drawing::Point(73, 191);
			this->trbLaplacian->Maximum = 3;
			this->trbLaplacian->Minimum = 1;
			this->trbLaplacian->Name = L"trbLaplacian";
			this->trbLaplacian->Size = System::Drawing::Size(252, 56);
			this->trbLaplacian->TabIndex = 16;
			this->trbLaplacian->Value = 1;
			this->trbLaplacian->Scroll += gcnew System::EventHandler(this, &frmPreprocessing::trbLaplacian_Scroll);
			// 
			// trbMedian
			// 
			this->trbMedian->Location = System::Drawing::Point(73, 116);
			this->trbMedian->Maximum = 3;
			this->trbMedian->Minimum = 1;
			this->trbMedian->Name = L"trbMedian";
			this->trbMedian->Size = System::Drawing::Size(252, 56);
			this->trbMedian->TabIndex = 15;
			this->trbMedian->Value = 1;
			this->trbMedian->Scroll += gcnew System::EventHandler(this, &frmPreprocessing::trbMedian_Scroll);
			// 
			// cbOpening
			// 
			this->cbOpening->AutoSize = true;
			this->cbOpening->Checked = true;
			this->cbOpening->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbOpening->Location = System::Drawing::Point(331, 339);
			this->cbOpening->Name = L"cbOpening";
			this->cbOpening->Size = System::Drawing::Size(210, 19);
			this->cbOpening->TabIndex = 14;
			this->cbOpening->Text = L"Make thick border (Opening)";
			this->cbOpening->UseVisualStyleBackColor = true;
			// 
			// cbThresholding
			// 
			this->cbThresholding->AutoSize = true;
			this->cbThresholding->Checked = true;
			this->cbThresholding->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbThresholding->Location = System::Drawing::Point(331, 265);
			this->cbThresholding->Name = L"cbThresholding";
			this->cbThresholding->Size = System::Drawing::Size(261, 19);
			this->cbThresholding->TabIndex = 13;
			this->cbThresholding->Text = L"Convert to bin-image (Thresholding)";
			this->cbThresholding->UseVisualStyleBackColor = true;
			// 
			// cbLaplacian
			// 
			this->cbLaplacian->AutoSize = true;
			this->cbLaplacian->Checked = true;
			this->cbLaplacian->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbLaplacian->Location = System::Drawing::Point(331, 197);
			this->cbLaplacian->Name = L"cbLaplacian";
			this->cbLaplacian->Size = System::Drawing::Size(191, 19);
			this->cbLaplacian->TabIndex = 12;
			this->cbLaplacian->Text = L"Detect border (Laplacian)";
			this->cbLaplacian->UseVisualStyleBackColor = true;
			// 
			// cbMedian
			// 
			this->cbMedian->AutoSize = true;
			this->cbMedian->Checked = true;
			this->cbMedian->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbMedian->Location = System::Drawing::Point(331, 120);
			this->cbMedian->Name = L"cbMedian";
			this->cbMedian->Size = System::Drawing::Size(213, 19);
			this->cbMedian->TabIndex = 11;
			this->cbMedian->Text = L"Remove salt pepper (Median)";
			this->cbMedian->UseVisualStyleBackColor = true;
			// 
			// lbOrder4
			// 
			this->lbOrder4->AutoSize = true;
			this->lbOrder4->Location = System::Drawing::Point(34, 343);
			this->lbOrder4->Name = L"lbOrder4";
			this->lbOrder4->Size = System::Drawing::Size(33, 15);
			this->lbOrder4->TabIndex = 10;
			this->lbOrder4->Text = L"4 - ";
			// 
			// lbOrder3
			// 
			this->lbOrder3->AutoSize = true;
			this->lbOrder3->Location = System::Drawing::Point(34, 269);
			this->lbOrder3->Name = L"lbOrder3";
			this->lbOrder3->Size = System::Drawing::Size(33, 15);
			this->lbOrder3->TabIndex = 9;
			this->lbOrder3->Text = L"3 - ";
			// 
			// lbOrder2
			// 
			this->lbOrder2->AutoSize = true;
			this->lbOrder2->Location = System::Drawing::Point(34, 201);
			this->lbOrder2->Name = L"lbOrder2";
			this->lbOrder2->Size = System::Drawing::Size(33, 15);
			this->lbOrder2->TabIndex = 8;
			this->lbOrder2->Text = L"2 - ";
			// 
			// lbOrder1
			// 
			this->lbOrder1->AutoSize = true;
			this->lbOrder1->Location = System::Drawing::Point(34, 120);
			this->lbOrder1->Name = L"lbOrder1";
			this->lbOrder1->Size = System::Drawing::Size(28, 15);
			this->lbOrder1->TabIndex = 7;
			this->lbOrder1->Text = L"1 -";
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(487, 378);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(105, 30);
			this->btnStart->TabIndex = 6;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &frmPreprocessing::btnStart_Click);
			// 
			// btnOpenOutput
			// 
			this->btnOpenOutput->Location = System::Drawing::Point(487, 55);
			this->btnOpenOutput->Name = L"btnOpenOutput";
			this->btnOpenOutput->Size = System::Drawing::Size(105, 30);
			this->btnOpenOutput->TabIndex = 5;
			this->btnOpenOutput->Text = L"Open";
			this->btnOpenOutput->UseVisualStyleBackColor = true;
			this->btnOpenOutput->Click += gcnew System::EventHandler(this, &frmPreprocessing::btnOpenOutput_Click);
			// 
			// btnOpenInput
			// 
			this->btnOpenInput->Location = System::Drawing::Point(487, 19);
			this->btnOpenInput->Name = L"btnOpenInput";
			this->btnOpenInput->Size = System::Drawing::Size(105, 30);
			this->btnOpenInput->TabIndex = 4;
			this->btnOpenInput->Text = L"Open";
			this->btnOpenInput->UseVisualStyleBackColor = true;
			this->btnOpenInput->Click += gcnew System::EventHandler(this, &frmPreprocessing::btnOpenInput_Click);
			// 
			// lbOutput
			// 
			this->lbOutput->AutoSize = true;
			this->lbOutput->Location = System::Drawing::Point(139, 67);
			this->lbOutput->Name = L"lbOutput";
			this->lbOutput->Size = System::Drawing::Size(72, 15);
			this->lbOutput->TabIndex = 3;
			this->lbOutput->Text = L"D:/Output";
			// 
			// lbInput
			// 
			this->lbInput->AutoSize = true;
			this->lbInput->Location = System::Drawing::Point(136, 27);
			this->lbInput->Name = L"lbInput";
			this->lbInput->Size = System::Drawing::Size(60, 15);
			this->lbInput->TabIndex = 2;
			this->lbInput->Text = L"D:/Input";
			// 
			// lbTittleOutput
			// 
			this->lbTittleOutput->AutoSize = true;
			this->lbTittleOutput->Location = System::Drawing::Point(34, 67);
			this->lbTittleOutput->Name = L"lbTittleOutput";
			this->lbTittleOutput->Size = System::Drawing::Size(95, 15);
			this->lbTittleOutput->TabIndex = 1;
			this->lbTittleOutput->Text = L"Output folder:";
			// 
			// lbInputTittle
			// 
			this->lbInputTittle->AutoSize = true;
			this->lbInputTittle->Location = System::Drawing::Point(34, 27);
			this->lbInputTittle->Name = L"lbInputTittle";
			this->lbInputTittle->Size = System::Drawing::Size(83, 15);
			this->lbInputTittle->TabIndex = 0;
			this->lbInputTittle->Text = L"Input folder:";
			// 
			// backgroundWorker
			// 
			this->backgroundWorker->WorkerReportsProgress = true;
			this->backgroundWorker->WorkerSupportsCancellation = true;
			this->backgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &frmPreprocessing::backgroundWorker_DoWork);
			this->backgroundWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &frmPreprocessing::backgroundWorker_ProgressChanged);
			this->backgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &frmPreprocessing::backgroundWorker_RunWorkerCompleted);
			// 
			// frmPreprocessing
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(622, 435);
			this->Controls->Add(this->pnMain);
			this->HelpButton = true;
			this->MaximumSize = System::Drawing::Size(640, 480);
			this->MinimumSize = System::Drawing::Size(640, 480);
			this->Name = L"frmPreprocessing";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Pre-processing";
			this->pnMain->ResumeLayout(false);
			this->pnMain->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbOpening))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbThresholding))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbLaplacian))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbMedian))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void btnOpenInput_Click(System::Object^  sender, System::EventArgs^  e);
		 System::Void btnCancel_Click(System::Object^  sender, System::EventArgs^  e);
		 System::Void btnStart_Click(System::Object^  sender, System::EventArgs^  e);
		 System::Void btnOpenOutput_Click(System::Object^  sender, System::EventArgs^  e);
		 System::Void trbOpening_Scroll(System::Object^  sender, System::EventArgs^  e);
		 System::Void trbLaplacian_Scroll(System::Object^  sender, System::EventArgs^  e);
		 System::Void trbThresholding_Scroll(System::Object^  sender, System::EventArgs^  e);
		 System::Void trbMedian_Scroll(System::Object^  sender, System::EventArgs^  e);
		 System::Void backgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
		 System::Void backgroundWorker_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
		 System::Void backgroundWorker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
		 //
private: Extent* extent = new Extent();
		 Preprocess* preprocess;

};
}
