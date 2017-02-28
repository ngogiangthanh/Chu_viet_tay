#pragma once
#include "iostream"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include <opencv2/opencv.hpp>
#include <string>
#include <ctime>
#include "Extent.h"
#include "PreProcess.h"
#include "Segmentation.h"
#include "Normalization.h"
#include <filesystem>
#include <iterator>
namespace fs = experimental::filesystem;

namespace Thesis {

	using namespace cv;
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
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
			this->cbbMAFLength->SelectedIndex = 0;
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
	private: System::Windows::Forms::TabControl^  tabControlFirst;
	protected:

	protected:
	private: System::Windows::Forms::TabPage^  tabPageFirst;

	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  lbPathImage;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  btnChooseImage;
	private: System::Windows::Forms::TextBox^  tbKeywords;


	private: System::Windows::Forms::Button^  btnSearch;




	private: System::Windows::Forms::RadioButton^  rbItakura;

	private: System::Windows::Forms::RadioButton^  rdSakoeChiba;

	private: System::Windows::Forms::RadioButton^  rdNonGPC;

	private: System::Windows::Forms::RadioButton^  rdLowerWord;

	private: System::Windows::Forms::RadioButton^  rdUpperWord;

	private: System::Windows::Forms::RadioButton^  rdWordProfiles;
	private: System::Windows::Forms::CheckBox^  cbProjectionProfiles;


	private: System::Windows::Forms::CheckBox^  cbSkewDetect;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  lbSegValHeigh;
	private: System::Windows::Forms::Label^  lbMaxHeigh;
	private: System::Windows::Forms::Label^  lbMinHeigh;
	private: System::Windows::Forms::TrackBar^  trbSegHeighOfLine;
	private: System::Windows::Forms::ComboBox^  cbbMAFLength;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::CheckBox^  cbMorphGradient;


	private: System::Windows::Forms::CheckBox^  cbThresholding;

	private: System::Windows::Forms::CheckBox^  cbMedianFilter;





	private: System::Windows::Forms::Label^  lbPathDB;

	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Button^  btnChooseDB;


	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::PictureBox^  pbDTW;

	private: System::Windows::Forms::PictureBox^  pbFeatures;

	private: System::Windows::Forms::PictureBox^  pbSegmentation;


	private: System::Windows::Forms::PictureBox^  pbPreProcess;









