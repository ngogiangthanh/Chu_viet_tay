#pragma once
#ifndef MatModifies_H
#define MatModifies_H
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;


class MatModifies
{
public:
		Mat cropImage(Mat, int, int, int, int);
		Mat addRowEnd(Mat);
		Mat addRowBegin(Mat);
		Mat cut(Mat, vector<Point>*);
};
#endif
