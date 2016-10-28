#include "frmPreprocessing.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <algorithm>


using namespace std;
namespace fs = std::experimental::filesystem;
using namespace System;
using namespace System::IO;
using namespace System::Threading;

System::Void OpenCV_JP::frmPreprocessing::btnOpenInput_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	folderBrowserDialog->SelectedPath = "D:\\Input\\";
	if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		this->lbInput->Text = folderBrowserDialog->SelectedPath;
}

System::Void OpenCV_JP::frmPreprocessing::btnCancel_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	backgroundWorker->CancelAsync();   //cancel backgroundworker
}

System::Void OpenCV_JP::frmPreprocessing::btnOpenOutput_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	folderBrowserDialog->SelectedPath = "D:\\Output\\";
	if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		this->lbOutput->Text = folderBrowserDialog->SelectedPath;
}


System::Void OpenCV_JP::frmPreprocessing::btnStart_Click(System::Object ^ sender, System::EventArgs ^ e)
{

	/*int* mask = (int*)calloc(3, sizeof( int));
	memset(mask, -1, 3 * sizeof(int));

	mask = (int*)realloc(mask, 8 * sizeof( int));
	for (int i = 3; i < 8; i++) {
		*(mask + i) = -1;
	}

	this->preprocess = new Preprocess(Mat(), Mat());
	int val = 4;
	this->preprocess->addElement(mask, val, 8);
	val = 3;
	this->preprocess->addElement(mask, val, 8);
	val = 1;
	this->preprocess->addElement(mask, val, 8);
	val = 3;
	this->preprocess->addElement(mask, val, 8);
	val = 5;
	this->preprocess->addElement(mask, val, 8);
	val = 0;
	this->preprocess->addElement(mask, val, 8);
	val = 0;
	this->preprocess->addElement(mask, val, 8);
	val = 1;
	this->preprocess->addElement(mask, val, 8);
	val = 9;
	this->preprocess->addElement(mask, val, 8);*/

	//for (int i = 0; i < 8; i++) {
	//	cout << *(mask + i) << endl;
	//}

	btnStart->Enabled = false;
	btnCancel->Enabled = true;

	backgroundWorker->RunWorkerAsync();  //starting background worker
}

System::Void OpenCV_JP::frmPreprocessing::trbMedian_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	string model(to_string(trbMedian->Value * 2 + 1));
	System::String^ val = gcnew System::String(model.c_str());
	lbKernelMedian->Text = val;
}

System::Void OpenCV_JP::frmPreprocessing::backgroundWorker_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	string path_image;
	this->extent->MarshalString(lbInput->Text, path_image);
	fs::path directory (path_image);
	fs::directory_iterator iter(directory), end;

	for (; iter != end; ++iter)
	{
		if (iter->path().extension() == ".jpg" | iter->path().extension() == ".JPG" | iter->path().extension() == ".png" | iter->path().extension() == ".PNG" | iter->path().extension() == ".BMP" | iter->path().extension() == ".bmp")
		{
			string str = iter->path().string();
			System::String^ path = gcnew System::String(iter->path().string().c_str()); 
			cout << iter->path().string().c_str() << endl;
			backgroundWorker->ReportProgress(1, path);  //reporting progress
		}

		if (backgroundWorker->CancellationPending) //if it was cancelled
		{
			e->Cancel = true;
			break;
		}
	}
}



System::Void OpenCV_JP::frmPreprocessing::backgroundWorker_ProgressChanged(System::Object ^ sender, System::ComponentModel::ProgressChangedEventArgs ^ e)
{
		System::String^ path = e->UserState->ToString();
		string str_path;
		this->extent->MarshalString(path, str_path);

		Mat src = imread(str_path, CV_LOAD_IMAGE_COLOR);
		//Khởi tạo object preprocess
		cv::cvtColor(src, src, COLOR_BGR2GRAY);
		Mat dst = src.clone();
		this->preprocess = new Preprocess(src, dst);

		//1 - Median check
		if (cbMedian->Checked) {
			//int kernelMedian = trbMedian->Value * 2 + 1;
			//Processing
			this->preprocess->adaptiveMedian();
		}
		//2 - Laplacian check
		if (cbLaplacian->Checked) {
			this->preprocess->setSrc(this->preprocess->getDist());
			int kernelLaplacian = trbLaplacian->Value * 2 + 1;
			//Processing
			this->preprocess->laplacian(kernelLaplacian);
		}
		//3 - Thresholding check
		if (cbThresholding->Checked) {
			this->preprocess->setSrc(this->preprocess->getDist());
			int thresholding_val = trbThresholding->Value;

			if (cbLaplacian->Checked) {
				//Processing
			//	this->preprocess->threshold(thresholding_val, 255, THRESH_BINARY_INV);
			}
			else {
				//Processing
			//	this->preprocess->threshold(thresholding_val, 255, THRESH_BINARY);
			}
		}
		//3.1 - Adaptive Thresholding check
		if (cbAdaptiveThresholding->Checked) {
		/*	this->preprocess->setSrc(this->preprocess->getDist());
			this->preprocess->adaptive(false, false, 39, 2);

			this->preprocess->setSrc(this->preprocess->getDist());
			int kernelMedian = trbMedian->Value * 2 + 1;*/
			//Processing
			//this->preprocess->medianBlur(kernelMedian);
		}
		//4 - Opening check
		if (cbOpening->Checked) {
			//this->preprocess->adaptiveMedian();
			this->preprocess->setSrc(this->preprocess->getDist());
			int kernelOpening = trbOpening->Value;
			//Processing
			this->preprocess->Morphology_Operations(MORPH_OPEN, MORPH_RECT, kernelOpening);
		}

		//saving
		vector<string> arrPath = this->extent->split(str_path, '\\');
		this->extent->MarshalString(lbOutput->Text, str_path);
		std::string savePath = str_path + "\\" + arrPath.back();
		imwrite(savePath, this->preprocess->getDist());
		//end saving

}

System::Void OpenCV_JP::frmPreprocessing::backgroundWorker_RunWorkerCompleted(System::Object ^ sender, System::ComponentModel::RunWorkerCompletedEventArgs ^ e)
{
	if (e->Cancelled)    //Messages for the events
	{
		lbInform->Text = "You have cancelled background worker!!!";
	}
	else
	{
		lbInform->Text = "Work completed!!";
	}
	btnStart->Enabled = true;
	btnCancel->Enabled = false;
}

System::Void OpenCV_JP::frmPreprocessing::cbAdaptiveThresholding_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	cbThresholding->Checked = !cbAdaptiveThresholding->Checked;
}

System::Void OpenCV_JP::frmPreprocessing::cbThresholding_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	cbAdaptiveThresholding->Checked = !cbThresholding->Checked;
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

