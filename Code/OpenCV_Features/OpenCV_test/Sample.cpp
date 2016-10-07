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

	if (!img_org.data)
	{
		cout << " --(!) Error reading images " << endl;
		return -1;
	}

	////-- Step 1: Detect the keypoints using SURF Detector
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
	//-----------------------
	Projection projection_profile(img_org);
	projection_profile.cal_pp();
	projection_profile.draw_pp();
	int* pp = projection_profile.get_pp();

	Word_Up word_up(img_org);
	word_up.cal_up();
	word_up.interpolated_value();
	word_up.draw_up();
	int* wup = word_up.get_up();

	Word_lp word_lp(img_org);
	word_lp.cal_lp();
	word_lp.interpolated_value();
	word_lp.draw_lp();
	int* wlp = word_lp.get_lp();

	nbit nbit_p(img_org);
	nbit_p.cal_nbit();
	nbit_p.interpolated_value();
	nbit_p.draw_nbit();
	//nbit_p.get_nbit();
	
	//------------DTW---------
	int a[] = {1,2,2};
		int b[] = {1,2,4,6};
	int height = (sizeof(a)/sizeof(*a));
	int width = (sizeof(b)/sizeof(*b));
	DTWDistance(a, b,height,width);
	waitKey(0);

	return 0;
}

/** @function readme */
void readme()
{
	std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl;
}