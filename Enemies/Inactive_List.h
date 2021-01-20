#pragma once
#include "Enemy.h"

class Inactive_List :public Enemy
{
public:
	Inactive_List(int id, int arrTime, int d = MaxDistance);
	~Inactive_List();
};