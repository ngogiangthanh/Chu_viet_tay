#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "Projection.h"
#include "Word_Up.h"
#include "Word_lp.h"
#include "DTW.h"
#include "Equations.h"
#include <time.h>
#include "SIFT.h"
#include "Normalized.h"

using namespace cv;
using namespace std;

void readme();

/** @function main */
int main(int argc, char** argv)
{
	Mat img_org = imread("D:\\Thesis\\Chu_viet_tay\\SIFT\\pre_alexandria_UN.PNG", CV_LOAD_IMAGE_GRAYSCALE);
	//Mat img_org1 = imread("D:\\Thesis\\Chu_viet_tay\\SIFT\\alexandria.PNG", CV_LOAD_IMAGE_GRAYSCALE);
	//Mat img_org2 = imread("D:\\Thesis\\Chu_viet_tay\\SIFT\\nui.PNG", CV_LOAD_IMAGE_GRAYSCALE);
	
	Normalized normalized(img_org);
	normalized.MeasurementOfAverageStrokeThickness();
	normalized.StraightLineRemoval();

	/*
	if (!img_org.data)
	{
		cout << " --(!) Error reading images " << endl;
		return -1;
	}

	//-- Step 1: Detect the keypoints using SURF Detector
	Ptr<xfeatures2d::SIFT> sift = xfeatures2d::SIFT::create();
	vector<KeyPoint> sift_keypoint;
	sift->detect(img_org, sift_keypoint);
	int size_of_points = sift_keypoint.size();

	//-- Draw keypoints
	Mat img_sift;
	cv::Size size = img_org.size();
	Mat img_white = Mat(size.height, size.width, CV_8UC3, Scalar(255, 255, 255));
	drawKeypoints(img_white, sift_keypoint, img_sift, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	//-- Show detected (drawn) keypoints
	imshow("Ảnh gốc", img_org);
	imshow("SIFT", img_sift);
	*/
	
	//-----------------------
	/*
	Projection projection_profile(img_org);
	projection_profile.cal_pp();
	projection_profile.draw_pp();
	//float *pp = 0;
	//int size_pp = projection_profile.get_pp(pp);
	
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
	//float* wup = 0;
	//int size_wup = word_up.get_up(wup);*/
	/*
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
	*/
	
	Word_lp word_lp(img_org);
	word_lp.cal_lp();
	word_lp.interpolated_value();
	word_lp.draw_lp();
	/*
	//float* wlp = 0;
	//word_lp.get_lp(wlp);
	
	------------DTW---------

	clock_t tStart = clock();
	Dynamic_Time_Warping DTW(pp2, pp1, size_pp2, size_pp1);
	cout << "Projection profile - matching cost [nui-dap1] = " << DTW.DTWDistance() << endl;
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	tStart = clock();
	Dynamic_Time_Warping DTW1(pp2, pp1, size_pp2, size_pp1);
	cout << "Projection profile - matching cost [nui-dap1] = " << DTW.DTWDistance_GPC(100) << endl;
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	//cout << "Projection profile - matching cost [dap-nui] = " << DTW1.DTWDistance() << endl;
	Dynamic_Time_Warping DTW2(pp2, pp1, size_pp2, size_pp1);
	cout << "Projection profile - matching cost [nui-dap1] = " << DTW2.DTWDistance() << endl;
	////
	Dynamic_Time_Warping DTW3(wup, wup1, size_wup, size_wup1);
	cout << "Upper Upper profile - matching cost [dap-dap1] = " << DTW3.DTWDistance() << endl;
	Dynamic_Time_Warping DTW4(wup, wup2, size_wup, size_wup2);
	cout << "Upper Upper profile - matching cost [dap-nui] = " << DTW4.DTWDistance() << endl;
	Dynamic_Time_Warping DTW5(wup2, wup1, size_wup2, size_wup1);
	cout << "Upper Upper profile - matching cost [nui-dap1] = " << DTW5.DTWDistance() << endl;
	*/
	
	/*
	float  a[] = { 2,3,4,5,7,1,2,3,4,5 };
	float b[] = { 2,4,4,5,9,4,5,6,3 };
	Dynamic_Time_Warping DTW(a, b, 10, 9);
	cout << "matching cost = " << DTW.DTWDistance() << endl;
	//cout << "matching cost gpc = " << DTW.DTWDistance_GPC(121) << endl;
	*/
	
	/*
	//Try using matching in opencv
	SIFT sift;
	sift.FeatureMatching(img_org, img_org1, false);
	*/

	//Try using morphological
	/*
	src : Source (input) image
	dst: Output image
	operation: The kind of morphology transformation to be performed. Note that we have 5 alternatives:

	Opening: MORPH_OPEN : 2
	Closing: MORPH_CLOSE: 3
	Gradient: MORPH_GRADIENT: 4
	Top Hat: MORPH_TOPHAT: 5
	Black Hat: MORPH_BLACKHAT: 6

	*/
	/*Mat dilation_dst, erode_dst, open_dst, open_dst_fn; 
	int erosion_size = 1;
	Mat element = getStructuringElement(cv::MORPH_CROSS,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));
	erode(img_org, erode_dst, element);
	dilate(img_org, dilation_dst, element);
	dilate(erode_dst, open_dst, element);

	morphologyEx(img_org, open_dst_fn, MORPH_OPEN, element);
	imshow("original", img_org);
	imshow("erode", erode_dst);
	imshow("dilate", dilation_dst);
	imshow("open", open_dst);
	imshow("open fn", open_dst);*/

	waitKey(0);

	return 0;
}

/** @function readme */
void readme()
{
	std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl;
}