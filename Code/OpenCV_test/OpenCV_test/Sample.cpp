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

void readme();

int main( int argc, char** argv )
{
	Mat src;

	src = imread("D:\\test.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//Mat copy = src.clone();
	//src.convertTo(src, CV_8UC1);
	//Obstructing* obstructing = new Obstructing();
	//obstructing->setSrc(src);
	//obstructing->setX(54);
	//obstructing->setY(97);
	//int y_min = 19;
	//int y_max = 127;
	//Mat rs = obstructing->obstructing(ALL, y_min, y_max);
	//cv::Rect crop(obstructing->getXMin(), obstructing->getYMin(), obstructing->getXMax() - obstructing->getXMin(), obstructing->getYMax() - obstructing->getYMin());
	//Mat imageUpSource = rs(crop);

	//int y_min_0 = obstructing->convert(obstructing->getYMin(), y_min, true);
	//int y_max_0 = obstructing->convert(obstructing->getYMax(), y_min, true);

	//cv::line(copy, cv::Point(0, y_min), cv::Point(copy.cols, y_min), Scalar(128, 0, 0));
	//cv::line(copy, cv::Point(0, y_max), cv::Point(copy.cols, y_max), Scalar(128, 0, 0));
	//cv::line(copy, cv::Point(obstructing->getXMin(), y_min_0), cv::Point(obstructing->getXMax(), y_min_0), Scalar(128, 0, 0));
	//cv::line(copy, cv::Point(obstructing->getXMax(), y_min_0), cv::Point(obstructing->getXMax(), y_max_0), Scalar(128, 0, 0));
	//cv::line(copy, cv::Point(obstructing->getXMax(), y_max_0), cv::Point(obstructing->getXMin(), y_max_0), Scalar(128, 0, 0));
	//cv::line(copy, cv::Point(obstructing->getXMin(), y_max_0), cv::Point(obstructing->getXMin(), y_min_0), Scalar(128, 0, 0));
	//imwrite("D:\\rs.jpg", imageUpSource);
	//imwrite("D:\\rs_1.jpg", copy);
	//cout << "test" << endl;
	//system("pause");


	imshow("Ảnh gốc", src);

	cv::Size size = src.size();
	//Các thông số dòng giả lập
	int x_start = 54;
	int y_start = 79;
	int x_end = 218;
	int y_end = 79;
	int y_pre_valley = 1;
	int y_next_valley = 170;
	int x_line = 0;
	int x_line_end = 0;
	//cv::line(src, cv::Point(0, y_pre_valley), cv::Point(288, y_pre_valley), Scalar(0, 0, 0));
	//cv::line(src, cv::Point(0, y_next_valley), cv::Point(288, y_next_valley), Scalar(0, 0, 0));
	//Khởi tạo các biến cần thiết
	int x_max = 0;
	int y_max = 0;
	int x_min = size.width;
	int y_min = size.height;
	Obstructing* obstructing = new Obstructing();
	DrawDecision* drawDecision = new DrawDecision();
	ShortestPath* shortest = new ShortestPath(src);
	MatModifies* matModifies = new MatModifies();
	obstructing->setSrc(src);

	vector<cv::Point>* pts = new vector<cv::Point>();
	vector<cv::Point>* v_pts;

	//Tiến hành lấy phần liên thông
	for (int i = x_start; i < x_end; i++) {

			obstructing->setX(i);
			obstructing->setY(y_start);
			if(obstructing->isCut()){
				x_line_end = i;
				//Thêm
				pts->push_back(cv::Point(x_line, y_start));
				pts->push_back(cv::Point(x_line_end, y_start));
			//	cv::line(src, cv::Point(x_line, y_start), cv::Point(x_line_end, y_start), Scalar(200, 200, 200));

				//Lấy kết quả phần liên thông
				Mat rs = obstructing->obstructing(ALL, y_pre_valley, y_next_valley);
				x_max = obstructing->getXMax();
				y_max = obstructing->getYMax();
				x_min = obstructing->getXMin();
				y_min = obstructing->getYMin();

				y_min = obstructing->convert(obstructing->getYMin(), y_pre_valley, true);
				y_max = obstructing->convert(obstructing->getYMax(), y_pre_valley, true);

				//Cắt phần liên thông và lưu

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

				//cout << " x_min - 1, y_min" << x_min - 1 << ", " << y_min << endl;
				//cout << " x_max + 2, y_max" << x_max + 2 << ", " << y_max << endl;
				Mat rsCrop = matModifies->cropImage(src, x_min - 1, y_min, x_max + 2, y_max);
				//cout << "cat xong rs crop" << endl;

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

						shortest->setX_start(i);
						shortest->setY_start(y_start);
						shortest->setX_goal(z + 2);
						shortest->setY_goal(y_start);
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

						shortest->setX_start(i);
						shortest->setY_start(y_start);
						shortest->setX_goal(z + 2);
						shortest->setY_goal(y_start);
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
						//Thêm

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

	pts->push_back(cv::Point(size.width, 0));
	pts->push_back(cv::Point(size.width / 2, 10));
	pts->push_back(cv::Point(0, 0));
	Mat rs = matModifies->cut(src, pts);

	savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/line_cut.jpg";
	imwrite(savePath, rs);
	

	waitKey(0);
	return 0;
  }

  /** @function readme */
  void readme()
  { std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl; }