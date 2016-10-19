#include "frmPreprocessing.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = std::experimental::filesystem;
using namespace System;
using namespace System::IO;

System::Void OpenCV_JP::frmPreprocessing::btnOpenInput_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	folderBrowserDialog->SelectedPath = "D:\\Input\\";
	if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		this->lbInput->Text = folderBrowserDialog->SelectedPath;
}

System::Void OpenCV_JP::frmPreprocessing::btnOpenOutput_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	folderBrowserDialog->SelectedPath = "D:\\Output\\";
	if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		this->lbOutput->Text = folderBrowserDialog->SelectedPath;
}


System::Void OpenCV_JP::frmPreprocessing::btnStart_Click(System::Object ^ sender, System::EventArgs ^ e)
{

	fs::path directory("D:\\");
	fs::directory_iterator iter(directory), end;

	for (; iter != end; ++iter)
	{
		if (iter->path().extension() == ".jpg" | iter->path().extension() == ".JPG")
		{
			cout << iter->path().filename() << endl;
		}
	}

	//1 - Median check
	if (cbMedian->Checked) {
		int kernelMedian = trbMedian->Value * 2 + 1;
		//Processing
	}
	//2 - Laplacian check
	if (cbLaplacian->Checked) {
		int kernelLaplacian = trbLaplacian->Value * 2 + 1;
		//Processing
	}
	//3 - Thresholding check
	if (cbThresholding->Checked) {
		int thresholding_val = trbThresholding->Value;
		if (cbLaplacian->Checked) {
			//Processing
		}
		else {
			//Processing
		}
	}
	//4 - Opening check
	if (cbOpening->Checked) {
		int kernelOpening = trbOpening->Value * 2 + 1;
		//Processing
	}
}

System::Void OpenCV_JP::frmPreprocessing::trbMedian_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	string model(to_string(trbMedian->Value * 2 + 1));
	System::String^ val = gcnew System::String(model.c_str());
	lbKernelMedian->Text = val;
}

System::Void OpenCV_JP::frmPreprocessing::trbLaplacian_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	string model(to_string(trbLaplacian->Value * 2 + 1));
	System::String^ val = gcnew System::String(model.c_str());
	lbKernelLaplacian->Text = val;
}

System::Void OpenCV_JP::frmPreprocessing::trbThresholding_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	string model(to_string(trbThresholding->Value));
	System::String^ val = gcnew System::String(model.c_str());
	lbValThresholding->Text = val;
}

System::Void OpenCV_JP::frmPreprocessing::trbOpening_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	string model(to_string(trbOpening->Value * 2 + 1));
	System::String^ val = gcnew System::String(model.c_str());
	lbKernelOpening->Text = val;
}

