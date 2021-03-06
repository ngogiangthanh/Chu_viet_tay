#include "frmMain.h"
#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;
using namespace System;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Windows::Forms;


[STAThread]
int main(int argc, char** argv)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	OpenCV_Threshold::frmMain form;
	Application::Run(%form);

	return 0;
}

System::Void OpenCV_Threshold::frmMain::btnOpen_Click_1(System::Object ^ sender, System::EventArgs ^ e)
{
	openFileDialog1->InitialDirectory = "D:\\Thesis\\Chu_viet_tay";
	openFileDialog1->Filter = "PNG (*.png)|*.png|JPG (*.jpg)|*.jpg";
	openFileDialog1->FilterIndex = 2;
	openFileDialog1->RestoreDirectory = true;

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		this->lbPath->Text = openFileDialog1->FileName;
	}
}


System::Void OpenCV_Threshold::frmMain::trackBar1_Scroll_1(System::Object ^ sender, System::EventArgs ^ e)
{
	std::string model(std::to_string(trackBar1->Value));
	System::String^ val = gcnew System::String(model.c_str());
	lbThresholdVal->Text = val;
}

System::Void OpenCV_Threshold::frmMain::rbthreshold_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	this->cbAdaptiveMethod->Enabled = this->rbAdaptive->Checked;
	this->cbThresholdType->Enabled = this->rbAdaptive->Checked;
}

System::Void OpenCV_Threshold::frmMain::cbAdaptive_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	this->cbAdaptiveMethod->Text = this->cbAdaptiveMethod->Checked ? "Adaptive Method (ADAPTIVE_THRESH_GAUSSIAN_C selected)" : "Adaptive Method (ADAPTIVE_THRESH_MEAN_C selected)";
	this->cbThresholdType->Text = this->cbThresholdType->Checked ? "Threshold Type (THRESH_BINARY_INV selected)" : "Threshold Type (THRESH_BINARY selected)";
}

System::Void OpenCV_Threshold::frmMain::btnThreshold_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	system("cls");

	//Lấy thông tin ảnh
	string path_image;
	this->extent->MarshalString(openFileDialog1->FileName, path_image);
	Mat anh_goc_mat = imread(path_image, CV_LOAD_IMAGE_COLOR);
	cout << "Path of image: " << path_image << ";" << endl;

	//Lấy tất cả thông tin trong cbb order trước
	int cbbThres = Int32::Parse(this->cbbOrderThreshold->Text);
	int cbbGauss = Int32::Parse(this->cbbOrderGauss->Text);
	int cbbAverage = Int32::Parse(this->cbbOrderAveraging->Text);
	int cbbMedian = Int32::Parse(this->cbbOrderMedian->Text);
	int cbbLaplacian = Int32::Parse(this->cbbOrderLaplacian->Text);

	//Khởi tạo object preprocess
	Mat anh_kq = anh_goc_mat.clone();
	cv::cvtColor(anh_kq, anh_kq, COLOR_BGR2GRAY);
	this->preprocess = new Preprocess(anh_goc_mat, anh_kq);

	//Gọi phương thức chuyển đổi tương ứng
	while (cbbThres != 0 || cbbGauss != 0 || cbbAverage != 0 || cbbMedian != 0 || cbbLaplacian != 0) {
		{
			this->preprocess->setSrc(preprocess->getDist());
			//
			int min_val = min(min(min(min(cbbThres, cbbGauss), cbbAverage), cbbMedian), cbbLaplacian);
			if (cbbThres == min_val)
				cbbThres = 1;
			if (cbbGauss == min_val)
				cbbGauss = 1;
			if (cbbAverage == min_val)
				cbbAverage = 1;
			if (cbbMedian == min_val)
				cbbMedian = 1;
			if (cbbLaplacian == min_val)
				cbbLaplacian = 1;

			if (cbbThres == 1) {
				int threshold_type = rbBin->Checked ? 0 : (rbBinaryInvert->Checked ? 1 : (rbTruncate->Checked ? 2 : (rbZero->Checked ? 3 : (rbZero->Checked ? 4 : (rbAdaptive->Checked ? 5 : 0)))));
				if (threshold_type != 5)
					this->preprocess->threshold(trackBar1->Value, 255, threshold_type);
				else
					this->preprocess->adaptive(this->cbAdaptiveMethod->Checked, this->cbThresholdType->Checked, Int32::Parse(this->cbbKernelAdaptiveThreshold->Text), 0);
				cbbThres = 0;
			}
			if (cbbGauss == 1) {
				int kernel_size = Int32::Parse(this->cbbKernelGauss->Text);
				this->preprocess->gaussianBlur(kernel_size);
				cbbGauss = 0;
			}
			if (cbbAverage == 1) {
				int kernel_size = Int32::Parse(this->cbbAveraging->Text);
				this->preprocess->averageBlur(kernel_size);
				cbbAverage = 0;
			}
			if (cbbMedian == 1) {
				int kernel_size = Int32::Parse(this->cbbMedian->Text);
				this->preprocess->medianBlur(kernel_size);
				cbbMedian = 0;
			}
			if (cbbLaplacian == 1) {
				int kernel_size = Int32::Parse(this->cbbLaplacian->Text);
				this->preprocess->laplacian(kernel_size);
				cbbLaplacian = 0;
			}
		}
	}

	//Hiện kết quả
	//Ảnh gốc
	namedWindow("Anh goc", CV_WINDOW_NORMAL);
	resizeWindow("Anh goc", 720, 480);
	imshow("Anh goc", anh_goc_mat);
	//Ảnh kết quả
	namedWindow("Anh ket qua", CV_WINDOW_NORMAL);
	resizeWindow("Anh ket qua", 720, 480);
	imshow("Anh ket qua", this->preprocess->getDist());
}

