#include "frmMain.h"
#include "frmPreprocessing.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace cv;
using namespace std;


[STAThread]
int main(int argc, char** argv){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	OpenCV_JP::frmPreprocessing preprocessing;
	Application::Run(%preprocessing);
}

System::Void OpenCV_JP::frmMain::tbOperator_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	string model(to_string(tbOperator->Value));
	System::String^ val = gcnew System::String(model.c_str());
	lbOperatorCurr->Text = val;
}

System::Void OpenCV_JP::frmMain::tbElement_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	string model(to_string(tbElement->Value));
	System::String^ val = gcnew System::String(model.c_str());
	lbElementCurr->Text = val;
}

System::Void OpenCV_JP::frmMain::tbKernel_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	string model(to_string(tbKernel->Value));
	System::String^ val = gcnew System::String(model.c_str());
	lbKernelCurr->Text = val;
}

System::Void OpenCV_JP::frmMain::btnProcess_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int morph_operator = tbOperator->Value;
	int morph_elem = tbElement->Value;
	int morph_size = tbKernel->Value;
	Mat img_org = imread("D:\\Thesis\\Chu_viet_tay\\SIFT\\pre_sf_hp_v2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	
	Morphology_Operations(img_org, morph_operator, morph_elem, morph_size);
}

/**
* @function Morphology_Operations
*/
void OpenCV_JP::frmMain::Morphology_Operations(Mat src, int morph_operator, int morph_elem, int morph_size)
{

	// Since MORPH_X : 2,3,4,5 and 6
	int operation = morph_operator + 2;

	Mat element = getStructuringElement(morph_elem, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));

	/// Apply the specified morphology operation
	Mat dst;
	morphologyEx(src, dst, operation, element);
	imshow("src", src);
	imshow("destination", dst);
}
