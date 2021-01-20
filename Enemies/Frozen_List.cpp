#include "Frozen_List.h"

Frozen_List::Frozen_List(int id, int arrTime, int d) : Enemy(id, arrTime, d)
{
	status = FRST;
}
Frozen_List::~Frozen_List() {}