#include "DTW.h"

Dynamic_Time_Warping::Dynamic_Time_Warping(vector<float> x, vector<float> y)
{
	this->M = x.size();
	this->N = y.size();
	this->X = x;
	this->Y = y;

	cout << endl;

	this->DTW = new float*[this->M];
	for (int h = 0; h < this->M; h++)
	{
		this->DTW[h] = new float[this->N];
		for (int w = 0; w < this->N; w++)
			this->DTW[h][w] = infinity;
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
	}
	*/
	return this->DTW[this->M - 1][this->N - 1] / this->pathWarping();
}

float Dynamic_Time_Warping::DTWDistance_GPC(int r) {
	Equations equation_line_up(this->N, 1, this->M - r, r, 1, 0);
	//Equations equation_line_up(r, 1, 0, this->N, 1, this->M - r);
	equation_line_up.solve();
	Equations equation_line_down(this->N - r, 1, this->M, 0, 1, r);
	//Equations equation_line_down(0, 1, r,this->N - r, 1, this->M);
	equation_line_down.solve();
	//verifying
	r = min(r, min(this->M, this->N));
	//init zero point
	this->DTW[0][0] = pow(this->X[0] - this->Y[0], 2);
	//init height
	for (int h = 1; h <= r; h++)
		this->DTW[h][0] = this->DTW[h - 1][0] + pow(this->X[h] - this->Y[0], 2);
	//init width
	for (int w = 1; w <= r; w++)
		this->DTW[0][w] = this->DTW[0][w - 1] + pow(this->X[0] - this->Y[w], 2);
	//calculating
	float cost;
	for (int i = 1; i < this->N; i++)
	{
		int up = ceil(equation_line_up.getX() * i + equation_line_up.getY()) < 1 ? 1 : ceil(equation_line_up.getX() * i + equation_line_up.getY());
		int down = ceil(equation_line_down.getX() * i + equation_line_down.getY()) >= this->M ? this->M - 1 : ceil(equation_line_down.getX() * i + equation_line_down.getY());
		for (int k = up; k <= down; k++) {
			cost = pow(X[k] - Y[i], 2);
			this->DTW[k][i] = cost + this->minimum(this->DTW[k - 1][i],
				this->DTW[k][i - 1],
				this->DTW[k - 1][i - 1]);
		}
	}

	//cout << "Result: \n";
	//for (int h = 0; h < this->M; h++)
	//{
	//	for (int w = 0; w < this->N; w++)
	//		cout << this->DTW[h][w] << "  ";
	//	cout << "\n";
	//}
	
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
		cv::line(this->draw, Point(M_temp, round(this->X[M_temp] * 99)), Point(this->draw.cols/2 + N_temp, 100 + round(this->Y[N_temp] * 99)), Scalar(128, 128, 128));
		//cout << " [" << M_temp << "][" << N_temp << "] -";
		length_K++;
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


	//Show
	/*imshow("Word drawMatching", this->draw);
	imwrite("D:/drawMatching.jpg", this->draw);*/
	return length_K;
}

void Dynamic_Time_Warping::drawMatching()
{
	int cols = 2*((this->M > this->N) ? this->M : this->N);
	int rows = 200;
	this->draw = Mat(rows, cols, CV_8UC3, Scalar(255, 255, 255));

	for (int i = 0; i < this->M - 1; i++)
		cv::line(this->draw, Point(i, this->X[i] * 99), Point(i, this->X[i+1] * 99), Scalar(0, 0, 0));
	for (int i = 0; i < this->N - 1; i++)
		cv::line(this->draw, Point(cols/2 + i, 100 + this->Y[i] * 99), Point(cols / 2 + i, 100 + this->Y[i + 1] * 99), Scalar(0, 0, 0));

}

Mat Dynamic_Time_Warping::getDraw()
{
	return this->draw;
}
