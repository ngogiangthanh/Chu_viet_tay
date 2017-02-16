#pragma once
#include <iostream>
#include <cmath>
#include "Equations.h"
#include <opencv2/opencv.hpp>
#define infinity 100

using namespace std;
using namespace cv;

class Dynamic_Time_Warping
{
private:
	float** DTW; //results matrix
	float* X; //vector X
	float* Y; //vector Y
	int M, N; //length of X,Y
	Mat draw;

public:
	Dynamic_Time_Warping(float*, float*, int, int);
	float minimum(float, float, float);
	float max(float, float);
	float min(float, float);
	float DTWDistance();
	float DTWDistance_GPC(int);
	int pathWarping();
	void drawMatching();
	Mat getDraw();
};


