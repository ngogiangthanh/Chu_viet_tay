#pragma once
#ifndef Extent_H
#define Extent_H
#include <iostream>
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

class Extent
{
public:
	Extent();
	//Chuyển từ định dạng mat sang bitmap
	Bitmap^ ConvertMatToBitmap(Mat);
	// Chuyển từ định dạng bitmap sang mat
	Mat BitmapToMat(Bitmap^);
	// Ép kiểu System::String sang std::string
	void MarshalString(System::String^, std::string&);
	//Split a string in C++? => vector<string> x = split("one:two::three", ':');
	vector<string> &split(const string&, char, vector<string>&);
	vector<string> split(const string &, char);
	void LoadImage(PictureBox^, Mat);
	void showImage(string);
};
#endif