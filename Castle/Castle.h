#pragma once
#include "..\Defs.h"
#include "..\Enemies\Enemy.h"  

//A castle can attack any enemy type
class Castle
{
private:
	double Health;
	// TODO: Add More Data Members As Needed
	int MaxEnemyTimeStep;
	int CastlePower;
	int M;
	static const int k = 10;
	double DamageC;
	int AmountofIceThrown; // amount of ice a freezer can throw on a castle.
	int IceOnCastle;
	static const int I = 10;
	double currentHealth;
public:
	Castle();
	void SetHealth(double h);
	double GetHealth() const;
	// TODO: Add More Member Functions As Needed
	int GetMaxEnemyTimeStep() const;
	void SetMaxEnemyTimeStep(int h);
	int GetCastlePower() const;
	void SetCastlePower(int h);
	void FIDamageToCastle(Enemy* E,double Fighterfirepower);//Damage a fighter causes to Castle
	bool isFrosted(); //castle frosted for some time by a freezer
	void FRDamageToCastle(Enemy* E);//Damage a Freezer causes to Castle
	void resetIceOnCastle();
	int getIceOnCastle();
	void setCurrentHealth(double  c);
	double getCurrentHealth();
	//void FreezerAttack();
};