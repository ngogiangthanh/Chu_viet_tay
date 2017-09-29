#include "frmMain.h"
#include "ocr.hpp"
#define MAX_WIDTH 1380

using namespace System;
using namespace std;
using namespace System::Windows::Forms;

[STAThread]
int main(int argc, char** argv)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Thesis::frmMain form;
	Application::Run(%form);
	return 0;
}

System::Void Thesis::frmMain::btnSearch_Click(System::Object ^ sender, System::EventArgs ^ e)
{

	Ptr<cv::text::OCRTesseract> tess = cv::text::OCRTesseract::create(NULL, NULL, NULL, 3, 3);
	if (this->tbKeywords->Text != "") {
		string str;
		this->extent->MarshalString(this->tbKeywords->Text, str);
		vector<string> terms = this->extent->split(str, ' ');
		if (this->lbPathImage->Text == "FakePath\\") {
			MessageBox::Show(L"Vui lòng chọn lại ảnh");
			this->ActiveControl = this->btnChooseImage;
		}
		else {
			string path_image;
			this->extent->MarshalString(this->lbPathImage->Text, path_image);
			Mat anhGoc = imread(path_image, CV_LOAD_IMAGE_GRAYSCALE);
			Mat success_icon = imread("D:\\Thesis\\Data\\icons\\yes.png", CV_LOAD_IMAGE_COLOR);
			//--tiền xử lý --

			Mat anhGocResize;
			Mat anhTienXuLy = this->khuNhieu(anhGoc, anhGocResize);
			this->extent->LoadImage(this->pbPreProcess, success_icon);
			//--kết thúc tiền xử lý --

			//--tách dòng và tách từ
			vector<string> arrPath = this->extent->split(path_image, '\\');
			string duongDanDsTu = this->tachDongTachTu(anhTienXuLy, anhGocResize, arrPath.back());
			string path = duongDanDsTu + "\\ket_qua_phan_doan.jpg";
			imwrite(path, anhGocResize);
			this->extent->LoadImage(this->pbSegmentation, success_icon);
			//this->extent->showImage(path);
			//-- kết thúc tách dòng và tách từ

			//--so khớp
			Mat anhKetQua = this->soKhop(terms, duongDanDsTu, anhGocResize);
			this->extent->LoadImage(this->pbFeatures, success_icon);
			this->extent->LoadImage(this->pbDTW, success_icon);
			//--kết thúc so khớp
		}
	}
	else {
		MessageBox::Show(L"Vui lòng nhập từ khóa");
		this->ActiveControl = this->tbKeywords;
	}
}

Mat Thesis::frmMain::khuNhieu(Mat anhGoc, Mat &anhGocResize)
{
	bool isLocNhieu = this->cbMedianFilter->Checked;
	bool isPhanNguong = this->cbThresholding->Checked;
	bool isMorphGradient = this->cbMorphGradient->Checked;
	if (MAX_WIDTH < anhGoc.cols)
		cv::resize(anhGoc, anhGocResize, cv::Size(MAX_WIDTH, MAX_WIDTH * anhGoc.rows / anhGoc.cols), 0, 0);
	else
		anhGocResize = anhGoc.clone();
	Mat anhTienXuLy = anhGocResize.clone();
	PreProcess preprocessing;
	//lọc nhiễu
	if (isLocNhieu) {
		int kernelMedian = 3;
		preprocessing.medianBlur(anhGocResize, anhTienXuLy, kernelMedian);
		preprocessing.medianBlur(anhGocResize, anhGocResize, kernelMedian);
	}
	//kết thúc lọc nhiễu
	//phân ngưỡng
	if (isPhanNguong) {
		preprocessing.gaussianBlur(anhTienXuLy, anhTienXuLy, 3);
		preprocessing.threshold(anhTienXuLy, anhTienXuLy);
	}
	//kết thúc phân ngưỡng
	//biến đổi hình thái gradient
	if (isMorphGradient) {
		int kernel = 3;
		int type = MORPH_GRADIENT;
		preprocessing.Morphology_Operations(anhTienXuLy, anhTienXuLy, type, MORPH_RECT, kernel);
	}
	//kết thúc biến đổi hình thái gradient
	imwrite("D:\\phan_nguong.jpg", anhTienXuLy);
	return anhTienXuLy;
}

string Thesis::frmMain::tachDongTachTu(Mat anhTienXuLy, Mat& anhGocResize, string tenAnh)
{
	string duongDanDsTu;
	double elapsed_secs = 0;
	system("cls");

	elapsed_secs = 0;
	clock_t begin = clock();

	Segmentation* segment = new Segmentation(anhTienXuLy);
	segment->setName(tenAnh);
	segment->setHeighOfLine(this->trbSegHeighOfLine->Value);
	segment->normalized(anhGocResize);
	segment->init();
	segment->setKernelMAF(Int32::Parse(this->cbbMAFLength->Text));
	segment->movingAverageFilter();
	segment->findValley();
	segment->connectValley();
	segment->setWordResult(anhGocResize);
	segment->drawConnects();
	anhGocResize = segment->getWordResult().clone();
	string pathThungLung = "D:\\ket_qua_thung_lung.jpg";
	imwrite(pathThungLung, segment->getDist());
	string pathDong = PATH + tenAnh + "\\ket_qua_tach_dong.jpg";
	imwrite(pathDong, segment->getLineResult());

	clock_t end = clock();
	elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
	cout << "Thoi gian phan tich " << elapsed_secs << endl;
	//
	bool isChuanHoa = this->cbSkewDetect->Checked;
	if (isChuanHoa) {
		this->chuanHoa(PATH + tenAnh+"/words/");
	}
	return PATH + tenAnh;
}

void Thesis::frmMain::chuanHoa(string duongDan)
{
	fs::path directory(duongDan);
	fs::directory_iterator iter(directory), end;
	Extent* extent = new Extent();

	mkdir((duongDan + "/normalization/").c_str());

	for (; iter != end; ++iter)
	{
		if (iter->path().extension() == ".jpg" | iter->path().extension() == ".JPG" | iter->path().extension() == ".png" | iter->path().extension() == ".PNG" | iter->path().extension() == ".BMP" | iter->path().extension() == ".bmp")
		{
			string str = iter->path().string();
			cout << "str " << str << endl;
			Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);

			Normalization normalized(img_org);

			Mat temp = img_org.clone();
			Mat element = getStructuringElement(MORPH_RECT, cv::Size(3, 3));
			erode(img_org, img_org, element);
			Mat preprocessed = normalized.preprocess2(img_org);

			double skew;
			normalized.hough_transform(preprocessed, img_org, &skew);
			Mat rotated = normalized.rot(temp, skew* CV_PI / 180);

			vector<string> arrPath = extent->split(str, '\\');
			std::string savePath = duongDan + "//normalization//"+ arrPath.back();
			imwrite(savePath, rotated);
		}
	}
}

Mat Thesis::frmMain::soKhop(vector<string> dsTuKhoa, string duongDanDsTu, Mat anhGocResize)
{
	
	return Mat();
}
