#pragma once
#include "frmPreprocessing.h"
#include "frmSegmentation.h"
#include "frmExtractFeatures.h"
#include "frmDTW.h"
#include "frmNormalization.h"

namespace OpenCV_JP {

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
	private: System::Windows::Forms::Button^  btnPre;
	protected:
	private: System::Windows::Forms::Button^  btnExtract;
	private: System::Windows::Forms::Button^  btnNormal;
	private: System::Windows::Forms::Button^  btnSeg;
	private: System::Windows::Forms::Button^  btnDTW;

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
			this->btnPre = (gcnew System::Windows::Forms::Button());
			this->btnExtract = (gcnew System::Windows::Forms::Button());
			this->btnNormal = (gcnew System::Windows::Forms::Button());
			this->btnSeg = (gcnew System::Windows::Forms::Button());
			this->btnDTW = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnPre
			// 
			this->btnPre->Location = System::Drawing::Point(12, 12);
			this->btnPre->Name = L"btnPre";
			this->btnPre->Size = System::Drawing::Size(598, 28);
			this->btnPre->TabIndex = 1;
			this->btnPre->Text = L"Step 1: Pre-processing";
			this->btnPre->UseVisualStyleBackColor = true;
			this->btnPre->Click += gcnew System::EventHandler(this, &frmMain::btnPre_Click);
			// 
			// btnExtract
			// 
			this->btnExtract->Location = System::Drawing::Point(12, 114);
			this->btnExtract->Name = L"btnExtract";
			this->btnExtract->Size = System::Drawing::Size(598, 28);
			this->btnExtract->TabIndex = 4;
			this->btnExtract->Text = L"Step 4: Extracting features";
			this->btnExtract->UseVisualStyleBackColor = true;
			this->btnExtract->Click += gcnew System::EventHandler(this, &frmMain::btnExtract_Click);
			// 
			// btnNormal
			// 
			this->btnNormal->Location = System::Drawing::Point(12, 80);
			this->btnNormal->Name = L"btnNormal";
			this->btnNormal->Size = System::Drawing::Size(598, 28);
			this->btnNormal->TabIndex = 3;
			this->btnNormal->Text = L"Step 3: Normalization";
			this->btnNormal->UseVisualStyleBackColor = true;
			this->btnNormal->Click += gcnew System::EventHandler(this, &frmMain::btnNormal_Click);
			// 
			// btnSeg
			// 
			this->btnSeg->Location = System::Drawing::Point(12, 46);
			this->btnSeg->Name = L"btnSeg";
			this->btnSeg->Size = System::Drawing::Size(598, 28);
			this->btnSeg->TabIndex = 2;
			this->btnSeg->Text = L"Step 2: Segmentation";
			this->btnSeg->UseVisualStyleBackColor = true;
			this->btnSeg->Click += gcnew System::EventHandler(this, &frmMain::btnSeg_Click);
			// 
			// btnDTW
			// 
			this->btnDTW->Location = System::Drawing::Point(12, 148);
			this->btnDTW->Name = L"btnDTW";
			this->btnDTW->Size = System::Drawing::Size(598, 28);
			this->btnDTW->TabIndex = 5;
			this->btnDTW->Text = L"Step 5: DTW";
			this->btnDTW->UseVisualStyleBackColor = true;
			this->btnDTW->Click += gcnew System::EventHandler(this, &frmMain::btnDTW_Click);
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(622, 435);
			this->Controls->Add(this->btnDTW);
			this->Controls->Add(this->btnSeg);
			this->Controls->Add(this->btnNormal);
			this->Controls->Add(this->btnExtract);
			this->Controls->Add(this->btnPre);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximumSize = System::Drawing::Size(640, 480);
			this->MinimumSize = System::Drawing::Size(640, 480);
			this->Name = L"frmMain";
			this->Text = L"Main form";
			this->ResumeLayout(false);

		}
#pragma endregion
	private:	System::Void btnPre_Click(System::Object^  sender, System::EventArgs^  e);
				System::Void btnSeg_Click(System::Object^  sender, System::EventArgs^  e);
				System::Void btnNormal_Click(System::Object^  sender, System::EventArgs^  e);
				System::Void btnExtract_Click(System::Object^  sender, System::EventArgs^  e);
				System::Void btnDTW_Click(System::Object^  sender, System::EventArgs^  e);
};
}
