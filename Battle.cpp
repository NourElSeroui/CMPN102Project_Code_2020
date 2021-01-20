#include "Battle.h"
#include <time.h>

Battle::Battle()
{	
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	CurrentTimeStep = 0;
	ActiveFighterCount = 0;
	ActiveFreezerCount = 0;
	ActiveHealerCount = 0;
	//FrostedFighterCount = 0;
	//FrostedFreezerCount = 0;
	//FrostedHealerCount = 0;
	pGUI = NULL;
}
void Battle::AddtoActiveFreezer(Enemy* Ptr)
{
	ActiveFreezerCount++;
	Q_Active_Freezers.enqueue(dynamic_cast<Active_Freezers*>(Ptr));
}
void Battle::AddtoActiveHealer(Enemy* Ptr)
{
	//stack
	ActiveHealerCount++;
	S_Active_Healers.push(dynamic_cast<Active_Healers*>(Ptr));
}
void Battle::AddtoActiveFighter(Enemy* Ptr)
{
	// priority
	ActiveFighterCount++;
	Active_Fighters* a = dynamic_cast<Active_Fighters*>(Ptr);
	PQ_Active_Fighters.enqueueSort(a);
}
void Battle::AddtoFrozenList(Enemy* Ptr)
{
	// priority
	PQ_Frozen_List.enqueueSort(dynamic_cast<Frozen_List*>(Ptr));
}
void Battle::AddtoKilledList(Enemy* Ptr)
{
	// queue
	Q_Killed_List.enqueue(dynamic_cast<Killed_List*>(Ptr));
}
Castle * Battle::GetCastle()
{
	return &BCastle;
}
void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive();
	case MODE_STEP:
		StepByStep();
	case MODE_SLNT:
		Silent();
	}
	delete pGUI;
}
void Battle::Interactive()
{
	load_file(pGUI); 

	pGUI->PrintMessage("Generating Enemies from loaded file... .CLICK to continue");
	pGUI->waitForClick();

	CurrentTimeStep = 0;
	AddAllListsToDrawingList2();
	//AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();
	int KilledCount3;
	while (KilledCount < EnemyCount && BCastle.GetHealth()>0)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();
		int InactiveCount;
		Enemy* const* EnemyList = Q_Inactive.toArray(InactiveCount);

		int frostedcount;
		int FrostedFighter = 0;
		int FrostedHealer = 0;
		int FrostedFreezer = 0;
		Enemy* const* Frosted = PQ_Frozen_List.toArray(frostedcount);
		for (int i = 0; i < frostedcount; i++)
		{
			if (Frosted[i]->GetEnemyType() == 0)
				FrostedFighter++;
			else if (Frosted[i]->GetEnemyType() == 1)
				FrostedHealer++;
			else if (Frosted[i]->GetEnemyType() == 2)
				FrostedFreezer++;
		}
		int activeFreezerCount;
		Active_Freezers* const* FreezerEnemyList = Q_Active_Freezers.toArray(activeFreezerCount);

		int activeHealerCount;
		Active_Healers* const* HealerEnemyList = S_Active_Healers.toArray(activeHealerCount);

		int activeFighterCount;
		Active_Fighters* const* FighterEnemyList = PQ_Active_Fighters.toArray(activeFighterCount);

		int KilledFighter = 0;
		int KilledHealer = 0;
		int KilledFreezer = 0;
		Enemy* const* KilledEnemyList = Q_Killed_List.toArray(KilledCount3);
		for (int i = 0; i < KilledCount3; i++)
		{
			if (KilledEnemyList[i]->GetEnemyType() == 0)
				KilledFighter++;
			else if (KilledEnemyList[i]->GetEnemyType() == 1)
				KilledHealer++;
			else if (KilledEnemyList[i]->GetEnemyType() == 2)
				KilledFreezer++;
		}

		// genertate (in update castle).....sublists of killed and frosted
		string msg = "TimeStep: " + to_string(CurrentTimeStep) + "\n Current health of the castle: " + to_string(BCastle.GetHealth()) + " whether it is frosted or not: " + to_string(BCastle.isFrosted()) + " Number of active fighters: " + to_string(activeFighterCount)
			+ "\nNumber of active healers: " + to_string(activeHealerCount) + " Number of active freezers: " + to_string(activeFreezerCount) + "\n Total Number of active Enemies: " + to_string(activeHealerCount + activeFreezerCount + activeFighterCount) +
			"\nNumber of frosted fighters: " + to_string(FrostedFighter) + "  Number of frosted healers: " + to_string(FrostedHealer) + "  Number of frosted freezers: " + to_string(FrostedFreezer) +
			+"\nTotal Number of frosted Enemies: " + to_string(FrostedCount) + " Number of killed fighters: " + to_string(KilledFighter) + " Number of killed healers: " + to_string(KilledHealer) + "\n Number of killed freezers: " + to_string(KilledFreezer) + " Total Number of Killed Enemies: " + to_string(KilledCount3) + "\n";
		pGUI->PrintMessage(msg);
		Sleep(1000);

		//Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)
		UpdateEnemies(CurrentTimeStep);
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList2();
		//AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		pGUI->waitForClick();
	}
	if (KilledCount3 == EnemyCount)
		game = "Win";
	else if ( BCastle.GetHealth() <= 0)
		game = "Lose";
	else
		game = "Draw";
	OutputFile();
}
void Battle::Silent()
{
	load_file(pGUI);

	pGUI->PrintMessage("Generating Enemies from loaded file... .CLICK to continue");
	pGUI->waitForClick();
	CurrentTimeStep = 0;
	
	while (KilledCount < EnemyCount && BCastle.GetHealth()>0)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();
		UpdateEnemies(CurrentTimeStep);
	}
	if (KilledCount == EnemyCount)
		game = "Win";
	else if ( BCastle.GetHealth() <= 0)
		game = "Lose";
	else
		game = "Draw";
	OutputFile();
}

