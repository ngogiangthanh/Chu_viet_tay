#include "ShortestPath.h"

ShortestPath::ShortestPath(Mat src)
{
	this->data = src.clone();
	this->size = this->data.size();
}

void ShortestPath::setData(Mat src)
{
	this->data = src.clone();
}

Mat ShortestPath::getData()
{
	return this->data;
}

void ShortestPath::setX_goal(int x)
{
	this->x_end = x;
}

void ShortestPath::setY_goal(int y)
{
	this->y_end = y;
}

void ShortestPath::setX_start(int x)
{
	this->x_start = x;
}

void ShortestPath::setY_start(int y)
{
	this->y_start = y;
}

int ShortestPath::getX_goal()
{
	return this->x_end;
}

int ShortestPath::getY_goal()
{
	return this->y_end;
}

int ShortestPath::getX_start()
{
	return this->x_start;
}

int ShortestPath::getY_start()
{
	return this->y_start;
}

State ShortestPath::getStart()
{
	return this->start;
}

State ShortestPath::getGoal()
{
	return this->goal;
}

float ShortestPath::HeuristicEstimate(State A, State Goal)
{
	return abs(A.rows - Goal.rows) + abs(A.cols - Goal.cols);
}

Node * ShortestPath::min(vector<Node*>& frontier)
{
	int size = frontier.size();
	int min = 0;
	for (int i = 1; i < size; i++) {
		if (frontier[min]->h + frontier[min]->g > frontier[i]->h + frontier[i]->g)
			min = i;
	}
	Node* node = frontier[min];
	frontier.erase(frontier.begin() + min);
	return node;
}

bool ShortestPath::Move(State A, State & B, int action)
{
	cv::Scalar intensity;

	switch (action) {
	case UP:
		if (A.rows - 1 < 0)
			return false;
		intensity = this->data.at<uchar>(A.rows - 1, A.cols);
		if (intensity[0] <= THRESHOLD)
			return false;
		else
			A.rows--;
		break;
	case DOWN:
		if (A.rows + 1 > size.height - 1)
			return false;
		intensity = this->data.at<uchar>(A.rows + 1, A.cols);
		if (intensity[0] <= THRESHOLD)
			return false;
		else
			A.rows++;
		break;
	case LEFT:
		if (A.cols - 1 < 0)
			return false;

		intensity = this->data.at<uchar>(A.rows, A.cols - 1);
		if (intensity[0] <= THRESHOLD)
			return false;
		else
			A.cols--;
		break;
	case RIGHT:
		if (A.cols + 1 > size.width - 1)
			return false;
		intensity = this->data.at<uchar>(A.rows, A.cols + 1);
		if (intensity[0] <= THRESHOLD)
			return false;
		else
			A.cols++;
		break;
	}
	B.rows = A.rows;
	B.cols = A.cols;
	return true;
}

bool ShortestPath::equals(State A, State B)
{
	return A.rows == B.rows && A.cols == B.cols;
}

int ShortestPath::Contains(const vector<Node*> q, const State& S)
{
	int size = q.size();
	for (int i = 0; i < size; i++)
		if (this->equals(q[i]->state, S))
			return i;
	return -1;
}

void ShortestPath::init()
{
	this->start.cols = this->x_start;
	this->start.rows = this->y_start;

	this->goal.cols = this->x_end;
	this->goal.rows = this->y_end;
}

Node * ShortestPath::Astar()
{
	Node* root = new Node;
	root->state = start;
	root->h = 0;
	root->g = 0;
	root->parent = 0;
	vector<Node*> frontier, explored;
	frontier.push_back(root);

	while (!frontier.empty()) {
		Node* node = min(frontier);
		if (node->state.rows == this->y_end && node->state.cols == this->x_end)
			return node;
		explored.push_back(node);

		State new_state;
		for (int i = 0; i < 4; i++) {
			if (Move(node->state, new_state, i))
			{
				Node* new_node = new Node;
				new_node->state = new_state;
				new_node->g = node->g + 1;
				new_node->h = HeuristicEstimate(new_node->state, goal);
				new_node->parent = node;
				int indexfrontier = Contains(frontier, new_node->state);
				if (indexfrontier != -1)
				{
					if (new_node->g < frontier[indexfrontier]->g)
					{
						frontier[indexfrontier]->g = new_node->g;
						frontier[indexfrontier]->parent = node;
					}
				}
				else {
					int indexexplored = Contains(explored, new_node->state);
					if (indexexplored == -1)
						frontier.push_back(new_node);
					else if (new_node->g < explored[indexexplored]->g) {
						explored[indexexplored]->g = new_node->g;
						explored[indexexplored]->parent = node;
						frontier.push_back(explored[indexexplored]);
						explored.erase(explored.begin() + indexexplored);
					}
				}
			}
		}
	}
	return 0;
}

Elements* ShortestPath::print(Node* X, Mat& rs, int x, int y)
{
	vector<Node*> results;
	Elements* elements = new Elements();
	while (X != 0)
	{
		results.push_back(X);
		X = X->parent;
	}

	int size = results.size();
	int i;
	rs.convertTo(rs, CV_8UC1);
	for (i = size - 1; i >= 0; i--)
	{
		rs.at<uchar>(y + results[i]->state.rows, x + results[i]->state.cols) = 200;
		elements->add(new Element(x + results[i]->state.cols, y + results[i]->state.rows));
	}

	return elements;
}
