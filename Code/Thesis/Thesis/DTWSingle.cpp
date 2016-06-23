#include <iostream>
#include <cmath>
#include "DTWSingle.h"

using namespace std;
template<class T, size_t N>
size_t size(T(&)[N]) { return N; }
/*
int DTWDistance(s: array [1..n], t: array [1..m]) {
DTW := array [0..n, 0..m]

for i := 1 to n
DTW[i, 0] := infinity
for i := 1 to m
DTW[0, i] := infinity
DTW[0, 0] := 0

for i := 1 to n
for j := 1 to m
cost:= d(s[i], t[j])
DTW[i, j] := cost + minimum(DTW[i-1, j  ],    // insertion
DTW[i  , j-1],    // deletion
DTW[i-1, j-1])    // match

return DTW[n, m]
}
*/

float minimum(float insertion, float deletion, float match)
{
	return (insertion > deletion) ? (deletion > match) ? match : deletion : (insertion > match) ? match : insertion;
}

void DTWDistance(float X[], float Y[], int M, int N) {
	float** DTW = 0;

	DTW = new float*[M];
	for (int h = 0; h < M; h++)
	{
		DTW[h] = new float[N];
		for (int w = 0; w < N; w++)
			DTW[h][w] = 0;
	}
	DTW[0][0] = pow(X[0] - Y[0], 2);

	for (int h = 1; h < M; h++)
		DTW[h][0] = DTW[h - 1][0] + pow(X[h] - Y[0], 2);

	for (int w = 1; w < N; w++)
		DTW[0][w] = DTW[0][w - 1] + pow(X[0] - Y[w], 2);

	float cost;
	for (int h = 1; h < M; h++)
		for (int w = 1; w < N; w++)
		{
			cost = pow(X[h - 1] - Y[w - 1], 2);
			DTW[h][w] = cost + minimum(DTW[h - 1][w],
				DTW[h][w - 1],
				DTW[h - 1][w - 1]);
		}

	cout << "Result: \n";
	for (int h = 0; h < M; h++)
	{
		for (int w = 0; w < N; w++)
			cout << DTW[h][w] << "  ";
		cout << "\n";
	}

}

//int main()
//{
//	float a[] = {1,2,2};
//	float b[] = {1,2,3};
//    int height = (sizeof(a)/sizeof(*a));
//    int width = (sizeof(b)/sizeof(*b));
//	DTWDistance(a,b,height,width);
//	
//	return 0;
//}
