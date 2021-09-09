#include "ActionUndo.h"
#include "../Registrar.h"
#include <string>
#include <iostream>

ActionUndo::ActionUndo(Registrar* P) :Action(P)
{
}
bool ActionUndo::Execute()
{
	pReg->Decrement_Current_StudyPlan();
	return true;
}

ActionUndo::~ActionUndo()
{
}