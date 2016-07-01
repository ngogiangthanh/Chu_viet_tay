#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "Obstructing.h"

using namespace cv;

void readme();

/** @function main */
int main( int argc, char** argv )
{
	cout << "test" << endl;
	Mat src;

	src = imread("D:\\line.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	src.convertTo(src, CV_8UC1);

	imshow("Ảnh gốc", src);

	cv::Size size = src.size();

	int x_start = 0;
	int y_start = 77;
	int x_corner = 426;
	int y_corner = 77;
	int x_end = 426;
	int y_end = 57;
	int pixel = 255;
	int THRESHOLDING = 0;


	int x_max = 0;
	int y_max = 0;
	int x_min = size.width;
	int y_min = size.height;
	Obstructing* obstructing = new Obstructing();
	obstructing->setSrc(src);

	for (int i = x_start; i < x_corner; i++) {
			obstructing->setX(i);
			obstructing->setY(y_start);
			if(obstructing->isCut()){
				cout << "bat dau cat tai = "<< i << endl;
				Mat rs = obstructing->obstructing(ALL);

				x_max = obstructing->getXMax();
				y_max = obstructing->getYMax();
				x_min = obstructing->getXMin();
				y_min = obstructing->getYMin();

				for (int z = x_max; z > i; z--) {
					obstructing->setX(z);
					obstructing->setY(y_start);
					if (obstructing->isCut()) {
						cout << "ket thuc cat tai = " << z << endl;
						break;
					}
				}

				cv::Rect crop(x_min, y_min, x_max - x_min, y_max - y_min);
				string savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/" + to_string(i) + "_" + to_string(y_start) + ".jpg";
				imwrite(savePath, rs(crop));
				if (x_corner > x_max) {
					cout << "cat trong vung xmax=" << x_max << endl;
					i = x_max + 1;
				}
				else {
					cout << "Het " << endl;
					break;
				}
				cout << endl;
			}
	}//for i

	waitKey(0);

	return 0;
  }

  /** @function readme */
  void readme()
  { std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl; }