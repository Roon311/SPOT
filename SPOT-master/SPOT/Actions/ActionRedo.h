#pragma once
#include "Action.h"
//Class responsible for saving study plan
class ActionRedo: public Action
{
public:
	ActionRedo(Registrar*);
	virtual ~ActionRedo();
	bool virtual Execute();
};
