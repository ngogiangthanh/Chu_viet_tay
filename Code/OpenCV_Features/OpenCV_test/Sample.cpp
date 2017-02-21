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
#include <iterator>

using namespace cv;
using namespace std;
namespace fs = experimental::filesystem;

void readme();

/** @function main */
int main(int argc, char** argv)
{

	//fs::path directory("D:\\Thesis\\Chu_viet_tay\\Outputs\\page-1.jpg\\");
		fs::path directory("D:\\Thesis\\Chu_viet_tay\\DTW\\");
		fs::directory_iterator iter(directory), end;
		Extent* extent = new Extent();

		for (; iter != end; ++iter)
		{
			if (iter->path().extension() == ".jpg" | iter->path().extension() == ".JPG" | iter->path().extension() == ".png" | iter->path().extension() == ".PNG" | iter->path().extension() == ".BMP" | iter->path().extension() == ".bmp")
			{
				string str = iter->path().string();
				cout << "str " << str << endl;
				Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);

				Normalized normalized(img_org);



							//normalized.MeasurementOfAverageStrokeThickness();
							//normalized.StraightLineRemoval();
							//int upper, lower; 
							//normalized.BaseLineDetection(img_org.clone(), upper, lower);
							//Mat center = normalized.SkewDetectionUsesCentreOfMass(upper, lower);

										/*cv::Rect crop_part_1(0, 0, img_org.cols / 2, img_org.rows);
										cv::Rect crop_part_2(img_org.cols / 2, 0, img_org.cols / 2, img_org.rows);
										int upper_part_1, lower_part_1;
										int upper_part_2, lower_part_2;
										Mat Part_1 = img_org(crop_part_1).clone();
										Mat Part_2 = img_org(crop_part_2).clone();

										normalized.BaseLineDetection(Part_1, upper_part_1, lower_part_1);
										normalized.BaseLineDetection(Part_2, upper_part_2, lower_part_2);
										vector<cv::Point> pts;
										pts.push_back(cv::Point(0, upper_part_1));*/
										//pts.push_back(cv::Point(this->word.cols/2, upper_part_1));
										//pts.push_back(cv::Point(this->word.cols / 2, upper_part_2));
										//pts.push_back(cv::Point(img_org.cols, upper_part_2));
										//pts.push_back(cv::Point(img_org.cols, lower_part_2));
										//pts.push_back(cv::Point(this->word.cols / 2, lower_part_2));
										//pts.push_back(cv::Point(this->word.cols / 2, lower_part_1));
										//pts.push_back(cv::Point(0, lower_part_1));

									//	MatModifies matMod;

										//Mat word_removed_baseline = matMod.cut(img_org, pts);

										//cv::line(Part_1, cv::Point(0, upper_part_1), cv::Point(Part_1.cols, upper_part_1), Scalar(128, 128, 128));
										//cv::line(Part_1, cv::Point(0, lower_part_1), cv::Point(Part_1.cols, lower_part_1), Scalar(128, 128, 128));
										//imshow("Baseline 1", Part_1);
										//cv::line(Part_2, cv::Point(0, upper_part_2), cv::Point(Part_2.cols, upper_part_2), Scalar(128, 128, 128));
										//cv::line(Part_2, cv::Point(0, lower_part_2), cv::Point(Part_2.cols, lower_part_2), Scalar(128, 128, 128));
										//imshow("Baseline 2", Part_2);
							//cv::Rect crop(0, upper, img_org.cols, lower - upper);
							//Mat word_removed_baseline = img_org(crop).clone();
							Mat temp = img_org.clone();
							Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
							erode(img_org, img_org, element);
							Mat preprocessed = normalized.preprocess2(img_org);
							imshow("preprocessed2", preprocessed);
							double skew;
							normalized.hough_transform(preprocessed, img_org, &skew);
							Mat rotated = normalized.rot(temp, skew* CV_PI / 180);

				//normalized.StraightLineRemoval();

				//saving
				vector<string> arrPath = extent->split(str, '\\');
				std::string savePath = "D:\\Rs\\" + arrPath.back();
				imshow("corrected", rotated);
				cv::waitKey(0);
				cv::destroyWindow("corrected");
				imwrite(savePath, rotated);
			}
		}


	//Mat pattern_img = imread("D:\\Thesis\\Chu_viet_tay\\DTW\\word_1_2.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	//fs::path directory("D:\\Thesis\\Chu_viet_tay\\DTW\\");
	//Projection pattern_pp(pattern_img);
	//pattern_pp.cal_pp();
	//Mat pattern_draw = pattern_pp.draw_pp();
	//float *pattern = 0;
	//int size_pattern = pattern_pp.get_pp(pattern);
	////
	//Word_lp pattern_lp(pattern_img);
	//pattern_lp.cal_lp();
	//pattern_lp.interpolated_value();
	//Mat pattern_draw_lp = pattern_lp.draw_lp();
	//float* pattern_a_lp = 0;
	//int size_pattern_lp = pattern_lp.get_lp(pattern_a_lp);
	////
	//Word_Up pattern_up(pattern_img);
	//pattern_up.cal_up();
	//pattern_up.interpolated_value();
	//Mat pattern_draw_up = pattern_up.draw_up();
	//float* pattern_a_up = 0;
	//int size_pattern_up = pattern_up.get_up(pattern_a_up);

	//imshow("Pattern", pattern_img);

	//vector<Element_RS> rs_pp;
	//vector<Element_RS> rs_up_lp;
	//vector<Element_RS> rs;

	////-- Step 1: Detect the keypoints using SIFT Detector
	////Ptr<xfeatures2d::SIFT> sift = xfeatures2d::SIFT::create();
	////vector<KeyPoint> sift_keypoint;
	////sift->detect(pattern_img, sift_keypoint);
	////int size_of_points = sift_keypoint.size();
	//////-- Draw keypoints
	////Mat img_sift;
	////cout << sift_keypoint.size() << endl;
	////cout << sift_keypoint.at(0).angle << ", "<< sift_keypoint.at(0). << ", " << sift_keypoint.at(0).angle << endl;
	////Mat img_white = pattern_img.clone();
	////drawKeypoints(img_white, sift_keypoint, img_sift, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//////-- Show detected (drawn) keypoints
	////imshow("SIFT", img_sift);

	//fs::directory_iterator iter(directory), end;
	//Extent* extent = new Extent();

	//	for (; iter != end; ++iter)
	//	{
	//		if (iter->path().extension() == ".jpg" | iter->path().extension() == ".JPG" | iter->path().extension() == ".png" | iter->path().extension() == ".PNG" | iter->path().extension() == ".BMP" | iter->path().extension() == ".bmp")
	//		{
	//						//initial file pattern
	//						string str = iter->path().string();
	//						//cout << "str " << str << endl;
	//						Mat search_img = imread(str, CV_LOAD_IMAGE_GRAYSCALE);
	//						//---projection profiles

	//						Projection search_pp(search_img);
	//						search_pp.cal_pp();
	//						Mat search_draw = search_pp.draw_pp();
	//						float *search = 0;
	//						int size_search = search_pp.get_pp(search);

	//						Dynamic_Time_Warping DTW(pattern, search, size_pattern, size_search);
	//						DTW.drawMatching();
	//						//cout << "Projection profile - matching cost = " << DTW.DTWDistance_GPC(20) << endl;
	//						//saving
	//						vector<string> arrPath = extent->split(str, '\\');
	//						//std::string savePath = "D:\\rs\\pp_" + arrPath.back();
	//						//imwrite(savePath, search_draw);
	//						std::string savePath = "D:\\rs\\pp\\" + arrPath.back();

	//						float cost = DTW.DTWDistance_GPC(20);
	//						if (cost < 0.01) {
	//							Element_RS element_rs(search_img, cost, savePath, str);
	//							rs_pp.push_back(element_rs);
	//						}
	//						//---end projection profiles

	//						//---lower and upper word
	//						Word_lp search_lp(search_img);
	//						search_lp.cal_lp();
	//						search_lp.interpolated_value();
	//						Mat search_lp_draw = search_lp.draw_lp();
	//						float* search_low = 0;
	//						int size_search_lp = search_lp.get_lp(search_low);
	//						//savePath = "D:\\rs\\lp_" + arrPath.back();
	//						//imwrite(savePath, search_lp_draw);

	//						Word_Up search_up(search_img);
	//						search_up.cal_up();
	//						search_up.interpolated_value();
	//						Mat search_up_draw = search_up.draw_up();
	//						float* search_upw = 0;
	//						int size_search_up = search_up.get_up(search_upw);
	//						//savePath = "D:\\rs\\up_" + arrPath.back();
	//						//imwrite(savePath, search_up_draw);

	//						Dynamic_Time_Warping DTW_UP(pattern_a_up, search_upw, size_pattern_up, size_search_up);
	//						Dynamic_Time_Warping DTW_LP(pattern_a_lp, search_low, size_pattern_lp, size_search_lp);
	//						DTW_LP.drawMatching();
	//						DTW_UP.drawMatching();
	//						float mean_cost = (DTW_LP.DTWDistance_GPC(20) + DTW_UP.DTWDistance_GPC(20))/2;
	//						//float cost = DTW_UP.DTWDistance_GPC(20);
	//						if (mean_cost < 0.01) {
	//							savePath = "D:\\rs\\lp_up\\" + arrPath.back();
	//							Element_RS element_up(search_img, mean_cost, savePath, str);
	//							rs_up_lp.push_back(element_up);
	//						}

	//		}
	//	}

	////Sort by first element in vector
	//std::sort(rs_pp.begin(), rs_pp.end(),
	//	[]( Element_RS& a, Element_RS& b) {
	//	return a.getCost() < b.getCost();
	//});

	//std::sort(rs_up_lp.begin(), rs_up_lp.end(),
	//	[](Element_RS& a, Element_RS& b) {
	//	return a.getCost() < b.getCost();
	//});

	//int s_pp = rs_pp.size();
	//for (vector<Element_RS>::size_type m = 0; m != s_pp; m++) {
	//	//if (rs_pp.at(m).getCost() < 0.01) {
	//		imwrite(rs_pp.at(m).getPathSave(), rs_pp.at(m).getDraw());
	//		cout << rs_pp.at(m).getPathSave() << " | " << rs_pp.at(m).getCost() << endl;
	//		imwrite(rs_pp.at(m).getPathSave(), rs_pp.at(m).getDraw());
	//	//}
	//}
	//cout << endl;


	//int count = 0;
	//int s_up = rs_up_lp.size();
	//for (vector<Element_RS>::size_type m = 0; m != s_up; m++) {
	//	//if (rs_up.at(m).getCost() < 0.01) {
	//		count++;
	//		cout << rs_up_lp.at(m).getPathSave() << " | " << rs_up_lp.at(m).getCost() << endl;
	//		imwrite(rs_up_lp.at(m).getPathSave(), rs_up_lp.at(m).getDraw());
	//	//}
	//}
	//cout << "s_up = " << count << endl;

	//cout << endl;

	////int s_lp = rs_lp.size();

	////count = 0;
	////for (vector<Element_RS>::size_type m = 0; m != s_lp; m++) {
	////	//if (rs_lp.at(m).getCost() < 0.01) {
	////		count++;
	////		cout << rs_lp.at(m).getPathSave() << " | " << rs_lp.at(m).getCost() << endl;
	////		imwrite(rs_lp.at(m).getPathSave(), rs_lp.at(m).getDraw());
	////	//}
	////}
	////cout << "s_lp = " << count << endl;

	////cout << endl;

	////std::set_intersection(rs_up.begin(), rs_up.end(),
	////	rs_lp.begin(), rs_lp.end(),
	////	std::back_inserter(rs_rs), [](Element_RS& a, Element_RS& b) {
	////	return a.getPathSrc().compare(b.getPathSrc()) == 0;
	////});

	////set_intersection(rs_up.begin(), rs_up.end(), rs_lp.begin(), rs_lp.end(), std::back_inserter(rs_lp_up)); //myvec3: 1 3 10
	//set_intersection(rs_up_lp.begin(), rs_up_lp.end(), rs_pp.begin(), rs_pp.end(), std::back_inserter(rs)); //myvec3: 1 3 10

	//cout << endl;

	////int s_rs_rs = rs_lp_up.size();
	////cout << "s_rs_lp_up = "<< s_rs_rs << endl;
	////for (vector<Element_RS>::size_type m = 0; m != s_rs_rs; m++) {
	////		cout << rs_lp_up.at(m).getPathSave() << " | " << rs_lp_up.at(m).getCost() << endl;
	////}

	////cout << endl;


	//int s_rs = rs.size();
	//cout << "s_rs = " << s_rs << endl;
	//for (vector<Element_RS>::size_type m = 0; m != s_rs; m++) {
	//	cout << rs.at(m).getPathSave() << " | " << rs.at(m).getCost() << endl;
	//	imwrite(rs.at(m).getPathSave(), rs.at(m).getDraw());
	//}

	//cout << endl;

	/*
	Projection pp_img_2(img2);
	pp_img_2.cal_pp();
	Mat draw_pp_2 = pp_img_2.draw_pp();
	float *pp2 = 0;
	int s_pp2 = pp_img_2.get_pp(pp2);


	clock_t tStart = clock();
	Dynamic_Time_Warping DTW(pp1, pp2, s_pp1, s_pp2);
	DTW.drawMatching();
	cout << "Projection profile - matching cost = " << DTW.DTWDistance_GPC(20) << endl;
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);*/

	/*Word_Up word_up(img_org);
	word_up.cal_up();
	word_up.interpolated_value();
	word_up.draw_up();*/

	/*
	
	/*
	Projection projection_profile(img_org);
	projection_profile.cal_pp();
	projection_profile.draw_pp();
	//float *pp = 0;
	//int size_pp = projection_profile.get_pp(pp);
	
	Projection projection_profile1(img_org1);
	projection_profile1.cal_pp();
	projection_profile1.draw_pp();
	float *pp1 = 0;
	int size_pp1 = projection_profile1.get_pp(pp1);

	Projection projection_profile2(img_org2);
	projection_profile2.cal_pp();
	projection_profile2.draw_pp();
	float *pp2 = 0;
	int size_pp2 = projection_profile2.get_pp(pp2);
	
	Word_Up word_up(img_org);
	word_up.cal_up();
	word_up.interpolated_value();
	word_up.draw_up();
	//float* wup = 0;
	//int size_wup = word_up.get_up(wup);*/
	/*
	Word_Up word_up1(img_org1);
	word_up1.cal_up();
	word_up1.interpolated_value();
	word_up1.draw_up();
	float* wup1 = 0;
	int size_wup1 = word_up1.get_up(wup1);


	Word_Up word_up2(img_org2);
	word_up2.cal_up();
	word_up2.interpolated_value();
	word_up2.draw_up();
	float* wup2 = 0;
	int size_wup2 = word_up2.get_up(wup2);
	*/

	/*
	Word_lp word_lp(img_org);
	word_lp.cal_lp();
	word_lp.interpolated_value();
	word_lp.draw_lp();
	//float* wlp = 0;
	//word_lp.get_lp(wlp);
	
	------------DTW---------
*/
	//float  a[] = { 0.2,0.3,0.4,0.5,0.7,0.1,0.2,0.3,0.4,0.5 };
	//float b[] = { 0.2,0.4,0.4,0.5,0.9,0.4,0.5,0.6,0.3 };
	//Dynamic_Time_Warping DTW(a, b, 10, 9);
	//DTW.drawMatching();
	//cout << "matching cost = " << DTW.DTWDistance() << endl;
	//cout << "matching cost gpc = " << DTW.DTWDistance_GPC(5) << endl;
	



	waitKey(0);

	return 0;
}

/** @function readme */
void readme()
{
	std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl;
}