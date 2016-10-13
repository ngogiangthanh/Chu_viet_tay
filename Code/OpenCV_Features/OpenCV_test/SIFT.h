#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#ifndef  _SIFT_H_

using namespace cv;
using namespace std;

class SIFT1
{
private:
public:
	SIFT1();
	void FeatureMatching(
		Mat img1,			// 画像１のファイル名
		Mat img2);
};
#endif // ! _SIFT_H_
#define _SIFT_H_


