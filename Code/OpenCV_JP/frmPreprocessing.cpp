#include "frmPreprocessing.h"

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
			backgroundWorker->ReportProgress(1, path);  //reporting progress
		}

		if (backgroundWorker->CancellationPending) //if it was cancelled
		{
			e->Cancel = true;
			break;
		}
	}//for iter
}

System::Void OpenCV_JP::frmPreprocessing::backgroundWorker_ProgressChanged(System::Object ^ sender, System::ComponentModel::ProgressChangedEventArgs ^ e)
{
		System::String^ path = e->UserState->ToString();
		string str_path;
		this->extent->MarshalString(path, str_path);
		Mat src = imread(str_path, CV_LOAD_IMAGE_GRAYSCALE);

		//Resize
		cv::Size size = src.size();
		if (MAX_WIDTH < size.width)
			cv::resize(src, src, cv::Size(MAX_WIDTH, MAX_WIDTH * size.height / size.width), 0, 0);

		//Initing object preprocess
		Mat dst = src.clone();
		this->preprocess = new Preprocess(src, dst);
		cout << str_path << " is processing..." << endl;
		//1 - Median check
		if (cbbSaltPepperFilter->Text == "Median") {
			int kernelMedian = trbMedian->Value * 2 + 1;
			//Processing
			this->preprocess->medianBlur(kernelMedian);
		}
		//1.1 - adaptive Median check
		if (cbbSaltPepperFilter->Text == "Adaptive median") {
			//Processing
			this->preprocess->adaptiveMedian();
		}
		//3 - Thresholding check
		if (cbbConvert2Bin->Text == "Otsu thresholding") {

			this->preprocess->setSrc(this->preprocess->getDist());
			this->preprocess->gaussianBlur(3);
			this->preprocess->setSrc(this->preprocess->getDist());
			this->preprocess->threshold();
		}
		//3.1 - Adaptive Thresholding check
		if (cbbConvert2Bin->Text == "Adaptive thresholding") {
			this->preprocess->setSrc(this->preprocess->getDist());
			this->preprocess->adaptive(false, false, 99, 0);
		}
		//4 - Opening check
		if (cbbMorphologyTransformations->Text != "- Nothing -") {
			//this->preprocess->adaptiveMedian();
			this->preprocess->setSrc(this->preprocess->getDist());
			int kernel = trbOpening->Value;
			int type = MORPH_OPEN;

			if (cbbMorphologyTransformations->Text == "Opening") {
				type = MORPH_OPEN;
			}
			else if (cbbMorphologyTransformations->Text == "Closing") {
				type = MORPH_CLOSE;
			}
			else if (cbbMorphologyTransformations->Text == "Gradient") {
				type = MORPH_GRADIENT;
			}
			else if (cbbMorphologyTransformations->Text == "Top Hat") {
				type = MORPH_TOPHAT;
			}
			else if (cbbMorphologyTransformations->Text == "Black Hat") {
				type = MORPH_BLACKHAT;
			}
			//Processing
		
			this->preprocess->Morphology_Operations(type, MORPH_RECT, kernel);
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

System::Void OpenCV_JP::frmPreprocessing::btnAddNoise_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	string path_image;
	this->extent->MarshalString(lbInput->Text, path_image);
	fs::path directory(path_image);
	fs::directory_iterator iter(directory), end;
	int val = trbNumNoise->Value;

	for (; iter != end; ++iter)
	{
		if (iter->path().extension() == ".jpg" | iter->path().extension() == ".JPG" | iter->path().extension() == ".png" | iter->path().extension() == ".PNG" | iter->path().extension() == ".BMP" | iter->path().extension() == ".bmp")
		{
			string str = iter->path().string();
			Noise addNoise(imread(str, CV_LOAD_IMAGE_GRAYSCALE));
			addNoise.Salt(val);
			addNoise.Pepper(val);

			//saving
			vector<string> arrPath = this->extent->split(str, '\\');
		//	this->extent->MarshalString(lbOutput->Text, str);
			std::string savePath = "D:\\Noise\\" + arrPath.back();
			imwrite(savePath, addNoise.getImage());
			//end saving
		}
	}//for iter
}

System::Void OpenCV_JP::frmPreprocessing::trbOpening_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	string model(to_string(trbOpening->Value * 2 + 1));
	System::String^ val = gcnew System::String(model.c_str());
	lbKernelOpening->Text = val;
}

System::Void OpenCV_JP::frmPreprocessing::trbNumNoise_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	string model(to_string(trbNumNoise->Value));
	System::String^ val = gcnew System::String(model.c_str());
	lbNumberNoise->Text = val+"%";
}

