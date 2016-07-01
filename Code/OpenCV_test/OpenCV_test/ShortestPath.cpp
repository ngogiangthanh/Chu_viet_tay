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
	this->x_goal = x;
}

void ShortestPath::setY_goal(int y)
{
	this->y_goal = y;
}

int ShortestPath::getX_goal()
{
	return this->x_goal;
}

int ShortestPath::getY_goal()
{
	return this->y_goal;
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

void ShortestPath::init(State & S, State &Goal)
{
	S.cols = 8;
	S.rows = 59;

	Goal.cols = this->x_goal;
	Goal.rows = this->y_goal;
}

Node * ShortestPath::Astar(State start, State goal)
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
		if (node->state.rows == this->y_goal && node->state.cols == this->x_goal)
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
