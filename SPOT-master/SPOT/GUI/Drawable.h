#pragma once
#include"../GUI/GUI.h"
class GUI;

struct graphicsInfo
{
	//coords of left corner of rectangular area where this obj should be drawn
	int x = 0, y = 0;	
};
//constants related to objects to be drawn
enum
{
	CRS_WIDTH = (int)(GUI::Year_X2 * (4.0/65.0)) + 8,		//width of course rectangle to be drawn on screen
	CRS_HEIGHT = GUI::One_Semester_Div - 4,	//Height of course rectangle to be drawn on screen
	//PLAN_YEAR_WIDTH = CRS_WIDTH * 4,	//width of plan year rectangle to be drawn on screen
	//PLAN_YEAR_HEIGHT	//Height of play year rectangle to be drawn on screen
};

//Base class for all drawable classes
class Drawable
{
protected:
	//Info required for drawing
	graphicsInfo GfxInfo;
	bool Selected;	//is this obj selected (to highlight when drawing)
public:
	Drawable();
	void setGfxInfo(graphicsInfo);
	graphicsInfo getGfxInfo() const;
	void setSelected(bool );
	bool isSelected() const;
	void virtual DrawMe(GUI*) const = 0;
	Drawable::Drawable(const Drawable& CopiedDW);
	virtual ~Drawable();
};

