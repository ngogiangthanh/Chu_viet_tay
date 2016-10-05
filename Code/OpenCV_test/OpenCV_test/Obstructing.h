#pragma once
#ifndef  _Obstructing_H_
#define _Obstructing_H_
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#define ALL 0
#define UP 1
#define DOWN 2
#define THRESHOLD 200

using namespace cv;
using namespace std;
class Obstructing
{
private: Mat src;
		 int width, height;
		 int x, y, x_max, y_max, x_min, y_min;

public:
		Obstructing();
		int getX();
		int getY();
		int getXMin();
		int getYMin();
		int getXMax();
		int getYMax();
		Mat getSrc();
		void setX(int);
		void setY(int);
		void setXMin(int);
		void setYMin(int);
		void setXMax(int);
		void setYMax(int);
		void setSrc(Mat);
		Mat obstructing(int, int, int);
		void findMaxMin(Mat);
		bool isCut();
		int convert(int, int, bool);
};
#endif // ! _Obstruting_H_

