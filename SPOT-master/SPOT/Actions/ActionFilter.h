#pragma once
#include "Action.h"
#include"../GUI/CMUgraphicsLib/colors.h"
#include"../Courses/Course.h"

class ActionFilter :
	public Action
{
public:
	ActionFilter(Registrar*);
	bool virtual Execute();
	virtual ~ActionFilter();
	void Filteringyear(int inputyear);
	void Filteringsemester(int inputsem);
	void Filteringcolour(color col);
	void FilteringType(Type type);
	void FilteringDoneOrNot(bool Input);
	//void FilteringStatus(string s);
	void UNFiltering();
};
