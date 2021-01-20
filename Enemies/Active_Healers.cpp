#include "Active_Healers.h"

Active_Healers::~Active_Healers() {}
Active_Healers::Active_Healers(int id, int arrTime, int d) : Enemy(id, arrTime, d)
{
	Enemytype = HEALER;
	heal = 2;
	//status = ACTV;
	//we need to set heal!!
	//SetCurrentHealth(0);//not 0
}
//Damage to an enemy by a castle bullet
void Active_Healers::DamageToEnemy(int castlefirepower)
{
	double k = 2;
	DamageE = (1.0 / Distance) * castlefirepower * 1.0 / k;
	CurrentHealth = CurrentHealth - DamageE;
	//ReduceSpeedtoHalf(); //check if currenthealth<0.5*health
}
//Healer can heal only enemies that are at most 2 meters ahead in his moving direction.
//Healer cannot heal killed enemies.Healer cannot heal frosted enemies.

// healers increase the health of other enemies
//The formula should depend on healer health, enemy to be healed health, distance between healer and enemy
void Active_Healers::Act(Enemy* E) //Ta2lefy¬nour
{
	//we can send heal as a parameter for this function??!
	//During reload period enemies cannot act(i.e.cannot attack or heal) but can move.Once reload period is over, enemies can act again
	if (E->GetCurrentHealth() < E->GetHealth())
	{
		if (CurrentHealth > E->GetCurrentHealth())
		{
			double h = 0.0;//Distance between healer and enemy
			h = (GetDistance() - E->GetDistance()) * (GetCurrentHealth() - E->GetCurrentHealth());

			h = h + E->GetCurrentHealth();
			E->SetCurrentHealth(h);
		}
		else
			E->SetCurrentHealth(E->GetCurrentHealth() + heal);
	}
}
int Active_Healers::Act2(Enemy* E) //Ta2lefy¬nour
{
	//we can send heal as a parameter for this function??!
	//During reload period enemies cannot act(i.e.cannot attack or heal) but can move.Once reload period is over, enemies can act again
	if (E->GetCurrentHealth() < E->GetHealth())
	{
		if (CurrentHealth > E->GetCurrentHealth())
		{
			int h = 0;//Distance between healer and enemy
			h = (GetDistance() - E->GetDistance()) * (GetCurrentHealth() - E->GetCurrentHealth());

			h = h + E->GetCurrentHealth();
			E->SetCurrentHealth(h);
		}
		else
			E->SetCurrentHealth(E->GetCurrentHealth() + heal);
	}
	return E->GetCurrentHealth();
}
//Enemies can move at their reload period but cannot act. (cannot fire nor heal)
void Active_Healers::Move()
{
	//or just call DecrementDist()
	//if (Distance > MinDistance)
		//Distance--;
	if (Distance == MinDistance)
		Enemyspeed = -Enemyspeed;

	if (CurrentHealth < 0.5 * Health)
			Distance = Distance - 0.5 * Enemyspeed;
	else
		Distance = Distance - Enemyspeed;

	if (Distance <MinDistance)
		Distance = MinDistance;
	if (Distance > MaxDistance)
		Distance = MaxDistance;
	if (Distance == MaxDistance)
		Enemyspeed = -Enemyspeed;
}

void Active_Healers::SetHeal(int HH)
{
	heal = (HH > 0) ? HH: 0;
}
int Active_Healers::GetHeal() const
{
	return heal;
}

void Active_Healers::SetCurrentHealth(double CH) //has logic: firepower reduces the health
{
	if (CH > 0)
		CurrentHealth = CH;
	else
		CurrentHealth = 0;
}
double Active_Healers::GetCurrentHealth()
{
	return CurrentHealth;
}
//void Active_Healers::SetDistance(int d)
//{
//	if (d >= MinDistance && d <= MaxDistance)
//		Distance = d;
//	else if (Distance == 0)
//		Distance = MinDistance;
//	else
//		Distance = MaxDistance;
//}
//int Active_Healers::GetDistance()const
//{
//	return Distance;
//}

//void Active_Healers::SetCurrentHealth(int CH)
//{
//	if (CH > 0)
//		CurrentHealth = CH;
//	else
//		CurrentHealth = 0;
//}
//int Active_Healers::GetCurrentHealth() const
//{
//	return CurrentHealth;
//}
/*
void Active_Healers::SetCurrentSpeed(int CS)
{
	if (CS > 0)
		CurrentSpeed = CS;
	else
		CurrentSpeed = 0;
}
int Active_Healers::GetCurrentSpeed() const
{
	return CurrentSpeed;
}
void Active_Healers::ReduceSpeedtoHalf()
{
	if (CurrentHealth < 0.5 * GetHealth())
		SetCurrentSpeed(0.5 * GetEnemy_speed());
}*/

//void Active_Healers::Act()
//{
//
//}