#pragma once
#include <iostream>
#include <vector>
#include "CPoint.h"

using namespace std;

class Cluster
{
private:
	int id_cluster;
	vector<float> central_values;
	vector<CPoint> points;

public:
	Cluster(int id_cluster, CPoint point);

	void addPoint(CPoint point);

	bool removePoint(int id_point);

	float getCentralValue(int index);

	vector<float> getCentralValues();

	void setCentralValue(int index, float value);

	CPoint getPoint(int index);

	int getTotalPoints();

	int getID();
};