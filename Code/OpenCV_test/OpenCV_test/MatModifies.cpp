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

Mat MatModifies::cut(Mat src, Elements * line_pre, Elements * line_curr)
{
	//Tim x_max, y_max, x_min, y_min
	int x_min = 0;
	int y_min = 0;
	int x_max = 0;
	int y_max = 0;

	vector<Element*> el = line_curr->getElements();
	int s = el.size();

	for (vector<int>::size_type m = 0; m != s; m++) {
		if (el[m]->getX() > x_max) x_max = el[m]->getX();
		if (el[m]->getY() > y_max) y_max = el[m]->getY();
	}

	//Cat theo x_max, y_max, x_min, y_min
	Mat rs = this->cropImage(src, x_min, y_min, x_max, y_max);
	//Xoa phan du
	for (vector<int>::size_type m = 0; m != s; m++) {
		if (!el[m]->isNext() & !el[m]->isPre()) {
			cv::line(rs, cv::Point(el[m]->getX(), el[m]->getY()), cv::Point(el[m]->getX(), y_max), Scalar(255, 255, 255));
		}
	}
	return rs;
}
