#include "MatModifies.h"

MatModifies::MatModifies(Mat src)
{
	this->src = src.clone();
	this->src.convertTo(this->src, CV_64F);
}

void MatModifies::cropImage(int x_min, int y_min, int x_max, int y_max)
{
	cv::Rect crop(x_min, y_min, x_max - x_min, y_max - y_min);
	this->src = this->src(crop);
}

Mat MatModifies::getSrc()
{
	return this->src;
}

Mat MatModifies::getDist()
{
	return this->dist;
}

void MatModifies::setSrc(Mat src)
{
	this->src = src.clone();
	this->src.convertTo(this->src, CV_64F);
}

void MatModifies::setDist(Mat dist)
{
	this->dist = dist.clone();
	this->src.convertTo(this->src, CV_64F);
}

Mat MatModifies::addRowEnd()
{
	cv::Size size = this->src.size();
	cv::Mat row = Mat(1, size.width, CV_64F, Scalar(255, 255, 255)); 
	//
	this->dist = this->src.clone();
	this->dist.push_back(row);
	//
	return this->dist;
}

Mat MatModifies::addRowBegin()
{
	cv::Size size = this->src.size();
	this->dist = Mat(1, size.width, CV_64F, Scalar(255, 255, 255));
	//
	this->dist.push_back(this->src);

	return this->dist;
}
