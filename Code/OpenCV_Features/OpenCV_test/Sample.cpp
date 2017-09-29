#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "Projection.h"
#include "Word_Up.h"
#include "Word_lp.h"
#include "DTW.h"
#include "Equations.h"
#include <time.h>
#include "SIFT.h"
#include "Normalized.h"
#include <filesystem>
#include "Extent.h"
#include "Element_RS.h"
#include "KMeans.h"
#include <iterator>
#include <time.h>
#include <fstream>

using namespace cv;
using namespace std;
namespace fs = experimental::filesystem;

void fill(vector<float>&, int);
int findTotalValuesAndFill(vector<CPoint>& points);

/** @function main */
int main(int argc, char** argv)
{
		//fs::path directory("D:\\Thesis\\Chu_viet_tay\\DTW\\");
		//fs::directory_iterator iter(directory), end;
		//Extent* extent = new Extent();

		//for (; iter != end; ++iter)
		//{
		//	if (iter->path().extension() == ".jpg" | iter->path().extension() == ".JPG" | iter->path().extension() == ".png" | iter->path().extension() == ".PNG" | iter->path().extension() == ".BMP" | iter->path().extension() == ".bmp")
		//	{
		//		string str = iter->path().string();
		//		cout << "str " << str << endl;
		//		Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);

		//		Normalized normalized(img_org);


		//		normalized.MeasurementOfAverageStrokeThickness();
		//		normalized.StraightLineRemoval();
		//		normalized.MeasurementOfAverageStrokeThickness();
		//		int upper, lower;
		//		normalized.BaseLineDetection(normalized.getWord(), upper, lower);
		//		normalized.UnderlineRemoval();
		//		Mat center = normalized.SkewDetectionUsesCentreOfMass(upper, lower);


		//		//saving
		//		vector<string> arrPath = extent->split(str, '\\');
		//		std::string savePath = "D:\\rs_1\\" + arrPath.back();
		//		//imshow("corrected", center);
		//		cv::waitKey(0);
		//		cv::destroyWindow("corrected");
		//		imwrite(savePath, normalized.getWord());
		//	}
		//}

	//this seperate

	/*srand(time(NULL));

	int total_points, total_values, K, max_iterations;
	K = 3;
	max_iterations = 100;

	vector<CPoint> points;
	string point_name;

	fs::path directory("D:\\Thesis\\Chu_viet_tay\\test1\\");
	fs::directory_iterator iter(directory), end;
	Extent* extent = new Extent();
	int count = 0;
	for (; iter != end; ++iter)
	{
		if (iter->path().extension() == ".jpg" | iter->path().extension() == ".JPG" | iter->path().extension() == ".png" | iter->path().extension() == ".PNG" | iter->path().extension() == ".BMP" | iter->path().extension() == ".bmp")
		{
			string str = iter->path().string();
			cout << "str " << str << endl;
			Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);

			Projection projection_profile(img_org);
			projection_profile.cal_pp();
			projection_profile.draw_pp();
			float *pp = 0;
			int size_pp = projection_profile.get_pp(pp);

			vector<float> v{ pp, pp + size_pp };

			CPoint p(count++, v, str);
			points.push_back(p);
		}
	}

	total_values = findTotalValuesAndFill(points);

	total_points = points.size();


	cout << "total_values = " << total_values << endl;
	cout << "total_points = " << total_points << endl;
	KMeans kmeans(K, total_points, total_values, max_iterations);
	kmeans.run(points);*/

	ofstream myfile;
	myfile.open("D:\\example.txt");

	fs::path directory("D:\\Thesis\\Chu_viet_tay\\OneElement");
	fs::directory_iterator iter(directory), end;
	Extent* extent = new Extent();
	int count = 0;
	for (; iter != end; ++iter)
	{
		if (iter->path().extension() == ".jpg" | iter->path().extension() == ".JPG" | iter->path().extension() == ".png" | iter->path().extension() == ".PNG" | iter->path().extension() == ".BMP" | iter->path().extension() == ".bmp")
		{
			string str = iter->path().string();
			cout << "str " << str << endl;
			Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);

			Projection projection_profile(img_org);
			projection_profile.cal_pp();
			projection_profile.draw_pp();
			float *pp = 0;
			int size_pp = projection_profile.get_pp(pp);
			string line = str+" ";
			for (int i = 0; i < size_pp; i++) {

				std::ostringstream ss;
				ss << pp[i];
				std::string s(ss.str());
				if(i < size_pp - 1)
					line = line + s + " ";
				else if(i == size_pp - 1)
					line = line + s;
			}
			myfile << line+"\n";
		}
	}

	myfile.close();

	waitKey(0);

	float val;
	cin >> val;
	return 0;
}

int findTotalValuesAndFill(vector<CPoint>& points) {
	int size_points = points.size();

	CPoint cpoint = points[0];
	vector<float> vec = cpoint.getValues();
	int totalValues = vec.size();

	for (int i = 1; i < size_points; i++) {
		CPoint cpoint1 = points[i];
		vector<float> vec1 = cpoint1.getValues();
		int size_cpoint = vec1.size();

		if (totalValues < size_cpoint) totalValues = size_cpoint;
	}

	for (int i = 0; i < size_points; i++) {
		CPoint cpoint1 = points[i];
		vector<float> vec1 = cpoint1.getValues();
		int size_cpoint = vec1.size();

		fill(vec1, totalValues);

		points[i].setValues(vec1);
	}

	return totalValues;
}

void fill(vector<float>& vec, int total_values){
	int size = vec.size();
	
	if (size < total_values) {
		float avg = 0;
		for (int i = 0; i < size; i++) {
			avg += vec[i];
		}
		avg /= size;

		for (int i = size; i < total_values; i++)
			vec.push_back(avg);
	}
}