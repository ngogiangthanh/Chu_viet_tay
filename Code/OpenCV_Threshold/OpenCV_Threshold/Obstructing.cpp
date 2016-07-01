#include "Obstructing.h"

Obstructing::Obstructing()
{

}

int Obstructing::getX()
{
	return this->x;
}

int Obstructing::getY()
{
	return this->y;
}

Mat Obstructing::getSrc()
{
	return this->src;
}

Mat Obstructing::getDist()
{
	return this->dist;
}

System::Void Obstructing::setX(int x)
{
	this->x = x;
}

System::Void Obstructing::setY(int y)
{
	this->y = y;
}

System::Void Obstructing::setDist(Mat dist)
{
	this->dist = dist.clone();
}

System::Void Obstructing::setSrc(Mat src)
{
	this->src = src.clone();
	cv::Size s = this->src.size();
	this->height = s.height;
	this->width = s.width;
	this->dist = Mat(this->height, this->width, CV_8UC3, Scalar(255, 255, 255));
	cvtColor(this->dist, this->dist, COLOR_BGR2GRAY);
}

System::Void Obstructing::allSource(int x, int y, int& x_min, int& y_min, int& x_max, int& y_max)
{
	Scalar intensity_dist = this->dist.at<uchar>(y, x);
	if (x >= 1 & y >= 1 & x < width - 1 & intensity_dist[0] == 255) {
		if (x < x_min) x_min = x;
		else if (x > x_max) x_max = x;
		if (y < y_min) y_min = y;
		else if (y > y_max) y_max = y;

		this->dist.at<uchar>(y, x) = 0;
		Scalar top, right, left, bot;
		top = this->src.at<uchar>(y - 1, x);//top
		left = this->src.at<uchar>(y, x - 1);//left
		right = this->src.at<uchar>(y, x + 1);//right
		bot = this->src.at<uchar>(y + 1, x);//bottom

		if ((top[0] <= 200)) {
			allSource(x, y - 1, x_min, y_min, x_max, y_max);
		}
		if ((left[0] <= 200)) {
			allSource(x - 1, y, x_min, y_min, x_max, y_max);
		}
		if ((right[0] <= 200)) {
			allSource(x + 1, y, x_min, y_min, x_max, y_max);
		}
		if ((bot[0] <= 200)) {
			allSource(x, y + 1, x_min, y_min, x_max, y_max);
		}
	}
	return System::Void();
}

System::Void Obstructing::upSource(int x, int y, int y_limit)
{
	Scalar intensity_dist = this->dist.at<uchar>(y, x);
	if (x >= 1 & y >= 1 & x < width - 1 & y <= y_limit & intensity_dist[0] == 255) {
		this->dist.at<uchar>(y, x) = 0;
		Scalar top, right, left, bot;
		top = this->src.at<uchar>(y - 1, x);//top
		left = this->src.at<uchar>(y, x - 1);//left
		right = this->src.at<uchar>(y, x + 1);//right
		bot = this->src.at<uchar>(y + 1, x);//bottom

		if ((top[0] <= 200)) {
			upSource(x, y - 1, y_limit);
		}
		if ((left[0] <= 200)) {
			upSource(x - 1, y, y_limit);
		}
		if ((right[0] <= 200)) {
			upSource(x + 1, y, y_limit);
		}
		if ((bot[0] <= 200)) {
			upSource(x, y + 1, y_limit);
		}
	}
	return System::Void();
}

System::Void Obstructing::downSource(int x, int y, int y_limit)
{
	Scalar intensity_dist = dist.at<uchar>(y, x);
	if (x >= 1 & y >= y_limit & x < width - 1 & y < height - 1 & intensity_dist[0] == 255) {
		dist.at<uchar>(y, x) = 0;
		Scalar top, right, left, bot;
		top = src.at<uchar>(y - 1, x);//top
		left = src.at<uchar>(y, x - 1);//left
		right = src.at<uchar>(y, x + 1);//right
		bot = src.at<uchar>(y + 1, x);//bottom

		if ((top[0] <= 200)) {
			downSource(x, y - 1, y_limit);
		}
		if ((left[0] <= 200)) {
			downSource(x - 1, y, y_limit);
		}
		if ((right[0] <= 200)) {
			downSource(x + 1, y, y_limit);
		}
		if ((bot[0] <= 200)) {
			downSource(x, y + 1, y_limit);
		}
	}
	return System::Void();
}
