#include "DTW.h"

Dynamic_Time_Warping::Dynamic_Time_Warping(int* x, int* y, int M, int N)
{
	this->M = M;
	this->N = N;
	this->X = new int[this->M];
	this->Y = new int[this->N];

	for (int i = 0; i < this->M; i++)
		this->X[i] = x[i];

	for (int i = 0; i < this->N; i++)
		this->Y[i] = y[i];

	this->DTW = new float*[this->M];
	for (int h = 0; h < this->M; h++)
	{
		this->DTW[h] = new float[this->N];
		for (int w = 0; w < this->N; w++)
			this->DTW[h][w] = -1;//infinity
	}
}

float Dynamic_Time_Warping::minimum(float insertion, float deletion, float match)
{
	return (insertion > deletion) ? (deletion > match) ? match : deletion : (insertion > match) ? match : insertion;
}

float Dynamic_Time_Warping::max(int a, int b)
{
	return (a > b) ? a : b;
}

float Dynamic_Time_Warping::min(int a, int b)
{
	return (a > b) ? b : a;
}

float Dynamic_Time_Warping::DTWDistance() {
	this->DTW[0][0] = pow(this->X[0] - this->Y[0], 2);
	//
	for (int h = 1; h < this->M; h++)
		this->DTW[h][0] = this->DTW[h - 1][0] + pow(this->X[h] - this->Y[0], 2);
	//
	for (int w = 1; w < N; w++)
		this->DTW[0][w] = this->DTW[0][w - 1] + pow(this->X[0] - this->Y[w], 2);
	//
	float cost;
	for (int h = 1; h < this->M; h++)
		for (int w = 1; w < this->N; w++)
		{
			cost = pow(this->X[h] - this->Y[w], 2);
			this->DTW[h][w] = cost + minimum(this->DTW[h - 1][w],
				this->DTW[h][w - 1],
				this->DTW[h - 1][w - 1]);
		}

	/*cout << "Result: \n";
	for (int h = 0; h < this->M; h++)
	{
		for (int w = 0; w < this->N; w++)
			cout << this->DTW[h][w] << "  ";
		cout << "\n";
	}*/

	return (float)(this->DTW[M - 1][N - 1]);
}

float Dynamic_Time_Warping::DTWDistance_GPC(int r) {
	r = this->max(r,abs(this->N - this->M));
	//
	this->DTW[0][0] = pow(this->X[0] - this->Y[0], 2);
	//
	for (int h = 1; h < this->M; h++)
		this->DTW[h][0] = this->DTW[h - 1][0] + pow(this->X[h] - this->Y[0], 2);
	//
	for (int w = 1; w < this->N; w++)
		this->DTW[0][w] = this->DTW[0][w - 1] + pow(this->X[0] - this->Y[w], 2);
	//
	float cost;
	for (int h = 1; h < this->M; h++)
		for (int w = this->max(1, h - r); w < this->min(this->N, h + r); w++)
		{
			cost = pow(X[h] - Y[w], 2);
			this->DTW[h][w] = cost + this->minimum(this->DTW[h - 1][w],
				this->DTW[h][w - 1],
				this->DTW[h - 1][w - 1]);
		}

	//cout << "Result: \n";
	//for (int h = 0; h < this->M; h++)
	//{
	//	for (int w = 0; w < this->N; w++)
	//		cout << this->DTW[h][w] << "  ";
	//	cout << "\n";
	//}

	return (float)(this->DTW[M - 1][N - 1]);
}

void Dynamic_Time_Warping::setX(int* x)
{

}

void Dynamic_Time_Warping::setY(int* y)
{
	
}
