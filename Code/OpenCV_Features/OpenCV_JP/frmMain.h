#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace OpenCV_JP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;

	/// <summary>
	/// Summary for frmMain
	/// </summary>
	public ref class frmMain : public System::Windows::Forms::Form
	{
	public:
		frmMain(void)
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
		~frmMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TrackBar^  tbOperator;
	private: System::Windows::Forms::TrackBar^  tbElement;
	private: System::Windows::Forms::TrackBar^  tbKernel;
	private: System::Windows::Forms::Label^  lbOperatorMin;
	private: System::Windows::Forms::Label^  lbOperatorMax;
	private: System::Windows::Forms::Label^  lbOperatorCurr;
	private: System::Windows::Forms::Label^  lbElementCurr;


	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  lbKernelCurr;

	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Button^  btnProcess;


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->tbOperator = (gcnew System::Windows::Forms::TrackBar());
			this->tbElement = (gcnew System::Windows::Forms::TrackBar());
			this->tbKernel = (gcnew System::Windows::Forms::TrackBar());
			this->lbOperatorMin = (gcnew System::Windows::Forms::Label());
			this->lbOperatorMax = (gcnew System::Windows::Forms::Label());
			this->lbOperatorCurr = (gcnew System::Windows::Forms::Label());
			this->lbElementCurr = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->lbKernelCurr = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->btnProcess = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbOperator))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbElement))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbKernel))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(66, 15);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Operator:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(38, 45);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(155, 15);
			this->label2->TabIndex = 1;
			this->label2->Text = L"0: Opening - 1: Closing";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(38, 72);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(161, 15);
			this->label3->TabIndex = 2;
			this->label3->Text = L"2: Gradient - 3: Top Hat";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(38, 101);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(85, 15);
			this->label4->TabIndex = 3;
			this->label4->Text = L"4: Black Hat";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(12, 132);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(61, 15);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Element:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(38, 162);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(202, 15);
			this->label6->TabIndex = 5;
			this->label6->Text = L"0: Rect - 1: Cross - 2: Eclipse";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(21, 201);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(81, 15);
			this->label7->TabIndex = 6;
			this->label7->Text = L"Kernel size:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(38, 229);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(49, 15);
			this->label8->TabIndex = 7;
			this->label8->Text = L"2n + 1";
			// 
			// tbOperator
			// 
			this->tbOperator->Location = System::Drawing::Point(265, 45);
			this->tbOperator->Maximum = 4;
			this->tbOperator->Name = L"tbOperator";
			this->tbOperator->Size = System::Drawing::Size(297, 56);
			this->tbOperator->TabIndex = 8;
			this->tbOperator->Scroll += gcnew System::EventHandler(this, &frmMain::tbOperator_Scroll);
			// 
			// tbElement
			// 
			this->tbElement->Location = System::Drawing::Point(265, 132);
			this->tbElement->Maximum = 2;
			this->tbElement->Name = L"tbElement";
			this->tbElement->Size = System::Drawing::Size(297, 56);
			this->tbElement->TabIndex = 9;
			this->tbElement->Scroll += gcnew System::EventHandler(this, &frmMain::tbElement_Scroll);
			// 
			// tbKernel
			// 
			this->tbKernel->Location = System::Drawing::Point(265, 220);
			this->tbKernel->Maximum = 4;
			this->tbKernel->Minimum = 1;
			this->tbKernel->Name = L"tbKernel";
			this->tbKernel->Size = System::Drawing::Size(297, 56);
			this->tbKernel->TabIndex = 10;
			this->tbKernel->Value = 1;
			this->tbKernel->Scroll += gcnew System::EventHandler(this, &frmMain::tbKernel_Scroll);
			// 
			// lbOperatorMin
			// 
			this->lbOperatorMin->AutoSize = true;
			this->lbOperatorMin->Location = System::Drawing::Point(253, 60);
			this->lbOperatorMin->Name = L"lbOperatorMin";
			this->lbOperatorMin->Size = System::Drawing::Size(15, 15);
			this->lbOperatorMin->TabIndex = 11;
			this->lbOperatorMin->Text = L"0";
			// 
			// lbOperatorMax
			// 
			this->lbOperatorMax->AutoSize = true;
			this->lbOperatorMax->Location = System::Drawing::Point(559, 60);
			this->lbOperatorMax->Name = L"lbOperatorMax";
			this->lbOperatorMax->Size = System::Drawing::Size(15, 15);
			this->lbOperatorMax->TabIndex = 12;
			this->lbOperatorMax->Text = L"4";
			// 
			// lbOperatorCurr
			// 
			this->lbOperatorCurr->AutoSize = true;
			this->lbOperatorCurr->Location = System::Drawing::Point(397, 27);
			this->lbOperatorCurr->Name = L"lbOperatorCurr";
			this->lbOperatorCurr->Size = System::Drawing::Size(15, 15);
			this->lbOperatorCurr->TabIndex = 13;
			this->lbOperatorCurr->Text = L"0";
			// 
			// lbElementCurr
			// 
			this->lbElementCurr->AutoSize = true;
			this->lbElementCurr->Location = System::Drawing::Point(397, 104);
			this->lbElementCurr->Name = L"lbElementCurr";
			this->lbElementCurr->Size = System::Drawing::Size(15, 15);
			this->lbElementCurr->TabIndex = 16;
			this->lbElementCurr->Text = L"0";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(559, 137);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(15, 15);
			this->label10->TabIndex = 15;
			this->label10->Text = L"2";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(253, 137);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(15, 15);
			this->label11->TabIndex = 14;
			this->label11->Text = L"0";
			// 
			// lbKernelCurr
			// 
			this->lbKernelCurr->AutoSize = true;
			this->lbKernelCurr->Location = System::Drawing::Point(397, 202);
			this->lbKernelCurr->Name = L"lbKernelCurr";
			this->lbKernelCurr->Size = System::Drawing::Size(15, 15);
			this->lbKernelCurr->TabIndex = 19;
			this->lbKernelCurr->Text = L"0";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(559, 235);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(15, 15);
			this->label13->TabIndex = 18;
			this->label13->Text = L"4";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(253, 235);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(15, 15);
			this->label14->TabIndex = 17;
			this->label14->Text = L"1";
			// 
			// btnProcess
			// 
			this->btnProcess->Location = System::Drawing::Point(510, 291);
			this->btnProcess->Name = L"btnProcess";
			this->btnProcess->Size = System::Drawing::Size(75, 23);
			this->btnProcess->TabIndex = 20;
			this->btnProcess->Text = L"Process";
			this->btnProcess->UseVisualStyleBackColor = true;
			this->btnProcess->Click += gcnew System::EventHandler(this, &frmMain::btnProcess_Click);
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(622, 435);
			this->Controls->Add(this->btnProcess);
			this->Controls->Add(this->lbKernelCurr);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->lbElementCurr);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->lbOperatorCurr);
			this->Controls->Add(this->lbOperatorMax);
			this->Controls->Add(this->lbOperatorMin);
			this->Controls->Add(this->tbKernel);
			this->Controls->Add(this->tbElement);
			this->Controls->Add(this->tbOperator);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximumSize = System::Drawing::Size(640, 480);
			this->MinimumSize = System::Drawing::Size(640, 480);
			this->Name = L"frmMain";
			this->Text = L"Morphology Transformations Demo";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbOperator))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbElement))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbKernel))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void tbOperator_Scroll(System::Object^  sender, System::EventArgs^  e);
private: System::Void tbElement_Scroll(System::Object^  sender, System::EventArgs^  e);
private: System::Void tbKernel_Scroll(System::Object^  sender, System::EventArgs^  e);
private: System::Void btnProcess_Click(System::Object^  sender, System::EventArgs^  e);
private: void Morphology_Operations(Mat, int, int, int);
};
}
