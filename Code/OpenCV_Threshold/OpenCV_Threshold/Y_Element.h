#pragma once
class Y_Element
{
private:
	int curr_val;
	int MAF_val;
	int y_coordinate;
public: Y_Element(int, int);
		Y_Element(int, int, int);
		void setCurr_Val(int);
		void setMAF_Val(int);
		void setY_Coordinate(int);
		int getCurr_Val();
		int getMAF_Val();
		int getY_Coordinate();
};
