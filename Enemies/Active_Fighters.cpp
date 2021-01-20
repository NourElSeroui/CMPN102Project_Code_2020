#include "Active_Fighters.h"

Active_Fighters::~Active_Fighters() {}
Active_Fighters::Active_Fighters(int id, int arrTime, int d) : Enemy(id, arrTime, d)
{
	Enemytype = FIGHTER;
	fighterfirepower = 2;
	//status = ACTV;
	//SetCurrentHealth(0);
}
//Damage to an enemy by a castle bullet
void Active_Fighters::DamageToEnemy(int castlefirepower) 
{
	double k = 1.0;
	DamageE = (1.0 / Distance) * castlefirepower * 1.0 / k;
	CurrentHealth = CurrentHealth - DamageE;
	//ReduceSpeedtoHalf(); //check if currenthealth<0.5*health
}
int Active_Fighters::priority()
{
	int h = CurrentHealth;
	int d = Distance; 
	int s= GetStatus();
	int p = Enemypower;
	int e = (p * ((h ) * (s + 1))) / d;
	return e;
}
void Active_Fighters::Setfighterfirepower(double fp)
{
	fighterfirepower = (fp > 0) ? fp : 0;
}
double Active_Fighters::Getfighterfirepower() const
{
	return fighterfirepower;
}

void Active_Fighters::Act(Castle* C)
{
	//During reload period enemies cannot act(i.e.cannot attack or heal) but can move.Once reload period is over, enemies can act again
	C->SetHealth(C->GetHealth() - Enemypower);
	if (Health == 0)
	{
		SetStatus(KILD);
		//EnemyCount--; //logic may be in battle?!
	}
}
//Enemies can move at their reload period but cannot act. (cannot fire nor heal)
void Active_Fighters::Move()
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
void Active_Fighters::SetCurrentHealth(double CH) //has logic: firepower reduces the health
{
	if (CH > 0)
		CurrentHealth = CH;
	else
		CurrentHealth = 0;
}
double Active_Fighters::GetCurrentHealth()
{
	return CurrentHealth;
}
/*
double Active_Fighters::GetDamage() const
{
	return DamageE;
}

void Active_Fighters::SetCurrentSpeed(int CS)
{
	if (CS > 0)
		CurrentSpeed = CS;
	else
		CurrentSpeed = 0;
}
int Active_Fighters::GetCurrentSpeed() const
{
	return CurrentSpeed;
}

Active_Fighters::Active_Fighters(int CH, int id, int arrTime, int EH, int EP, int S, int RT, int d) : Enemy(id,arrTime,EH,EP,S,RT,d)
{
	Enemy_type = FIGHTER;
	status = ACTV;
	SetCurrentHealth(CH);
}

void Active_Fighters::SetCurrentHealth(double CH) //has logic: firepower reduces the health
{
	if (CH > 0)
		CurrentHealth = CH;
	else
		CurrentHealth = 0;
}
double Active_Fighters::GetCurrentHealth() const
{
	return CurrentHealth;
}
void Active_Fighters::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else if (Distance == 0)
		Distance = MinDistance;
	else
		Distance = MaxDistance;
}
int Active_Fighters::GetDistance()const
{
	return Distance;
}
void Active_Fighters::SetfighterSpeed(double fs)
{
	fighterSpeed = (fs > 0) ? fs:0;
}
double Active_Fighters::GetfighterSpeed() const
{
	return fighterSpeed;
}
*/