void Battle::StepByStep()
{
	load_file(pGUI); 

	pGUI->PrintMessage("Generating Enemies from loaded file... .CLICK to continue");
	pGUI->waitForClick();

	CurrentTimeStep = 0;
	AddAllListsToDrawingList2();
	//AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();
	int KilledCount2;
	while (KilledCount < EnemyCount && BCastle.getCurrentHealth()>0)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();
		int InactiveCount;
		Enemy* const* EnemyList = Q_Inactive.toArray(InactiveCount);
	
		int frostedcount;
		int FrostedFighter = 0;
		int FrostedHealer = 0;
		int FrostedFreezer = 0;
		Enemy* const* Frosted = PQ_Frozen_List.toArray(frostedcount);
		for (int i = 0; i < frostedcount; i++)
		{
			if (Frosted[i]->GetEnemyType() == 0)
				FrostedFighter++;
			else if (Frosted[i]->GetEnemyType() == 1)
				FrostedHealer++;
			else if (Frosted[i]->GetEnemyType() == 2)
				FrostedFreezer++;
		}
		
		int activeFreezerCount;
		Active_Freezers* const* FreezerEnemyList = Q_Active_Freezers.toArray(activeFreezerCount);

		int activeHealerCount;
		Active_Healers* const* HealerEnemyList = S_Active_Healers.toArray(activeHealerCount);

		int activeFighterCount;
		Active_Fighters* const* FighterEnemyList = PQ_Active_Fighters.toArray(activeFighterCount);

		int KilledFighter = 0;
		int KilledHealer = 0;
		int KilledFreezer = 0;
		Enemy* const* KilledEnemyList = Q_Killed_List.toArray(KilledCount2);
		for (int i = 0; i < KilledCount2; i++)
		{
			if (KilledEnemyList[i]->GetEnemyType() == 0)
				KilledFighter++;
			else if (KilledEnemyList[i]->GetEnemyType() == 1)
				KilledHealer++;
			else if (KilledEnemyList[i]->GetEnemyType() == 2)
				KilledFreezer++;
		}

		// genertate (in update castle).....sublists of killed and frosted
		string msg = "TimeStep: " + to_string(CurrentTimeStep) + "\n Current health of the castle: " + to_string(BCastle.getCurrentHealth()) + " whether it is frosted or not: " + to_string(BCastle.isFrosted()) + " Number of active fighters: " + to_string(ActiveFighterCount)
			+ "\nNumber of active healers: " + to_string(ActiveHealerCount) + " Number of active freezers: " + to_string(ActiveFreezerCount) + "\n Total Number of active Enemies: " + to_string(ActiveHealerCount + ActiveFreezerCount+ activeFighterCount) +
			"\nNumber of frosted fighters: " + to_string(FrostedFighter) + "  Number of frosted healers: " + to_string(FrostedHealer) + "  Number of frosted freezers: " + to_string(FrostedFreezer) +
			+"\nTotal Number of frosted Enemies: " + to_string(FrostedCount) + " Number of killed fighters: " + to_string(KilledFighter) + " Number of killed healers: " + to_string(KilledHealer) + "\n Number of killed freezers: " + to_string(KilledFreezer) + " Total Number of Killed Enemies: " + to_string(KilledCount) + "\n";
		pGUI->PrintMessage(msg);
		Sleep(1000);

		//Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)
		UpdateEnemies(CurrentTimeStep);
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList2();
		//AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		Sleep(250);
	}
	if (KilledCount == EnemyCount)
		game = "Win";
	else if (BCastle.getCurrentHealth() <= 0)
		game = "Lose";
	else
		game = "Draw";
	OutputFile();
}

