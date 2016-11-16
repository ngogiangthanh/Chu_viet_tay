#pragma once
#ifndef  _DrawDecision_H_
#define _DrawDecision_H_
#define UP_UP 1
#define UP_DOWN 2
#define DOWN_DOWN 3
#define THROUGH 4
#include <iostream>
#include <stdio.h>

using namespace std;

class DrawDecision
{
	private:
		int y_u, y_d;
		int y_curr_valley;
		int y_pre_valley;
		int y_next_valley;
	public:
		DrawDecision();
		void setYu(int);
		void setYd(int);
		void setYCurrValley(int);
		void setYPreValley(int);
		void setYNextValley(int);
		int distance(int, int);
		int getYu();
		int getYd();
		int getYCurrValley();
		int getYPreValley();
		int getYNextValley();
		int decision();
		bool isLinesOverride();
};

#endif // ! _DrawLine_H_
