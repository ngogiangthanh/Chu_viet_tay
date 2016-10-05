#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "Projection.h"

using namespace cv;
using namespace std;

void readme();

/** @function main */
int main(int argc, char** argv)
{
	Mat img_org = imread("D:\\Thesis\\Chu_viet_tay\\SIFT\\sf_gt_v1.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	if (!img_org.data)
	{
		cout << " --(!) Error reading images " << endl;
		return -1;
	}

	//

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
	//-----------------------
	Projection projection_profile(img_org);
	projection_profile.getFeatures();
	projection_profile.getProjection_pts();

	waitKey(0);

	return 0;
}

/** @function readme */
void readme()
{
	std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl;
}