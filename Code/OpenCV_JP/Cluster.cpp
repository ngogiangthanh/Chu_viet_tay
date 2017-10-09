#include "Cluster.h"

Cluster::Cluster()
{
	this->times = 0;
	this->name = "";
}

int Cluster::getTimes()
{
	return this->times;
}

void Cluster::addTime(int time = 1)
{
	this->times += time;
}

string Cluster::getName()
{
	return this->name;
}

void Cluster::setName(string name)
{
	this->name = name;
}
