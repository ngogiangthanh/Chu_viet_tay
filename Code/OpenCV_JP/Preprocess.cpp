#include "Preprocess.h"

Preprocess::Preprocess(Mat src)
{
	this->src = src.clone();
	this->dist = src.clone();
}

Preprocess::Preprocess(Mat src, Mat dist)
{
	this->src = src.clone();
	this->dist = dist.clone();
}

void Preprocess::threshold(unsigned int threshold_val, unsigned int max_val, unsigned int threshold_type)
{
	cout << "- Thresholding filter;" << endl;
	cv::threshold(this->src, this->dist, threshold_val, max_val, threshold_type);
}

void Preprocess::gaussianBlur(unsigned int kernel_size)
{
	cout << "- Gaussian filter;" << endl;
	cv::GaussianBlur(this->src, this->dist, cv::Size(kernel_size, kernel_size), 0, 0, BORDER_DEFAULT);
}

void Preprocess::averageBlur(unsigned int kernel_size)
{
	cout << "- Average filter;" << endl;
	cv::blur(this->src, this->dist, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));

}

void Preprocess::medianBlur(unsigned int kernel_size)
{
	cout << "- Median filter;" << endl;
	cv::medianBlur(this->src, this->dist, kernel_size);
}

void Preprocess::laplacian(unsigned int kernel_size, int ddepth, int scale, int delta)
{
	cout << "- Laplacian filter;" << endl;
	cv::Laplacian(this->src, this->dist, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
}

void Preprocess::adaptive(bool adaptiveMethod, bool thresholdType, unsigned int blockSize, unsigned int C)
{
	int MAX_VALUE = 255;
	cv::adaptiveThreshold(this->src, this->dist, MAX_VALUE, (adaptiveMethod ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C), (thresholdType ? THRESH_BINARY_INV : THRESH_BINARY), blockSize, C);
}

void Preprocess::Morphology_Operations(int morph_operator, int morph_elem, int morph_size)
{
	// Since MORPH_X : 2,3,4,5 and 6
	int operation = morph_operator;
	Mat element = getStructuringElement(morph_elem, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));

	// Apply the specified morphology operation
	morphologyEx(this->src, this->dist, operation, element);
}

void Preprocess::setSrc(Mat src)
{
	this->src = src.clone();
}

void Preprocess::setDist(Mat dist)
{
	this->dist = dist.clone();
}

Mat Preprocess::getSrc()
{
	return this->src;
}

Mat Preprocess::getDist()
{
	return this->dist;
}
