#pragma once
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

class Entropy {
private:
	vector<int> columns;
	int n, n_i;
public:
	Entropy();
	void setN(int);
	void addNi(int);
	void addColumn(int);
	double getEntropy();
	int getN();
	int getNi();
};