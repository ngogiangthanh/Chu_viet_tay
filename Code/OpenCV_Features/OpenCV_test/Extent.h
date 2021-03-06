#pragma once
#include <iostream>
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

class Extent
{
public:
	Extent();
	//Split a string in C++? => vector<string> x = split("one:two::three", ':');
	vector<string> &split(const string&, char, vector<string>&);
	vector<string> split(const string &, char);
	void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
};