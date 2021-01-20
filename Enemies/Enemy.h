#pragma once
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{
protected:
	const int ID;         //Each enemy has a unique ID (sequence number)
	const int ArrvTime;	 //arrival time (time it starts to join battle) -(Enemy Arrival Time): When the enemy arrives.
	ENMY_STATUS status;	    //status of the enemy (inactive, inactive, frosted, killed)
	/* At any time, an enemy should be in one of four states: inactive (not arrived yet), active,
    frosted or killed (health <= 0). Only active enemies can act
    (fight/heal/freeze).*/
	int Distance;	//Horizontal distance between enemy & the tower of its region(castle) //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health -The starting health of the enemy.

	// TODO: Add More Data Members As Needed
	int Enemytype;  //fighter, freezer or healer
	int Enemypower; //The power of the enemy.
	int Enemyspeed; //number of meters an enemy can move in a single time step.
	int Reloadperiod; //Time for an enemy to reload its weapon.
	int CurrentReloadperiod;
	/*
	Reload Period: it is an interval where enemies are reloading their weapons. During reload
	period enemies cannot act (i.e. cannot attack or heal) but can move. Once reload period is
	over, enemies can act again.
	For example, Enemy e1(arrival time=5, reload period=3) will act at time step 5 then
	wait to reload at time steps: 6, 7 and 8 then it will act again at time step 9 then wait to
	reload at 10, 11 and 12 then act at 13 and so on.
	*/
	double CurrentHealth;
	int CurrentSpeed;
	int IceOnEnemy;
	// static double k;
	double DamageE; //Damage to an enemy by a castle bullet

	int FirstTimeToShot; //Tfirstshot
	const int FirstShotDelay; //FD=Tfirstshot-Tarrival,The time elapsed until an enemy is first shot by castle
	int KilledTimeStep;
	int killedDelay;  //KD=Tenemykilled-Tfirstshot,The time elapsed between first time a castle shoots the enemy and its kill time
	int Lifetime;  //LT=FD+KD=Tenemykilled-Tarrival,The total time an enemy stays alive until being killed 
public:
	//Enemy(int id, int arrTime,int EH,int EP,int S,int RT, int d = MaxDistance);
	Enemy(int id, int arrTime,int d = MaxDistance);
	virtual ~Enemy();

	int Enemy::GetID() const;
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);
	
	void DecrementDist();

	void SetHealth(double);
	double GetHealth() const ;
	
	virtual void setCurrentReloadperiod(int);
	virtual int GetCurrentReloadperiod() const;

	int GetArrvTime() const;

	void SetEnemyType(int);
	int GetEnemyType() const;
	virtual void SetEnemyPower(int);
	virtual int GetEnemyPower() const;
	virtual void SetReloadPeriod(int);
	virtual int GetReloadPeriod() const;
	void SetEnemySpeed(int);
	int GetEnemySpeed() const;

	double GetDamage() const;

	virtual void SetFirstTimeToShot(int);
	virtual int GetFirstTimeToShot() const;

	//void SetFirstShotDelay(int);
	virtual int GetFirstShotDelay()const;
	virtual void SetKilledTimeStep(int currenttimestep);
	//void SetkilledDelay(int);
	virtual int GetkilledDelay();
	//void SetLifetime(int);
	virtual int GetLifetime();

	virtual void SetCurrentSpeed(int CS);
	virtual int GetCurrentSpeed() const;
	virtual void ReduceSpeedtoHalf();

	virtual void SetCurrentHealth(double CH)=0;
	virtual double GetCurrentHealth() =0;
	virtual void SetDistance(int);
	virtual int GetDistance() const ;
	bool isLessThanHalfHealth();
	// Virtual Functions: ----------------
	//virtual void DamageToEnemy(int castlefirepower);
	virtual void Move() = 0;	//All enemies can move
	//virtual void Act() = 0;	//Acting means fighting or healing
	/*
	By default all enemies move in the forward direction (approaching castle) but only
	healers can move backward. When a healer reaches end of forward direction, it starts
	moving backward until it reaches end of backward direction where it turns back and
	moves forward again and so on.
	*/
	// TODO: Add More Member Functions As Needed
	virtual void SetIceOnEnemy();
	virtual int GetIceOnEnemy() const;
	virtual bool isFrosted();
	virtual void MeltIce();
	virtual int GetKilledTimeStep();
};