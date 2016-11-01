#include "Noise.h"

Noise::Noise(Mat image)
{
	this->image = image.clone();
}

void Noise::Salt(int n)
{
	int i, j;
	unsigned int total = image.cols * image.rows * n/100;
	for (int k = 0; k < total/2; k++) {
		//Rand(is) the random / number generator
		i = std::rand() % this->image.cols; // % divisible mod operator, rand = 1022, cols = 1000, rand%cols = 22
		j = std::rand() % this->image.rows;

		if (this->image.type() == CV_8UC1) {
			// gray - level image
			this->image.at<uchar>(j, i) = 255; //at method needs to specify the return value of the Mat variable, such as uchar, etc.  
		}
		else if (this->image.type() == CV_8UC3) {
			// color image
			this->image.at<cv::Vec3b>(j, i)[0] = 255; //cv:: Vec3b for the opencv definition of a 3 value of vector type  
			this->image.at<cv::Vec3b>(j, i)[1] = 255; //[]; B:0, G:1, specified channel, R:2  
			this->image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}

void Noise::Pepper(int n)
{
	int i, j;
	unsigned int total = image.cols * image.rows * n / 100;
	for (int k = 0; k < total/2; k++) {
		//Rand(is) the random / number generator
		i = std::rand() % this->image.cols; // % divisible mod operator, rand = 1022, cols = 1000, rand%cols = 22
		j = std::rand() % this->image.rows;

		if (this->image.type() == CV_8UC1) {
			// gray - level image
			this->image.at<uchar>(j, i) = 0; //at method needs to specify the return value of the Mat variable, such as uchar, etc.  
		}
		else if (this->image.type() == CV_8UC3) {
				// color image
				this->image.at<cv::Vec3b>(j, i)[0] = 0; //cv:: Vec3b for the opencv definition of a 3 value of vector type  
				this->image.at<cv::Vec3b>(j, i)[1] = 0; //[]; B:0, G:1, specified channel, R:2  
				this->image.at<cv::Vec3b>(j, i)[2] = 0;
		}
	}
}

void Noise::setImage(Mat image)
{
	this->image = image.clone();
}

Mat Noise::getImage()
{
	return this->image;
}
