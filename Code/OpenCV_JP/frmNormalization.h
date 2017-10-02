#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
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
	/// Summary for frmNormalization
	/// </summary>
	public ref class frmNormalization : public System::Windows::Forms::Form
	{
	public: static bool instance = false;
	public:
		frmNormalization(void)
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
		~frmNormalization()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::GroupBox^  groupBox2;


	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;


	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  btnNormDS2;

	private: System::Windows::Forms::Button^  btnNormDS1;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Button^  btnCreateDS3;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  btnCreateDS2;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  btnCreateDS1;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Button^  btnNormDS4;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  btnNormDS3;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Button^  btnCreateDS4;
	private: System::Windows::Forms::Label^  label14;
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
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->btnNormDS2 = (gcnew System::Windows::Forms::Button());
			this->btnNormDS1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->btnCreateDS3 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->btnCreateDS2 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->btnCreateDS1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->btnCreateDS4 = (gcnew System::Windows::Forms::Button());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->btnNormDS3 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->btnNormDS4 = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->groupBox2);
			this->panel1->Controls->Add(this->groupBox1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(698, 424);
			this->panel1->TabIndex = 0;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label15);
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->btnNormDS4);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->btnNormDS3);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->btnNormDS2);
			this->groupBox2->Controls->Add(this->btnNormDS1);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Location = System::Drawing::Point(13, 208);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(673, 204);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Normalization";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(19, 72);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(83, 20);
			this->label8->TabIndex = 14;
			this->label8->Text = L"Dataset 2:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(18, 32);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(83, 20);
			this->label9->TabIndex = 13;
			this->label9->Text = L"Dataset 1:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(108, 72);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(425, 20);
			this->label3->TabIndex = 5;
			this->label3->Text = L"D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_2";
			// 
			// btnNormDS2
			// 
			this->btnNormDS2->Location = System::Drawing::Point(562, 65);
			this->btnNormDS2->Name = L"btnNormDS2";
			this->btnNormDS2->Size = System::Drawing::Size(93, 34);
			this->btnNormDS2->TabIndex = 11;
			this->btnNormDS2->Text = L"Normalize";
			this->btnNormDS2->UseVisualStyleBackColor = true;
			this->btnNormDS2->Click += gcnew System::EventHandler(this, &frmNormalization::btnNormDS2_Click);
			// 
			// btnNormDS1
			// 
			this->btnNormDS1->Location = System::Drawing::Point(562, 25);
			this->btnNormDS1->Name = L"btnNormDS1";
			this->btnNormDS1->Size = System::Drawing::Size(93, 34);
			this->btnNormDS1->TabIndex = 10;
			this->btnNormDS1->Text = L"Normalize";
			this->btnNormDS1->UseVisualStyleBackColor = true;
			this->btnNormDS1->Click += gcnew System::EventHandler(this, &frmNormalization::btnNormDS1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(107, 32);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(425, 20);
			this->label2->TabIndex = 2;
			this->label2->Text = L"D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_1";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label13);
			this->groupBox1->Controls->Add(this->btnCreateDS4);
			this->groupBox1->Controls->Add(this->label14);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->btnCreateDS3);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->btnCreateDS2);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->btnCreateDS1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(13, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(673, 190);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Generate dataset";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(109, 103);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(425, 20);
			this->label10->TabIndex = 12;
			this->label10->Text = L"D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_3";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(109, 64);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(425, 20);
			this->label11->TabIndex = 11;
			this->label11->Text = L"D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_2";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(109, 25);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(425, 20);
			this->label12->TabIndex = 10;
			this->label12->Text = L"D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_1";
			// 
			// btnCreateDS3
			// 
			this->btnCreateDS3->Location = System::Drawing::Point(562, 93);
			this->btnCreateDS3->Name = L"btnCreateDS3";
			this->btnCreateDS3->Size = System::Drawing::Size(93, 34);
			this->btnCreateDS3->TabIndex = 9;
			this->btnCreateDS3->Text = L"Create";
			this->btnCreateDS3->UseVisualStyleBackColor = true;
			this->btnCreateDS3->Click += gcnew System::EventHandler(this, &frmNormalization::btnCreateDS3_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(20, 104);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(83, 20);
			this->label6->TabIndex = 7;
			this->label6->Text = L"Dataset 3:";
			// 
			// btnCreateDS2
			// 
			this->btnCreateDS2->Location = System::Drawing::Point(562, 53);
			this->btnCreateDS2->Name = L"btnCreateDS2";
			this->btnCreateDS2->Size = System::Drawing::Size(93, 34);
			this->btnCreateDS2->TabIndex = 6;
			this->btnCreateDS2->Text = L"Create";
			this->btnCreateDS2->UseVisualStyleBackColor = true;
			this->btnCreateDS2->Click += gcnew System::EventHandler(this, &frmNormalization::btnCreateDS2_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(20, 64);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(83, 20);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Dataset 2:";
			// 
			// btnCreateDS1
			// 
			this->btnCreateDS1->Location = System::Drawing::Point(563, 13);
			this->btnCreateDS1->Name = L"btnCreateDS1";
			this->btnCreateDS1->Size = System::Drawing::Size(93, 34);
			this->btnCreateDS1->TabIndex = 3;
			this->btnCreateDS1->Text = L"Create";
			this->btnCreateDS1->UseVisualStyleBackColor = true;
			this->btnCreateDS1->Click += gcnew System::EventHandler(this, &frmNormalization::btnCreateDS1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(20, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(83, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Dataset 1:";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(109, 149);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(425, 20);
			this->label13->TabIndex = 15;
			this->label13->Text = L"D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_4";
			// 
			// btnCreateDS4
			// 
			this->btnCreateDS4->Location = System::Drawing::Point(562, 139);
			this->btnCreateDS4->Name = L"btnCreateDS4";
			this->btnCreateDS4->Size = System::Drawing::Size(93, 34);
			this->btnCreateDS4->TabIndex = 14;
			this->btnCreateDS4->Text = L"Create";
			this->btnCreateDS4->UseVisualStyleBackColor = true;
			this->btnCreateDS4->Click += gcnew System::EventHandler(this, &frmNormalization::btnCreateDS4_Click);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(20, 150);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(83, 20);
			this->label14->TabIndex = 13;
			this->label14->Text = L"Dataset 4:";
			// 
			// btnNormDS3
			// 
			this->btnNormDS3->Location = System::Drawing::Point(562, 105);
			this->btnNormDS3->Name = L"btnNormDS3";
			this->btnNormDS3->Size = System::Drawing::Size(93, 34);
			this->btnNormDS3->TabIndex = 12;
			this->btnNormDS3->Text = L"Normalize";
			this->btnNormDS3->UseVisualStyleBackColor = true;
			this->btnNormDS3->Click += gcnew System::EventHandler(this, &frmNormalization::btnNormDS3_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(108, 112);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(425, 20);
			this->label5->TabIndex = 8;
			this->label5->Text = L"D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_3";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(19, 112);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(83, 20);
			this->label7->TabIndex = 15;
			this->label7->Text = L"Dataset 3:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(18, 156);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(83, 20);
			this->label15->TabIndex = 18;
			this->label15->Text = L"Dataset 4:";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(107, 156);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(425, 20);
			this->label16->TabIndex = 16;
			this->label16->Text = L"D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_4";
			// 
			// btnNormDS4
			// 
			this->btnNormDS4->Location = System::Drawing::Point(561, 149);
			this->btnNormDS4->Name = L"btnNormDS4";
			this->btnNormDS4->Size = System::Drawing::Size(93, 34);
			this->btnNormDS4->TabIndex = 17;
			this->btnNormDS4->Text = L"Normalize";
			this->btnNormDS4->UseVisualStyleBackColor = true;
			this->btnNormDS4->Click += gcnew System::EventHandler(this, &frmNormalization::btnNormDS4_Click);
			// 
			// frmNormalization
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(698, 424);
			this->Controls->Add(this->panel1);
			this->MaximumSize = System::Drawing::Size(720, 480);
			this->MinimumSize = System::Drawing::Size(720, 480);
			this->Name = L"frmNormalization";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Normalization";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &frmNormalization::frmNormalization_FormClosing);
			this->panel1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void frmNormalization_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		frmNormalization::instance = false;
	}
	private: System::Void btnCreateDS1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnCreateDS2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnCreateDS3_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnNormDS1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnNormDS2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnNormDS3_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void btnCreateDS4_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void btnNormDS4_Click(System::Object^  sender, System::EventArgs^  e);

};
}
