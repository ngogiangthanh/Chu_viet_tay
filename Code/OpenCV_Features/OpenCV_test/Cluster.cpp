#include "Cluster.h"

Cluster::Cluster(int id_cluster, CPoint point)
{
	this->id_cluster = id_cluster;

	int total_values = point.getTotalValues();

	for (int i = 0; i < total_values; i++)
		central_values.push_back(point.getValue(i));

	this->points.push_back(point);
}

void Cluster::addPoint(CPoint point)
{
	this->points.push_back(point);
}

bool Cluster::removePoint(int id_point)
{
	int total_points = this->points.size();

	for (int i = 0; i < total_points; i++)
	{
		if (this->points[i].getID() == id_point)
		{
			this->points.erase(this->points.begin() + i);
			return true;
		}
	}
	return false;
}

float Cluster::getCentralValue(int index)
{
	return this->central_values[index];
}

vector<float> Cluster::getCentralValues()
{
	int size = central_values.size();
	cout << "Size cluster = " << size << endl;
	//for (int i = 0; i < size; i++)
	//	cout << central_values[i] << " ";
	//cout << endl;
	return this->central_values;
}

void Cluster::setCentralValue(int index, float value)
{
	this->central_values[index] = value;
}

CPoint Cluster::getPoint(int index)
{
	return this->points[index];
}

int Cluster::getTotalPoints()
{
	return this->points.size();
}

int Cluster::getID()
{
	return this->id_cluster;
}
