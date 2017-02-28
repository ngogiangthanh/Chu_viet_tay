#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#define THRESHOLD_INK_UP 180
#define NORMALIZATION_WP_UP 100
#define INK_UP 0
#define BACKGROUND_UP 255

using namespace cv;
using namespace std;
/*
* Class name: UpperWord
* Description: Upper word profile - the second feature that use to DTW algorithm
*/
class UpperWord
{
private:
	Mat source;
	float* up;
	float max;
public:
	UpperWord(Mat);
	void cal_up();
	int is_ink(int, int);
	int get_up(float *&);
	void interpolated_value();
	Mat draw_up();
};