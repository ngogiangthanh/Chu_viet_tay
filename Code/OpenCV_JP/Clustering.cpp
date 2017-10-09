#include "Clustering.h"

Clustering::Clustering(string name)
{
	this->cluster_name = name;
}

void Clustering::addCluster(string name)
{
	int size = this->clusters.size();
	bool isExist = false;
	for (int i = 0; i < size; i++) {
		if (this->clusters[i].getName() == name) {
			this->clusters[i].addTime(1);
			isExist = true;
		}
	}
	if (!isExist) {
		Cluster clus;
		clus.setName(name);
		clus.addTime(1);
		this->clusters.push_back(clus);
	}
}

string Clustering::getClusterName()
{
	return this->cluster_name;
}

string Clustering::printClusterChild()
{
	int size = this->clusters.size();
	string content = "";
	for (int i = 0; i < size; i++) {
		content += this->clusters[i].getName() + " " + std::to_string(this->clusters[i].getTimes()) + "	";
	}
	return content;
}

vector<Cluster> Clustering::getClusters()
{
	return this->clusters;
}
