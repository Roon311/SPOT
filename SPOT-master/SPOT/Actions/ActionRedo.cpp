#include "ActionRedo.h"
#include "../Registrar.h"
#include <string>
#include <iostream>

ActionRedo::ActionRedo(Registrar* P) :Action(P)
{
}
bool ActionRedo::Execute()
{
	pReg->Increment_Current_StudyPlan();
	return true;
}

ActionRedo::~ActionRedo()
{
}