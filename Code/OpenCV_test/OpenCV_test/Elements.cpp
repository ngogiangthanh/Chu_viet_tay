#include "Elements.h"

Elements::Elements()
{
}

void Elements::setElements(vector<Element*> els)
{
	this->elements.clear();
	this->elements = els;
}

vector<Element*> Elements::getElements()
{
	return this->elements;
}

void Elements::add(Element* el)
{
	(elements).push_back(el);
}

void Elements::combine(Elements* els)
{
	vector<Element*> el = els->getElements();
	int size = el.size();
	for (vector<int>::size_type i = 0; i != size; i++) {
		this->elements.push_back(el[i]);
	}
}
