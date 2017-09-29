#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <iomanip>
#define _USE_MATH_DEFINES // for C++  
#include <math.h>
#include "MatModifies.h"

#define THRESHOLD_INK 220
using namespace std;
using namespace cv;
/*
* Class name: Normalized
* Description: Detecting and removing skew, straingth line
*/
class Normalized
{
private:
	Mat word;
	int AST;
	int peak_line;
public:
	Normalized(Mat);
	void MeasurementOfAverageStrokeThickness();
	void StraightLineRemoval();
	void UnderlineRemoval();
	void BaseLineDetection(Mat&,int&,int&);
	Mat SkewDetectionUsesCentreOfMass(int, int, int, int );
	Mat SkewDetectionUsesCentreOfMass(int, int);
	int xCentroid(Mat, int, int, int, int);
	int yCentroid(Mat, int, int, int);
	void setWord(Mat);
	Mat getWord();
	void hough_transform(Mat& im, Mat& orig, double* skew);
	Mat preprocess1(Mat& im);
	Mat preprocess2(Mat& im);
	Mat rot(Mat& im, double thetaRad);
	Mat Skeleton(Mat);
};
