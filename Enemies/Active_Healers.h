#pragma once
#include "Enemy.h"
//Active Enemy: is an enemy with Arrival Time ≤ current time step & Health > 0
//Healer can heal other enemiesand does not attack castle.
class Active_Healers : public Enemy
{
private:
	//static const int k = 2;
	int CurrentHealth;
	//int CurrentSpeed;
	double heal;
	//int Distance;
public:
	Active_Healers(int id, int arrTime, int d = MaxDistance);
	//Active_Healers(int CH, int id, int arrTime, int EH, int EP, int S, int RT, int d = MaxDistance);

	~Active_Healers();
	void DamageToEnemy(int castlefirepower);
	void SetHeal(int HH);
	int GetHeal() const;
	//healer heal enemys
	void Act(Enemy* E);	//Acting means fighting or healing
	void Move();	//All enemies can move
	int Act2(Enemy* E);
	//void SetCurrentHealth(int CH);
	//int GetCurrentHealth() const;
	void SetCurrentHealth(double CH);
	double GetCurrentHealth();
	//void SetDistance(int);
	//int GetDistance() const;
	/*void SetCurrentSpeed(int CS);
	int GetCurrentSpeed() const;
	double GetDamage() const;
	void ReduceSpeedtoHalf();
	*/
};