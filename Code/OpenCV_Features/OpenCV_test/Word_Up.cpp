#include "Word_Up.h"

Word_Up::Word_Up(Mat src)
{
	this->source = src.clone();
}

void Word_Up::cal_up()
{
	Size size = this->source.size();
	this->up = new int[size.width];
	int value = 0;

	for (int i = 0; i < size.width; i++)
	{
		int j = 0;
		for (j = 0; j < size.height; j++)
		{
			if (this->is_ink(j, i) == 0)
			{
				value = j;
				this->up[i] = value;
				if (i == 0)
					this->max = value;
				else if (this->max < value)
					this->max = value;
				break;
			}
		}//for j
		//undefined situation
		if (j == size.height){
			this->up[i] = -1;
			cout << "undefined" << endl;
		}
	}//for i
}

int Word_Up::is_ink(int r, int c)
{
	Scalar intensity = this->source.at<uchar>(r, c);
	return (intensity[0] <= THRESHOLD_INK_UP) ? INK_UP : BACKGROUND_UP;
}

int* Word_Up::get_up()
{
	return this->up;
}

void Word_Up::interpolated_value()
{
	Size size = this->source.size();
	// find two nearest and get avg from them
	int first = - 1;
	int second = -1;
	for (int i = 0; i < size.width; i++)
		if (this->up[i] == -1)
		{
			//find the first
			for (int k = 0; k < size.width; k++)
				if (this->up[k] != -1)
				{
					if (first == -1)
						first = k;
					else if (abs(first - i) > abs(k - i))
						first = k;
				}

			//find the second
			for (int k = 0; k < size.width; k++)
				if (this->up[k] != -1 & k != first)
				{
					if (second == -1)
						second = k;
					else if (abs(second - i) > abs(k - i))
						second = k;
				}
					
			cout << "[F=" << first << "-" << this->up[first] << "][M=" << i << "-" << (this->up[first] + this->up[second]) / 2 << "][S=" << second << "-" << this->up[second] << "]"<<endl;
			this->up[i] = (this->up[first] + this->up[second]) / 2;
		}
}

void Word_Up::draw_up()
{
	this->interpolated_value();
	//normalization height to [0..1]
	Size size = this->source.size();
	Mat dist = Mat(NORMALIZATION_WP_UP, size.width, CV_8UC3, Scalar(255, 255, 255));
	int size_of_pp = size.width;

	for (int i = 0; i < size_of_pp; i++)
	{
		this->up[i] = this->up[i] * NORMALIZATION_WP_UP / max;
	}//end for i

	for (int i = 0; i < size_of_pp - 1; i++)
	{
		cv::line(dist, Point(i, this->up[i]), Point(i, this->up[i + 1]), Scalar(0, 0, 0));
	}//end for i

	imshow("Word_Up upper profile", dist);
	imwrite("D:/save_up.jpg", dist);
}
