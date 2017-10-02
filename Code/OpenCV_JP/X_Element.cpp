#include "X_Element.h"

X_Element::X_Element(int curr_val, int x_coordinate)
{
	this->curr_val = curr_val;
	this->MAF_val = curr_val;
	this->x_coordinate = x_coordinate;
}

X_Element::X_Element(int curr_val, int MAF_val, int x_coordinate)
{
	this->curr_val = curr_val;
	this->MAF_val = MAF_val;
	this->x_coordinate = x_coordinate;
}

void X_Element::setCurr_Val(int curr_val)
{
	this->curr_val = curr_val;
}

void X_Element::setMAF_Val(int MAF_val)
{
	this->MAF_val = MAF_val;
}

void X_Element::setX_Coordinate(int x_coordinate)
{
	this->x_coordinate = x_coordinate;
}

int X_Element::getCurr_Val()
{
	return this->curr_val;
}

int X_Element::getMAF_Val()
{
	return this->MAF_val;
}

int X_Element::getX_Coordinate()
{
	return this->x_coordinate;
}
