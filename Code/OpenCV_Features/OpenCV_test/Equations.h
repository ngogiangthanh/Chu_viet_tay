#pragma once
#ifndef  _Equations_H_
#include <iostream>
#include <cmath>

using namespace std;

class Equations
{
private:
	int a1, b1, c1, a2, b2, c2;
	float x, y;
public:
	Equations(int, int, int, int, int, int);
	void solve();
	float getX();
	float getY();
};
#endif // ! _DTW_H_
#define _Equations_H_


