#pragma once
#ifndef Preprocess_H
#define Preprocess_H
#include "iostream"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
class Preprocess
{
	private:
		Mat src;
		Mat dist;
	public:
		Preprocess(Mat);
		Preprocess(Mat, Mat);
		void threshold(unsigned int, unsigned int, unsigned int);
		void gaussianBlur(unsigned int);
		void averageBlur(unsigned int);
		void medianBlur(unsigned int);
		void laplacian(unsigned int, int = CV_8U, int = 1, int = 0);
		void setSrc(Mat);
		void setDist(Mat);
		Mat getSrc();
		Mat getDist();
};
#endif
