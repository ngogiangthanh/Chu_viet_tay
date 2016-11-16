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

int Obstructing::getXMin()
{
	return this->x_min;
}

int Obstructing::getYMin()
{
	return this->y_min;
}

int Obstructing::getXMax()
{
	return this->x_max;
}

int Obstructing::getYMax()
{
	return this->y_max;
}

Mat Obstructing::getSrc()
{
	return this->src;
}

void Obstructing::setX(int x)
{
	this->x = x;
}

void Obstructing::setY(int y)
{
	this->y = y;
}

void Obstructing::setXMin(int x)
{
	this->x_min = x;
}

void Obstructing::setYMin(int y)
{
	this->y_min = y;
}

void Obstructing::setXMax(int x)
{
	this->x_max = x;
}

void Obstructing::setYMax(int y)
{
	this->y_max = y;
}


void Obstructing::setSrc(Mat src)
{
	this->src = src.clone();
	cv::Size s = this->src.size();
	this->height = s.height;
	this->width = s.width;
}

Mat Obstructing::obstructing(int obstructing_type, int y_min, int y_max)
{
	//int y_r = y - this->height_of_lines * 2;

	cv::Rect crop(0, y_min, this->width, y_max - y_min);
	Mat imageUpSource = this->src(crop);
	this->height = y_max - y_min;

	Mat dist = Mat(imageUpSource.size(), CV_8UC1, Scalar(255, 255, 255));

	this->y = this->convert(this->y, y_min, false);
	switch (obstructing_type) {
	case UP:
		for (int i = 0; i < this->width; i++)
			for (int j = this->y + 1; j < this->height; j++)
				imageUpSource.at<uchar>(j, i) = 255;
		break;
	case DOWN:
		for (int i = 0; i < this->width; i++)
			for (int j = 0; j < this->y - 1; j++)
				imageUpSource.at<uchar>(j, i) = 255;
		break;
	}

	dist.at<uchar>(this->y, this->x) = 0;

	long count_cur = 1;
	long count_pre = 0;
	while (count_cur != count_pre) {

		Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
		erode(dist, dist, element);
		bitwise_or(dist, imageUpSource, dist);
		count_pre = count_cur;
		count_cur = 0;
		for (int i = 0; i < this->width; i++)
			for (int j = 0; j < this->height; j++) {
				cv::Scalar intentsity = dist.at<uchar>(j, i);
				
				if (intentsity[0] <= THRESHOLD) {
					count_cur++;
				}
			}
	}
	this->findMaxMin(dist);
	/*cout << "x_min" << this->x_min << endl;
	cout << "y_min" << this->y_min << endl;
	cout << "x_max" << this->x_max << endl;
	cout << "y_max" << this->y_max << endl;*/

	imwrite("D:\\src.jpg", imageUpSource);
	imwrite("D:\\dist.jpg", dist);
	return dist;
}

void Obstructing::findMaxMin(Mat dist)
{
	//Init max min
	this->x_min = this->width;
	this->y_min = this->height;
	this->x_max = 0;
	this->y_max = 0;
	//Find
	for (int i = 0; i < this->width; i++)
		for (int j = 0; j < this->height; j++) {
			cv::Scalar intentsity = dist.at<uchar>(j, i);
			if (intentsity[0] <= THRESHOLD) {
				if (i < this->x_min) this->x_min = i;
				else if (i > this->x_max) this->x_max = i;
				if (j < this->y_min) this->y_min = j;
				else if (j > this->y_max) this->y_max = j;
			}
		}
}

bool Obstructing::isCut()
{
	cv::Scalar pix_curr = this->src.at<uchar>(this->y, this->x);
	if (pix_curr[0] <= THRESHOLD) {
		cv::Scalar pix_top = (this->y - 1 >= 0) ? this->src.at<uchar>(this->y - 1, this->x) : pix_curr;
		cv::Scalar pix_tl = (this->x - 1 >= 0 & this->y - 1 >= 0) ? this->src.at<uchar>(this->y - 1, this->x - 1) : pix_curr;
		cv::Scalar pix_tr = (this->x + 1 < this->width & this->y - 1 >= 0) ? this->src.at<uchar>(this->y - 1, this->x + 1) : pix_curr;
		cv::Scalar pix_l = (this->x - 1 >= 0) ? this->src.at<uchar>(this->y, this->x - 1) : pix_curr;
		cv::Scalar pix_r = (this->x + 1 < this->width) ? this->src.at<uchar>(this->y, this->x + 1) : pix_curr;
		cv::Scalar pix_bot = (this->y + 1 < this->height) ? this->src.at<uchar>(this->y + 1, this->x) : pix_curr;
		cv::Scalar pix_bl = (this->x - 1 >= 0 & this->y + 1 < this->height) ? this->src.at<uchar>(this->y + 1, this->x - 1) : pix_curr;
		cv::Scalar pix_br = (this->x + 1 < this->width & this->y + 1 < this->height) ? this->src.at<uchar>(this->y + 1, this->x + 1) : pix_curr;
		//check condition
		if (pix_top[0] <= THRESHOLD)
			return true;
		if (pix_tl[0] <= THRESHOLD)
			return true;
		if (pix_tr[0] <= THRESHOLD)
			return true;
		if (pix_l[0] <= THRESHOLD)
			return true;
		if (pix_r[0] <= THRESHOLD)
			return true;
		if (pix_bot[0] <= THRESHOLD)
			return true;
		if (pix_bl[0] <= THRESHOLD)
			return true;
		if (pix_br[0] <= THRESHOLD)
			return true;
	}
	return false;
}

int Obstructing::convert(int y, int y_pre_valley, bool isInvert)
{
	cv::Point result;
	//Invert is converting from ' to orginal
	if (isInvert)
		y = y + y_pre_valley;
	else
		y = y - y_pre_valley;

	return y;
}
