#pragma once
#define Noise_H
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

class Noise
{
private:
	Mat image;
public:
	Noise(Mat);
	void Salt(int);
	void Pepper(int);
	void setImage(Mat);
	Mat getImage();
};
#ifndef Noise_H
#endif
