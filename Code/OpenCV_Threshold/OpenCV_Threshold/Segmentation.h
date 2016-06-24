//Yêu cầu src đã được tiền xử lý - Phân ngưỡng trắng đen trước đó
#pragma once
#ifndef Segmentation_H
#define Segmentation_H
#define THRESHOLDING 200
#define NUMBER_OF_COLUMNS 20
#define MIN_PROBABILITY 0.4
#define AVG_PROBABILITY 0.6
#define MAX_PROBABILITY 0.7
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
		bool setConnect(long, int);
		//Khoảng cách a half of Manhattan
		double distance(int, int);
		//Kiểm tra thung lũng này có phải là thung lũng trên dấu
		bool isPunctuationMarkValley(int, int);
		//Vẽ thung lũng lên hình
		void drawValleys();
		//Vẽ kết nối
		void drawConnects(cv::Point, cv::Point, cv::Point);

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
