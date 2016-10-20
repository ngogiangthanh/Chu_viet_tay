#include "frmPreprocessing.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <algorithm>


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
		fs::path directory(path_image);
		fs::directory_iterator iter(directory), end;

		for (; iter != end; ++iter)
		{
			cout << "do work" << endl;
			if (iter->path().extension() == ".jpg" | iter->path().extension() == ".JPG")
			{

				Mat src = imread(iter->path().string(), CV_LOAD_IMAGE_COLOR);
				//Khởi tạo object preprocess
				cv::cvtColor(src, src, COLOR_BGR2GRAY);
				Mat dst = src.clone();
				this->preprocess = new Preprocess(src, dst);

				//1 - Median check
				if (cbMedian->Checked) {
					int kernelMedian = trbMedian->Value * 2 + 1;
					//Processing
					this->preprocess->medianBlur(kernelMedian);
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
						this->preprocess->threshold(thresholding_val, 255, THRESH_BINARY_INV);
					}
					else {
						//Processing
						this->preprocess->threshold(thresholding_val, 255, THRESH_BINARY);
					}
				}
				//4 - Opening check
				if (cbOpening->Checked) {
					this->preprocess->setSrc(this->preprocess->getDist());
					int kernelOpening = trbOpening->Value;
					//Processing
					this->preprocess->Morphology_Operations(MORPH_OPEN, MORPH_RECT, kernelOpening);
				}

				//saving
				this->extent->MarshalString(lbOutput->Text, path_image);
				vector<string> arrPath = this->extent->split(iter->path().filename().string(), '\\');
				std::string savePath = path_image + "\\" + arrPath.back();
				imwrite(savePath, this->preprocess->getDist());
				//end saving
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
	return System::Void();
}

System::Void OpenCV_JP::frmPreprocessing::backgroundWorker_RunWorkerCompleted(System::Object ^ sender, System::ComponentModel::RunWorkerCompletedEventArgs ^ e)
{
	if (e->Cancelled)    //Messages for the events
	{
		MessageBox::Show("You have cancelled background worker!!!");
	}
	else
	{
		MessageBox::Show("Work completed!!");
	}
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

