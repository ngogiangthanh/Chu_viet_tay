#pragma once
class Word_Element
{
private:
	int x_begin;
	int x_end;
public: 
		Word_Element();
		Word_Element(int, int);
		void setX_Begin(int);
		void setX_End(int);
		int getX_Begin();
		int getX_End();
		int getX_Middle_Coordinate();
		int get_Distance();
};