#pragma once
#include "Action.h"
#include"../GUI/GUI.h"
//Class responsible for adding course action
class ActionDeclareMinor :
	public Action
{
private:
	window* pMinorWind;

	static const int
		MinorWindWidth = 500,
		MinorWindowHeight = 200,
		StartX = (GUI::WindWidth / 2) - (MinorWindWidth / 2),
		StartY = (GUI::WindHeight / 2) - (MinorWindowHeight / 2);
		color BackgroundColor = WHITE;
public:
	ActionDeclareMinor(Registrar*);
	bool virtual Execute();
	virtual ~ActionDeclareMinor();
	// window stuff
	void UpdateWind() const;
	void ClearDrawingArea() const;
};


