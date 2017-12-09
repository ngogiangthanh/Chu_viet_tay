#pragma once
#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include <filesystem>
#include <fstream>
#include "Extent.h"
namespace fs = experimental::filesystem;

using namespace cv;
using namespace std;

namespace OpenCV_JP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for frmExtractFeatures
	/// </summary>
	public ref class frmExtractFeatures : public System::Windows::Forms::Form
	{
	public: static bool instance = false;
	public:
		frmExtractFeatures(void)
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
		~frmExtractFeatures()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  pbMain;
	protected:
	private: System::Windows::Forms::TextBox^  tbAlert;
	private: System::Windows::Forms::Button^  btnExtract;
	private: System::Windows::Forms::CheckBox^  cblw;
	private: System::Windows::Forms::CheckBox^  cbupw;
	private: System::Windows::Forms::Label^  lbOutput;
	private: System::Windows::Forms::Label^  lbOutputlabel;
	private: System::Windows::Forms::Button^  btnOpenOutput;
	private: System::Windows::Forms::CheckBox^  cbPp;
	private: System::Windows::Forms::Label^  lbInput;
	private: System::Windows::Forms::Label^  lbInputLabel;
	private: System::Windows::Forms::Button^  btnOpenInput;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;

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
			this->pbMain = (gcnew System::Windows::Forms::Panel());
			this->tbAlert = (gcnew System::Windows::Forms::TextBox());
			this->btnExtract = (gcnew System::Windows::Forms::Button());
			this->cblw = (gcnew System::Windows::Forms::CheckBox());
			this->cbupw = (gcnew System::Windows::Forms::CheckBox());
			this->lbOutput = (gcnew System::Windows::Forms::Label());
			this->lbOutputlabel = (gcnew System::Windows::Forms::Label());
			this->btnOpenOutput = (gcnew System::Windows::Forms::Button());
			this->cbPp = (gcnew System::Windows::Forms::CheckBox());
			this->lbInput = (gcnew System::Windows::Forms::Label());
			this->lbInputLabel = (gcnew System::Windows::Forms::Label());
			this->btnOpenInput = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->pbMain->SuspendLayout();
			this->SuspendLayout();
			// 
			// pbMain
			// 
			this->pbMain->Controls->Add(this->tbAlert);
			this->pbMain->Controls->Add(this->btnExtract);
			this->pbMain->Controls->Add(this->cblw);
			this->pbMain->Controls->Add(this->cbupw);
			this->pbMain->Controls->Add(this->lbOutput);
			this->pbMain->Controls->Add(this->lbOutputlabel);
			this->pbMain->Controls->Add(this->btnOpenOutput);
			this->pbMain->Controls->Add(this->cbPp);
			this->pbMain->Controls->Add(this->lbInput);
			this->pbMain->Controls->Add(this->lbInputLabel);
			this->pbMain->Controls->Add(this->btnOpenInput);
			this->pbMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pbMain->Location = System::Drawing::Point(0, 0);
			this->pbMain->Name = L"pbMain";
			this->pbMain->Size = System::Drawing::Size(618, 424);
			this->pbMain->TabIndex = 0;
			// 
			// tbAlert
			// 
			this->tbAlert->Location = System::Drawing::Point(12, 179);
			this->tbAlert->Multiline = true;
			this->tbAlert->Name = L"tbAlert";
			this->tbAlert->ReadOnly = true;
			this->tbAlert->Size = System::Drawing::Size(594, 233);
			this->tbAlert->TabIndex = 10;
			// 
			// btnExtract
			// 
			this->btnExtract->Location = System::Drawing::Point(498, 128);
			this->btnExtract->Name = L"btnExtract";
			this->btnExtract->Size = System::Drawing::Size(108, 33);
			this->btnExtract->TabIndex = 9;
			this->btnExtract->Text = L"Extract";
			this->btnExtract->UseVisualStyleBackColor = true;
			this->btnExtract->Click += gcnew System::EventHandler(this, &frmExtractFeatures::btnExtract_Click);
			// 
			// cblw
			// 
			this->cblw->AutoSize = true;
			this->cblw->Location = System::Drawing::Point(333, 133);
			this->cblw->Name = L"cblw";
			this->cblw->Size = System::Drawing::Size(116, 24);
			this->cblw->TabIndex = 8;
			this->cblw->Text = L"Lower word";
			this->cblw->UseVisualStyleBackColor = true;
			// 
			// cbupw
			// 
			this->cbupw->AutoSize = true;
			this->cbupw->Location = System::Drawing::Point(171, 133);
			this->cbupw->Name = L"cbupw";
			this->cbupw->Size = System::Drawing::Size(117, 24);
			this->cbupw->TabIndex = 7;
			this->cbupw->Text = L"Upper word";
			this->cbupw->UseVisualStyleBackColor = true;
			// 
			// lbOutput
			// 
			this->lbOutput->AutoSize = true;
			this->lbOutput->Location = System::Drawing::Point(121, 73);
			this->lbOutput->Name = L"lbOutput";
			this->lbOutput->Size = System::Drawing::Size(175, 20);
			this->lbOutput->TabIndex = 6;
			this->lbOutput->Text = L"D:/Dataset/3-Clustering";
			// 
			// lbOutputlabel
			// 
			this->lbOutputlabel->AutoSize = true;
			this->lbOutputlabel->Location = System::Drawing::Point(23, 73);
			this->lbOutputlabel->Name = L"lbOutputlabel";
			this->lbOutputlabel->Size = System::Drawing::Size(98, 20);
			this->lbOutputlabel->TabIndex = 5;
			this->lbOutputlabel->Text = L"Output path:";
			// 
			// btnOpenOutput
			// 
			this->btnOpenOutput->Location = System::Drawing::Point(498, 61);
			this->btnOpenOutput->Name = L"btnOpenOutput";
			this->btnOpenOutput->Size = System::Drawing::Size(108, 32);
			this->btnOpenOutput->TabIndex = 4;
			this->btnOpenOutput->Text = L"Open";
			this->btnOpenOutput->UseVisualStyleBackColor = true;
			this->btnOpenOutput->Click += gcnew System::EventHandler(this, &frmExtractFeatures::btnOpenOutput_Click);
			// 
			// cbPp
			// 
			this->cbPp->AutoSize = true;
			this->cbPp->Location = System::Drawing::Point(12, 133);
			this->cbPp->Name = L"cbPp";
			this->cbPp->Size = System::Drawing::Size(152, 24);
			this->cbPp->TabIndex = 3;
			this->cbPp->Text = L"Projection profile";
			this->cbPp->UseVisualStyleBackColor = true;
			// 
			// lbInput
			// 
			this->lbInput->AutoSize = true;
			this->lbInput->Location = System::Drawing::Point(121, 29);
			this->lbInput->Name = L"lbInput";
			this->lbInput->Size = System::Drawing::Size(175, 20);
			this->lbInput->TabIndex = 2;
			this->lbInput->Text = L"D:/Dataset/3-Clustering";
			// 
			// lbInputLabel
			// 
			this->lbInputLabel->AutoSize = true;
			this->lbInputLabel->Location = System::Drawing::Point(23, 29);
			this->lbInputLabel->Name = L"lbInputLabel";
			this->lbInputLabel->Size = System::Drawing::Size(86, 20);
			this->lbInputLabel->TabIndex = 1;
			this->lbInputLabel->Text = L"Input path:";
			// 
			// btnOpenInput
			// 
			this->btnOpenInput->Location = System::Drawing::Point(498, 23);
			this->btnOpenInput->Name = L"btnOpenInput";
			this->btnOpenInput->Size = System::Drawing::Size(108, 32);
			this->btnOpenInput->TabIndex = 0;
			this->btnOpenInput->Text = L"Open";
			this->btnOpenInput->UseVisualStyleBackColor = true;
			this->btnOpenInput->Click += gcnew System::EventHandler(this, &frmExtractFeatures::btnOpenInput_Click);
			// 
			// frmExtractFeatures
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(618, 424);
			this->Controls->Add(this->pbMain);
			this->MaximumSize = System::Drawing::Size(640, 480);
			this->MinimumSize = System::Drawing::Size(640, 480);
			this->Name = L"frmExtractFeatures";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Extracting Features";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &frmExtractFeatures::frmExtractFeatures_FormClosing);
			this->pbMain->ResumeLayout(false);
			this->pbMain->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void frmExtractFeatures_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		frmExtractFeatures::instance = false;
	}
private: System::Void btnOpenInput_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void btnOpenOutput_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void btnExtract_Click(System::Object^  sender, System::EventArgs^  e);
};
}
