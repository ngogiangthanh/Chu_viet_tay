#pragma once
#include "iostream"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#define INIT_VAL -100

using namespace cv;
using namespace std;
class PreProcess
{
private:
public:
	void threshold(Mat, Mat&, unsigned int = 0, unsigned int = 255, unsigned int = CV_THRESH_OTSU);
	void gaussianBlur(Mat, Mat&, unsigned int);
	void averageBlur(Mat, Mat&, unsigned int);
	void medianBlur(Mat, Mat&, unsigned int);
	void adaptiveMedian(Mat, Mat&, unsigned int = 15);
	void laplacian(Mat, Mat&, unsigned int, int = CV_8U, int = 1, int = 0);
	void adaptive(Mat, Mat&, bool, bool, unsigned int, unsigned int);
	void Morphology_Operations(Mat, Mat&, int, int, int);
	void addElement(int *, int, unsigned int);
};