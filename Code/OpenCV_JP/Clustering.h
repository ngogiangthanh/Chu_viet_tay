#pragma once
#include <iostream>
#include <vector>
#include "Cluster.h"
#include <string>

using namespace std;

class Clustering {
private:
	vector<Cluster> clusters;
	string cluster_name;
public:
	Clustering(string);
	void addCluster(string);
	string getClusterName();
	string printClusterChild();
	vector<Cluster> getClusters();
};