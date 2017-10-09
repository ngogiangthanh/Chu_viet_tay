#include "Entropy.h"

Entropy::Entropy()
{
	this->n_i = 0;
	this->n = 0;
	this->columns.clear();
}

void Entropy::setN(int N)
{
	this->n = N;
}

void Entropy::addNi(int n)
{
	this->n_i += n;
}

void Entropy::addColumn(int colVal)
{
	this->columns.push_back(colVal);
}

double Entropy::getEntropy()
{
	int size = this->columns.size();
	double entropy = 0;
	double logVal = 0;

	for (int i = 0; i < size; i++) {
		double el = (double)this->columns.at(i);
		if(el > 0)
			logVal += -(el / this->n_i) * log2(el / this->n_i);
	}
	entropy = (this->n_i*logVal /this->n);

	return entropy;
}

int Entropy::getN()
{
	return this->n;
}

int Entropy::getNi()
{
	return this->n_i;
}


