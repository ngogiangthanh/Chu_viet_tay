#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "Cluster.h"
#include "CPoint.h"
#include <stdlib.h>
#include "DTW.h"

using namespace std;
class KMeans
{
private:
	int K; // number of clusters
	int total_values, total_points, max_iterations;
	vector<Cluster> clusters;

	// return ID of nearest center (uses DTW)
	int getIDNearestCenter(CPoint point);

public:
	KMeans(int K, int total_points, int total_values, int max_iterations);
	void run(vector<CPoint> points);
};