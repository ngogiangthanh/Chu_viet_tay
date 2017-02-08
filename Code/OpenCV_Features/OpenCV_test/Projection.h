#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#define NORMALIZATION_PP 100

using namespace cv;
using namespace std;
/*
* Class name: Projection
* Description: Projection profile - the first feature that use to DTW algorithm
*/
class Projection
{
private:
	Mat source;
	float* pp;
	float max;
public:
	Projection(Mat);
	void cal_pp();
	float I(int, int);
	int get_pp(float *&);
	Mat draw_pp();
};