#include "Castle.h"

Castle::Castle()
{
	AmountofIceThrown = 0;
	IceOnCastle = 0;
	currentHealth = 0;
	Health = 0;
}
void Castle::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; //killed
}
double Castle::GetHealth() const
{
	return Health;
}
int Castle::GetMaxEnemyTimeStep() const
{
	return MaxEnemyTimeStep;
}
void Castle::SetMaxEnemyTimeStep(int M)
{
	if (M > 0)
		MaxEnemyTimeStep = M;
	else
		MaxEnemyTimeStep = 0; 
}
int Castle::GetCastlePower() const
{
	return CastlePower;
}
void Castle::SetCastlePower(int P)
{
	if (P > 0)
		CastlePower = P;
	else
		CastlePower = 0;
}
void Castle::setCurrentHealth(double  c)
{
	currentHealth = c;
}
double Castle::getCurrentHealth()
{
	return currentHealth;
}
void Castle::FIDamageToCastle(Enemy* E, double Fighterfirepower) //Damage a fighter causes to Castle
{
	double k=0;
	if (E->isLessThanHalfHealth())
	{
		k = 0.5;
		DamageC = (k / E->GetDistance()) * Fighterfirepower;
	}
	else //Enemy is of full health
	{
		k = 1.0;
		DamageC = (k / E->GetDistance()) * Fighterfirepower;
	}
	currentHealth = currentHealth - DamageC;
}
bool Castle::isFrosted()
{
	if (IceOnCastle >= I)
		return true;//Freezer can throw ice on the castle to frost it for some time.
	else
		return false;
}
void Castle::FRDamageToCastle(Enemy* E) //Ice a freezer causes to Castle
{
	IceOnCastle++;
}
void Castle::resetIceOnCastle()
{
	IceOnCastle = 0;
}
int Castle::getIceOnCastle()
{
	return IceOnCastle;
}
/*
void Castle::FreezerAttack()
{
	M = 1;
	if ((AmountofIceThrown % k) * M == 0)
	{
		//castle frozen for 1 time step
	}
}*/