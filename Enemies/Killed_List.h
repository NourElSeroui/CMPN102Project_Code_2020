#pragma once
#include "Enemy.h"

class Killed_List : public Enemy
{
public:
	Killed_List(int id, int arrTime, int d = MaxDistance);
	~Killed_List();
};