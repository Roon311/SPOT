#pragma once
#include "Action.h"
//Class responsible for adding course action
class ActionMoveCourse :
	public Action
{
public:
	ActionMoveCourse(Registrar*);
	bool virtual Execute();
	virtual ~ActionMoveCourse();
};
