#pragma once
#ifndef Elements_H
#define Elements_H
#include <iostream>
#include <queue>
#include "Element.h"

using namespace std;

class Elements
{
private: 
	vector<Element*> elements;
public:
	Elements();
	void setElements(vector<Element*>);
	vector<Element*> getElements();
	void add(Element*);
	void combine(Elements*);
};
#endif


