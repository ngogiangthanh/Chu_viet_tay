#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#define NORMALIZATION_NBIT 100
#define THRESHOLD_INK_NBIT 180

using namespace cv;
using namespace std;
/*
* Class name: nbit
* Description: nbit profile - the fourth feature that use to DTW algorithm
*/
class nbit
{
private:
	Mat source;
	float* nbit_p;
	float max;
public:
	nbit(Mat);
	void cal_nbit();
	bool is_bground_to_ink(int, int);
	int get_nbit(float *&);
	void interpolated_value();
	Mat draw_nbit();
};
