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
	src.convertTo(src, CV_8UC1);
	Obstructing* obstructing = new Obstructing();
	obstructing->setSrc(src);
	obstructing->setX(54);
	obstructing->setY(97);
	int y_min = 19;
	int y_max = 127;
	Mat rs = obstructing->obstructing(2, y_min, y_max);
	cv::Rect crop(obstructing->getXMin(), obstructing->getYMin(), obstructing->getXMax() - obstructing->getXMin(), obstructing->getYMax() - obstructing->getYMin());
	Mat imageUpSource = rs(crop);
	imwrite("D:\\rs.jpg", imageUpSource);
	cout << "test" << endl;
	system("pause");


	//imshow("Ảnh gốc", src);

	//cv::Size size = src.size();
	//Các thông số dòng giả lập
	//int x_start = 0;
	//int y_start = 114;
	//int x_end = 426;
	//int y_end = 114;
	//int y_pre_valley = 40;
	//int y_next_valley = 180;
	//int x_line = 0;
	//int x_line_end = 0;
	//cv::line(src, cv::Point(0, y_pre_valley), cv::Point(433, y_pre_valley), Scalar(0, 0, 0));
	//cv::line(src, cv::Point(0, y_next_valley), cv::Point(433, y_next_valley), Scalar(0, 0, 0));
	////Khởi tạo các biến cần thiết
	//int x_max = 0;
	//int y_max = 0;
	//int x_min = size.width;
	//int y_min = size.height;
	//Obstructing* obstructing = new Obstructing();
	//DrawDecision* drawDecision = new DrawDecision();
	//ShortestPath* shortest = new ShortestPath(src);
	//MatModifies* matModifies = new MatModifies();
	//obstructing->setSrc(src);

	//vector<cv::Point>* pts = new vector<cv::Point>();
	//vector<cv::Point>* v_pts;

	////Tiến hành lấy phần liên thông
	//for (int i = x_start; i < x_end; i++) {

	//		obstructing->setX(i);
	//		obstructing->setY(y_start);
	//		if(obstructing->isCut()){
	//			x_line_end = i;
	//			//Thêm
	//			pts->push_back(cv::Point(x_line, y_start));
	//			pts->push_back(cv::Point(x_line_end, y_start));
	//			cv::line(src, cv::Point(x_line, y_start), cv::Point(x_line_end, y_start), Scalar(200, 200, 200));

	//			//Lấy kết quả phần liên thông
	//			Mat rs = obstructing->obstructing(ALL);
	//			x_max = obstructing->getXMax();
	//			y_max = obstructing->getYMax();
	//			x_min = obstructing->getXMin();
	//			y_min = obstructing->getYMin();
	//			//Cắt phần liên thông và lưu
	//			Mat rsCrop = matModifies->cropImage(rs, x_min - 1, y_min, x_max + 2, y_max); 
	//		

	//			//Tìm phần cắt cuối cùng
	//			int z = 0;
	//			for (z = x_max; z > i; z--) {
	//				obstructing->setX(z);
	//				obstructing->setY(y_start);
	//				if (obstructing->isCut()) {
	//					break;
	//				}
	//			}

	//			//Decision draw
	//			drawDecision->setYu(y_min);
	//			drawDecision->setYd(y_max);
	//			drawDecision->setYCurrValley(y_start);
	//			drawDecision->setYPreValley(y_pre_valley);
	//			drawDecision->setYNextValley(y_next_valley);
	//			Node* X;
	//			switch (drawDecision->decision()) {
	//				case UP_UP:
	//					rsCrop = matModifies->addRowBegin(rsCrop);

	//					cout << "Ke len tren phan lien thong tren" << endl;
	//					shortest  = new ShortestPath(rsCrop);

	//					shortest->setX_start(i - x_min);
	//					shortest->setY_start(y_start - y_min);
	//					shortest->setX_goal(x_max + 2 - x_min);
	//					shortest->setY_goal(y_start - y_min);
	//					shortest->init();
	//					X = shortest->Astar();
	//					//Thêm
	//					v_pts = shortest->print(X, src, x_min, y_min);
	//					pts->insert(pts->end(), v_pts->begin(), v_pts->end());
	//					break;
	//				case DOWN_DOWN:
	//					cout << "Ke xuong duoi phan lien thong duoi" << endl;
	//					rsCrop = matModifies->addRowEnd(rsCrop);
	//					shortest = new ShortestPath(rsCrop);

	//					shortest->setX_start(i - x_min - 1);
	//					shortest->setY_start(y_start - y_min);
	//					shortest->setX_goal(z + 2 - x_min);
	//					shortest->setY_goal(y_start - y_min);
	//					shortest->init();
	//					X = shortest->Astar();
	//					//Thêm
	//					v_pts = shortest->print(X, src, x_min, y_min);
	//					pts->insert(pts->end(), v_pts->begin(), v_pts->end());
	//					pts->push_back(cv::Point(z + 2, y_start));
	//					pts->push_back(cv::Point(x_max, y_start));

	//					cv::line(src, cv::Point(z + 2, y_start), cv::Point(x_max, y_start), Scalar(200, 200, 200));
	//					break;
	//				case UP_DOWN:
	//				case THROUGH:
	//					cout << "Ke cat ngang" << endl; 
	//					//Thêm

	//					pts->push_back(cv::Point(i, y_start));
	//					pts->push_back(cv::Point(x_max, y_start));

	//					cv::line(src, cv::Point(i, y_start), cv::Point(x_max, y_start), Scalar(200, 200, 200));
	//					break;
	//			}

	//			//Bắt đầu lặp từ phần cuối phần liên thông trước đó
	//			if (x_end > x_max) {
	//				i = x_max + 1;
	//				x_line = i;
	//			}
	//			else 
	//				break;
	//		}//if
	//}//for i

	//string savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/line.jpg";
	//imwrite(savePath, src);

	//pts->push_back(cv::Point(size.width, 0));
	//pts->push_back(cv::Point(size.width / 2, 10));
	//pts->push_back(cv::Point(0, 0));
	//Mat rs = matModifies->cut(src, pts);

	//savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/line_cut.jpg";
	//imwrite(savePath, rs);
	

	waitKey(0);
	return 0;
  }

  /** @function readme */
  void readme()
  { std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl; }