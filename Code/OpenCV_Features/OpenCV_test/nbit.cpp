#include "nbit.h"

nbit::nbit(Mat src)
{
	this->source = src.clone();
}

void nbit::cal_nbit()
{
	Size size = this->source.size();
	this->nbit_p = new float[size.width];
	float counter = 0;

	for (int i = 0; i < size.width; i++)
	{
		int j = 0;
		counter = 0;
		//counter - loop from 0 to size.height - 1 and get the number background to ink transitions
		for (j = 0; j < size.height; j++)
		{
			if (this->is_bground_to_ink(j, i))
				counter++;
		}//for j

		//undefined situation
		if (counter == 0){
			this->nbit_p[i] = -1;
			cout << "undefined" << endl;
		}

		this->nbit_p[i] = counter / 6;
		//find maximum value in array pp
		if (i == 0)
			this->max = counter / 6;
		else if (this->max < counter / 6)
			this->max = counter / 6;
	}//for i
}

bool nbit::is_bground_to_ink(int r, int c)
{
	Scalar intensity = this->source.at<uchar>(r, c);
	Scalar intensity_next = (r + 1 < this->source.size().height) ? this->source.at<uchar>(r + 1, c) : intensity;

	return (intensity[0] > THRESHOLD_INK_NBIT & intensity_next[0] <= THRESHOLD_INK_NBIT) | (intensity[0] <= THRESHOLD_INK_NBIT & intensity_next[0] > THRESHOLD_INK_NBIT);
}

float * nbit::get_nbit()
{
	return this->nbit_p;
}

void nbit::interpolated_value()
{
	// find two nearest and get avg from them
	Size size = this->source.size();
	int first = -1;
	int second = -1;

	for (int i = 0; i < size.width; i++)
		if (this->nbit_p[i] == -1)
		{
			//find the first
			for (int k = 0; k < size.width; k++)
				if (this->nbit_p[k] != -1) {
					if (first == -1)
						first = k;
					else if (abs(first - i) > abs(k - i))
						first = k;
				}//end if

				 //find the second
			for (int k = 0; k < size.width; k++)
				if (this->nbit_p[k] != -1 & k != first)
				{
					if (second == -1)
						second = k;
					else if (abs(second - i) > abs(k - i))
						second = k;
				}//end if

				 //Calculating the average value
			this->nbit_p[i] = (this->nbit_p[first] + this->nbit_p[second]) / 2;
		}//end if
}

void nbit::draw_nbit()
{
	//normalization height to [0..1]
	Size size = this->source.size();
	int size_of_pp = size.width;
	Mat dist = Mat(NORMALIZATION_NBIT, size.width, CV_8UC3, Scalar(255, 255, 255));

	//Calculating
	for (int i = 0; i < size_of_pp; i++)
	{
		this->nbit_p[i] = (this->nbit_p[i] / max) *  (NORMALIZATION_NBIT - 1);
	}
		

	//Drawing
	for (int i = 0; i < size_of_pp; i++)
		cv::line(dist, Point(i, 0), Point(i, this->nbit_p[i]), Scalar(0, 0, 0));

	//Show
	imshow("Word nbit profile", dist);
	imwrite("D:/save_nbit.jpg", dist);
}
