#pragma once
#include "iostream"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#define NORMALIZATION_PP 100

using namespace cv;
using namespace std;

class Projection
{
	private:
		Mat source;
		int* pp;
		int max;
	public:
		Projection(Mat);
		void cal_pp();
		int I(int, int);
		int* get_pp();
		void draw_pp();
};