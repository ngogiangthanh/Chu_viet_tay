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

void MatModifies::addPts(Mat src, cv::Point start, cv::Point end, int height_of_lines, int y_pre_valley, int y_next_valley)
{
	cv::Size size = src.size();
	int x_max = 0;
	int y_max = 0;
	int x_min = size.width;
	int y_min = size.height;
	int x_line = 0;
	int x_line_end = 0;
	Obstructing* obstructing = new Obstructing();
	DrawDecision* drawDecision = new DrawDecision();
	ShortestPath* shortest = new ShortestPath(src);

	obstructing->setSrc(src);
	obstructing->setHeightOfLines(height_of_lines);
	//Tiến hành lấy phần liên thông

	vector<cv::Point>* pts = new vector<cv::Point>();
	vector<cv::Point>* v_pts;
	cout << "Kiem tra.... " << start.x  << ", " << start.y << endl;
	cout << "y pre valley = " << y_pre_valley << endl;
	cout << "y next valley = " << y_next_valley << endl;

	for (int i = start.x; i < end.x; i++) {

		obstructing->setX(i);
		obstructing->setY(start.y);
		if (obstructing->isCut()) {
			cout << "Bat dau cat tai x,y = " << i << ", " << start.y << endl;
			x_line_end = i;

			pts->push_back(cv::Point(x_line, start.y));
			pts->push_back(cv::Point(x_line_end, start.y));

			Mat rs = obstructing->obstructing(ALL, y_pre_valley, y_next_valley);
			x_max = obstructing->getXMax();
			y_max = obstructing->getYMax();
			x_min = obstructing->getXMin();
			y_min = obstructing->getYMin();
			y_min = obstructing->convert(obstructing->getYMin(), y_pre_valley, true);
			y_max = obstructing->convert(obstructing->getYMax(), y_pre_valley, true);

			//Tìm phần cắt cuối cùng
			int z = 0;
			for (z = x_max; z > i; z--) {
				obstructing->setX(z);
				obstructing->setY(start.y);
				if (obstructing->isCut()) {
					cout << "Ket thuc cat tai x,y = " << z << ", " << start.y << endl;
					break;
				}
			}

			Mat rsCrop = this->cropImage(src, x_min - 1, y_min, x_max + 1, y_max);
			cv::line(rsCrop, cv::Point(0, 0), cv::Point(0, rsCrop.rows), Scalar(255, 255, 255));
			cv::line(rsCrop, cv::Point(rsCrop.cols - 1, 0), cv::Point(rsCrop.cols - 1, rsCrop.rows), Scalar(255, 255, 255));

			//Decision draw
			drawDecision->setYu(y_min);
			drawDecision->setYd(y_max);
			drawDecision->setYCurrValley(start.y);
			drawDecision->setYPreValley(y_pre_valley);
			drawDecision->setYNextValley(y_next_valley);
			Node* X;

			switch (drawDecision->decision()) {
			case UP_UP:
				rsCrop = this->addRowBegin(rsCrop);

				cout << "Ke len tren phan lien thong tren" << endl;
				shortest = new ShortestPath(rsCrop);

				shortest->setX_start(i - x_min - 2);
				shortest->setY_start(start.y - y_min);
				shortest->setX_goal(z - x_min + 2);
				shortest->setY_goal(start.y - y_min);
				shortest->init();
				X = shortest->Astar();
				//Thêm
				v_pts = shortest->print(X, src, x_min, y_min);
				pts->insert(pts->end(), v_pts->begin(), v_pts->end());
				break;
			case DOWN_DOWN:
				cout << "Ke xuong duoi phan lien thong duoi" << endl;
				rsCrop = this->addRowEnd(rsCrop);
				shortest = new ShortestPath(rsCrop);

				shortest->setX_start(i - x_min - 2);
				shortest->setY_start(start.y - y_min);
				shortest->setX_goal(z - x_min + 2);
				shortest->setY_goal(start.y - y_min);
				shortest->init();
				X = shortest->Astar();
				//Thêm
				v_pts = shortest->print(X, src, x_min, y_min);
				pts->insert(pts->end(), v_pts->begin(), v_pts->end());
				pts->push_back(cv::Point(z + 2, start.y));
				pts->push_back(cv::Point(x_max, start.y));

				cv::line(src, cv::Point(z + 2, start.y), cv::Point(x_max, start.y), Scalar(200, 200, 200));
				break;
			case UP_DOWN:
			case THROUGH:
				cout << "Ke cat ngang" << endl;
				pts->push_back(cv::Point(i, start.y));
				pts->push_back(cv::Point(x_max, start.y));

				cv::line(src, cv::Point(i, start.y), cv::Point(x_max, start.y), Scalar(200, 200, 200));
				break;
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

int MatModifies::getValleyY(vector<cv::Point> pts, int x)
{
	int y;
	int s_el = (int)pts.size();
	if (s_el == 0) return -1;
	for (vector<int>::size_type k = 1; k != s_el; k++) {
		if (pts.at(k).x > x) 
			return pts.at(k - 1).y;
	}
	return -2;
}
