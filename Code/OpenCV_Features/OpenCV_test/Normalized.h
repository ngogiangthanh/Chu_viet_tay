#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#define THRESHOLD_INK 200
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
	int upperBaseLine;
	int lowerBaseLine;
public:
	Normalized(Mat);
	void MeasurementOfAverageStrokeThickness();
	void StraightLineRemoval();
	void BaseLineDetection();
	void UnderlineDetectionAndRemoval();
	void SkewDetectionUsesCentreOfMass();
	void RemovalOfUnderlinesMatchingTheSlopeOfTheWord();
	void setWord(Mat);
	Mat getWord();
};
