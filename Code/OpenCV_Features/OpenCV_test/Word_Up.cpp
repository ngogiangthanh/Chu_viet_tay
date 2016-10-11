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
		//argmin - loop from 0 to size.height - 1 and get the index of the first ink value
		for (j = 0; j < size.height; j++)
		{
			if (this->is_ink(j, i) == 0)
			{
				value = j;
				this->up[i] = value;

				//find maximum value in array pp
				if (i == 0)
					this->max = value;
				else if (this->max < value)
					this->max = value;
				break;
			}//end if
		}//for j
		//undefined situation
		if (j == size.height)
			this->up[i] = -1;
	}//for i
}

int Word_Up::is_ink(int r, int c)
{
	Scalar intensity = this->source.at<uchar>(r, c);
	return (intensity[0] <= THRESHOLD_INK_UP) ? INK_UP : BACKGROUND_UP;
}

int Word_Up::get_up(int *&returnVal)
{
	int length = this->source.size().width;
	returnVal = new int[length];
	for (int i = 0; i < length; i++)
		returnVal[i] = this->up[i];
	return length;
}

void Word_Up::interpolated_value()
{
	//find two nearest and get avg from them
	Size size = this->source.size();
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
				}//end if

			//find the second
			for (int k = 0; k < size.width; k++)
				if (this->up[k] != -1 & k != first)
				{
					if (second == -1)
						second = k;
					else if (abs(second - i) > abs(k - i))
						second = k;
				}//end if
			
			//Calculating the average value
			this->up[i] = (this->up[first] + this->up[second]) / 2;
		}//end if
}

void Word_Up::draw_up()
{
	//normalization height to [0..1]
	Size size = this->source.size();
	int size_of_pp = size.width;
	Mat dist = Mat(NORMALIZATION_WP_UP, size.width, CV_8UC3, Scalar(255, 255, 255));

	//Calculating
	for (int i = 0; i < size_of_pp; i++)
		this->up[i] = (this->up[i] * (NORMALIZATION_WP_UP - 1)) / max;

	//Drawing
	for (int i = 0; i < size_of_pp - 1; i++)
		cv::line(dist, Point(i, this->up[i]), Point(i, this->up[i + 1]), Scalar(0, 0, 0));

	//Show
	imshow("Word upper profile", dist);
	imwrite("D:/save_up.jpg", dist);
}
