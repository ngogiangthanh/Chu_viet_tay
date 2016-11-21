#include <stdio.h>
#include <iostream>
#include <queue>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "Obstructing.h"
#include "DrawDecision.h"
#include "ShortestPath.h"
#include "MatModifies.h"

using namespace cv;

int main( int argc, char** argv )
{
	Mat src;

	src = imread("D:\\test.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	int x_start = 0;
	int y_start = 84;
	int x_end = 218;
	int y_end = 84;
	int y_pre_valley = 1;
	int y_next_valley = 170;
	int x_line = 0;
	int x_line_end = 0;
	int x_max = 0;
	int y_max = 0;
	int x_min = src.cols;
	int y_min = src.rows;
	Obstructing* obstructing = new Obstructing();
	DrawDecision* drawDecision = new DrawDecision();
	ShortestPath* shortest = new ShortestPath(src);
	MatModifies* matModifies = new MatModifies();

	obstructing->setSrc(src);

	vector<cv::Point>* pts = new vector<cv::Point>();
	vector<cv::Point>* v_pts;

	for (int i = start.x; i < end.x; i++) {

		obstructing->setX(i);
		obstructing->setY(start.y);
		if (obstructing->isCut()) {
			cout << "Kiem tra.... " << start.x << ", " << start.y << endl;
			cout << "y pre valley = " << y_pre_valley << endl;
			cout << "y next valley = " << y_next_valley << endl;
			cout << "Bat dau cat tai x,y = " << i << ", " << start.y << endl;
			//x_line_end = i;

			//pts.push_back(cv::Point(i, start.y));
			//pts.push_back(cv::Point(x_line_end, start.y));

			Mat rs = obstructing->obstructing(ALL, y_pre_valley, y_next_valley);
			x_max = obstructing->getXMax();
			y_max = obstructing->getYMax();
			x_min = obstructing->getXMin();
			y_min = obstructing->getYMin();

			//y_min = obstructing->convert(obstructing->getYMin(), y_pre_valley, true);
			//y_max = obstructing->convert(obstructing->getYMax(), y_pre_valley, true);

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

			//saving - nho xoa
			string savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/cat_lien_thong_" + std::to_string(i) + "_" + std::to_string(start.y) + ".jpg";
			imwrite(savePath, rsCrop);
			numLine++;
			//saving - nho xoa

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
				//nho xoa
				cout << "v_pts size is " << v_pts->size() << endl;
				//nho xoa
				pts.insert(pts.end(), v_pts->begin(), v_pts->end());
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

			//Bắt đầu lặp từ phần cuối phần liên thông trước đó
			if (end.x > x_max) {
				i = x_max + 1;
				x_line = i;
			}
			else
				break;
		}//if
	}//for i

	string savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/line.jpg";
	imwrite(savePath, src);

	//pts->push_back(cv::Point(size.width, 0));
	pts->push_back(cv::Point(x_max + 1, y_pre_valley));
	pts->push_back(cv::Point(x_min - 1, y_pre_valley));
	Mat rs = matModifies->cut(src, pts);

	savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/line_cut.jpg";
	imwrite(savePath, rs);

	waitKey(0);
	return 0;
  }