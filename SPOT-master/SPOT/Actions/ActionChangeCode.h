#pragma once
#include "Action.h"
class ActionChangeCode :
	public Action
{
public:
	ActionChangeCode(Registrar*);
	bool virtual Execute();
	virtual ~ActionChangeCode();
};