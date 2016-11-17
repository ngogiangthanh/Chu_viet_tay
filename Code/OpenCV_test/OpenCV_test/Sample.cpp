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

	for (int i = x_start; i < x_end; i++) {
			obstructing->setX(i);
			obstructing->setY(y_start);
			if(obstructing->isCut()){
				x_line_end = i;

				pts->push_back(cv::Point(x_line, y_start));
				pts->push_back(cv::Point(x_line_end, y_start));
		
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
					obstructing->setY(y_start);
					if (obstructing->isCut()) {
						cout << "Ket thuc cat tai x,y = " << z << ", " << y_start << endl;
						break;
					}
				}

				Mat rsCrop = matModifies->cropImage(src, x_min - 1, y_min, x_max + 1, y_max);
				cv::line(rsCrop, cv::Point(0, 0), cv::Point(0, rsCrop.rows), Scalar(255, 255, 255));
				cv::line(rsCrop, cv::Point(rsCrop.cols - 1, 0), cv::Point(rsCrop.cols - 1, rsCrop.rows), Scalar(255, 255, 255));

				//Decision draw
				drawDecision->setYu(y_min);
				drawDecision->setYd(y_max);
				drawDecision->setYCurrValley(y_start);
				drawDecision->setYPreValley(y_pre_valley);
				drawDecision->setYNextValley(y_next_valley);
				Node* X;

				switch (drawDecision->decision()) {
					case UP_UP:
						rsCrop = matModifies->addRowBegin(rsCrop);

						cout << "Ke len tren phan lien thong tren" << endl;
						shortest  = new ShortestPath(rsCrop);

						shortest->setX_start(i - x_min - 2);
						shortest->setY_start(y_start - y_min);
						shortest->setX_goal(z - x_min + 2);
						shortest->setY_goal(y_start - y_min);
						shortest->init();
						X = shortest->Astar();
						//Thêm
						v_pts = shortest->print(X, src, x_min, y_min);
						pts->insert(pts->end(), v_pts->begin(), v_pts->end());
						break;
					case DOWN_DOWN:
						cout << "Ke xuong duoi phan lien thong duoi" << endl;
						rsCrop = matModifies->addRowEnd(rsCrop);
						shortest = new ShortestPath(rsCrop);

						shortest->setX_start(i - x_min - 2);
						shortest->setY_start(y_start - y_min);
						shortest->setX_goal(z - x_min + 2);
						shortest->setY_goal(y_start - y_min);
						shortest->init();
						X = shortest->Astar();
						//Thêm
						v_pts = shortest->print(X, src, x_min, y_min);
						pts->insert(pts->end(), v_pts->begin(), v_pts->end());
						pts->push_back(cv::Point(z + 2, y_start));
						pts->push_back(cv::Point(x_max, y_start));

						cv::line(src, cv::Point(z + 2, y_start), cv::Point(x_max, y_start), Scalar(200, 200, 200));
						break;
					case UP_DOWN:
					case THROUGH:
						cout << "Ke cat ngang" << endl; 
						pts->push_back(cv::Point(i, y_start));
						pts->push_back(cv::Point(x_max, y_start));

						cv::line(src, cv::Point(i, y_start), cv::Point(x_max, y_start), Scalar(200, 200, 200));
						break;
				}

				//Bắt đầu lặp từ phần cuối phần liên thông trước đó
				if (x_end > x_max) {
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