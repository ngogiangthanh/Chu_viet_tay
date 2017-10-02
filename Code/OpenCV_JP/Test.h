#pragma once
#include <string>
#include "md5.h"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

class Test
{
private:
	string pathname;
	Mat image;
	bool isCheck;
public:
	Test(string);
	void setImage(Mat);
	Mat getImage();

	void setPath(string);
	string getPath();
	string getPathMd5();
	
	void setCheck(bool);
	bool isChecked();
};
