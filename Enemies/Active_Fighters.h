#pragma once
#include "Enemy.h"
#include "..\Castle\Castle.h"

//Active Enemy: is an enemy with Arrival Time ≤ current time step & Health > 0
//Fighter can attack castle and cause damage to castle.
class Active_Fighters :public Enemy
{
private:
	double CurrentHealth;
	double fighterfirepower;
	//double fighterSpeed;  //in document they say:in game rules every enemy has its own speed and its own firepower?!
	//static const int k = 1;
	//double DamageE;
	//int Distance;
public:
	//Active_Fighters(int CH, int id, int arrTime, int EH, int EP, int S, int RT,int d = MaxDistance);
	Active_Fighters(int id, int arrTime, int d = MaxDistance);
	~Active_Fighters();
	void DamageToEnemy(int castlefirepower);

	void Setfighterfirepower(double fp);
	double Getfighterfirepower() const;

	void Act(Castle *C);	//Acting means fighting or healing
	void Move();

	void SetCurrentHealth(double CH);
	double GetCurrentHealth() ;
	int priority();
	//void SetDistance(int) ;
	// int GetDistance() const;
	//void SetCurrentSpeed(int CS);
	//int GetCurrentSpeed() const;
	//double GetDamage() const;
	//void SetfighterSpeed(double fs);
	//double GetfighterSpeed() const;
};