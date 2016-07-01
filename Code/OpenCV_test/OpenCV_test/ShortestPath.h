#pragma once
#ifndef  _ShortestPath_H_
#define _ShortestPath_H_
#include <iostream>
#include <queue>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define THRESHOLD 200

using namespace cv;
using namespace std;
typedef struct State {
	int rows, cols;
};

typedef struct Node {
	State state;
	Node *parent;
	float h, g;
};
class ShortestPath
{
private:
	Mat data;
	cv::Size size;
	int x_goal, y_goal;
public:
	ShortestPath(Mat);
	void setData(Mat);
	Mat getData();
	void setX_goal(int);
	void setY_goal(int);
	int getX_goal();
	int getY_goal();
	float HeuristicEstimate(State, State);
	Node* min(vector<Node*>&);
	bool Move(State, State &, int);
	bool equals(State, State);
	int Contains(const vector<Node*>, const State&);
	void init(State&, State&);
	Node* Astar(State, State);
};

#endif // ! _ShortestPath_H_