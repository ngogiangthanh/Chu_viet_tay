#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include <direct.h>
#include <fstream>
#include <iomanip>

using namespace std;

namespace OpenCV_JP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for frmDTW
	/// </summary>
	public ref class frmDTW : public System::Windows::Forms::Form
	{
	public: static bool instance = false;
	public:
		frmDTW(void)
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
		~frmDTW()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  lbPath;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  btnCreate;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button3;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorkerFastDTW;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorkerLBImproved;

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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->lbPath = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnCreate = (gcnew System::Windows::Forms::Button());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->backgroundWorkerFastDTW = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorkerLBImproved = (gcnew System::ComponentModel::BackgroundWorker());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->button4);
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->lbPath);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->btnCreate);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(618, 424);
			this->panel1->TabIndex = 0;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(56, 81);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(122, 39);
			this->button4->TabIndex = 6;
			this->button4->Text = L"Lemire LB";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &frmDTW::button4_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(202, 81);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(122, 39);
			this->button3->TabIndex = 5;
			this->button3->Text = L"FastDTW";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &frmDTW::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(342, 81);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(122, 39);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Entropy";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &frmDTW::button2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(484, 81);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(122, 39);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Create";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &frmDTW::button1_Click);
			// 
			// lbPath
			// 
			this->lbPath->AutoSize = true;
			this->lbPath->Location = System::Drawing::Point(73, 43);
			this->lbPath->Name = L"lbPath";
			this->lbPath->Size = System::Drawing::Size(172, 20);
			this->lbPath->TabIndex = 2;
			this->lbPath->Text = L"D:\\Dataset\\4-Features\\";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(21, 43);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Path:";
			// 
			// btnCreate
			// 
			this->btnCreate->Location = System::Drawing::Point(484, 25);
			this->btnCreate->Name = L"btnCreate";
			this->btnCreate->Size = System::Drawing::Size(122, 39);
			this->btnCreate->TabIndex = 0;
			this->btnCreate->Text = L"Choose";
			this->btnCreate->UseVisualStyleBackColor = true;
			this->btnCreate->Click += gcnew System::EventHandler(this, &frmDTW::btnCreate_Click);
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog";
			// 
			// backgroundWorkerFastDTW
			// 
			this->backgroundWorkerFastDTW->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &frmDTW::backgroundWorkerFastDTW_DoWork);
			// 
			// backgroundWorkerLBImproved
			// 
			this->backgroundWorkerLBImproved->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &frmDTW::backgroundWorkerLBImproved_DoWork);
			// 
			// frmDTW
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(618, 424);
			this->Controls->Add(this->panel1);
			this->MaximumSize = System::Drawing::Size(640, 480);
			this->MinimumSize = System::Drawing::Size(640, 480);
			this->Name = L"frmDTW";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"DTW Result";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &frmDTW::frmDTW_FormClosing);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void frmDTW_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		frmDTW::instance = false;
	}
	private: System::Void btnCreate_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void backgroundWorkerFastDTW_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void backgroundWorkerLBImproved_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
};
}
