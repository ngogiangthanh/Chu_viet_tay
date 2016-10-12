#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "Projection.h"
#include "Word_Up.h"
#include "Word_lp.h"
#include "nbit.h"
#include "DTW.h"

using namespace cv;
using namespace std;

void readme();

/** @function main */
int main(int argc, char** argv)
{
	Mat img_org = imread("D:\\Thesis\\Chu_viet_tay\\SIFT\\alexandria.PNG", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img_org1 = imread("D:\\Thesis\\Chu_viet_tay\\SIFT\\alexandria1.PNG", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img_org2 = imread("D:\\Thesis\\Chu_viet_tay\\SIFT\\nui.PNG", CV_LOAD_IMAGE_GRAYSCALE);

	//if (!img_org.data)
	//{
	//	cout << " --(!) Error reading images " << endl;
	//	return -1;
	//}

	////-- Step 1: Detect the keypoints using SURF Detector
	//Ptr<xfeatures2d::SIFT> sift = xfeatures2d::SIFT::create();
	//vector<KeyPoint> sift_keypoint;
	//sift->detect(img_org, sift_keypoint);
	//int size_of_points = sift_keypoint.size();

	////-- Draw keypoints
	//Mat img_sift;
	//cv::Size size = img_org.size();
	//Mat img_white = Mat(size.height, size.width, CV_8UC3, Scalar(255, 255, 255));
	//drawKeypoints(img_white, sift_keypoint, img_sift, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	////-- Show detected (drawn) keypoints
	//imshow("Ảnh gốc", img_org);
	//imshow("SIFT", img_sift);
	//-----------------------
	/*Projection projection_profile(img_org);
	projection_profile.cal_pp();
	projection_profile.draw_pp();
	float *pp = 0;
	int size_pp = projection_profile.get_pp(pp);

	Projection projection_profile1(img_org1);
	projection_profile1.cal_pp();
	projection_profile1.draw_pp();
	float *pp1 = 0;
	int size_pp1 = projection_profile1.get_pp(pp1);

	Projection projection_profile2(img_org2);
	projection_profile2.cal_pp();
	projection_profile2.draw_pp();
	float *pp2 = 0;
	int size_pp2 = projection_profile2.get_pp(pp2);

	Word_Up word_up(img_org);
	word_up.cal_up();
	word_up.interpolated_value();
	word_up.draw_up();
	float* wup = 0;
	int size_wup = word_up.get_up(wup);

	Word_Up word_up1(img_org1);
	word_up1.cal_up();
	word_up1.interpolated_value();
	word_up1.draw_up();
	float* wup1 = 0;
	int size_wup1 = word_up1.get_up(wup1);


	Word_Up word_up2(img_org2);
	word_up2.cal_up();
	word_up2.interpolated_value();
	word_up2.draw_up();
	float* wup2 = 0;
	int size_wup2 = word_up2.get_up(wup2);

	Word_lp word_lp(img_org);
	word_lp.cal_lp();
	word_lp.interpolated_value();
	word_lp.draw_lp();
	float* wlp = 0;
	word_lp.get_lp(wlp);*/

	//nbit nbit_p(img_org);
	//nbit_p.cal_nbit();
	//nbit_p.interpolated_value();
	//nbit_p.draw_nbit();
	////nbit_p.get_nbit();

	//------------DTW---------
	//Dynamic_Time_Warping DTW(pp, pp1, size_pp, size_pp1);
	//cout << "Projection profile - matching cost [dap-dap1] = " << DTW.DTWDistance() << endl;
	//Dynamic_Time_Warping DTW1(pp, pp2, size_pp, size_pp2);
	//cout << "Projection profile - matching cost [dap-nui] = " << DTW1.DTWDistance() << endl;
	//Dynamic_Time_Warping DTW2(pp2, pp1, size_pp2, size_pp1);
	//cout << "Projection profile - matching cost [nui-dap1] = " << DTW2.DTWDistance() << endl;
	////
	//Dynamic_Time_Warping DTW3(wup, wup1, size_wup, size_wup1);
	//cout << "Upper Upper profile - matching cost [dap-dap1] = " << DTW3.DTWDistance() << endl;
	//Dynamic_Time_Warping DTW4(wup, wup2, size_wup, size_wup2);
	//cout << "Upper Upper profile - matching cost [dap-nui] = " << DTW4.DTWDistance() << endl;
	//Dynamic_Time_Warping DTW5(wup2, wup1, size_wup2, size_wup1);
	//cout << "Upper Upper profile - matching cost [nui-dap1] = " << DTW5.DTWDistance() << endl;

	float a[] = { 1,1,1,1,1,1,1 };
	float b[] = { 1,1,1,1,1,1,1 };
	Dynamic_Time_Warping DTW(a, b, 7, 7);
	/*int a[] = { 2,3,4,5,7};
	int b[] = { 2,4,4,5,9};
	Dynamic_Time_Warping DTW(a, b, 5, 5);*/
	//int a[] = { 1,2,2};
	//int b[] = { 1,2,4,6 };
	//Dynamic_Time_Warping DTW(a, b, 3, 4);
	cout << "matching cost = " << DTW.DTWDistance_GPC(3) << endl;

	int r = 3;
	r = max(r, abs(5 - 7));
	for (int i = 0; i < 5; i++)
	{
		for (int j = max(1, i - r); j < min(7, i + r); j++) {
				cout << "[" <<i << "][" << j << "] -";
		}
		cout << endl;
	}
	system("pause");
	//waitKey(0);

	return 0;
}

/** @function readme */
void readme()
{
	std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl;
}