void Battle::AddAllListsToDrawingList2()
{
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const* EnemyList = Q_Inactive.toArray(InactiveCount);
	for (int i = 0; i < InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//Add other lists to drawing list
	//TO DO
	//In next phases, you should add enemies from different lists to the drawing list
	//For the sake of demo, we will use DemoList
	int activeFreezerCount;
	Active_Freezers* const* FreezerEnemyList = Q_Active_Freezers.toArray(activeFreezerCount);
	for (int i = 0; i < activeFreezerCount; i++)
		pGUI->AddToDrawingList(FreezerEnemyList[i]);

	int activeHealerCount;
	Active_Healers* const* HealerEnemyList = S_Active_Healers.toArray(activeHealerCount);
	for (int i = 0; i < activeHealerCount; i++)
		pGUI->AddToDrawingList(HealerEnemyList[i]);

	int activeFighterCount;
	Active_Fighters* const* FighterEnemyList = PQ_Active_Fighters.toArray(activeFighterCount);
	for (int i = 0; i < activeFighterCount; i++)
		pGUI->AddToDrawingList(FighterEnemyList[i]);

	int KilledCount3;
	Enemy* const* KilledEnemyList = Q_Killed_List.toArray(KilledCount3);
	for (int i = 0; i < KilledCount3; i++)
		pGUI->AddToDrawingList(KilledEnemyList[i]);
	int frostedcount;
	Enemy* const* Frosted = PQ_Frozen_List.toArray(frostedcount);
	for (int i = 0; i < frostedcount; i++)
		pGUI->AddToDrawingList(Frosted[i]);
}

void Battle::ActivateEnemies()
{
	Enemy *pE;
	while (Q_Inactive.peekFront(pE))	//as long as there are more inactive enemies
	{
		if (pE->GetArrvTime() > CurrentTimeStep)	//no more arrivals at current time
			return;
		
		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		int t = pE->GetEnemyType();
		// based on type , categorize into active lists
		if (t == FIGHTER)
			AddtoActiveFighter(pE);
		else if (t == HEALER)
			AddtoActiveHealer(pE);
		else if (t == FREEZER)
			AddtoActiveFreezer(pE);
		else
			return;

	}
}
//Randomly update enemies distance/status (for demo purposes)

void Battle::MoveEnemies()
{
	Active_Freezers*  Freezer;
	int activeFreezerCount;
	Active_Freezers* const* FreezerList = Q_Active_Freezers.toArray(activeFreezerCount);

	for (int i = 0; i < activeFreezerCount; i++)
	{
		Freezer = FreezerList[i];
		if (Freezer != NULL)
		{
			if (Freezer->GetStatus() == ACTV)
			{
				Freezer->Move();
				if (Freezer->GetCurrentReloadperiod() == 0)
				{
					BCastle.FRDamageToCastle(Freezer);
					Freezer->setCurrentReloadperiod((Freezer->GetReloadPeriod()));
				}// we need to adjust this Act function**
				else
					Freezer->setCurrentReloadperiod((Freezer->GetCurrentReloadperiod()) - 1);
			}
		}
	}
	Active_Fighters* Fighter;
	int activeFighterCount;
	Active_Fighters* const* FighterList = PQ_Active_Fighters.toArray(activeFighterCount);

	for (int i = 0; i < activeFighterCount; i++)
	{
		Fighter = FighterList[i];
		if (Fighter != NULL)
		{
			
			if (Fighter->GetStatus() == ACTV)
			{
				Fighter->Move();
				if (Fighter->GetCurrentReloadperiod() == 0)
				{
						BCastle.FIDamageToCastle(Fighter, Fighter->Getfighterfirepower());
						Fighter->setCurrentReloadperiod((Fighter->GetReloadPeriod()));
				}/// we need to adjust this Act function**
				else
					Fighter->setCurrentReloadperiod((Fighter->GetCurrentReloadperiod()) - 1);
			}
		}
	}
	Active_Healers* Healer;
	int activeHealerCount;
	Active_Healers* const* HealerList = S_Active_Healers.toArray(activeHealerCount);

	for (int i = 0; i < activeHealerCount; i++)
	{
		Healer = HealerList[i];
		if (Healer != NULL)
		{
	
			if (Healer->GetStatus() == ACTV)
			{
				Healer->Move();
				for (int i = 0; i < activeFreezerCount; i++)
				{
					Freezer = FreezerList[i];
					if (Freezer != NULL)
					{
						if (Freezer->GetStatus() == ACTV)
						{
							if ((Freezer->GetDistance() - Healer->GetDistance()) == 2 || (Healer->GetDistance() - Freezer->GetDistance()) == 2)
							{
								if (Healer->GetCurrentReloadperiod() == 0)
								{
									Healer->Act(Freezer);
									Healer->setCurrentReloadperiod((Healer->GetReloadPeriod()));
								}
								else
									Healer->setCurrentReloadperiod((Healer->GetCurrentReloadperiod()) - 1);
							}
						}
					}
				}
				for (int i = 0; i < activeFighterCount; i++)
				{
					Fighter = FighterList[i];
					if (Fighter != NULL)
					{
						if (Fighter->GetStatus() == ACTV)
						{
							if ((Fighter->GetDistance() - Healer->GetDistance()) == 2 || (Healer->GetDistance() - Fighter->GetDistance()) == 2)
							{
								if (Healer->GetCurrentReloadperiod() == 0)
								{
									Healer->Act(Fighter);
									Healer->setCurrentReloadperiod((Healer->GetReloadPeriod()));
								}
								else
									Healer->setCurrentReloadperiod((Healer->GetCurrentReloadperiod()) - 1);
							}
						}
					}
				}
			}
		}
	}

	Enemy* Frosted;
	int Frostedcount;
	Enemy* const* FrostedList = PQ_Frozen_List.toArray(Frostedcount);
	for (int i = 0; i < Frostedcount; i++)
	{
		Frosted = FrostedList[i];
		Frosted->MeltIce();
		if (!(Frosted->isFrosted()) && Frosted->GetCurrentHealth() > 0)
		{
			Enemy* temp;
			PQ_Frozen_List.dequeue(temp);
			if (temp->GetEnemyType() == FIGHTER)
			{
				Active_Fighters* f = dynamic_cast<Active_Fighters*>(temp);
				PQ_Active_Fighters.enqueueSort(f);
				f->SetStatus(ACTV);
				FrostedCount--;
				ActiveCount++;
				ActiveFighterCount++;
				FrostedFighterCount--;
			}
			else if (temp->GetEnemyType() == HEALER)
			{
				Active_Healers* h = dynamic_cast<Active_Healers*>(temp);
				S_Active_Healers.push(h);
				h->SetStatus(ACTV);
				FrostedCount--;
				ActiveCount++;
				ActiveHealerCount++;
				FrostedHealerCount--;
			}
			else if (temp->GetEnemyType() == FREEZER)
			{
				Active_Freezers* F = dynamic_cast<Active_Freezers*>(temp);
				Q_Active_Freezers.enqueue(F);
				F->SetStatus(ACTV);
				FrostedCount--;
				ActiveCount++;
				ActiveFreezerCount++;
				FrostedFreezerCount--;
			}
		}
		else if (!(Frosted->isFrosted()) && Frosted->GetCurrentHealth() <= 0)
		{
			Enemy* temp;
			PQ_Frozen_List.dequeue(temp);
			Q_Killed_List.enqueue(temp);
			temp->SetStatus(KILD);
			FrostedCount--;
			KilledCount++;
		}
	}
}
void Battle::UpdateEnemies(int C)
{
	MoveEnemies();
	if (!BCastle.isFrosted())
	{
		int result =   (rand() % 6);

		if (result==3 || result ==5)
		CastleFreeze();
		else
		CastleFight(C);
	}
	else
	BCastle.resetIceOnCastle();
}
void Battle::CastleFight(int c)
{
		int n = BCastle.GetMaxEnemyTimeStep();
		int nfi;
		Active_Fighters* const* EnemyList3 = PQ_Active_Fighters.toArray(nfi);
		int nhe;
		Active_Healers* const* EnemyList2 = S_Active_Healers.toArray(nhe);
		int nfr;
		Active_Freezers* const* EnemyList = Q_Active_Freezers.toArray(nfr);

		Stack<Active_Healers*> temp;
		Stack<Active_Healers*> temp2;
		Queue<Active_Freezers*> qtemp;
		Queue<Active_Freezers*> qtemp2;

		if (n > 0)
		{
			int ActFighterCount;
			Active_Fighters* const* EnemyList = PQ_Active_Fighters.toArray(ActFighterCount);

			//act
			for (int i = 0; i < nfi && n>0; i++)
			{

				if (EnemyList[i] != NULL)
				{

					if (EnemyList[i]->GetFirstTimeToShot() > 0)
						EnemyList[i]->DamageToEnemy(BCastle.GetCastlePower());
					else
					{
						EnemyList[i]->DamageToEnemy(BCastle.GetCastlePower());
						EnemyList[i]->SetFirstTimeToShot(CurrentTimeStep);
					}

					if (EnemyList[i]->GetCurrentHealth() <= 0)
					{
						EnemyList[i]->SetStatus(KILD);
						EnemyList[i]->SetKilledTimeStep(c);
					}
					Active_Fighters* a = NULL;
					PQ_Active_Fighters.dequeue(a);
					if (a->GetStatus() == ACTV)
						PQ_Active_Fighters.enqueueSort(a);
					if (a->GetStatus() == KILD)
					{
						Q_Killed_List.enqueue(a);
						ActiveCount--;
						ActiveFighterCount--;
						KilledCount++;

					}
					n--;
				}
			}
			//load lists

		}
			if (n >0)
			{
				// act
				//pGUI->UpdateStatusBar(90);
				//pGUI->waitForClick();
				int ActHealerCount;
				Active_Healers* const* EnemyList = S_Active_Healers.toArray(ActHealerCount);
				for (int i = 0; i < ActHealerCount && n>0; i++)
				{
					if (EnemyList[i] != NULL)
					{
						//pGUI->UpdateStatusBar(20000);
						//pGUI->waitForClick();
						if (EnemyList[i]->GetFirstTimeToShot() > 0)
							EnemyList[i]->DamageToEnemy(BCastle.GetCastlePower());
						else
						{
							EnemyList[i]->DamageToEnemy(BCastle.GetCastlePower());
							EnemyList[i]->SetFirstTimeToShot(CurrentTimeStep);
						}
						if (EnemyList[i]->GetCurrentHealth() <= 0)
						{
							EnemyList[i]->SetStatus(KILD);
							EnemyList[i]->SetKilledTimeStep(c);
							if (EnemyList[i]->GetDistance() <= 5)
							{
								BCastle.SetHealth(BCastle.GetHealth() * 130 / 100);
								
							}
						}
						Active_Healers* a = NULL;
						S_Active_Healers.pop(a);
						if (a->GetStatus() == ACTV)
							temp.push(a);
						 if (a->GetStatus() == KILD)
						{
							Q_Killed_List.enqueue(a);
							ActiveCount--;
							ActiveHealerCount--;
							KilledCount++;
						}
						 n--;
					}
					
				}
				// load lists
				Active_Healers* h;
				while (temp.pop(h))
				{
					if (h != NULL)
					{
						S_Active_Healers.push(h);
					}
				}

				if (n>0)   // freezers
				{
					//act 

					int ActfreezerCount;
					Active_Freezers* const* EnemyList = Q_Active_Freezers.toArray(ActfreezerCount);
					for (int i = 0; i < ActfreezerCount && n>0; i++)
					{
						if (EnemyList[i] != NULL)
						{

							if (EnemyList[i]->GetFirstTimeToShot() > 0)
								EnemyList[i]->DamageToEnemy(BCastle.GetCastlePower());
							else
							{
								EnemyList[i]->DamageToEnemy(BCastle.GetCastlePower());
								EnemyList[i]->SetFirstTimeToShot(CurrentTimeStep);
							}
							if (EnemyList[i]->GetCurrentHealth() <= 0)
							{
								EnemyList[i]->SetStatus(KILD);
								EnemyList[i]->SetKilledTimeStep(c);
							}
							Active_Freezers* a = NULL;
							Q_Active_Freezers.dequeue(a);
							if (a->GetStatus() == ACTV)
								qtemp.enqueue(a);
							else if (a->GetStatus() == KILD)
							{
								Q_Killed_List.enqueue(a);
								ActiveFreezerCount--;
								ActiveCount--;
								KilledCount++;
							}
							n--;
						}
					}
					//load lists
					Active_Freezers* b;
					while (qtemp.dequeue(b))
					{
						if (b != NULL)
						Q_Active_Freezers.enqueue(b);
					}
				}

			}
}

// castle -> freeze 
void Battle::CastleFreeze()
{
	int n = BCastle.GetMaxEnemyTimeStep();
	int nfi = PQ_Active_Fighters.getSize();
	int nhe = S_Active_Healers.getSize();
	int nfr = Q_Active_Freezers.getSize();
	n = n * 0.2;
	Stack<Active_Healers*> temp;
	Stack<Active_Healers*> temp2;
	Queue<Active_Freezers*> qtemp;
	Queue<Active_Freezers*> qtemp2;
	if (n > 0)
	{
		int ActFighterCount;
		Active_Fighters* const* EnemyList = PQ_Active_Fighters.toArray(ActFighterCount);
		//act
		for (int i = 0; i < ActFighterCount && n>0; i++)
		{
			if (EnemyList[i] != NULL)
			{
				EnemyList[i]->SetIceOnEnemy();
				if (EnemyList[i]->isFrosted() == true)
					EnemyList[i]->SetStatus(FRST);
				Active_Fighters* a = NULL;
				PQ_Active_Fighters.dequeue(a);
				if (a->GetStatus() == ACTV)
					PQ_Active_Fighters.enqueueSort(a);
				else if (a->GetStatus() == FRST)
				{
					PQ_Frozen_List.enqueueSort(a);
					FrostedCount++;
					ActiveCount--;
					FrostedFighterCount++;
					ActiveFighterCount--;
				}
				n--;
			}
		}
		//load lists

	}
	if (n>0)
	{
		// act
		int ActHealerCount;
		Active_Healers* const* EnemyList = S_Active_Healers.toArray(ActHealerCount);
		for (int i = 0; i < ActHealerCount && n>0; i++)
		{
			if (EnemyList[i] != NULL)
			{
				EnemyList[i]->SetIceOnEnemy();
				if (EnemyList[i]->isFrosted() == true)
					EnemyList[i]->SetStatus(FRST);
				Active_Healers* a = NULL;
				S_Active_Healers.pop(a);
				if (a->GetStatus() == ACTV)
					temp.push(a);
				else if (a->GetStatus() == FRST)
				{
					PQ_Frozen_List.enqueueSort(a);
					FrostedCount++;
					ActiveCount--;
					FrostedHealerCount++;
					ActiveHealerCount--;
				}
					n--;
				}
			}
			// load lists
			Active_Healers* b;
			while (temp.pop(b))
			{
				if (b!=NULL)
				PQ_Frozen_List.enqueueSort(b);
			}

			if (n >0)
			{
				//act 
				int ActfreezerCount;
				Active_Freezers* const* EnemyList = Q_Active_Freezers.toArray(ActfreezerCount);
				for (int i = 0; i < ActfreezerCount; i++)
				{
					if (EnemyList[i] != NULL)
					{
						EnemyList[i]->SetIceOnEnemy();
						if (EnemyList[i]->isFrosted() == true)
							EnemyList[i]->SetStatus(FRST);
						Active_Freezers* a = NULL;
						Q_Active_Freezers.dequeue(a);
						if (a->GetStatus() == ACTV)
							qtemp.enqueue(a);
						else if (a->GetStatus() == FRST)
						{
							PQ_Frozen_List.enqueueSort(a);
							FrostedCount++;
							FrostedFreezerCount++;
							ActiveCount--;
							ActiveFreezerCount--;
						}
						n--;
					}
				}
				//load lists
				Active_Freezers* c;
				while (qtemp.dequeue(c))
				{
					if (c!=NULL)
						Q_Active_Freezers.enqueue(c);
				}
			}
		}
}
void Battle::load_file(GUI* pOut)
{
	pOut->PrintMessage("enter the file name");
	string fileName = pOut->GetString();
	ifstream InFile;
	InFile.open(fileName, ios::in);
	while (!(InFile.is_open()))//check if the file opens or not if not it keeps asking for a valid name.
	{
		//pOut->ClearStatusBar();
		pOut->PrintMessage("please enter valid file name");
		fileName = pOut->GetString();
		InFile.open(fileName, ios::in);
	}

	int ch, n, cp;
	InFile >> ch >> n >> cp;

	GetCastle()->SetHealth(ch);
	GetCastle()->setCurrentHealth(ch);
	GetCastle()->SetMaxEnemyTimeStep(n);
	GetCastle()->SetCastlePower(cp);

	int c;
	InFile >> c;
	set_Enemy_Count(c);
	EnemyCount = c;
	//ActiveCount = c;
	int ID, TYP, AT, POW, RLD, SPD;
	double H;


	for (int i = 0; i < c; i++)
	{
		InFile >> ID >> TYP >> AT >> H >> POW >> RLD >> SPD;
		if (TYP == 0)
		{
			Enemy* pE;
			pE = new Active_Fighters(ID, AT);
			pE->SetEnemyType(TYP);
			pE->SetEnemyPower(POW);
			pE->SetEnemySpeed(SPD);
			pE->SetReloadPeriod(RLD);
			pE->setCurrentReloadperiod(RLD);
			pE->SetHealth(H);
			//pE->SetDistance(30);
			pE->SetCurrentHealth(H);
			pE->SetStatus(INAC); //initiall all enemies are inactive
			Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
		}
		else if (TYP == 1)
		{
			Enemy* pE;
			pE = new Active_Healers(ID, AT);
			//Active_Healers* pE = NULL;
			//pE = new Active_Healers(ID, AT,MaxDistance);
			pE->SetEnemyType(TYP);
			pE->SetEnemyPower(POW);
			pE->SetEnemySpeed(SPD);
			pE->SetReloadPeriod(RLD);
			pE->setCurrentReloadperiod(RLD);
			pE->SetHealth(H);
			//pE->SetDistance(MaxDistance);
			pE->SetCurrentHealth(H);
			pE->SetStatus(INAC); //initiall all enemies are inactive
			Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
		}
		else if (TYP == 2)
		{
			Enemy* pE;
			pE = new Active_Freezers(ID, AT);
			pE->SetEnemyType(TYP);
			pE->SetEnemyPower(POW);
			pE->SetEnemySpeed(SPD);
			pE->SetReloadPeriod(RLD);
			//pE->SetDistance(60);
			pE->setCurrentReloadperiod(RLD);
			pE->SetHealth(H);
			pE->SetCurrentHealth(H);
			pE->SetStatus(INAC); //initiall all enemies are inactive
			Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
		}
	}
}
void Battle::OutputFile()
{
	string FileName = "output";

	ofstream out("Out_" + FileName + ".txt");
	out << "Game is "<<game<<"\n";
	out << "KTS\tID\tFD\tKD\tLT\n";

	Enemy* fighter;
	int activefightercount;
	Enemy* const* FighterList = Q_Killed_List.toArray(activefightercount);
	double totF = 0;
	double totK = 0;
	for (int i = activefightercount - 1; i >= 0; i--)
	{
		fighter = FighterList[i];
		out << fighter->GetKilledTimeStep()<<"\t" << fighter->GetID() << "\t" << fighter->GetFirstShotDelay() << "\t" <<fighter->GetkilledDelay() << "\t" <<fighter->GetLifetime()<< "\n";
		totF = totF+fighter->GetFirstShotDelay();
		totK = totK + fighter->GetkilledDelay();
	}
	out << ".................................................\n.................................................\n";
	out << "Castle Total Damage ="<<BCastle.GetHealth()-BCastle.getCurrentHealth()<<" \n";
	out << "Total Enemies = " << EnemyCount<<"\n";
	out << "Average First-Shot Delay ="<<totF/ activefightercount <<"\n";
	out << "Average Kill Delay ="<<totK/ activefightercount <<"\n";
	out.close();
}
void Battle::set_Enemy_Count(int c)
{
	EnemyCount = c;
}
Battle::~Battle()
{
	delete pGUI;
}