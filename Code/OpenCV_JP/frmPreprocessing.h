#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <filesystem>
#include <algorithm>
#include "Extent.h"
#include "Preprocess.h"
#include "Noise.h"
#define MAX_WIDTH 1366

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
			this->cbbConvert2Bin->SelectedIndex = 0;
			this->cbbMorphologyTransformations->SelectedIndex = 0;
			this->cbbSaltPepperFilter->SelectedIndex = 0;
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






	private: System::Windows::Forms::TrackBar^  trbMedian;

	private: System::Windows::Forms::Label^  lbOrder4;






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




	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker;
	private: System::Windows::Forms::Label^  lbInform;



	private: System::Windows::Forms::Label^  lbTitlePepperSalt;
	private: System::Windows::Forms::ComboBox^  cbbMorphologyTransformations;
	private: System::Windows::Forms::ComboBox^  cbbConvert2Bin;

	private: System::Windows::Forms::ComboBox^  cbbSaltPepperFilter;
	private: System::Windows::Forms::TrackBar^  trbNumNoise;
	private: System::Windows::Forms::Button^  btnAddNoise;
	private: System::Windows::Forms::Label^  lbNumberNoise;
	private: System::Windows::Forms::Label^  lbOrder3;





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
			this->lbNumberNoise = (gcnew System::Windows::Forms::Label());
			this->btnAddNoise = (gcnew System::Windows::Forms::Button());
			this->cbbMorphologyTransformations = (gcnew System::Windows::Forms::ComboBox());
			this->cbbConvert2Bin = (gcnew System::Windows::Forms::ComboBox());
			this->cbbSaltPepperFilter = (gcnew System::Windows::Forms::ComboBox());
			this->trbNumNoise = (gcnew System::Windows::Forms::TrackBar());
			this->lbTitlePepperSalt = (gcnew System::Windows::Forms::Label());
			this->lbInform = (gcnew System::Windows::Forms::Label());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->lbKernelOpening = (gcnew System::Windows::Forms::Label());
			this->lbKernelMedian = (gcnew System::Windows::Forms::Label());
			this->trbOpening = (gcnew System::Windows::Forms::TrackBar());
			this->trbMedian = (gcnew System::Windows::Forms::TrackBar());
			this->lbOrder4 = (gcnew System::Windows::Forms::Label());
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
			this->lbOrder3 = (gcnew System::Windows::Forms::Label());
			this->pnMain->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbNumNoise))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbOpening))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbMedian))->BeginInit();
			this->SuspendLayout();
			// 
			// pnMain
			// 
			this->pnMain->Controls->Add(this->lbNumberNoise);
			this->pnMain->Controls->Add(this->btnAddNoise);
			this->pnMain->Controls->Add(this->cbbMorphologyTransformations);
			this->pnMain->Controls->Add(this->cbbConvert2Bin);
			this->pnMain->Controls->Add(this->cbbSaltPepperFilter);
			this->pnMain->Controls->Add(this->trbNumNoise);
			this->pnMain->Controls->Add(this->lbTitlePepperSalt);
			this->pnMain->Controls->Add(this->lbInform);
			this->pnMain->Controls->Add(this->btnCancel);
			this->pnMain->Controls->Add(this->lbKernelOpening);
			this->pnMain->Controls->Add(this->lbKernelMedian);
			this->pnMain->Controls->Add(this->trbOpening);
			this->pnMain->Controls->Add(this->trbMedian);
			this->pnMain->Controls->Add(this->lbOrder4);
			this->pnMain->Controls->Add(this->lbOrder3);
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
			this->pnMain->Size = System::Drawing::Size(678, 480);
			this->pnMain->TabIndex = 0;
			// 
			// lbNumberNoise
			// 
			this->lbNumberNoise->AutoSize = true;
			this->lbNumberNoise->Location = System::Drawing::Point(253, 81);
			this->lbNumberNoise->Name = L"lbNumberNoise";
			this->lbNumberNoise->Size = System::Drawing::Size(23, 15);
			this->lbNumberNoise->TabIndex = 35;
			this->lbNumberNoise->Text = L"0%";
			// 
			// btnAddNoise
			// 
			this->btnAddNoise->Location = System::Drawing::Point(495, 107);
			this->btnAddNoise->Name = L"btnAddNoise";
			this->btnAddNoise->Size = System::Drawing::Size(105, 30);
			this->btnAddNoise->TabIndex = 34;
			this->btnAddNoise->Text = L"Add";
			this->btnAddNoise->UseVisualStyleBackColor = true;
			this->btnAddNoise->Click += gcnew System::EventHandler(this, &frmPreprocessing::btnAddNoise_Click);
			// 
			// cbbMorphologyTransformations
			// 
			this->cbbMorphologyTransformations->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbMorphologyTransformations->FormattingEnabled = true;
			this->cbbMorphologyTransformations->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"- Nothing -", L"Opening",
					L"Closing", L"Gradient", L"Top Hat", L"Black Hat"
			});
			this->cbbMorphologyTransformations->Location = System::Drawing::Point(495, 403);
			this->cbbMorphologyTransformations->Name = L"cbbMorphologyTransformations";
			this->cbbMorphologyTransformations->Size = System::Drawing::Size(160, 23);
			this->cbbMorphologyTransformations->TabIndex = 33;
			// 
			// cbbConvert2Bin
			// 
			this->cbbConvert2Bin->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbConvert2Bin->FormattingEnabled = true;
			this->cbbConvert2Bin->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"- Nothing -", L"Otsu thresholding", L"Adaptive thresholding" });
			this->cbbConvert2Bin->Location = System::Drawing::Point(495, 330);
			this->cbbConvert2Bin->Name = L"cbbConvert2Bin";
			this->cbbConvert2Bin->Size = System::Drawing::Size(160, 23);
			this->cbbConvert2Bin->TabIndex = 32;
			// 
			// cbbSaltPepperFilter
			// 
			this->cbbSaltPepperFilter->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbSaltPepperFilter->FormattingEnabled = true;
			this->cbbSaltPepperFilter->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"- Nothing -", L"Median", L"Adaptive median" });
			this->cbbSaltPepperFilter->Location = System::Drawing::Point(495, 184);
			this->cbbSaltPepperFilter->Name = L"cbbSaltPepperFilter";
			this->cbbSaltPepperFilter->Size = System::Drawing::Size(160, 23);
			this->cbbSaltPepperFilter->TabIndex = 30;
			// 
			// trbNumNoise
			// 
			this->trbNumNoise->Location = System::Drawing::Point(73, 99);
			this->trbNumNoise->Maximum = 100;
			this->trbNumNoise->Name = L"trbNumNoise";
			this->trbNumNoise->Size = System::Drawing::Size(380, 56);
			this->trbNumNoise->TabIndex = 29;
			this->trbNumNoise->Value = 1;
			this->trbNumNoise->Scroll += gcnew System::EventHandler(this, &frmPreprocessing::trbNumNoise_Scroll);
			// 
			// lbTitlePepperSalt
			// 
			this->lbTitlePepperSalt->AutoSize = true;
			this->lbTitlePepperSalt->Location = System::Drawing::Point(23, 107);
			this->lbTitlePepperSalt->Name = L"lbTitlePepperSalt";
			this->lbTitlePepperSalt->Size = System::Drawing::Size(58, 15);
			this->lbTitlePepperSalt->TabIndex = 27;
			this->lbTitlePepperSalt->Text = L"Impulse:";
			// 
			// lbInform
			// 
			this->lbInform->AutoSize = true;
			this->lbInform->Location = System::Drawing::Point(39, 439);
			this->lbInform->Name = L"lbInform";
			this->lbInform->Size = System::Drawing::Size(0, 15);
			this->lbInform->TabIndex = 24;
			// 
			// btnCancel
			// 
			this->btnCancel->Enabled = false;
			this->btnCancel->Location = System::Drawing::Point(459, 447);
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
			this->lbKernelOpening->Location = System::Drawing::Point(253, 385);
			this->lbKernelOpening->Name = L"lbKernelOpening";
			this->lbKernelOpening->Size = System::Drawing::Size(15, 15);
			this->lbKernelOpening->TabIndex = 22;
			this->lbKernelOpening->Text = L"3";
			// 
			// lbKernelMedian
			// 
			this->lbKernelMedian->AutoSize = true;
			this->lbKernelMedian->Location = System::Drawing::Point(253, 162);
			this->lbKernelMedian->Name = L"lbKernelMedian";
			this->lbKernelMedian->Size = System::Drawing::Size(15, 15);
			this->lbKernelMedian->TabIndex = 19;
			this->lbKernelMedian->Text = L"3";
			// 
			// trbOpening
			// 
			this->trbOpening->LargeChange = 1;
			this->trbOpening->Location = System::Drawing::Point(73, 403);
			this->trbOpening->Maximum = 3;
			this->trbOpening->Minimum = 1;
			this->trbOpening->Name = L"trbOpening";
			this->trbOpening->Size = System::Drawing::Size(380, 56);
			this->trbOpening->TabIndex = 18;
			this->trbOpening->Value = 1;
			this->trbOpening->Scroll += gcnew System::EventHandler(this, &frmPreprocessing::trbOpening_Scroll);
			// 
			// trbMedian
			// 
			this->trbMedian->Location = System::Drawing::Point(73, 180);
			this->trbMedian->Maximum = 3;
			this->trbMedian->Minimum = 1;
			this->trbMedian->Name = L"trbMedian";
			this->trbMedian->Size = System::Drawing::Size(380, 56);
			this->trbMedian->TabIndex = 15;
			this->trbMedian->Value = 1;
			this->trbMedian->Scroll += gcnew System::EventHandler(this, &frmPreprocessing::trbMedian_Scroll);
			// 
			// lbOrder4
			// 
			this->lbOrder4->AutoSize = true;
			this->lbOrder4->Location = System::Drawing::Point(23, 403);
			this->lbOrder4->Name = L"lbOrder4";
			this->lbOrder4->Size = System::Drawing::Size(33, 15);
			this->lbOrder4->TabIndex = 10;
			this->lbOrder4->Text = L"4 - ";
			// 
			// lbOrder1
			// 
			this->lbOrder1->AutoSize = true;
			this->lbOrder1->Location = System::Drawing::Point(23, 180);
			this->lbOrder1->Name = L"lbOrder1";
			this->lbOrder1->Size = System::Drawing::Size(28, 15);
			this->lbOrder1->TabIndex = 7;
			this->lbOrder1->Text = L"1 -";
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(570, 447);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(105, 30);
			this->btnStart->TabIndex = 6;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &frmPreprocessing::btnStart_Click);
			// 
			// btnOpenOutput
			// 
			this->btnOpenOutput->Location = System::Drawing::Point(550, 38);
			this->btnOpenOutput->Name = L"btnOpenOutput";
			this->btnOpenOutput->Size = System::Drawing::Size(105, 30);
			this->btnOpenOutput->TabIndex = 5;
			this->btnOpenOutput->Text = L"Open";
			this->btnOpenOutput->UseVisualStyleBackColor = true;
			this->btnOpenOutput->Click += gcnew System::EventHandler(this, &frmPreprocessing::btnOpenOutput_Click);
			// 
			// btnOpenInput
			// 
			this->btnOpenInput->Location = System::Drawing::Point(550, 2);
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
			this->lbOutput->Location = System::Drawing::Point(149, 46);
			this->lbOutput->Name = L"lbOutput";
			this->lbOutput->Size = System::Drawing::Size(72, 15);
			this->lbOutput->TabIndex = 3;
			this->lbOutput->Text = L"D:/Output";
			// 
			// lbInput
			// 
			this->lbInput->AutoSize = true;
			this->lbInput->Location = System::Drawing::Point(146, 10);
			this->lbInput->Name = L"lbInput";
			this->lbInput->Size = System::Drawing::Size(60, 15);
			this->lbInput->TabIndex = 2;
			this->lbInput->Text = L"D:/Input";
			// 
			// lbTittleOutput
			// 
			this->lbTittleOutput->AutoSize = true;
			this->lbTittleOutput->Location = System::Drawing::Point(44, 46);
			this->lbTittleOutput->Name = L"lbTittleOutput";
			this->lbTittleOutput->Size = System::Drawing::Size(95, 15);
			this->lbTittleOutput->TabIndex = 1;
			this->lbTittleOutput->Text = L"Output folder:";
			// 
			// lbInputTittle
			// 
			this->lbInputTittle->AutoSize = true;
			this->lbInputTittle->Location = System::Drawing::Point(44, 10);
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
			// lbOrder3
			// 
			this->lbOrder3->AutoSize = true;
			this->lbOrder3->Location = System::Drawing::Point(23, 329);
			this->lbOrder3->Name = L"lbOrder3";
			this->lbOrder3->Size = System::Drawing::Size(33, 15);
			this->lbOrder3->TabIndex = 9;
			this->lbOrder3->Text = L"3 - ";
			// 
			// frmPreprocessing
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(702, 495);
			this->Controls->Add(this->pnMain);
			this->HelpButton = true;
			this->MaximumSize = System::Drawing::Size(720, 540);
			this->MinimumSize = System::Drawing::Size(720, 540);
			this->Name = L"frmPreprocessing";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Pre-processing";
			this->pnMain->ResumeLayout(false);
			this->pnMain->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbNumNoise))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbOpening))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbMedian))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void btnOpenInput_Click(System::Object^  sender, System::EventArgs^  e);
		 System::Void btnCancel_Click(System::Object^  sender, System::EventArgs^  e);
		 System::Void btnStart_Click(System::Object^  sender, System::EventArgs^  e);
		 System::Void btnOpenOutput_Click(System::Object^  sender, System::EventArgs^  e);
		 System::Void trbNumNoise_Scroll(System::Object^  sender, System::EventArgs^  e);
		 System::Void trbOpening_Scroll(System::Object^  sender, System::EventArgs^  e);
		 System::Void trbMedian_Scroll(System::Object^  sender, System::EventArgs^  e); 
		 System::Void backgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
		 System::Void backgroundWorker_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
		 System::Void backgroundWorker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
		 System::Void btnAddNoise_Click(System::Object^  sender, System::EventArgs^  e);
		 //
private: Extent* extent = new Extent();
		 Preprocess* preprocess;
};
}