System::Void OpenCV_Threshold::frmMain::btnClearAll_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->rbBin->Checked = true;
	this->trackBar1->Value = 200;
	this->lbThresholdVal->Text = "200";
	this->cbbOrderThreshold->SelectedIndex = 0;
	this->cbbKernelAdaptiveThreshold->SelectedIndex = 0;
	//
	this->cbbKernelGauss->SelectedIndex = 0;
	this->cbbOrderGauss->SelectedIndex = 0;
	//
	this->cbbAveraging->SelectedIndex = 0;
	this->cbbOrderAveraging->SelectedIndex = 0;
	//
	this->cbbMedian->SelectedIndex = 0;
	this->cbbOrderMedian->SelectedIndex = 0;
	//
	this->cbbLaplacian->SelectedIndex = 0;
	this->cbbOrderLaplacian->SelectedIndex = 0;
}

System::Void OpenCV_Threshold::frmMain::btnSavePre_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	string path_image;
	this->extent->MarshalString(openFileDialog1->FileName, path_image);
	vector<string> arrPath = this->extent->split(path_image,'\\');
	std::string savePath = "D:/Thesis/Chu_viet_tay/Outputs/pre_" + arrPath.back();
	//Luu vao o cung
	imwrite(savePath, this->preprocess->getDist());
	MessageBox::Show(L"Lưu kết quả tiền xử lý thành công!!!");
	//Mo file hinh bang chuong trinh mac dinh cua windows
	savePath = "start " + savePath;
	const char * executeStr = savePath.c_str();
	system(executeStr);
}

System::Void OpenCV_Threshold::frmMain::btnThresholdCls_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->rbBin->Checked = true;
	this->trackBar1->Value = 200;
	this->lbThresholdVal->Text = "200";
	this->cbbOrderThreshold->SelectedIndex = 0;
	this->cbbKernelAdaptiveThreshold->SelectedIndex = 0;
}

System::Void OpenCV_Threshold::frmMain::btnGaussCls_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->cbbKernelGauss->SelectedIndex = 0;
	this->cbbOrderGauss->SelectedIndex = 0;
}

System::Void OpenCV_Threshold::frmMain::btnAverageCls_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->cbbAveraging->SelectedIndex = 0;
	this->cbbOrderAveraging->SelectedIndex = 0;
}

System::Void OpenCV_Threshold::frmMain::btnMedianCls_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->cbbMedian->SelectedIndex = 0;
	this->cbbOrderMedian->SelectedIndex = 0;
}

System::Void OpenCV_Threshold::frmMain::btnLaplacianCls_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->cbbLaplacian->SelectedIndex = 0;
	this->cbbOrderLaplacian->SelectedIndex = 0;
}

System::Void OpenCV_Threshold::frmMain::btnSegOpenFile_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	openFileDialog1->InitialDirectory = "D:\\Dataset\\1-Segementation";
	openFileDialog1->Filter = "PNG (*.png)|*.png|JPG (*.jpg)|*.jpg";
	openFileDialog1->FilterIndex = 2;
	openFileDialog1->RestoreDirectory = true;

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		this->lbSegPathImg->Text = openFileDialog1->FileName;
	}
}

