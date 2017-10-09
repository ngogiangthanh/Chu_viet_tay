#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Cluster {
private:
	int times;
	string name;
public:
	Cluster();
	int getTimes();
	void addTime(int);

	string getName();
	void setName(string);
};