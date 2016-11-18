#pragma once
#ifndef MatModifies_H
#define MatModifies_H
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Obstructing.h"
#include "DrawDecision.h"
#include "ShortestPath.h"

using namespace cv;
using namespace std;


class MatModifies
{
public:
	Mat cropImage(Mat, int, int, int, int);
	Mat addRowEnd(Mat);
	Mat addRowBegin(Mat);
	Mat cut(Mat, vector<cv::Point>);
	void addPts(Mat, cv::Point, cv::Point, int, int, int, vector<cv::Point>&);
	int getValleyY(vector<cv::Point>, int);
};
#endif