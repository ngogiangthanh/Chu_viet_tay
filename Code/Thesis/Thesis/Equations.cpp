#include "Equations.h"

Equations::Equations(int a1, int b1, int c1, int a2, int b2, int c2)
{
	this->a1 = a1;
	this->b1 = b1;
	this->c1 = c1;
	this->a2 = a2;
	this->b2 = b2;
	this->c2 = c2;
}

void Equations::solve()
{
	if ((this->a1*this->a1) + (this->b1*this->b1) != 0 && (this->a2*this->a2) + (this->b2*this->b2) != 0)
	{
		float D = this->a1*this->b2 - this->a2*this->b1;
		float Dx = this->c1*this->b2 - this->c2*this->b1;
		float Dy = this->a1*this->c2 - this->a2*this->c1;

		if (D != 0) {
			this->x = Dx / D;
			this->y = Dy / D;
			//printf("\nThere is one solution: x= %3.2f and y= %3.2f\n", Dx / D, Dy / D);
		}
		else if (D == 0)
		{
			if (Dx != 0 && Dy != 0)
				cout << "No solution" << endl;
			else if (Dx == 0 && Dy == 0)
				cout << "infinite solution" << endl;
		}
	}
}

float Equations::getX()
{
	return this->x;
}

float Equations::getY()
{
	return this->y;
}