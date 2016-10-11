#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#define NORMALIZATION_PP 100

using namespace cv;
using namespace std;
/*
* Class name: Projection
* Description: Projection profile - the frist feature that use to DTW algorithm
*/
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
		int get_pp(int *&);
		void draw_pp();
};