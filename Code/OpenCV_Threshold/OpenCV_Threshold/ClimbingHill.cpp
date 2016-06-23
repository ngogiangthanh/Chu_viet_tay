#include "ClimbingHill.h"

int ClimbingHill::f(Column current_column, unsigned int index)
{
	vector<Element>* find_range = current_column.getElements();
	vector<Element>::iterator it = (*find_range).begin();
	for (; it != (*find_range).end(); ++it)
	{
		if (it->getY() == index) {
			return it->getIntensity();//Trả về gía trị Intensity của current_column tại vị trí index
		}
	}
	return -1;//Không tồn tại index trong current_column
}
