#include "Column.h"
#include <iostream>

using namespace std;

Column::Column()
{
}

Column::Column(int size)
{
	this->order = -1;
	this->Elements = new Element[size];
	this->size = size;
}

Column::Column(int order, int size)
{
	this->order = order;
	this->Elements = new Element[size];
	this->size = size;
}

void Column::initColumn()
{
	this->Elements = new Element[this->size];
}

int Column::getOrder()
{
	return this->order;
}

int Column::getSize()
{
	return this->size;
}

Element* Column::getElements()
{
	return this->Elements;
}

Element& Column::getElement(int index)
{
	return this->Elements[index];
}

void Column::setOrder(int order)
{
	this->order = order;
}

void Column::setSize(int size)
{
	this->size = size;
}

void Column::addElements(Element* element, int index)
{
	this->Elements[index] = *element;
}

void Column::editElements(Element* element, int index)
{
	this->Elements[index] = *element;
}
