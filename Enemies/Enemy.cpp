#include "Enemy.h"

Enemy::~Enemy() {}
Enemy::Enemy(int id, int arrTime, int d) :ID(id), ArrvTime(arrTime),FirstShotDelay(0) //const data memeber initialization
{
	Distance = d;
	//ArrvTime = 0;
	Reloadperiod = 0;
	CurrentReloadperiod = 0;
	FirstTimeToShot = 0;
	KilledTimeStep = 0;
	killedDelay = 0;
	Lifetime = 0;
}
int Enemy::GetID() const
{
	return ID;
}
void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}
ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}
void Enemy::DecrementDist()
{
	if (Distance > MinDistance) //EDIT??for speed??
		Distance--;
}
void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else if (Distance == 0)  //d?
		Distance = MinDistance;
	else
		Distance = MaxDistance;
}
int Enemy::GetDistance() const
{
	return Distance;
}
int Enemy::GetArrvTime() const
{
	return ArrvTime;
}
void Enemy::SetEnemyType(int t)
{
	Enemytype = t;
}
int Enemy::GetEnemyType() const
{
	return Enemytype;
}
void Enemy::SetEnemyPower(int p)
{
	if (p > 0)
		Enemypower = p;
	else
		Enemypower = 0;
}
int Enemy::GetEnemyPower() const
{
	return Enemypower;
}
void Enemy::SetEnemySpeed(int s)
{
	if (s > 0)
		Enemyspeed = s;
	else
		Enemyspeed = 0;
}
int Enemy::GetCurrentReloadperiod() const
{
	return CurrentReloadperiod;
}
void Enemy::setCurrentReloadperiod(int r)
{
	if (r > 0)
		CurrentReloadperiod = r;
	else
		CurrentReloadperiod = 0;
}
int Enemy::GetEnemySpeed() const
{
	return Enemyspeed;
}
void Enemy::SetReloadPeriod(int r)
{
	if (r > 0)
		Reloadperiod = r;
	else
		Reloadperiod = 0;
}
int Enemy::GetReloadPeriod() const
{
	return Reloadperiod;
}
void Enemy::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else 
		Health = 0;
}
double Enemy::GetHealth() const 
{
	return Health;
}
double Enemy::GetDamage() const
{
	return DamageE;
}
void Enemy::SetFirstTimeToShot(int f)
{
	FirstTimeToShot = f;
}
/*
For example, Enemy e1(arrival time=5, reload period=3) will act at time step 5 then
wait to reload at time steps: 6, 7 and 8 then it will act again at time step 9 then wait to
reload at 10, 11 and 12 then act at 13 and so on.
*/
int Enemy::GetFirstTimeToShot() const
{
	//FirstTimeToShot = ArrvTime + Reloadperiod + 1;
	return FirstTimeToShot;
}
/*void Enemy::SetFirstShotDelay(int)
{
	//FD=Tfirstshot-Tarrival
	FirstShotDelay = FirstTimeToShot - ArrvTime;
}*/
int Enemy::GetFirstShotDelay() const
{
	//FD=Tfirstshot-Tarrival
	int t = FirstTimeToShot - ArrvTime;  //GetFirstTimeToShot()??
	return t;
}
void Enemy::SetKilledTimeStep(int currenttimestep)
{
	KilledTimeStep = currenttimestep;
}

int Enemy::GetKilledTimeStep()
{
	return KilledTimeStep;
}
int Enemy::GetkilledDelay()
{
	//KD=Tenemykilled-Tfirstshot
	killedDelay = KilledTimeStep - FirstTimeToShot;
	return killedDelay;
}
int Enemy::GetLifetime() 
{
	//LT=FD+KD=Tenemykilled-Tarrival
	Lifetime= KilledTimeStep - ArrvTime;
	return Lifetime;
}
void Enemy::SetCurrentSpeed(int CS)
{
	if (CS > 0)
		CurrentSpeed = CS;
	else
		CurrentSpeed = 0;
}
int Enemy::GetCurrentSpeed() const
{
	return CurrentSpeed;
}
void Enemy::ReduceSpeedtoHalf()
{
	if (CurrentHealth < 0.5 * GetHealth())
		SetCurrentSpeed(0.5 * GetEnemySpeed());
}
bool Enemy::isLessThanHalfHealth()
{
	if (GetCurrentHealth() < 0.5 * GetHealth())
		return true;
	return false;
}
int Enemy::GetIceOnEnemy() const
{
	return IceOnEnemy;
}
void Enemy::SetIceOnEnemy()
{
	IceOnEnemy = 6;
}

void Enemy::MeltIce()
{
	if (Distance > 20 && CurrentHealth > (Health / 2))
		IceOnEnemy = IceOnEnemy - 3;
	else if (Distance > 20 && CurrentHealth < (Health / 2))
		IceOnEnemy = IceOnEnemy - 2;
	else if (Distance < 20 && CurrentHealth >(Health / 2))
		IceOnEnemy = IceOnEnemy - 2;
	else
		IceOnEnemy = IceOnEnemy - 1;
}
bool Enemy::isFrosted()
{
	if (IceOnEnemy > 0)
		return true;//Freezer can throw ice on the castle to frost it for some time.
	else
		return false;
}
/*
Enemy::Enemy(int id, int arrTime, int EH, int EP, int S, int RT, int d):ID(id),ArrvTime(arrTime) //const data memeber initialization
{
	SetDistance(d);
	SetEnemy_speed(S);
	SetReload_time(RT);
	SetHealth(EH);
}
void Enemy::SetCurrentHealth(double CH) //has logic: firepower reduces the health
{
	if (CH > 0)
		CurrentHealth = CH;
	else
		CurrentHealth = 0;
}
double Enemy::GetCurrentHealth() 
{
	return CurrentHealth;
}
*/