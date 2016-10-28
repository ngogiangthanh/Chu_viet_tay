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

void Preprocess::adaptiveMedian(unsigned int Smax)
{
	unsigned int Smin = 3,Zmin = 255, Zmax = 0, Zmed, Zxy;
	unsigned int windowSize = Smin;
	int A1, A2, B1, B2;
	int* mask = (int*)calloc(Smin * Smin - 1, sizeof(int));
	//Init all val -1
	memset(mask, -1, (Smin * Smin - 1) * sizeof(int));
	Size size = this->src.size();
	unsigned int width = size.width,height = size.height;
	bool isFirst = true;
	Scalar intensity;
	int val;
	cout << "width =" << width << " height = " << height << endl;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			windowSize = Smin;
			while (windowSize < Smax) {
				int mid = floor(windowSize / 2);
				for (int k = -mid; k <= mid; k++) {
					for (int z = -mid; z <= mid; z++) {
						if (k == 0 && z == 0) continue;
						if (abs(z) == mid | abs(k) == mid) {//không phải lần đầu
							//Lấy giá trị ra
							intensity = this->src.at<uchar>((j + k < 0 | j + k >= height) ? j : j + k, (i + z < 0 | i + z >= width) ? i : i + z);
							val = intensity[0];
							//Gán vào mảng có thứ tự từ bé đến lớn.
							this->addElement(mask, val, windowSize * windowSize - 1);
							
						}
						else if (isFirst & abs(z) != mid & abs(k) != mid) {//Nếu đây là lần đầu thì duyệt toàn bộ
							//Lấy giá trị gán vào mảng
							intensity = this->src.at<uchar>((j + k < 0 | j + k >= height) ? j : j + k, (i + z < 0 | i + z >= width) ? i : i + z);
							val = intensity[0];
							//Gán vào mảng có thứ tự từ bé đến lớn.
							this->addElement(mask, val, windowSize * windowSize - 1);
							isFirst = false;
						}
					}//for z
				}//for k
					//Lấy giá trị Zmin, Zmax, Zmed, Zxy
					intensity = this->src.at<uchar>(j, i);
					Zxy = intensity[0];
					Zmin = *(mask + 0);
					Zmed = *(mask + (windowSize * windowSize - 2) / 2);
					Zmax = *(mask + windowSize * windowSize - 2);
					//Xử lý 2 bước
					A1 = Zmed - Zmin;
					A2 = Zmed - Zmax;
					/*cout << "A1 " << A1 << endl;
					cout << "A2 " << A2 << endl;*/
					if (A1 > 0 & A2 < 0) {
				/*		cout << "B1 " << B1 << endl;
						cout << "B2 " << B2 << endl;*/
						B1 = Zxy - Zmin;
						B2 = Zxy - Zmax;
						if (B1 <= 0 | B2 >= 0)
							//cout << "i =" << i << " j = " << j << endl;
							//cout << "val =" << Zmed << endl;
							this->dist.at<uchar>(j, i) = Zmed;
						break;
					}
					else {
						windowSize += 2;
						mask = (int*)realloc(mask,  (windowSize * windowSize - 1) * sizeof(int));
						for (int h = windowSize * windowSize - 9; h < windowSize * windowSize - 1; h++)
							*(mask + h) = -1;
					}
			}//while
		}//for j
	}//for i 
}

void Preprocess::addElement(int *arr, int element , unsigned int length)
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
