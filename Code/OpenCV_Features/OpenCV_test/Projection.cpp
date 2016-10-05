#include "Projection.h"

Projection::Projection(Mat src)
{
	this->source = src.clone();
}

void Projection::getFeatures()
{
	Size size = this->source.size();
	this->projection_pts = new int[size.width];
	long sum_intensity = 0;

	for (int i = 0; i < size.width; i++)
	{
		sum_intensity = 0;
		for (int j = 0; j < size.height; j++)
		{
			sum_intensity += 255 - this->source.at<uchar>(j, i);
		}//for j
		this->projection_pts[i] = sum_intensity;
		if (i == 0)
			max = sum_intensity;
		else if (max < sum_intensity) max = sum_intensity;
	}//for i
}

int* Projection::getProjection_pts()
{
	//normalization height to [0..1]
		//initial
		Mat dist = Mat(100, this->source.size().width, CV_8UC3, Scalar(255, 255, 255));
		float unit = max / 100;
		int size_of_projection = this->source.size().width;
		cout << "with=" << size_of_projection << endl;
		for (int i = 0; i < size_of_projection; i++)
		{
			cout << "" << this->projection_pts[i] << endl;
			cv::line(dist, cv::Point(i, 100), cv::Point(i, round(this->projection_pts[i] / unit)), Scalar(0, 0, 0));
		}
		
		imshow("Projection profile", dist);
		imwrite("D:/save.jpg", dist);
	//return the result
	return this->projection_pts;
}