	public:
	protected:

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(frmMain::typeid));
			this->tabControlFirst = (gcnew System::Windows::Forms::TabControl());
			this->tabPageFirst = (gcnew System::Windows::Forms::TabPage());
			this->lbPathDB = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->btnChooseDB = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->pbDTW = (gcnew System::Windows::Forms::PictureBox());
			this->rbItakura = (gcnew System::Windows::Forms::RadioButton());
			this->rdSakoeChiba = (gcnew System::Windows::Forms::RadioButton());
			this->rdNonGPC = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->pbFeatures = (gcnew System::Windows::Forms::PictureBox());
			this->rdLowerWord = (gcnew System::Windows::Forms::RadioButton());
			this->rdUpperWord = (gcnew System::Windows::Forms::RadioButton());
			this->rdWordProfiles = (gcnew System::Windows::Forms::RadioButton());
			this->cbProjectionProfiles = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->pbSegmentation = (gcnew System::Windows::Forms::PictureBox());
			this->cbSkewDetect = (gcnew System::Windows::Forms::CheckBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->lbSegValHeigh = (gcnew System::Windows::Forms::Label());
			this->lbMaxHeigh = (gcnew System::Windows::Forms::Label());
			this->lbMinHeigh = (gcnew System::Windows::Forms::Label());
			this->trbSegHeighOfLine = (gcnew System::Windows::Forms::TrackBar());
			this->cbbMAFLength = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->pbPreProcess = (gcnew System::Windows::Forms::PictureBox());
			this->cbMorphGradient = (gcnew System::Windows::Forms::CheckBox());
			this->cbThresholding = (gcnew System::Windows::Forms::CheckBox());
			this->cbMedianFilter = (gcnew System::Windows::Forms::CheckBox());
			this->lbPathImage = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnChooseImage = (gcnew System::Windows::Forms::Button());
			this->tbKeywords = (gcnew System::Windows::Forms::TextBox());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tabControlFirst->SuspendLayout();
			this->tabPageFirst->SuspendLayout();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDTW))->BeginInit();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbFeatures))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSegmentation))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSegHeighOfLine))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPreProcess))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControlFirst
			// 
			this->tabControlFirst->Controls->Add(this->tabPageFirst);
			this->tabControlFirst->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControlFirst->Location = System::Drawing::Point(0, 0);
			this->tabControlFirst->Name = L"tabControlFirst";
			this->tabControlFirst->SelectedIndex = 0;
			this->tabControlFirst->Size = System::Drawing::Size(1002, 712);
			this->tabControlFirst->TabIndex = 0;
			// 
			// tabPageFirst
			// 
			this->tabPageFirst->Controls->Add(this->lbPathDB);
			this->tabPageFirst->Controls->Add(this->label10);
			this->tabPageFirst->Controls->Add(this->btnChooseDB);
			this->tabPageFirst->Controls->Add(this->groupBox4);
			this->tabPageFirst->Controls->Add(this->groupBox3);
			this->tabPageFirst->Controls->Add(this->groupBox2);
			this->tabPageFirst->Controls->Add(this->groupBox1);
			this->tabPageFirst->Controls->Add(this->lbPathImage);
			this->tabPageFirst->Controls->Add(this->label1);
			this->tabPageFirst->Controls->Add(this->btnChooseImage);
			this->tabPageFirst->Controls->Add(this->tbKeywords);
			this->tabPageFirst->Controls->Add(this->btnSearch);
			this->tabPageFirst->Location = System::Drawing::Point(4, 29);
			this->tabPageFirst->Name = L"tabPageFirst";
			this->tabPageFirst->Padding = System::Windows::Forms::Padding(3);
			this->tabPageFirst->Size = System::Drawing::Size(994, 679);
			this->tabPageFirst->TabIndex = 0;
			this->tabPageFirst->Text = L"Tìm kiếm";
			this->tabPageFirst->UseVisualStyleBackColor = true;
			// 
			// lbPathDB
			// 
			this->lbPathDB->AutoSize = true;
			this->lbPathDB->Location = System::Drawing::Point(121, 151);
			this->lbPathDB->Name = L"lbPathDB";
			this->lbPathDB->Size = System::Drawing::Size(192, 20);
			this->lbPathDB->TabIndex = 11;
			this->lbPathDB->Text = L"D:\\Thesis\\Data\\Database\\";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(23, 151);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(92, 20);
			this->label10->TabIndex = 10;
			this->label10->Text = L"Đường dẫn:";
			// 
			// btnChooseDB
			// 
			this->btnChooseDB->Location = System::Drawing::Point(828, 149);
			this->btnChooseDB->Name = L"btnChooseDB";
			this->btnChooseDB->Size = System::Drawing::Size(158, 38);
			this->btnChooseDB->TabIndex = 9;
			this->btnChooseDB->Text = L"Chọn folder CSDL";
			this->btnChooseDB->UseVisualStyleBackColor = true;
			this->btnChooseDB->Click += gcnew System::EventHandler(this, &frmMain::btnChooseDB_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->pbDTW);
			this->groupBox4->Controls->Add(this->rbItakura);
			this->groupBox4->Controls->Add(this->rdSakoeChiba);
			this->groupBox4->Controls->Add(this->rdNonGPC);
			this->groupBox4->Location = System::Drawing::Point(6, 552);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(983, 124);
			this->groupBox4->TabIndex = 8;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Tùy chọn so khớp Dynamic Time Warping";
			// 
			// pbDTW
			// 
			this->pbDTW->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbDTW.Image")));
			this->pbDTW->Location = System::Drawing::Point(862, 41);
			this->pbDTW->Name = L"pbDTW";
			this->pbDTW->Size = System::Drawing::Size(30, 30);
			this->pbDTW->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbDTW->TabIndex = 32;
			this->pbDTW->TabStop = false;
			// 
			// rbItakura
			// 
			this->rbItakura->AutoSize = true;
			this->rbItakura->Location = System::Drawing::Point(573, 41);
			this->rbItakura->Name = L"rbItakura";
			this->rbItakura->Size = System::Drawing::Size(283, 24);
			this->rbItakura->TabIndex = 8;
			this->rbItakura->Text = L"Ràng buộc hình bình hành - Itakura";
			this->rbItakura->UseVisualStyleBackColor = true;
			// 
			// rdSakoeChiba
			// 
			this->rdSakoeChiba->AutoSize = true;
			this->rdSakoeChiba->Location = System::Drawing::Point(272, 41);
			this->rdSakoeChiba->Name = L"rdSakoeChiba";
			this->rdSakoeChiba->Size = System::Drawing::Size(281, 24);
			this->rdSakoeChiba->TabIndex = 7;
			this->rdSakoeChiba->Text = L"Ràng buộc hình thoi - Sakoe-Chiba";
			this->rdSakoeChiba->UseVisualStyleBackColor = true;
			// 
			// rdNonGPC
			// 
			this->rdNonGPC->AutoSize = true;
			this->rdNonGPC->Checked = true;
			this->rdNonGPC->Location = System::Drawing::Point(33, 41);
			this->rdNonGPC->Name = L"rdNonGPC";
			this->rdNonGPC->Size = System::Drawing::Size(219, 24);
			this->rdNonGPC->TabIndex = 6;
			this->rdNonGPC->TabStop = true;
			this->rdNonGPC->Text = L"Non global path constraint";
			this->rdNonGPC->UseVisualStyleBackColor = true;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->pbFeatures);
			this->groupBox3->Controls->Add(this->rdLowerWord);
			this->groupBox3->Controls->Add(this->rdUpperWord);
			this->groupBox3->Controls->Add(this->rdWordProfiles);
			this->groupBox3->Controls->Add(this->cbProjectionProfiles);
			this->groupBox3->Location = System::Drawing::Point(8, 442);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(980, 106);
			this->groupBox3->TabIndex = 7;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Tùy chọn rút trích đặt trưng";
			// 
			// pbFeatures
			// 
			this->pbFeatures->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbFeatures.Image")));
			this->pbFeatures->Location = System::Drawing::Point(860, 44);
			this->pbFeatures->Name = L"pbFeatures";
			this->pbFeatures->Size = System::Drawing::Size(30, 30);
			this->pbFeatures->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbFeatures->TabIndex = 31;
			this->pbFeatures->TabStop = false;
			// 
			// rdLowerWord
			// 
			this->rdLowerWord->AutoSize = true;
			this->rdLowerWord->Location = System::Drawing::Point(316, 51);
			this->rdLowerWord->Name = L"rdLowerWord";
			this->rdLowerWord->Size = System::Drawing::Size(136, 24);
			this->rdLowerWord->TabIndex = 5;
			this->rdLowerWord->Text = L"Chỉ lower word";
			this->rdLowerWord->UseVisualStyleBackColor = true;
			// 
			// rdUpperWord
			// 
			this->rdUpperWord->AutoSize = true;
			this->rdUpperWord->Location = System::Drawing::Point(166, 51);
			this->rdUpperWord->Name = L"rdUpperWord";
			this->rdUpperWord->Size = System::Drawing::Size(140, 24);
			this->rdUpperWord->TabIndex = 4;
			this->rdUpperWord->Text = L"Chỉ upper word";
			this->rdUpperWord->UseVisualStyleBackColor = true;
			// 
			// rdWordProfiles
			// 
			this->rdWordProfiles->AutoSize = true;
			this->rdWordProfiles->Checked = true;
			this->rdWordProfiles->Location = System::Drawing::Point(33, 50);
			this->rdWordProfiles->Name = L"rdWordProfiles";
			this->rdWordProfiles->Size = System::Drawing::Size(127, 24);
			this->rdWordProfiles->TabIndex = 3;
			this->rdWordProfiles->TabStop = true;
			this->rdWordProfiles->Text = L"Word profiles";
			this->rdWordProfiles->UseVisualStyleBackColor = true;
			// 
			// cbProjectionProfiles
			// 
			this->cbProjectionProfiles->AutoSize = true;
			this->cbProjectionProfiles->Checked = true;
			this->cbProjectionProfiles->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbProjectionProfiles->Location = System::Drawing::Point(603, 51);
			this->cbProjectionProfiles->Name = L"cbProjectionProfiles";
			this->cbProjectionProfiles->Size = System::Drawing::Size(160, 24);
			this->cbProjectionProfiles->TabIndex = 2;
			this->cbProjectionProfiles->Text = L"Projection profiles";
			this->cbProjectionProfiles->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->pbSegmentation);
			this->groupBox2->Controls->Add(this->cbSkewDetect);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->lbSegValHeigh);
			this->groupBox2->Controls->Add(this->lbMaxHeigh);
			this->groupBox2->Controls->Add(this->lbMinHeigh);
			this->groupBox2->Controls->Add(this->trbSegHeighOfLine);
			this->groupBox2->Controls->Add(this->cbbMAFLength);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Location = System::Drawing::Point(8, 318);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(978, 118);
			this->groupBox2->TabIndex = 6;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Tùy chọn phân đoạn";
			// 
			// pbSegmentation
			// 
			this->pbSegmentation->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbSegmentation.Image")));
			this->pbSegmentation->Location = System::Drawing::Point(860, 67);
			this->pbSegmentation->Name = L"pbSegmentation";
			this->pbSegmentation->Size = System::Drawing::Size(30, 30);
			this->pbSegmentation->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbSegmentation->TabIndex = 30;
			this->pbSegmentation->TabStop = false;
			// 
			// cbSkewDetect
			// 
			this->cbSkewDetect->AutoSize = true;
			this->cbSkewDetect->Checked = true;
			this->cbSkewDetect->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbSkewDetect->Location = System::Drawing::Point(780, 37);
			this->cbSkewDetect->Name = L"cbSkewDetect";
			this->cbSkewDetect->Size = System::Drawing::Size(192, 24);
			this->cbSkewDetect->TabIndex = 29;
			this->cbSkewDetect->Text = L"Chuẩn hóa từ nghiêng";
			this->cbSkewDetect->UseVisualStyleBackColor = true;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(414, 14);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(224, 20);
			this->label6->TabIndex = 28;
			this->label6->Text = L"Chiều cao trung bình mỗi dòng";
			// 
			// lbSegValHeigh
			// 
			this->lbSegValHeigh->AutoSize = true;
			this->lbSegValHeigh->Location = System::Drawing::Point(695, 49);
			this->lbSegValHeigh->Name = L"lbSegValHeigh";
			this->lbSegValHeigh->Size = System::Drawing::Size(27, 20);
			this->lbSegValHeigh->TabIndex = 27;
			this->lbSegValHeigh->Text = L"50";
			// 
			// lbMaxHeigh
			// 
			this->lbMaxHeigh->AutoSize = true;
			this->lbMaxHeigh->Location = System::Drawing::Point(653, 49);
			this->lbMaxHeigh->Name = L"lbMaxHeigh";
			this->lbMaxHeigh->Size = System::Drawing::Size(36, 20);
			this->lbMaxHeigh->TabIndex = 26;
			this->lbMaxHeigh->Text = L"128";
			// 
			// lbMinHeigh
			// 
			this->lbMinHeigh->AutoSize = true;
			this->lbMinHeigh->Location = System::Drawing::Point(394, 54);
			this->lbMinHeigh->Name = L"lbMinHeigh";
			this->lbMinHeigh->Size = System::Drawing::Size(18, 20);
			this->lbMinHeigh->TabIndex = 25;
			this->lbMinHeigh->Text = L"0";
			// 
			// trbSegHeighOfLine
			// 
			this->trbSegHeighOfLine->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->trbSegHeighOfLine->Location = System::Drawing::Point(418, 37);
			this->trbSegHeighOfLine->Maximum = 128;
			this->trbSegHeighOfLine->Name = L"trbSegHeighOfLine";
			this->trbSegHeighOfLine->Size = System::Drawing::Size(229, 69);
			this->trbSegHeighOfLine->TabIndex = 24;
			this->trbSegHeighOfLine->Value = 50;
			this->trbSegHeighOfLine->Scroll += gcnew System::EventHandler(this, &frmMain::trbSegHeighOfLine_Scroll);
			// 
			// cbbMAFLength
			// 
			this->cbbMAFLength->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbMAFLength->FormattingEnabled = true;
			this->cbbMAFLength->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				L"5", L"7", L"9", L"11", L"13", L"15", L"17",
					L"19", L"21"
			});
			this->cbbMAFLength->Location = System::Drawing::Point(17, 51);
			this->cbbMAFLength->Name = L"cbbMAFLength";
			this->cbbMAFLength->Size = System::Drawing::Size(121, 28);
			this->cbbMAFLength->TabIndex = 5;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(144, 51);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(211, 20);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Độ dài Moving Average Filter";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->pbPreProcess);
			this->groupBox1->Controls->Add(this->cbMorphGradient);
			this->groupBox1->Controls->Add(this->cbThresholding);
			this->groupBox1->Controls->Add(this->cbMedianFilter);
			this->groupBox1->Location = System::Drawing::Point(8, 195);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(978, 123);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Tùy chọn tiền xử lý";
			// 
			// pbPreProcess
			// 
			this->pbPreProcess->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbPreProcess.Image")));
			this->pbPreProcess->Location = System::Drawing::Point(860, 49);
			this->pbPreProcess->Name = L"pbPreProcess";
			this->pbPreProcess->Size = System::Drawing::Size(30, 30);
			this->pbPreProcess->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbPreProcess->TabIndex = 31;
			this->pbPreProcess->TabStop = false;
			// 
			// cbMorphGradient
			// 
			this->cbMorphGradient->AutoSize = true;
			this->cbMorphGradient->Checked = true;
			this->cbMorphGradient->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbMorphGradient->Location = System::Drawing::Point(418, 41);
			this->cbMorphGradient->Name = L"cbMorphGradient";
			this->cbMorphGradient->Size = System::Drawing::Size(258, 24);
			this->cbMorphGradient->TabIndex = 2;
			this->cbMorphGradient->Text = L"Kết hợp Morphological Gradient";
			this->cbMorphGradient->UseVisualStyleBackColor = true;
			// 
			// cbThresholding
			// 
			this->cbThresholding->AutoSize = true;
			this->cbThresholding->Checked = true;
			this->cbThresholding->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbThresholding->Location = System::Drawing::Point(244, 41);
			this->cbThresholding->Name = L"cbThresholding";
			this->cbThresholding->Size = System::Drawing::Size(130, 24);
			this->cbThresholding->TabIndex = 1;
			this->cbThresholding->Text = L"Phân ngưỡng";
			this->cbThresholding->UseVisualStyleBackColor = true;
			// 
			// cbMedianFilter
			// 
			this->cbMedianFilter->AutoSize = true;
			this->cbMedianFilter->Checked = true;
			this->cbMedianFilter->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbMedianFilter->Location = System::Drawing::Point(33, 41);
			this->cbMedianFilter->Name = L"cbMedianFilter";
			this->cbMedianFilter->Size = System::Drawing::Size(172, 24);
			this->cbMedianFilter->TabIndex = 0;
			this->cbMedianFilter->Text = L"Lọc nhiễu muối tiêu";
			this->cbMedianFilter->UseVisualStyleBackColor = true;
			// 
			// lbPathImage
			// 
			this->lbPathImage->AutoSize = true;
			this->lbPathImage->Location = System::Drawing::Point(121, 102);
			this->lbPathImage->Name = L"lbPathImage";
			this->lbPathImage->Size = System::Drawing::Size(82, 20);
			this->lbPathImage->TabIndex = 4;
			this->lbPathImage->Text = L"FakePath\\";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(23, 102);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 20);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Đường dẫn:";
			// 
			// btnChooseImage
			// 
			this->btnChooseImage->Location = System::Drawing::Point(828, 107);
			this->btnChooseImage->Name = L"btnChooseImage";
			this->btnChooseImage->Size = System::Drawing::Size(158, 38);
			this->btnChooseImage->TabIndex = 2;
			this->btnChooseImage->Text = L"Chọn ảnh";
			this->btnChooseImage->UseVisualStyleBackColor = true;
			this->btnChooseImage->Click += gcnew System::EventHandler(this, &frmMain::btnChooseImage_Click);
			// 
			// tbKeywords
			// 
			this->tbKeywords->Location = System::Drawing::Point(8, 22);
			this->tbKeywords->Multiline = true;
			this->tbKeywords->Name = L"tbKeywords";
			this->tbKeywords->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->tbKeywords->Size = System::Drawing::Size(814, 76);
			this->tbKeywords->TabIndex = 1;
			this->tbKeywords->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &frmMain::tbKeywords_KeyDown);
			// 
			// btnSearch
			// 
			this->btnSearch->Location = System::Drawing::Point(828, 22);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(158, 38);
			this->btnSearch->TabIndex = 0;
			this->btnSearch->Text = L"Tìm kiếm";
			this->btnSearch->UseVisualStyleBackColor = true;
			this->btnSearch->Click += gcnew System::EventHandler(this, &frmMain::btnSearch_Click);
			// 
			// openFileDialog
			// 
			this->openFileDialog->Title = L"Chọn ảnh";
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1002, 712);
			this->Controls->Add(this->tabControlFirst);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(1024, 768);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(1024, 768);
			this->Name = L"frmMain";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Rút trích đặc trưng theo giải thuật Dynamic Time Warping";
			this->tabControlFirst->ResumeLayout(false);
			this->tabPageFirst->ResumeLayout(false);
			this->tabPageFirst->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDTW))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbFeatures))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSegmentation))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSegHeighOfLine))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPreProcess))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnSearch_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnChooseImage_Click(System::Object^  sender, System::EventArgs^  e) {
		openFileDialog->InitialDirectory = "C:\\Users\\thanh\\Google Drive\\Pages\\";
		openFileDialog->Filter = "PNG (*.png)|*.png|JPG (*.jpg)|*.jpg";
		openFileDialog->FilterIndex = 2;
		openFileDialog->RestoreDirectory = true;

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			this->lbPathImage->Text = openFileDialog->FileName;
		}
	}
	private: System::Void btnChooseDB_Click(System::Object^  sender, System::EventArgs^  e) {
		folderBrowserDialog->SelectedPath = "D:\\Thesis\\Data\\Database\\";
		if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			this->lbPathDB->Text = folderBrowserDialog->SelectedPath;
		}
	}
	private: System::Void trbSegHeighOfLine_Scroll(System::Object^  sender, System::EventArgs^  e) {
		std::string model(std::to_string(trbSegHeighOfLine->Value));
		System::String^ val = gcnew System::String(model.c_str());
		lbSegValHeigh->Text = val;
	}

	private: System::Void tbKeywords_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->Control && e->KeyCode == Keys::A) this->tbKeywords->SelectAll();
	}
	//Hàm tự định nghĩa
	private: Mat khuNhieu(Mat anhGoc, Mat& anhGocResize); //trả về tấm hình đã khử nhiễu và phân đoạn
	private: string tachDongTachTu(Mat anhTienXuLy, Mat& anhGocResize, string tenAnh); //trả về đường dẫn thư mục lưu trữ từ tách
	private: void chuanHoa(string duongDan);
	private: Mat soKhop(vector<string> dsTuKhoa, string duongDanDsTu, Mat anhGocResize); //trả về tấm hình đã được hightlight
	//Kết thúc hàm tự định nghĩa
	private: 
		Extent* extent = new Extent();
};
}
