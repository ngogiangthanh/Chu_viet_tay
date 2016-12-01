#include "Y_Element.h"

Y_Element::Y_Element(int curr_val, int y_coordinate)
{
	this->curr_val = curr_val;
	this->MAF_val = curr_val;
	this->y_coordinate = y_coordinate;
}

Y_Element::Y_Element(int curr_val, int MAF_val, int y_coordinate)
{
	this->curr_val = curr_val;
	this->MAF_val = MAF_val;
	this->y_coordinate = y_coordinate;
}

void Y_Element::setCurr_Val(int curr_val)
{
	this->curr_val = curr_val;
}

void Y_Element::setMAF_Val(int MAF_val)
{
	this->MAF_val = MAF_val;
}

void Y_Element::setY_Coordinate(int y_coordinate)
{
	this->y_coordinate = y_coordinate;
}

int Y_Element::getCurr_Val()
{
	return this->curr_val;
}

int Y_Element::getMAF_Val()
{
	return this->MAF_val;
}

int Y_Element::getY_Coordinate()
{
	return this->y_coordinate;
}