#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*Class name : Word_Profile
* Description : Upper/word word profile combined
*/
class Word_Profile
{
	int size;
	float* up;
	float* lp;
	float * wp;

public:
	Word_Profile(float*, float*, int);
	void combined(float*&);
	Mat draw_wp();
};
