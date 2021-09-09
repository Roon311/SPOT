#pragma once
#include"Registrar.h"
#include<iostream>
#include<iterator>
#include<vector>
using namespace std;

//Class responsible for adding course action
class Maestro 
{
	Registrar* pReg;
	friend class Registrar;
	vector<Registrar*>List_Of_Spots;
	vector<window*>List_Of_windows;
	int Current_Spot = 0;
	static const int
		MaestroWindWidth = 400,
		MaestroWindowHeight = 150,
		StartX = (GUI::WindWidth / 2) - (MaestroWindWidth / 2),
		StartY = (GUI::WindHeight / 2) - (MaestroWindowHeight / 2);
	color BackgroundColor = WHITE;
public:
	static window* pMaestroWind;
	Maestro();
	void Run();
	void AddSpot();
	void DeleteSpot(int Number);
	void UpdateWind();
	void ClearDrawingArea();
	/*bool ExecuteAction(Action*);*/
	~Maestro();
};