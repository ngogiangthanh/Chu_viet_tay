#pragma once
#include <iostream>
#include <vector>

using namespace std;
class CPoint
{
private:
	int id_point, id_cluster;
	vector<float> values;
	int total_values;
	string name;

public:
	CPoint(int id_point, vector<float>& values, string name = "");

	int getID();

	void setCluster(int id_cluster);

	void setValues(vector<float> values);

	int getCluster();

	float getValue(int index);

	int getTotalValues();

	void addValue(float value);

	string getName();

	vector<float> getValues();
};