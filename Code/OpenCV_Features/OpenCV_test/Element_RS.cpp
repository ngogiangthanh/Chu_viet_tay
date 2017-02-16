#include "Element_RS.h"

Element_RS::Element_RS(Mat draw, float cost, string pathSave, string pathSrc)
{
	this->draw = draw.clone();
	this->cost = cost;
	this->pathSave = pathSave;
	this->pathSrc = pathSrc;
}

void Element_RS::setDraw(Mat draw)
{
	this->draw = draw.clone();
}

void Element_RS::setCost(float cost)
{
	this->cost = cost;
}

void Element_RS::setPathSave(string pathSave)
{
	this->pathSave = pathSave;
}

void Element_RS::setPathSrc(string pathSrc)
{
	this->pathSrc = pathSrc;
}

string Element_RS::getPathSave()
{
	return this->pathSave;
}

string Element_RS::getPathSrc()
{
	return this->pathSrc;
}

float Element_RS::getCost()
{
	return this->cost;
}

Mat Element_RS::getDraw()
{
	return this->draw;
}

bool Element_RS::operator<(const Element_RS & rhs)
{
	return this->pathSrc.compare(rhs.pathSrc) < 0;
}

bool Element_RS::operator==(const Element_RS & rhs)
{
	return this->pathSrc.compare(rhs.pathSrc) == 0;
}
