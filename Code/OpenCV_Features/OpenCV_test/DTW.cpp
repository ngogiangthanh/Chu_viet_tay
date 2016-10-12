#include "DTW.h"

Dynamic_Time_Warping::Dynamic_Time_Warping(float* x, float* y, int M, int N)
{
	this->M = M;
	this->N = N;
	this->X = new float[this->M];
	this->Y = new float[this->N];

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
	return (insertion > deletion) ? ((deletion >= match) ? match : deletion) : ((insertion >= match) ? match : insertion);
}

float Dynamic_Time_Warping::max(float a, float b)
{
	return (a > b) ? a : b;
}

float Dynamic_Time_Warping::min(float a, float b)
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
	
	return this->DTW[this->M - 1][this->N - 1] / this->pathWarping();
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

	cout << "Result: \n";
	for (int h = 0; h < this->M; h++)
	{
		for (int w = 0; w < this->N; w++)
			cout << this->DTW[h][w] << "  ";
		cout << "\n";
	}

	return this->DTW[this->M - 1][this->N - 1] / this->pathWarping();
}

int Dynamic_Time_Warping::pathWarping()
{
	int M_temp = this->M - 1;
	int N_temp = this->N - 1;
	float insertion = 0;//insertion
	float deletion = 0;//deletion
	float match = 0;//matching
	int length_K = 0;
	//cout << "Path warping: ";
	while (true)
	{
		//cout << " [" << M_temp << "][" << N_temp << "] -";
		length_K++;
		//
		insertion = (float) this->DTW[(M_temp - 1 < 0) ? 0 : (M_temp - 1)][N_temp];//insertion
		deletion = (float) this->DTW[M_temp][(N_temp - 1 < 0) ? 0 : (N_temp - 1)];//deletion
		match = (float) this->DTW[(M_temp - 1 < 0) ? 0 : (M_temp - 1)][(N_temp - 1 < 0) ? 0 : (N_temp - 1)];//matching
		if (insertion > deletion) {
			if (deletion >= match) {
				M_temp = (M_temp - 1 < 0) ? 0 : (M_temp - 1);//match 
				N_temp = (N_temp - 1 < 0) ? 0 : (N_temp - 1);//match 
			}
			else
				N_temp = (N_temp - 1 < 0) ? 0 : (N_temp - 1);//deletion 
		}
		else
		{
			if (insertion >= match) {
				M_temp = (M_temp - 1 < 0) ? 0 : (M_temp - 1);//match 
				N_temp = (N_temp - 1 < 0) ? 0 : (N_temp - 1);//match 
			}
			else
				M_temp = (M_temp - 1 < 0) ? 0 : (M_temp - 1);//insertion 
		}

		//stop condition
		if (M_temp == 0 & N_temp == 0)
		{
			//cout << " [" << M_temp << "][" << N_temp << "]" << endl;
			length_K++;
			break;
		}
	}
	return length_K;
}
