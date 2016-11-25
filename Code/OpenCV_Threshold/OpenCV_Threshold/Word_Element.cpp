#include "Word_Element.h"

Word_Element::Word_Element()
{
}

Word_Element::Word_Element(int x_begin, int x_end)
{
	this->x_begin = x_begin;
	this->x_end = x_end;
}

void Word_Element::setX_Begin(int x_begin)
{
	this->x_begin = x_begin;
}

void Word_Element::setX_End(int x_end)
{
	this->x_end = x_end;
}

int Word_Element::getX_Begin()
{
	return this->x_begin;
}

int Word_Element::getX_End()
{
	return this->x_end;
}

int Word_Element::getX_Middle_Coordinate()
{
	return this->x_begin + (this->x_end - this->x_begin)/2;
}

int Word_Element::get_Distance()
{
	return this->x_end - this->x_begin;
}
