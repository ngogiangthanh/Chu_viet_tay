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

Mat MatModifies::cut(Mat src, vector<Point> pts)
{
	//Tim x_max, y_max, x_min, y_min
	cv::Size size = src.size();
	int x_min = size.width;
	int y_min = size.height;
	int x_max = 0;
	int y_max = 0;

	int numPoints = (int) pts.size();

	for (vector<int>::size_type m = 0; m != numPoints; m++) {
		if (pts.at(m).x > x_max) x_max = pts.at(m).x;
		if (pts.at(m).x < x_min) x_min = pts.at(m).x;
		if (pts.at(m).y > y_max) y_max = pts.at(m).y;
		if (pts.at(m).y < y_min) y_min = pts.at(m).y;
	}

	//Cat theo x_max, y_max, x_min, y_min
	Mat rs = this->cropImage(src, x_min, y_min, x_max, y_max);
	//Tao mask và ghép 2 hình với nhau
	Mat mMask = Mat(src.size(), CV_8UC1, Scalar(0, 0, 0));
	const Point* elementPoints[1] = { &pts.at(0) };
	fillPoly(mMask, elementPoints, &numPoints, 1 , Scalar(255, 255, 255));
	mMask = this->cropImage(mMask, x_min, y_min, x_max, y_max);

	Mat Destination;
	rs.copyTo(Destination, mMask);

	 mMask = Mat(src.size(), CV_8UC1, Scalar(255, 255, 255));
	fillPoly(mMask, elementPoints, &numPoints, 1, Scalar(0, 0, 0));
	mMask = this->cropImage(mMask, x_min, y_min, x_max, y_max);

	bitwise_xor(mMask, Destination, Destination);

	return Destination;
}

void MatModifies::addPts(Mat src, cv::Point start, cv::Point end, int height_of_lines)
{
	cv::Size size = src.size();
	int x_max = 0;
	int y_max = 0;
	int x_min = size.width;
	int y_min = size.height;
	int x_line = 0;
	int x_line_end = 0;
	DrawDecision drawDecision;
	ShortestPath shortest(src);
	Obstructing obstructing;
	obstructing.setSrc(src);
	obstructing.setHeightOfLines(height_of_lines);
	//Tiến hành lấy phần liên thông
	cout << endl;
	cout << "Kiem tra.... " << start.x  << ", " << end.x << endl;
	for (int i = start.x; i < end.x; i++) {

		obstructing.setX(i);
		obstructing.setY(start.y);
		if (obstructing.isCut()) {
			x_line_end = i;
			//Thêm
			//pts->push_back(cv::Point(x_line, y_start));
			//pts->push_back(cv::Point(x_line_end, y_start));
			//cv::line(src, cv::Point(x_line, y_start), cv::Point(x_line_end, y_start), Scalar(200, 200, 200));
			cout << "Bat dau cat tai x,y = " << x_line_end << ", "<< start.y << endl;
			//Lấy kết quả phần liên thông
			Mat rs = obstructing.obstructing(ALL);
			x_max = obstructing.getXMax();
			y_max = obstructing.getYMax();
			x_min = obstructing.getXMin();
			y_min = obstructing.getYMin();
			//Cắt phần liên thông và lưu

			Mat rsCrop = this->cropImage(rs, x_min - 1, y_min, x_max + 2, y_max);
			string savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/obstructing_" + std::to_string(x_line_end) + ".jpg";
			imwrite(savePath, rs);
			//Tìm phần cắt cuối cùng
			int z = 0;
			for (z = x_max; z > i; z--) {
				obstructing.setX(z);
				obstructing.setY(start.y);
				if (obstructing.isCut()) {
					cout << "Ket thuc cat tai x,y = " << z << ", " << start.y << endl;
					break;
				}
			}

			//Bắt đầu lặp từ phần cuối phần liên thông trước đó
			if (end.x > x_max) {
				i = x_max + 1;
				x_line = i;
			}
			else
				break;
		}//if
	}//for i
}
