#pragma once
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


