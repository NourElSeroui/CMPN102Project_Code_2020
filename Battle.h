#pragma once
#include <fstream>		
#include <iostream>				

#include "Enemies\Enemy.h"
#include "Enemies\Active_Fighters.h"
#include "Enemies\Active_Healers.h"
#include "Enemies\Active_Freezers.h"
#include "Enemies\Frozen_List.h"
#include "Enemies\Inactive_List.h"
#include "Enemies\Killed_List.h"
#include "Castle\Castle.h"
#include "Generic_DS\Queue.h"
#include "Generic_DS\Stack.h"
#include "Generic_DS\PriorityQueue.h"
#include "GUI\GUI.h"

// it is the controller of the project
class Battle
{
private:
	GUI* pGUI;
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int ActiveCount, FrostedCount, KilledCount ,ActiveHealerCount,ActiveFighterCount,ActiveFreezerCount , FrostedFighterCount, FrostedFreezerCount, FrostedHealerCount;	//no. of enemies (Active, Frosted, killed so far)
	int CurrentTimeStep;

	Queue<Enemy*> Q_Inactive;		//Queue of inactive enemies    
	Queue<Active_Freezers* > Q_Active_Freezers; 
	Queue<Enemy*> Q_Killed_List;
	Stack<Active_Healers*> S_Active_Healers;
	PriorityQueue<Active_Fighters*> PQ_Active_Fighters;
	PriorityQueue<Enemy*> PQ_Frozen_List;
	
	string game = " ";
	/*Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function*/
public:
	
	Battle();
	//void AddAllListsToDrawingList();
	void AddAllListsToDrawingList2();//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle * GetCastle();
	void RunSimulation();
	void ActivateEnemies();		//check the inactive list and activate all enemies that has arrived
	

	//void AddtoDemoList(Enemy* Ptr);		//Add Enemy to the demo queue of enemies (for demo purposes only)
	void AddtoActiveFreezer(Enemy* Ptr);
	void AddtoActiveHealer(Enemy* Ptr);
	void AddtoActiveFighter(Enemy* Ptr);
	void AddtoFrozenList(Enemy* Ptr);
	void AddtoKilledList(Enemy* Ptr);

	void UpdateEnemies(int c);
	void CastleFight(int c );
	void CastleFreeze();
	void StepByStep();
	void Silent();
	void Interactive();
	
	void load_file(GUI* pOut);
	void set_Enemy_Count(int);

	void MoveEnemies();
	void OutputFile();
	~Battle();
};