﻿#include "MatModifies.h"


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
	int x_min = src.cols;
	int y_min = src.rows;
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

int MatModifies::addPts(Mat src, cv::Point start, cv::Point end, int height_of_lines, int y_pre_valley, int y_next_valley, vector<cv::Point>& pts)
{
	y_pre_valley = (y_pre_valley < start.y) ? y_pre_valley : start.y - 1;
	y_next_valley = (y_next_valley > start.y) ? y_next_valley : start.y + 1;
	//
	int x_max = 0;
	int y_max = 0;
	int x_min = src.cols;
	int y_min = src.rows;
	int x_line = 0;
	int x_line_end = 0;
	Obstructing* obstructing = new Obstructing();
	DrawDecision* drawDecision = new DrawDecision();

	obstructing->setSrc(src);
	obstructing->setHeightOfLines(height_of_lines);

	//Tiến hành lấy phần liên thông
	vector<cv::Point>* v_pts;
	if (start.x == end.x) {
		int start_y = (start.y < end.y) ? start.y : end.y;
		int end_y = (start.y > end.y) ? start.y : end.y;
		for (int i = start_y; i < end_y; i++) {
			obstructing->setX(start.x);
			obstructing->setY(i);
			if (obstructing->isCut()) {
				cout << "Kiem tra cat DOC........ " << start.x << ", " << start.y << endl;
				cout << "y pre valley = " << y_pre_valley << endl;
				cout << "y next valley = " << y_next_valley << endl;
				cout << "Bat dau cat tai x,y = " << start.x << ", " << i << endl;

				Mat rs = obstructing->obstructing(ALL, y_pre_valley, y_next_valley);
				x_max = obstructing->getXMax();
				y_max = obstructing->getYMax();
				x_min = obstructing->getXMin();
				y_min = obstructing->getYMin();

				//Tìm phần cắt cuối cùng
				int z = 0;
				for (z = y_max; z > i; z--) {
					obstructing->setX(start.x);
					obstructing->setY(z);
					if (obstructing->isCut()) {
						cout << "Ket thuc cat tai x,y = " << start.x << ", " << z << endl;
						break;
					}
				}

				Mat rsCrop = this->cropImage(rs, x_min - 1, y_min, x_max + 1, y_max);
				cv::line(rsCrop, cv::Point(0, 0), cv::Point(0, rsCrop.rows), Scalar(255, 255, 255));
				cv::line(rsCrop, cv::Point(rsCrop.cols - 1, 0), cv::Point(rsCrop.cols - 1, rsCrop.rows), Scalar(255, 255, 255));
				rsCrop = this->addRowBegin(rsCrop);
				rsCrop = this->addRowEnd(rsCrop);
				int y_u = obstructing->convert(obstructing->getYMin(), y_pre_valley, true);
				int y_d = obstructing->convert(obstructing->getYMax(), y_pre_valley, true);

				Node* X;
				ShortestPath* shortest = new ShortestPath(rsCrop);

				cout << "(x_start, y_start) " << start.x - x_min << ", " << i - y_u<< endl;
				cout << "(x_end, y_end) " << start.x - x_min << ", " << z + 1 - y_min<< endl;

				shortest->setX_start(start.x - x_min);
				shortest->setY_start(i - y_u);
				shortest->setX_goal(start.x - x_min);
				shortest->setY_goal(z + 1 - y_min);
				shortest->init();
				X = shortest->Astar();
				//Thêm
				v_pts = shortest->print(X, rsCrop, x_min - 1, y_u);
				pts.insert(pts.end(), v_pts->begin(), v_pts->end());

				//saving - nho xoa
				string savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/cat_lien_thong_doc_" + std::to_string(start.x) + "_" + std::to_string(i) + ".jpg";
				imwrite(savePath, rsCrop);
				//saving - nho xoa
				return -1;
			}//if
		}
	}//if (start.x == end.x) 
	else {
		for (int i = start.x; i < end.x; i++) {
			obstructing->setX(i);
			obstructing->setY(start.y);
			if (obstructing->isCut()) {
				cout << "Kiem tra.... " << start.x << ", " << start.y << endl;
				cout << "y pre valley = " << y_pre_valley << endl;
				cout << "y next valley = " << y_next_valley << endl;
				cout << "Bat dau cat tai x,y = " << i << ", " << start.y << endl;


				Mat rs = obstructing->obstructing(ALL, y_pre_valley, y_next_valley);
				x_max = obstructing->getXMax();
				y_max = obstructing->getYMax();
				x_min = obstructing->getXMin();
				y_min = obstructing->getYMin();

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

				Mat rsCrop = this->cropImage(rs, x_min - 1, y_min, x_max + 1, y_max);
				cv::line(rsCrop, cv::Point(0, 0), cv::Point(0, rsCrop.rows), Scalar(255, 255, 255));
				cv::line(rsCrop, cv::Point(rsCrop.cols - 1, 0), cv::Point(rsCrop.cols - 1, rsCrop.rows), Scalar(255, 255, 255));


				//Decision draw
				int y_u = obstructing->convert(obstructing->getYMin(), y_pre_valley, true);
				int y_d = obstructing->convert(obstructing->getYMax(), y_pre_valley, true);

				drawDecision->setYu(y_u);
				drawDecision->setYd(y_d);
				drawDecision->setYCurrValley(start.y);
				drawDecision->setYPreValley(y_pre_valley);
				drawDecision->setYNextValley(y_next_valley);
				Node* X;

				ShortestPath* shortest = new ShortestPath(rsCrop);
				switch (drawDecision->decision()) {
				case UP_UP:
					rsCrop = this->addRowBegin(rsCrop);
					shortest->setData(rsCrop);
					cout << "Ke len tren phan lien thong tren" << endl;
					//nho xoa
					cout << "(x_start, y_start) " << 0 << ", " << start.y - y_u + 1 << endl;
					cout << "(x_end, y_end) " << rsCrop.cols - 1 << ", " << start.y - y_u + 1 << endl;
					//nho xoa
					shortest->setX_start(0);
					shortest->setY_start(start.y - y_u + 1);
					shortest->setX_goal(rsCrop.cols - 1);
					shortest->setY_goal(start.y - y_u + 1);
					shortest->init();
					X = shortest->Astar();
					//Thêm
					v_pts = shortest->print(X, rsCrop, x_min - 1, y_u);
					//nho xoa
					cout << "v_pts size is " << v_pts->size() << endl;
					//nho xoa
					pts.insert(pts.end(), v_pts->begin(), v_pts->end());
					break;
				case DOWN_DOWN:
					cout << "Ke xuong duoi phan lien thong duoi" << endl;
					rsCrop = this->addRowEnd(rsCrop);
					shortest->setData(rsCrop);

					shortest->setX_start(0);
					shortest->setY_start(start.y - y_u);
					shortest->setX_goal(rsCrop.cols - 1);
					shortest->setY_goal(start.y - y_u);
					shortest->init();
					X = shortest->Astar();
					//Thêm
					v_pts = shortest->print(X, rsCrop, x_min - 1, y_u);
					//nho xoa
					cout << "v_pts size is " << v_pts->size() << endl;
					//nho xoa
					pts.insert(pts.end(), v_pts->begin(), v_pts->end());
					//pts.push_back(cv::Point(z + 2, start.y));
					//pts.push_back(cv::Point(x_max, start.y));

					//cv::line(src, cv::Point(z + 2, start.y), cv::Point(x_max, start.y), Scalar(200, 200, 200));
					break;
				case UP_DOWN:
				case THROUGH:
					cout << "Ke cat ngang" << endl;
					pts.push_back(cv::Point(i, start.y));
					pts.push_back(cv::Point(x_max, start.y));

					//cv::line(src, cv::Point(i, start.y), cv::Point(x_max, start.y), Scalar(200, 200, 200));
					break;
				}

				//saving - nho xoa
				string savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/cat_lien_thong_ngang_" + std::to_string(i) + "_" + std::to_string(start.y) + ".jpg";
				imwrite(savePath, rsCrop);
				//saving - nho xoa

				//Bắt đầu lặp từ phần cuối phần liên thông trước đó
				if (end.x > x_max) {
					i = x_max + 1;
					x_line = i;
				}
				else
					return 1;

			}//if
		}//for i
	}//else (start.x == end.x) 
	return 0;
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

void MatModifies::insert(vector<cv::Point>& line, vector<cv::Point> a_part_line, int flag)
{
	int size_a_part_line = a_part_line.size();
	int x_min_part_line = a_part_line.at(0).x;
	int x_max_part_line = a_part_line.at(size_a_part_line - 1).x;
	int y_min_part_line = a_part_line.at(0).y;
	int y_max_part_line = a_part_line.at(size_a_part_line - 1).y;
	for (std::vector<cv::Point>::iterator it = line.begin(); it != line.end(); ++it) {
		if (flag == 1 & it->x >= x_min_part_line & it->x <= x_max_part_line) {
			line.erase(it);
		}
		else if (flag == -1 & it->y >= y_min_part_line & it->y <= y_max_part_line & it->x >= x_min_part_line & it->x <= x_max_part_line) {
			line.erase(it);
		}
	}

	int size_line = line.size();
	for (vector<int>::size_type k = 0; k != size_line; k++) {
		if (flag == 1 & line.at(k).x > x_min_part_line) {
			line.insert(line.begin() + k, a_part_line.begin(), a_part_line.end());
			break;
		}
		else if (flag == -1 & line.at(k).x > x_min_part_line & line.at(k).y > y_min_part_line) {
			line.insert(line.begin() + k, a_part_line.begin(), a_part_line.end());
			break;
		}
	}
}
