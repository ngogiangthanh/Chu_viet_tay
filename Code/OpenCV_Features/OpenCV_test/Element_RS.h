#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Element_RS
{
private:
	Mat draw;
	float cost;
	string pathSave;
	string pathSrc;
public:
	Element_RS(Mat, float, string, string);
	void setDraw(Mat);
	void setCost(float);
	void setPathSave(string);
	void setPathSrc(string);
	string getPathSave();
	string getPathSrc();
	float getCost();
	Mat getDraw();
	bool operator<(const Element_RS& rhs);
	bool operator==(const Element_RS& rhs);
};