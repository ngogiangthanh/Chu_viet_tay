#include "Normalized.h"

Normalized::Normalized(Mat word)
{
	this->word = word.clone();
}

void Normalized::MeasurementOfAverageStrokeThickness()
{
	int size = this->word.cols*this->word.rows;
	int* val = new int[size];
	int sum = 0;
	int order = 0;
	int ast = 0;

	for (int i = 0; i < this->word.cols; i++)
	{
		for (int j = 0; j < this->word.rows; j++)
		{
			Scalar intensity = this->word.at<uchar>(j, i);
			if (intensity[0] <= THRESHOLD_INK)
				sum++;
			else {
				if (sum != 0 & sum < this->word.rows / 2) {
					//them vao mang
					val[order++] = sum;
					ast += sum;
				}
				sum = 0;
			}
		}

		if (sum != 0 & sum < this->word.rows / 2) {
			//them vao mang
			val[order++] = sum;
			ast += sum;
		}
		sum = 0;
	}
	ast /= order;
	//cout << "average stroke thickness = " << ast << endl;

	int new_order = 0;
	for (int i = 0; i < order; i++) {
		if (ast > val[i]) {
			//cout << val[i] << endl;
			AST += val[i];
			new_order++;
		}
	}
	AST /= new_order;
	//cout << " new ast = " << AST << endl;
	delete[] val;
}

void Normalized::StraightLineRemoval()
{
	int sum = 0;
	int sum_rows = 0;

	for (int j = 0; j < this->word.rows; j++)
	{
		for (int i = 0; i < this->word.cols; i++)
		{
			Scalar intensity = this->word.at<uchar>(j, i);
			if (intensity[0] <= THRESHOLD_INK)
				sum++;
			else {
				if (sum != 0 & sum > this->word.cols / 2) {
					for (int k = i - sum; k <= i; k++) {
						sum_rows = 0;
						for (int l = j; l < this->word.rows; l++) {
							intensity = this->word.at<uchar>(l, k);
							if (intensity[0] <= THRESHOLD_INK)
								sum_rows++;
							else {
								if (sum_rows != 0 & sum_rows <= AST)
									cv::line(this->word, cv::Point(k, j - 1), cv::Point(k, l), Scalar(255, 255, 255));
								sum_rows = 0;
								break;
							}
						}
					}
				}					
				sum = 0;
			}
		}
		if (sum != 0 & sum > this->word.cols / 2) {
			for (int k = this->word.cols - sum; k < this->word.cols; k++) {
				sum_rows = 0;
				for (int l = j; l < this->word.rows; l++) {
					Scalar intensity = this->word.at<uchar>(l, k);
					if (intensity[0] <= THRESHOLD_INK)
						sum_rows++;
					else {
						if (sum_rows != 0 & sum_rows <= AST)
							cv::line(this->word, cv::Point(k, j - 1), cv::Point(k, l), Scalar(255, 255, 255));
						sum_rows = 0;
						break;
					}
				}
			}
		}		
			sum = 0;
	}

	imshow("straighline", this->word);
	imwrite("D:/straighline.jpg", this->word);
}

void Normalized::BaseLineDetection()
{
}

void Normalized::UnderlineDetectionAndRemoval()
{
}

void Normalized::SkewDetectionUsesCentreOfMass()
{
}

void Normalized::RemovalOfUnderlinesMatchingTheSlopeOfTheWord()
{
}

void Normalized::setWord(Mat word)
{
	this->word = word.clone();
}

Mat Normalized::getWord()
{
	return this->word;
}
