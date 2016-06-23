#pragma once
#ifndef  _Header_H_
#define _Header_H_
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;
class Header
{
private: Mat src,dist;
		 int width, height;
public: Mat getSrc();
		Mat getDist();
		System::Void setDist(Mat);
		System::Void setSrc(Mat);
		System::Void upSource(int, int, int);
		System::Void downSource(int, int, int);
};
#endif // ! _Header_H_
