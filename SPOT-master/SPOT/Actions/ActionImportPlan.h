#pragma once
#include "Action.h"

class ActionImportPlan : public Action
{
public:
	ActionImportPlan(Registrar*);
	bool virtual Execute();
	virtual ~ActionImportPlan();
};

