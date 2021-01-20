#include "Killed_List.h"

Killed_List::Killed_List(int id, int arrTime, int d) : Enemy(id, arrTime, d)
{
	status = KILD;
}
Killed_List::~Killed_List(){}