#include "Projection.h"

Projection::Projection(Mat src)
{
	this->source = src.clone();
}

void Projection::cal_pp()
{
	Size size = this->source.size();
	this->pp = new int[size.width];
	int summing = 0;

	for (int i = 0; i < size.width; i++)
	{
		summing = 0;
		for (int j = 0; j < size.height; j++)
		{
			summing += (255 - this->I(j, i));
		}//for j

		this->pp[i] = summing;
		//find maximum value in array pp
		if (i == 0)
			this->max = summing;
		else if (this->max < summing)
			this->max = summing;
	}//for i
}

int Projection::I(int r, int c)
{
	Scalar intensity = this->source.at<uchar>(r, c);
	return intensity[0];
}

int* Projection::get_pp()
{
	return this->pp;
}

void Projection::draw_pp()
{
	//normalization the height to [0..1]
	Size size = this->source.size();
	int size_of_pp = size.width;
	Mat dist = Mat(NORMALIZATION_PP, size.width, CV_8UC3, Scalar(255, 255, 255));

	//Calculating
	for (int i = 0; i < size_of_pp; i++)
		this->pp[i] = (this->pp[i] * (NORMALIZATION_PP - 1)) / max;

	//Drawing
	for (int i = 0; i < size_of_pp - 1; i++)
		cv::line(dist, Point(i, this->pp[i]), Point(i, this->pp[i + 1]), Scalar(0, 0, 0));

	//Show
	imshow("Projection profile", dist);
	imwrite("D:/save_pp.jpg", dist);
}


