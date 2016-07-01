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
	private: Mat src;
			 Mat dist;
	public: MatModifies(Mat);
			void cropImage(int, int, int, int);
			Mat getSrc();
			Mat getDist();
			void setSrc(Mat);
			void setDist(Mat);
			Mat addRowEnd();
			Mat addRowBegin();
};
#endif
