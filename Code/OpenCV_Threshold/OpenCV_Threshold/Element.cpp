#include "Element.h"

Element::Element()
{
	this->x = 0;
	this->y = 0;
	this->intensity = 0;
	this->valley = false;
	this->top = false;
	this->minDistance = -1;//Nothing;
	this->doneNext = false;
	this->donePre = false;
	this->punctuationMarks = false;
	this->idxConnect = -1;
	this->iterator = false;
}

Element::Element(unsigned int x, unsigned int y, unsigned int intensity)
{
	this->x = x;
	this->y = y;
	this->intensity = intensity;
	this->valley = false;
	this->top = false;
	this->minDistance = -1;//Nothing;
	this->doneNext = false;
	this->donePre = false;
	this->punctuationMarks = false;
	this->idxConnect = -1;
	this->iterator = false;
}

unsigned int Element::getX()
{
	return this->x;
}

unsigned int Element::getY()
{
	return this->y;
}

unsigned int Element::getOrder()
{
	return this->order;
}

unsigned int Element::getIntensity()
{
	return this->intensity;
}

double Element::getMinDistance()
{
	return this->minDistance;
}

cv::Point Element::getCorner()
{
	return this->corner;
}

long Element::getIdxConnect()
{
	return this->idxConnect;
}

bool Element::isValley()
{
	return this->valley;
}

bool Element::isTop()
{
	return this->top;
}

bool Element::isDoneNext()
{
	return this->doneNext;
}

bool Element::isDonePre()
{
	return this->donePre;
}

bool Element::isPunctuationMarks()
{
	return this->punctuationMarks;
}

bool Element::isIterator()
{
	return this->iterator;
}

void Element::setX(unsigned int x)
{
	this->x = x;
}

void Element::setY(unsigned int y)
{
	this->y = y;
}

void Element::setOrder(unsigned int order)
{
	this->order = order;
}

void Element::setIdxConnect(long idxConnect)
{
	this->idxConnect = idxConnect;
}

void Element::setTop(bool top)
{
	this->top = top;
}

void Element::setIntensity(unsigned int intensity)
{
	this->intensity = intensity;
}

void Element::setValley(bool valley)
{
	this->valley = valley;
}

void Element::setDoneNext(bool done)
{
	this->doneNext = done;
}

void Element::setDonePre(bool done)
{
	this->donePre = done;
}

void Element::setMinDistance(double minDistance)
{
	this->minDistance = minDistance;
}

void Element::setPunctuationMarks(bool punctuationMarks)
{
	this->punctuationMarks = punctuationMarks;
}

void Element::setIterator(bool iterator)
{
	this->iterator = iterator;
}

void Element::setCorner(cv::Point corner)
{
	this->corner = corner;
}
