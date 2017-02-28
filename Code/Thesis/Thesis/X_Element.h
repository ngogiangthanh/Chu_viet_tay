#pragma once
class X_Element
{
private:
	int curr_val;
	int MAF_val;
	int x_coordinate;
public: X_Element(int, int);
		X_Element(int, int, int);
		void setCurr_Val(int);
		void setMAF_Val(int);
		void setX_Coordinate(int);
		int getCurr_Val();
		int getMAF_Val();
		int getX_Coordinate();
};
