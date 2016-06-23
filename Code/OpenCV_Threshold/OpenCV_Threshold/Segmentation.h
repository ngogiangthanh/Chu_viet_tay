//Yêu cầu src đã được tiền xử lý - Phân ngưỡng trắng đen trước đó
#pragma once
#ifndef Segmentation_H
#define Segmentation_H
#define THRESHOLDING 200
#define NUMBER_OF_COLUMNS 20
#include "iostream"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <array>
#include "Column.h"

using namespace cv;
using namespace std;
class Segmentation
{
	private:
		Mat src;
		Mat dist;
		unsigned int height, width;
		Element* elements;
		int width_size;
		int heigh_of_line;
	public:
		Segmentation(Mat);
		//Chuẩn hóa kích thước cho phù hợp với NUMBER_OF_COLUMNS
		void normalized();
		//Khởi tạo ảnh và mapping vào Cấu Trúc Dữ Liệu
		void init();
		//Khữ nhiễu thung lũng và đỉnh bằng cách tính MAF bộ chập 5 phần tử
		void movingAverageFilter();
		//Tìm thung lũng
		void findValley();
		//Kết nối các thung lũng giữa các cột với nhau
		void connectValley();
		//Tính độ lệch chuẩn
		bool standardDeviation(long, int);
		//Khoảng cách
		double distance(int, int, int, int);
		//
		bool isPunctuationMarkValley(int, int);
		void setSrc(Mat);
		void setDist(Mat);
		void setHeight(unsigned int);
		void setWidth(unsigned int);
		void setHeighOfLine(int);
		Mat getSrc();
		Mat getDist();
		unsigned int getHeight();
		unsigned int getWidth();
		int getHeighOfLine();
};
#endif
