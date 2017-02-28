#include "PreProcess.h"

void PreProcess::threshold(Mat src, Mat &dist, unsigned int threshold_val, unsigned int max_val, unsigned int threshold_type)
{
	cout << "- Thresholding filter;" << endl;
	cv::threshold(src, dist, threshold_val, max_val, threshold_type); // Threshold the Image using the value obtained from OTSU method

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	//erode(dist, dist, element);
	//dilate(dist, dist, element);
}

void PreProcess::gaussianBlur(Mat src, Mat &dist, unsigned int kernel_size)
{
	cout << "- Gaussian filter;" << endl;
	cv::GaussianBlur(src, dist, cv::Size(kernel_size, kernel_size), 0, 0, BORDER_DEFAULT);
}

void PreProcess::averageBlur(Mat src, Mat &dist, unsigned int kernel_size)
{
	cout << "- Average filter;" << endl;
	cv::blur(src, dist, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));
}

void PreProcess::medianBlur(Mat src, Mat &dist, unsigned int kernel_size)
{
	cout << "- Median filter;" << endl;
	cv::medianBlur(src, dist, kernel_size);
}

void PreProcess::adaptiveMedian(Mat src, Mat &dist, unsigned int Smax)
{
	cout << "- Adaptive Median filter;" << endl;
	unsigned int Smin = 3, Zmin, Zmax, Zmed, Zxy;
	unsigned int windowSize = Smin;
	int A1, A2, B1, B2;
	int* mask;
	unsigned int width = src.cols, height = src.rows;
	Scalar intensity;
	int val;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			windowSize = Smin;
			mask = (int*)calloc(windowSize * windowSize - 1, sizeof(int));
			//Init all val -1
			for (int h = 0; h < windowSize * windowSize - 1; h++)
				*(mask + h) = INIT_VAL;

			intensity = src.at<uchar>(j, i);
			Zxy = intensity[0];

			while (windowSize <= Smax) {
				int mid = floor(windowSize / 2);
				for (int k = -mid; k <= mid; k++) {
					for (int z = -mid; z <= mid; z++) {
						if (abs(z) == mid | abs(k) == mid) {
							if (k == 0 & z == 0) continue;
							if ((j + k >= 0 & j + k < height) & (i + z >= 0 & i + z < width)) {
								intensity = src.at<uchar>(j + k, i + z);
								val = intensity[0];
							}
							else
								val = 255;
							this->addElement(mask, val, windowSize * windowSize - 1);
						}
					}//for z
				}//for k
				 //Zmin, Zmax, Zmed
				Zmin = *(mask);
				int mid_id = floor(((windowSize * windowSize) - 2) / 2);
				Zmed = (*(mask + mid_id) + *(mask + mid_id + 1)) / 2;
				Zmax = *(mask + (windowSize * windowSize - 2));
				//Xử lý 2 bước
				A1 = Zmed - Zmin;
				A2 = Zmed - Zmax;
				if (A1 > 0 & A2 < 0) {
					B1 = Zxy - Zmin;
					B2 = Zxy - Zmax;
					if (B1 <= 0 || B2 >= 0)
						dist.at<uchar>(j, i) = Zmed;
					break;
				}
				else {
					windowSize += 2;
					mask = (int*)realloc(mask, (windowSize * windowSize - 1) * sizeof(int));
					int min = (windowSize - 1) * 4;
					for (int h = windowSize * windowSize - 1 - min; h < windowSize * windowSize - 1; h++)
						*(mask + h) = INIT_VAL;
				}
			}//while

			delete[] mask;//delete all vals
		}//for j
	}//for i 
}

void PreProcess::addElement(int *arr, int element, unsigned int length)
{
	for (int i = 0; i < length; i++) {
		if (*(arr + i) > element) {
			for (int j = length - 1; j > i; j--)
				*(arr + j) = *(arr + j - 1);
			*(arr + i) = element;
			break;
		}
		else if (*(arr + i) < 0) {
			*(arr + i) = element;
			break;
		}
	}
}

void PreProcess::laplacian(Mat src, Mat &dist, unsigned int kernel_size, int ddepth, int scale, int delta)
{
	cout << "- Laplacian filter;" << endl;
	cv::Laplacian(src, dist, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
}

void PreProcess::adaptive(Mat src, Mat &dist, bool adaptiveMethod, bool thresholdType, unsigned int blockSize, unsigned int C)
{
	cout << "- Adaptive thresholding filter;" << endl;
	int MAX_VALUE = 255;
	cv::adaptiveThreshold(src, dist, MAX_VALUE, (adaptiveMethod ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C), (thresholdType ? THRESH_BINARY_INV : THRESH_BINARY), blockSize, C);
}

void PreProcess::Morphology_Operations(Mat src, Mat &dist, int morph_operator, int morph_elem, int morph_size)
{
	cout << "- Morphology Operations;" << endl;
	// Since MORPH_X : 2,3,4,5 and 6
	int operation = morph_operator;
	Mat element = getStructuringElement(morph_elem, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));

	// Apply the specified morphology operation
	morphologyEx(src, dist, operation, element);
	if (morph_operator == MORPH_GRADIENT) {

		// initialize the output matrix with zeros
		Mat new_image = Mat::zeros(dist.size(), dist.type());

		// create a matrix with all elements equal to 255 for subtraction
		Mat sub_mat = Mat::ones(dist.size(), dist.type()) * 255;

		//subtract the original matrix by sub_mat to give the negative output new_image
		subtract(sub_mat, dist, dist);
	}
}