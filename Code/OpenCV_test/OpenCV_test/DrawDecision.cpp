#include "DrawDecision.h"

DrawDecision::DrawDecision()
{
}

void DrawDecision::setYu(int y_u)
{
	this->y_u = y_u;
}

void DrawDecision::setYd(int y_d)
{
	this->y_d = y_d;
}

void DrawDecision::setYCurrValley(int y_curr_valley)
{
	this->y_curr_valley = y_curr_valley;
}

void DrawDecision::setYPreValley(int y_pre_valley)
{
	this->y_pre_valley = y_pre_valley;
}

void DrawDecision::setYNextValley(int y_next_valley)
{
	this->y_next_valley = y_next_valley;
}

int DrawDecision::distance(int a, int b)
{
	return abs(a - b);
}

int DrawDecision::getYu()
{
	return this->y_u;
}

int DrawDecision::getYd()
{
	return this->y_d;
}

int DrawDecision::getYCurrValley()
{
	return this->y_curr_valley;
}

int DrawDecision::getYPreValley()
{
	return this->y_pre_valley;
}

int DrawDecision::getYNextValley()
{
	return this->y_next_valley;
}

int DrawDecision::decision()
{
	if(!this->isLinesOverride())
		if (this->distance(this->y_u, this->y_curr_valley) > this->distance(this->y_u, this->y_pre_valley))
			if (this->distance(this->y_d, this->y_curr_valley) > this->distance(this->y_d, this->y_next_valley))
				return UP_DOWN;
			else
				return DOWN_DOWN;
		else
			if (this->distance(this->y_d, this->y_curr_valley) > this->distance(this->y_d, this->y_next_valley))
				return UP_DOWN;
			else
				return UP_UP;
	else
		return THROUGH;
}

bool DrawDecision::isLinesOverride()
{
	return (this->distance(this->y_u, this->y_curr_valley) > this->distance(this->y_u, this->y_pre_valley) &
		this->distance(this->y_d, this->y_curr_valley) > this->distance(this->y_d, this->y_next_valley));
}