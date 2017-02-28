#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#define NORMALIZATION_PP 100

using namespace cv;
using namespace std;
/*
* Class name: ProjectionProfiles
* Description: ProjectionProfiles profile - the first feature that use to DTW algorithm
*/
class ProjectionProfiles
{
private:
	Mat source;
	float* pp;
	float max;
public:
	ProjectionProfiles(Mat);
	void cal_pp();
	float I(int, int);
	int get_pp(float *&);
	Mat draw_pp();
};