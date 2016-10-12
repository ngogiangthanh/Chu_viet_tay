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
	float* X; //vector X
	float* Y; //vector Y
	int M, N; //length of X,Y
public:
	Dynamic_Time_Warping(float*, float*, int, int);
	float minimum(float, float, float);
	float max(float, float);
	float min(float, float);
	float DTWDistance();
	float DTWDistance_GPC(int);
	int pathWarping();
};
#endif // ! _DTW_H_


