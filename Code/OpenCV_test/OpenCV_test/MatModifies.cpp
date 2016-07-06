#include "MatModifies.h"


Mat MatModifies::cropImage(Mat mat, int x_min, int y_min, int x_max, int y_max)
{
	cv::Rect crop(x_min, y_min, x_max - x_min, y_max - y_min);
	return mat(crop);
}

Mat MatModifies::addRowEnd(Mat mat)
{
	cv::Size size = mat.size();
	Mat row = Mat(1, size.width, CV_8UC1, Scalar(255, 255, 255));
	mat.push_back(row);
	return mat;
}

Mat MatModifies::addRowBegin(Mat mat)
{
	cv::Size size = mat.size();
	Mat row = Mat(1, size.width, CV_8UC1, Scalar(255, 255, 255));
	row.push_back(mat);
	return row;
}

Mat MatModifies::cut(Mat src, vector<Point>* pts)
{
	//Tim x_max, y_max, x_min, y_min
	cv::Size size = src.size();
	int x_min = size.width;
	int y_min = size.height;
	int x_max = 0;
	int y_max = 0;

	int numPoints = pts->size();

	for (vector<cv::Point>::size_type m = 0; m != numPoints; m++) {
		if (pts->at(m).x > x_max) x_max = pts->at(m).x;
		if (pts->at(m).x < x_min) x_min = pts->at(m).x;
		if (pts->at(m).y > y_max) y_max = pts->at(m).y;
		if (pts->at(m).y < y_min) y_min = pts->at(m).y;
	}

	//Cat theo x_max, y_max, x_min, y_min
	Mat rs = this->cropImage(src, x_min, y_min, x_max, y_max);
	//Tao mask và ghép 2 hình với nhau
	Mat mMask = Mat(rs.size(), CV_8UC1, Scalar(0, 0, 0));
	const Point* elementPoints[1] = { &pts->at(0) };
	fillPoly(mMask, elementPoints, &numPoints, 1, Scalar(255, 255, 255));

	Mat Destination;
	rs.copyTo(Destination, mMask);
	imshow("mask", mMask);

	mMask = Mat(rs.size(), CV_8UC1, Scalar(255, 255, 255));
	fillPoly(mMask, elementPoints, &numPoints, 1, Scalar(0, 0, 0));

	bitwise_xor(mMask, Destination, Destination);

	return Destination;
}
