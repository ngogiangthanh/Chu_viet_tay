#include "MyForm.h"
#include "DTWSingle.h"
#include "A2DD.h"
#include <stdio.h>
#include <string> 
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Obstructing.h"

using namespace cv;
using namespace System;
using namespace System::Windows::Forms;

Mat src;

[STAThread]
int main(int argc, char** argv)
{
	//float a[] = { 1,2,2,4 };
	//float b[] = { 1,2,3 };
	//int height = (sizeof(a) / sizeof(*a));
	//int width = (sizeof(b) / sizeof(*b));
	//DTWDistance(a, b, height, width);

	src = imread("D:\\Thesis\\Chu_viet_tay\\Outputs\\pre_pfp_v3.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	if (!src.data)
	{
		std::cout << " --(!) Error reading images " << std::endl; return -1;
	}

	//int dilation_type;
	//if (dilation_elem == 0) { dilation_type = MORPH_RECT; }
	//else if (dilation_elem == 1) { dilation_type = MORPH_CROSS; }
	//else if (dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

	//Mat element = getStructuringElement(MORPH_RECT,cv::Size(3, 3),cv::Point(0, 1));
	/// Apply the dilation operation
	//dilate(src, dilation_dst, element);
	//imshow("Dilation Demo", dilation_dst);

	int x = 592;
	int y = 302;

	Obstructing* head = new Obstructing();
	head->setSrc(src);
	//head->setDist(src);
	//head->downSource(x, y, y);
	head->allSource(25, 72);
	//head->Dilation(180, 67, 180, 67);
	//head->Dilation(269, 74, 269, 74);
	//head->Dilation(305, 61, 305, 61);

	//Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));

	//imwrite("D:/dilation_org.jpg", head->getDist());
	//dilate(head->getSrc(), head->getDist(), element);

	imshow("Ảnh goc", head->getSrc());
	imshow("Anh dilation", head->getDist());
	imwrite("D:/dilation.jpg", head->getDist());

	////-- Step 1: Detect the keypoints using SURF Detector

	//Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create();
	//Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create();
	//std::vector<KeyPoint> surf_keypoint, sift_keypoint;

	//surf->detect(src, surf_keypoint);
	//sift->detect(src, sift_keypoint);

	////-- Draw keypoints
	//Mat img_surf, img_sift;

	//drawKeypoints(src, surf_keypoint, img_surf, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//drawKeypoints(src, sift_keypoint, img_sift, Scalar::all(-1), DrawMatchesFlags::DEFAULT);



	////-- Show detected (drawn) keypoints
	//imshow("Ảnh gốc", src);
	//imshow("SURF", img_surf);
	//imshow("SIFT", img_sift);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Thesis::MyForm form;
	Application::Run(%form);
	return 0;
}

System::Void Thesis::MyForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	A2DD* add = new A2DD(2, 3);
	std::string model(std::to_string(add->getSum()));
	System::String^ MyString = gcnew System::String(model.c_str());
	this->label1->Text = MyString;
	return System::Void();
}
