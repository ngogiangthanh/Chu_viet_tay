#pragma once
#include <stdio.h>
#include <iostream>
#include <string>

namespace OpenCV_JP {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for frmSegmentation
	/// </summary>
	public ref class frmSegmentation : public System::Windows::Forms::Form
	{
	public: static bool instance = false;
	public:
		frmSegmentation(void)
		{
			InitializeComponent();

			this->cbbSegMAF->SelectedIndex = 2;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmSegmentation()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  pnSegmentation;
	private: System::Windows::Forms::Button^  btnMAFSeg;
	private: System::Windows::Forms::Button^  btnSegSave;
	private: System::Windows::Forms::Button^  btnSegConnectValley;
	private: System::Windows::Forms::Button^  btnFindValley;
	private: System::Windows::Forms::Button^  btnKhoiTao;
	private: System::Windows::Forms::GroupBox^  gbSegMAF;
	private: System::Windows::Forms::Button^  btnSegSetMAF;
	private: System::Windows::Forms::Button^  btnSegResetMAF;
	private: System::Windows::Forms::Label^  lbSegMAFKernel;
	private: System::Windows::Forms::ComboBox^  cbbSegMAF;
	private: System::Windows::Forms::GroupBox^  gbSegHeighOfLine;
	private: System::Windows::Forms::Button^  btnSegSetHeighOfLine;
	private: System::Windows::Forms::Button^  btnSegResetHeighOfLine;
	private: System::Windows::Forms::Label^  lbSegValHeigh;
	private: System::Windows::Forms::Label^  lbMaxHeigh;
	private: System::Windows::Forms::Label^  lbMinHeigh;
	private: System::Windows::Forms::TrackBar^  trbSegHeighOfLine;
	private: System::Windows::Forms::Button^  btnOpenOutput;
	private: System::Windows::Forms::Button^  btnOpenInput;
	private: System::Windows::Forms::Label^  lbOutput;
	private: System::Windows::Forms::Label^  lbInput;
	private: System::Windows::Forms::Label^  lbTittleOutput;
	private: System::Windows::Forms::Label^  lbInputTittle;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;
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
			this->pnSegmentation = (gcnew System::Windows::Forms::Panel());
			this->btnMAFSeg = (gcnew System::Windows::Forms::Button());
			this->btnSegSave = (gcnew System::Windows::Forms::Button());
			this->btnSegConnectValley = (gcnew System::Windows::Forms::Button());
			this->btnFindValley = (gcnew System::Windows::Forms::Button());
			this->btnKhoiTao = (gcnew System::Windows::Forms::Button());
			this->gbSegMAF = (gcnew System::Windows::Forms::GroupBox());
			this->btnSegSetMAF = (gcnew System::Windows::Forms::Button());
			this->btnSegResetMAF = (gcnew System::Windows::Forms::Button());
			this->lbSegMAFKernel = (gcnew System::Windows::Forms::Label());
			this->cbbSegMAF = (gcnew System::Windows::Forms::ComboBox());
			this->gbSegHeighOfLine = (gcnew System::Windows::Forms::GroupBox());
			this->btnSegSetHeighOfLine = (gcnew System::Windows::Forms::Button());
			this->btnSegResetHeighOfLine = (gcnew System::Windows::Forms::Button());
			this->lbSegValHeigh = (gcnew System::Windows::Forms::Label());
			this->lbMaxHeigh = (gcnew System::Windows::Forms::Label());
			this->lbMinHeigh = (gcnew System::Windows::Forms::Label());
			this->trbSegHeighOfLine = (gcnew System::Windows::Forms::TrackBar());
			this->btnOpenOutput = (gcnew System::Windows::Forms::Button());
			this->btnOpenInput = (gcnew System::Windows::Forms::Button());
			this->lbOutput = (gcnew System::Windows::Forms::Label());
			this->lbInput = (gcnew System::Windows::Forms::Label());
			this->lbTittleOutput = (gcnew System::Windows::Forms::Label());
			this->lbInputTittle = (gcnew System::Windows::Forms::Label());
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->pnSegmentation->SuspendLayout();
			this->gbSegMAF->SuspendLayout();
			this->gbSegHeighOfLine->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSegHeighOfLine))->BeginInit();
			this->SuspendLayout();
			// 
			// pnSegmentation
			// 
			this->pnSegmentation->Controls->Add(this->btnMAFSeg);
			this->pnSegmentation->Controls->Add(this->btnSegSave);
			this->pnSegmentation->Controls->Add(this->btnSegConnectValley);
			this->pnSegmentation->Controls->Add(this->btnFindValley);
			this->pnSegmentation->Controls->Add(this->btnKhoiTao);
			this->pnSegmentation->Controls->Add(this->gbSegMAF);
			this->pnSegmentation->Controls->Add(this->gbSegHeighOfLine);
			this->pnSegmentation->Controls->Add(this->btnOpenOutput);
			this->pnSegmentation->Controls->Add(this->btnOpenInput);
			this->pnSegmentation->Controls->Add(this->lbOutput);
			this->pnSegmentation->Controls->Add(this->lbInput);
			this->pnSegmentation->Controls->Add(this->lbTittleOutput);
			this->pnSegmentation->Controls->Add(this->lbInputTittle);
			this->pnSegmentation->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnSegmentation->Location = System::Drawing::Point(0, 0);
			this->pnSegmentation->Name = L"pnSegmentation";
			this->pnSegmentation->Size = System::Drawing::Size(702, 495);
			this->pnSegmentation->TabIndex = 0;
			// 
			// btnMAFSeg
			// 
			this->btnMAFSeg->Location = System::Drawing::Point(259, 435);
			this->btnMAFSeg->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnMAFSeg->Name = L"btnMAFSeg";
			this->btnMAFSeg->Size = System::Drawing::Size(105, 49);
			this->btnMAFSeg->TabIndex = 47;
			this->btnMAFSeg->Text = L"MAF";
			this->btnMAFSeg->UseVisualStyleBackColor = true;
			this->btnMAFSeg->Click += gcnew System::EventHandler(this, &frmSegmentation::btnMAFSeg_Click);
			// 
			// btnSegSave
			// 
			this->btnSegSave->Location = System::Drawing::Point(585, 435);
			this->btnSegSave->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnSegSave->Name = L"btnSegSave";
			this->btnSegSave->Size = System::Drawing::Size(105, 49);
			this->btnSegSave->TabIndex = 46;
			this->btnSegSave->Text = L"Save";
			this->btnSegSave->UseVisualStyleBackColor = true;
			this->btnSegSave->Click += gcnew System::EventHandler(this, &frmSegmentation::btnSegSave_Click);
			// 
			// btnSegConnectValley
			// 
			this->btnSegConnectValley->Location = System::Drawing::Point(476, 435);
			this->btnSegConnectValley->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnSegConnectValley->Name = L"btnSegConnectValley";
			this->btnSegConnectValley->Size = System::Drawing::Size(105, 49);
			this->btnSegConnectValley->TabIndex = 45;
			this->btnSegConnectValley->Text = L"Connect Valley";
			this->btnSegConnectValley->UseVisualStyleBackColor = true;
			this->btnSegConnectValley->Click += gcnew System::EventHandler(this, &frmSegmentation::btnSegConnectValley_Click);
			// 
			// btnFindValley
			// 
			this->btnFindValley->Location = System::Drawing::Point(367, 435);
			this->btnFindValley->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnFindValley->Name = L"btnFindValley";
			this->btnFindValley->Size = System::Drawing::Size(105, 49);
			this->btnFindValley->TabIndex = 44;
			this->btnFindValley->Text = L"Find Valley";
			this->btnFindValley->UseVisualStyleBackColor = true;
			this->btnFindValley->Click += gcnew System::EventHandler(this, &frmSegmentation::btnFindValley_Click);
			// 
			// btnKhoiTao
			// 
			this->btnKhoiTao->Location = System::Drawing::Point(150, 435);
			this->btnKhoiTao->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnKhoiTao->Name = L"btnKhoiTao";
			this->btnKhoiTao->Size = System::Drawing::Size(105, 49);
			this->btnKhoiTao->TabIndex = 43;
			this->btnKhoiTao->Text = L"Init";
			this->btnKhoiTao->UseVisualStyleBackColor = true;
			this->btnKhoiTao->Click += gcnew System::EventHandler(this, &frmSegmentation::btnKhoiTao_Click);
			// 
			// gbSegMAF
			// 
			this->gbSegMAF->Controls->Add(this->btnSegSetMAF);
			this->gbSegMAF->Controls->Add(this->btnSegResetMAF);
			this->gbSegMAF->Controls->Add(this->lbSegMAFKernel);
			this->gbSegMAF->Controls->Add(this->cbbSegMAF);
			this->gbSegMAF->Location = System::Drawing::Point(12, 99);
			this->gbSegMAF->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->gbSegMAF->Name = L"gbSegMAF";
			this->gbSegMAF->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->gbSegMAF->Size = System::Drawing::Size(678, 82);
			this->gbSegMAF->TabIndex = 42;
			this->gbSegMAF->TabStop = false;
			this->gbSegMAF->Text = L"Moving Average Filter";
			// 
			// btnSegSetMAF
			// 
			this->btnSegSetMAF->Location = System::Drawing::Point(569, 16);
			this->btnSegSetMAF->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnSegSetMAF->Name = L"btnSegSetMAF";
			this->btnSegSetMAF->Size = System::Drawing::Size(105, 30);
			this->btnSegSetMAF->TabIndex = 33;
			this->btnSegSetMAF->Text = L"Set";
			this->btnSegSetMAF->UseVisualStyleBackColor = true;
			this->btnSegSetMAF->Click += gcnew System::EventHandler(this, &frmSegmentation::btnSegSetMAF_Click);
			// 
			// btnSegResetMAF
			// 
			this->btnSegResetMAF->Location = System::Drawing::Point(569, 47);
			this->btnSegResetMAF->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnSegResetMAF->Name = L"btnSegResetMAF";
			this->btnSegResetMAF->Size = System::Drawing::Size(105, 30);
			this->btnSegResetMAF->TabIndex = 32;
			this->btnSegResetMAF->Text = L"Reset";
			this->btnSegResetMAF->UseVisualStyleBackColor = true;
			this->btnSegResetMAF->Click += gcnew System::EventHandler(this, &frmSegmentation::btnSegResetMAF_Click);
			// 
			// lbSegMAFKernel
			// 
			this->lbSegMAFKernel->AutoSize = true;
			this->lbSegMAFKernel->Location = System::Drawing::Point(19, 31);
			this->lbSegMAFKernel->Name = L"lbSegMAFKernel";
			this->lbSegMAFKernel->Size = System::Drawing::Size(48, 15);
			this->lbSegMAFKernel->TabIndex = 27;
			this->lbSegMAFKernel->Text = L"Kernel";
			// 
			// cbbSegMAF
			// 
			this->cbbSegMAF->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbSegMAF->FormattingEnabled = true;
			this->cbbSegMAF->Items->AddRange(gcnew cli::array< System::Object^  >(11) {
				L"5", L"7", L"9", L"11", L"13", L"15", L"17", L"19",
					L"21", L"23", L"25"
			});
			this->cbbSegMAF->Location = System::Drawing::Point(85, 28);
			this->cbbSegMAF->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->cbbSegMAF->Name = L"cbbSegMAF";
			this->cbbSegMAF->Size = System::Drawing::Size(96, 23);
			this->cbbSegMAF->TabIndex = 25;
			// 
			// gbSegHeighOfLine
			// 
			this->gbSegHeighOfLine->Controls->Add(this->btnSegSetHeighOfLine);
			this->gbSegHeighOfLine->Controls->Add(this->btnSegResetHeighOfLine);
			this->gbSegHeighOfLine->Controls->Add(this->lbSegValHeigh);
			this->gbSegHeighOfLine->Controls->Add(this->lbMaxHeigh);
			this->gbSegHeighOfLine->Controls->Add(this->lbMinHeigh);
			this->gbSegHeighOfLine->Controls->Add(this->trbSegHeighOfLine);
			this->gbSegHeighOfLine->Location = System::Drawing::Point(12, 186);
			this->gbSegHeighOfLine->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->gbSegHeighOfLine->Name = L"gbSegHeighOfLine";
			this->gbSegHeighOfLine->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->gbSegHeighOfLine->Size = System::Drawing::Size(678, 82);
			this->gbSegHeighOfLine->TabIndex = 41;
			this->gbSegHeighOfLine->TabStop = false;
			this->gbSegHeighOfLine->Text = L"Heigh of line";
			// 
			// btnSegSetHeighOfLine
			// 
			this->btnSegSetHeighOfLine->Location = System::Drawing::Point(566, 15);
			this->btnSegSetHeighOfLine->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnSegSetHeighOfLine->Name = L"btnSegSetHeighOfLine";
			this->btnSegSetHeighOfLine->Size = System::Drawing::Size(105, 30);
			this->btnSegSetHeighOfLine->TabIndex = 32;
			this->btnSegSetHeighOfLine->Text = L"Set";
			this->btnSegSetHeighOfLine->UseVisualStyleBackColor = true;
			this->btnSegSetHeighOfLine->Click += gcnew System::EventHandler(this, &frmSegmentation::btnSegSetHeighOfLine_Click);
			// 
			// btnSegResetHeighOfLine
			// 
			this->btnSegResetHeighOfLine->Location = System::Drawing::Point(566, 46);
			this->btnSegResetHeighOfLine->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnSegResetHeighOfLine->Name = L"btnSegResetHeighOfLine";
			this->btnSegResetHeighOfLine->Size = System::Drawing::Size(105, 30);
			this->btnSegResetHeighOfLine->TabIndex = 31;
			this->btnSegResetHeighOfLine->Text = L"Reset";
			this->btnSegResetHeighOfLine->UseVisualStyleBackColor = true;
			this->btnSegResetHeighOfLine->Click += gcnew System::EventHandler(this, &frmSegmentation::btnSegResetHeighOfLine_Click);
			// 
			// lbSegValHeigh
			// 
			this->lbSegValHeigh->AutoSize = true;
			this->lbSegValHeigh->Location = System::Drawing::Point(255, 12);
			this->lbSegValHeigh->Name = L"lbSegValHeigh";
			this->lbSegValHeigh->Size = System::Drawing::Size(23, 15);
			this->lbSegValHeigh->TabIndex = 23;
			this->lbSegValHeigh->Text = L"40";
			// 
			// lbMaxHeigh
			// 
			this->lbMaxHeigh->AutoSize = true;
			this->lbMaxHeigh->Location = System::Drawing::Point(517, 40);
			this->lbMaxHeigh->Name = L"lbMaxHeigh";
			this->lbMaxHeigh->Size = System::Drawing::Size(31, 15);
			this->lbMaxHeigh->TabIndex = 22;
			this->lbMaxHeigh->Text = L"128";
			// 
			// lbMinHeigh
			// 
			this->lbMinHeigh->AutoSize = true;
			this->lbMinHeigh->Location = System::Drawing::Point(24, 32);
			this->lbMinHeigh->Name = L"lbMinHeigh";
			this->lbMinHeigh->Size = System::Drawing::Size(15, 15);
			this->lbMinHeigh->TabIndex = 21;
			this->lbMinHeigh->Text = L"0";
			// 
			// trbSegHeighOfLine
			// 
			this->trbSegHeighOfLine->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->trbSegHeighOfLine->Location = System::Drawing::Point(40, 22);
			this->trbSegHeighOfLine->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->trbSegHeighOfLine->Maximum = 128;
			this->trbSegHeighOfLine->Name = L"trbSegHeighOfLine";
			this->trbSegHeighOfLine->Size = System::Drawing::Size(471, 56);
			this->trbSegHeighOfLine->TabIndex = 20;
			this->trbSegHeighOfLine->Value = 40;
			this->trbSegHeighOfLine->Scroll += gcnew System::EventHandler(this, &frmSegmentation::trbSegHeighOfLine_Scroll);
			// 
			// btnOpenOutput
			// 
			this->btnOpenOutput->Location = System::Drawing::Point(582, 49);
			this->btnOpenOutput->Name = L"btnOpenOutput";
			this->btnOpenOutput->Size = System::Drawing::Size(105, 30);
			this->btnOpenOutput->TabIndex = 11;
			this->btnOpenOutput->Text = L"Open";
			this->btnOpenOutput->UseVisualStyleBackColor = true;
			this->btnOpenOutput->Click += gcnew System::EventHandler(this, &frmSegmentation::btnOpenOutput_Click);
			// 
			// btnOpenInput
			// 
			this->btnOpenInput->Location = System::Drawing::Point(582, 13);
			this->btnOpenInput->Name = L"btnOpenInput";
			this->btnOpenInput->Size = System::Drawing::Size(105, 30);
			this->btnOpenInput->TabIndex = 10;
			this->btnOpenInput->Text = L"Open";
			this->btnOpenInput->UseVisualStyleBackColor = true;
			this->btnOpenInput->Click += gcnew System::EventHandler(this, &frmSegmentation::btnOpenInput_Click);
			// 
			// lbOutput
			// 
			this->lbOutput->AutoSize = true;
			this->lbOutput->Location = System::Drawing::Point(118, 56);
			this->lbOutput->Name = L"lbOutput";
			this->lbOutput->Size = System::Drawing::Size(101, 15);
			this->lbOutput->TabIndex = 9;
			this->lbOutput->Text = L"D:/Output_Seg";
			// 
			// lbInput
			// 
			this->lbInput->AutoSize = true;
			this->lbInput->Location = System::Drawing::Point(118, 19);
			this->lbInput->Name = L"lbInput";
			this->lbInput->Size = System::Drawing::Size(99, 15);
			this->lbInput->TabIndex = 8;
			this->lbInput->Text = L"D:/Output_Pre";
			// 
			// lbTittleOutput
			// 
			this->lbTittleOutput->AutoSize = true;
			this->lbTittleOutput->Location = System::Drawing::Point(17, 56);
			this->lbTittleOutput->Name = L"lbTittleOutput";
			this->lbTittleOutput->Size = System::Drawing::Size(95, 15);
			this->lbTittleOutput->TabIndex = 7;
			this->lbTittleOutput->Text = L"Output folder:";
			// 
			// lbInputTittle
			// 
			this->lbInputTittle->AutoSize = true;
			this->lbInputTittle->Location = System::Drawing::Point(17, 19);
			this->lbInputTittle->Name = L"lbInputTittle";
			this->lbInputTittle->Size = System::Drawing::Size(83, 15);
			this->lbInputTittle->TabIndex = 6;
			this->lbInputTittle->Text = L"Input folder:";
			// 
			// frmSegmentation
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(702, 495);
			this->Controls->Add(this->pnSegmentation);
			this->MaximumSize = System::Drawing::Size(720, 540);
			this->MinimumSize = System::Drawing::Size(720, 540);
			this->Name = L"frmSegmentation";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Segmentation";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &frmSegmentation::frmSegmentation_FormClosing);
			this->pnSegmentation->ResumeLayout(false);
			this->pnSegmentation->PerformLayout();
			this->gbSegMAF->ResumeLayout(false);
			this->gbSegMAF->PerformLayout();
			this->gbSegHeighOfLine->ResumeLayout(false);
			this->gbSegHeighOfLine->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSegHeighOfLine))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void btnSegSave_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnOpenOutput_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnSegSetMAF_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnSegResetMAF_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnSegSetHeighOfLine_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnSegResetHeighOfLine_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnKhoiTao_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnMAFSeg_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnFindValley_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnSegConnectValley_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnOpenInput_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void trbSegHeighOfLine_Scroll(System::Object^  sender, System::EventArgs^  e);
		System::Void frmSegmentation_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			frmSegmentation::instance = false;
};
};
}
