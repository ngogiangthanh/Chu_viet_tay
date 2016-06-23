#include "Header.h"

Mat Header::getSrc()
{
	return src;
}

Mat Header::getDist()
{
	return dist;
}

System::Void Header::setDist(Mat dist)
{
	this->dist = dist.clone();
}

System::Void Header::setSrc(Mat src)
{
	this->src = src.clone();
	cv::Size s = this->src.size();
	height = s.height;
	width = s.width;
	this->dist = Mat(height, width, CV_8UC3, Scalar(255, 255, 255));
	cvtColor(this->dist, this->dist, COLOR_BGR2GRAY);

}

System::Void Header::downSource(int x, int y, int y_limit)
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

System::Void Header::upSource(int x, int y, int y_limit)
{
	Scalar intensity_dist = dist.at<uchar>(y, x);
	if (x >= 1 & y >= 1 & x < width - 1 & y <= y_limit & intensity_dist[0] == 255) {
		dist.at<uchar>(y, x) = 0;
		Scalar top, right, left, bot;
		top = src.at<uchar>(y - 1, x);//top
		left = src.at<uchar>(y, x - 1);//left
		right = src.at<uchar>(y, x + 1);//right
		bot = src.at<uchar>(y + 1, x);//bottom

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
