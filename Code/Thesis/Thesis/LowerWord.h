#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#define THRESHOLD_INK_LP 180
#define NORMALIZATION_WP_LP 100
#define INK_LP 0
#define BACKGROUND_LP 255

using namespace cv;
using namespace std;
/*
* Class name: LowerWord
* Description: Lower word profile - the third feature that use to DTW algorithm
*/
class LowerWord
{
private:
	Mat source;
	float* lp;
	float max;
public:
	LowerWord(Mat);
	void cal_lp();
	int is_ink(int, int);
	int get_lp(float *&);
	void interpolated_value();
	Mat draw_lp();
};