#pragma once
#include "iostream"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#define INIT_VAL -100

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
	void threshold(unsigned int = 0, unsigned int = 255, unsigned int = CV_THRESH_OTSU);
	void gaussianBlur(unsigned int);
	void averageBlur(unsigned int);
	void medianBlur(unsigned int);
	void adaptiveMedian(unsigned int = 15);
	void addElement(int*, int, unsigned int);
	void laplacian(unsigned int, int = CV_8U, int = 1, int = 0);
	void adaptive(bool, bool, unsigned int, unsigned int);
	void Morphology_Operations(int, int, int);
	void setSrc(Mat);
	void setDist(Mat);
	Mat getSrc();
	Mat getDist();
};