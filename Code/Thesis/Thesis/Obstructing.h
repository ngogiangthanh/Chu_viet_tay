#pragma once
#ifndef  _Obstructing_H_
#define _Obstructing_H_
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
class Obstructing
{
private: Mat src, dist;
		 int width, height;
		 int x, y;
public: Obstructing();
		Mat getSrc();
		Mat getDist();
		System::Void setDist(Mat);
		System::Void setSrc(Mat);
		System::Void allSource(int, int);
		System::Void upSource(int, int, int);
		System::Void downSource(int, int, int);
};
#endif // ! _Obstruting_H_

