#pragma once

namespace Thesis {

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
	private: System::Windows::Forms::TabPage^  tabPageSecond;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::CheckBox^  checkBox5;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  lbSegValHeigh;
	private: System::Windows::Forms::Label^  lbMaxHeigh;
	private: System::Windows::Forms::Label^  lbMinHeigh;
	private: System::Windows::Forms::TrackBar^  trbSegHeighOfLine;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Button^  button6;








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
			this->tabPageSecond = (gcnew System::Windows::Forms::TabPage());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->lbSegValHeigh = (gcnew System::Windows::Forms::Label());
			this->lbMaxHeigh = (gcnew System::Windows::Forms::Label());
			this->lbMinHeigh = (gcnew System::Windows::Forms::Label());
			this->trbSegHeighOfLine = (gcnew System::Windows::Forms::TrackBar());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->tabControlFirst->SuspendLayout();
			this->tabPageFirst->SuspendLayout();
			this->tabPageSecond->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSegHeighOfLine))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControlFirst
			// 
			this->tabControlFirst->Controls->Add(this->tabPageFirst);
			this->tabControlFirst->Controls->Add(this->tabPageSecond);
			this->tabControlFirst->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControlFirst->Location = System::Drawing::Point(0, 0);
			this->tabControlFirst->Name = L"tabControlFirst";
			this->tabControlFirst->SelectedIndex = 0;
			this->tabControlFirst->Size = System::Drawing::Size(1002, 712);
			this->tabControlFirst->TabIndex = 0;
			// 
			// tabPageFirst
			// 
			this->tabPageFirst->Controls->Add(this->label9);
			this->tabPageFirst->Controls->Add(this->label10);
			this->tabPageFirst->Controls->Add(this->button6);
			this->tabPageFirst->Controls->Add(this->groupBox4);
			this->tabPageFirst->Controls->Add(this->groupBox3);
			this->tabPageFirst->Controls->Add(this->groupBox2);
			this->tabPageFirst->Controls->Add(this->groupBox1);
			this->tabPageFirst->Controls->Add(this->label2);
			this->tabPageFirst->Controls->Add(this->label1);
			this->tabPageFirst->Controls->Add(this->button2);
			this->tabPageFirst->Controls->Add(this->textBox1);
			this->tabPageFirst->Controls->Add(this->button1);
			this->tabPageFirst->Location = System::Drawing::Point(4, 29);
			this->tabPageFirst->Name = L"tabPageFirst";
			this->tabPageFirst->Padding = System::Windows::Forms::Padding(3);
			this->tabPageFirst->Size = System::Drawing::Size(994, 679);
			this->tabPageFirst->TabIndex = 0;
			this->tabPageFirst->Text = L"Tìm kiếm";
			this->tabPageFirst->UseVisualStyleBackColor = true;
			// 
			// tabPageSecond
			// 
			this->tabPageSecond->Controls->Add(this->label7);
			this->tabPageSecond->Controls->Add(this->label8);
			this->tabPageSecond->Controls->Add(this->button5);
			this->tabPageSecond->Controls->Add(this->button4);
			this->tabPageSecond->Controls->Add(this->label3);
			this->tabPageSecond->Controls->Add(this->label4);
			this->tabPageSecond->Controls->Add(this->button3);
			this->tabPageSecond->Location = System::Drawing::Point(4, 29);
			this->tabPageSecond->Name = L"tabPageSecond";
			this->tabPageSecond->Padding = System::Windows::Forms::Padding(3);
			this->tabPageSecond->Size = System::Drawing::Size(994, 679);
			this->tabPageSecond->TabIndex = 1;
			this->tabPageSecond->Text = L"Thu thập tập dữ liệu";
			this->tabPageSecond->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(828, 22);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(158, 38);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Tìm kiếm";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(25, 22);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(797, 76);
			this->textBox1->TabIndex = 1;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(828, 107);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(158, 38);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Chọn ảnh";
			this->button2->UseVisualStyleBackColor = true;
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
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(121, 102);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 20);
			this->label2->TabIndex = 4;
			this->label2->Text = L"FakePath/";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->checkBox3);
			this->groupBox1->Controls->Add(this->checkBox2);
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Location = System::Drawing::Point(8, 195);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(978, 123);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Tùy chọn tiền xử lý";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->checkBox4);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->lbSegValHeigh);
			this->groupBox2->Controls->Add(this->lbMaxHeigh);
			this->groupBox2->Controls->Add(this->lbMinHeigh);
			this->groupBox2->Controls->Add(this->trbSegHeighOfLine);
			this->groupBox2->Controls->Add(this->comboBox1);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Location = System::Drawing::Point(8, 318);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(978, 118);
			this->groupBox2->TabIndex = 6;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Tùy chọn phân đoạn";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->radioButton3);
			this->groupBox3->Controls->Add(this->radioButton2);
			this->groupBox3->Controls->Add(this->radioButton1);
			this->groupBox3->Controls->Add(this->checkBox5);
			this->groupBox3->Location = System::Drawing::Point(8, 442);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(980, 106);
			this->groupBox3->TabIndex = 7;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Tùy chọn rút trích đặt trưng";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->radioButton4);
			this->groupBox4->Controls->Add(this->radioButton5);
			this->groupBox4->Controls->Add(this->radioButton6);
			this->groupBox4->Location = System::Drawing::Point(6, 554);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(983, 100);
			this->groupBox4->TabIndex = 8;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Tùy chọn so khớp Dynamic Time Warping";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(170, 30);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(82, 20);
			this->label3->TabIndex = 7;
			this->label3->Text = L"FakePath/";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(72, 30);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(92, 20);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Đường dẫn:";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(513, 30);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(127, 38);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Chọn thư mục";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(33, 41);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(172, 24);
			this->checkBox1->TabIndex = 0;
			this->checkBox1->Text = L"Lọc nhiễu muối tiêu";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Checked = true;
			this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox2->Location = System::Drawing::Point(244, 41);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(130, 24);
			this->checkBox2->TabIndex = 1;
			this->checkBox2->Text = L"Phân ngưỡng";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(408, 49);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(258, 24);
			this->checkBox3->TabIndex = 2;
			this->checkBox3->Text = L"Kết hợp Morphological Gradient";
			this->checkBox3->UseVisualStyleBackColor = true;
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
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(17, 51);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 28);
			this->comboBox1->TabIndex = 5;
			// 
			// lbSegValHeigh
			// 
			this->lbSegValHeigh->AutoSize = true;
			this->lbSegValHeigh->Location = System::Drawing::Point(695, 49);
			this->lbSegValHeigh->Name = L"lbSegValHeigh";
			this->lbSegValHeigh->Size = System::Drawing::Size(27, 20);
			this->lbSegValHeigh->TabIndex = 27;
			this->lbSegValHeigh->Text = L"40";
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
			this->trbSegHeighOfLine->Value = 40;
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
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Checked = true;
			this->checkBox5->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox5->Location = System::Drawing::Point(603, 51);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(160, 24);
			this->checkBox5->TabIndex = 2;
			this->checkBox5->Text = L"Projection profiles";
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(762, 54);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(192, 24);
			this->checkBox4->TabIndex = 29;
			this->checkBox4->Text = L"Chuẩn hóa từ nghiêng";
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(33, 50);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(127, 24);
			this->radioButton1->TabIndex = 3;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Word profiles";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(166, 51);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(140, 24);
			this->radioButton2->TabIndex = 4;
			this->radioButton2->Text = L"Chỉ upper word";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(316, 51);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(136, 24);
			this->radioButton3->TabIndex = 5;
			this->radioButton3->Text = L"Chỉ lower word";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(573, 41);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(283, 24);
			this->radioButton4->TabIndex = 8;
			this->radioButton4->Text = L"Ràng buộc hình bình hành - Itakura";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(272, 41);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(281, 24);
			this->radioButton5->TabIndex = 7;
			this->radioButton5->Text = L"Ràng buộc hình thoi - Sakoe-Chiba";
			this->radioButton5->UseVisualStyleBackColor = true;
			// 
			// radioButton6
			// 
			this->radioButton6->AutoSize = true;
			this->radioButton6->Checked = true;
			this->radioButton6->Location = System::Drawing::Point(33, 41);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(219, 24);
			this->radioButton6->TabIndex = 6;
			this->radioButton6->TabStop = true;
			this->radioButton6->Text = L"Non global path constraint";
			this->radioButton6->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(513, 137);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(127, 38);
			this->button4->TabIndex = 8;
			this->button4->Text = L"Lập dữ liệu";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(170, 78);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(82, 20);
			this->label7->TabIndex = 11;
			this->label7->Text = L"FakePath/";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(72, 78);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(92, 20);
			this->label8->TabIndex = 10;
			this->label8->Text = L"Đường dẫn:";
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(513, 78);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(127, 38);
			this->button5->TabIndex = 9;
			this->button5->Text = L"Chọn thư mục";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(121, 151);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(82, 20);
			this->label9->TabIndex = 11;
			this->label9->Text = L"FakePath/";
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
			// button6
			// 
			this->button6->Location = System::Drawing::Point(828, 151);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(158, 38);
			this->button6->TabIndex = 9;
			this->button6->Text = L"Chọn folder CSDL";
			this->button6->UseVisualStyleBackColor = true;
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
			this->tabPageSecond->ResumeLayout(false);
			this->tabPageSecond->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSegHeighOfLine))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	public: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