System::Void OpenCV_Threshold::frmMain::btnKhoiTao_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	try{
		system("cls");

		//Lấy thông tin ảnh cho Tab phân đoạn
		string path_image;
		this->extent->MarshalString(openFileDialog1->FileName, path_image);
		Mat anh_goc_mat = imread(path_image, CV_LOAD_IMAGE_COLOR);
		cv::cvtColor(anh_goc_mat, anh_goc_mat, COLOR_BGR2GRAY);
		cout << "Path of image: " << path_image << ";" << endl;

		vector<string> arrPath = this->extent->split(path_image, '\\');
		this->elapsed_secs = 0;
		clock_t begin = clock();

		this->segment = new Segmentation(anh_goc_mat);
		this->segment->setName(arrPath.back());
		this->segment->setHeighOfLine(trbSegHeighOfLine->Value);
		this->segment->normalized();
		this->segment->init();

		clock_t end = clock();
		this->elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
	}
	catch (...) {
		Console::WriteLine("An error occurred in init. Please try again...");
	}
}

System::Void OpenCV_Threshold::frmMain::btnFindValley_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	try{
		clock_t begin = clock();
		this->segment->findValley();

		clock_t end = clock();
		this->elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
	}
	catch (...) {
		Console::WriteLine("An error occurred in Find valleys. Please try again...");
	}
}

System::Void OpenCV_Threshold::frmMain::btnSegSave_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	string path_image;
	this->extent->MarshalString(openFileDialog1->FileName, path_image);
	vector<string> arrPath = this->extent->split(path_image, '\\');
	string saveValleyPath = "D:/Dataset/1-Segementation/results/seg_valley_" + arrPath.back();
	string savePagePath = "D:/Dataset/1-Segementation/results/seg_page_org_" + arrPath.back();
	string saveLinePath = "D:/Dataset/1-Segementation/results/seg_page_line_" + arrPath.back();
	string saveWordPath = "D:/Dataset/1-Segementation/results/seg_page_word_" + arrPath.back();
	//Luu vao o cung
	imwrite(saveValleyPath, this->segment->getDist());
	imwrite(savePagePath, this->segment->getSrc());
	imwrite(saveLinePath, this->segment->getLineResult());
	imwrite(saveWordPath, this->segment->getWordResult());
	MessageBox::Show(L"Lưu kết quả phân đoạn thành công!!! [" + this->elapsed_secs + " giây]");

	//Mo file hinh bang chuong trinh mac dinh cua windows
	saveValleyPath = "start " + saveValleyPath;
	savePagePath = "start " + savePagePath;
	saveLinePath = "start " + saveLinePath;
	saveWordPath = "start " + saveWordPath;
	const char * executeStr = saveValleyPath.c_str();
	system(executeStr);
	executeStr = savePagePath.c_str();
	system(executeStr);
	executeStr = saveLinePath.c_str();
	system(executeStr);
	executeStr = saveWordPath.c_str();
	system(executeStr);
}

System::Void OpenCV_Threshold::frmMain::btnMAFSeg_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	try {
	clock_t begin = clock();
	this->segment->setKernelMAF(Int32::Parse(this->cbbSegMAF->Text));
	this->segment->movingAverageFilter();

	clock_t end = clock();
	this->elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
	}
	catch (...) {
		Console::WriteLine("An error occurred in MAF. Please try again...");
	}
}

System::Void OpenCV_Threshold::frmMain::btnSegConnectValley_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	try {
		clock_t begin = clock();
		this->segment->connectValley();

		clock_t end = clock();
		this->elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
	}
	catch (...) {
		Console::WriteLine("An error occurred in segementation connecting. Please try again...");
	}
}

System::Void OpenCV_Threshold::frmMain::trbSegHeighOfLine_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	std::string model(std::to_string(trbSegHeighOfLine->Value));
	System::String^ val = gcnew System::String(model.c_str());
	lbSegValHeigh->Text = val;
}

System::Void OpenCV_Threshold::frmMain::btnSegSetMAF_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->segment->setKernelMAF(Int32::Parse(this->cbbSegMAF->Text));
}

System::Void OpenCV_Threshold::frmMain::btnSegResetMAF_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->cbbSegMAF->SelectedIndex = 2;
}

System::Void OpenCV_Threshold::frmMain::btnSegSetHeighOfLine_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->segment->setHeighOfLine(trbSegHeighOfLine->Value);
}

System::Void OpenCV_Threshold::frmMain::btnSegResetHeighOfLine_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->trbSegHeighOfLine->Value = 40;
	this->lbSegValHeigh->Text = "40";
}

int OpenCV_Threshold::frmMain::min(int a, int b)
{
	return a == 0 ? b : (b == 0 ? a : (a > b ? b : a));
}