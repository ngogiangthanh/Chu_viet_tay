#pragma once
#include "Preprocess.h"
#include "Segmentation.h"
#include "Extent.h"
#include <ctime>

namespace OpenCV_Threshold {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for frmMain
	/// </summary>
	public ref class frmMain : public System::Windows::Forms::Form
	{
	public:
		frmMain(void)
		{
			InitializeComponent();
			this->cbbOrderThreshold->SelectedIndex = 0;
			this->cbbOrderAveraging->SelectedIndex = 0;
			this->cbbOrderGauss->SelectedIndex = 0;
			this->cbbOrderMedian->SelectedIndex = 0;
			this->cbbOrderLaplacian->SelectedIndex = 0;
			this->cbbKernelAdaptiveThreshold->SelectedIndex = 0;
			//

			this->cbbAveraging->SelectedIndex = 0;
			this->cbbKernelGauss->SelectedIndex = 0;
			this->cbbLaplacian->SelectedIndex = 0;
			this->cbbMedian->SelectedIndex = 0;
			//
			this->cbbSegMAF->SelectedIndex = 2;
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

	protected:

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Label^  lbThresholdVal;
	private: System::Windows::Forms::Label^  lbMaxThresholdVal;
	private: System::Windows::Forms::Label^  lbMinThresholdVal;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::RadioButton^  rbZeroInvert;
	private: System::Windows::Forms::RadioButton^  rbZero;
	private: System::Windows::Forms::RadioButton^  rbTruncate;
	private: System::Windows::Forms::RadioButton^  rbBinaryInvert;
	private: System::Windows::Forms::RadioButton^  rbBin;
	private: System::Windows::Forms::Button^  btnOpen;
	private: System::Windows::Forms::Label^  lbPath;
	private: System::Windows::Forms::Label^  lbImage;
	private: System::Windows::Forms::Button^  btnProcess;

	private: System::Windows::Forms::GroupBox^  gbThreshold;
	private: System::Windows::Forms::ComboBox^  cbbOrderThreshold;
	private: System::Windows::Forms::GroupBox^  gbGauss;
	private: System::Windows::Forms::ComboBox^  cbbOrderGauss;
	private: System::Windows::Forms::Label^  lbKernelGaus;
	private: System::Windows::Forms::ComboBox^  cbbKernelGauss;
	private: System::Windows::Forms::GroupBox^  gbAveraging;
	private: System::Windows::Forms::ComboBox^  cbbOrderAveraging;


	private: System::Windows::Forms::Label^  lbKernelAveraging;
	private: System::Windows::Forms::ComboBox^  cbbAveraging;
	private: System::Windows::Forms::GroupBox^  gbMedian;
	private: System::Windows::Forms::ComboBox^  cbbOrderMedian;
	private: System::Windows::Forms::Label^  lbMedian;
	private: System::Windows::Forms::ComboBox^  cbbMedian;
	private: System::Windows::Forms::GroupBox^  gbLaplacian;
	private: System::Windows::Forms::ComboBox^  cbbOrderLaplacian;
	private: System::Windows::Forms::Label^  lbLaplacian;
	private: System::Windows::Forms::ComboBox^  cbbLaplacian;
	private: System::Windows::Forms::Button^  btnThresholdCls;
	private: System::Windows::Forms::Button^  btnGaussCls;
	private: System::Windows::Forms::Button^  btnAverageCls;
	private: System::Windows::Forms::Button^  btnMedianCls;
	private: System::Windows::Forms::Button^  btnLaplacianCls;
	private: System::Windows::Forms::Button^  btnClearAll;
	private: System::Windows::Forms::TabControl^  tabMain;
	private: System::Windows::Forms::TabPage^  tabPagePreprocessing;
	private: System::Windows::Forms::TabPage^  tabPageSegmentation;
	private: System::Windows::Forms::Button^  btnKhoiTao;
	private: System::Windows::Forms::Button^  btnFindValley;
	private: System::Windows::Forms::Button^  btnSavePre;



	private: System::Windows::Forms::Button^  btnSegConnectValley;
	private: System::Windows::Forms::Button^  btnSegOpenFile;
	private: System::Windows::Forms::Label^  lbSegPathImg;
	private: System::Windows::Forms::Label^  lbSegTitlePath;
	private: System::Windows::Forms::Button^  btnSegSave;





















	private: System::Windows::Forms::Button^  btnMAFSeg;
private: System::Windows::Forms::GroupBox^  gbSegHeighOfLine;
private: System::Windows::Forms::Button^  btnSegResetHeighOfLine;
private: System::Windows::Forms::Label^  lbSegValHeigh;




private: System::Windows::Forms::Label^  lbMaxHeigh;

private: System::Windows::Forms::Label^  lbMinHeigh;
private: System::Windows::Forms::TrackBar^  trbSegHeighOfLine;
private: System::Windows::Forms::Button^  btnSegSetHeighOfLine;
private: System::Windows::Forms::GroupBox^  gbSegMAF;
private: System::Windows::Forms::Button^  btnSegSetMAF;
private: System::Windows::Forms::Button^  btnSegResetMAF;



private: System::Windows::Forms::Label^  lbSegMAFKernel;
private: System::Windows::Forms::ComboBox^  cbbSegMAF;
private: System::Windows::Forms::ComboBox^  cbbKernelAdaptiveThreshold;


private: System::Windows::Forms::RadioButton^  rbAdaptive;
private: System::Windows::Forms::CheckBox^  cbThresholdType;

private: System::Windows::Forms::CheckBox^  cbAdaptiveMethod;







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
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->lbThresholdVal = (gcnew System::Windows::Forms::Label());
			this->lbMaxThresholdVal = (gcnew System::Windows::Forms::Label());
			this->lbMinThresholdVal = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->rbZeroInvert = (gcnew System::Windows::Forms::RadioButton());
			this->rbZero = (gcnew System::Windows::Forms::RadioButton());
			this->rbTruncate = (gcnew System::Windows::Forms::RadioButton());
			this->rbBinaryInvert = (gcnew System::Windows::Forms::RadioButton());
			this->rbBin = (gcnew System::Windows::Forms::RadioButton());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->lbPath = (gcnew System::Windows::Forms::Label());
			this->lbImage = (gcnew System::Windows::Forms::Label());
			this->btnProcess = (gcnew System::Windows::Forms::Button());
			this->gbThreshold = (gcnew System::Windows::Forms::GroupBox());
			this->cbThresholdType = (gcnew System::Windows::Forms::CheckBox());
			this->cbAdaptiveMethod = (gcnew System::Windows::Forms::CheckBox());
			this->cbbKernelAdaptiveThreshold = (gcnew System::Windows::Forms::ComboBox());
			this->rbAdaptive = (gcnew System::Windows::Forms::RadioButton());
			this->btnThresholdCls = (gcnew System::Windows::Forms::Button());
			this->cbbOrderThreshold = (gcnew System::Windows::Forms::ComboBox());
			this->gbGauss = (gcnew System::Windows::Forms::GroupBox());
			this->btnGaussCls = (gcnew System::Windows::Forms::Button());
			this->cbbOrderGauss = (gcnew System::Windows::Forms::ComboBox());
			this->lbKernelGaus = (gcnew System::Windows::Forms::Label());
			this->cbbKernelGauss = (gcnew System::Windows::Forms::ComboBox());
			this->gbAveraging = (gcnew System::Windows::Forms::GroupBox());
			this->btnAverageCls = (gcnew System::Windows::Forms::Button());
			this->cbbOrderAveraging = (gcnew System::Windows::Forms::ComboBox());
			this->lbKernelAveraging = (gcnew System::Windows::Forms::Label());
			this->cbbAveraging = (gcnew System::Windows::Forms::ComboBox());
			this->gbMedian = (gcnew System::Windows::Forms::GroupBox());
			this->btnMedianCls = (gcnew System::Windows::Forms::Button());
			this->cbbOrderMedian = (gcnew System::Windows::Forms::ComboBox());
			this->lbMedian = (gcnew System::Windows::Forms::Label());
			this->cbbMedian = (gcnew System::Windows::Forms::ComboBox());
			this->gbLaplacian = (gcnew System::Windows::Forms::GroupBox());
			this->btnLaplacianCls = (gcnew System::Windows::Forms::Button());
			this->cbbOrderLaplacian = (gcnew System::Windows::Forms::ComboBox());
			this->lbLaplacian = (gcnew System::Windows::Forms::Label());
			this->cbbLaplacian = (gcnew System::Windows::Forms::ComboBox());
			this->btnClearAll = (gcnew System::Windows::Forms::Button());
			this->tabMain = (gcnew System::Windows::Forms::TabControl());
			this->tabPagePreprocessing = (gcnew System::Windows::Forms::TabPage());
			this->btnSavePre = (gcnew System::Windows::Forms::Button());
			this->tabPageSegmentation = (gcnew System::Windows::Forms::TabPage());
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
			this->btnMAFSeg = (gcnew System::Windows::Forms::Button());
			this->btnSegSave = (gcnew System::Windows::Forms::Button());
			this->btnSegConnectValley = (gcnew System::Windows::Forms::Button());
			this->btnSegOpenFile = (gcnew System::Windows::Forms::Button());
			this->lbSegPathImg = (gcnew System::Windows::Forms::Label());
			this->lbSegTitlePath = (gcnew System::Windows::Forms::Label());
			this->btnFindValley = (gcnew System::Windows::Forms::Button());
			this->btnKhoiTao = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->gbThreshold->SuspendLayout();
			this->gbGauss->SuspendLayout();
			this->gbAveraging->SuspendLayout();
			this->gbMedian->SuspendLayout();
			this->gbLaplacian->SuspendLayout();
			this->tabMain->SuspendLayout();
			this->tabPagePreprocessing->SuspendLayout();
			this->tabPageSegmentation->SuspendLayout();
			this->gbSegMAF->SuspendLayout();
			this->gbSegHeighOfLine->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSegHeighOfLine))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// lbThresholdVal
			// 
			this->lbThresholdVal->AutoSize = true;
			this->lbThresholdVal->Location = System::Drawing::Point(691, 79);
			this->lbThresholdVal->Name = L"lbThresholdVal";
			this->lbThresholdVal->Size = System::Drawing::Size(36, 20);
			this->lbThresholdVal->TabIndex = 23;
			this->lbThresholdVal->Text = L"200";
			// 
			// lbMaxThresholdVal
			// 
			this->lbMaxThresholdVal->AutoSize = true;
			this->lbMaxThresholdVal->Location = System::Drawing::Point(628, 79);
			this->lbMaxThresholdVal->Name = L"lbMaxThresholdVal";
			this->lbMaxThresholdVal->Size = System::Drawing::Size(36, 20);
			this->lbMaxThresholdVal->TabIndex = 22;
			this->lbMaxThresholdVal->Text = L"255";
			// 
			// lbMinThresholdVal
			// 
			this->lbMinThresholdVal->AutoSize = true;
			this->lbMinThresholdVal->Location = System::Drawing::Point(11, 79);
			this->lbMinThresholdVal->Name = L"lbMinThresholdVal";
			this->lbMinThresholdVal->Size = System::Drawing::Size(18, 20);
			this->lbMinThresholdVal->TabIndex = 21;
			this->lbMinThresholdVal->Text = L"0";
			// 
			// trackBar1
			// 
			this->trackBar1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->trackBar1->Location = System::Drawing::Point(35, 55);
			this->trackBar1->Maximum = 255;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(587, 69);
			this->trackBar1->TabIndex = 20;
			this->trackBar1->Value = 200;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &frmMain::trackBar1_Scroll_1);
			// 
			// rbZeroInvert
			// 
			this->rbZeroInvert->AutoSize = true;
			this->rbZeroInvert->Location = System::Drawing::Point(547, 25);
			this->rbZeroInvert->Name = L"rbZeroInvert";
			this->rbZeroInvert->Size = System::Drawing::Size(151, 24);
			this->rbZeroInvert->TabIndex = 19;
			this->rbZeroInvert->Text = L"To Zero Inverted";
			this->rbZeroInvert->UseVisualStyleBackColor = true;
			this->rbZeroInvert->CheckedChanged += gcnew System::EventHandler(this, &frmMain::rbthreshold_CheckedChanged);
			// 
			// rbZero
			// 
			this->rbZero->AutoSize = true;
			this->rbZero->Location = System::Drawing::Point(426, 25);
			this->rbZero->Name = L"rbZero";
			this->rbZero->Size = System::Drawing::Size(89, 24);
			this->rbZero->TabIndex = 18;
			this->rbZero->Text = L"To Zero";
			this->rbZero->UseVisualStyleBackColor = true;
			this->rbZero->CheckedChanged += gcnew System::EventHandler(this, &frmMain::rbthreshold_CheckedChanged);
			// 
			// rbTruncate
			// 
			this->rbTruncate->AutoSize = true;
			this->rbTruncate->Location = System::Drawing::Point(297, 25);
			this->rbTruncate->Name = L"rbTruncate";
			this->rbTruncate->Size = System::Drawing::Size(97, 24);
			this->rbTruncate->TabIndex = 17;
			this->rbTruncate->Text = L"Truncate";
			this->rbTruncate->UseVisualStyleBackColor = true;
			this->rbTruncate->CheckedChanged += gcnew System::EventHandler(this, &frmMain::rbthreshold_CheckedChanged);
			// 
			// rbBinaryInvert
			// 
			this->rbBinaryInvert->AutoSize = true;
			this->rbBinaryInvert->Location = System::Drawing::Point(125, 25);
			this->rbBinaryInvert->Name = L"rbBinaryInvert";
			this->rbBinaryInvert->Size = System::Drawing::Size(140, 24);
			this->rbBinaryInvert->TabIndex = 16;
			this->rbBinaryInvert->Text = L"Binary Inverted";
			this->rbBinaryInvert->UseVisualStyleBackColor = true;
			this->rbBinaryInvert->CheckedChanged += gcnew System::EventHandler(this, &frmMain::rbthreshold_CheckedChanged);
			// 
			// rbBin
			// 
			this->rbBin->AutoSize = true;
			this->rbBin->Checked = true;
			this->rbBin->Location = System::Drawing::Point(15, 25);
			this->rbBin->Name = L"rbBin";
			this->rbBin->Size = System::Drawing::Size(78, 24);
			this->rbBin->TabIndex = 15;
			this->rbBin->TabStop = true;
			this->rbBin->Text = L"Binary";
			this->rbBin->UseVisualStyleBackColor = true;
			this->rbBin->CheckedChanged += gcnew System::EventHandler(this, &frmMain::rbthreshold_CheckedChanged);
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(482, 23);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(108, 31);
			this->btnOpen->TabIndex = 14;
			this->btnOpen->Text = L"Open file";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &frmMain::btnOpen_Click_1);
			// 
			// lbPath
			// 
			this->lbPath->AutoSize = true;
			this->lbPath->Location = System::Drawing::Point(141, 28);
			this->lbPath->Name = L"lbPath";
			this->lbPath->Size = System::Drawing::Size(42, 20);
			this->lbPath->TabIndex = 13;
			this->lbPath->Text = L"Path";
			// 
			// lbImage
			// 
			this->lbImage->AutoSize = true;
			this->lbImage->Location = System::Drawing::Point(77, 28);
			this->lbImage->Name = L"lbImage";
			this->lbImage->Size = System::Drawing::Size(58, 20);
			this->lbImage->TabIndex = 12;
			this->lbImage->Text = L"Image:";
			// 
			// btnProcess
			// 
			this->btnProcess->Location = System::Drawing::Point(596, 23);
			this->btnProcess->Name = L"btnProcess";
			this->btnProcess->Size = System::Drawing::Size(108, 31);
			this->btnProcess->TabIndex = 24;
			this->btnProcess->Text = L"Proccess";
			this->btnProcess->UseVisualStyleBackColor = true;
			this->btnProcess->Click += gcnew System::EventHandler(this, &frmMain::btnThreshold_Click);
			// 
			// gbThreshold
			// 
			this->gbThreshold->Controls->Add(this->cbThresholdType);
			this->gbThreshold->Controls->Add(this->cbAdaptiveMethod);
			this->gbThreshold->Controls->Add(this->cbbKernelAdaptiveThreshold);
			this->gbThreshold->Controls->Add(this->rbAdaptive);
			this->gbThreshold->Controls->Add(this->btnThresholdCls);
			this->gbThreshold->Controls->Add(this->cbbOrderThreshold);
			this->gbThreshold->Controls->Add(this->rbBinaryInvert);
			this->gbThreshold->Controls->Add(this->rbBin);
			this->gbThreshold->Controls->Add(this->lbThresholdVal);
			this->gbThreshold->Controls->Add(this->rbTruncate);
			this->gbThreshold->Controls->Add(this->lbMaxThresholdVal);
			this->gbThreshold->Controls->Add(this->rbZero);
			this->gbThreshold->Controls->Add(this->lbMinThresholdVal);
			this->gbThreshold->Controls->Add(this->rbZeroInvert);
			this->gbThreshold->Controls->Add(this->trackBar1);
			this->gbThreshold->Location = System::Drawing::Point(0, 60);
			this->gbThreshold->Name = L"gbThreshold";
			this->gbThreshold->Size = System::Drawing::Size(978, 173);
			this->gbThreshold->TabIndex = 25;
			this->gbThreshold->TabStop = false;
			this->gbThreshold->Text = L"Threshold";
			// 
			// cbThresholdType
			// 
			this->cbThresholdType->AutoSize = true;
			this->cbThresholdType->Enabled = false;
			this->cbThresholdType->Location = System::Drawing::Point(547, 130);
			this->cbThresholdType->Name = L"cbThresholdType";
			this->cbThresholdType->Size = System::Drawing::Size(358, 24);
			this->cbThresholdType->TabIndex = 35;
			this->cbThresholdType->Text = L"Threshold Type (THRESH_BINARY selected)";
			this->cbThresholdType->UseVisualStyleBackColor = true;
			this->cbThresholdType->CheckedChanged += gcnew System::EventHandler(this, &frmMain::cbAdaptive_CheckedChanged);
			// 
			// cbAdaptiveMethod
			// 
			this->cbAdaptiveMethod->AutoSize = true;
			this->cbAdaptiveMethod->Enabled = false;
			this->cbAdaptiveMethod->Location = System::Drawing::Point(15, 130);
			this->cbAdaptiveMethod->Name = L"cbAdaptiveMethod";
			this->cbAdaptiveMethod->Size = System::Drawing::Size(464, 24);
			this->cbAdaptiveMethod->TabIndex = 34;
			this->cbAdaptiveMethod->Text = L"Adaptive Method (ADAPTIVE_THRESH_MEAN_C selected)";
			this->cbAdaptiveMethod->UseVisualStyleBackColor = true;
			this->cbAdaptiveMethod->CheckedChanged += gcnew System::EventHandler(this, &frmMain::cbAdaptive_CheckedChanged);
			// 
			// cbbKernelAdaptiveThreshold
			// 
			this->cbbKernelAdaptiveThreshold->DisplayMember = L"0, 1, 2, 3";
			this->cbbKernelAdaptiveThreshold->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbKernelAdaptiveThreshold->FormattingEnabled = true;
			this->cbbKernelAdaptiveThreshold->Items->AddRange(gcnew cli::array< System::Object^  >(12) {
				L"3", L"5", L"7", L"9", L"11",
					L"13", L"15", L"17", L"19", L"21", L"23", L"25"
			});
			this->cbbKernelAdaptiveThreshold->Location = System::Drawing::Point(746, 96);
			this->cbbKernelAdaptiveThreshold->Name = L"cbbKernelAdaptiveThreshold";
			this->cbbKernelAdaptiveThreshold->Size = System::Drawing::Size(108, 28);
			this->cbbKernelAdaptiveThreshold->TabIndex = 33;
			// 
			// rbAdaptive
			// 
			this->rbAdaptive->AutoSize = true;
			this->rbAdaptive->Location = System::Drawing::Point(710, 25);
			this->rbAdaptive->Name = L"rbAdaptive";
			this->rbAdaptive->Size = System::Drawing::Size(96, 24);
			this->rbAdaptive->TabIndex = 32;
			this->rbAdaptive->Text = L"Adaptive";
			this->rbAdaptive->UseVisualStyleBackColor = true;
			this->rbAdaptive->CheckedChanged += gcnew System::EventHandler(this, &frmMain::rbthreshold_CheckedChanged);
			// 
			// btnThresholdCls
			// 
			this->btnThresholdCls->Location = System::Drawing::Point(853, 55);
			this->btnThresholdCls->Name = L"btnThresholdCls";
			this->btnThresholdCls->Size = System::Drawing::Size(108, 35);
			this->btnThresholdCls->TabIndex = 31;
			this->btnThresholdCls->Text = L"Reset";
			this->btnThresholdCls->UseVisualStyleBackColor = true;
			this->btnThresholdCls->Click += gcnew System::EventHandler(this, &frmMain::btnThresholdCls_Click);
			// 
			// cbbOrderThreshold
			// 
			this->cbbOrderThreshold->DisplayMember = L"0, 1, 2, 3";
			this->cbbOrderThreshold->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbOrderThreshold->FormattingEnabled = true;
			this->cbbOrderThreshold->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"0", L"1", L"2", L"3", L"4", L"5" });
			this->cbbOrderThreshold->Location = System::Drawing::Point(743, 55);
			this->cbbOrderThreshold->Name = L"cbbOrderThreshold";
			this->cbbOrderThreshold->Size = System::Drawing::Size(108, 28);
			this->cbbOrderThreshold->TabIndex = 24;
			// 
			// gbGauss
			// 
			this->gbGauss->Controls->Add(this->btnGaussCls);
			this->gbGauss->Controls->Add(this->cbbOrderGauss);
			this->gbGauss->Controls->Add(this->lbKernelGaus);
			this->gbGauss->Controls->Add(this->cbbKernelGauss);
			this->gbGauss->Location = System::Drawing::Point(3, 239);
			this->gbGauss->Name = L"gbGauss";
			this->gbGauss->Size = System::Drawing::Size(978, 86);
			this->gbGauss->TabIndex = 26;
			this->gbGauss->TabStop = false;
			this->gbGauss->Text = L"Gauss filtering";
			// 
			// btnGaussCls
			// 
			this->btnGaussCls->Location = System::Drawing::Point(853, 36);
			this->btnGaussCls->Name = L"btnGaussCls";
			this->btnGaussCls->Size = System::Drawing::Size(108, 35);
			this->btnGaussCls->TabIndex = 32;
			this->btnGaussCls->Text = L"Reset";
			this->btnGaussCls->UseVisualStyleBackColor = true;
			this->btnGaussCls->Click += gcnew System::EventHandler(this, &frmMain::btnGaussCls_Click);
			// 
			// cbbOrderGauss
			// 
			this->cbbOrderGauss->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbOrderGauss->FormattingEnabled = true;
			this->cbbOrderGauss->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"0", L"1", L"2", L"3", L"4", L"5" });
			this->cbbOrderGauss->Location = System::Drawing::Point(743, 37);
			this->cbbOrderGauss->Name = L"cbbOrderGauss";
			this->cbbOrderGauss->Size = System::Drawing::Size(108, 28);
			this->cbbOrderGauss->TabIndex = 27;
			// 
			// lbKernelGaus
			// 
			this->lbKernelGaus->AutoSize = true;
			this->lbKernelGaus->Location = System::Drawing::Point(119, 41);
			this->lbKernelGaus->Name = L"lbKernelGaus";
			this->lbKernelGaus->Size = System::Drawing::Size(54, 20);
			this->lbKernelGaus->TabIndex = 27;
			this->lbKernelGaus->Text = L"Kernel";
			// 
			// cbbKernelGauss
			// 
			this->cbbKernelGauss->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbKernelGauss->FormattingEnabled = true;
			this->cbbKernelGauss->Items->AddRange(gcnew cli::array< System::Object^  >(14) {
				L"3", L"5", L"7", L"9", L"11", L"13", L"15",
					L"17", L"19", L"21", L"23", L"25", L"27", L"29"
			});
			this->cbbKernelGauss->Location = System::Drawing::Point(194, 37);
			this->cbbKernelGauss->Name = L"cbbKernelGauss";
			this->cbbKernelGauss->Size = System::Drawing::Size(108, 28);
			this->cbbKernelGauss->TabIndex = 25;
			// 
			// gbAveraging
			// 
			this->gbAveraging->Controls->Add(this->btnAverageCls);
			this->gbAveraging->Controls->Add(this->cbbOrderAveraging);
			this->gbAveraging->Controls->Add(this->lbKernelAveraging);
			this->gbAveraging->Controls->Add(this->cbbAveraging);
			this->gbAveraging->Location = System::Drawing::Point(3, 331);
			this->gbAveraging->Name = L"gbAveraging";
			this->gbAveraging->Size = System::Drawing::Size(978, 110);
			this->gbAveraging->TabIndex = 27;
			this->gbAveraging->TabStop = false;
			this->gbAveraging->Text = L"Averaging filtering";
			// 
			// btnAverageCls
			// 
			this->btnAverageCls->Location = System::Drawing::Point(853, 36);
			this->btnAverageCls->Name = L"btnAverageCls";
			this->btnAverageCls->Size = System::Drawing::Size(108, 35);
			this->btnAverageCls->TabIndex = 33;
			this->btnAverageCls->Text = L"Reset";
			this->btnAverageCls->UseVisualStyleBackColor = true;
			this->btnAverageCls->Click += gcnew System::EventHandler(this, &frmMain::btnAverageCls_Click);
			// 
			// cbbOrderAveraging
			// 
			this->cbbOrderAveraging->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbOrderAveraging->FormattingEnabled = true;
			this->cbbOrderAveraging->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"0", L"1", L"2", L"3", L"4", L"5" });
			this->cbbOrderAveraging->Location = System::Drawing::Point(743, 37);
			this->cbbOrderAveraging->Name = L"cbbOrderAveraging";
			this->cbbOrderAveraging->Size = System::Drawing::Size(108, 28);
			this->cbbOrderAveraging->TabIndex = 27;
			// 
			// lbKernelAveraging
			// 
			this->lbKernelAveraging->AutoSize = true;
			this->lbKernelAveraging->Location = System::Drawing::Point(119, 41);
			this->lbKernelAveraging->Name = L"lbKernelAveraging";
			this->lbKernelAveraging->Size = System::Drawing::Size(54, 20);
			this->lbKernelAveraging->TabIndex = 27;
			this->lbKernelAveraging->Text = L"Kernel";
			// 
			// cbbAveraging
			// 
			this->cbbAveraging->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbAveraging->FormattingEnabled = true;
			this->cbbAveraging->Items->AddRange(gcnew cli::array< System::Object^  >(14) {
				L"3", L"5", L"7", L"9", L"11", L"13", L"15",
					L"17", L"19", L"21", L"23", L"25", L"27", L"29"
			});
			this->cbbAveraging->Location = System::Drawing::Point(194, 37);
			this->cbbAveraging->Name = L"cbbAveraging";
			this->cbbAveraging->Size = System::Drawing::Size(108, 28);
			this->cbbAveraging->TabIndex = 25;
			// 
			// gbMedian
			// 
			this->gbMedian->Controls->Add(this->btnMedianCls);
			this->gbMedian->Controls->Add(this->cbbOrderMedian);
			this->gbMedian->Controls->Add(this->lbMedian);
			this->gbMedian->Controls->Add(this->cbbMedian);
			this->gbMedian->Location = System::Drawing::Point(3, 447);
			this->gbMedian->Name = L"gbMedian";
			this->gbMedian->Size = System::Drawing::Size(978, 110);
			this->gbMedian->TabIndex = 28;
			this->gbMedian->TabStop = false;
			this->gbMedian->Text = L"Median filtering";
			// 
			// btnMedianCls
			// 
			this->btnMedianCls->Location = System::Drawing::Point(853, 36);
			this->btnMedianCls->Name = L"btnMedianCls";
			this->btnMedianCls->Size = System::Drawing::Size(108, 35);
			this->btnMedianCls->TabIndex = 34;
			this->btnMedianCls->Text = L"Reset";
			this->btnMedianCls->UseVisualStyleBackColor = true;
			this->btnMedianCls->Click += gcnew System::EventHandler(this, &frmMain::btnMedianCls_Click);
			// 
			// cbbOrderMedian
			// 
			this->cbbOrderMedian->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbOrderMedian->FormattingEnabled = true;
			this->cbbOrderMedian->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"0", L"1", L"2", L"3", L"4", L"5" });
			this->cbbOrderMedian->Location = System::Drawing::Point(743, 37);
			this->cbbOrderMedian->Name = L"cbbOrderMedian";
			this->cbbOrderMedian->Size = System::Drawing::Size(108, 28);
			this->cbbOrderMedian->TabIndex = 27;
			// 
			// lbMedian
			// 
			this->lbMedian->AutoSize = true;
			this->lbMedian->Location = System::Drawing::Point(119, 41);
			this->lbMedian->Name = L"lbMedian";
			this->lbMedian->Size = System::Drawing::Size(54, 20);
			this->lbMedian->TabIndex = 27;
			this->lbMedian->Text = L"Kernel";
			// 
			// cbbMedian
			// 
			this->cbbMedian->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbMedian->FormattingEnabled = true;
			this->cbbMedian->Items->AddRange(gcnew cli::array< System::Object^  >(14) {
				L"3", L"5", L"7", L"9", L"11", L"13", L"15", L"17",
					L"19", L"21", L"23", L"25", L"27", L"29"
			});
			this->cbbMedian->Location = System::Drawing::Point(194, 37);
			this->cbbMedian->Name = L"cbbMedian";
			this->cbbMedian->Size = System::Drawing::Size(108, 28);
			this->cbbMedian->TabIndex = 25;
			// 
			// gbLaplacian
			// 
			this->gbLaplacian->Controls->Add(this->btnLaplacianCls);
			this->gbLaplacian->Controls->Add(this->cbbOrderLaplacian);
			this->gbLaplacian->Controls->Add(this->lbLaplacian);
			this->gbLaplacian->Controls->Add(this->cbbLaplacian);
			this->gbLaplacian->Location = System::Drawing::Point(3, 563);
			this->gbLaplacian->Name = L"gbLaplacian";
			this->gbLaplacian->Size = System::Drawing::Size(978, 110);
			this->gbLaplacian->TabIndex = 29;
			this->gbLaplacian->TabStop = false;
			this->gbLaplacian->Text = L"Laplacian";
			// 
			// btnLaplacianCls
			// 
			this->btnLaplacianCls->Location = System::Drawing::Point(853, 36);
			this->btnLaplacianCls->Name = L"btnLaplacianCls";
			this->btnLaplacianCls->Size = System::Drawing::Size(108, 35);
			this->btnLaplacianCls->TabIndex = 35;
			this->btnLaplacianCls->Text = L"Reset";
			this->btnLaplacianCls->UseVisualStyleBackColor = true;
			this->btnLaplacianCls->Click += gcnew System::EventHandler(this, &frmMain::btnLaplacianCls_Click);
			// 
			// cbbOrderLaplacian
			// 
			this->cbbOrderLaplacian->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbOrderLaplacian->FormattingEnabled = true;
			this->cbbOrderLaplacian->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"0", L"1", L"2", L"3", L"4", L"5" });
			this->cbbOrderLaplacian->Location = System::Drawing::Point(743, 37);
			this->cbbOrderLaplacian->Name = L"cbbOrderLaplacian";
			this->cbbOrderLaplacian->Size = System::Drawing::Size(108, 28);
			this->cbbOrderLaplacian->TabIndex = 27;
			// 
			// lbLaplacian
			// 
			this->lbLaplacian->AutoSize = true;
			this->lbLaplacian->Location = System::Drawing::Point(119, 41);
			this->lbLaplacian->Name = L"lbLaplacian";
			this->lbLaplacian->Size = System::Drawing::Size(54, 20);
			this->lbLaplacian->TabIndex = 27;
			this->lbLaplacian->Text = L"Kernel";
			// 
			// cbbLaplacian
			// 
			this->cbbLaplacian->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbbLaplacian->FormattingEnabled = true;
			this->cbbLaplacian->Items->AddRange(gcnew cli::array< System::Object^  >(14) {
				L"3", L"5", L"7", L"9", L"11", L"13", L"15",
					L"17", L"19", L"21", L"23", L"25", L"27", L"29"
			});
			this->cbbLaplacian->Location = System::Drawing::Point(194, 37);
			this->cbbLaplacian->Name = L"cbbLaplacian";
			this->cbbLaplacian->Size = System::Drawing::Size(108, 28);
			this->cbbLaplacian->TabIndex = 25;
			// 
			// btnClearAll
			// 
			this->btnClearAll->Location = System::Drawing::Point(710, 23);
			this->btnClearAll->Name = L"btnClearAll";
			this->btnClearAll->Size = System::Drawing::Size(108, 31);
			this->btnClearAll->TabIndex = 30;
			this->btnClearAll->Text = L"Reset All";
			this->btnClearAll->UseVisualStyleBackColor = true;
			this->btnClearAll->Click += gcnew System::EventHandler(this, &frmMain::btnClearAll_Click);
			// 
			// tabMain
			// 
			this->tabMain->Controls->Add(this->tabPagePreprocessing);
			this->tabMain->Controls->Add(this->tabPageSegmentation);
			this->tabMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabMain->Location = System::Drawing::Point(0, 0);
			this->tabMain->Name = L"tabMain";
			this->tabMain->SelectedIndex = 0;
			this->tabMain->Size = System::Drawing::Size(1002, 712);
			this->tabMain->TabIndex = 31;
			// 
			// tabPagePreprocessing
			// 
			this->tabPagePreprocessing->Controls->Add(this->btnSavePre);
			this->tabPagePreprocessing->Controls->Add(this->btnClearAll);
			this->tabPagePreprocessing->Controls->Add(this->gbThreshold);
			this->tabPagePreprocessing->Controls->Add(this->btnProcess);
			this->tabPagePreprocessing->Controls->Add(this->gbLaplacian);
			this->tabPagePreprocessing->Controls->Add(this->btnOpen);
			this->tabPagePreprocessing->Controls->Add(this->gbGauss);
			this->tabPagePreprocessing->Controls->Add(this->lbPath);
			this->tabPagePreprocessing->Controls->Add(this->gbMedian);
			this->tabPagePreprocessing->Controls->Add(this->lbImage);
			this->tabPagePreprocessing->Controls->Add(this->gbAveraging);
			this->tabPagePreprocessing->Location = System::Drawing::Point(4, 29);
			this->tabPagePreprocessing->Name = L"tabPagePreprocessing";
			this->tabPagePreprocessing->Padding = System::Windows::Forms::Padding(3);
			this->tabPagePreprocessing->Size = System::Drawing::Size(994, 679);
			this->tabPagePreprocessing->TabIndex = 0;
			this->tabPagePreprocessing->Text = L"Tiền xử lý";
			this->tabPagePreprocessing->UseVisualStyleBackColor = true;
			// 
			// btnSavePre
			// 
			this->btnSavePre->Location = System::Drawing::Point(824, 23);
			this->btnSavePre->Name = L"btnSavePre";
			this->btnSavePre->Size = System::Drawing::Size(99, 31);
			this->btnSavePre->TabIndex = 31;
			this->btnSavePre->Text = L"Save";
			this->btnSavePre->UseVisualStyleBackColor = true;
			this->btnSavePre->Click += gcnew System::EventHandler(this, &frmMain::btnSavePre_Click);
			// 
			// tabPageSegmentation
			// 
			this->tabPageSegmentation->Controls->Add(this->gbSegMAF);
			this->tabPageSegmentation->Controls->Add(this->gbSegHeighOfLine);
			this->tabPageSegmentation->Controls->Add(this->btnMAFSeg);
			this->tabPageSegmentation->Controls->Add(this->btnSegSave);
			this->tabPageSegmentation->Controls->Add(this->btnSegConnectValley);
			this->tabPageSegmentation->Controls->Add(this->btnSegOpenFile);
			this->tabPageSegmentation->Controls->Add(this->lbSegPathImg);
			this->tabPageSegmentation->Controls->Add(this->lbSegTitlePath);
			this->tabPageSegmentation->Controls->Add(this->btnFindValley);
			this->tabPageSegmentation->Controls->Add(this->btnKhoiTao);
			this->tabPageSegmentation->Location = System::Drawing::Point(4, 29);
			this->tabPageSegmentation->Name = L"tabPageSegmentation";
			this->tabPageSegmentation->Padding = System::Windows::Forms::Padding(3);
			this->tabPageSegmentation->Size = System::Drawing::Size(994, 679);
			this->tabPageSegmentation->TabIndex = 1;
			this->tabPageSegmentation->Text = L"Phân đoạn";
			this->tabPageSegmentation->UseVisualStyleBackColor = true;
			// 
			// gbSegMAF
			// 
			this->gbSegMAF->Controls->Add(this->btnSegSetMAF);
			this->gbSegMAF->Controls->Add(this->btnSegResetMAF);
			this->gbSegMAF->Controls->Add(this->lbSegMAFKernel);
			this->gbSegMAF->Controls->Add(this->cbbSegMAF);
			this->gbSegMAF->Location = System::Drawing::Point(12, 67);
			this->gbSegMAF->Name = L"gbSegMAF";
			this->gbSegMAF->Size = System::Drawing::Size(978, 110);
			this->gbSegMAF->TabIndex = 40;
			this->gbSegMAF->TabStop = false;
			this->gbSegMAF->Text = L"Moving Average Filter";
			// 
			// btnSegSetMAF
			// 
			this->btnSegSetMAF->Location = System::Drawing::Point(850, 17);
			this->btnSegSetMAF->Name = L"btnSegSetMAF";
			this->btnSegSetMAF->Size = System::Drawing::Size(108, 35);
			this->btnSegSetMAF->TabIndex = 33;
			this->btnSegSetMAF->Text = L"Set";
			this->btnSegSetMAF->UseVisualStyleBackColor = true;
			this->btnSegSetMAF->Click += gcnew System::EventHandler(this, &frmMain::btnSegSetMAF_Click);
			// 
			// btnSegResetMAF
			// 
			this->btnSegResetMAF->Location = System::Drawing::Point(850, 58);
			this->btnSegResetMAF->Name = L"btnSegResetMAF";
			this->btnSegResetMAF->Size = System::Drawing::Size(108, 35);
			this->btnSegResetMAF->TabIndex = 32;
			this->btnSegResetMAF->Text = L"Reset";
			this->btnSegResetMAF->UseVisualStyleBackColor = true;
			this->btnSegResetMAF->Click += gcnew System::EventHandler(this, &frmMain::btnSegResetMAF_Click);
			// 
			// lbSegMAFKernel
			// 
			this->lbSegMAFKernel->AutoSize = true;
			this->lbSegMAFKernel->Location = System::Drawing::Point(119, 41);
			this->lbSegMAFKernel->Name = L"lbSegMAFKernel";
			this->lbSegMAFKernel->Size = System::Drawing::Size(54, 20);
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
			this->cbbSegMAF->Location = System::Drawing::Point(194, 37);
			this->cbbSegMAF->Name = L"cbbSegMAF";
			this->cbbSegMAF->Size = System::Drawing::Size(108, 28);
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
			this->gbSegHeighOfLine->Location = System::Drawing::Point(13, 183);
			this->gbSegHeighOfLine->Name = L"gbSegHeighOfLine";
			this->gbSegHeighOfLine->Size = System::Drawing::Size(978, 110);
			this->gbSegHeighOfLine->TabIndex = 39;
			this->gbSegHeighOfLine->TabStop = false;
			this->gbSegHeighOfLine->Text = L"Heigh of line";
			// 
			// btnSegSetHeighOfLine
			// 
			this->btnSegSetHeighOfLine->Location = System::Drawing::Point(849, 12);
			this->btnSegSetHeighOfLine->Name = L"btnSegSetHeighOfLine";
			this->btnSegSetHeighOfLine->Size = System::Drawing::Size(108, 35);
			this->btnSegSetHeighOfLine->TabIndex = 32;
			this->btnSegSetHeighOfLine->Text = L"Set";
			this->btnSegSetHeighOfLine->UseVisualStyleBackColor = true;
			this->btnSegSetHeighOfLine->Click += gcnew System::EventHandler(this, &frmMain::btnSegSetHeighOfLine_Click);
			// 
			// btnSegResetHeighOfLine
			// 
			this->btnSegResetHeighOfLine->Location = System::Drawing::Point(849, 53);
			this->btnSegResetHeighOfLine->Name = L"btnSegResetHeighOfLine";
			this->btnSegResetHeighOfLine->Size = System::Drawing::Size(108, 35);
			this->btnSegResetHeighOfLine->TabIndex = 31;
			this->btnSegResetHeighOfLine->Text = L"Reset";
			this->btnSegResetHeighOfLine->UseVisualStyleBackColor = true;
			this->btnSegResetHeighOfLine->Click += gcnew System::EventHandler(this, &frmMain::btnSegResetHeighOfLine_Click);
			// 
			// lbSegValHeigh
			// 
			this->lbSegValHeigh->AutoSize = true;
			this->lbSegValHeigh->Location = System::Drawing::Point(791, 53);
			this->lbSegValHeigh->Name = L"lbSegValHeigh";
			this->lbSegValHeigh->Size = System::Drawing::Size(27, 20);
			this->lbSegValHeigh->TabIndex = 23;
			this->lbSegValHeigh->Text = L"40";
			// 
			// lbMaxHeigh
			// 
			this->lbMaxHeigh->AutoSize = true;
			this->lbMaxHeigh->Location = System::Drawing::Point(728, 53);
			this->lbMaxHeigh->Name = L"lbMaxHeigh";
			this->lbMaxHeigh->Size = System::Drawing::Size(36, 20);
			this->lbMaxHeigh->TabIndex = 22;
			this->lbMaxHeigh->Text = L"128";
			// 
			// lbMinHeigh
			// 
			this->lbMinHeigh->AutoSize = true;
			this->lbMinHeigh->Location = System::Drawing::Point(13, 53);
			this->lbMinHeigh->Name = L"lbMinHeigh";
			this->lbMinHeigh->Size = System::Drawing::Size(18, 20);
			this->lbMinHeigh->TabIndex = 21;
			this->lbMinHeigh->Text = L"0";
			// 
			// trbSegHeighOfLine
			// 
			this->trbSegHeighOfLine->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->trbSegHeighOfLine->Location = System::Drawing::Point(37, 29);
			this->trbSegHeighOfLine->Maximum = 128;
			this->trbSegHeighOfLine->Name = L"trbSegHeighOfLine";
			this->trbSegHeighOfLine->Size = System::Drawing::Size(685, 69);
			this->trbSegHeighOfLine->TabIndex = 20;
			this->trbSegHeighOfLine->Value = 40;
			this->trbSegHeighOfLine->Scroll += gcnew System::EventHandler(this, &frmMain::trbSegHeighOfLine_Scroll);
			// 
			// btnMAFSeg
			// 
			this->btnMAFSeg->Location = System::Drawing::Point(305, 360);
			this->btnMAFSeg->Name = L"btnMAFSeg";
			this->btnMAFSeg->Size = System::Drawing::Size(126, 36);
			this->btnMAFSeg->TabIndex = 35;
			this->btnMAFSeg->Text = L"MAF";
			this->btnMAFSeg->UseVisualStyleBackColor = true;
			this->btnMAFSeg->Click += gcnew System::EventHandler(this, &frmMain::btnMAFSeg_Click);
			// 
			// btnSegSave
			// 
			this->btnSegSave->Location = System::Drawing::Point(700, 360);
			this->btnSegSave->Name = L"btnSegSave";
			this->btnSegSave->Size = System::Drawing::Size(126, 36);
			this->btnSegSave->TabIndex = 34;
			this->btnSegSave->Text = L"Save";
			this->btnSegSave->UseVisualStyleBackColor = true;
			this->btnSegSave->Click += gcnew System::EventHandler(this, &frmMain::btnSegSave_Click);
			// 
			// btnSegConnectValley
			// 
			this->btnSegConnectValley->Location = System::Drawing::Point(569, 360);
			this->btnSegConnectValley->Name = L"btnSegConnectValley";
			this->btnSegConnectValley->Size = System::Drawing::Size(126, 36);
			this->btnSegConnectValley->TabIndex = 33;
			this->btnSegConnectValley->Text = L"Connect Valley";
			this->btnSegConnectValley->UseVisualStyleBackColor = true;
			this->btnSegConnectValley->Click += gcnew System::EventHandler(this, &frmMain::btnSegConnectValley_Click);
			// 
			// btnSegOpenFile
			// 
			this->btnSegOpenFile->Location = System::Drawing::Point(849, 25);
			this->btnSegOpenFile->Name = L"btnSegOpenFile";
			this->btnSegOpenFile->Size = System::Drawing::Size(126, 36);
			this->btnSegOpenFile->TabIndex = 32;
			this->btnSegOpenFile->Text = L"Open file";
			this->btnSegOpenFile->UseVisualStyleBackColor = true;
			this->btnSegOpenFile->Click += gcnew System::EventHandler(this, &frmMain::btnSegOpenFile_Click);
			// 
			// lbSegPathImg
			// 
			this->lbSegPathImg->AutoSize = true;
			this->lbSegPathImg->Location = System::Drawing::Point(92, 33);
			this->lbSegPathImg->Name = L"lbSegPathImg";
			this->lbSegPathImg->Size = System::Drawing::Size(42, 20);
			this->lbSegPathImg->TabIndex = 31;
			this->lbSegPathImg->Text = L"Path";
			// 
			// lbSegTitlePath
			// 
			this->lbSegTitlePath->AutoSize = true;
			this->lbSegTitlePath->Location = System::Drawing::Point(19, 33);
			this->lbSegTitlePath->Name = L"lbSegTitlePath";
			this->lbSegTitlePath->Size = System::Drawing::Size(58, 20);
			this->lbSegTitlePath->TabIndex = 30;
			this->lbSegTitlePath->Text = L"Image:";
			// 
			// btnFindValley
			// 
			this->btnFindValley->Location = System::Drawing::Point(437, 360);
			this->btnFindValley->Name = L"btnFindValley";
			this->btnFindValley->Size = System::Drawing::Size(126, 36);
			this->btnFindValley->TabIndex = 29;
			this->btnFindValley->Text = L"Find Valley";
			this->btnFindValley->UseVisualStyleBackColor = true;
			this->btnFindValley->Click += gcnew System::EventHandler(this, &frmMain::btnFindValley_Click);
			// 
			// btnKhoiTao
			// 
			this->btnKhoiTao->Location = System::Drawing::Point(173, 360);
			this->btnKhoiTao->Name = L"btnKhoiTao";
			this->btnKhoiTao->Size = System::Drawing::Size(126, 36);
			this->btnKhoiTao->TabIndex = 0;
			this->btnKhoiTao->Text = L"Init";
			this->btnKhoiTao->UseVisualStyleBackColor = true;
			this->btnKhoiTao->Click += gcnew System::EventHandler(this, &frmMain::btnKhoiTao_Click);
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1002, 712);
			this->Controls->Add(this->tabMain);
			this->MaximumSize = System::Drawing::Size(1024, 768);
			this->MinimumSize = System::Drawing::Size(1024, 768);
			this->Name = L"frmMain";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Tiền xử lý ảnh nhận dạng chữ viết tay";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->gbThreshold->ResumeLayout(false);
			this->gbThreshold->PerformLayout();
			this->gbGauss->ResumeLayout(false);
			this->gbGauss->PerformLayout();
			this->gbAveraging->ResumeLayout(false);
			this->gbAveraging->PerformLayout();
			this->gbMedian->ResumeLayout(false);
			this->gbMedian->PerformLayout();
			this->gbLaplacian->ResumeLayout(false);
			this->gbLaplacian->PerformLayout();
			this->tabMain->ResumeLayout(false);
			this->tabPagePreprocessing->ResumeLayout(false);
			this->tabPagePreprocessing->PerformLayout();
			this->tabPageSegmentation->ResumeLayout(false);
			this->tabPageSegmentation->PerformLayout();
			this->gbSegMAF->ResumeLayout(false);
			this->gbSegMAF->PerformLayout();
			this->gbSegHeighOfLine->ResumeLayout(false);
			this->gbSegHeighOfLine->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSegHeighOfLine))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnOpen_Click_1(System::Object^  sender, System::EventArgs^  e);
			 System::Void trackBar1_Scroll_1(System::Object^  sender, System::EventArgs^  e);
			 System::Void rbthreshold_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
			 System::Void cbAdaptive_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnThreshold_Click(System::Object^  sender, System::EventArgs^  e);
			 int OpenCV_Threshold::frmMain::min(int a, int b);
			 System::Void btnClearAll_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnSavePre_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnThresholdCls_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnGaussCls_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnAverageCls_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnMedianCls_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnLaplacianCls_Click(System::Object^  sender, System::EventArgs^  e);
			 //Tab phân đoạn
			 System::Void btnSegOpenFile_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnKhoiTao_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnFindValley_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnSegSave_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnMAFSeg_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnSegConnectValley_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void trbSegHeighOfLine_Scroll(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnSegSetMAF_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnSegResetMAF_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnSegSetHeighOfLine_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void btnSegResetHeighOfLine_Click(System::Object^  sender, System::EventArgs^  e);
			 
	private:
			Preprocess* preprocess;
			Segmentation* segment;
			Extent* extent = new Extent(); 
			double elapsed_secs = 0;
};
}
