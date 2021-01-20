#include "Inactive_List.h"

Inactive_List::Inactive_List(int id, int arrTime, int d) : Enemy(id, arrTime, d)
{
	status = INAC;
}
Inactive_List::~Inactive_List(){}