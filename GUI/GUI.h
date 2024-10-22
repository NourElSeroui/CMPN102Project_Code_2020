#ifndef __GUI_H_
#define __GUI_H_

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"
#include "..\Enemies\Enemy.h"
#include "..\Generic_DS\Queue.h"
#include "..\Enemies\Active_Fighters.h"
#include "..\Enemies\Active_Healers.h"
#include "..\Enemies\Active_Freezers.h"
#include <string>
#include <sstream>
using namespace std;

class GUI
{
	enum GUI_REGION {	
		INAC_REG,	//GUI Regions where inactive enemies are drawn
		ACTV_REG,	//GUI Regions where active enemies are drawn
		FRST_REG,	//GUI Regions where frosted enemies are drawn
		KILD_REG,	//GUI Regions where killed enemies are drawn
		REG_CNT		//Total number of regions
	};

	string RegionsLabels[REG_CNT];

	struct DrawingItem	//holds info for each item to be drawn on screen
	{
		int ID;				//ID to be printed on the screen indicating this item
		int distance;		//ditance to be drawn at
		GUI_REGION region;	//Region where it should be drawn
		color	clr;		//drawing color
	};
private:
	window *pWind;
	color DrawingColors[ENMY_TYPE_CNT];	//drawing colors for enemies
	
	color BackgroundClr, StatusBarClr;	//Background and status bar color
	
	// Some Static Constant Data Members: ---------------------
	static const int	
		WindWidth=1200, WindHeight=650,		//Window width and height
		StatusBarHeight = 150,	//Status Bar Height
		MenuBarHeight = 0,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 80,		//Width of each item in menu bar menu
		
		DrawingAreaHeight = WindHeight - MenuBarHeight - StatusBarHeight,		
		YHalfDrawingArea = MenuBarHeight + DrawingAreaHeight/2, //The y coordinate of half the Drawing area

		CastleStartX = (int)(WindWidth * 0.45), //The x coordinate of the upper left corner of the Castle
		CastleEndX = (int)(WindWidth * 0.55),   //The x coordinate of the lower right corner of the Castle

		CastleWidth = CastleEndX - CastleStartX, //The width of the Castle (Note: the Castle is a Square)		

		CastleStartY = YHalfDrawingArea - CastleWidth/2, //The y coordinate of the upper left corner of the Castle
		CastleEndY = YHalfDrawingArea + CastleWidth/2,   //The y coordinate of the lower right corner of the Castle

		EnemyWidth = (WindWidth-CastleWidth-(MaxDistance*2))/(MaxDistance*2),  
		                                           // the width of the enemy to make 60 unit distance 
                                             	   // from the enemy to the castle
												   // and 1 blank pixel between each consecutive enemies: ((MaxDistance*2) in numurator)
		EnemyHeight = (DrawingAreaHeight-((MaxVerticalEnemies+1)*2))/((MaxVerticalEnemies+1)*2), // the height of the enemy 
	                                                          // to make any region carry 15 enemies + 1 for more space
	                                                          // also 1 blank pixel between vertical enemies


		MaxHorizEnemies	= ((WindWidth-CastleWidth)/2 ) / (EnemyWidth+1),		//The max no. of enemies the can be drwan in on Horizontal line in a region
		MaxRegionEnemyCount  = MaxHorizEnemies * MaxVerticalEnemies;

	
	static const int maxItemCnt = MaxEnemyCount;
	DrawingItem* DrawingList[maxItemCnt] ;	 //List of items pointers to be drawn every timestep
	int DrawingItemsCount;	//actual no. of items in the drawing list
	 
	// TODO: Add more members if needed

	void DrawSingleItem(const DrawingItem* pDitem, int RegionCount) const;		//draws ONE item 
	void DrawAllItems() ;		//drwas ALL items in DrawingList

	void DrawString(const int iX, const int iY, const string Text); // prints a message in the passed coordinates
	void DrawCastleArea() const;	    // draws the Castle area

	void ClearStatusBar() const;    // clears the status bar
	void ClearDrawingArea() const;	// clears the Drawing area from all drawings
	
	/*void AddFighterToDrawingList(const Active_Fighters* pE);
	void AddHealerToDrawingList(const Active_Healers* pE);
	void AddFreezerToDrawingList(const Active_Freezers* pE);*/
public:
	GUI();
	~GUI();
	// Input Functions  ---------------------------
	void waitForClick() const;	// waits a user click from the user
	string GetString() const ; // reads a string (keyboard input) from the user

	// Output Functions  ---------------------------
	void PrintMessage(string msg) const; // prints a message in the status bar
	void UpdateStatusBar(int TimeStep);	//prints info on status bar. Info includes timestep and other enemies info as illustrated in project doc
	void UpdateInterface(int TimeStep);
	void AddToDrawingList(const Enemy*);	//Adds a new enemy to the drawing queue
	void ResetDrawingList();		//resets drawing list (should be called every timestep after drawing)

	PROG_MODE getGUIMode() const;	//returns the mode of the program
};
\
#endif