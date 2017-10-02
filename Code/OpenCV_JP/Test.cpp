#include "Test.h"

Test::Test(string pathName)
{
	this->pathname = pathName;
	this->isCheck = false;
}

void Test::setImage(Mat mat)
{
	this->image = mat.clone();
}

Mat Test::getImage()
{
	return this->image.clone();
}

void Test::setPath(string pathName)
{
	this->pathname = pathName;
}

string Test::getPath()
{
	return this->pathname;
}

string Test::getPathMd5()
{
	return md5(this->pathname);
}

void Test::setCheck(bool check)
{
	this->isCheck = check;
}

bool Test::isChecked()
{
	return this->isCheck;
}
