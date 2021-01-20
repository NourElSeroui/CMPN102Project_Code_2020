#pragma once
#include "Enemy.h"

//Frosted enemies cannot move or attack castle. Any active enemy can be frosted for some
//time steps(freezing time) due to an attack from the castle

class Frozen_List : public Enemy
{
public:
	Frozen_List(int id, int arrTime, int d = MaxDistance);
	~Frozen_List();
};

/*
A frosted enemy is affected by castle fire but is not affected by castle ice.
A frosted castle cannot attack enemies.
A frosted castle is affected by fighter attacks only. Freezer enemy has no effect on it.
*/