#pragma once
#ifndef  _DTW_H_
#define _DTW_H_
#include <iostream>
#include <cmath>

using namespace std;

template<class T, size_t N>
size_t size(T(&)[N]) { return N; }

class Dynamic_Time_Warping
{
private:
	float** DTW; //results matrix
	int* X; //vector X
	int* Y; //vector Y
	int M, N; //length of X,Y
public:
	Dynamic_Time_Warping(int*, int*, int, int);
	float minimum(float, float, float);
	float max(int, int);
	float min(int, int);
	float DTWDistance();
	float DTWDistance_GPC(int);
	void setX(int*);
	void setY(int*);
};
#endif // ! _DTW_H_


