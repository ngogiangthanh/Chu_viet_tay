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
public:
	Normalized(Mat);
	void MeasurementOfAverageStrokeThickness();
	void StraightLineRemoval();
	void BaseLineDetection(Mat,int&,int&);
	void SkewDetectionUsesCentreOfMass(int, int, int, int );
	void SkewDetectionUsesCentreOfMass(int, int);
	int xCentroid(int, int, int, int);
	int yCentroid(int, int, int);
	void setWord(Mat);
	Mat getWord();
};
