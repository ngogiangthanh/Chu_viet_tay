﻿#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
using namespace cv;
using namespace std;

class SIFT
{
private:
public:
	SIFT();
	void FeatureMatching(Mat, Mat, bool);
};