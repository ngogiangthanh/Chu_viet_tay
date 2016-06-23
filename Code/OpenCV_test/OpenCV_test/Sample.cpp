#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"

using namespace cv;

void readme();

/** @function main */
int main( int argc, char** argv )
{
  //Mat img_org = imread("D:\\test.png", CV_LOAD_IMAGE_GRAYSCALE );

  //if(!img_org.data)
  //{ std::cout<< " --(!) Error reading images " << std::endl; return -1; }

  ////-- Step 1: Detect the keypoints using SURF Detector

  //Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create();
  //Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create();
  //std::vector<KeyPoint> surf_keypoint, sift_keypoint;

  //surf->detect(img_org, surf_keypoint);
  //sift->detect(img_org, sift_keypoint);
  // 
  ////-- Draw keypoints
  //Mat img_surf, img_sift; 

  //drawKeypoints(img_org, surf_keypoint, img_surf, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
  //drawKeypoints(img_org, sift_keypoint, img_sift, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

  ////-- Show detected (drawn) keypoints
  //imshow("Ảnh gốc", img_org);
  //imshow("SURF", img_surf);
  //imshow("SIFT", img_sift);

  	float a[] = {1,2,2};
  	float b[] = {1,2,3};
      int height = (sizeof(a)/sizeof(*a));
      int width = (sizeof(b)/sizeof(*b));
  	DTWDistance(a,b,height,width);

  waitKey(0);

  return 0;
  }

  /** @function readme */
  void readme()
  { std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl; }