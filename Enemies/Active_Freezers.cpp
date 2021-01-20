#include "Active_Freezers.h"

Active_Freezers::~Active_Freezers(){}
Active_Freezers::Active_Freezers(int id, int arrTime, int d) : Enemy(id, arrTime, d)
{
	Enemytype = FREEZER;
	status = ACTV;
	//status = FRST; //seif wrote this,i think its wrong as frost means cant move or act,,,but a freezer can act and move untill frosted by the castle
	//SetCurrentHealth(0);
}
//Damage to an enemy by a castle bullet
void Active_Freezers::DamageToEnemy(int castlefirepower)
{
	double k = 1;
	DamageE = (1.0 / Distance) * castlefirepower * 1.0 / k;
	CurrentHealth = CurrentHealth - DamageE;
	//ReduceSpeedtoHalf(); //check if currenthealth<0.5*health
}
//underconstruction:
bool Active_Freezers::IsitTimeToShot() //ta2leef ashraf
{
	    //time -//how to get the automatic timestep of the system
	if ( GetFirstTimeToShot() % (Reloadperiod + 1) == 0)
		return true;
	return false;
}
//Enemies can move at their reload period but cannot act. (cannot fire nor heal)
void Active_Freezers::Move()
{
	//or just call DecrementDist()
	//if (Distance > MinDistance)
		//Distance--;
	if (CurrentHealth < 0.5 * Health)
	{
		if (Distance - 0.5 * Enemyspeed > MinDistance)
		{
			Distance = Distance - 0.5 * Enemyspeed;
		}
		else
			Distance = MinDistance;
	}
	else
	{
		if (Distance - Enemyspeed > MinDistance)
		{
			Distance = Distance - Enemyspeed;
		}
		else
			Distance = MinDistance;
	}
	if (Distance == 0)
		Distance = MinDistance;
}
void Active_Freezers::SetCurrentHealth(double CH) //has logic: firepower reduces the health
{
	if (CH > 0)
		CurrentHealth = CH;
	else
		CurrentHealth = 0;
}
double Active_Freezers::GetCurrentHealth()
{
	return CurrentHealth;
}
//void Active_Freezers::SetDistance(int d)
//{
//	if (d >= MinDistance && d <= MaxDistance)
//		Distance = d;
//	else if (Distance == 0)
//		Distance = MinDistance;
//	else
//		Distance = MaxDistance;
//}
//int Active_Freezers::GetDistance() const
//{
//	return Distance;
//}
//int Active_Freezers::TimeToShot()
//{
//	//if (IsitTimeToShot())
//		//return time;
//}

//void Active_Freezers::SetCurrentHealth(int CH)
//{
//	if (CH > 0)
//		CurrentHealth = CH;
//	else
//		CurrentHealth = 0;
//}
//int Active_Freezers::GetCurrentHealth() const
//{
//	return CurrentHealth;
//}
/*
void Active_Freezers::SetCurrentSpeed(int CS)
{
	if (CS > 0)
		CurrentSpeed = CS;
	else
		CurrentSpeed = 0;
}
int Active_Freezers::GetCurrentSpeed() const
{
	return CurrentSpeed;
}
void Active_Freezers::Act(Castle* C)
{
	//During reload period enemies cannot act(i.e.cannot attack or heal) but can move.Once reload period is over, enemies can act again
	
}
*/