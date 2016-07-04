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
#include "Elements.h"

using namespace cv;

void readme();

int main( int argc, char** argv )
{
	cout << "test" << endl;
	Mat src;

	src = imread("D:\\line.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	src.convertTo(src, CV_8UC1);

	//imshow("Ảnh gốc", src);

	cv::Size size = src.size();
	////Các thông số dòng giả lập
	//Elements* line_pre = new Elements();
	//Elements* line_cur = new Elements();
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

	////Tiến hành lấy phần liên thông
	//for (int i = x_start; i < x_end; i++) {

	//		obstructing->setX(i);
	//		obstructing->setY(y_start);
	//		if(obstructing->isCut()){
	//			x_line_end = i;
	//			Element* element_pre = new Element(x_line, y_start);
	//			element_pre->setNext(true);
	//			Element* element_next = new Element(x_line_end, y_start);
	//			element_next->setPre(true);
	//			line_cur->add(element_pre);
	//			line_cur->add(element_next);

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
	//					line_cur->combine(shortest->print(X, src, x_min, y_min));
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
	//					line_cur->combine(shortest->print(X, src, x_min, y_min));

	//					element_pre = new Element(z + 2, y_start);
	//					element_pre->setNext(true);
	//					element_next = new Element(x_max, y_start);
	//					element_next->setPre(true);
	//					line_cur->add(element_pre);
	//					line_cur->add(element_next);

	//					cv::line(src, cv::Point(z + 2, y_start), cv::Point(x_max, y_start), Scalar(200, 200, 200));
	//					break;
	//				case UP_DOWN:
	//				case THROUGH:
	//					cout << "Ke cat ngang" << endl; 
	//					element_pre = new Element(i, y_start);
	//					element_pre->setNext(true);
	//					element_next = new Element(x_max, y_start);
	//					element_next->setPre(true);
	//					line_cur->add(element_pre);
	//					line_cur->add(element_next);

	//					cv::line(src, cv::Point(i, y_start), cv::Point(z + 2, y_start), Scalar(200, 200, 200));
	//					cv::line(src, cv::Point(z + 2, y_start), cv::Point(x_max, y_start), Scalar(200, 200, 200));
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

	//Mat rs = matModifies->cut(src, line_pre, line_cur);

	// savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/line_cut.jpg";
	//imwrite(savePath, rs);
	//
	//vector<Element*> el = line_cur->getElements();
	//int s = el.size();

	//for (vector<int>::size_type m = 0; m != s; m++) {
	//	cout << el[m]->getX() << "," << el[m]->getY() << "|next="<< el[m]->isNext() << "|pre=" << el[m]->isPre() << endl;
	//}

	vector<Point> pts(9);
	pts[0] = Point(26,26);
	pts[1] = Point(14, 147);
	pts[2] = Point(103, 166);
	pts[3] = Point(91, 117);
	pts[4] = Point(203, 128);
	pts[5] = Point(369, 149);
	pts[6] = Point(421, 115);
	pts[7] = Point(359, 28);
	pts[8] = Point(198, 38);


	const Point* elementPoints[1] = { &pts[0] };
	int numPoints = (int)pts.size();
	Mat mMask = Mat(size, CV_8UC1, Scalar(0, 0, 0));
	fillPoly(mMask, elementPoints, &numPoints, 1, Scalar(255, 255,255));
	imshow("mMask", mMask);

	Mat Destination;
	src.copyTo(Destination, mMask);
	imshow("Destination", Destination);


	 mMask = Mat(size, CV_8UC1, Scalar(255, 255, 255));
	fillPoly(mMask, elementPoints, &numPoints, 1, Scalar(0, 0, 0));

	bitwise_xor(mMask, Destination, Destination);
	imshow("Destination", Destination);

	waitKey(0);
	return 0;
  }

  /** @function readme */
  void readme()
  { std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl; }