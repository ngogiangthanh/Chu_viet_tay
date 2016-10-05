#pragma once
#include "iostream"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Projection
{
	private:
		Mat source;
		int* projection_pts;
		int max;
	public:
		Projection(Mat);
		void getFeatures();
		int* getProjection_pts();
};