#pragma once
#include "Action.h"
//Class responsible for saving study plan
class ActionUndo : public Action
{
public:
	ActionUndo(Registrar*);
	virtual ~ActionUndo();
	bool virtual Execute();
};