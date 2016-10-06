#pragma once
#include "iostream"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#define THRESHOLD_INK_UP 180
#define NORMALIZATION_WP_UP 100
#define INK_UP 0
#define BACKGROUND_UP 255

using namespace cv;
using namespace std;

class Word_Up
{
private:
	Mat source;
	int* up;
	int max;
public:
	Word_Up(Mat);
	void cal_up();
	int is_ink(int, int);
	int* get_up();
	void interpolated_value();
	void draw_up();
};