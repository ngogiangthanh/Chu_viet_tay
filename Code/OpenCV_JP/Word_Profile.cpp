#include "Word_Profile.h"
#define NORMALIZATION_WP 100

Word_Profile::Word_Profile(float *up, float *lp, int size)
{
	this->up = up;
	this->lp = lp;
	this->size = size;
}

void Word_Profile::combined(float*& wp)
{
	//this->wp = new float[size];
	wp = new float[size];
	for (int i = 0; i < size; i++) {
		//this->wp[i] = (float) (this->lp[i] + this->up[i]) / 2;
		wp[i] = (float) (this->lp[i] + this->up[i]) / 2;
	}
}

Mat Word_Profile::draw_wp(){

	Mat dist = Mat(100, size, CV_8UC3, Scalar(255, 255, 255));

	for (int i = 0; i < this->size; i++)
		cv::line(dist, Point(i, round(this->wp[i] * (NORMALIZATION_WP - 1))), Point(i, round(this->wp[i + 1] * (NORMALIZATION_WP - 1))), Scalar(0, 0, 0));

	//Show
	imshow("Word word profile", dist);
	imwrite("D:/save_wp.jpg", dist);

	return dist;
}
