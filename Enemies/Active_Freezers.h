#pragma once
#include "Enemy.h"
#include "..\Castle\Castle.h"

//Active Enemy: is an enemy with Arrival Time ≤ current time step & Health > 0
//Freezer can throw ice on the castle to frost it for some time.
class Active_Freezers : public Enemy
{
private:
	int CurrentHealth;
	//int CurrentSpeed; //they are protected in enemy.h
	//int freezetime;
	//int Distance;
public:
	Active_Freezers(int id, int arrTime, int d = MaxDistance);
	~Active_Freezers();

	void DamageToEnemy(int castlefirepower);
	bool IsitTimeToShot();

	void Move();	//All enemies can move
	void Act(Castle* C);	//Acting means fighting or healing

	void SetCurrentHealth(double CH);
	double GetCurrentHealth();
	//int TimeToShot();
	//void SetCurrentHealth(int CH);
	//int GetCurrentHealth() const;
	//void SetDistance(int);
	//int GetDistance() const;
	/*void SetCurrentSpeed(int CS);
	int GetCurrentSpeed() const;*/
	//void SingleShot();//logic for act function
};