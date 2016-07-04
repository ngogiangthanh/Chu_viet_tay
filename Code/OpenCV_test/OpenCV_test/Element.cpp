#include "Element.h"

Element::Element(int x, int y)
{
	this->x = x;
	this->y = y;
	this->pre = false;
	this->next = false;
}

void Element::setX(int x)
{
	this->x = x;
}

void Element::setY(int y)
{
	this->y = y;
}

void Element::setPre(bool pre)
{
	this->pre = pre;
}

void Element::setNext(bool next)
{
	this->next = next;
}

int Element::getX()
{
	return this->x;
}

int Element::getY()
{
	return this->y;
}

bool Element::isPre()
{
	return this->pre;
}

bool Element::isNext()
{
	return this->next;
}
