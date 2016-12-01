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
#include "X_Element.h"
#include "Y_Element.h"

using namespace cv;
using namespace std;


class MatModifies
{
public:
	Mat cropImage(Mat, int, int, int, int);
	Mat addRowEnd(Mat);
	Mat addRowBegin(Mat);
	Mat cut(Mat, vector<cv::Point>, int&);
	int addPts(Mat, cv::Point, cv::Point, int, int, int, vector<cv::Point>&);//1 cat ngang, -1 cat doc, 0 khong cat
	int getValleyY(vector<cv::Point>, int);
	void insert(vector<cv::Point>&, vector<cv::Point>, int);
	void findMinMax(Mat, int&, int&, int&, int&);
};
#endif