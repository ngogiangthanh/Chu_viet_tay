#include "CPoint.h"

CPoint::CPoint(int id_point, vector<float>& values, string name)
{
	this->id_point = id_point;
	this->total_values = values.size();

	for (int i = 0; i < this->total_values; i++)
		this->values.push_back(values[i]);

	this->name = name;
	this->id_cluster = -1;
}

int CPoint::getID()
{
	return this->id_point;
}

void CPoint::setCluster(int id_cluster)
{
	this->id_cluster = id_cluster;
}

void CPoint::setValues(vector<float> vals)
{
	this->values.clear();
	this->values = vals;
}

int CPoint::getCluster()
{
	return this->id_cluster;
}

float CPoint::getValue(int index)
{
	return this->values[index];
}

int CPoint::getTotalValues()
{
	return this->total_values;
}

void CPoint::addValue(float value)
{
	this->values.push_back(value);
}

string CPoint::getName()
{
	return this->name;
}

vector<float> CPoint::getValues()
{
	int size = values.size();
	cout << "Size cpoint = " << size << endl;
	/*
	for (int i = 0; i < size; i++)
		cout << values[i] << " ";
	cout << endl;*/
	return this->values;
}
