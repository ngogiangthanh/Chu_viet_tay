#include "Word_lp.h"

Word_lp::Word_lp(Mat src)
{
	this->source = src.clone();
}

void Word_lp::cal_lp()
{
	Size size = this->source.size();
	this->lp = new int[size.width];
	int value = 0;

	for (int i = 0; i < size.width; i++)
	{
		int j = 0;
		//argmax - loop from size.height - 1 to 0 and get the index of the first ink value
		for (j = size.height - 1; j >= 0; j--)
		{
			if (this->is_ink(j, i) == 0)
			{
				value = j;
				this->lp[i] = value;

				//find maximum value in array pp
				if (i == 0)
					this->max = value;
				else if (this->max < value)
					this->max = value;
				break;
			}//end if
		}//for j
		 //undefined situation
		if (j == -1)
			this->lp[i] = -1;
	}//for i
}

int Word_lp::is_ink(int r, int c)
{
	Scalar intensity = this->source.at<uchar>(r, c);
	return (intensity[0] <= THRESHOLD_INK_LP) ? INK_LP : BACKGROUND_LP;
}

int * Word_lp::get_lp()
{
	return this->lp;
}

void Word_lp::interpolated_value()
{
	// find two nearest and get avg from them
	Size size = this->source.size();
	int first = -1;
	int second = -1;

	for (int i = 0; i < size.width; i++)
		if (this->lp[i] == -1)
		{
			//find the first
			for (int k = 0; k < size.width; k++)
				if (this->lp[k] != -1) {
					if (first == -1)
						first = k;
					else if (abs(first - i) > abs(k - i))
						first = k;
				}//end if

			//find the second
			for (int k = 0; k < size.width; k++)
				if (this->lp[k] != -1 & k != first)
				{
					if (second == -1)
						second = k;
					else if (abs(second - i) > abs(k - i))
						second = k;
				}//end if

			//Calculating the average value
			this->lp[i] = (this->lp[first] + this->lp[second]) / 2;
		}//end if
}

void Word_lp::draw_lp()
{
	//normalization height to [0..1]
	Size size = this->source.size();
	int size_of_pp = size.width;
	Mat dist = Mat(NORMALIZATION_WP_LP, size.width, CV_8UC3, Scalar(255, 255, 255));
	
	//Calculating
	for (int i = 0; i < size_of_pp; i++)
		this->lp[i] = (this->lp[i] * (NORMALIZATION_WP_LP - 1)) / max;

	//Drawing
	for (int i = 0; i < size_of_pp - 1; i++)
		cv::line(dist, Point(i, this->lp[i]), Point(i, this->lp[i + 1]), Scalar(0, 0, 0));

	//Show
	imshow("Word lower profile", dist);
	imwrite("D:/save_lp.jpg", dist);
}
