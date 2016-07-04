#pragma once
#ifndef Element_H
#define Element_H

class Element
{
private: int x, y;
		 bool pre, next;
public:
	Element(int, int);
	void setX(int);
	void setY(int);
	void setPre(bool);
	void setNext(bool);
	int getX();
	int getY();
	bool isPre();
	bool isNext();
};
#endif

