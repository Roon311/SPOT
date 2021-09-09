#pragma once
#include "Action.h"
#include"../GUI/GUI.h"
class ActionDeclareMajor :
    public Action
{
private:
	window* pMajorWind;

	static const int
		MajorWindWidth = 800,
		MajorWindowHeight = 600,
		StartX = (GUI::WindWidth / 2) - (MajorWindWidth / 2),
		StartY = (GUI::WindHeight / 2) - (MajorWindowHeight / 2);
	color BackgroundColor = WHITE;

public:
	ActionDeclareMajor(Registrar*);
	bool virtual Execute();
	virtual ~ActionDeclareMajor();
	void UpdateWind() const;
	void ClearDrawingArea() const;
};

