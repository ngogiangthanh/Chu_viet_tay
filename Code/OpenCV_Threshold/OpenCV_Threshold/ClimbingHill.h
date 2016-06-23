#pragma once
#ifndef ClimbingHill_H
#define ClimbingHill_H
#include "Column.h"
class ClimbingHill {
public:
	//f(x) function
	int f(Column current_column, unsigned int index);
	//void dropAnchor();
	//bool goal();
	void move();
};
#endif