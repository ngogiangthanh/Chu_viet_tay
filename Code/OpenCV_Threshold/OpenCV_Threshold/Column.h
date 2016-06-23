#pragma once
#ifndef Column_H
#define Column_H
#include "Element.h"

class Column {

private: 
	int order;
	int size;
	Element* Elements;
public:
	Column();
	Column(int size);
	Column(int order, int size);
	void initColumn();
	int getOrder();
	int getSize();
	Element* getElements();
	Element& getElement(int);
	void setOrder(int order);
	void setSize(int size);
	void addElements(Element* element, int index);
	void editElements(Element* element, int index);
};

#endif
